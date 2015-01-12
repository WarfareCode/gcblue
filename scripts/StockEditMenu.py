from UnitCommands import *
from GroupCommands import *
from MissionEditCommands import *
from HotKey import *
from Amram_Utilities import *
from service_period import *



# top-level edit menu
def StockBuildEditMenu(UnitMenu, SM):
    UnitMenu.Clear()
    UnitMenu.AddItem('Scenario', '')
    UnitMenu.BeginSubMenu()
    #UnitMenu.AddItem('Save scenario', 'SaveGame')
    UnitMenu.AddItemUI('Edit name', 'SetScenarioName', 'Text Scenario name')
    UnitMenu.AddItemUI('Edit description', 'SetScenarioDescription', 'Paragraph ScenarioDescription')
    UnitMenu.AddItemUI('Set date and time', 'SetDateTimeString', 'Text Enter YYYY/MM/DD HH:MM:SS')
    
    UnitMenu.AddItem('Filter','')
    UnitMenu.BeginSubMenu()
    filterByYearActive = SM.GetFilterByYear()
    if (filterByYearActive):
        UnitMenu.AddItemWithParam('Disable year filtering', 'SetFilterByYear', 0)
    else:
        UnitMenu.AddItemWithParam('Enable year filtering', 'SetFilterByYear', 1)
    filterByCountryActive = SM.GetFilterByCountry()
    if (filterByCountryActive):
        UnitMenu.AddItemWithParam('Disable country filtering', 'SetFilterByCountry', 0)
    else:
        UnitMenu.AddItemWithParam('Enable country filtering', 'SetFilterByCountry', 1)  
    UnitMenu.EndSubMenu()
    
    UnitMenu.EndSubMenu()
	
    current_team = SM.GetUserAlliance()
    UnitMenu.AddItem('Side data (%s)' % SM.GetAllianceCountry(current_team),'')
    UnitMenu.BeginSubMenu()
    UnitMenu.AddItem('Change side','ToggleAlliance')
    UnitMenu.AddItemUI('Set country', 'SetAllianceCountry', 'Text Enter country name')
    UnitMenu.AddItemUI('Edit briefing', 'SetBriefing', 'Paragraph Briefing');
    UnitMenu.AddItemUI('Import briefing', 'ImportBriefing', 'File *.txt');
    if (SM.IsAlliancePlayable(current_team)):
        UnitMenu.AddItemWithParam('Set non-playable', 'SetAlliancePlayable', 0)
    else:
        UnitMenu.AddItemWithParam('Set playable', 'SetAlliancePlayable', 1)
    BuildROEMenu(UnitMenu, SM)
    StartGoalTree(UnitMenu, SM)
    UnitMenu.EndSubMenu()

    Amram_Menu.AmramCreateAllianceUnitMenu(UnitMenu, SM)
    #BuildCreateUnitMenu(UnitMenu, SM)
    UnitMenu.AddItem('Scenario Report',''); UnitMenu.BeginSubMenu(); UnitMenu.SetStayOpen(1)
    UnitMenu.AddItemUI('Generate Scenario Issue Report','GetAllUnits', 'Text Please input the date: YYYY/MM/DD')
    if isfile(reportfile_path):
        mod_date = modification_date(reportfile_path)
        UnitMenu.AddItemWithTextParam('Delete Report: %s' % mod_date,'read_write_scenario_issue_reports', 'Delete')
        UnitMenu.AddItem('Report: %s' % mod_date,''); UnitMenu.BeginSubMenu(); UnitMenu.SetStayOpen(1)
        report = read_write_scenario_issue_reports('', 'GetReport')
        traverse_dict_report(UnitMenu, SM, report)
        UnitMenu.EndSubMenu()
    UnitMenu.EndSubMenu()
    UnitMenu.AddItem('Add graphic','')
    UnitMenu.BeginSubMenu()
    UnitMenu.AddItemUI('Dot', 'AddMapText', 'Datum');
    UnitMenu.EndSubMenu()
    
    sea_state = SM.GetSeaState()
    UnitMenu.AddItem('Weather','')
    UnitMenu.BeginSubMenu()
    UnitMenu.AddItem('Sea State','')
    UnitMenu.BeginSubMenu()
    for n in range(0, 8):
        if (n != sea_state):
            UnitMenu.AddItemWithParam('%d' % n, 'SetSeaState', n)
        else:
            UnitMenu.AddItem('%d [x]' % n, '')
    UnitMenu.EndSubMenu()
    
    UnitMenu.AddItem('Sonar SVP','')
    UnitMenu.BeginSubMenu()
    nTemplates = SM.GetNumberSonarTemplates()
    currentTemplate = SM.GetSonarTemplate()
    for n in range(0, nTemplates):
        if (n == currentTemplate):
            UnitMenu.AddItemWithParam('%s [x]' % SM.GetTemplateName(n), 'SetSonarTemplate', n)
        else:
            UnitMenu.AddItemWithParam(SM.GetTemplateName(n), 'SetSonarTemplate', n)
    UnitMenu.AddItem('Edit SVP', '*ShowSonarPanel')
    UnitMenu.EndSubMenu()
    
    UnitMenu.EndSubMenu()
    
def HookUnitFromMenu(SM, className):
    id = SM.GetUnitIdByName(className)
    UI = SM.GetUnitInterface(className)
    alliance = UI.GetUnitAlliance()
    SM.SetAlliance(alliance)
    SM.HookUnit(id)
    
def BuildCreateUnitMenu(UnitMenu, SM):
    page_count = 25
    
    # Create surface ship submenu ###
    UnitMenu.AddItem('Surface','')
    BuildPagedCreateMenu(SM, UnitMenu, 'Surface', page_count)
    
    # Create submarine submenu ###
    UnitMenu.AddItem('Submarine','')
    BuildPagedCreateMenu(SM, UnitMenu, 'Sub', page_count)
    

    # Create fixed wing air submenu ###
    UnitMenu.AddItem('Air fixed wing','')
    BuildPagedCreateMenu(SM, UnitMenu, 'AirFW', page_count)
    

    # Create helo submenu ###
    UnitMenu.AddItem('Helo','')
    BuildPagedCreateMenu(SM, UnitMenu, 'Helo', page_count)
    

    # Create land submenu ###
    UnitMenu.AddItem('Land','')
    BuildPagedCreateMenu(SM, UnitMenu, 'Land', page_count)
    
    # Create underwater mines (subset of torpedo database class)
    UnitMenu.AddItem('Mine','')
    BuildPagedCreateMenu(SM, UnitMenu, 'Mine', page_count)
    
    UnitMenu.EndSubMenu()
 
  
# Version for edit mode
def BuildUnitEditMenu(UnitMenu, UnitInfo):
    UnitMenu.Clear()
    page_count = 25
    
    if (not UnitInfo.IsValid()):
        return
    Amram_Menu.BuildAmramMenu(UnitMenu, UnitInfo, EditMode = True)
    return
    UnitMenu.AddItem('Stock Menu','');UnitMenu.BeginSubMenu();UnitMenu.SetStayOpen(0)    


    # Multiplayer options
    if (UnitInfo.IsMultiplayerActive()):
        return   # no editing in MP mode
        
    UnitMenu.AddItemUI('Duplicate', 'CopyPlatform', 'Datum')
    UnitMenu.SetStayOpen(0)
    UnitMenu.AddItem('Navigate', '')
    UnitMenu.BeginSubMenu()
    
    if (UnitInfo.IsInFormation() and ~UnitInfo.IsFormationLeader()):
        UnitMenu.AddItem('Break formation','BreakAirFormation')
    
    UnitMenu.AddItemUI('Move unit', 'MovePlatform', 'Datum')
    UnitMenu.AddItemUI('Move unit to coordinate', 'MovePlatformString', 'Text Enter Latitude Longitude')
    UnitMenu.AddItemUI('Set heading [h]','SetHeading','Heading')
    # Speed submenu
    UnitMenu.SetStayOpen(1)
    UnitMenu.AddItem('Set speed','')
    UnitMenu.BeginSubMenu()
    UnitMenu.AddItem('30% [1]','Speed30')
    UnitMenu.AddItem('50% [2]','Speed50')
    UnitMenu.AddItem('80% [3]','Speed80')
    UnitMenu.AddItem('100% [4]','Speed100')
    UnitMenu.AddItem('Max [5]','SpeedAB')
    UnitMenu.EndSubMenu()
    UnitMenu.SetStayOpen(0)
    
    if (UnitInfo.IsAir()):
        # Altitude submenu
        UnitMenu.AddItem('Set altitude','')
        UnitMenu.BeginSubMenu()
        UnitMenu.AddItem('High [H]','AltitudeHigh')
        UnitMenu.AddItem('Medium [M]','AltitudeMedium')
        UnitMenu.AddItem('Low [L]','AltitudeLow')
        UnitMenu.AddItem('Very low','AltitudeVeryLow') 
        UnitMenu.EndSubMenu()
        
    UnitMenu.AddItem('Waypoints','')
    UnitMenu.BeginSubMenu()
    UnitMenu.SetStayOpen(1)
    UnitMenu.AddItemUI('Add [w]', 'AddWaypointOrder', 'Datum')
    UnitMenu.AddItem('Clear all', 'ClearWaypoints')
    if (UnitInfo.GetNavLoopState()):
        UnitMenu.AddItemWithParam('Set loop off', 'SetNavLoopState', 0)
    else:
        UnitMenu.AddItemWithParam('Set loop on', 'SetNavLoopState', 1)
    UnitMenu.SetStayOpen(0)
    UnitMenu.EndSubMenu()

    UnitMenu.EndSubMenu()

    BuildFormationMenu(UnitMenu, UnitInfo)

    BuildLoadoutMenu(UnitMenu, UnitInfo)
    
    UnitMenu.AddItem('Delete unit', 'DeletePlatform')
    #UnitMenu.AddItemUI('Rename unit', 'RenamePlatform', 'Text Enter unit name')
    BuildRenameMenu(UnitMenu, UnitInfo)
    BuildRandomizeEditMenu(UnitMenu, UnitInfo)
    
    UnitMenu.AddItem('Special', '')
    UnitMenu.BeginSubMenu()
    if (UnitInfo.IsFixed() or UnitInfo.IsGroundVehicle()):
        if (UnitInfo.GetAlwaysVisible()):
            UnitMenu.AddItemWithParam('Clear always visible', 'SetAlwaysVisible', 0)
        else:
            UnitMenu.AddItemWithParam('Set always visible', 'SetAlwaysVisible', 1)
    cost_millions = 1e-6 * UnitInfo.GetCost()
    UnitMenu.AddItemUI('Set Custom Cost (%.1f)' % cost_millions, 'SetCustomCost', 'Text Enter Custom Cost in Millions')
    UnitMenu.EndSubMenu()
    
    if (UnitInfo.HasFlightPort()):
        UnitMenu.AddItem('Add mission', '')
        UnitMenu.BeginSubMenu()
        UnitMenu.AddItemUI('CAP', 'AddCAPMission', 'Datum')      
        UnitMenu.EndSubMenu()
        
        group_name = UnitInfo.GetAirGroupName()
        group_count = UnitInfo.GetAirGroupCount()
        start_id = UnitInfo.GetAirUnitId()
        UnitMenu.AddItem('Add to flight deck','')
        UnitMenu.BeginSubMenu()
        
        
        UnitMenu.AddItem('Set group (%s-%d x%d)' % (group_name, start_id, group_count), '')
        UnitMenu.BeginSubMenu()
        UnitMenu.AddItemUI('Name', 'SetAirGroupNameUnit', 'Text')
        
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItem('Size','')
        UnitMenu.BeginSubMenu()
        sizes = [1, 2, 3, 4, 6, 8, 10, 12, 14, 16, 18, 24]
        for size in sizes:
            UnitMenu.AddItemWithParam('%s' % size, 'SetAirGroupSizeUnit', size)
        UnitMenu.SetStayOpen(0)
        UnitMenu.AddItemUI('Enter value', 'SetAirGroupSizeUnit', 'Text')
        UnitMenu.EndSubMenu()
        UnitMenu.EndSubMenu()
    
        # Create fixed wing air on carrier or airstrip ###
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItem('Air fixed wing','')
        BuildPagedCreateChildMenuUnit(UnitInfo, UnitMenu, 'AirFW', page_count)
        # Create helo on carrier or airstrip ###
        UnitMenu.AddItem('Helo','')
        BuildPagedCreateChildMenuUnit(UnitInfo, UnitMenu, 'Helo', page_count)
        UnitMenu.EndSubMenu()
        UnitMenu.SetStayOpen(0)

    if (UnitInfo.HasMagazine()):
        magazineAddCount = UnitInfo.GetMagazineAddCount()
        UnitMenu.AddItem('Add stores','')
        UnitMenu.BeginSubMenu()
        UnitMenu.AddItem('Edit quantity (x%d)' % magazineAddCount, '')
        UnitMenu.BeginSubMenu()
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItemWithParam('1', 'SetMagazineAddCount', 1)
        UnitMenu.AddItemWithParam('10', 'SetMagazineAddCount', 10)
        UnitMenu.AddItemWithParam('50', 'SetMagazineAddCount', 50)
        UnitMenu.AddItemWithParam('100', 'SetMagazineAddCount', 100)
        UnitMenu.SetStayOpen(0)
        UnitMenu.AddItemUI('Enter value', 'SetMagazineAddCount', 'Text')
        UnitMenu.EndSubMenu()
        BuildAddStoresMenu(UnitMenu, UnitInfo)
        UnitMenu.EndSubMenu()
        
    # add auto-configure menu if applicable
    BuildAutoConfigMenu(UnitMenu, UnitInfo)
    
    
    # Orders test
    UnitMenu.AddItem('Tasks','')
    UnitMenu.BeginSubMenu() 
    UnitMenu.AddItemUI('Patrol station','AddPatrolStation', 'Datum')
    UnitMenu.SetStayOpen(1)
    UnitMenu.AddItemUI('EngageAll [e]', 'AddEngageAllOrder','Null')
    if (HasGravityBombs(UnitInfo)):
        UnitMenu.SetStayOpen(0)
        UnitMenu.AddItem('Bomb', '')
        UnitMenu.BeginSubMenu()
        UnitMenu.AddItemUI('Set coordinates', 'AddBombDatumTask', 'Datum')
        UnitMenu.AddItemUI('Set target', 'AddBombDatumTaskTargetID', 'Target')
        UnitMenu.EndSubMenu()
        UnitMenu.SetStayOpen(1)
    UnitMenu.AddItemUI('Clear all tasks','ClearTasks','Null')
    UnitMenu.SetStayOpen(0)
    UnitMenu.AddItemUI('Add by name', 'AddTaskByName','Text Enter new task name')
    UnitMenu.EndSubMenu() 
    
    if (UnitInfo.IsAir()):
        UnitMenu.AddItemUI('Land at','AddLandingOrder', 'Target')

        
    # Submarine menu
    if (UnitInfo.IsSub()):
        BuildSubmarineEditMenu(UnitMenu, UnitInfo)

    UnitMenu.AddItem('Platform panel [s]', 'ShowPlatformPanel')

    # Flight port panel if available
    if (UnitInfo.HasFlightPort()):
        UnitMenu.AddItem('Flight deck [f]', 'ShowFlightPanel')

def BuildAddStoresMenu(UnitMenu, UnitInfo):
    page_count = 20
    
    UnitMenu.AddItemUI('Add by name', 'AddItemToMagazine', 'Text')
    UnitMenu.SetStayOpen(1)
    UnitMenu.AddItem('Add suggested', '')
    UnitMenu.BeginSubMenu()
    childStores = GetChildStores(UnitInfo)
    nStores = len(childStores)
    if (nStores > page_count):
        nSubmenus = nStores/page_count + 1
        for sm in range(0, nSubmenus):
            UnitMenu.AddItem('Page %d' % (sm+1),'')
            UnitMenu.BeginSubMenu()
            nPage = min(page_count, nStores - sm*page_count)
            for n in range(0, nPage):
                item_n = childStores[n+sm*page_count]
                UnitMenu.AddItemWithTextParam('%s' % item_n, 'AddItemToMagazine', item_n)
            UnitMenu.EndSubMenu()
    else:
        for n in range(0, nStores):
            UnitMenu.AddItemWithTextParam('%s' % childStores[n], 'AddItemToMagazine', childStores[n])
    UnitMenu.EndSubMenu()
    UnitMenu.AddItem('Missile','')
    BuildPagedAddStores(UnitInfo, UnitMenu, 'Missile', page_count)
    UnitMenu.AddItem('Torpedo','')
    BuildPagedAddStores(UnitInfo, UnitMenu, 'Torpedo', page_count)
    UnitMenu.AddItem('Ballistic','')
    BuildPagedAddStores(UnitInfo, UnitMenu, 'Ballistic', page_count)
    UnitMenu.AddItem('CM','')
    BuildPagedAddStores(UnitInfo, UnitMenu, 'CM', page_count)      
    UnitMenu.SetStayOpen(0)

def BuildAutoConfigMenu(UnitMenu, UnitInfo):
    if ((not UnitInfo.HasMagazine()) and (not UnitInfo.HasFlightPort())):
        return
    setupList = UnitInfo.GetPlatformSetups()
    if (setupList.Size() == 0):
        return
    UnitMenu.AddItem('Auto setup', '')
    UnitMenu.BeginSubMenu()
    for n in range(0, setupList.Size()):
        setup_n = setupList.GetString(n)
        UnitMenu.AddItemWithTextParam('%s' % setup_n, 'AutoConfigurePlatform', setup_n)
    UnitMenu.EndSubMenu()
    
# Gets list of strings of all possible equipment for child platforms
# Will not return strings with ? or * wild cards so some equip will be
# missing for now
def GetChildStores(UI):
    result = [];
    FP = UI.GetFlightPortInfo()
    if (not FP.IsValid()): # just return items compatible with this unit's launchers
        stores = UI.GetCompatibleItemList(-1)
        for k in range(0, stores.Size()):
            result.append(stores.GetString(k))
    else: # return items compatible with child aircraft
        nCount = FP.GetUnitCount()
        for n in range(0, nCount):
            UIn = FP.GetUnitPlatformInterface(n)
            stores_n = UIn.GetCompatibleItemList(-1)
            for k in range(0, stores_n.Size()):
                result.append(stores_n.GetString(k))

    result.sort()
    filtered_result = [] # version with no duplicates
    for n in range(0, len(result)):
        if ((n == 0) or (result[n] != result[n-1])):
            filtered_result.append(result[n])

    return filtered_result
    
# menu to change loadout of unit
def BuildLoadoutMenu(UnitMenu, UnitInfo):
    nLaunchers = UnitInfo.GetLauncherCount()
    if (nLaunchers <= 0):
        return
    UnitMenu.AddItem('Change loadout', '')
    UnitMenu.BeginSubMenu()
    
    # if air then add menu for loading with preset db loadouts, if available
    if (UnitInfo.IsAir()):
        loadouts = UnitInfo.GetLoadoutList()
        loadouts.PushBack('AAW')
        loadouts.PushBack('ASuW')
        loadouts.PushBack('ASW')
        loadouts.PushBack('Strike')
        loadouts.PushBack('Nuclear')
        
        UnitMenu.AddItem('Preset','')
        UnitMenu.BeginSubMenu()
        BuildPagedLoadoutMenu(UnitMenu, loadouts, 20, 'EquipLoadout', '')
        UnitMenu.EndSubMenu()
    
    for n in range(0, nLaunchers):
        UnitMenu.AddItem('L%d' % (n+1), '')
        UnitMenu.BeginSubMenu()
        UnitMenu.AddItemWithParam('Unload', 'Unload', n)
        equipment = UnitInfo.GetCompatibleItemList(n)
        BuildPagedLoadoutMenu(UnitMenu, equipment, 20, 'ReloadLauncher', '%d' % n)
        UnitMenu.EndSubMenu()
    UnitMenu.EndSubMenu()

# items is tcStringArray
def BuildPagedLoadoutMenu(Menu, items, page_count, command, prefix):
    nItems = items.Size()
    if (nItems > page_count):
        nPages = nItems/page_count + 1
        for p in range(0, nPages):
            Menu.AddItem('Page %d' % (p+1),'')
            Menu.BeginSubMenu()
            nItemsPage = min(page_count, nItems - p*page_count)
            for n in range(0, nItemsPage):
                itemName = items.GetString(n+p*page_count)
                Menu.AddItemWithTextParam('%s' % itemName, command, prefix + itemName)
            Menu.EndSubMenu()
    else:
        for n in range(0, nItems):
            itemName = items.GetString(n)
            Menu.AddItemWithTextParam('%s' % itemName, command, prefix + itemName)
            

    
def BuildRandomizeEditMenu(UnitMenu, UnitInfo):
    include_prob = 100.0*UnitInfo.GetIncludeProbability()
    
    UnitMenu.AddItem('Randomize', '')
    UnitMenu.BeginSubMenu()

    UnitMenu.AddItem('Include probability (%.0f%%)' % include_prob, '')
    UnitMenu.BeginSubMenu()
    UnitMenu.AddItemWithTextParam('10%', 'SetIncludeProbability', '0.1')
    UnitMenu.AddItemWithTextParam('25%', 'SetIncludeProbability', '0.25')
    UnitMenu.AddItemWithTextParam('50%', 'SetIncludeProbability', '0.5')
    UnitMenu.AddItemUI('Enter', 'SetIncludeProbability', 'Text')
    UnitMenu.EndSubMenu()

    UnitMenu.AddItem('Start location', '')
    UnitMenu.BeginSubMenu()
    UnitMenu.AddItem('Add random box', 'AddRandomBox')
    UnitMenu.AddItem('DeleteAllRandomBoxes', 'DeleteAllRandomBoxes');
    UnitMenu.EndSubMenu()

    UnitMenu.EndSubMenu()

def BuildRenameMenu(UnitMenu, UnitInfo):
    UnitMenu.AddItem('Rename', '')
    UnitMenu.BeginSubMenu()
    UnitMenu.AddItemUI('Enter name', 'RenamePlatform', 'Text Enter unit name')
    real_names = UnitInfo.GetPlatformNameList()
    if (real_names.Size() > 0):
        UnitMenu.AddItem('Select name', '')
        UnitMenu.BeginSubMenu()
        for k in range(0, real_names.Size()):
            name_k = real_names.GetString(k)
            UnitMenu.AddItemWithTextParam('%s' % name_k, 'RenamePlatform', '%s' % name_k)
        UnitMenu.EndSubMenu()
    UnitMenu.EndSubMenu()

def BuildSubmarineEditMenu(UnitMenu, UnitInfo):
    UnitMenu.AddItem('Set depth','')
    UnitMenu.BeginSubMenu()
    UnitMenu.AddItem('Surface','DepthSurface')
    UnitMenu.AddItem('Periscope','DepthPeriscope')
    UnitMenu.AddItem('Medium','DepthMedium')
    UnitMenu.AddItem('Deep','DepthDeep') 
    UnitMenu.EndSubMenu()

    SubMenu = UnitInfo.GetSubInterface()
    if (SubMenu.IsAtPeriscopeDepth()):
        UnitMenu.AddItem('Scope-Mast','')
        UnitMenu.BeginSubMenu()
        if (SubMenu.IsPeriscopeRaised()):
            UnitMenu.AddItemWithParam('Lower scope', 'SetPeriscope', 0)
        else:
            UnitMenu.AddItemWithParam('Raise scope', 'SetPeriscope', 1)
            
        if (SubMenu.IsRadarMastRaised()):
            UnitMenu.AddItemWithParam('Lower mast', 'SetRadarMast', 0)
        else:
            UnitMenu.AddItemWithParam('Raise mast', 'SetRadarMast', 1)
            
        if (SubMenu.IsDieselElectric()):
            if (SubMenu.IsSnorkeling()):
                UnitMenu.AddItemWithParam('Stop snorkeling', 'SetSnorkel', 0)
            else:
                UnitMenu.AddItemWithParam('Start snorkeling', 'SetSnorkel', 1)

        UnitMenu.EndSubMenu()
        
    UnitMenu.AddItem('Mounts','')
    UnitMenu.BeginSubMenu()
    nCount = UnitInfo.GetLauncherCount()
    for n in range(0, nCount):
        weap_name = UnitInfo.GetLauncherWeaponName(n)
        weap_qty = UnitInfo.GetLauncherQuantity(n)
        if (weap_qty == 0):
            nTypes = UnitInfo.GetLauncherTypesCount(n)
            for k in range(0, nTypes):
                type_name = UnitInfo.GetLauncherTypeName(n, k)
                reload_qty = UnitInfo.GetMagazineQuantity(type_name)
                if (reload_qty > 0):
                    UnitMenu.AddItemWithTextParam('Reload %s [%d]' % (type_name, reload_qty), 'Reload%d' % n, type_name)
        else:
            if (UnitInfo.CanMagazineAcceptItem(weap_name)):
                UnitMenu.AddItemWithParam('Unload %s' % weap_name, 'Unload', n)
    UnitMenu.EndSubMenu()

def BuildFormationMenu(UnitMenu, UnitInfo):
    UnitMenu.AddItem('Formation', '')
    UnitMenu.BeginSubMenu()
	
    formEditId = UnitInfo.GetFormationEditId()
    myId = UnitInfo.GetPlatformId()
	
    if (~UnitInfo.IsFormationLeader()):
        if (UnitInfo.IsInFormation()):
            leaderId = UnitInfo.GetFormationLeader()
            UnitMenu.AddItemWithParam('Leave formation', 'SetFormationLeader', -2)
            UnitMenu.AddItemUI('Change formation leader', 'SetFormationLeader', 'Target')
            UnitMenu.AddItem('Formation mode','')
            current_mode = UnitInfo.GetFormationMode()
            UnitMenu.BeginSubMenu()
            if (current_mode == 1): # FOLLOW mode
                UnitMenu.AddItemWithParam('Follow [x]', 'SetFormationMode', 1)
                UnitMenu.AddItemWithParam('Sprint-drift', 'SetFormationMode', 2)
            else:
                UnitMenu.AddItemWithParam('Follow', 'SetFormationMode', 1)
                UnitMenu.AddItemWithParam('Sprint-drift [x]', 'SetFormationMode', 2)
            UnitMenu.EndSubMenu()
            if (formEditId == leaderId):
                UnitMenu.AddItem('Clear formation edit', 'DisableFormationEdit')
            else:
                UnitMenu.AddItem('Enable formation edit', 'EnableFormationEdit')
        else:
            UnitMenu.AddItemUI('Set formation leader', 'SetFormationLeader', 'Target')
    if (UnitInfo.IsFormationLeader()):
        if (formEditId == myId):
            UnitMenu.AddItem('Clear formation edit', 'DisableFormationEdit')
        else:
            UnitMenu.AddItem('Enable formation edit', 'EnableFormationEdit')
        
    UnitMenu.EndSubMenu()


def BuildPagedCreateMenu(SM, Menu, create_class, page_count):
    Menu.BeginSubMenu()
    platforms = SM.GetPlatformListByClass(create_class)
    nPlatforms = platforms.Size()
    if (nPlatforms > page_count):
        nSubmenus = nPlatforms/page_count + 1
        if (SM.IsUsingNATONames()):
            for sm in range(0, nSubmenus):
                Menu.AddItem('Page %d' % (sm+1),'')
                Menu.BeginSubMenu()
                nPlatformsPage = min(page_count, nPlatforms - sm*page_count)
                for n in range(0, nPlatformsPage):
                    className = platforms.GetString(n+sm*page_count)
                    displayName = SM.GetDisplayName(className)
                    if (displayName != className):
                        Menu.AddItemUIWithTextParam('%s (%s)' % (className, displayName), 'AddNewPlatform', 'Datum', className)
                    else:
                        Menu.AddItemUIWithTextParam('%s' % className, 'AddNewPlatform', 'Datum', className)
                Menu.EndSubMenu()
        else:
            for sm in range(0, nSubmenus):
                Menu.AddItem('Page %d' % (sm+1),'')
                Menu.BeginSubMenu()
                nPlatformsPage = min(page_count, nPlatforms - sm*page_count)
                for n in range(0, nPlatformsPage):
                    className = platforms.GetString(n+sm*page_count)
                    Menu.AddItemUIWithTextParam('%s' % className, 'AddNewPlatform', 'Datum', className)
                Menu.EndSubMenu()
    else:
        for n in range(0, nPlatforms):
            className = platforms.GetString(n)
            Menu.AddItemUIWithTextParam('%s' % className, 'AddNewPlatform', 'Datum', className)
    Menu.EndSubMenu()

    
def BuildPagedCreateChildMenu(SM, Menu, create_class, page_count):
    Menu.BeginSubMenu()
    platforms = SM.GetPlatformListByClass(create_class)
    nPlatforms = platforms.Size()
    if (nPlatforms > page_count):
        nSubmenus = nPlatforms/page_count + 1
        for sm in range(0, nSubmenus):
            Menu.AddItem('Page %d' % (sm+1),'')
            Menu.BeginSubMenu()
            nPlatformsPage = min(page_count, nPlatforms - sm*page_count)
            for n in range(0, nPlatformsPage):
                className = platforms.GetString(n+sm*page_count)
                Menu.AddItemUIWithTextParam('%s' % className, 'AddNewPlatformToFlightDeck', 'Target', className)
            Menu.EndSubMenu()
    else:
        for n in range(0, nPlatforms):
            className = platforms.GetString(n)
            Menu.AddItemUIWithTextParam('%s' % className, 'AddNewPlatformToFlightDeck', 'Target', className)
    Menu.EndSubMenu()
    
def BuildPagedCreateChildMenuUnit(UI, Menu, create_class, page_count):
    Menu.BeginSubMenu()
    platforms = UI.GetPlatformListByClass(create_class)
    nPlatforms = platforms.Size()
    if (nPlatforms > page_count):
        nSubmenus = nPlatforms/page_count + 1
        for sm in range(0, nSubmenus):
            Menu.AddItem('Page %d' % (sm+1),'')
            Menu.BeginSubMenu()
            nPlatformsPage = min(page_count, nPlatforms - sm*page_count)
            for n in range(0, nPlatformsPage):
                className = platforms.GetString(n+sm*page_count)
                Menu.AddItemWithTextParam('%s' % className, 'AddToMyFlightDeck', className)
            Menu.EndSubMenu()
    else:
        for n in range(0, nPlatforms):
            className = platforms.GetString(n)
            Menu.AddItemWithTextParam('%s' % className, 'AddToMyFlightDeck', className)
    Menu.EndSubMenu()


def BuildPagedAddStores(UI, Menu, stores_class, page_count):
    Menu.BeginSubMenu()
    equipment = UI.GetEquipmentListByClass(stores_class)
    nEquipment = equipment.Size()
    if (nEquipment > page_count):
        nSubmenus = nEquipment/page_count + 1
        for sm in range(0, nSubmenus):
            Menu.AddItem('Page %d' % (sm+1),'')
            Menu.BeginSubMenu()
            nPage = min(page_count, nEquipment - sm*page_count)
            for n in range(0, nPage):
                className = equipment.GetString(n+sm*page_count)
                Menu.AddItemWithTextParam('%s' % className, 'AddItemToMagazine', className)
            Menu.EndSubMenu()
    else:
        for n in range(0, nEquipment):
            className = equipment.GetString(n)
            Menu.AddItemWithTextParam('%s' % className, 'AddItemToMagazine', className)
    Menu.EndSubMenu()    
    
    
def StartGoalTree(Menu, SM):
    Menu.AddItem('Goals', '')
    Menu.BeginSubMenu()
    top_goal = SM.GetAllianceGoal(SM.GetUserAlliance())
    if (top_goal.GetTypeString() != 'Error'):
        BuildGoalTree(Menu, SM, top_goal)
    else: # no top-level goal for alliance
        InsertAddGoalAllianceMenu(Menu, SM)
            
    Menu.EndSubMenu()
    
    
def BuildGoalTree(Menu, SM, goal):
    Menu.SetStayOpen(1)
    goal_type = goal.GetTypeString()
    if (goal_type == 'Compound'):
        compound_goal = goal.AsCompoundGoal()
        if (compound_goal.GetLogicType() == 0): # and
            description = 'Compound AND'
        else:
            description = 'Compound OR'
        Menu.AddItem(description, '')
        Menu.BeginSubMenu()
        Menu.AddItemWithParam('Delete this', 'DeleteGoal', compound_goal.GetId())
        Menu.AddItemWithParam('Toggle type', 'ToggleCompoundType', compound_goal.GetId())
        nGoals = compound_goal.GetSubGoalCount()
        for n in range(0, nGoals):
            BuildGoalTree(Menu, SM, compound_goal.GetSubGoal(n))

        InsertAddGoalMenu(Menu, SM, compound_goal)    
        Menu.EndSubMenu()
    elif (goal_type == 'Destroy'):
        destroy_goal = goal.AsDestroyGoal()
        description = 'Destroy %d/%d' % (destroy_goal.GetQuantity(), destroy_goal.GetTargetCount())
        Menu.AddItem(description, '')
        Menu.BeginSubMenu()
        Menu.AddItemWithParam('Delete', 'DeleteGoal', destroy_goal.GetId())
        InsertGoalTargetMenu(Menu, SM, destroy_goal)
        Menu.EndSubMenu()
    elif (goal_type == 'Protect'):
        protect_goal = goal.AsProtectGoal()
        description = 'Protect %d/%d' % (protect_goal.GetQuantity(), protect_goal.GetTargetCount())
        Menu.AddItem(description, '')
        Menu.BeginSubMenu()
        Menu.AddItemWithParam('Delete', 'DeleteGoal', protect_goal.GetId())
        InsertGoalTargetMenu(Menu, SM, protect_goal)
        Menu.EndSubMenu()        
    elif (goal_type == 'Time'):
        time_goal = goal.AsTimeGoal()
        pass_minutes = (1.0/60.0)*time_goal.GetPassTimeout()
        fail_minutes = (1.0/60.0)*time_goal.GetFailTimeout()
        
        if (pass_minutes < fail_minutes):
            description = 'Time +%.0f m' % pass_minutes
        else:
            description = 'Time -%.0f m' % fail_minutes
        Menu.AddItem(description, '')
        Menu.BeginSubMenu()
        Menu.AddItemWithParam('Delete', 'DeleteGoal', time_goal.GetId())
        Menu.AddItemUIWithParam('Set pass time', 'ChangePassTime', 'Text Enter pass minutes', time_goal.GetId())
        Menu.AddItemUIWithParam('Set fail time', 'ChangeFailTime', 'Text Enter fail minutes', time_goal.GetId())        
        Menu.EndSubMenu()
    elif (goal_type == 'Area'):
        area_goal = goal.AsAreaGoal()
        description = 'Area goal'
        Menu.AddItem(description, '')
        Menu.BeginSubMenu()
        Menu.AddItemWithParam('Delete', 'DeleteGoal', area_goal.GetId())
        if (area_goal.GetEnterGoal()):
            s = '%d%d' % (0, area_goal.GetId())
            Menu.AddItemWithTextParam('Switch to avoid', 'SetAreaEnter', s)
        else:
            s = '%d%d' % (1, area_goal.GetId())
            Menu.AddItemWithTextParam('Switch to enter', 'SetAreaEnter', s)
        
        timeDelay_min = int(0.5 + 0.0166666 * area_goal.GetTimeObjective())
        Menu.AddItemUIWithParam('Set time delay (%d)' % timeDelay_min, 'SetAreaTimeDelay', 'Text Enter Time Delay in Minutes', area_goal.GetId())
        
        if (area_goal.IsLogicAny()):
            s = '%d%d' % (0, area_goal.GetId())
            Menu.AddItemWithTextParam('Set logic ALL', 'SetAreaLogic', s)
        else:
            s = '%d%d' % (1, area_goal.GetId())
            Menu.AddItemWithTextParam('Set logic ANY', 'SetAreaLogic', s)
            
        Menu.AddItem('Edit units', '');
        Menu.BeginSubMenu()
        area_goal_id = area_goal.GetId()
        Menu.AddItemWithTextParam('Clear', 'SetAreaTargets', '%04d' % area_goal_id)
        Menu.AddItemUIWithParam('Add specific unit', 'AddAreaTarget', 'Target', area_goal_id)
        Menu.AddItemWithTextParam('Add all', 'SetAreaTargets', '%04dAll' % area_goal_id)
        Menu.AddItemWithTextParam('Add all air', 'SetAreaTargets', '%04dAir' % area_goal_id)
        Menu.AddItemWithTextParam('Add all surface', 'SetAreaTargets', '%04dSurface' % area_goal_id)
        Menu.AddItemWithTextParam('Add all sub', 'SetAreaTargets', '%04dSub' % area_goal_id)
        Menu.AddItemWithTextParam('Add all ground', 'SetAreaTargets', '%04dGround' % area_goal_id)
        
        quantity = area_goal.GetQuantity()
        Menu.AddItem('Set quantity (%d)' % quantity,'')
        Menu.BeginSubMenu()
        Menu.AddItemUIWithParam('Enter', 'SetGoalQuantity2', 'Text', goal.GetId()) 
        for n in range(1, 9):
            arg_string = '%08d%02d' % (goal.GetId(), n)
            Menu.AddItemWithTextParam('%d' % n, 'SetGoalQuantity', arg_string)
        Menu.EndSubMenu()        
        
        Menu.EndSubMenu()
        
        Menu.EndSubMenu()       
        Menu.SetStayOpen(0)
    
def InsertAddGoalMenu(Menu, SM, compound_goal):
    Menu.AddItem('Add goal','')
    Menu.BeginSubMenu()
    Menu.AddItemWithParam('Compound', 'AddCompoundGoal', compound_goal.GetId())
    Menu.AddItemWithParam('Time', 'AddTimeGoal', compound_goal.GetId())
    Menu.AddItemUIWithParam('Destroy', 'AddDestroyGoal', 'Target', compound_goal.GetId())
    Menu.AddItemUIWithParam('Protect', 'AddProtectGoal', 'Target', compound_goal.GetId())    
    Menu.AddItemUIWithParam('Area', 'AddAreaGoal', 'Datum', compound_goal.GetId())        
    Menu.EndSubMenu()

# version that adds goal as top-level alliance goal
def InsertAddGoalAllianceMenu(Menu, SM):
    Menu.AddItem('Add side goal','')
    Menu.BeginSubMenu()
    Menu.AddItemWithParam('Compound', 'AddCompoundGoalAlliance', SM.GetUserAlliance())
    Menu.AddItemWithParam('Time', 'AddTimeGoalAlliance', SM.GetUserAlliance())
    Menu.AddItemWithParam('Destroy', 'AddDestroyGoalAlliance', SM.GetUserAlliance())
    Menu.AddItemWithParam('Protect', 'AddProtectGoalAlliance', SM.GetUserAlliance())
    Menu.AddItemUIWithParam('Area', 'AddAreaGoalAlliance', 'Datum', SM.GetUserAlliance())    
    Menu.EndSubMenu()    
    
    
def InsertGoalTargetMenu(Menu, SM, goal):
    Menu.AddItemUIWithParam('Add target', 'AddGoalTarget', 'Target', goal.GetId())
    Menu.AddItemUIWithParam('Add targets in area', 'AddGoalTargetArea', 'Box', goal.GetId())
    nTargets = goal.GetTargetCount()
    Menu.AddItem('Remove targets (%d)' % nTargets,'')
    Menu.BeginSubMenu()
    for n in range(0,nTargets):
        target_n = goal.GetTargetName(n)
        arg_string = '%08d%s' % (goal.GetId(), target_n)
        Menu.AddItemWithTextParam(target_n, 'RemoveGoalTarget', arg_string)
    Menu.EndSubMenu()
    quantity = goal.GetQuantity()
    Menu.AddItem('Set Quantity (%d)' % quantity,'')
    Menu.BeginSubMenu()
    Menu.AddItemUIWithParam('Enter', 'SetGoalQuantity2', 'Text', goal.GetId()) 
    for n in range(1, 9):
        arg_string = '%08d%02d' % (goal.GetId(), n)
        Menu.AddItemWithTextParam('%d' % n, 'SetGoalQuantity', arg_string)
    Menu.EndSubMenu()
    
def BuildGroupEditMenu(GroupMenu, GroupInfo):
    GroupMenu.Clear()
    
    unit_count = GroupInfo.GetUnitCount()
    if (unit_count <= 0):
        return
    
    
    Amram_Menu.BuildAmramMenu(GroupMenu, GroupInfo, EditMode = True)
    return
    #determine number of carriers, helos, subs etc. in group
    #used to build menu depending on group configuration
    carrier_count = 0
    helo_count = 0
    air_count = 0
    for n in range(0,unit_count):
        UI = GroupInfo.GetPlatformInterface(n)
        if(UI.HasFlightPort()):
            carrier_count = carrier_count + 1
        if(UI.IsHelo()):
            helo_count = helo_count + 1
        if(UI.IsAir()):
            air_count = air_count + 1

    GroupMenu.AddItem('Total units: %d' % unit_count, '')

    # display info if group consists only of aircraft/helo 
    if(air_count==unit_count and helo_count == 0):
        GroupMenu.AddItem('Air Group: %d units' % air_count,'')
    if(helo_count==unit_count):
        GroupMenu.AddItem('Helo Group: %d units' % helo_count,'')

    GroupMenu.AddItemUI('Duplicate', 'CopyGroup', 'Datum')
    GroupMenu.AddItemUI('Rename Group', 'RenameGroup', 'Text Enter Group Name')
    GroupMenu.AddItem('Navigate','')
    GroupMenu.BeginSubMenu()
    GroupMenu.AddItemUI('Move group', 'MoveGroup', 'Datum')
    GroupMenu.AddItemUI('Rotate group', 'RotateGroup', 'Heading')
    GroupMenu.AddItemUI('Set heading [h]','SetHeadingGroup','Heading')

    # Group Speed relative to fastest unit
    GroupMenu.AddItem('GroupSpeed','')
    GroupMenu.BeginSubMenu()
    GroupMenu.AddItem('30% [1]','RelGroupSpeed30')
    GroupMenu.AddItem('50% [2]','RelGroupSpeed50')
    GroupMenu.AddItem('80% [3]','RelGroupSpeed80')
    GroupMenu.AddItem('100% [4]','RelGroupSpeed100')
    GroupMenu.AddItem('Max [5]','RelGroupSpeedMax')
    GroupMenu.EndSubMenu()

    # aircraft/helo altitude submenu, when group is aircraft/helo only
    # we add a specific altitude control submenu. 
    if(air_count == unit_count and helo_count == 0):
        GroupMenu.AddItem('Set Altitude','')
        GroupMenu.BeginSubMenu()
        GroupMenu.AddItem('High','GroupAltitudeHigh')
        GroupMenu.AddItem('Medium','GroupAltitudeMedium')
        GroupMenu.AddItem('Low','GroupAltitudeLow')
        GroupMenu.AddItem('Very low','GroupAltitudeVeryLow') 
        GroupMenu.EndSubMenu()
    if(helo_count == unit_count):
        GroupMenu.AddItem('Altitude','')
        GroupMenu.BeginSubMenu()
        GroupMenu.AddItem('Medium','GroupHeloAltitudeMedium')
        GroupMenu.AddItem('Low','GroupHeloAltitudeLow')
        GroupMenu.AddItem('Very low','GroupHeloAltitudeVeryLow') 
        GroupMenu.EndSubMenu()
        
    GroupMenu.EndSubMenu() # Navigate
    GroupMenu.AddItem('Delete group', 'DeleteGroup')
    
    # Group Sensor Settings
    GroupMenu.AddItem('Sensors','')
    GroupMenu.BeginSubMenu()
    GroupMenu.AddItem('Full Sensors','GroupAllSensors')
    GroupMenu.AddItem('Passive Sensors','GroupPassiveSensors')
    GroupMenu.AddItem('Offline','GroupOfflineSensors')
    GroupMenu.EndSubMenu()

        
    # Group orders
    GroupMenu.AddItem('Tasks','')
    GroupMenu.BeginSubMenu()
    GroupMenu.AddItem('Engage all','AddEngageAllOrderGroup')
    GroupMenu.AddItem('Zig-zag patrol','AddPatrolOrderGroup')
    GroupMenu.AddItemUI('Add waypoint', 'AddWaypointOrderGroup', 'Datum')
    GroupMenu.AddItem('Clear all tasks','ClearTasksGroup')
    GroupMenu.EndSubMenu()
    

def BuildROEMenu(UnitMenu, SM):
	return
    # current_alliance = SM.GetUserAlliance()
    # roe = SM.GetAllianceROE(current_alliance)
    # UnitMenu.AddItem('Set ROE','')
    # UnitMenu.BeginSubMenu()
    # if (roe == 0):
        # UnitMenu.AddItemWithParam('Weapons Free [x]','SetAllianceROE',0)
    # else:
        # UnitMenu.AddItemWithParam('Weapons Free','SetAllianceROE',0)
    # if (roe == 1):
        # UnitMenu.AddItemWithParam('Weapons Tight [x]','SetAllianceROE',1)
    # else:
        # UnitMenu.AddItemWithParam('Weapons Tight','SetAllianceROE',1)
    # if (roe == 2):
        # UnitMenu.AddItemWithParam('Weapons Hold [x]','SetAllianceROE',2)
    # else:
        # UnitMenu.AddItemWithParam('Weapons Hold','SetAllianceROE',2)        
        
        
    # UnitMenu.EndSubMenu()
    
def BuildWeaponEditMenu(UnitMenu, WeaponInfo):
    UnitMenu.Clear()
    if (not WeaponInfo.IsValid()):
        return
    
    weapon_type = WeaponInfo.GetWeaponType()
    UnitMenu.AddItem('Weapon Type: %s' % weapon_type, '')
    UnitMenu.AddItemUI('Move unit', 'MovePlatform', 'Datum')
    UnitMenu.AddItemUI('Move unit to coordinate', 'MovePlatformString', 'Text Enter Latitude Longitude')
    UnitMenu.AddItem('Delete unit', 'DeletePlatform')
    UnitMenu.AddItemUI('Rename', 'RenamePlatform', 'Text Enter unit name')
    UnitMenu.AddItemUI('Duplicate', 'CopyPlatform', 'Datum')
    

    