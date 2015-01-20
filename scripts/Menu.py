#Amram Menu Items.
import sys, os, math, json, operator
from os.path import dirname, abspath, join, normpath, isfile
sys.path.append(abspath(join(dirname(__file__), 'Amram_Script_Data', '..', 'log')))
sys.path.append(abspath(join(dirname(__file__), 'Magazine_Generator_Module')))
    #script data in, well, script data, '..' to gain access to logs, and logs to access the scenario report file.
from Amram_Utilities import *
from Amram_AI_Weapon_Lists import *
from magazine_generator import *
from Alliances import *

#importing from stock
from DevMode import *
from MissionEditCommands import *
from UnitCommands import *
from Landing import *
from SecondaryHook import *


#the Menu files are superceded by this file, import them to use some stuff.
from StockEditMenu import *
from StockMenu import *

#scenario report log file path    
reportfile_path = 'log/scenario_script_report.txt'
#import hotshot, hotshot.stats
#import pstats


def BuildUnitEditMenu(UnitMenu, UnitInfo):
    UnitMenu.Clear()
    BuildAmramMenu(UnitMenu, UnitInfo, EditMode=True)
    #prof = hotshot.Profile("log/UnitEditMenu.prof")
    #prof.runcall(BuildAmramMenu, UnitMenu, UnitInfo, EditMode=True)
    #prof.close()
    
def BuildGroupEditMenu(GroupMenu, GroupInfo):
    GroupMenu.Clear()
    BuildAmramMenu(GroupMenu, GroupInfo, EditMode=True)
    #prof = hotshot.Profile("log/GroupEditMenu.prof")
    #prof.runcall(BuildAmramMenu, GroupMenu, GroupInfo, EditMode=True)
    #prof.close()

def BuildGroupMenu(GroupMenu, GroupInfo):
    GroupMenu.Clear()
    BuildAmramMenu(GroupMenu, GroupInfo)
    #prof = hotshot.Profile("log/GroupMenu.prof")
    #prof.runcall(BuildAmramMenu, GroupMenu, GroupInfo)
    #prof.close()
    
def BuildUnitMenu(UnitMenu, UnitInfo):
    UnitMenu.Clear()
    BuildAmramMenu(UnitMenu, UnitInfo)
    #prof = hotshot.Profile("log/UnitMenu.prof")
    #prof.runcall(BuildAmramMenu, UnitMenu, UnitInfo)
    #prof.close()

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
        
def Get_Alliance_Members(SM, side_name):
    current_year = DateString_DecimalYear(SM.GetScenarioDateAsString())
    members = []
    def iterate_snapshots(alliance):
        for dates in Alliance_List[alliance]:
            Start = Alliance_List[alliance][dates]['Start']
            Stop = Alliance_List[alliance][dates]['Stop']
            if Start < current_year < Stop:
                return dates
    
    def iterate_members(alliance, snapshot):
        for member in Alliance_List[alliance][snapshot]['Members']:
            if member in Alliance_List and member != alliance:
                #so we can use Germany as an alliance for east, and west combined with Germany.
                initial_snapshot = iterate_members(member, iterate_snapshots(member))
            else:
                if member in Aliases:
                    members.append(Aliases[member])
                else:
                    members.append(member)

    iterate_members(side_name, iterate_snapshots(side_name))
    return sorted(members)

def AmramCreateAllianceUnitMenu(Menu, SM):
    debug = open('log/names.txt','w')
    page_count = 25
    side_name = SM.GetAllianceCountry(SM.GetUserAlliance())
    country_filter = SM.GetFilterByCountry()
    categories = {'Surface':'Surface','Submarine':'Sub','Air Fixed Wing':'AirFW','Helo':'Helo','Land':'Land','Mine/Torpedo':'Mine'}
    category_list = ['Surface','Submarine','Air Fixed Wing','Helo','Land','Mine/Torpedo']
    alliance = False
    
    def ReturnUnitsListFromGetPlatformArray(platforms, filter):
        units = []
        for n in xrange(platforms.Size()):
            platform = platforms.GetString(n)
            if platform not in filter:
                units.append(platform)
        return tuple(units)

    def DoSubMenu(Units, country, category):
        nPlatforms = len(Units[country][category])
        if (nPlatforms > page_count):
            nSubmenus = nPlatforms/page_count + 1
            for sm in xrange(nSubmenus):
                Menu.AddItem('Page %d' % (sm+1),'')
                Menu.BeginSubMenu()
                nPlatformsPage = min(page_count, nPlatforms - sm*page_count)
                for n in xrange(nPlatformsPage):
                    className = Units[country][category][n+sm*page_count]
                    NatoName = SM.GetDisplayName(className)
                    if category in ['Surface', 'Submarine']:
                        qty = GetUnitQty(className)
                    else:
                        qty = ''
                    if SM.IsUsingNATONames() and ClassName != NatoName:
                        Menu.AddItemUIWithTextParam('%s%s (%s)' % (qty, className, NatoName), 'AddNewPlatform', 'Datum', className)
                    else:
                        Menu.AddItemUIWithTextParam('%s%s' % (qty, className), 'AddNewPlatform', 'Datum', className)
                Menu.EndSubMenu()
        else:
            for className in Units[country][category]:
                NatoName = SM.GetDisplayName(className)
                qty = GetUnitQty(className)
                if SM.IsUsingNATONames() and ClassName != NatoName:
                    Menu.AddItemUIWithTextParam('%s%s (%s)' % (qty, className, NatoName), 'AddNewPlatform', 'Datum', className)
                else:
                    Menu.AddItemUIWithTextParam('%s%s' % (qty, className), 'AddNewPlatform', 'Datum', className)
                    
    def GetUnitQty(unit_class):
        names_array = SM.QueryDatabase('platform_names',unit_class,'DateInService, DateOutService')
        if names_array.GetRow(0).GetString(0) == 'Error':
            return ''
        else:
            filter = SM.GetFilterByYear()
            if filter:
                current_year = DateString_DecimalYear(SM.GetScenarioDateAsString())
                names = 0
                for name in xrange(names_array.Size()):
                    try:
                        date1 = float(names_array.GetRow(name).GetString(0))
                        date2 = float(names_array.GetRow(name).GetString(1))
                    except ValueError:
                        #some units have notes instead, see burkes for example
                        date1 = 2999
                        date2 = 1000
                    if date1 <= current_year <= date2:
                        names += 1
                return '%s - ' % names
            else:
                return '%s - ' % names_array.Size()

    
    if side_name in Aliases:
        side_name = Aliases[side_name]

    #are we an alliance:
    if side_name in Alliance_List:
        alliance = True
        new_members = sorted(Get_Alliance_Members(SM, side_name))
        members = ['ThIsCoUnTrYdOeSnTeXiSt']
        for country in new_members:
            members.append(country)
    else:
        members = ['ThIsCoUnTrYdOeSnTeXiSt', side_name]

    unit_filter = []
    SM.SetFilterByCountry(1)
    units = {}
    for country in members:
        for category in category_list:
            SM.SetAllianceDefaultCountry(SM.GetUserAlliance(),country)
            platforms = SM.GetPlatformListByClass(categories[category])
            unit_list = ReturnUnitsListFromGetPlatformArray(platforms, unit_filter)
            if len(unit_list) > 0:
                for unit in unit_list:
                    unit_filter.append(unit)
                if country == 'ThIsCoUnTrYdOeSnTeXiSt':
                    try:
                        units['No Assigned Country'][category] = unit_list
                    except KeyError:
                        units['No Assigned Country'] = {category:unit_list}
                else:
                    try:
                        units[country][category] = unit_list
                    except KeyError:
                        units[country] = {category:unit_list}
    if not country_filter:
        for category in category_list:
            SM.SetAllianceDefaultCountry(SM.GetUserAlliance(),'ThIsCoUnTrYdOeSnTeXiSt')
            SM.SetFilterByCountry(0)
            platforms = SM.GetPlatformListByClass(categories[category])
            unit_list = ReturnUnitsListFromGetPlatformArray(platforms, unit_filter)
            if len(unit_list) > 0:
                try:
                    units['Unfiltered'][category] = unit_list
                except KeyError:
                    units['Unfiltered'] = {category:unit_list}
        
    SM.SetFilterByCountry(country_filter)
    SM.SetAllianceDefaultCountry(SM.GetUserAlliance(),side_name)

    #sort the country listing
    new_list = []
    filter = ['Unfiltered', 'No Assigned Country']
    country_list = sorted(units.keys())
    unfiltered = False
    unassigned = False
    for country in country_list:
        if country not in filter:
            new_list.append(country)
        else:
            if country == 'Unfiltered':
                unfiltered = True
            else:
                unassigned = True
    if unfiltered:
        new_list.append('Unfiltered')
    if unassigned:
        new_list.append('No Assigned Country')
    
    #begin alliance menu function.
    Menu.AddItem('Create unit','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
    for country in new_list:
        if len(units[country].keys()) > 0:
            if country != 'Unfiltered':
                Menu.AddItem('%s' % country,'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            else:
                Menu.AddItem('Other countries','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            for category in category_list:
                if category in units[country] and len(units[country][category]) > 0:
                    Menu.AddItem('%s' % category,'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
                    DoSubMenu(units, country, category)
                    Menu.EndSubMenu()
            Menu.EndSubMenu()
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
                        Menu.AddItemWithTextParam('Throttle %d%%' % show_throttle,  'OptionHandler', 'SetThrottle|Function|%f' % throttle_set)
                    if Selected['FixedWing'] > 0:
                        for throttle in range(6, 11):
                            throttle_set = throttle / 5.0
                            show_throttle = throttle_set * 100 - 100
                            Menu.AddItemWithTextParam('Throttle AB %d%%' % show_throttle,  'OptionHandler', 'SetThrottle|Function|%f' % throttle_set)
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

    if Selected['Ship'] > 0 or Selected['Air'] > 0 or Selected['Sub'] > 0 or Selected['MobileLand'] > 0 and Selected['Speed+'] > 0:
        Menu.AddItem('Waypoint Options','')
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
    TargetRestrictionsMenu(Menu, interface, Selected)
    if Selected['UnitCount'] > 1:
        group_string = ['Group ','s']
    else:
        group_string = ['','']
    Menu.AddItemUI('Set %s Target' % group_string[0],'OptionSetTargeting', 'Target')
    if Selected['TargetSet'] > 0:
        Menu.AddItemWithTextParam('Clear %sTarget%s' % (group_string[0], group_string[1]),'OptionHandler', 'Target|Function|-1')
    
    Menu.AddItem('Engage Target','');Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    if 1==1:
        #Menu.AddItem('Launch Weapon At Target', '');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        #if 1==1:
        #    loaded_list = Selected['WeaponList']
        #    weapon_list = loaded_list.keys()
        #    weapon_list.sort()
        #    for weapon_n in xrange(len(weapon_list)):
        #        if loaded_list[weapon_list[weapon_n]][0] > 0:
        #            Menu.AddItemUIWithParam('%s : %d' % (weapon_list[weapon_n], loaded_list[weapon_list[weapon_n]][0]), 'MenuLaunchCommand', 'Target', weapon_n)
        #    Menu.EndSubMenu()
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
            if Selected['HasGBU']:
                Menu.AddItemWithTextParam('Guided Bomb Target','OptionHandler', 'GBUBombRun|Task|Start~1~0')
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

def TargetRestrictionsMenu(Menu, interface, Selected):
    #toggles and limits on attacks.
    Menu.AddItem('Target Restrictions','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
    if 1==1:
        Menu.AddItem('Category Limits','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        if 1==1:
            engage_classes = [['Air',['All Air',32,1,4],['Fixed Wing',33,1,5],['Helo',34,1,6]],['Ground',['All Ground',256,2,9],['Ground Vehicle',258,2,10],['Airfield',257,24,11]],['Missile',['All Missile',64,1,7]],['Ship',['All Surface',16,4,0],['Small Surface',17,6,1],['Large Surface',18,12,2],['Carrier',22,24,3]],['Sub',['All Submarine',129,1,8]]]
            for cat in engage_classes:
                Menu.AddItem('%s' % cat[0],'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
                for subcat in cat:
                    if type(subcat) == type([]):
                        current_limit = Selected['%s_EngageLimit' % subcat[1]]
                        if current_limit == -1:
                            current_limit = subcat[2]
                        Menu.AddItem('%s limit  (%s)' % (subcat[0], current_limit),'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
                        if 1==1:
                            Menu.AddItemUIWithParam('Input Limit','CombatLimitsInputHandler','Text Please Enter New %s Engage Limit' % subcat[0],subcat[3])
                            Menu.AddItem('From List','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
                            if 1==1:
                                for n in [0,1,2,4,6,8,10,12,14,16,19,21,24,27,30,35,40,45,50]:
                                    if n == subcat[2]:
                                        tag = ' (default)'
                                    else:
                                        tag = ''
                                    Menu.AddItemWithTextParam('%d%s' % (n,tag),'OptionHandler', '%s_EngageLimit|Set|%s'% (subcat[1],n))
                                Menu.EndSubMenu()
                            Menu.EndSubMenu()
                Menu.EndSubMenu()
            Menu.AddItemWithTextParam('Reset Category Limits','DefaultCombatLimitInputs', 'EngageLimits')
            Menu.EndSubMenu()
            
        Menu.AddItem('ID Specific Limits','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        if 1==1:
            IDEngageLimitMenu(interface, Menu)
            Menu.EndSubMenu()
        
        if 1==1:
            EngagementZoneMenu(interface, Menu)
            Menu.EndSubMenu()
    Menu.EndSubMenu()

def IDEngageLimitMenu(interface, Menu):
    #compile a dict of entries, sorted by categories
    #dict>
    #   CATEGORY>
    #       CLASSIFICATION>
    #           ID>
    #               player unit : limit
    
    catids = {0:['Undetected','Not Known'],32:['Air','All Air'],33:['Air','Fixed Wing'],34:['Air','Helo'],256:['Ground','All Ground'],257:['Ground','Airfield'],258:['Ground','Ground Vehicle'],64:['Missile','All Missile'],16:['Ship','All Surface'],17:['Ship','Small Surface'],18:['Ship','Large Surface'],22:['Ship','Carrier'],129:['Sub','All Submarine']}
    newIDdict = {}
    def newdict(newIDdict, id):
        track = UI.GetTrackById(int(float(id)))
        classid = track.Classification
        cats = catids[classid]
        try:
            newIDdict[cats[0]][cats[1]][id][UI.GetPlatformName()] = idlimits[id]
        except KeyError:
            try:
                newIDdict[cats[0]][cats[1]][id] = {UI.GetPlatformName():idlimits[id]}
            except KeyError:
                if cats[0] in newIDdict:
                    newIDdict[cats[0]][cats[1]] = {id:{UI.GetPlatformName():idlimits[id]}}
                else:
                    newIDdict[cats[0]] = {cats[1]:{id:{UI.GetPlatformName():idlimits[id]}}}
        return newIDdict
    
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
    if group:
        GI = interface
        for n in xrange(GI.GetUnitCount()):
            UI = GI.GetPlatformInterface(n)
            BB = UI.GetBlackboardInterface()
            idlimits = Read_Message_Dict(BB,'ID_EngageLimit')
            for id in idlimits.keys():
                newIDdict = newdict(newIDdict, id)
    else:
        UI = interface
        BB = UI.GetBlackboardInterface()
        idlimits = Read_Message_Dict(BB,'ID_EngageLimit')
        for id in idlimits.keys():
            newIDdict = newdict(newIDdict, id)

    #set new limits per id.
    targetready = True
    commonid = None
    if group:
        tag = 'common '
        param = 12
        GI = interface
        for n in xrange(GI.GetUnitCount()):
            UI = GI.GetPlatformInterface(n)
            target = UI.GetTarget()
            if target == -1:
                targetready = False
                break
            elif commonid != None and commonid != target:
                targetready = False
                break
            elif commonid == None:
                commonid = target
    else:
        tag = ''
        param = 13
        UI = interface
        target = UI.GetTarget()
        if target == -1:
            targetready = False
        else:
            commonid = target
            
    if not targetready:
        Menu.AddItemUI('Please Set a %sTarget' % tag,'OptionSetTargeting', 'Target')
    else:
        Menu.AddItem('Set Limit for < %s >' % target,'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
        if 1==1:
            Menu.AddItemUIWithParam('Input Limit','CombatLimitsInputHandler','Text Please Enter New Engage Limit',param)
            Menu.AddItem('From List','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            if 1==1:
                for n in [0,1,2,4,6,8,10,12,14,16,19,21,24,27,30,35,40,45,50]:
                    Menu.AddItemWithTextParam('%d' % n,'OptionHandler', 'ID_EngageLimit|DictSet|%s~%s'% (target,n))
                Menu.EndSubMenu()
            Menu.EndSubMenu()
            
    #iterate over the dict keys and print the results to a menu entry.
    if len(newIDdict.keys()) > 0:
        Menu.AddItem('Current ID Limits','')
        for category in newIDdict:
            Menu.AddItem('%s' % category,'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            for classification in newIDdict[category]:
                Menu.AddItem('%s' % str(classification),'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
                for id in newIDdict[category][classification]:
                    Menu.AddItem('%s' % int(float(str(id))),'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
                    for platform in newIDdict[category][classification][id]:
                        Menu.AddItem('%s  =  %s' % (str(platform),str(newIDdict[category][classification][id][platform])),'')
                    Menu.EndSubMenu()
                Menu.EndSubMenu()
            Menu.EndSubMenu()
        Menu.AddItemWithTextParam('Reset ID Limits','DefaultCombatLimitInputs', 'IdLimits')
        
def EngagementZoneMenu(interface, Menu):
    Menu.AddItem('Engagement Zones','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
    Menu.AddItem('Create New Zone','');Menu.BeginSubMenu();Menu.SetStayOpen(1)
    Menu.AddItemUIWithParam('Inclusion Zone','CoOrdsEngageLimitHandler','Box',1)
    Menu.AddItemUIWithParam('Exclusion Zone','CoOrdsEngageLimitHandler','Box',2)
    Menu.EndSubMenu()
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
    new_zones = {}
    if group:
        GI = interface
        for n in xrange(GI.GetUnitCount()):
            UI = GI.GetPlatformInterface(n)
            BB = UI.GetBlackboardInterface()
            zones = Read_Message_Dict(BB,'Engagement_Zones')
            for ztype in zones:
                for zone in zones[ztype]:
                    try:
                        new_zones[ztype]['%0.2f_%0.2f_%0.2f_%0.2f'% (zones[ztype][zone][zone][0],zones[ztype][zone][1],zones[ztype][zone][2],zones[ztype][zone][3])] = UI.GetPlatformName()
                    except KeyError:
                        new_zones[ztype] = {'%0.2f_%0.2f_%0.2f_%0.2f'% (zones[ztype][zone][0],zones[ztype][zone][1],zones[ztype][zone][2],zones[ztype][zone][3]):UI.GetPlatformName()}
    else:
        UI = interface
        BB = UI.GetBlackboardInterface()
        zones = Read_Message_Dict(BB,'Engagement_Zones')
        for ztype in zones:
            for zone in zones[ztype]:
                try:
                    new_zones[ztype]['[%0.2f, %0.2f], [%0.2f, %0.2f]'% (math.degrees(zones[ztype][zone][0]),math.degrees(zones[ztype][zone][1]),math.degrees(zones[ztype][zone][2]),math.degrees(zones[ztype][zone][3]))] = {UI.GetPlatformName():''}
                except KeyError:
                    new_zones[ztype] = {'[%0.2f, %0.2f], [%0.2f, %0.2f]'% (math.degrees(zones[ztype][zone][0]),math.degrees(zones[ztype][zone][1]),math.degrees(zones[ztype][zone][2]),math.degrees(zones[ztype][zone][3])):{UI.GetPlatformName():''}}

    if len(new_zones.keys()) > 0:
        Menu.AddItem('Current Zones','')
        Menu.AddItem('=============','')
        for ztype in new_zones:
            Menu.AddItem('%s' % str(ztype),'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            for zone in new_zones[ztype]:
                Menu.AddItem('%s' % str(zone),'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
                for unit in new_zones[ztype][zone].keys():
                    Menu.AddItem('%s' % str(unit),'')
                Menu.EndSubMenu()
            Menu.EndSubMenu()
        Menu.AddItemWithTextParam('Clear Zones','DefaultCombatLimitInputs','Zones')

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
                            Menu.AddItemWithTextParam('%d - Load %s [%d]' % (n, type_name, reload_qty), 'ReloadLauncher', '%d~%s' % (n, type_name))
                else:
                    Menu.AddItemWithParam('%d - Cancel load %s' % (n, weap_name), 'Unload', n)
            else:
                if (not isLoadingUnloading):
                    if (UI.CanMagazineAcceptItem(weap_name)):
                        Menu.AddItemWithParam('%d - Unload %s' % (n,weap_name), 'Unload', n)
                    else:
                        Menu.AddItem('%d - Cannot Unload %s' % (n, weap_name), '')
                else:
                    Menu.AddItemWithTextParam('%d - Cancel unload %s' % (n, weap_name), 'ReloadLauncher', '%d~%s' % (n, weap_name))
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
            BuildRefuelMenu(Menu, interface)
            BuildLandMenu(Menu, interface)
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
        
    return get_loadouts(UI, aircraft_list, Filter, filter_list), aircraft_dict
    
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
        Menu.AddItem('Additive Loadout', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
        if BB.KeyExists('InvMulti'):
            InvMulti = Try_Read_Message(BB, 'InvMulti', 2)
        else:
            BB.Write('InvMulti', '1')
            InvMulti = 1
        Menu.AddItemUIWithParam('Inventory Multi: %s' % InvMulti, 'InputHandler', 'Text Inventory Miltiplier, may be less than one', 5)
    else:
        InvMulti = 1
        Menu.AddItem('Loadouts Menu', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    
    #Write_Message_List(BB, 'loadouts_dict', loadouts_dict)
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
                        if len(weapon) > 1:
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
    Menu.AddItem('Configure Unit', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
    if single:
        Menu.AddItemUI('Duplicate', 'CopyPlatform', 'Datum')
        Menu.AddItemUI('Move unit', 'MovePlatform', 'Datum')
        Menu.AddItemUI('Move unit to coordinate', 'MovePlatformString', 'Text Enter Latitude Longitude')
        BuildRenameMenu(Menu, UI)
        Menu.AddItemWithTextParam('Delete Unit', 'OptionHandler', 'DeleteUnit|Function|1')
        ParentConfigs(Menu, UI)
        
        if UI.HasMagazine():
            Menu.AddItem("Setup Generator",''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
            BB = UI.GetBlackboardInterface()
            if BB.KeyExists('MagGenAllowNukes'):
                Menu.AddItemWithTextParam('Nuclear Weapons Permitted','OptionHandler', 'MagGenAllowNukes|Erase|1')
            else:
                Menu.AddItemWithTextParam('Nuclear Weapons Not Permitted','OptionHandler', 'MagGenAllowNukes|Set|1')
            if UI.IsSurface() or UI.IsGroundVehicle() or (UI.IsFixed() and not UI.HasFlightPort()):
                Menu.AddItem('Autoconfigure Magazine and Launchers', 'MagGenerator')
            elif UI.HasFlightPort():
                #stock level is pointless if you don't, its based entirely on aircraft count...
                #intended specifically for airbases
                Menu.AddItem('===================================','')
                Menu.AddItemWithTextParam('Set Low Stock Level', 'OptionHandler', 'MagTonnage|Set|15')
                Menu.AddItemWithTextParam('Set Standard Stock Level', 'OptionHandler', 'MagTonnage|Set|25')
                Menu.AddItemWithTextParam('Set High Stock Level', 'OptionHandler', 'MagTonnage|Set|35')
                if BB.KeyExists('MagTonnage') or BB.KeyExists('MagItems'):
                    Menu.AddItem('Autoconfigure Magazine and Launchers', 'MagGenerator')
                else:
                    Menu.AddItem('Please set a maximum tonnage or maximum','')
                    Menu.AddItem('item count to enable the generator','')
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
                        Amram_Paged_Loadout_Menu(Menu, UI, loadouts_dict, aircraft_dict)
                        loadouts = True
                        break
                        break
        Menu.AddItem('Launchers', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
        for launcher_num in xrange(UI.GetLauncherCount()):
            Menu.AddItem('L%d' % (launcher_num+1), '')
            Menu.BeginSubMenu()
            Menu.AddItemWithParam('Unload', 'Unload', launcher_num)
            equipment = UI.GetCompatibleItemList(launcher_num)
            BuildPagedLoadoutMenu(Menu, equipment, 20, 'ReloadLauncher', '%d~' % launcher_num)
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
    Menu.AddItem('Add To Magazine', ''); Menu.BeginSubMenu(); Menu.SetStayOpen(1)
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
                'HasGBU':0,
                '16_EngageLimit':-1,
                '17_EngageLimit':-1,
                '18_EngageLimit':-1,
                '22_EngageLimit':-1,
                '32_EngageLimit':-1,
                '33_EngageLimit':-1,
                '34_EngageLimit':-1,
                '64_EngageLimit':-1,
                '129_EngageLimit':-1,
                '256_EngageLimit':-1,
                '258_EngageLimit':-1,
                '257_EngageLimit':-1,
                'Alliance0_EngageLimit':-1,
                'Alliance1_EngageLimit':-1,
                'Alliance2_EngageLimit':-1,
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
    if HasGBU(UI):
        Selected['HasGBU'] = 1
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
    for num in [16,17,18,22,32,33,34,64,129,256,258,257]:  #unit classification id's
        if BB.KeyExists('%s_EngageLimit' % num) and int(BB.ReadMessage('%s_EngageLimit' % num)) > int(Selected['%s_EngageLimit' % num]):
            Selected['%s_EngageLimit' % num] = BB.ReadMessage('%s_EngageLimit' % num)
        elif not BB.KeyExists('%s_EngageLimit' % num):
            limit = {32:1,33:1,34:1,256:2,258:2,257:24,64:1,16:4,17:6,18:12,22:24,129:1}
            BB.WriteGlobal('%s_EngageLimit' % num,'%s' % limit[num])
            Selected['%s_EngageLimit' % num] = limit[num]
        
    Selected['UnitCount'] = Selected['UnitCount']+1
    return Selected

#def Get_Relevant_Stock(UI, loadouts_dict):
#    prof = hotshot.Profile("log/GetRelevantStock.prof")
#    prof.runcall(Get_Relevant_Stock2, UI, loadouts_dict)
#    prof.close()    
    
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
        owner = 'Parent'
        #just primary categories for now.
        if not done:
            classification = UI.QueryDatabase('missile',stock,'ClassificationId').GetRow(0).GetString(0)
            if classification == '64':  #missile
                if 'Nuclear' in UI.QueryDatabase('missile',stock,'DamageModel').GetRow(0).GetString(0):
                    classified[owner]['NUC'][stock] = None
                else:
                    classified[owner]['MIS'][stock] = None
                done = True
        if not done:
            ballistic_type = UI.QueryDatabase('ballistic',stock,'BallisticType').GetRow(0).GetString(0)
            if ballistic_type != 'Error':
                if 'Nuclear' in UI.QueryDatabase('ballistic',stock,'DamageModel').GetRow(0).GetString(0):
                    classified[owner]['NUC'][stock] = None
                else:
                    if ballistic_type == '1':  #unguided bomb
                        classified[owner]['UBU'][stock] = None
                    elif ballistic_type == '3':  #guided bomb
                        classified[owner]['GBU'][stock] = None
                    elif ballistic_type == '0':  #Gun Round
                        classified[owner]['GUN'][stock] = None
                    elif ballistic_type == '2':  #Gun round
                        classified[owner]['GUN'][stock] = None
                    elif ballistic_type == '5':  #rockets
                        classified[owner]['ROC'][stock] = None
                    elif ballistic_type == '4':  #gun fired cm
                        classified[owner]['CM'][stock] = None
                done = True
        if not done:
            torpedo_type = UI.QueryDatabase('torpedo',stock,'ClassificationId').GetRow(0).GetString(0)
            if torpedo_type != 'Error':
                if 'Nuclear' in UI.QueryDatabase('torpedo',stock,'DamageModel').GetRow(0).GetString(0):
                    classified[owner]['NUC'][stock] = None
                else:
                    if torpedo_type == '130':  #torpedo
                        classified[owner]['TRP'][stock] = None
                    elif torpedo_type == '138':  #mine
                        classified[owner]['MIN'][stock] = None
                done = True
        if not done:
            if UI.QueryDatabase('sonobuoy',stock,'ClassificationId').GetRow(0).GetString(0) == '132':  #sonobuoy
                classified[owner]['BUI'][stock] = None
                done = True
        if not done:
            classification = UI.QueryDatabase('cm',stock,'ClassificationId').GetRow(0).GetString(0)
            if classification in  ['36', '136']:
                classified[owner]['CM'][stock] = None
                done = True
        if not done:
            classified[owner]['UNK'][stock] = None
    if children:
        for stock in child_stocks:
            done = False
            owner = 'Child'
            #just primary categories for now.
            if not done:
                classification = UI.QueryDatabase('missile',stock,'ClassificationId').GetRow(0).GetString(0)
                if classification == '64':  #missile
                    if 'Nuclear' in UI.QueryDatabase('missile',stock,'DamageModel').GetRow(0).GetString(0):
                        classified[owner]['NUC'][stock] = None
                    else:
                        classified[owner]['MIS'][stock] = None
                    done = True
            if not done:
                ballistic_type = UI.QueryDatabase('ballistic',stock,'BallisticType').GetRow(0).GetString(0)
                if ballistic_type != 'Error':
                    if 'Nuclear' in UI.QueryDatabase('ballistic',stock,'DamageModel').GetRow(0).GetString(0):
                        classified[owner]['NUC'][stock] = None
                    else:
                        if ballistic_type == '1':  #unguided bomb
                            classified[owner]['UBU'][stock] = None
                        elif ballistic_type == '3':  #guided bomb
                            classified[owner]['GBU'][stock] = None
                        elif ballistic_type == '0':  #Gun Round
                            classified[owner]['GUN'][stock] = None
                        elif ballistic_type == '2':  #Gun round
                            classified[owner]['GUN'][stock] = None
                        elif ballistic_type == '5':  #rockets
                            classified[owner]['ROC'][stock] = None
                        elif ballistic_type == '4':  #gun fired cm
                            classified[owner]['CM'][stock] = None
                    done = True
            if not done:
                torpedo_type = UI.QueryDatabase('torpedo',stock,'ClassificationId').GetRow(0).GetString(0)
                if torpedo_type != 'Error':
                    if 'Nuclear' in UI.QueryDatabase('torpedo',stock,'DamageModel').GetRow(0).GetString(0):
                        classified[owner]['NUC'][stock] = None
                    else:
                        if torpedo_type == '130':  #torpedo
                            classified[owner]['TRP'][stock] = None
                        elif torpedo_type == '138':  #mine
                            classified[owner]['MIN'][stock] = None
                    done = True
            if not done:
                if UI.QueryDatabase('sonobuoy',stock,'ClassificationId').GetRow(0).GetString(0) == '132':  #sonobuoy
                    classified[owner]['BUI'][stock] = None
                    done = True
            if not done:
                classification = UI.QueryDatabase('cm',stock,'ClassificationId').GetRow(0).GetString(0)
                if classification in  ['36', '136']:
                    classified[owner]['CM'][stock] = None
                    done = True
            if not done:
                classified[owner]['UNK'][stock] = None
    return classified                        

def ToggleFilterByYear(SM, state):
    try:
        SM.SetFilterByYear(state)
    except:
        #SM is probably UI...
        SM = SM.GetScenarioInterface()
        SM.SetFilterByYear(state)

def MenuLaunchCommand(interface, *args):
    #get our weapon name back
    #load Selected from the first unit we can find the key saved to.
    #group or single?
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
            BB = UI.GetBlackboardInterface()
            Selected = Read_Message_Dict(BB, 'Selected')
            break
    else:
        UI = interface
        BB = UI.GetBlackboardInterface()
        Selected = Read_Message_Dict(BB, 'Selected')    
    
    
    #target or datum?
    if len(args) == 2:
        #we were given a target to engage
        target_id = int(args[0])
        weapon_n = args[1]
        target = True
        track = UI.GetTrackById(target_id)
        Alt = track.Alt
        Lon = track.Lon
        Lat = track.Lat
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

    
    #now get the weapon name back.
    loaded_list = Selected['WeaponList']
    weapon_list = loaded_list.keys()
    weapon_list.sort()
    weapon_name = weapon_list[weapon_n]
    unit_count = Selected['UnitCount']
        
    def Execute_Launch_Target(UI, excuses, weapon_name, target_id):
        name = UI.GetPlatformName()
        want_shoot = False
        for launcher_n in xrange(UI.GetLauncherCount()):
            if weapon_name == UI.GetLauncherWeaponName(launcher_n):
                #then we have the chosen weapon, proceed to launch.
                want_shoot = True
                launcher = UI.GetLauncherInfo(launcher_n)
                UI.SetTarget(target_id)
                UI.HandoffTargetToLauncher(launcher_n)
                launcher = UI.GetLauncherInfo(launcher_n)
                status, excuse = Check_Status(UI, launcher, 1)
                if status and Use_Launcher_On_Target_Amram(UI, launcher_n, -2, target_id):
                    UI.DisplayMessage('%s, %s' % (name,excuse))
                    return want_shoot, excuses
                else:
                    excuses.append(excuse)
        return want_shoot, excuses
    def Execute_Launch_Datum(UI, excuses, Alt, Lon, Lat, weapon_name):
        name = UI.GetPlatformName()
        if Alt == -1:
            Alt = UI.GetMapTerrainElevation(Lon, Lat)+1
        want_shoot = False
        for launcher_n in xrange(UI.GetLauncherCount()):
            if weapon_name == UI.GetLauncherWeaponName(launcher_n):
                #then we have the chosen weapon, proceed to launch.
                want_shoot = True
                launcher = UI.GetLauncherInfo(launcher_n)
                UI.SendDatumToLauncher(Lon, Lat, Alt, launcher_n)
                launcher = UI.GetLauncherInfo(launcher_n)
                status, excuse = Check_Status(UI, launcher, 1)
                if status and Use_Launcher_On_Target_Amram(UI, launcher_n, -2, Lon, Lat):
                    UI.DisplayMessage('%s, %s' % (name,excuse))
                    return want_shoot, excuses
                else:
                    excuses.append(excuse)
        return want_shoot, excuses
        
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
            excuses = []
            if target:
                want_shoot, excuses = Execute_Launch_Target(UI, excuses, weapon_name, target_id)
            else:
                want_shoot, excuses = Execute_Launch_Datum(UI, excuses, Alt, Lon, Lat, weapon_name)
    else:
        #its just the one unit, proceed direct to launcher selection.
        #try to get the weapon name back from weapon_n
        UI = interface
        excuses = []
        name = UI.GetPlatformName()
        if target:
            want_shoot, excuses = Execute_Launch_Target(UI, excuses, weapon_name, target_id)
        else:
            want_shoot, excuses = Execute_Launch_Datum(UI, excuses, Alt, Lon, Lat, weapon_name)
    if want_shoot:
        UI.DisplayMessage('%s did not shoot, reasons:%s' % (name, excuses))    
        
def GetAllUnits(SM, date):
    #iterative climb through the entire run of id's from 0 through 1e6
    #repeated for all three alliances
    date = DateString_DecimalYear(date)
    
    Units = {}
    for id in xrange(1000):
        try:
            trackName = SM.GetUnitNameById(id)
            gotunit = True
        except:
            gotunit = False
        if gotunit:
            id = SM.GetUnitIdByName(trackName)
            UI = SM.GetUnitInterface(trackName)
            num = UI.GetPlatformAlliance()
            if id != -1:
                try:
                    Units[num][trackName] = id
                except KeyError:
                    Units[num] = {}
                    Units[num][trackName] = id
    
    problems = {}
    for alliance in Units:
        for track in Units[alliance]:
            UI = SM.GetUnitInterface(track)
            className = UI.GetPlatformClass()
            UnitName = UI.GetPlatformName()
            service = check_service(UI, className, date)
            if not service:
                #is this unit in service
                problems = recordprob(problems, alliance, 'Units', track, 'Unit Not in Service')
            if UI.GetLauncherCount() > 0:
                for lnum in xrange(UI.GetLauncherCount()):
                    weapon = UI.GetLauncherWeaponName(lnum)
                    if weapon != 'Empty':
                        service = check_service(UI, weapon, date)
                        if not service:
                            #are its loaded items in service?
                            problems = recordprob(problems, alliance, 'Launcher Items', weapon, track, 'Loaded Item not in service')
            if UI.HasFlightPort():
                FP = UI.GetFlightPortInfo()
                for n in xrange(FP.GetUnitCount()):
                    UIn = FP.GetUnitPlatformInterface(n)
                    childClass = UIn.GetPlatformClass()
                    childName = UIn.GetPlatformName()
                    service = check_service(UI, className, date)
                    if not service:
                        #are its landed child units in service?
                        problems = recordprob(problems, alliance, 'FlightPorts', UnitName, childClass, childName, 'Aircraft Not in service')
                    if UIn.GetLauncherCount() > 0:
                        for lnum in xrange(UIn.GetLauncherCount()):
                            weapon = UIn.GetLauncherWeaponName(lnum)
                            if weapon != 'Empty':
                                service = check_service(UI, weapon, date)
                                if not service:
                                    #are weapons loaded on its landed child aircraft in service?
                                    problems = recordprob(problems, alliance, 'Unit Armaments', UnitName, childClass, childName, weapon, 'Loaded Item Not in service')
            if UI.HasMagazine():
                items = UI.GetMagazineItems()
                for item_n in xrange(items.Size()):
                    item = items.GetString(item_n)
                    qty = UI.GetMagazineQuantity(item)
                    service = check_service(UI, item, date)
                    if not service:
                        #are weapons/items in the magazines in service?
                        problems = recordprob(problems, alliance, 'Magazine', UnitName, item, 'Supplied Item Not in service')
    if len(problems.keys()) == 0:
        problems  =  '\n'.join(('Nothing to Report.',
                                'Everything this script can currently',
                                'check appears to be acceptable.',
                                '===============================',
                                'All loaded/stocked weapons/items are',
                                'in service',
                                '===============================',
                                'All placed units, and child aircraft',
                                'are in service'
                                ))
    read_write_scenario_issue_reports(problems, 'WriteReport')
    UI.DisplayMessage('Scan Complete')

def recordprob(dd, *args):
    #handled up to 6 args, minimum 2.
    if len(args) == 2:
        arg0, arg1 = args
        dd[arg0] = arg1
    elif len(args) == 3:
        arg0, arg1, arg2 = args
        try:
            dd[arg0][arg1] = arg2
        except:
            dd[arg0] = {}
            dd[arg0][arg1] = arg2
    elif len(args) == 4:
        arg0, arg1, arg2, arg3 = args
        try:
            dd[arg0][arg1][arg2] = arg3
        except:
            try:
                dd[arg0][arg1] = {}
                dd[arg0][arg1][arg2] = arg3
            except:
                dd[arg0] = {}
                dd[arg0][arg1] = {}
                dd[arg0][arg1][arg2] = arg3
    elif len(args) == 5:
        arg0, arg1, arg2, arg3, arg4 = args
        try:
            dd[arg0][arg1][arg2][arg3] = arg4
        except:
            try:
                dd[arg0][arg1][arg2] = {}
                dd[arg0][arg1][arg2][arg3] = arg4
            except:
                try:
                    dd[arg0][arg1] = {}
                    dd[arg0][arg1][arg2] = {}
                    dd[arg0][arg1][arg2][arg3] = arg4
                except:
                    dd[arg0] = {}
                    dd[arg0][arg1] = {}
                    dd[arg0][arg1][arg2] = {}
                    dd[arg0][arg1][arg2][arg3] = arg4
    elif len(args) == 6:
        arg0, arg1, arg2, arg3, arg4, arg5 = args
        try:
            dd[arg0][arg1][arg2][arg3][arg4] = arg5
        except:
            try:
                dd[arg0][arg1][arg2][arg3] = {}
                dd[arg0][arg1][arg2][arg3][arg4] = arg5
            except:
                try:
                    dd[arg0][arg1][arg2] = {}
                    dd[arg0][arg1][arg2][arg3] = {}
                    dd[arg0][arg1][arg2][arg3][arg4] = arg5
                except:
                    try:
                        dd[arg0][arg1] = {}
                        dd[arg0][arg1][arg2] = {}
                        dd[arg0][arg1][arg2][arg3] = {}
                        dd[arg0][arg1][arg2][arg3][arg4] = arg5
                    except:
                        dd[arg0] = {}
                        dd[arg0][arg1] = {}
                        dd[arg0][arg1][arg2] = {}
                        dd[arg0][arg1][arg2][arg3] = {}
                        dd[arg0][arg1][arg2][arg3][arg4] = arg5
                            
    return dd
    
def traverse_dict_report(Menu, SM, problems):
    if type(problems) != type({}):
        Menu.AddItem('%s' % str(problems),'')
    else:
        for alliance in sorted(problems):
            Menu.AddItem('%s: %s' % (str(alliance), SM.GetAllianceCountry(int(alliance))),'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
            if type(problems[alliance]) == type({}):
                #go deeper:
                for sub1 in sorted(problems[alliance]):
                    if type(problems[alliance][sub1]) == type({}):
                        #go deeper
                        Menu.AddItem('%s' % str(sub1),'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
                        for sub2 in sorted(problems[alliance][sub1]):
                            if type(problems[alliance][sub1][sub2]) == type({}):
                                #go deeper:
                                Menu.AddItem('%s' % str(sub2),'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
                                for sub3 in sorted(problems[alliance][sub1][sub2]):
                                    if type(problems[alliance][sub1][sub2][sub3]) == type({}):
                                        #go deeper:
                                        Menu.AddItem('%s' % str(sub3),'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
                                        for sub4 in sorted(problems[alliance][sub1][sub2][sub3]):
                                            if type(problems[alliance][sub1][sub2][sub3][sub4]) == type({}):
                                                #go deeper:
                                                Menu.AddItem('%s' % str(sub4),'');Menu.BeginSubMenu();Menu.SetStayOpen(1)
                                                for sub5 in sorted(problems[alliance][sub1][sub2][sub3][sub4]):
                                                    Menu.AddItem('%s  Issue is  %s' % (str(sub5), str(problems[alliance][sub1][sub2][sub3][sub4][sub5])),'')
                                                Menu.EndSubMenu()
                                            else:
                                                Menu.AddItem('%s  Issue is  %s' % (str(sub4), str(problems[alliance][sub1][sub2][sub3][sub4])),'')
                                        Menu.EndSubMenu()
                                    else:
                                        Menu.AddItem('%s  Issue is  %s' % (str(sub3), str(problems[alliance][sub1][sub2][sub3])),'')
                                Menu.EndSubMenu()
                            else:
                                Menu.AddItem('%s  Issue is  %s' % (str(sub2), str(problems[alliance][sub1][sub2])),'')
                        Menu.EndSubMenu()
                    else:
                        Menu.AddItem('%s  Issue is  %s' % (str(sub1), str(problems[alliance][sub1])),'')
            else:
                Menu.AddItem('%s' % str(problems[alliance]),'')
            Menu.EndSubMenu()

def read_write_scenario_issue_reports(dd, param):
    if param == 'GetReport':
        #load up the report file, and provide the data to the player somehow.
        #
        #perhaps: if the file exists, read it in, and merge it with the menu automatically, with a disclaimer that the data was last generated on <recorded date/time>
        with open(reportfile_path, 'r') as logfile:
            return json.load(logfile)
    elif param == 'Delete' and isfile(reportfile_path):
        os.remove(reportfile_path)
    elif param == 'WriteReport':
        #take the provided dict file and write it down.
        with open(reportfile_path, 'w') as logfile:
            json.dump(dd, logfile, ensure_ascii=False, skipkeys=True, indent=2, sort_keys=True)
                    
def check_service(UI, className, date):
    if className == UI.GetPlatformClass():
        if UI.HasThrottle():
            tab = 'air'
        elif UI.IsSurface():
            tab = 'ship'
        elif UI.IsFixed() or UI.IsGroundVehicle():
            tab = 'ground'
        elif UI.IsSub():
            tab = 'sub'
        else:
            tab = 'simpleair'
        if not UI.IsGroundVehicle() or not UI.IsFixed() or not tab == 'ground':
            date1 = float(UI.QueryDatabase(tab ,className, 'InitialYear').GetRow(0).GetString(0))
            date2 = float(UI.QueryDatabase(tab ,className, 'FinalYear').GetRow(0).GetString(0))
            return date1 <= date <= date2
        else:
            return True
    else:
        country = ''
        if className == UI.GetPlatformClass():
            if UI.HasThrottle():
                tab = 'air'
            elif UI.IsSurface():
                tab = 'ship'
            elif UI.IsFixed() or UI.IsGroundVehicle():
                tab = 'ground'
            elif UI.IsSub():
                tab = 'sub'
            else:
                tab = 'simpleair'
        #if not UI.IsGroundVehicle() or not UI.IsFixed() or not tab == 'ground':
        if UI.IsSurface() or UI.IsFixed() and UI.HasFlightPort():
            try:
                country = UI.QueryDatabase(tab, className, 'Country').GetRow(0).GetString(0)
            except UnboundLocalError:
                if UI.IsSurface():
                    tab = 'ship'
                elif UI.IsFixed() or UI.IsGroundVehicle():
                    tab = 'ground'
                country = UI.QueryDatabase(tab, className, 'Country').GetRow(0).GetString(0)
        if country in servicekit:
            if className in servicekit[country]:
                date1 = servicekit[country][className]['Entry']
                date2 = servicekit[country][className]['Exit']
                return date1 <= date <= date2
            else:
                return False
        else:
            classified, tab = classify_item(UI, className)
            if classified:
                try:
                    date1 = float(UI.QueryDatabase(tab ,className, 'InitialYear').GetRow(0).GetString(0))
                    date2 = float(UI.QueryDatabase(tab ,className, 'FinalYear').GetRow(0).GetString(0))
                    return date1 <= date <= date2
                except:
                    UI.DisplayMessage('This Unit(%s : %s) failed to classify, please report this' % (UI.GetPlatformName(), className, ))
            else:
                return True

#def BuildEditMenu(UnitMenu, SM):                
#    prof = hotshot.Profile("log/EditMenu.prof")
#    prof.runcall(BuildEditMenu2, UnitMenu, SM)
#    prof.close()
     
def BuildEditMenu(UnitMenu, SM):
    UnitMenu.Clear()
    UnitMenu.AddItem('Scenario', '')
    UnitMenu.BeginSubMenu()
    #UnitMenu.AddItem('Save scenario', 'SaveGame')
    dt = SM.GetScenarioDateAsString()
    date_string = [dt[:4], dt[5:7],dt[8:10],dt[-6:-4],dt[-4:-2],dt[-2:]]
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

    AmramCreateAllianceUnitMenu(UnitMenu, SM)
    #BuildCreateUnitMenu(UnitMenu, SM)
    UnitMenu.AddItem('Scenario Report',''); UnitMenu.BeginSubMenu(); UnitMenu.SetStayOpen(1)
    UnitMenu.AddItemWithTextParam('Generate Scenario Issue Report','GetAllUnits', '%s/%s/%s' % (date_string[0],date_string[1],date_string[2]))
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

#       
#
#