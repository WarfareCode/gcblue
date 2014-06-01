/** 
** @file tcStores.cpp
*/  
/*
**  Copyright (c) 2014, GCBLUE PROJECT
**  All rights reserved.
**
**  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
**
**  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
**
**  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the 
**     documentation and/or other materials provided with the distribution.
**
**  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from 
**     this software without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
**  NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
**  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
**  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
**  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
**  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "stdwx.h" // precompiled header file

#include "tcStores.h"

#include "tcLauncher.h"
#include "tcMessageInterface.h"
#include "tcGameObject.h"
#include "tcPlatformObject.h"
#include "tcAirObject.h"
#include "tcStoresDBObject.h"
#include <iostream>
#include "common/tcObjStream.h"
#include "tcGameStream.h"
#include "tcDatabase.h"
#include "tcAirDBObject.h"
#include "tcPlatformDBObject.h"
#include "tcFuelTankDBObject.h"
#include "tcCounterMeasureDBObject.h"
#include "tcWeaponDBObject.h"
#include "tcMissileDBObject.h"
#include "tcTorpedoDBObject.h"
#include "tcBallisticDBObject.h"
#include "tcFlightOpsObject.h"
#include "tcFlightPort.h"
#include "tcScenarioLogger.h"
#include "tcSimState.h"
#include <limits>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

tcDatabaseObject* tcStores::StoreItem::GetDatabaseObject() const
{
    return databaseObj;
}

tcDatabaseObject* tcStores::StoreItem::GetOrLoadDatabaseObject()
{
    if (databaseObj != 0)
    {
        return databaseObj;
    }
    else
    {
        LoadDatabaseObject();
        return databaseObj;
    }
}

void tcStores::StoreItem::SetDatabaseObject(tcDatabaseObject* obj)
{
	databaseObj = obj;
}

/**
* Set pointer to database object associated with
* this item.
*/
void tcStores::StoreItem::LoadDatabaseObject()
{
    databaseObj = tcDatabase::Get()->GetObject(className);
    
    if (databaseObj == 0)
    {
        fprintf(stderr, "tcStores::StoreItem::LoadDatabaseObject - "
            "Can't find %s in database\n", className.c_str());
        wxASSERT(false);
    }
}

tcStores::StoreItem::StoreItem()
:   databaseObj(0),
    quantity(0),
    itemId(0)
{
}

tcStores::StoreItem::StoreItem(const StoreItem& src)
:   className(src.className), 
    quantity(src.quantity),
    databaseObj(src.databaseObj),
    itemId(src.itemId)
{
}

tcStores::StoreItem::StoreItem(const std::string& name, unsigned long qty, unsigned int id)
:   className(name), 
    quantity(qty),
    itemId(id)
{
    LoadDatabaseObject();
}


tcGameObject* tcStores::StoreOperation::GetObj()
{   
    if (tcGameObject* obj = tcSimState::Get()->GetObject(platformId))
    {
        if (childId == -1)
        {
            return obj;
        }
        else
        {
            return obj->GetChildById(long(childId));
        }
    }
    else
    {
        return 0;
    }
}



/**
*
*/
tcCreateStream& tcStores::operator<<(tcCreateStream& stream)
{
    return stream;
}


/**
*
*/
tcCreateStream& tcStores::operator>>(tcCreateStream& stream)
{

    return stream;
}


/**
* Loads state from update stream
*/
tcUpdateStream& tcStores::operator<<(tcUpdateStream& stream)
{
	tcDatabase* database = tcDatabase::Get();

	/* delete and rebuild stores for each update
	** might be more efficient to search and selectively update?
	*/
	stores.clear();

	unsigned char nItems;
	stream >> nItems;

	for (unsigned char n=0; n<nItems; n++)
	{
		long id;
		stream >> id;
		
		unsigned long quantity;
		stream >> quantity;

        unsigned int itemId;
        stream >> itemId;

		tcDatabaseObject* databaseObj = database->GetObject(id);
		
		if (databaseObj == 0)
		{
			wxASSERT(false);
			fprintf(stderr, "tcStores::operator<<(tcUpdateStream& stream) - not found in DB\n");
			return stream;
		}

		std::string itemName(databaseObj->mzClass.c_str());
		AddItemsForceId(itemName, quantity, itemId);
	}

    return stream;
}

/**
* Saves state to update stream
*/
tcUpdateStream& tcStores::operator>>(tcUpdateStream& stream)
{
	unsigned char nItems = stores.size();
	stream << nItems;
	for (unsigned char n=0; n<nItems; n++)
	{
		tcDatabaseObject* databaseObj = stores[n].GetDatabaseObject();
		long databaseId = databaseObj->mnKey;
		unsigned long quantity = stores[n].quantity;
        unsigned int itemId = stores[n].itemId;
		
		stream << databaseId;
		stream << quantity;
        stream << itemId;
	}

    return stream;
}





/**
* Load from command stream
*/
tcCommandStream& tcStores::operator<<(tcCommandStream& stream)
{
    unsigned char nCommands;
	stream >> nCommands;

	for (unsigned char n=0; n<nCommands; n++)
	{
		short int id;
		unsigned char op;
		long itemId = -1;
		unsigned long quantity = 0;
        unsigned char launcherIdx = 99;
		std::string type;

        stream >> id;
		stream >> op;

		if (op != StoreOperation::AUTOMATION)
		{
			stream >> itemId;
			stream >> quantity;
			stream >> launcherIdx;
		}
		else
		{
			stream >> type;
		}
		
		bool ok = true;
		tcGameObject* obj = 0;
		if (id != -1)
		{
            obj = parent->GetChildById(id);
            if (obj == 0) ok = false;
        }

		if (ValidateOpObject(obj) == false)
		{
			ok = false;
		}
		

        std::string item;
		if ((op != StoreOperation::UNLOAD) && (op != StoreOperation::AUTOMATION))
        {
            tcDatabaseObject* databaseObj = tcDatabase::Get()->GetObject(itemId);
            if (databaseObj == 0)
            {
                ok = false;
            }
            else
            {
                item = databaseObj->mzClass.c_str();
            }
        }

        if (ok)
        {
			if (op == StoreOperation::AUTOMATION)
			{
				AddAutomationOp(type, obj);
			}
            else if (op == StoreOperation::LOAD)
            {
                LoadLauncher(launcherIdx, item, obj);
            }
            else if (op == StoreOperation::UNLOAD)
            {
                UnloadLauncher(launcherIdx, obj); 
            }
            else if (op == StoreOperation::REFUEL)
            {
                LoadOther(item, quantity, obj);
            }
            else
            {
                fprintf(stderr, "tcStores::operator<< -- Bad op (%d)\n", op);
                wxASSERT(false);
            }
        }
        
	}
        
    return stream;
}

/**
* Save to command stream
*/
tcCommandStream& tcStores::operator>>(tcCommandStream& stream)
{
	unsigned char nCommands = commandList.size();
	stream << nCommands;

	for (unsigned char n=0; n<nCommands; n++)
	{
        CommandInfo& cmd = commandList[n];
        
 		stream << cmd.id;
		stream << cmd.op;
		if (cmd.op != StoreOperation::AUTOMATION)
		{
			stream << cmd.itemId;
			stream << cmd.quantity;
			stream << cmd.launcherIdx;
		}
		else
		{
			stream << cmd.type;
		}
	}

    return stream;
}


/**
* Loads state from game stream
*/
tcGameStream& tcStores::operator<<(tcGameStream& stream)
{
    stream >> errorCode;
    stream >> lastUpdate;

	tcDatabase* database = tcDatabase::Get();

    // ---------- load stores ----------
	stores.clear();
	unsigned char nItems;
	stream >> nItems;
	for (unsigned char n=0; n<nItems; n++)
	{
        std::string itemName;
		stream >> itemName;
		
		unsigned long quantity;
		stream >> quantity;

		tcDatabaseObject* databaseObj = database->GetObject(itemName);
		
		if (databaseObj == 0)
		{
			wxASSERT(false);
            fprintf(stderr, "tcStores::operator<<(tcUpdateStream& stream) - Warning, %s not found in DB\n", itemName.c_str());
		}

		AddItems(itemName, quantity);
	}

    // ---------- load store operations ----------
    ops.clear();
    unsigned char nOps;
    stream >> nOps;
    for (unsigned char n=0; n<nOps; n++)
    {
        StoreOperation op;
        stream >> op.item;        
        stream >> op.quantity; ///< quantity of item
        stream >> op.timeToComplete; ///< time left for op to complete [s]
        stream >> op.timeElapsed;
        stream >> op.launcherIdx; ///< launcher idx to transfer to/from
        stream >> op.transferType; ///< UNLOAD or LOAD

        stream >> op.platformId;
        stream >> op.childId;

        //long objId; // = (ops[n].obj == 0) ? -1 : ops[n].obj->mnID;
        //stream >> objId;
        //if (objId == -1)
        //{
        //    op.obj = 0;
        //}
        //else
        //{
        //    op.obj = parent->GetChildById(objId);
        //    wxASSERT(op.obj != 0);
        //}

        ops.push_back(op);
    }

    // ---------- load automation operations ----------
    automationOps.clear();
    unsigned char nAutomationOps;
    stream >> nAutomationOps;
    for (unsigned char n=0; n<nAutomationOps; n++)
    {
        AutomationOperation autoOp;
        stream >> autoOp.type;
        stream >> autoOp.stage;

        long objId; // = (automationOps[n].obj == 0) ? -1 : automationOps[n].obj->mnID;
        stream >> objId;
        if (objId == -1)
        {
            autoOp.obj = 0;
        }
        else
        {
            autoOp.obj = parent->GetChildById(objId);
            wxASSERT(autoOp.obj != 0);
        }

        automationOps.push_back(autoOp);
    }

    // ---------- load command list ----------
    commandList.clear();
    unsigned char nCommands;
    stream >> nCommands;
    for (unsigned char n=0; n<nCommands; n++)
    {
        CommandInfo cmd;
		stream >> cmd.id;
		stream >> cmd.op;
		stream >> cmd.itemId;
		stream >> cmd.quantity;
		stream >> cmd.launcherIdx;
		stream >> cmd.type;

        commandList.push_back(cmd);
    }

    stream.ReadCheckValue(9876);

    return stream;
}

/**
* Saves state to game stream
*/
tcGameStream& tcStores::operator>>(tcGameStream& stream)
{
    stream << errorCode;
    stream << lastUpdate;

    wxASSERT(stores.size() < 256);
	unsigned char nItems = stores.size();
	stream << nItems;
	for (unsigned char n=0; n<nItems; n++)
	{
		//tcDatabaseObject* databaseObj = stores[n].GetDatabaseObject();
        std::string itemName = stores[n].className;
		unsigned long quantity = stores[n].quantity;
		
		stream << itemName;
		stream << quantity;
	}

    wxASSERT(ops.size() < 256);
    unsigned char nOps = ops.size();
    stream << nOps;
    for (unsigned char n=0; n<nOps; n++)
    {
        stream << ops[n].item;        
        stream << ops[n].quantity; ///< quantity of item
        stream << ops[n].timeToComplete; ///< time left for op to complete [s]
        stream << ops[n].timeElapsed;
        stream << ops[n].launcherIdx; ///< launcher idx to transfer to/from
        stream << ops[n].transferType; ///< UNLOAD or LOAD

        stream << ops[n].platformId;
        stream << ops[n].childId;

        //long objId = (ops[n].obj == 0) ? -1 : ops[n].obj->mnID;
        //stream << objId;
    }

    wxASSERT(automationOps.size() < 256);
    unsigned char nAutomationOps = automationOps.size();
    stream << nAutomationOps;
    for (unsigned char n=0; n<nAutomationOps; n++)
    {
        stream << automationOps[n].type;
        stream << automationOps[n].stage;

        long objId = (automationOps[n].obj == 0) ? -1 : automationOps[n].obj->mnID;
        stream << objId;
    }

    wxASSERT(commandList.size() < 256);
    unsigned char nCommands = commandList.size();
    stream << nCommands;
    for (unsigned char n=0; n<nCommands; n++)
    {
		stream << commandList[n].id;
		stream << commandList[n].op;
		stream << commandList[n].itemId;
		stream << commandList[n].quantity;
		stream << commandList[n].launcherIdx;
		stream << commandList[n].type;
    }

    stream.WriteCheckValue(9876);

    return stream;
}




void tcStores::ClearNewCommand()
{
	commandList.clear();
}

bool tcStores::HasNewCommand() const
{
	return (commandList.size() > 0);
}


/**
* Adds new automation operation used to set platform to one of several generic
* configurations.
* @param type "Empty" empty all launchers, "AAW" anti-air warfare, "ASuW" antisurface warfare, "ASW" antisubmarine warfare, "Strike" ground strike
*/
void tcStores::AddAutomationOp(const std::string& type, tcGameObject* child)
{
	if (type == "Error")
	{
		wxASSERT(false);
		return;
	}

	if (parent->IsClientMode())
	{
		CommandInfo cmd;

		if (child->parent != 0)
		{
			cmd.id = child->mnID;
		}
		else
		{
			cmd.id = -1;
		}

		cmd.op = StoreOperation::AUTOMATION;
		cmd.itemId = -1;
		cmd.quantity = 0;
		cmd.launcherIdx = 0;
		cmd.type = type;

		commandList.push_back(cmd);

		return;
	}

	// first search for any existing ops with this child and remove
	std::vector<AutomationOperation> temp;
	for (size_t n=0; n<automationOps.size(); n++)
	{
		if (automationOps[n].obj != child)
		{
			temp.push_back(automationOps[n]);
		}
		else if (automationOps[n].type == type)
		{
			return; // op already exists, don't add again
		}
	}
	automationOps = temp;


	AutomationOperation op;
	op.type = type;
	op.obj = child;
	op.stage = 0;

	automationOps.push_back(op);
}


/**
*
*/
bool tcStores::AddItems(const std::string& item, unsigned long quantity)
{
    tcDatabaseObject* databaseObject = tcDatabase::Get()->GetObject(item);

    if (databaseObject == 0)
    {
        fprintf(stderr, "tcStores::AddItems -- not found (%s)\n", item.c_str());
        return false; // not found in database
    }

    unsigned long freeCapacity = GetFreeCapacityForItem(databaseObject->weight_kg, databaseObject->volume_m3);

    if ((freeCapacity > 0) && IsCompatible(item))
    {
        if (quantity > (unsigned)freeCapacity) quantity = (unsigned)freeCapacity;

        for (size_t n=0; n<stores.size(); n++)
        {
            if (stores[n].className == item)
            {
                stores[n].quantity += quantity;
                UpdateWeightAndVolume();
                return true;
            }
        }

		if (quantity > 0)
		{
			stores.push_back(StoreItem(item, quantity, nextItemId++));
		}
        UpdateWeightAndVolume();
		return true;
    }
	else
	{
		return false;
	}
}

bool tcStores::AddItemsForceId(const std::string& item, unsigned long quantity, unsigned int itemId)
{
    tcDatabaseObject* databaseObject = tcDatabase::Get()->GetObject(item);

    if (databaseObject == 0)
    {
        fprintf(stderr, "tcStores::AddItemsForceId -- not found (%s)\n", item.c_str());
        return false; // not found in database
    }

    unsigned long freeCapacity = GetFreeCapacityForItem(databaseObject->weight_kg, databaseObject->volume_m3);
    if ((freeCapacity > 0) && IsCompatible(item))
    {
        if (quantity > (unsigned)freeCapacity) quantity = (unsigned)freeCapacity;

        stores.push_back(StoreItem(item, quantity, itemId));
        UpdateWeightAndVolume();
        return true;
    }
    else
    {
        return false;
    }
}


void tcStores::RemoveAllItems()
{
    stores.clear();
    ops.clear();
	automationOps.clear();
    commandList.clear();

    weight_kg = 0;
    volume_m3 = 0;
}

/**
* Removes specified items from stores.
* @return true if any of specified type were removed
*/
bool tcStores::RemoveItems(const std::string& item, unsigned long quantity)
{
    wxASSERT(quantity > 0); // technically not a problem, but this shouldn't happen

    bool found = false;
    int nStores = (int)stores.size();
    unsigned long removeQuantity = 0;
    for (int k=nStores-1; (k>=0) && !found; k--)
    {
        if (stores[k].className == item)
        {
            found = true;
            wxASSERT(stores[k].quantity);
            if (stores[k].quantity >= (unsigned)quantity)
            {
                removeQuantity = (unsigned)quantity;
            }
            else
            {
                removeQuantity = stores[k].quantity;
            }
            stores[k].quantity -= removeQuantity;
            if (stores[k].quantity == 0)
            {
                stores.erase(stores.begin()+k);
            }

            UpdateWeightAndVolume();
        }
    }

    return found;
}


bool tcStores::AddOperation(const std::string& itemName, unsigned int launcherIdx, unsigned long quantity, float transferTime_s,
							int opType, tcGameObject* obj)
{
	/* Search for existing op with launcher (or platform for REFUEL)
	** opType 
	** LOAD - Search for existing LOAD and UNLOAD ops
	**        If existing op is UNLOAD, then ignore this add request and return
	**        If existing op is LOAD and item is the same, then ignore and return
	**        If existing op is LOAD and item is different, then switch to new item (new items already removed from stores)
	** UNLOAD - Search for existing LOAD and UNLOAD ops
	**        If existing op is UNLOAD, then ignore this add request and return
	**        If existing op is LOAD then cancel the load op and return items to stores
	** REFUEL - Search for existing REFUEL or DEFUEL ops
	**        If found then ignore this add request and return
	** DEFUEL - Search for existing REFUEL or DEFUEL ops
	**        If found then ignore this add request and return
	*/

	if (parent->IsClientMode())
	{
		CommandInfo cmd;

		tcDatabaseObject* databaseObj = tcDatabase::Get()->GetObject(itemName);
		if (databaseObj == 0)
		{
			wxASSERT(false);
			return false;
		}
        
        
		cmd.id = ((obj != 0) && (obj->parent != 0)) ? obj->mnID : -1;
		cmd.op = opType;
		cmd.itemId = databaseObj->mnKey;
		cmd.quantity = quantity;
		cmd.launcherIdx = launcherIdx;

		commandList.push_back(cmd);
		return true;
	}


	bool isLoadOp = (opType == StoreOperation::LOAD);
	bool isUnloadOp = (opType == StoreOperation::UNLOAD);
    bool isFuelOp = (opType == StoreOperation::REFUEL) || (opType == StoreOperation::DEFUEL);
    //bool isMoveOp = (opType == StoreOperation::MOVE);

    bool found = false;
    std::vector<StoreOperation>::iterator opIter;
    std::vector<StoreOperation>::iterator matchIter;
    for (opIter = ops.begin(); (opIter != ops.end()) && (!found); ++opIter)
    {
        bool allowMatch = (isLoadOp && (opIter->transferType != StoreOperation::REFUEL) && (opIter->transferType != StoreOperation::DEFUEL)) ||
			              (isUnloadOp && (opIter->transferType != StoreOperation::REFUEL) && (opIter->transferType != StoreOperation::DEFUEL)) ||
			              (isFuelOp && (opIter->transferType == StoreOperation::REFUEL)) ||
                          (isFuelOp && (opIter->transferType == StoreOperation::DEFUEL));

        if ((opIter->GetObj() == obj) && (allowMatch) && (opIter->launcherIdx == launcherIdx))
        {
            matchIter = opIter;
            found = true;
        }
    }

	bool success = false;
	wxString msg;

    if (found) // do nothing, modify existing op, or cancel existing op
    {
		if (matchIter->transferType == StoreOperation::UNLOAD)
		{            
			msg = wxString::Format("%s (%s) - Unload of %s to %s must finish\n", 
				obj->mzUnit.c_str(), obj->mzClass.c_str(), 
				matchIter->item.c_str(), storesDBObj->displayName.c_str());
		}
		else if (matchIter->transferType == StoreOperation::LOAD)
		{
			if (isLoadOp && (matchIter->item == itemName))
			{
				msg = wxString::Format("%s (%s) - Already loading %s\n", 
				    obj->mzUnit.c_str(), obj->mzClass.c_str(), itemName.c_str());
			}
			else if (isLoadOp)
			{
				msg = wxString::Format("%s (%s) - load in progress, cant load %s\n", 
				    obj->mzUnit.c_str(), obj->mzClass.c_str(), itemName.c_str());
			}
			else // isUnloadOp
			{
				msg = wxString::Format("%s (%s) - load in progress, cant unload\n", 
				    obj->mzUnit.c_str(), obj->mzClass.c_str());
			}
		}
		else // if (matchIter->transferType == REFUEL) || (matchIter->transferType == DEFUEL)
		{
			msg = wxString::Format("%s (%s) - Already refueling or defueling\n", 
				obj->mzUnit.c_str(), obj->mzClass.c_str());
		}   
    }
	else // add new operation
	{
		StoreOperation op;

		op.item = itemName;
		op.launcherIdx = launcherIdx;
		op.quantity = quantity;
		op.timeToComplete = transferTime_s;
        op.timeElapsed = 0;
		op.transferType = opType;
        op.opId = nextItemId++;

        if (obj == 0)
        {
            op.platformId = parent->mnID;
            op.childId = -1;
        }
        else if (obj->parent != 0)
        {
            op.platformId = obj->parent->mnID;
            op.childId = obj->mnID;
        }
        else
        {
            op.platformId = obj->mnID;
            op.childId = -1;
        }

		ops.push_back(op);

		msg = wxString::Format("%s (%s) - Starting op with %s\n", 
			obj->mzUnit.c_str(), obj->mzClass.c_str(), op.item.c_str());

		success = true;
	}

	tcMessageInterface::Get()->ChannelMessage("Info", msg.ToStdString(), obj->GetAlliance());
	
	return success;
}

/**
* @return true if operation found and canceled, false otherwise
*/
bool tcStores::CancelOperation(unsigned char id)
{
    int nOps = (int)ops.size();
    for (int n=nOps-1; n>=0; n--)
    {
        if (ops[n].opId == id)
        {
            switch (ops[n].transferType)
            {
            case StoreOperation::MOVE:
                {
                // add op to move items back into this stores
                unsigned int myIndex = GetMyStoresIndex();
                float transferTime_s = ops[n].timeElapsed;
                AddOperation(ops[n].item, myIndex, ops[n].quantity, transferTime_s, StoreOperation::MOVE, parent);
                }
                break;
            case StoreOperation::REFUEL: 
            case StoreOperation::LOAD:
                AddItems(ops[n].item, ops[n].quantity); // instant cancel for these for now
                break;
            case StoreOperation::UNLOAD:
                break; // instant cancel for unload for now
            }

            ops.erase(ops.begin()+n);
            return true;
        }
    }

    return false;
}

/**
* Complete load or unload operation, updating stores and launcher
*/
void tcStores::CompleteOperation(tcStores::StoreOperation& op)
{
    tcGameObject* obj = op.GetObj();
    

    if (obj == 0) // object left or destroyed
    {
        AddItems(op.item, op.quantity);
        return;
    }

    if (op.transferType == StoreOperation::MOVE)
    {
        CompleteMoveOperation(op, obj);
        return;
    }
     
    tcLauncher* launcher = obj->GetLauncher(op.launcherIdx);
    wxASSERT(launcher || (op.transferType == StoreOperation::REFUEL));
    if (!launcher && (op.transferType != StoreOperation::REFUEL)) return;

    if (op.transferType == StoreOperation::LOAD)
    {
		launcher->SetChildQuantity(launcher->mnCurrent + op.quantity);
    }
	else if (op.transferType == StoreOperation::REFUEL)
	{
		if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj))
		{
			platform->fuel_kg += float(op.quantity);
			float fuelCapacity_kg = platform->GetFuelCapacity();
			if (platform->fuel_kg > fuelCapacity_kg)
			{
				platform->fuel_kg = fuelCapacity_kg;
			}
			platform->SetRefueling(false);
		}
	}
    else if (op.transferType == StoreOperation::DEFUEL)
    {
		if (tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj))
		{
			platform->fuel_kg -= float(op.quantity);
			if (platform->fuel_kg < 0)
			{
				platform->fuel_kg = 0;
			}
			platform->SetRefueling(false);
            AddItems(op.item, op.quantity);
		}
    }
    else // (op.transferType == StoreOperation::UNLOAD)
    {
        wxASSERT(op.transferType == StoreOperation::UNLOAD);
        wxASSERT(op.quantity < MAXSHORT);
        wxASSERT(launcher->mnCurrent >= short(op.quantity));
        op.quantity = std::min(op.quantity, (unsigned long)launcher->mnCurrent);
        AddItems(op.item, op.quantity);
        launcher->SetChildQuantity(launcher->mnCurrent - short(op.quantity));
    }

}

void tcStores::CompleteMoveOperation(tcStores::StoreOperation& op, tcGameObject* obj)
{
    tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj);
    if (platform == 0)
    {
        wxASSERT(false);
        AddItems(op.item, op.quantity);
        return;
    }

    tcStores* stores = platform->GetMagazine(op.launcherIdx);

    if (stores == 0)
    {
        wxASSERT(false);
        AddItems(op.item, op.quantity);
        return;
    }

    if (!stores->IsCompatible(op.item))
    {
        wxASSERT(false); // should have already check for this
        AddItems(op.item, op.quantity);
        return;
    }

    stores->AddItems(op.item, op.quantity);
}

/**
* @return current quantity of item available in magazine
* Modified to use mask with ? and * characters. If more than one item match, this only returns info
* on the first match
*/
unsigned long tcStores::CurrentItemQuantity(const std::string& itemMask, std::string& matchingItem) const
{
    wxString s;

    for (size_t n=0; n<stores.size(); n++)
    {
        s = stores[n].className.c_str();
        if (s.Matches(itemMask.c_str()))
        {
            matchingItem = s.c_str(); // handles soft match with ?,*
            return stores[n].quantity;
        }
    }

    return 0;
}

/**
* @return current quantity of stores, not including incoming unloads
* @see tcStores::IncomingQuantity
*/
unsigned long tcStores::CurrentQuantity() const
{
    unsigned long currentCount = 0;
    for (size_t n=0; n<stores.size(); n++)
    {
        currentCount += stores[n].quantity;
    }

    return currentCount;
}


/**
* Helper method to support operations between tcStores and 
* child object of parent. 
* @return host parent (of stores) if child is 0, child if child is valid (if e.g. this is flightport stores and child is an aircraft in the flightport), 0 otherwise
*/
tcGameObject* tcStores::GetChildOrParent(tcGameObject* child)
{
    wxASSERT(parent);
    
    if ((child == 0) || (child == parent))
    {
        return parent;
    }
    else if (parent->IsChild(child))
    {
        return child;
    }
    else
    {
        fprintf(stderr, "tcStores::GetChildOrParent - Child not found\n"); 
        return 0;
    }
}

/**
* @return true if stores operation is allowed between this stores obj and destination obj 
*/
bool tcStores::StoresOperationAllowed(tcPlatformObject* destination) const
{
    wxASSERT(parent != 0);

    return (destination == parent) || 
        ((destination != 0) && (destination->IsChild(parent) || parent->IsChild(destination)));
}

tcStoresDBObject* tcStores::GetDatabaseObject() const
{
	return storesDBObj;
}

/**
* Uses linear search
* @return database object for item or 0 if not found
*/
tcDatabaseObject* tcStores::GetDatabaseObjectForItem(const std::string& item) const
{
    for (size_t n=0; n<stores.size(); n++)
    {
        if (stores[n].className == item)
        {
            return stores[n].GetDatabaseObject();
        }
    }

    return 0;    
}

const std::string& tcStores::GetDisplayName() const
{
	wxASSERT(storesDBObj != 0);

	return storesDBObj->displayName;
}

const wxString& tcStores::GetFilledStatusString() const
{
    static wxString s;

    s.clear();

    if (storesDBObj->capacity > 0)
    {
        s += wxString::Format("C: %03.1f%%", 100.0f*float(CurrentQuantity())/float(storesDBObj->capacity));
    }

    if (storesDBObj->maxVolume_m3 > 0)
    {
        s += wxString::Format(" V: %03.1f%%", 100.0f*volume_m3/float(storesDBObj->maxVolume_m3));
    }

    if (storesDBObj->maxWeight_kg > 0)
    {
        s += wxString::Format(" W: %03.1f%%", 100.0f*weight_kg/float(storesDBObj->maxWeight_kg));
    }

    return s;
}

unsigned long tcStores::GetFreeCapacityForItem(float itemWeight_kg, float itemVolume_m3) const
{
    wxASSERT(storesDBObj);
	wxASSERT((storesDBObj->capacity >= CurrentQuantity()) || (storesDBObj->capacity == 0));

    long countCapacity = (storesDBObj->capacity > 0) ? (long)storesDBObj->capacity : std::numeric_limits<long>::max();
        
    long freeCapacity = countCapacity - CurrentQuantity();

    long volumeCapacity = std::numeric_limits<long>::max();
    if ((storesDBObj->maxVolume_m3 > 0) && (itemVolume_m3 > 0))
    {
        volumeCapacity = floorf((storesDBObj->maxVolume_m3 - volume_m3) / itemVolume_m3);
        freeCapacity = std::min(freeCapacity, volumeCapacity);
    }

    long weightCapacity = std::numeric_limits<long>::max();
    if ((storesDBObj->maxWeight_kg > 0) && (itemWeight_kg > 0))
    {
        weightCapacity = floorf((storesDBObj->maxWeight_kg - weight_kg) / itemWeight_kg);
        freeCapacity = std::min(freeCapacity, weightCapacity);
    }

    return (freeCapacity >= 0) ? (unsigned long)freeCapacity : 0;
}

const tcStores::StoreItemInfo& tcStores::GetItemInfo(size_t idx) const
{
    static StoreItemInfo info;
    if (idx < stores.size())
    {
        info.className = stores[idx].className;
        info.quantity = stores[idx].quantity;
        info.id = stores[idx].itemId;
        return info;
    }
    else
    {
        info.className.clear();
        info.quantity = 0;
        info.id = 0;
        return info;
    }

}

const std::string& tcStores::GetItemName(unsigned int idx) const
{
	static std::string errorString = "Error";

	if (idx >= stores.size())
	{
		return errorString;
	}
	else
	{
		return stores[idx].className;
	}
}

/**
* @return list of items/qtys of ongoing move operations
*/
const std::vector<tcStores::StoreItemInfo>& tcStores::GetMoveSummary() const
{
    static std::vector<tcStores::StoreItemInfo> moveSummary;
    moveSummary.clear();

    if (parent->IsEditMode()) return moveSummary;

    int nOps = (int)ops.size();
    for (int n=nOps-1; n>=0; n--)
    {
        if ((ops[n].transferType == StoreOperation::MOVE) && (ops[n].timeToComplete > 0))
        {
            StoreItemInfo info;
            info.className = ops[n].item;
            info.quantity = ops[n].quantity;
            info.id = ops[n].opId;

            moveSummary.push_back(info);
        }
    }

    return moveSummary;
}

/**
* @return index of this stores within parent
*/
size_t tcStores::GetMyStoresIndex() const
{
    wxASSERT(parent != 0);

    size_t nStores = parent->GetMagazineCount();
    for (size_t n=0; n<nStores; n++)
    {
        if (parent->GetMagazine(n) == this)
        {
            return n;
        }
    }

    wxASSERT(false); // not found
    return 99;
}


unsigned int tcStores::GetNumberItemTypes() const
{
	return stores.size();
}


tcGameObject* tcStores::GetParent() const
{
    return parent;
}

/**
* @return quantity of stores being unloaded into stores
* @see tcStores::CurrentQuantity
*/
unsigned long tcStores::IncomingQuantity() const
{
    unsigned long currentCount = 0;

    for (size_t k=0; k<ops.size(); k++)
    {
        if (ops[k].transferType == StoreOperation::UNLOAD)
        {
            currentCount += ops[k].quantity;
        }
    }

	return currentCount;
}

/**
*
*/
bool tcStores::IsCompatible(const std::string& item) const
{
    wxASSERT(storesDBObj);
    
    size_t nCompatible = storesDBObj->compatibleItems.size();
    
    /* if no compatible items are entered, all items are compatible.
    ** This can be used for airfield depots or other general storage */
    if (nCompatible == 0) return true;
    
    for (size_t n=0; n<nCompatible; n++)
    {
        if (storesDBObj->compatibleItems[n] == item) return true;
    }
    return false;
}

/**
* Only checks quantity restrictions, not weight or volume. Stores capacity of zero means unlimited capacity.
*/
bool tcStores::IsFull() const
{
    unsigned long currentQuantity = CurrentQuantity();
	unsigned long incomingQuantity = IncomingQuantity();

    return (storesDBObj->capacity > 0) && ((currentQuantity + incomingQuantity) >= storesDBObj->capacity);
}

/**
* Loads exactly one item into launcher
*/
bool tcStores::LoadLauncher(unsigned int idx, const std::string& item, 
        tcGameObject* child, unsigned int maxToLoad)
{
    if (item.size() == 0) return false;

    if (tcAirObject* air = dynamic_cast<tcAirObject*>(child))
    {
        if (air->MaintenanceHold()) return false;
    }

    tcGameObject* obj = GetChildOrParent(child);
    
    if (obj == 0)
	{
        wxString s = wxString::Format("%s (%s) - Cannot load launcher, no access to magazine\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());

		return false;
	}


    tcLauncher* launcher = obj->GetLauncher(idx);
    wxASSERT(launcher);
    if (!launcher) return false;

    if ((obj->parent == 0) && (!launcher->isReloadable))
    {
        wxString s = wxString::Format("%s (%s) - Launcher doesnt allow underway reload\n",
            obj->mzUnit.c_str(), obj->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

        return false; // launcher not empty
    }

	if (launcher->mnCurrent)
	{
		/* For non-empty launcher, same type can be loaded to "top off" launcher.
		** TODO In some cases partial loads should be restricted.
		*/
		if (launcher->GetChildClassName() != item)
		{
            wxString s = wxString::Format("%s (%s) - Cannot load non-empty launcher\n",
                obj->mzUnit.c_str(), obj->mzClass.c_str());
            tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

			return false; // launcher not empty
		}
    }

    float loadTime_s = 0;
    float cycleTime_s = 0;
    unsigned int launcherCapacity = launcher->GetCapacityForItem(item, loadTime_s, cycleTime_s);
    
    if (launcherCapacity == 0)
    {
        wxString s = wxString::Format("%s (%s) - Incompatible item for launcher\n",
            obj->mzUnit.c_str(), obj->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

        return false; // item not compatible with launcher  
    }

	int maxLoadQuantity = (int)launcherCapacity - launcher->mnCurrent;
	if (maxLoadQuantity <= 0)
	{
        wxString s = wxString::Format("%s (%s) - Launcher full\n",
            obj->mzUnit.c_str(), obj->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

		return false;
	}

    if (maxLoadQuantity > (int)maxToLoad) maxLoadQuantity = (int)maxToLoad;



    std::vector<StoreItem>::iterator iter;
    bool found = false;
    int nStores = (int)stores.size();
    unsigned long loadQuantity = 0;
    for (int k=nStores-1; (k>=0) && !found; k--)
    {
        if (stores[k].className == item)
        {
            found = true;
            wxASSERT(stores[k].quantity);
            if (stores[k].quantity >= (unsigned)maxLoadQuantity)
            {
                loadQuantity = (unsigned)maxLoadQuantity;
            }
            else
            {
                loadQuantity = stores[k].quantity;
            }
            stores[k].quantity -= loadQuantity;
            if (stores[k].quantity == 0)
            {
                stores.erase(stores.begin()+k);
            }
        }
    }

    if (!found)
    {
        wxString s = wxString::Format("%s (%s) - No %s in %s\n", 
            obj->mzUnit.c_str(), obj->mzClass.c_str(), 
            item.c_str(), storesDBObj->displayName.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

        return false; // stores not available
    }

	float databaseLoadTime_s = (loadTime_s + storesDBObj->moveTime);
	float transferTime_s = (tcOptions::Get()->fastLoad == 0) ? databaseLoadTime_s : std::min(30.0f, databaseLoadTime_s);
	bool result = AddOperation(item, idx, loadQuantity, transferTime_s, StoreOperation::LOAD, obj);


	if (result == true)
	{
        wxString s = wxString::Format("%s (%s) - Loading %s in %s\n", 
            obj->mzUnit.c_str(), obj->mzClass.c_str(), 
            item.c_str(), storesDBObj->displayName.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

		// SetChildClass empties launcher, so save current quantity, call SetChildClass,
		// then call SetChildQuantity to restore
		int currentLauncherQuantity = launcher->mnCurrent;
		launcher->SetChildClass(item);
		launcher->SetChildQuantity(currentLauncherQuantity); // note this calls SetLoadState(false)

		launcher->SetLoadState(true);
	}

    return result;
}

/**
* @return quantity to move
* Used to transfer items from one stores to another
*/
unsigned int tcStores::MoveStores(const std::string& item, unsigned int quantity, tcPlatformObject* destination, unsigned int storesIdx)
{
    bool moveAllowed = StoresOperationAllowed(destination);
    
    if (!moveAllowed)
	{
        wxString s = wxString::Format("%s (%s) - Cannot transfer item, no access to destination stores\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());
		return 0;
	}

    wxASSERT(destination != 0); // checked by StoresOperationsAllowed
    tcStores* destStores = destination->GetMagazine(storesIdx);
    if (destStores == 0)
    {
        wxASSERT(false);
        wxString s = wxString::Format("%s (%s) - Cannot transfer item, invalid stores idx\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());
		return 0;
    }

    if (destStores->IsCompatible(item))
    {
        tcDatabaseObject* itemData = tcDatabase::Get()->GetObject(item);

        if (itemData == 0)
        {
            fprintf(stderr, "tcStores::MoveStores -- item not found in database (%s)\n", item.c_str());
            return 0; // not found in database
        }

        unsigned long freeCapacity = destStores->GetFreeCapacityForItem(itemData->weight_kg, itemData->volume_m3);        
        unsigned int moveQuantity = (unsigned int)std::min((unsigned long)quantity, freeCapacity);

        float transferTime_s = storesDBObj->moveTime + destStores->GetDatabaseObject()->moveTime;
        RemoveItems(item, moveQuantity);

        AddOperation(item, storesIdx, moveQuantity, transferTime_s, StoreOperation::MOVE, destination);

        return moveQuantity;
    }
    else
    {
        wxString s = wxString::Format("%s (%s) - Cannot transfer item, not compatible with destination stores\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());
        return 0;
    }


}


/**
* Used to load a non-launcher item (e.g. fuel) from stores to platform
*/
bool tcStores::LoadOther(const std::string& item, unsigned long quantity, tcGameObject* child)
{
    long maxWeightFuel_kg = 9999999;
    if (tcAirObject* air = dynamic_cast<tcAirObject*>(child))
    {
        if (air->MaintenanceHold()) return false;
        maxWeightFuel_kg = long(air->mpDBObject->maxTakeoffWeight_kg - air->GetTotalWeight());
    }

    tcGameObject* obj = GetChildOrParent(child);
    
    if (obj == 0)
	{
        wxString s = wxString::Format("%s (%s) - Cannot load item, no access to stores\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());

		return false;
	}
	
	tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj);
	if (platform == 0)
	{
        wxString s = wxString::Format("%s (%s) - Cannot load item, not platform object\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

		return false;
	}

	// only support refueling right now
	if (item != "Fuel")
	{
		wxASSERT(false);
		return false;
	}

	long fuelNeeded_kg = long(ceilf((platform->GetFuelCapacity() - platform->fuel_kg)));
    fuelNeeded_kg = std::min(fuelNeeded_kg, maxWeightFuel_kg);

    if (fuelNeeded_kg <= 0)
    {
        wxString s;
        if (fuelNeeded_kg != maxWeightFuel_kg)
        {
            s = wxString::Format("%s (%s) - platform already refueled\n",
                obj->mzUnit.c_str(), obj->mzClass.c_str());
        }
        else
        {
            s = wxString::Format("%s (%s) - additional fuel would exceed max takeoff weight\n",
                obj->mzUnit.c_str(), obj->mzClass.c_str());
        }
        
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

        return false; // item not compatible with launcher  
    }

	fuelNeeded_kg = std::min((unsigned long)fuelNeeded_kg, quantity);

    std::vector<StoreItem>::iterator iter;
    bool found = false;
    int nStores = (int)stores.size();
    unsigned long loadQuantity = 0;
    for (int k=nStores-1; (k>=0) && !found; k--)
    {
        if (stores[k].className == item)
        {
            found = true;
            wxASSERT(stores[k].quantity);
            if (stores[k].quantity >= (unsigned long)fuelNeeded_kg)
            {
                loadQuantity = fuelNeeded_kg;
            }
            else
            {
                loadQuantity = stores[k].quantity;
            }
            stores[k].quantity -= loadQuantity;
            if (stores[k].quantity == 0)
            {
                stores.erase(stores.begin()+k);
            }
        }
    }

    if (!found)
    {
        wxString s = wxString::Format("%s (%s) - No %s in %s\n", 
            obj->mzUnit.c_str(), obj->mzClass.c_str(), 
            item.c_str(), storesDBObj->displayName.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

        return false; // stores not available
    }

    float transferTime_s = loadQuantity * 0.02f; // 50 kg/s refuel rate, hard-coded
	bool result = AddOperation(item, 0, loadQuantity, transferTime_s, StoreOperation::REFUEL, obj);

    if (result == true)
    {
        wxString s = wxString::Format("%s (%s) - Refueling\n", 
            obj->mzUnit.c_str(), obj->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

		platform->SetRefueling(true);
	}

    return result;
}


/**
* Used to unload a non-launcher item (e.g. fuel) from platform to stores
*/
bool tcStores::UnloadOther(const std::string& item, unsigned long quantity, tcGameObject* child)
{
    tcGameObject* obj = GetChildOrParent(child);
    
    if (obj == 0)
	{
        wxString s = wxString::Format("%s (%s) - Cannot unload item, no access to stores\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());
		return false;
	}
	
	tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(obj);
	if (platform == 0)
	{
        wxString s = wxString::Format("%s (%s) - Cannot unload item, not platform object\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());
		return false;
	}

	// only support defueling right now
	if (item != "Fuel")
	{
		wxASSERT(false);
		return false;
	}

    if (!IsCompatible("Fuel")) return false;

    // don't defuel external tanks
    long maxDefuel_kg = long(ceilf(std::min(platform->mpDBObject->GetInternalFuelCapacity(), (float)platform->fuel_kg)));
    long defuel_kg = std::min(maxDefuel_kg, (long)quantity);


    float transferTime_s = float(defuel_kg) * 0.02f; // 50 kg/s refuel rate, hard-coded
	bool result = AddOperation(item, 0, defuel_kg, transferTime_s, StoreOperation::DEFUEL, obj);

    if (result == true)
    {
        wxString s = wxString::Format("%s (%s) - Defueling\n", 
            obj->mzUnit.c_str(), obj->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());
		platform->SetRefueling(true);
	}

    return result;
}



void tcStores::SaveToPython(scriptinterface::tcScenarioLogger& logger)
{
	wxString s;

	for (size_t k=0; k<stores.size(); k++)
	{
		s.Printf("SM.AddToUnitMagazine(\"%s\", '%s', %d)", parent->mzUnit.c_str(),
			stores[k].className.c_str(), stores[k].quantity);
		logger.AddScenarioText(s.ToStdString());
	}
}

/**
*
*/
void tcStores::SetParent(tcPlatformObject* obj)
{
    parent = obj;
}

/**
* Unloads all items from launcher
*/
bool tcStores::UnloadLauncher(unsigned int idx, tcGameObject* child, unsigned long maxToUnload)
{
    tcGameObject* obj = GetChildOrParent(child);
    
    if (obj == 0)
	{
        wxString s = wxString::Format("%s (%s) - Cannot unload launcher, no access to magazine\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());

		return false;
	}

    tcLauncher* launcher = obj->GetLauncher(idx);    
    wxASSERT(launcher);
    if (!launcher) return false;

    if (launcher->mnCurrent == 0)
    {
        wxString s = wxString::Format("%s (%s) - Cannot unload empty launcher\n",
            obj->mzUnit.c_str(), obj->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

        return false; // launcher not empty
    }

    if ((obj->parent == 0) && (!launcher->isReloadable))
    {
        wxString s = wxString::Format("%s (%s) - Launcher doesnt allow underway unload\n",
            obj->mzUnit.c_str(), obj->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

        return false; // launcher not empty
    }

    std::string item = launcher->GetChildClassName();

    if (!IsCompatible(item))
    {
        wxString s = wxString::Format("%s (%s) - No magazine to hold %s from %s\n", 
            obj->mzUnit.c_str(), obj->mzClass.c_str(), 
            item.c_str(), storesDBObj->displayName.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

        return false;
    }


    if (IsFull())
    {
        wxString s = wxString::Format("%s (%s) - Magazine full, cannot unload %s from %s\n", 
            obj->mzUnit.c_str(), obj->mzClass.c_str(), 
            item.c_str(), storesDBObj->displayName.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

        return false;
    }

	float transferTime_s = (tcOptions::Get()->fastLoad == 0) ? storesDBObj->moveTime : std::min(10.0f, storesDBObj->moveTime);
    bool result = AddOperation(item, idx, std::min((unsigned long)launcher->mnCurrent, maxToUnload), transferTime_s, StoreOperation::UNLOAD, obj);

	if (result == true)
	{
		launcher->SetLoadState(true);

        wxString s = wxString::Format("%s (%s) - Unloading %s to %s\n", 
            obj->mzUnit.c_str(), obj->mzClass.c_str(), 
            item.c_str(), storesDBObj->displayName.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), obj->GetAlliance());

	}

    return result;
}

/**
*
*/
void tcStores::Update(double t)
{
    float dt = float(t - lastUpdate);
    if ((dt < 1.0) && (!parent->IsEditMode())) return;
    
	UpdateAutomation();

    lastUpdate = t;

    int nOps = (int)ops.size();
    for (int n=nOps-1; n>=0; n--)
    {
        ops[n].timeToComplete -= dt;
        ops[n].timeElapsed += dt;
        if ((ops[n].timeToComplete <= 0) || (parent->IsEditMode()))
        {
            CompleteOperation(ops[n]);
            ops.erase(ops.begin()+n);
        }
    }

}

void tcStores::UpdateAutomation()
{
    const int finishOp = 86;

    // first verify valid op target, otherwise set stage to finishOp
    for (size_t n=0; n<automationOps.size(); n++)
	{
        AutomationOperation& op = automationOps[n];
        tcGameObject* obj = GetChildOrParent(op.obj);
        if (obj == 0) op.stage = finishOp;
    }

	for (size_t n=0; n<automationOps.size(); n++)
	{
		AutomationOperation& op = automationOps[n];
		if (op.stage == 0)
		{
			// all ops start with completely unloading the platform
			if (UnloadPlatform(op.obj))
			{
				op.stage = 1;	
			}
			else
			{
				op.stage = finishOp;
			}
		}
		else if (op.stage == 1)
		{
			if (AllLaunchersEmpty(op.obj))
			{
				if (op.type == "Empty")
				{
					op.stage = finishOp;
				}
				else
				{
					if (LoadPlatform(op.obj, op.type))
					{
						op.stage = 2;
					}
					else
					{
						op.stage = finishOp;
					}
				}
			}
		}
		else if (op.stage == 2)
		{
			if (AllLaunchersReady(op.obj))
			{
				op.stage = finishOp;
			}
		}
		else
		{
			op.stage = finishOp;
		}
	}

	// remove all automation ops at delete stage (op.stage == finishOp)
	std::vector<AutomationOperation> temp;

	for (size_t n=0; n<automationOps.size(); n++)
    {
		if (automationOps[n].stage != finishOp)
		{
			temp.push_back(automationOps[n]);
		}
		else
		{
            wxString s = wxString::Format("%s (%s) - Completed loadout automation (%s)\n",
                parent->mzUnit.c_str(), parent->mzClass.c_str(), automationOps[n].type.c_str());
            tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());
		}
	}
	automationOps = temp;


}

/**
* Gets best calculated generic loadout based on target type
* @param type "AAW" targetMask = AIR_TARGET; "ASuW" targetMask = SURFACE_TARGET; "ASW" targetMask = SUBSURFACE_TARGET;
*	"Strike" targetMask = LAND_TARGET; "Nuclear"
*/
bool tcStores::GetBestGenericLoadout(tcPlatformObject* obj, const std::string& type, std::vector<WeaponInfo>& bestForLauncher)
{
    wxASSERT(obj != 0);
    if (obj == 0) return false;

    int targetMask = 0;
    bool allowNuclear = false;
	
	if (type == "AAW") targetMask = AIR_TARGET;
	else if (type == "ASuW") targetMask = SURFACE_TARGET;
	else if (type == "ASW") targetMask = SUBSURFACE_TARGET;
	else if (type == "Strike") targetMask = LAND_TARGET;
    else if (type == "Nuclear")
    {
        targetMask = (AIR_TARGET | SURFACE_TARGET | LAND_TARGET);
        allowNuclear = true;
    }

    // to load an assortment of CM
    bool haveFlares = false;
    bool haveChaff = false;

    bestForLauncher.clear();
    size_t nLaunchers = obj->GetLauncherCount();

	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = obj->GetLauncher(n);   
		size_t nTypes = launcher->GetCompatibleCount();
		wxASSERT(nTypes > 0);

        
        WeaponInfo best;
        best.capacity = launcher->GetCompatibleQuantity(0);
        best.quantity = CurrentItemQuantity(launcher->GetCompatibleName(0), best.name);

		GetWeaponInfo(best);

		// cycle through other types and compare
		for (size_t k=1; k<nTypes; k++)
		{
            WeaponInfo candidate;
            candidate.capacity = launcher->GetCompatibleQuantity(k);
            candidate.quantity = CurrentItemQuantity(launcher->GetCompatibleName(k), candidate.name); // quantity in stores
			GetWeaponInfo(candidate);

			bool betterMissionFit = ((best.targetFlags & targetMask) == 0) && 
				((candidate.targetFlags & targetMask) != 0);
			bool worseMissionFit = ((best.targetFlags & targetMask) != 0) &&
				((candidate.targetFlags & targetMask) == 0);
//			bool fitsMission = ((candidate.targetFlags & targetMask) != 0);
			bool betterRange = candidate.range_km > best.range_km;
            bool isAvailable = (candidate.quantity > 0) && (!candidate.isNuclear || allowNuclear);
            
            bool betterNuclear = allowNuclear && (!best.isNuclear && candidate.isNuclear);

			bool better = isAvailable && 
				         (betterMissionFit || (!worseMissionFit && betterRange) || 
                         (!worseMissionFit && betterNuclear));

            // section to load both chaff and flares
            if (candidate.miscType.size() > 0)
            {
                bool isChaff = (candidate.miscType == "Chaff");
                bool isFlares = (candidate.miscType == "Flare");
               
                if (isChaff && (!haveChaff))
                {
                    haveChaff = true;
                    better = true;
                }
                if (isFlares && (!haveFlares))
                {
                    haveFlares = true;
                    better = true;
                }
            }

			if (better)
			{
                best = candidate;
			}
		}

        bestForLauncher.push_back(best);
	}

    if (tcAirObject* air = dynamic_cast<tcAirObject*>(obj))
    {
        // check if overweight for takeoff (assuming fully fueled)
        float maxLoadWeight_kg = air->mpDBObject->maxTakeoffWeight_kg - air->mpDBObject->weight_kg -
            air->mpDBObject->mfFuelCapacity_kg;

        // if overweight, iterate through, removing one of biggest capacity item until weight is okay
        bool iteratingForWeight = true;
        unsigned int nIterations = 0;
        const unsigned int maxIterations = 32;

        while (iteratingForWeight && (nIterations++ < maxIterations))
        {
            float loadWeight_kg = 0;
            size_t bestIdx = 0;
            size_t bestCapacity = 0;
            float bestWeight = 99999.9f;

            for (size_t n=0; n<nLaunchers; n++)
            {
//                tcLauncher* launcher = obj->GetLauncher(n);   

                size_t capacity = bestForLauncher[n].capacity;
                float weight_kg = bestForLauncher[n].weight_kg;
                loadWeight_kg += weight_kg * float(capacity);
                
                if ((capacity > bestCapacity) || ((capacity == bestCapacity) && (weight_kg < bestWeight)))
                {
                    bestIdx = n;
                    bestCapacity = capacity;
                    bestWeight = weight_kg;
                }

            }
            
            if (loadWeight_kg <= maxLoadWeight_kg)
            {
                iteratingForWeight = false;
            }
            else
            {
                if (bestForLauncher[bestIdx].capacity > 0) bestForLauncher[bestIdx].capacity--;
            }

        }

        if (nIterations >= maxIterations)
        {
            fprintf(stderr, "(%s: %s) Failed to find loadout satisfying takeoff weight restriction."
                " Could be caused by database error\n", 
                air->mzClass.c_str(), air->mzUnit.c_str());
            return false;
        }   
    }

    return true;
}


/**
* @param type is either an auto-setup name like Empty, AAW, etc.; or a reference to
* a SetupName in the platform_setup table
*/
bool tcStores::LoadPlatform(tcGameObject* child, const std::string& type)
{
    tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(GetChildOrParent(child));

    // check that magazine is accessible (child hasn't taken off yet)
    if (obj == 0)
    {
        wxString s = wxString::Format("%s (%s) - Automation failed: Cannot load platform, no access to magazine\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());
        return false;
    }

    // verify all launchers are empty
    if (!AllLaunchersEmpty(child))
    {
        wxString s = wxString::Format("%s (%s) - Automation failed: Cannot load platform, launchers not empty\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());
        return false;
    }

    // verify launchers are all valid
    size_t nLaunchers = obj->GetLauncherCount();
    for (size_t n=0; n<nLaunchers; n++)
    {
        tcLauncher* launcher = obj->GetLauncher(n);    
        wxASSERT(launcher);

        if (launcher == 0)
        {
            wxString s = wxString::Format("%s (%s) - Automation failed: Cannot load platform, corrupt launcher\n",
                parent->mzUnit.c_str(), parent->mzClass.c_str());
            tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());
            return false;
        }
    }


    bool genericLoadout = 
        (type == "AAW") || 
        (type == "ASuW") ||
        (type == "ASW") ||
        (type == "Strike") ||
        (type == "Nuclear");

    if (!genericLoadout)
    {   // assume DB platform_setup loadout
        return LoadAirLoadout(child, type);
    }

    std::vector<WeaponInfo> bestForLauncher;
    bool success = GetBestGenericLoadout(obj, type, bestForLauncher);
    if (success)
    {
        // load launcher with best results
        for (size_t n=0; n<nLaunchers; n++)
        {
            // load launcher with best results
            LoadLauncher(n, bestForLauncher[n].name, child, bestForLauncher[n].capacity);
        }


        obj->SetLoadoutTag(type);
        return true;
    }
    else
    {
        return false;
    }
}


/**
* Intended to be called in edit mode, mirroring behavior of LoadPlatform, except with no
* limits on "stores" quantity of items available
*/
bool tcStores::LoadPlatformEditMode(tcGameObject* child, const std::string& type)
{
	tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(child);
	
    if (!tcGameObject::IsEditMode()) return false;

	// verify launchers are all valid
	size_t nLaunchers = obj->GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = obj->GetLauncher(n);    
		wxASSERT(launcher);
		if (launcher == 0) return false;
	}


	// for each launcher find the best loadout based on mission type, weapon range, weapon availability
	int targetMask = 0;
    bool allowNuclear = false;
	
	if (type == "AAW") targetMask = AIR_TARGET;
	else if (type == "ASuW") targetMask = SURFACE_TARGET;
	else if (type == "ASW") targetMask = SUBSURFACE_TARGET;
	else if (type == "Strike") targetMask = LAND_TARGET;
    else if (type == "Nuclear")
    {
        targetMask = (AIR_TARGET | SURFACE_TARGET | LAND_TARGET);
        allowNuclear = true;
    }
	else 
    {   // assume DB air loadout
        return LoadAirLoadoutEditMode(child, type);
    }

    // to load an assortment of CM
    bool haveFlares = false;
    bool haveChaff = false;

    const size_t nLots = 9999;

    std::vector<WeaponInfo> bestForLauncher;

	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = obj->GetLauncher(n);   
		size_t nTypes = launcher->GetCompatibleCount();
		wxASSERT(nTypes > 0);

        WeaponInfo best;
        best.name = launcher->GetCompatibleName(0);
        best.capacity = launcher->GetCompatibleQuantity(0);
        best.quantity = nLots;

		GetWeaponInfo(best);

		// cycle through other types and compare
		for (size_t k=1; k<nTypes; k++)
		{
            WeaponInfo candidate;
            candidate.name = launcher->GetCompatibleName(k);
            candidate.capacity = launcher->GetCompatibleQuantity(k);
            candidate.quantity = nLots;
			GetWeaponInfo(candidate);

			bool betterMissionFit = ((best.targetFlags & targetMask) == 0) && 
				((candidate.targetFlags & targetMask) != 0);
			bool worseMissionFit = ((best.targetFlags & targetMask) != 0) &&
				((candidate.targetFlags & targetMask) == 0);
//			bool fitsMission = ((candidate.targetFlags & targetMask) != 0);
			bool betterRange = candidate.range_km > best.range_km;
            bool isAvailable = (candidate.quantity > 0) && (!candidate.isNuclear || allowNuclear);
            
            bool betterNuclear = allowNuclear && (!best.isNuclear && candidate.isNuclear);

			bool better = isAvailable && 
				         (betterMissionFit || (!worseMissionFit && betterRange) || 
                         (!worseMissionFit && betterNuclear));

            // section to load both chaff and flares
            if (candidate.miscType.size() > 0)
            {
                bool isChaff = (candidate.miscType == "Chaff");
                bool isFlares = (candidate.miscType == "Flare");
               
                if (isChaff && (!haveChaff))
                {
                    haveChaff = true;
                    better = true;
                }
                if (isFlares && (!haveFlares))
                {
                    haveFlares = true;
                    better = true;
                }
            }

			if (better)
			{
                best = candidate;
			}
		}

        bestForLauncher.push_back(best);
	}

    if (tcAirObject* air = dynamic_cast<tcAirObject*>(obj))
    {
        // check if overweight for takeoff (assuming fully fueled)
        float maxLoadWeight_kg = air->mpDBObject->maxTakeoffWeight_kg - air->mpDBObject->weight_kg -
            air->mpDBObject->mfFuelCapacity_kg;

        // if overweight, iterate through, removing one of biggest capacity item until weight is okay
        bool iteratingForWeight = true;
        unsigned int nIterations = 0;
        const unsigned int maxIterations = 32;

        while (iteratingForWeight && (nIterations++ < maxIterations))
        {
            float loadWeight_kg = 0;
            size_t bestIdx = 0;
            size_t bestCapacity = 0;
            float bestWeight = 99999.9f;

            for (size_t n=0; n<nLaunchers; n++)
            {
//                tcLauncher* launcher = obj->GetLauncher(n);   

                size_t capacity = bestForLauncher[n].capacity;
                float weight_kg = bestForLauncher[n].weight_kg;
                loadWeight_kg += weight_kg * float(capacity);
                
                if ((capacity > bestCapacity) || ((capacity == bestCapacity) && (weight_kg < bestWeight)))
                {
                    bestIdx = n;
                    bestCapacity = capacity;
                    bestWeight = weight_kg;
                }

            }
            
            if (loadWeight_kg <= maxLoadWeight_kg)
            {
                iteratingForWeight = false;
            }
            else
            {
                if (bestForLauncher[bestIdx].capacity > 0) bestForLauncher[bestIdx].capacity--;
            }

        }

        if (nIterations >= maxIterations)
        {
            fprintf(stderr, "LoadPlatformEditMode: (%s: %s) Failed to find loadout satisfying takeoff weight restriction."
                " Could be caused by database error\n", 
                air->mzClass.c_str(), air->mzUnit.c_str());
            return false;
        }
        
    }

    // load launcher with best results
    for (size_t n=0; n<nLaunchers; n++)
	{
        tcLauncher* launcher = obj->GetLauncher(n);
        wxASSERT(launcher != 0);

		// load launcher with best results
        std::string item = bestForLauncher[n].name;
        unsigned int launcherCapacity = launcher->GetCapacityForItem(item);

        launcher->SetChildClass(item);
		launcher->SetChildQuantity(launcherCapacity); // note this calls SetLoadState(false)
	}

	return true;
}

/**
* @param groupSize multiplier to ensure that quantity is available for all platforms in group
* @return true if loadout found, false if no loadout satisfying weight restriction
*/
bool tcStores::GetBestLoadout(tcAirObject* obj, const std::vector<LauncherLoadout>& launcherLoadout,
                              std::vector<WeaponInfo>& bestForLauncher, unsigned int groupSize)
{
    bestForLauncher.clear();
    wxASSERT(obj != 0);
    if (obj == 0) return false;



    size_t nLaunchers = (size_t)obj->GetLauncherCount();
        
    for (size_t n=0; n<nLaunchers; n++)
	{
        unsigned int launcherId = obj->mpDBObject->launcherId[n]; // launcher id for this launcher
        WeaponInfo weaponInfo;
//		tcLauncher* launcher = obj->GetLauncher(n);   
		
        // search through each entry in the launcherLoadout list, checking for multiple entries for alternate loads
        bool searching = true;
        for (size_t opt=0; (opt<launcherLoadout.size()) && searching; opt++)
        {
            if (launcherLoadout[opt].launcherId == launcherId)
            {
                std::string itemName = launcherLoadout[opt].item;
                if ((itemName != "Empty") && (itemName.size() > 0))
                {
                    weaponInfo.capacity = launcherLoadout[opt].quantity;
                    weaponInfo.quantity = CurrentItemQuantity(launcherLoadout[opt].item, weaponInfo.name);
                    if (weaponInfo.quantity >= groupSize*weaponInfo.capacity)
                    {
                        searching = false;
                        GetWeaponInfo(weaponInfo);
                    }
                }
                else
                {
                    weaponInfo.name = "Empty";
                    weaponInfo.capacity = 0;
                    weaponInfo.weight_kg = 0;
                    searching = false;
                }
            }
        }

        bestForLauncher.push_back(weaponInfo);
    }

    // check if overweight for takeoff (assuming fully fueled)
    float maxLoadWeight_kg = obj->mpDBObject->maxTakeoffWeight_kg - obj->mpDBObject->weight_kg -
        obj->mpDBObject->mfFuelCapacity_kg;

    float loadWeight_kg = 0;

    for (size_t n=0; n<nLaunchers; n++)
    {
//        tcLauncher* launcher = obj->GetLauncher(n);   

        size_t capacity = bestForLauncher[n].capacity;
        float weight_kg = bestForLauncher[n].weight_kg;
        loadWeight_kg += weight_kg * float(capacity);
    }

    if (loadWeight_kg > maxLoadWeight_kg)
    {
        fprintf(stderr, "(%s: %s) Failed to find loadout satisfying takeoff weight restriction."
            " Could be caused by database error (loadout name: %s)\n", 
            obj->mzClass.c_str(), obj->mzUnit.c_str(), "unavailable");
        return false;
    }
    else
    {
        return true;
    }

}

/**
* Loads an air loadout according to database data
* Only applies to air platforms
*/
bool tcStores::LoadAirLoadout(tcGameObject* child, const std::string& type)
{
	tcAirObject* obj = dynamic_cast<tcAirObject*>(GetChildOrParent(child));
    if (obj == 0) return false;

    // assume that we've already done checks for magazine accessible, launcher empty, launchers valid
	// assume that we've checked for auto-loadout type

    const tcLoadoutData* loadoutInfo = obj->mpDBObject->GetLoadout(type);
    if (loadoutInfo == 0)
    {
        fprintf(stderr, "tcStores::LoadAirLoadout - Loadout not found, air unit: %s, loadout: %s\n",
            obj->mzUnit.c_str(), type.c_str());
        wxASSERT(false);
        return false;
    }

	// for each launcher find the first available option
    std::vector<WeaponInfo> bestForLauncher;
    bool success = GetBestLoadout(obj, loadoutInfo->launcherLoadout, bestForLauncher);
    if (!success)
    {
        return false;
    }

    size_t nLaunchers = (size_t)obj->GetLauncherCount();
    wxASSERT(bestForLauncher.size() == nLaunchers);

    // load launcher with best results
    for (size_t n=0; n<nLaunchers; n++)
	{
//		tcLauncher* launcher = obj->GetLauncher(n);   

		// load launcher with best results
        LoadLauncher(n, bestForLauncher[n].name, child, bestForLauncher[n].capacity);
	}

    obj->SetLoadoutTag(type);

	return true;
}

/**
* Loads an air loadout according to database data
* Only applies to air platforms
* Edit mode version that doesn't check stores availability
*/
bool tcStores::LoadAirLoadoutEditMode(tcGameObject* child, const std::string& type)
{
    tcAirObject* obj = dynamic_cast<tcAirObject*>(child);
    if (obj == 0) return false;

    if (!tcGameObject::IsEditMode()) return false;

    // assume that we've already done checks for magazine accessible, launcher empty, launchers valid
	// assume that we've checked for auto-loadout type

    const tcLoadoutData* loadoutInfo = obj->mpDBObject->GetLoadout(type);
    if (loadoutInfo == 0)
    {
        fprintf(stderr, "tcStores::LoadAirLoadout - Loadout not found, air unit: %s, loadout: %s\n",
            obj->mzUnit.c_str(), type.c_str());
        wxASSERT(false);
        return false;
    }

	// for each launcher find the first available option
    std::vector<WeaponInfo> bestForLauncher;
    
    size_t nLaunchers = (size_t)obj->GetLauncherCount();
        
    for (size_t n=0; n<nLaunchers; n++)
	{
        unsigned int launcherId = obj->mpDBObject->launcherId[n]; // launcher id for this launcher
        WeaponInfo weaponInfo;
//		tcLauncher* launcher = obj->GetLauncher(n);   
		
        // search through each entry in the launcherLoadout list, checking for multiple entries for alternate loads
        bool searching = true;
        for (size_t opt=0; (opt<loadoutInfo->launcherLoadout.size()) && searching; opt++)
        {
            if (loadoutInfo->launcherLoadout[opt].launcherId == launcherId)
            {
                std::string itemName = loadoutInfo->launcherLoadout[opt].item;
                if ((itemName != "Empty") && (itemName.size() > 0))
                {
                    weaponInfo.name = itemName;
                    weaponInfo.capacity = loadoutInfo->launcherLoadout[opt].quantity;
                    weaponInfo.quantity = 99999;
                    if (weaponInfo.quantity >= weaponInfo.capacity)
                    {
                        searching = false;
                        GetWeaponInfo(weaponInfo);
                    }
                }
                else
                {
                    weaponInfo.name = "Empty";
                    weaponInfo.capacity = 0;
                    weaponInfo.weight_kg = 0;
                    searching = false;
                }
            }
        }

        bestForLauncher.push_back(weaponInfo);
    }


    // load launcher with best results
    for (size_t n=0; n<nLaunchers; n++)
	{
        tcLauncher* launcher = obj->GetLauncher(n);
        wxASSERT(launcher != 0);

		// load launcher with best results
        std::string item = bestForLauncher[n].name;
        unsigned int launcherCapacity = launcher->GetCapacityForItem(item);

        launcher->SetChildClass(item);
		launcher->SetChildQuantity(launcherCapacity); // note this calls SetLoadState(false)
	}

	return true;
}


void tcStores::GetWeaponInfo(WeaponInfo& info)
{
	info.range_km = 0;
	info.targetFlags = 0;
    info.miscType.clear();
    info.isNuclear = false;
    info.weight_kg = 0;

    tcDatabase* database = tcDatabase::Get();
	tcDatabaseObject* databaseObj = database->GetObject(info.name);
	if (databaseObj == 0) return;

    info.weight_kg = databaseObj->weight_kg;

	if (tcWeaponDBObject* weaponObj = dynamic_cast<tcWeaponDBObject*>(databaseObj))
	{
		info.targetFlags = weaponObj->targetFlags;
        info.range_km = weaponObj->maxRange_km;

        // check if this is nuclear based on weapon energy
        info.isNuclear = weaponObj->IsNuclear();
	}
    else if (tcFuelTankDBObject* fuelTank = dynamic_cast<tcFuelTankDBObject*>(databaseObj))
    {
        info.weight_kg += fuelTank->fuelCapacity_kg; // assume will be fully fueled
    }
    else if (tcCounterMeasureDBObject* cm = dynamic_cast<tcCounterMeasureDBObject*>(databaseObj))
    {
        info.miscType = cm->subType;
    }


}

float tcStores::GetWeightKg() const
{
	return weight_kg;
}


bool tcStores::UnloadPlatform(tcGameObject* child)
{
	tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(GetChildOrParent(child));
    
    if (obj == 0)
    {
        wxString s = wxString::Format("%s (%s) - Automation failed: Cannot unload platform, no access to magazine\n",
            parent->mzUnit.c_str(), parent->mzClass.c_str());
        tcMessageInterface::Get()->ChannelMessage("Info", s.ToStdString(), parent->GetAlliance());
        return false;
	}
	
	size_t nLaunchers = obj->GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = obj->GetLauncher(n);    
		wxASSERT(launcher);

		if ((launcher != 0) && (launcher->mnCurrent > 0))
		{
			UnloadLauncher(n, child);
		}
	}

	obj->SetLoadoutTag("Empty");

	return true;
}

/**
* @return true if any ops for child are active
*/
bool tcStores::HasActiveOp(tcGameObject* child) const
{
	std::vector<AutomationOperation>::const_iterator opIter;
    for (opIter = automationOps.begin(); opIter != automationOps.end(); ++opIter)
    {
        if (opIter->obj == child)
        {
			return true;
        }
    }

	return false;
}

/**
* @return true if all launchers of child are empty
*/
bool tcStores::AllLaunchersEmpty(tcGameObject* child)
{
	tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(GetChildOrParent(child));
    if (obj == 0)
    {
        return false;
    }

	size_t nLaunchers = obj->GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = obj->GetLauncher(n);    
		wxASSERT(launcher);

		if ((launcher != 0) && (launcher->mnCurrent > 0))
		{
			return false;
		}
	}

	return true;
}

/**
* @return true if all launchers of child are full and ready
*/
bool tcStores::AllLaunchersReady(tcGameObject* child)
{
	tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(GetChildOrParent(child));
    if (obj == 0)
    {
        return false;
    }

	size_t nLaunchers = obj->GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = obj->GetLauncher(n);    
		wxASSERT(launcher);

		if ((launcher != 0) && ((launcher->mnCurrent == 0) || (launcher->IsLoading())))
		{
			return false;
		}
	}

	return true;
}

/**
* @return true if op found
*/
bool tcStores::FindLauncherOp(tcGameObject* obj, unsigned int launcherIdx, unsigned int& opId)
{
    for (size_t n=0; n<ops.size(); n++)
    {
        if ((ops[n].GetObj() == obj) && (ops[n].launcherIdx == launcherIdx))
        {
            opId = ops[n].opId;
            return true;
        }
    }

    opId = 0;
    return false;
}

const tcStores::StoreOperation* tcStores::FindOpById(unsigned int opId) const
{
    for (size_t n=0; n<ops.size(); n++)
    {
        if (ops[n].opId == opId)
        {
            return &ops[n];
        }
    }
    return 0;
}

/**
* @param nuclear true to only look at nuclear weapons
* @return bitwise OR of all target flags from weapons available in stores that
* are compatible with child's launchers
*/
int tcStores::GetAvailableTargetFlags(tcGameObject* child, bool nuclear)
{
	tcPlatformObject* obj = dynamic_cast<tcPlatformObject*>(GetChildOrParent(child));
    
	// check that magazine is accessible (child hasn't taken off yet)
    if (obj == 0) return 0;
	
	size_t nLaunchers = obj->GetLauncherCount();

	int netTargetFlags = 0;

	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = obj->GetLauncher(n);   

		size_t nTypes = launcher->GetCompatibleCount();
		for (size_t k=0; k<nTypes; k++)
		{
            WeaponInfo info;
            info.quantity = CurrentItemQuantity(launcher->GetCompatibleName(k), info.name);
			if (info.quantity > 0)
			{
				GetWeaponInfo(info);

                if (!nuclear)
                {
				    netTargetFlags |= info.targetFlags;
                }
                else if (info.isNuclear)
                {
                    netTargetFlags |= info.targetFlags;
                }
			}
		}
	}

	return netTargetFlags;
}

bool tcStores::HasNuclearWeapons()
{
    for (size_t n=0; n<stores.size(); n++)
    {
        tcDatabaseObject* databaseObj = stores[n].GetOrLoadDatabaseObject();
        
	    if (tcWeaponDBObject* weaponObj = dynamic_cast<tcWeaponDBObject*>(databaseObj))
	    {
            if (weaponObj->IsNuclear()) return true;
        }
    }

    return false;
}


/**
* Used for good guess as to which magazine should manage automation operation
* for obj.
* @return true if stores has any items that are compatible with obj
*/
bool tcStores::HasStoresForThisObject(tcGameObject* obj)
{
	tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(GetChildOrParent(obj));
	if (platform == 0)
	{
		wxASSERT(false);
		return false;
	}

    std::string s;
	size_t nLaunchers = platform->GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = platform->GetLauncher(n);    
		wxASSERT(launcher);
		
		size_t nCompatible = launcher->GetCompatibleCount();
		for (size_t k=0; k<nCompatible; k++)
		{
			if (CurrentItemQuantity(launcher->GetCompatibleName(k), s) > 0)
			{
				return true;
			}
		}
	}

	return false;
}

/**
* @return true if any of obj items are compatible with stores
*/
bool tcStores::CanUnloadThisObject(tcGameObject* obj)
{
	tcPlatformObject* platform = dynamic_cast<tcPlatformObject*>(GetChildOrParent(obj));
	if (platform == 0)
	{
		wxASSERT(false);
		return false;
	}

    std::string s;
	size_t nLaunchers = platform->GetLauncherCount();
	for (size_t n=0; n<nLaunchers; n++)
	{
		tcLauncher* launcher = platform->GetLauncher(n);    
		wxASSERT(launcher);

        if ((launcher->mnCurrent > 0) && IsCompatible(launcher->GetChildClassName()))
        {
            return true;
        }
		
	}

	return false;
}


/**
* @return true if adequate stores present to supply loadout
* Entire quantity (or alternate item quantity) must be available, otherwise returns false
*/
bool tcStores::HasStoresForLoadout(const tcLoadoutData& loadoutData) const
{
    std::map<unsigned int, bool> hasStores;

    for (size_t n=0; n<loadoutData.launcherLoadout.size(); n++)
    {
        hasStores[loadoutData.launcherLoadout[n].launcherId] = false;
    }

    for (size_t n=0; n<loadoutData.launcherLoadout.size(); n++)
    {
        if (!hasStores[loadoutData.launcherLoadout[n].launcherId])
        {
            std::string itemName = loadoutData.launcherLoadout[n].item;
            std::string matchingItem;
            unsigned int nAvailable = CurrentItemQuantity(itemName, matchingItem);
            if (nAvailable >= loadoutData.launcherLoadout[n].quantity)
            {
                hasStores[loadoutData.launcherLoadout[n].launcherId] = true;
            }
        }
    }

    std::map<unsigned int, bool>::iterator iter;
    for (iter = hasStores.begin(); iter != hasStores.end(); ++iter)
    {
        if (iter->second == false)
        {
            return false;
        }
    }

    return true;
}

/**
* Update weight and volume occupied by current stores, should be
* called whenever stores have changed
*/
void tcStores::UpdateWeightAndVolume()
{
    volume_m3 = 0;
    weight_kg = 0;

    for (size_t n=0; n<stores.size(); n++)
    {
        tcDatabaseObject* databaseObj = stores[n].GetOrLoadDatabaseObject();

	    if (databaseObj != 0)
        {
            weight_kg += float(stores[n].quantity) * databaseObj->weight_kg;
            volume_m3 += float(stores[n].quantity) * databaseObj->volume_m3;
        }
    }
}

/**
* For multiplayer, for obj's that are flightport objects, only objects in
* the ALERT15 position are allowed to interact with the stores
* (partially a bandwidth issue vs. realism)
* @returns true if op is allowed
*/
bool tcStores::ValidateOpObject(tcGameObject* obj)
{
	if (obj == 0) return true;

	/* if parent of this stores has a flightport, and obj is a child of parent,
    ** then return true if child is in a ALERT15 position, otherwise return true always
	*/
	tcFlightOpsObject* flightOps = dynamic_cast<tcFlightOpsObject*>(parent);
	if (flightOps == 0) return true;

	tcFlightPort* flightPort = flightOps->GetFlightPort();
	if (flightPort == 0) return true;

	int idx = flightPort->GetAirStateIdx(obj->mnID);
	if (idx < 0) return true;

	if (tcAirState* airState = flightPort->GetAirState(idx))
	{
		return (airState->current_location == ALERT15);
	}
	else
	{
		return true;
	}

}


/**
*
*/
tcStores::tcStores(tcStoresDBObject* dbObj)
: storesDBObj(dbObj), lastUpdate(0), parent(0),
  volume_m3(0), weight_kg(0), nextItemId(1)
{
    wxASSERT(storesDBObj);
}

/**
*
*/
tcStores::~tcStores()
{
}


