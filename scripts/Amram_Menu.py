#Amram Menu Items.
import sys, os, math
from os.path import dirname, abspath, join, normpath
sys.path.append(abspath(join(dirname(__file__), 'Amram_Script_Data')))
sys.path.append(abspath(join(dirname(__file__), 'Magazine_Generator_Module')))
from UnitCommands import *
from Amram_Utilities import *
from Amram_AI_Weapon_Lists import *
from magazine_generator import *
from EditMenu import BuildCreateUnitMenu, BuildRenameMenu, BuildPagedCreateChildMenuUnit, BuildPagedLoadoutMenu, BuildRandomizeEditMenu
from Alliances import *
import Menu as menu
from DevMode import *
from MissionEditCommands import DeleteGroup

def BuildAmramMenu(Menu, interface, EditMode = False):
    Menu.Clear()
    Menu.SetStayOpen(1)

    Selected = SelectedUnitInventory(interface)
    
    #store the Selected list, we need to do it here under the operative interface.
    #it cannot be stored for the group, so it needs to be stored on every selected unit
    #annoying, but necessary until I can get AddItemUIWithTextParam('','','Target','') working right.
    
    #test for group:
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
        single = True
    except:
        group = True
        single = False
    
    Flight = False
    if group:
        #we're a group, proceed as such
        GI = interface        
        for unit in xrange(interface.GetUnitCount()):
            UI = GI.GetPlatformInterface(unit)
            BB = UI.GetBlackboardInterface()
            Write_Message_List(BB, 'Selected', Selected)
            if UI.HasFlightPort():
                Flight = True
    else:
        #we're solo
        UI = interface
        BB = UI.GetBlackboardInterface()
        Write_Message_List(BB, 'Selected', Selected)
        if UI.HasFlightPort():
            Flight = True
    
#######################
##                   ##
##   Unit Editing    ##
##                   ##
#######################
    
    if EditMode and single:
        loadouts_dict, aircraft_dict = GetLoadouts(interface)
    else:
        loadouts_dict = None
        aircraft_dict = None

#######################
##                   ##
##   Unit Commands   ##
##                   ##
#######################
    
    # Multiplayer options
    if single:
        MultiplayerYieldTakeOwnership(Menu, interface)

    if EditMode:
        Menu.AddItem('Unit Operation','');Menu.BeginSubMenu();Menu.SetStayOpen(1)

    # Navigation commands
    NavigationCommands(Menu, interface, Selected, EditMode)
        
    # Combat commands
    if Selected['Launchers'] > 0:
        CombatMenuItems(Menu, interface, Selected)
    
    # Systems commands
    SystemsMenuItems(Menu, interface, Selected)
    
    # Management commands
    ManagementMenuItems(Menu, interface, Selected)

    #EditMenu Unit Creation
    if EditMode:
        Menu.EndSubMenu()
        Unit_Characteristics_Menu(Menu, interface, Selected, loadouts_dict, aircraft_dict, Flight, group, single)

    #Dev Mode commands
    if single:
        BuildDeveloperMenu(Menu, interface)    

def AmramCreateAllianceUnitMenu(Menu, SM):
    side_name = SM.GetAllianceCountry(SM.GetUserAlliance())
    Menu.AddItem('Create unit','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
    if side_name in Alliance_List.keys():
        #we have an alliance, retrieve the country list.
        alliance = Alliance_List[side_name]['Members']
        for country in sorted(alliance):
            Menu.AddItem('%s' % country,'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            SM.SetAllianceDefaultCountry(SM.GetUserAlliance(),country)
            BuildCreateUnitMenu(Menu, SM)
        Menu.EndSubMenu()
    else:
        BuildCreateUnitMenu(Menu, SM)
    SM.SetAllianceDefaultCountry(SM.GetUserAlliance(), side_name)
    Menu.EndSubMenu()

def MultiplayerYieldTakeOwnership(Menu, interface):    
    if (interface.IsMultiplayerActive()):
        if (not interface.IsPlayerControlled()):
            if (interface.IsAvailable()):
                Menu.AddItem('Take control', 'TakeControl')
                return
            else:
                controller = interface.GetController()
                Menu.AddItem('Unavailable interface (%s)' % controller, '')
                return 
        else:
            Menu.AddItem('Release control', 'ReleaseControl')
        
def NavigationCommands(Menu, interface, Selected, EditMode):
    Menu.AddItem('Navigation','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
    if Selected['Ship'] > 0 or Selected['Air'] > 0 or Selected['Sub'] > 0:
        leads = Selected['FormLeader']
        members = Selected['FormMember']
        sprint = Selected['FormModeSprint']
        pace = Selected['FormModePace']
        Menu.AddItem('Formation Options',''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
        if leads > 0 or members > 0:
            Menu.AddItem('Leaders: %s,  Members: %s' % (leads, members),'')
        Menu.AddItemUI('    Set Formation Leader', 'FormationLeaderInput', 'Target')
        if members > 0:
            Menu.AddItemWithTextParam('    Leave Formation', 'OptionHandler', 'Formation_Member|Function|-2')
            Menu.AddItem('Sprinting: %s, Pacing: %s' % (sprint, pace),'')
            Menu.AddItemWithTextParam('    Formation Follow Leader', 'OptionHandler', 'Formation_Mode_Sprint_Pace|Function|1')
            Menu.AddItemWithTextParam('    Formation Sprint/Drift', 'OptionHandler', 'Formation_Mode_Sprint_Pace|Function|2')
            Menu.AddItemWithTextParam('    Lock Formation Settings', 'OptionHandler', 'FormationEdit|Function|0')
            Menu.AddItemWithTextParam('    Unlock Formation Settings', 'OptionHandler', 'FormationEdit|Function|1')
            Menu.AddItemWithTextParam('    Set Formation North Bearing', 'OptionHandler', 'Formation_Mode_RN|Function|1')
            Menu.AddItemWithTextParam('    Set Formation Relative Bearing', 'OptionHandler', 'Formation_Mode_RN|Function|0')
        Menu.EndSubMenu()

    if Selected['Ship'] > 0 or Selected['Air'] > 0 or Selected['Sub'] > 0 or EditMode:
        Menu.AddItem('Heading Options',''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
        Menu.AddItemWithTextParam('Set Heading', 'OptionHandler', 'HeadingStandard|Function|1')
        Menu.AddItemUI('Enter New Heading', 'HeadingGetInput', 'Text Enter New Heading')
        if EditMode and Selected['UnitCount'] > 1:
            Menu.AddItemUI('Rotate group', 'RotateGroup', 'Heading')
        if Selected['TargetSet'] or Selected['TargetTrack']:
            Menu.AddItemWithTextParam('Intercept Target', 'OptionHandler', 'Intercept|Task|Start')
        Menu.EndSubMenu()
        
    if Selected['Air'] > 0:
        Menu.AddItemWithTextParam('Set Aircraft Cruise Alt/Speed', 'OptionHandler', 'CruiseEnforcement|Task|Start~5~-1')
        Menu.AddItem('Altitude Options','')
        if 1==1:
            Menu.BeginSubMenu(); Menu.SetStayOpen(1)
            Menu.AddItemWithTextParam('Set Altitude Cruise', 'OptionHandler', 'AltitudeStandard|Function|Cruise')
            if Selected['TargetSet'] or Selected['TargetTrack']:
                Menu.AddItemWithTextParam('Match Target Altitude', 'OptionHandler', 'AltitudeMatch|Function|0')
            Menu.AddItemUIWithParam('Enter New Altitude', 'AltitudeGetInput', 'Text Enter New Altitude', 1)
            Menu.AddItemWithTextParam('Set Altitude Max(%dm)' % Selected['Alt+'], 'OptionHandler', 'AltitudeStandard|Function|%s' % Selected['Alt+'])
            alts = [32000, 30000, 28000, 26000, 24000, 22000, 20000, 18000, 16000, 14000, 12000, 10000, 8000, 6000, 5000, 4000, 3000, 2000, 1000, 500, 250, 100, 50]
            for alt in alts:
                if Selected['Alt+'] >= alt:
                    Menu.AddItemWithTextParam('Set Altitude %dm' % alt, 'OptionHandler', 'AltitudeStandard|Function|%d' % alt)
            Menu.EndSubMenu()
    if Selected['Sub'] > 0:
        Menu.AddItem('Depth Options','')
        if 1==1:
            Menu.BeginSubMenu(); Menu.SetStayOpen(1)
            Menu.AddItemUIWithParam('Enter New depth', 'AltitudeGetInput', 'Text Enter New Depth', 2)
            Menu.AddItemWithTextParam('Set Depth Periscope', 'OptionHandler', 'AltitudeStandard|Function|Periscope')
            Menu.AddItemWithTextParam('Set Depth Missile', 'OptionHandler', 'AltitudeStandard|Function|Missile')
            depths = [30, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 600, 700]
            for depth in depths:
                if Selected['Depth+'] >=  depth:Menu.AddItemWithTextParam('Set Depth %dm' % depth, 'OptionHandler', 'AltitudeStandard|Function|-%d' % depth)
            Menu.AddItemWithTextParam('Set Depth Max(%dm)' % Selected['Depth+'], 'OptionHandler', 'AltitudeStandard|Function|-%d' % Selected['Depth+'])
            Menu.EndSubMenu()
    if Selected['Speed+'] > 0 or Selected['Speed-'] > 0:
        Menu.AddItem('Speed Options','')
        if 1==1:
            Menu.BeginSubMenu(); Menu.SetStayOpen(1)
            Menu.AddItemWithTextParam('Cruise',  'OptionHandler', 'SetSpeed|Function|Cruise')
            if Selected['HasThrottle']:
                Menu.AddItem('Throttle','')
                if 1==1:
                    Menu.BeginSubMenu(); Menu.SetStayOpen(1)
                    for throttle in xrange(11):
                        throttle_set = throttle / 10.0
                        show_throttle = throttle_set * 100
                        Menu.AddItemWithTextParam('Throttle %d%%' % show_throttle,  'OptionHandler', 'SetThrottle|Function|%d' % throttle_set)
                    if Selected['FixedWing'] > 0:
                        for throttle in range(6, 11):
                            throttle_set = throttle / 5.0
                            show_throttle = throttle_set * 100 - 100
                            Menu.AddItemWithTextParam('Throttle AB %d%%' % show_throttle,  'OptionHandler', 'SetThrottle|Function|%d' % throttle_set)
                    Menu.EndSubMenu()
            if 1==1:
                Menu.AddItem('Knots - Relative',''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
                speeds = [500, 200, 100, 50, 10, 5, 1]
                for speed in sorted(speeds, reverse = True):
                    if Selected['Speed+'] >= speed:
                        Menu.AddItemWithTextParam('Speed +%dkts' % speed,  'OptionHandler', 'SetSpeed+|Function|%d' % speed)
                for speed in sorted(speeds):
                    if Selected['Speed-'] >= speed:
                        Menu.AddItemWithTextParam('Speed   -%dkts' % speed,  'OptionHandler', 'SetSpeed+|Function|-%d' % speed)
                Menu.EndSubMenu()
            Menu.EndSubMenu()

    Menu.AddItem('Waypoint Options','')
    if Selected['Ship'] > 0 or Selected['Air'] > 0 or Selected['Sub'] > 0 and Selected['Speed+'] > 0:
        Menu.BeginSubMenu(); Menu.SetStayOpen(1)
        Menu.AddItemUI('Add Waypoint', 'CreateWaypointScript', 'Datum')
        Menu.AddItemUI('Remove Waypoint', 'RemoveWaypointScript', 'Text Enter Number of Waypoint to Remove\n Count begins with zero')
        Menu.AddItem('Clear all', 'ClearWaypoints')
        if Selected['UnitCount'] > 1:
            Menu.AddItemWithTextParam('Loop Group Waypoints', 'OptionHandler', 'WaypointLoop|Function|1')
            Menu.AddItemWithTextParam('Dont Group Loop Waypoints', 'OptionHandler', 'WaypointLoop|Function|0')
        else:
            if (interface.GetNavLoopState()):
                Menu.AddItemWithParam('Waypoint Loop off', 'SetNavLoopState', 0)
            else:
                Menu.AddItemWithParam('Waypoint Loop on', 'SetNavLoopState', 1)
        Menu.EndSubMenu()
    Menu.EndSubMenu()
    
def CombatMenuItems(Menu, interface, Selected):
    Menu.AddItem('Combat','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
    if Selected['UnitCount'] > 1:
        group_string = ['Group ','s']
    else:
        group_string = ['','']
    Menu.AddItemUI('Set %s Target' % group_string[0],'OptionSetTargeting', 'Target')
    if Selected['TargetSet'] > 0:
        Menu.AddItemWithTextParam('Clear %sTarget%s' % (group_string[0], group_string[1]),'OptionHandler', 'Target|Function|-1')
    
    
    Menu.AddItem('Engage Target','');Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    if 1==1:
        Menu.AddItem('Launch Weapon At Target', '');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        if 1==1:
            loaded_list = Selected['WeaponList']
            weapon_list = loaded_list.keys()
            weapon_list.sort()
            for weapon_n in xrange(len(weapon_list)):
                if loaded_list[weapon_list[weapon_n]][0] > 0:
                    Menu.AddItemUIWithParam('%s : %d' % (weapon_list[weapon_n], loaded_list[weapon_list[weapon_n]][0]), 'MenuLaunchCommand', 'Target', weapon_n)
            Menu.EndSubMenu()
        if Selected['Air'] > 0:
            Menu.AddItemWithTextParam('Intercept Target', 'OptionHandler','Intercept|Task|Start~1~0')
            if Selected['HasBombs']:
                if Selected['TargetSet']:
                    Menu.AddItemWithTextParam('Dive Bomb Selected Target(s)', 'OptionHandler','BombRunInitialized|Erase|1;Bombing_Complete|Erase|1;BombDatum|Erase|1;Style|Set|dive;BombRun|Task|Start~1~0')
                    Menu.AddItemWithTextParam('Level Bomb Selected Target(s)', 'OptionHandler','BombRunInitialized|Erase|1;Bombing_Complete|Erase|1;BombDatum|Erase|1;Style|Set|level;BombRun|Task|Start~1~0')
                    Menu.AddItemWithTextParam('Loft Bomb Selected Target(s)', 'OptionHandler','BombRunInitialized|Erase|1;Bombing_Complete|Erase|1;BombDatum|Erase|1;Style|Set|loft;BombRun|Task|Start~1~0')
                else:
                    Menu.AddItemUI('Set Dive Bomb Target', 'BombRunSetTargetDive', 'Target')
                    Menu.AddItemUI('Set Level Bomb Target', 'BombRunSetTargetLevel', 'Target')
                    Menu.AddItemUI('Set Loft Bomb Target', 'BombRunSetTargetLoft', 'Target')
                    
        Menu.EndSubMenu()
            
    Menu.AddItem('Engage Datum',''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    if 1==1:
        Menu.AddItem('Launch Weapon At Datum', '');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        if 1==1:
            loaded_list = Selected['WeaponList']
            weapon_list = loaded_list.keys()
            weapon_list.sort()
            for weapon_n in xrange(len(weapon_list)):
                Menu.AddItemUIWithParam('%s : %d' % (weapon_list[weapon_n], loaded_list[weapon_list[weapon_n]][0]), 'MenuLaunchCommand', 'Datum',  weapon_n)
            Menu.EndSubMenu()
        if Selected['Air'] == 1:
            if Selected['HasBombs']:
                Menu.AddItemUI('Dive Bomb Datum', 'BombRunSetDatumDive', 'Datum')
                Menu.AddItemUI('Level Bomb Datum', 'BombRunSetDatumLevel', 'Datum')
                Menu.AddItemUI('Loft Bomb Datum', 'BombRunSetDatumLoft', 'Datum')
        Menu.EndSubMenu()
        
    Menu.EndSubMenu()

def SystemsMenuItems(Menu, interface, Selected):
    Menu.AddItem('Sensors','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        
    if 1==1:
        if Selected['HasRadar']:
            Menu.AddItem('Radar','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            Menu.AddItemWithTextParam('All On','OptionHandler','SensorState|Function|1~1')
            Menu.AddItemWithTextParam('All Off','OptionHandler','SensorState|Function|1~0')
            Menu.EndSubMenu()
        if Selected['HasSonarP'] or Selected['HasSonarA']:
            Menu.AddItem('Sonar','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            Menu.AddItemWithTextParam('All On','OptionHandler','SensorState|Function|4~1;SensorState|Function|8~1')
            Menu.AddItemWithTextParam('All Off','OptionHandler','SensorState|Function|4~0;SensorState|Function|8~0')
            if Selected['HasSonarA']:
                Menu.AddItemWithTextParam('All Active On','OptionHandler','SensorState|Function|8~1')
                Menu.AddItemWithTextParam('All Active Off','OptionHandler','SensorState|Function|8~0')
            if Selected['HasSonarP']:
                Menu.AddItemWithTextParam('All Passive On','OptionHandler','SensorState|Function|4~1')
                Menu.AddItemWithTextParam('All Passive Off','OptionHandler','SensorState|Function|4~0')
            Menu.EndSubMenu()
        if Selected['HasECM']:
            Menu.AddItem('ECM','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            Menu.AddItemWithTextParam('All On','OptionHandler','SensorState|Function|32~1')
            Menu.AddItemWithTextParam('All Off','OptionHandler','SensorState|Function|32~0')
            Menu.EndSubMenu()
        Menu.EndSubMenu()
    if Selected['UnitCount'] == 1 and Selected['Launchers'] and (Selected['Ship'] or Selected['Sub'] or Selected['FixedLand'] or Selected['MobileLand']):
        Menu.AddItem('Launchers','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        UI = interface
        nCount = UI.GetLauncherCount()
        for n in range(0, nCount):
            launcher_info = UI.GetLauncherInfo(n)
            weap_name = UI.GetLauncherWeaponName(n)
            weap_qty = launcher_info.Quantity
            isLoadingUnloading = launcher_info.IsLoading
            if (weap_qty == 0):
                if (not isLoadingUnloading):
                    nTypes = UI.GetLauncherTypesCount(n)
                    for k in range(0, nTypes):
                        type_name = UI.GetLauncherTypeName(n, k)
                        reload_qty = UI.GetMagazineQuantity(type_name)
                        if (reload_qty > 0):
                            Menu.AddItemWithTextParam('Load %s [%d]' % (type_name, reload_qty), 'Reload %d' % n, type_name)
                else:
                    Menu.AddItemWithParam('Cancel load %s' % weap_name, 'Unload', n)
            else:
                if (not isLoadingUnloading):
                    if (UI.CanMagazineAcceptItem(weap_name)):
                        Menu.AddItemWithParam('Unload %s' % weap_name, 'Unload', n)
                    else:
                        Menu.AddItem('Cannot Unload %s' % weap_name, '')
                else:
                    Menu.AddItemWithTextParam('Cancel unload %s' % weap_name, 'Reload%d' % n, weap_name)
        Menu.EndSubMenu()
    if Selected['Sub'] > 0:
        Menu.AddItem('Masts','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        if 1==1:
            if Selected['PeriDeep']:
                if Selected['Periscope-']:
                    Menu.AddItemWithTextParam('Raise Periscope','OptionHandler','Periscope|Function|1')
                if Selected['Periscope+']:
                    Menu.AddItemWithTextParam('Lower Periscope','OptionHandler','Periscope|Function|0')
                if Selected['DieselSub']:
                    if Selected['Snorkel-']:
                        Menu.AddItemWithTextParam('Start Snorkeling','OptionHandler','Snorkel|Function|1')
                    if Selected['Snorkel+']:
                        Menu.AddItemWithTextParam('Stop Snorkeling','OptionHandler','Snorkel|Function|0')
                if Selected['HasRadar']:
                    if Selected['RadarMast-']:
                        Menu.AddItemWithTextParam('Raise Radar','OptionHandler','RadarMast|Function|1')
                    if Selected['RadarMast+']:
                        Menu.AddItemWithTextParam('Lower Radar','OptionHandler','RadarMast|Function|0')
            else:
                Menu.AddItemWithTextParam('Set Depth Periscope', 'OptionHandler', 'AltitudeStandard|Function|Periscope')
            Menu.EndSubMenu()
        Menu.EndSubMenu()

def ManagementMenuItems(Menu, interface, Selected):
    Menu.AddItem('Management','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
    if 1==1:
        Menu.AddItem('Add Tasks','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        Menu.AddItem('Patrol','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        if Selected["UnitCount"] == 1 and not interface.IsFixed():
            Menu.AddItemUI('Patrol station','AddPatrolStation', 'Datum')
            Menu.AddItemUI('Set patrol area', 'SetPatrolArea', 'Box')
            Menu.AddItem('Clear patrol area', 'ClearPatrolArea')
        Menu.EndSubMenu()
        if Selected["UnitCount"] == 1 and interface.IsAir():
            menu.BuildRefuelMenu(Menu, interface)
            menu.BuildLandMenu(Menu, interface)
        if 1==1:
            Menu.AddItemUI('By Name','AddTask', 'Text Name of Task to Add')
            Menu.AddItem('From List','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            useful_tasks = ['BombRun', 'EngageAll', 'EngageAllAir', 'Intercept', 'Land', 'MissileWarning', 'PatrolCircle', 'PointDefence', 'RTB', 'Refuel']
            hidden_tasks = ['MissileWarning', 'PointDefence', 'RTB', 'Refuel']
            for task in useful_tasks:
                if task in hidden_tasks:
                    Menu.AddItemWithTextParam('hidden - %s' % task,'OptionHandler', '%s|Task|Start~1~1' % task)
                else:
                    Menu.AddItemWithTextParam('              %s' % task,'OptionHandler', '%s|Task|Start~1~0' % task)
            Menu.EndSubMenu()
            Menu.EndSubMenu()
        Menu.AddItem('Remove Tasks','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        if 1==1:
            Menu.AddItemUI('By Name','DeleteTask','Text Name of Task to Remove')
            Menu.AddItem('From List','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            tasks = Selected['Tasks']
            for task in tasks:
                Menu.AddItemWithTextParam('%s : %s / %s' % (task, tasks[task], Selected['UnitCount']),'DeleteTask',task)
            Menu.EndSubMenu()
            Menu.EndSubMenu()
        if Selected['UnitCount'] == 1:
            Menu.AddItem('Open Unit Panel','ShowPlatformPanel')
            if Selected['HasMagazine'] == 1:
                Menu.AddItem('Open Magazine Panel','ShowStoresPanel')
            if Selected['HasFlightPort'] == 1:
                Menu.AddItem('Open FlightPort Panel','ShowFlightPanel')
                BuildMissionMenu(Menu, interface)
    Menu.EndSubMenu()
    
def GetLoadouts(UI):
    SM = UI.GetScenarioInterface()
    BB = UI.GetBlackboardInterface()
    if SM.GetFilterByYear():
        Filter = True
    else:
        Filter = False
    filter_list = {}
    aircraft_dict = {}
    
    if UI.HasFlightPort():
        FP = UI.GetFlightPortInfo()
        for n in xrange(FP.GetUnitCount()):
            UIn = FP.GetUnitPlatformInterface(n)
            setups = UIn.GetPlatformSetups()
            for s in xrange(setups.Size()):
                setup = setups.GetString(s)
                filter_list[setup] = None
            try:
                aircraft_dict[UIn.GetPlatformClass()] += 1
            except:
                aircraft_dict[UIn.GetPlatformClass()] = 1
        aircraft_list = aircraft_dict.keys()
        aircraft_list.sort()
    else:
        aircraft_list = [UI.GetPlatformClass()]
        setups = UI.GetPlatformSetups()
        for s in xrange(setups.Size()):
            setup = setups.GetString(s)
            filter_list[setup] = None
        aircraft_dict[UI.GetPlatformClass()]=1
    return read_loadout_file(aircraft_list, Filter, filter_list), aircraft_dict
    
def Amram_Paged_Loadout_Menu(Menu, UI, loadouts_dict, aircraft_dict, additive = False):
    
    SM = UI.GetScenarioInterface()
    Children = False
    if UI.HasFlightPort():
        FP = UI.GetFlightPortInfo()
        if FP.GetUnitCount() > 0:
            Children = True
    BB = UI.GetBlackboardInterface()
    
    if additive:
        if not Children:
            #we cannot do an additive loadout if there are no child aircraft to select from.
            return
        Menu.AddItem('Additive Loadout Menu', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
        if BB.KeyExists('InvMulti'):
            InvMulti = Try_Read_Message(BB, 'InvMulti', 2)
        else:
            BB.Write('InvMulti', '1')
            InvMulti = 1
        Menu.AddItemUIWithParam('Inventory Multiplier: %s' % InvMulti, 'InputHandler', 'Text Inventory Miltiplier, may be less than one', 5)
    else:
        InvMulti = 1
        Menu.AddItem('Loadouts Menu', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    
    Write_Message_List(BB, 'loadouts_dict', loadouts_dict)
    paging = 25
    page_load = False

    if Children or UI.IsAir():
        #is parent menu if UI.IsAir(), child menu is has flightport.
        for armament in sorted(loadouts_dict.iterkeys()):
            Menu.AddItem('%s' % armament,''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
                #aircraft might be long enough to need paging sometime.  prep paging
            for aircraft in sorted(loadouts_dict[armament].iterkeys()):
                count = aircraft_dict[aircraft]
                if Children:
                    Menu.AddItem('%s  %s' % (count, aircraft),''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
                load_max = len(loadouts_dict[armament][aircraft].keys())
                if load_max > paging:
                    #loadouts are long enough to need paging.  prep paging
                    page_load = True
                    page_load_set = 0
                    page_load_end = 1
                    load_count = 0
                for loadout in sorted(loadouts_dict[armament][aircraft].iterkeys()):
                    if page_load:
                        #do aircraft paging task.  Kill submenu to begin next one if warranted.
                        #begin new page with appropriate count.
                        load_count += 1
                        page_val2 = int(load_count/paging) + 1
                        if page_val2 > page_load_end:
                            #we need to start a new page, so close the old one.
                            Menu.EndSubMenu()
                            page_load_end += 1
                        if page_val2 > page_load_set:
                            #initiate the new page.
                            Menu.AddItem('Page %d' % page_load_set,''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
                            page_load_set += 1
                    add = 0
                    if additive:
                        add = 1
                    param = '%s|%s|%s|%s|%s|%s' % (armament, aircraft, loadout, aircraft_dict[aircraft], InvMulti, add)
                    Menu.AddItem('%s' % loadout, '');Menu.BeginSubMenu(); Menu.SetStayOpen(1)
                    Menu.AddItem('Select any item to load all items','')
                    if armament == 'Unknown':
                        Menu.AddItem('It would appear I missed some formatting','')
                        Menu.AddItem('Please post about this loadout so I can','')
                        Menu.AddItem('make it filter correctly in the future.','')
                    for weapon in sorted(loadouts_dict[armament][aircraft][loadout].iterkeys()):
                        if additive:
                            addcount = loadouts_dict[armament][aircraft][loadout][weapon] * InvMulti * count
                        else:
                            addcount = loadouts_dict[armament][aircraft][loadout][weapon]
                        #round it up
                        addcount = int(math.ceil(addcount))
                        Menu.AddItemWithTextParam('%s   %s ' % (addcount, weapon), 'LoadoutHandler', param)
                    Menu.EndSubMenu()
                    if page_load:
                        if load_count == load_max:
                            Menu.EndSubMenu()
                            page_load = False
                            load_count = 0
                            page_load_set = 0
                            page_load_end = 1
                Menu.EndSubMenu()
            if Children:
                Menu.EndSubMenu()
        Menu.EndSubMenu()
    return

def GenericLoadouts(menu, interface):
    if (UI.IsAir()):
        loadouts = UI.GetLoadoutList()
        loadouts.PushBack('AAW')
        loadouts.PushBack('ASuW')
        loadouts.PushBack('ASW')
        loadouts.PushBack('Strike')
        loadouts.PushBack('Nuclear')

        Menu.AddItem('Generic Loadouts','')
        Menu.BeginSubMenu()
        BuildPagedLoadoutMenu(Menu, loadouts, 20, 'EquipLoadout', '')
        Menu.EndSubMenu()
    
def ParentConfigs(Menu, UI):
    if ((not UI.HasMagazine()) and (not UI.HasFlightPort())):
        return
    setupList = UI.GetPlatformSetups()
    if (setupList.Size() == 0):
        return
    Menu.AddItem('Parent Platform Setup', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    Menu.AddItem('Caution:  Applying any of these will replace all launchers,\n                landed aircraft, their launchers, and magazines.','')

    for n in xrange(setupList.Size()):
        setup_n = setupList.GetString(n)
        Menu.AddItemWithTextParam('%s' % setup_n, 'AutoConfigurePlatform', setup_n)
    Menu.EndSubMenu()   
    
def Unit_Characteristics_Menu(Menu, UI, Selected, loadouts_dict, aircraft_dict, Flight, group, single):
    Menu.AddItem('Edit Characteristics', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    if single:
        Menu.AddItemUI('Duplicate', 'CopyPlatform', 'Datum')
        Menu.AddItemUI('Move unit', 'MovePlatform', 'Datum')
        Menu.AddItemUI('Move unit to coordinate', 'MovePlatformString', 'Text Enter Latitude Longitude')
        BuildRenameMenu(Menu, UI)
        Menu.AddItemWithTextParam('Delete Unit', 'OptionHandler', 'DeleteUnit|Function|1')
        ParentConfigs(Menu, UI)
        
        Menu.AddItem("Amram's SetupGenerator",''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
        Menu.AddItem('Stock Level is optional for ships','')
        Menu.AddItem('===================================','')
        Menu.AddItemWithTextParam('Set Low Stock Level', 'OptionHandler', 'MagTonnage|Set|15')
        Menu.AddItemWithTextParam('Set Standard Stock Level', 'OptionHandler', 'MagTonnage|Set|25')
        Menu.AddItemWithTextParam('Set High Stock Level', 'OptionHandler', 'MagTonnage|Set|35')
        BB = UI.GetBlackboardInterface()
        if BB.KeyExists('MagTonnage') or BB.KeyExists('MagItems') or UI.IsSurface():
            Menu.AddItemUI('Autoconfigure Magazine and Launchers', 'MagGenerator', 'Text Please input the date: YYYY/MM/DD')
        else:
            Menu.AddItem('Please set a maximum tonnage or maximum\n item count to enable the generator','')
        Menu.EndSubMenu()
       
        #EditMenu Unit Additions
        Add_To_Magazine_Menu(Menu, UI, loadouts_dict, aircraft_dict)
        if Flight:
            Add_To_FlightDeck(Menu, UI)
        if Selected['Air'] > 0:
            loadouts = 0
            for armament in loadouts_dict:
                for aircraft in loadouts_dict[armament]:
                    if len(loadouts_dict[armament][aircraft].keys()) > 0:
                        loadouts = 1
                        break
            if loadouts:
                Amram_Paged_Loadout_Menu(Menu, UI, loadouts_dict, aircraft_dict)
        Menu.AddItem('Launchers', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
        for launcher_num in xrange(UI.GetLauncherCount()):
            Menu.AddItem('L%d' % (launcher_num+1), '')
            Menu.BeginSubMenu()
            Menu.AddItemWithParam('Unload', 'Unload', launcher_num)
            equipment = UI.GetCompatibleItemList(launcher_num)
            BuildPagedLoadoutMenu(Menu, equipment, 20, 'ReloadLauncher', '%d' % launcher_num)
            Menu.EndSubMenu()
        Menu.EndSubMenu()
        BuildRandomizeEditMenu(Menu, UI)
    else:
        Menu.AddItemUI('Duplicate Group', 'CopyGroup', 'Datum')
        Menu.AddItemUI('Rename Group', 'RenameGroup', 'Text Enter Group Name')
        Menu.AddItemUI('Move group', 'MoveGroup', 'Datum')
        Menu.AddItem('Delete Units', 'DeleteGroup')

        

    Menu.EndSubMenu()
    
def Special_Edit_Items_Menu(Menu, UI):
    Menu.AddItem('Special', '')
    Menu.BeginSubMenu()
    if (UI.IsFixed() or UI.IsGroundVehicle()):
        if (UI.GetAlwaysVisible()):
            Menu.AddItemWithParam('Clear always visible', 'SetAlwaysVisible', 0)
        else:
            Menu.AddItemWithParam('Set always visible', 'SetAlwaysVisible', 1)
    cost_millions = 1e-6 * UI.GetCost()
    Menu.AddItemUI('Set Custom Cost (%.1f)' % cost_millions, 'SetCustomCost', 'Text Enter Custom Cost in Millions')
    Menu.EndSubMenu()

def Add_To_Magazine_Menu(Menu, UI, loadouts_dict, aircraft_dict):
    if not UI.HasMagazine():
        return
    Menu.AddItem('Add Stock To Magazine(s)', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    Menu.AddItemUI('Add by name', 'AddItemToMagazine', 'Text Name of Item to Add')
    paging = 25
    if 1==1:
        magazineAddCount = UI.GetMagazineAddCount()
        Menu.AddItem('Edit quantity (x%d)' % magazineAddCount, ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
        Menu.AddItemWithParam('1', 'SetMagazineAddCount', 1)
        Menu.AddItemWithParam('10', 'SetMagazineAddCount', 10)
        Menu.AddItemWithParam('50', 'SetMagazineAddCount', 50)
        Menu.AddItemWithParam('100', 'SetMagazineAddCount', 100)
        Menu.SetStayOpen(0)
        Menu.AddItemUI('Enter value', 'SetMagazineAddCount', 'Text')
        Menu.EndSubMenu()
    
    Suggested_Items_Menu(Menu, UI, loadouts_dict)
    Amram_Paged_Loadout_Menu(Menu, UI, loadouts_dict, aircraft_dict, additive = True)    
    Menu.EndSubMenu()
    
def Suggested_Items_Menu(Menu, UI, loadouts_dict):

    classified = Get_Relevant_Stock(UI, loadouts_dict)
    categories = [['MIS', 'Missile'], ['ROC', 'Rocket'], ['GBU', 'Guided Bomb'], ['UBU', 'Unguided Bomb'], ['GUN', 'Gun Round'], ['TRP', 'Torpedo'], ['BUI', 'Sonobuoy'], ['CM',  'Counter Measure'], ['UNK', 'Unknown Item Type'], ['NUC', 'Nuclear'], ['MIN', 'Mines'], ['FUEL', 'Fuel Tanks']]
    
    DoOwner = []
    Proceed = False
    for category in categories:
        if len(classified['Parent'][category[0]].keys()) > 0:
            DoOwner.append('Parent')
            Proceed = True
        if len(classified['Child'][category[0]].keys()) > 0:
            DoOwner.append('Child')
            Proceed = True
    paging = 25
    if Proceed:
        Menu.AddItem('Add Suggested', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
        Menu.AddItemWithTextParam('Fuel', 'AddItemToMagazine', 'Fuel')
        for owner in classified:
            if owner in DoOwner:
                Menu.AddItem('%s Stock' % owner, ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
                for category in categories:
                    nItems = len(classified[owner][category[0]].keys())
                    if nItems > 0:
                        Menu.AddItem('%s' % category[1], ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
                        item_list = sorted(classified[owner][category[0]].iterkeys())
                        if nItems > paging:
                            nPages = int(ceil(float(nItems)/paging))
                            for p in xrange(nPages):
                                nItemsPage = min(paging, nItems - p*paging)
                                Menu.AddItem('Page %d' % (p+1), ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
                                for n in xrange(nItemsPage):
                                    item = item_list[(p*paging)+n]
                                    Menu.AddItemWithTextParam('%s' % item, 'AddItemToMagazine', item)
                                Menu.EndSubMenu()
                        else:
                            for item in classified[owner][category[0]]:
                                Menu.AddItemWithTextParam('%s' % item, 'AddItemToMagazine', item)
                        Menu.EndSubMenu()
                Menu.EndSubMenu()
        Menu.EndSubMenu()
    
def Add_To_FlightDeck(Menu, UI):
    Menu.AddItem('Add to flight deck',''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    group_name = UI.GetAirGroupName()
    group_count = UI.GetAirGroupCount()
    start_id = UI.GetAirUnitId()
    Menu.AddItem('Set group (%s-%d x%d)' % (group_name, start_id, group_count), ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    Menu.AddItemUI('Name', 'SetAirGroupNameUnit', 'Text')
    
    Menu.SetStayOpen(1)
    Menu.AddItem('Size',''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    Menu.AddItemWithParam('1', 'SetAirGroupSizeUnit', 1)
    Menu.AddItemWithParam('2', 'SetAirGroupSizeUnit', 2)
    Menu.AddItemWithParam('4', 'SetAirGroupSizeUnit', 4)
    Menu.AddItemUI('Enter value', 'SetAirGroupSizeUnit', 'Text')
    Menu.EndSubMenu()
    Menu.EndSubMenu()

    # Create fixed wing air on carrier or airstrip ###
    Menu.AddItem('Air fixed wing','')
    BuildPagedCreateChildMenuUnit(UI, Menu, 'AirFW', 25)
    # Create helo on carrier or airstrip ###
    Menu.AddItem('Helo','')
    BuildPagedCreateChildMenuUnit(UI, Menu, 'Helo', 25)
    Menu.EndSubMenu()
    
def Add_Mission_Menu(Menu, UI):
    Menu.AddItem('Add mission', '')
    Menu.BeginSubMenu()
    Menu.AddItemUI('CAP', 'AddCAPMission', 'Datum')      
    Menu.EndSubMenu()

# menu for adding and editing aircraft missions    
def BuildMissionMenu(UnitMenu, UnitInfo):
    FP = UnitInfo.GetFlightPortInfo()
    if (not FP.IsValid()):
        return
        
    hasCAP = FP.HasAircraftForMission('cap')
    hasStrike = FP.HasAircraftForMission('strike')
    hasASW = FP.HasAircraftForMission('asw')
    hasAEW = FP.HasAircraftForMission('aew') 
    
    if (hasCAP or hasAEW or hasStrike or hasASW):
        UnitMenu.AddItem('Quick Mission', '')
        UnitMenu.BeginSubMenu()
        
        UnitMenu.AddItem('Add', '')
        UnitMenu.BeginSubMenu()
        if (hasCAP):
            UnitMenu.AddItemUI('CAP', 'AddCAPMission', 'Datum')
        if (hasStrike):
            UnitMenu.AddItemUI('Land/Surf Attack', 'AddAttackMission', 'Target')
        if (hasASW):
            UnitMenu.AddItemUI('ASW Patrol', 'AddASWMission', 'Datum')
        if (hasAEW):
            UnitMenu.AddItemUI('AEW Patrol', 'AddAEWMission', 'Datum')
        UnitMenu.EndSubMenu()
        
        UnitMenu.EndSubMenu()
    
########################
##                    ##
##   Menu Utilities   ##
##                    ##
########################
    
def BuildDeveloperMenu(Menu, UI):
    if (UI.IsDeveloperMode() == 0):
        return
    Menu.AddItem('Dev tools', '')
    Menu.BeginSubMenu()
    Menu.AddItemUI('Move unit', 'MovePlatformDev', 'Datum')
    if (UI.HasThrottle()):
        Menu.AddItem('Speed vs alt', '*ShowAirInfo')
    BuildDamageMenu(Menu, UI)
    Menu.AddItem('TestCollision', '*TestCollision')
    Menu.AddItem('TestCrossSection', '*TestCrossSection')
    Menu.AddItem('ShowPlatformDebug', '*ShowPlatformDebug')
    Menu.AddItem('Show Sonar Panel', '*ShowSonarPanel')
    Menu.AddItem('Make invulnerable', 'MakePlatformInvulnerable')
    Menu.AddItem('Show best launcher', 'ReportBestLauncherForTarget')
    BuildLoadLauncherMenuAll(Menu, UI)
    BuildSetFuelMenu(Menu, UI)
    BuildLaunchAtMeMenu(Menu, UI)
    Menu.EndSubMenu()       
 
def SelectedUnitInventory(interface):
    Selected = {'Air':0,
                'FixedWing':0,
                'RotaryWing':0,
                'Ship':0,
                'Sub':0,
                'FixedLand':0,
                'MobileLand':0,
                'Launchers':0,
                'HasTarget':0,
                'HasThrottle':0,
                'Speed+':0,
                'Speed-':0,
                'Alt+':0,
                'Depth-':0,
                'Depth+':0,
                'TargetDatum':0,
                'TargetTrack':0,
                'TargetSet':0,
                'HasAIWeap':0,
                'HasAINav':0,
                'UnitCount':0,
                'HasBombs':0,
                'CanStrafe':0,
                'WeaponList':{},
                'MagWeaponList':{},
                'Tasks':{},
                'Snorkel+':0,
                'Snorkel-':0,
                'Periscope+':0,
                'Periscope-':0,
                'PeriDeep':0,
                'RadarMast+':0,
                'RadarMast-':0,
                'DieselSub':0,
                'HasRadar':0,
                'HasSonarA':0,
                'HasSonarP':0,
                'HasOptical':0,
                'HasECM':0,
                'HasESM':0,
                'HasFlightPort':0,
                'HasMagazine':0,
                'FormLeader':0,
                'FormMember':0,
                'FormModeSprint':0,
                'FormModePace':0,
                }
    group = False
    try:
        #maybe we are a group
        test = interface.GetUnitCount()
        group = True
    except:
        #maybe we are not.
        group = False
        
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            Selected = PerformInventory(UI, Selected)
    else:
        UI = interface
        Selected = PerformInventory(UI, Selected)
    return Selected 
 
def PerformInventory(UI, Selected):
    
    BB = UI.GetBlackboardInterface()
            
    if UI.IsSurface():
        Selected['Ship'] += 1
    elif UI.IsAir():
        Selected['Air'] += 1
        if UI.IsHelo():
            Selected['RotaryWing'] += 1
        else:
            Selected['FixedWing'] += 1
        if UI.GetMaxAlt() > Selected['Alt+']:
            Selected['Alt+'] = UI.GetMaxAlt()
    elif UI.IsSub():
        SI = UI.GetSubInterface()
        Selected['Sub'] += 1
        if SI.GetMaxDepth() > Selected['Depth+']:
            Selected['Depth+'] = SI.GetMaxDepth()
        if SI.IsPeriscopeRaised():
            Selected['Periscope+'] = 1
        else:
            Selected['Periscope-'] = 1
        if SI.IsRadarMastRaised():
            Selected['RadarMast+'] = 1 
        else:
            Selected['RadarMast-'] = 1 
        if SI.IsAtPeriscopeDepth():
            Selected['PeriDeep'] = 1
        if SI.IsSnorkeling():
            Selected['Snorkel+'] = 1
        else:
            Selected['Snorkel-'] = 1
        if SI.IsDieselElectric():
            Selected['DieselSub'] = 1
    elif UI.IsFixed():
        Selected['FixedLand'] += 1
    elif UI.IsGroundVehicle():
        Selected['MobileLand'] += 1
    speeds = [1,5,10,50,100,200,500]
    for speed in speeds:
        if UI.IsAir() and UI.HasThrottle():
            if UI.GetSpeed() + speed <= max(UI.GetMaxSpeedForAltitude(UI.GetAlt()), UI.GetMaxSpeedForAltitudeAB(UI.GetAlt())):
                if speed > Selected['Speed+']:
                    Selected['Speed+'] = speed
        else:
            if UI.GetSpeed() + speed <= UI.GetMaxSpeed():
                if speed > Selected['Speed+']:
                    Selected['Speed+'] = speed
        if UI.GetSpeed() >= speed:
            if speed > Selected['Speed-']:
                Selected['Speed-'] = speed
    if BB.KeyExists('MissionTarget'):
        MissionTarget = Read_Message_List(BB, 'MissionTarget')
        if type(MissionTarget[1]) == type([]):
            Selected['TargetDatum'] = 1
        else:
            Selected['TargetTrack'] = 1
    if UI.GetTarget() > 0:
        Selected['TargetSet'] = 1
    if UI.HasFlightPort():
        Selected['HasFlightPort'] = 1
    if UI.HasMagazine():
        Selected['HasMagazine'] = 1
    if UI.GetLauncherCount() > 0:
        Selected['Launchers'] = 1
        Loaded_List = Selected['WeaponList']
        Potential_Load_List = Selected['MagWeaponList']
        for launcher_num in xrange(UI.GetLauncherCount()):
            weap_name = UI.GetLauncherWeaponName(launcher_num)
            launcher = UI.GetLauncherInfo(launcher_num)
            loaded_qty = launcher.Quantity
            load_qty = UI.GetLauncherQuantity(launcher_num)
            if weap_name in Loaded_List:
                Loaded_List[weap_name][0] = Loaded_List[weap_name][0] + loaded_qty
                Loaded_List[weap_name][1] = Loaded_List[weap_name][1] + load_qty
            else:
                Loaded_List[weap_name] = [loaded_qty, load_qty]
            for weapon in xrange(UI.GetLauncherTypesCount(launcher_num)):
                stored_weap_name = UI.GetLauncherTypeName(launcher_num, weapon)
                mag_qty = UI.GetMagazineQuantity(stored_weap_name)
                if stored_weap_name in Potential_Load_List:
                    Potential_Load_List[stored_weap_name] = Potential_Load_List[stored_weap_name] + mag_qty
                else:
                    Potential_Load_List[stored_weap_name] = mag_qty
        Selected['WeaponList'] = Loaded_List
        Selected['MagWeaponList'] = Potential_Load_List
    if UI.HasThrottle():
        Selected['HasThrottle'] = 1
    if HasIronBombs(UI):
        Selected['HasBombs'] = 1
    task_list = UI.GetTaskList()
    if (task_list.Size() > 0):
        for task in xrange(task_list.Size()):
            task_name = task_list.GetString(task)
            if task_name in Selected['Tasks']:
                Selected['Tasks'][task_name] = Selected['Tasks'][task_name] + 1
            else:
                Selected['Tasks'][task_name] = 1
    for sensor_num in xrange(UI.GetSensorCount()):
        sensor = UI.GetSensorInfo(sensor_num)
        if sensor.type == 1:
            Selected['HasRadar'] = 1
        elif sensor.type == 2:    
            Selected['HasESM'] = 1
        elif sensor.type == 4:    
            Selected['HasSonarP'] = 1
        elif sensor.type == 8:    
            Selected['HasSonarA'] = 1
        elif sensor.type == 16:    
            Selected['HasOptical'] = 1
        elif sensor.type == 32:
            Selected['HasECM'] = 1
    if UI.IsInFormation() or UI.IsFormationLeader():
        if UI.IsFormationLeader():
            Selected['FormLeader'] += 1
        else:
            Selected['FormMember'] += 1
            if UI.GetFormationMode() == 1:
                Selected['FormModePace'] += 1
            else:
                Selected['FormModeSprint'] += 1
    Selected['UnitCount'] = Selected['UnitCount']+1
    return Selected

def DateString_DecimalYear(string):
    #string formatted as YYYY/MM/DD HH:MM:SS
    import re
    date_time = re.split('\D+', string)
    #convert the date into a decimal year:
    import datetime
    date = datetime.datetime(int(date_time[0]),int(date_time[1]),int(date_time[2]),int(date_time[3]),int(date_time[4]),int(date_time[5]))
    dec_date = (float(date.strftime("%j"))-1) / 366 + float(date.strftime("%Y"))
    return dec_date
    
def Get_Relevant_Stock(UI, loadouts_dict):
    #do we have children?
    children = 0
    if UI.HasFlightPort():
        FP = UI.GetFlightPortInfo()
        if FP.GetUnitCount() > 0:
            children = 1
    #find all stocks for children
    child_stocks = {}
    done_list = []
    if children:
        for n in xrange(FP.GetUnitCount()):
            UIn = FP.GetUnitPlatformInterface(n)
            if UIn.GetClass() not in done_list:
                done = False
                for armament in loadouts_dict:
                    if UIn.GetClass() in loadouts_dict[armament]:
                        keys = sorted(loadouts_dict[armament][UIn.GetClass()].iterkeys())
                        for loadout in keys:
                            for item in loadouts_dict[armament][UIn.GetClass()][loadout]:
                                if UI.CanMagazineAcceptItem(item):
                                    child_stocks[item] = None
                    done = True
                    done_list.append(UIn.GetClass())
                if not done:
                    for L in xrange(UIn.GetLauncherCount()):
                        for x in xrange(UIn.GetLauncherTypesCount(L)):
                            item = UIn.GetLauncherTypeName(L, x)
                            if UI.CanMagazineAcceptItem(item):
                                child_stocks[item] = None
                    done_list.append(UIn.GetClass())
    #find all stocks for parent.
    parent_stocks = {}
    for L in xrange(UI.GetLauncherCount()):
        for x in xrange(UI.GetLauncherTypesCount(L)):
            item = UI.GetLauncherTypeName(L, x)
            if UI.CanMagazineAcceptItem(item):
                parent_stocks[item] = None

    classified = {'Parent':{}, 'Child':{}}
    categories = [['MIS', 'Missile'], ['ROC', 'Rocket'], ['GBU', 'Guided Bomb'], ['UBU', 'Unguided Bomb'], ['GUN', 'Gun Round'], ['TRP', 'Torpedo'], ['CM',  'Counter Measure'], ['UNK', 'Unknown Item Type'], ['NUC', 'Nuclear'], ['MIN', 'Mines'], ['FUEL', 'Fuel Tanks'], ['BUI', 'Sonobuoys']]
    for owner in classified:
        for category in categories:
            try:
                classified[owner][category[0]] = {}
            except KeyError:
                classified[owner] = {category[0]:{}}
    
    #classify the stocks now.  Begin with parent stocks.
    for stock in parent_stocks:
        done = False
        #just primary categories for now.
        if not done:
            if ('Nuclear' in UI.QueryDatabase('missile',stock,'DamageModel').GetString(0) or
               'Nuclear' in UI.QueryDatabase('ballistic',stock,'DamageModel').GetString(0) or
               'Nuclear' in UI.QueryDatabase('torpedo',stock,'DamageModel').GetString(0)):  #nuke
                classified['Parent']['NUC'][stock] = None
                done = True
        if not done:
            if UI.QueryDatabase('missile',stock,'ClassificationId').GetString(0) == '64':  #missile
                classified['Parent']['MIS'][stock] = None
                done = True
        if not done:
            if UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '1':  #unguided bomb
                classified['Parent']['UBU'][stock] = None
                done = True
            elif UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '3':  #guided bomb
                classified['Parent']['GBU'][stock] = None
                done = True
        if not done:
            if UI.QueryDatabase('torpedo',stock,'ClassificationId').GetString(0) == '130':  #torpedo
                classified['Parent']['TRP'][stock] = None
                done = True
            elif UI.QueryDatabase('torpedo',stock,'ClassificationId').GetString(0) == '138':  #mine
                classified['Parent']['MIN'][stock] = None
                done = True
        if not done:
            if (UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '0' or
            UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '2'):  #gun round, autocannon round
                classified['Parent']['GUN'][stock] = None
                done = True
        if not done:
            if (UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '4' or
                UI.QueryDatabase('cm',stock,'ClassificationId').GetString(0) == '36' or
                UI.QueryDatabase('cm',stock,'ClassificationId').GetString(0) == '136'):  #gun cm, air cm, water cm
                classified['Parent']['CM'][stock] = None
                done = True
        if not done:
            if UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '5':  #rockets
                classified['Parent']['ROC'][stock] = None
                done = True
        if not done:
            if UI.QueryDatabase('sonobuoy',stock,'ClassificationId').GetString(0) == '132':  #sonobuoy
                classified['Parent']['BUI'][stock] = None
                done = True
        if not done:
            classified['Parent']['UNK'][stock] = None
    if children:
        for stock in child_stocks:
            done = False
            #just primary categories for now.
            if not done:
                if ('Nuclear' in UI.QueryDatabase('missile',stock,'DamageModel').GetString(0) or
                   'Nuclear' in UI.QueryDatabase('ballistic',stock,'DamageModel').GetString(0) or
                   'Nuclear' in UI.QueryDatabase('torpedo',stock,'DamageModel').GetString(0)):  #nuke
                    classified['Child']['NUC'][stock] = None
                    done = True
            if not done:
                if UI.QueryDatabase('missile',stock,'ClassificationId').GetString(0) == '64':  #missile
                    classified['Child']['MIS'][stock] = None
                    done = True
            if not done:
                if UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '1':  #unguided bomb
                    classified['Child']['UBU'][stock] = None
                    done = True
                elif UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '3':  #guided bomb
                    classified['Child']['GBU'][stock] = None
                    done = True
            if not done:
                if UI.QueryDatabase('torpedo',stock,'ClassificationId').GetString(0) == '130':  #torpedo
                    classified['Parent']['TRP'][stock] = None
                    done = True
                elif UI.QueryDatabase('torpedo',stock,'ClassificationId').GetString(0) == '138':  #mine
                    classified['Parent']['MIN'][stock] = None
                    done = True
            if not done:
                if (UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '0' or
                UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '2'):  #gun round, autocannon round
                    classified['Child']['GUN'][stock] = None
                    done = True
            if not done:
                if (UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '4' or
                    UI.QueryDatabase('cm',stock,'ClassificationId').GetString(0) == '36' or
                    UI.QueryDatabase('cm',stock,'ClassificationId').GetString(0) == '136'):  #gun cm, air cm, water cm
                    classified['Child']['CM'][stock] = None
                    done = True
            if not done:
                if UI.QueryDatabase('ballistic',stock,'BallisticType').GetString(0) == '5':  #rockets
                    classified['Child']['ROC'][stock] = None
                    done = True
            if not done:
                if UI.QueryDatabase('sonobuoy',stock,'ClassificationId').GetString(0) == '132':  #sonobuoy
                    classified['Child']['BUI'][stock] = None
                    done = True
            if not done:
                classified['Child']['UNK'][stock] = None
    return classified                        

def ToggleFilterByYear(SM, state):
    try:
        SM.SetFilterByYear(state)
    except:
        #SM is probably UI...
        SM = SM.GetScenarioInterface()
        SM.SetFilterByYear(state)

def MenuLaunchCommand(interface, *args):
    #we do not know:
        #are we called by group or single unit
        #are we going to fire on a target, or a datum
        #the name of the weapon to be fired
    #lets find out...

    #target or datum?
    if len(args) == 2:
        #we were given a target to engage
        target_id = int(args[0])
        weapon_n = args[1]
        target = True
    elif len(args) == 3:
        #we are given a datum to engage
        Lon = args[0]
        Lat = args[1]
        Alt = -1
        weapon_n = args[2]
        target = False
    elif len(args) == 4:
        #we are given a datum to engage, includes altitude
        Lon = args[0]
        Lat = args[1]
        Alt = args[2]
        weapon_n = args[3]
        target = False

    #group or single?
    group = False
    try:
        #maybe we are a group
        test = interface.GetUnitCount()
        group = True
    except:
        #maybe we are not.
        group = False
        
    #get our weapon name back
    #load Selected from the first unit we can find the key saved to.
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            BB = UI.GetBlackboardInterface()
            Selected = Read_Message_Dict(BB, 'Selected')
            break
    else:
        UI = interface
        BB = UI.GetBlackboardInterface()
        Selected = Read_Message_Dict(BB, 'Selected')
    
    #now get the weapon name back.
    loaded_list = Selected['WeaponList']
    weapon_list = loaded_list.keys()
    weapon_list.sort()
    weapon_name = weapon_list[weapon_n]
    unit_count = Selected['UnitCount']
        
    #determine weapon name and perform engagement.
    if group:    
        #we have a group, treat this a bit different
        #try to get the weapon name back from Selected
        GI = interface
        #find closest unit
        friendly_range_list = []
        for unit in xrange(GI.GetUnitCount()):
            UI = GI.GetPlatformInterface(unit)
            if target:
                track = UI.GetTrackById(target_id)
                target_lon = track.Lon
                target_lat = track.Lat
                target_alt = track.Alt
            else:
                target_lon = Lon
                target_lat = Lat
                target_alt = UI.GetMapTerrainElevation(Lon, Lat)
            if target_alt < -400:
                target_alt = -400
            target_alt = target_alt * 0.001
            
            map_range = UI.GetRangeToDatum(Lon, Lat)
            true_range = sqrt(map_range**2 + target_alt**2)
            friendly_range_list.append([true_range, UI.GetPlatformId()])
        friendly_range_list.sort()
        
        #begin engagement
        for unit in friendly_range_list:
            for n in xrange(GI.GetUnitCount()):
                UI = GI.GetPlatformInterface(n)
                if UI.GetPlatformId() == unit[1]:
                    #we have the next unit in the sorted list
                    break
            want_shoot = False
            excuses = []
            name = UI.GetPlatformName()
            if Alt == -1:
                Alt = UI.GetMapTerrainElevation(Lon, Lat)+1
            for launcher_n in xrange(UI.GetLauncherCount()):
                if weapon_name == UI.GetLauncherWeaponName(launcher_n):
                    #then we have the chosen weapon, proceed to launch.
                    want_shoot = True
                    launcher = UI.GetLauncherInfo(launcher_n)
                    if target:
                        UI.SetTarget(target_id)
                        UI.HandoffTargetToLauncher(launcher_n)
                        launcher = UI.GetLauncherInfo(launcher_n)
                        status, excuse = Check_Status(UI, launcher, 1)
                        if status and Use_Launcher_On_Target_Amram(UI, launcher_n, -2, target_id):
                            UI.DisplayMessage('%s, %s' % (name,excuse))
                            return
                        else:
                            excuses.append(excuse)
                    else:
                        UI.SendDatumToLauncher(Lon, Lat, Alt, launcher_n)
                        launcher = UI.GetLauncherInfo(launcher_n)
                        status, excuse = Check_Status(UI, launcher, 1)
                        if status and Use_Launcher_On_Target_Amram(UI, launcher_n, -2, Lon, Lat):
                            UI.DisplayMessage('%s, %s' % (name,excuse))
                            return
                        else:
                            excuses.append(excuse)
            if want_shoot:
                UI.DisplayMessage('%s did not shoot, reasons:%s' % (name, excuses))
    else:
        #its just the one unit, proceed direct to launcher selection.
        #try to get the weapon name back from weapon_n
        UI = interface
        if Alt == -1:
            Alt = UI.GetMapTerrainElevation(Lon, Lat)+1
        excuses = []
        name = UI.GetPlatformName()
        #proceed to determining launcher to fire.
        for launcher_n in xrange(UI.GetLauncherCount()):
            if weapon_name == UI.GetLauncherWeaponName(launcher_n):
                #then we have the chosen weapon, proceed to launch.
                launcher = UI.GetLauncherInfo(launcher_n)
                #check basic status
                status, excuse = Check_Status(UI, launcher, 0)
                if status:
                    if target:
                        UI.SetTarget(targe_idD)
                        UI.HandoffTargetToLauncher(launcher_n)
                        launcher = UI.GetLauncherInfo(launcher_n)
                        #recheck status after assigning launcher.
                        status, excuse = Check_Status(UI, launcher, 1)
                        if status and Use_Launcher_On_Target_Amram(UI, launcher_n, -2, target_id):
                            UI.DisplayMessage('%s, %s' % (name,excuse))
                            return
                        else:
                            excuses.append(excuse)
                    else:
                        UI.SendDatumToLauncher(Lon, Lat, Alt, launcher_n)
                        launcher = UI.GetLauncherInfo(launcher_n)
                        status, excuse = Check_Status(UI, launcher, 1)
                        if status and Use_Launcher_On_Target_Amram(UI, launcher_n, -2, Lon, Lat):
                            UI.DisplayMessage('%s, %s' % (name,excuse))
                            return
                        else:
                            excuses.append(excuse)
                else:
                    excuses.append(excuse)
        UI.DisplayMessage('%s did not shoot, reasons:%s' % (name, excuses))
    return    
