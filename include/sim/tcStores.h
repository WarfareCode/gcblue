/**
**  @file tcStores.h
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

#ifndef _TCSTORES_H_
#define _TCSTORES_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <vector>
#include "tcLoadoutData.h" // since can't forward declare member class :(

namespace database
{
    class tcDatabaseObject;
    class tcStoresDBObject;
}
namespace scriptinterface
{
	class tcScenarioLogger;
}

using namespace database;

class tcGameObject;
class tcPlatformObject;
class tcAirObject;

class tcStream;
class tcCommandStream;
class tcCreateStream;
class tcUpdateStream;
class tcGameStream;



/**
* State for stores object, used for weapons magazines for subs
*/
class tcStores
{
public:
    class StoreItem
    {
    public:
        std::string className;
        unsigned long quantity;
        unsigned int itemId;
        
        tcDatabaseObject* GetDatabaseObject() const;
        tcDatabaseObject* GetOrLoadDatabaseObject();
        void SetDatabaseObject(tcDatabaseObject* obj);

        StoreItem();
        StoreItem(const StoreItem& src);
        StoreItem(const std::string& name, unsigned long qty, unsigned int id);
    private:
        tcDatabaseObject* databaseObj;
        
        void LoadDatabaseObject();
    };
    
    class StoreOperation
    {
    public:
        enum {UNLOAD = 0, LOAD = 1, REFUEL = 2, AUTOMATION = 3, MOVE = 4, DEFUEL = 5};
        std::string item; ///< item type to transfer
        unsigned long quantity; ///< quantity of item
        float timeToComplete; ///< time left for op to complete [s]
        float timeElapsed; ///< time since op started (used for reversing operation when canceled)
        unsigned int launcherIdx; ///< launcher idx to transfer to/from (also doubles as magazine index for store-to-store move)
        int transferType; ///< UNLOAD or LOAD

        long platformId; ///< id of obj or host obj in simState
        short int childId; ///< id of child obj, or -1 if not a child

        unsigned int opId; ///< unique id for this operation

        tcGameObject* GetObj();
    };

	struct AutomationOperation
	{
		std::string type; ///< "Empty", "AAW", "ASuW", "ASW", "Strike", or custom DB loadout
		tcGameObject* obj; ///< 0 for local platform, otherwise child obj
		int stage; ///< 0 not started, 1 waiting for unload to finish
	};

    struct StoreItemInfo
    {
        std::string className;
        unsigned long quantity;
        unsigned int id;
    };

    struct WeaponInfo
    {
        std::string name;
        size_t quantity; // quantity avail in stores
        size_t capacity; // capacity of launcher
        float range_km;
        int targetFlags;
        std::string miscType; // for info on non-weapons, "Chaff" "Flare"
        float weight_kg;
        bool isNuclear;
    };

    bool AddItems(const std::string& item, unsigned long quantity);
    bool AddItemsForceId(const std::string& item, unsigned long quantity, unsigned int itemId);
    bool RemoveItems(const std::string& item, unsigned long quantity);
    void RemoveAllItems();

    bool CancelOperation(unsigned char id);

    unsigned long CurrentItemQuantity(const std::string& itemMask, std::string& matchingItem) const;
    unsigned long CurrentQuantity() const;
	unsigned long IncomingQuantity() const;
	tcStoresDBObject* GetDatabaseObject() const;
    tcDatabaseObject* GetDatabaseObjectForItem(const std::string& item) const;
	const std::string& GetDisplayName() const;
	/// name of <idx> type
	const std::string& GetItemName(unsigned int idx) const;
    const wxString& GetFilledStatusString() const;
	
	/// number of different item types in storage
	unsigned int GetNumberItemTypes() const;
    const StoreItemInfo& GetItemInfo(size_t idx) const;

    tcGameObject* GetParent() const;
    bool IsCompatible(const std::string& item) const;
    bool IsFull() const;
    bool LoadLauncher(unsigned int idx, const std::string& item, 
             tcGameObject* child = 0, unsigned int maxToLoad = 12345);
	bool LoadOther(const std::string& item, unsigned long quantity, tcGameObject* child = 0);
    unsigned int MoveStores(const std::string& item, unsigned int quantity, tcPlatformObject* destination, unsigned int storesIdx);
    unsigned long GetFreeCapacityForItem(float itemWeight_kg, float itemVolume_m3) const;
    bool GetBestLoadout(tcAirObject* obj, const std::vector<LauncherLoadout>& launcherLoadout, std::vector<WeaponInfo>& bestForLauncher, unsigned int groupSize=1);
    bool GetBestGenericLoadout(tcPlatformObject* obj, const std::string& type, std::vector<WeaponInfo>& bestForLauncher);
    const std::vector<StoreItemInfo>& GetMoveSummary() const;

    virtual void SaveToPython(scriptinterface::tcScenarioLogger& logger);
    void SetParent(tcPlatformObject* obj);
    bool UnloadLauncher(unsigned int idx, tcGameObject* child = 0, unsigned long maxToUnload = 123456);
    bool UnloadOther(const std::string& item, unsigned long quantity, tcGameObject* child = 0);
    void Update(double t);

	void AddAutomationOp(const std::string& type, tcGameObject* child = 0);
	bool AllLaunchersEmpty(tcGameObject* child);
	bool AllLaunchersReady(tcGameObject* child);
	int GetAvailableTargetFlags(tcGameObject* child, bool nuclear=false);

	bool HasActiveOp(tcGameObject* child) const;
	bool HasStoresForThisObject(tcGameObject* obj);
    bool CanUnloadThisObject(tcGameObject* obj);
    bool FindLauncherOp(tcGameObject* obj, unsigned int launcherIdx, unsigned int& opId);
    const StoreOperation* FindOpById(unsigned int opId) const;

    bool HasStoresForLoadout(const tcLoadoutData& loadoutData) const;
    bool HasNuclearWeapons();

	float GetWeightKg() const;
    
    tcCommandStream& operator<<(tcCommandStream& stream);
    tcCreateStream& operator<<(tcCreateStream& stream);
    tcUpdateStream& operator<<(tcUpdateStream& stream);
    tcGameStream& operator<<(tcGameStream& stream);

    tcCommandStream& operator>>(tcCommandStream& stream);
    tcCreateStream& operator>>(tcCreateStream& stream);
    tcUpdateStream& operator>>(tcUpdateStream& stream);
    tcGameStream& operator>>(tcGameStream& stream);

    void ClearNewCommand();
    bool HasNewCommand() const;
    
    static bool LoadAirLoadoutEditMode(tcGameObject* child, const std::string& type); // edit mode version work-around
    static bool LoadPlatformEditMode(tcGameObject* child, const std::string& type); // edit mode version work-around

    tcStores(tcStoresDBObject* dbObj);
    virtual ~tcStores();

private:

    tcStoresDBObject* storesDBObj;
    tcPlatformObject* parent;
    std::vector<StoreItem> stores;
    std::vector<StoreOperation> ops;
	std::vector<AutomationOperation> automationOps;

    int errorCode; ///< used in multiplayer to pass error code to client
    double lastUpdate;
    float weight_kg; ///< current weight occupied by stores
    float volume_m3; ///< current volume occupied by stores

    unsigned int nextItemId; ///< id of item or move operation

	// data for multiplayer commands
	struct CommandInfo
	{
		short int id; ///< id of unit that command applies to, -1 for local unit
		unsigned char op; ///< UNLOAD = 0, LOAD = 1, REFUEL = 2, AUTOMATION = 3
		long itemId; ///< database id of item (if applicable)
		unsigned long quantity;
		unsigned char launcherIdx;
		std::string type; ///< for automation only
	};
	std::vector<CommandInfo> commandList;


    bool AddOperation(const std::string& itemName, unsigned int launcherIdx, unsigned long quantity, float transferTime_s,
							int opType, tcGameObject* obj);
    void CompleteOperation(StoreOperation& op);
    void CompleteMoveOperation(tcStores::StoreOperation& op, tcGameObject* obj);
    tcGameObject* GetChildOrParent(tcGameObject* child);
	bool ValidateOpObject(tcGameObject* obj);

	void UpdateAutomation();
	bool UnloadPlatform(tcGameObject* child);
	bool LoadPlatform(tcGameObject* child, const std::string& type);
    bool LoadAirLoadout(tcGameObject* child, const std::string& type);

	static void GetWeaponInfo(WeaponInfo& info);
    void UpdateWeightAndVolume(); 
    bool StoresOperationAllowed(tcPlatformObject* destination) const;
    size_t GetMyStoresIndex() const;
};
#endif