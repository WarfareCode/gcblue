import operator
from Amram_Menu import *
#from UnitCommands import *
#from HotKey import *
#from GroupCommands import *


# Updated with Ben "Mnfe" 20061217 post
def StocksBuildGroupMenu(GroupMenu, GroupInfo):
    GroupMenu.Clear()

    BuildAmramMenu(GroupMenu, GroupInfo)

    if (not IsGroupControlled(GroupInfo)):
        GroupMenu.AddItem('Take control of group', 'TakeControlGroup')
        return
    
    return
    
    unit_count = GroupInfo.GetUnitCount()
    if (unit_count <= 0):
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

    #GroupMenu.AddItem('Total units: %d' % unit_count, '')

    # display info if group consists only of aircraft/helo 
    if(air_count==unit_count and helo_count == 0):
        GroupMenu.AddItem('Air Group: %d units' % air_count,'')
    if(helo_count==unit_count):
        GroupMenu.AddItem('Helo Group: %d units' % helo_count,'')

    GroupMenu.AddItem('Navigate','')
    GroupMenu.BeginSubMenu()

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
    
    BuildGroupTargetMenu(GroupMenu, GroupInfo)
    
    BuildGroupLaunchMenu(GroupMenu, GroupInfo)
    
    # Group Sensor Settings
    GroupMenu.AddItem('Sensors','')
    GroupMenu.BeginSubMenu()
    GroupMenu.AddItem('Full Sensors','GroupAllSensors')
    GroupMenu.AddItem('Passive Sensors','GroupPassiveSensors')
    GroupMenu.AddItem('Offline','GroupOfflineSensors')
    GroupMenu.EndSubMenu()

    # aircraft/helo landing submenu, only if helo/air group
    if((air_count == unit_count and helo_count == 0)or(helo_count==unit_count)):
        BuildGroupFormationMenu(GroupMenu, GroupInfo)
        BuildGroupRefuelMenu(GroupMenu, GroupInfo)
        
        GroupMenu.AddItem('Land','')
        GroupMenu.BeginSubMenu()
        GroupMenu.AddItemUI('Land at selected','GroupAddLandingOrder','Target')
        GroupMenu.AddItem('Land at homebases','GroupAddLandingHBOrder')
        GroupMenu.EndSubMenu()
    
    # Group orders
    GroupMenu.AddItem('Tasks','')
    GroupMenu.BeginSubMenu()
    GroupMenu.AddItem('Engage all','AddEngageAllOrderGroup')
    GroupMenu.AddItem('Zig-zag patrol','AddPatrolOrderGroup')
    GroupMenu.AddItemUI('Add waypoint', 'AddWaypointOrderGroup', 'Datum')
    GroupMenu.AddItem('Clear all tasks','ClearTasksGroup')
    GroupMenu.EndSubMenu()
    
    UI = GroupInfo.GetPlatformInterface(0)
    if (UI.IsMultiplayerActive()):
        GroupMenu.AddItem('Release control of group', 'ReleaseControlGroup')

# should be called only if this group is all fixed-wing aircraft or all helo (not mixed)
def BuildGroupFormationMenu(GroupMenu, GroupInfo):
    GroupMenu.AddItem('Form on','')
    GroupMenu.BeginSubMenu()
    unit_count = GroupInfo.GetUnitCount()
    for k in range(0, unit_count):
        UI = GroupInfo.GetPlatformInterface(k)
        platform_name = UI.GetName()
        GroupMenu.AddItemWithTextParam('%s' % platform_name, 'GroupFormOn', platform_name)
    GroupMenu.EndSubMenu()
    
    
# should be called only if this group is all aircraft, adds menu if there's a tanker in the group
def BuildGroupRefuelMenu(GroupMenu, GroupInfo):
    tanker_list = GroupInfo.GetTankerList()
    nTankers = tanker_list.Size()
    if (nTankers == 0):
        return
        
    GroupMenu.AddItem('Refuel all','')
    GroupMenu.BeginSubMenu()
    for k in range(0, nTankers):
        tanker_name = tanker_list.GetString(k)
        GroupMenu.AddItemWithTextParam('%s' % tanker_name, 'GroupRefuelOn', tanker_name)
    GroupMenu.EndSubMenu()    
    
def BuildGroupLaunchMenu(GroupMenu, GroupInfo):
    unit_count = GroupInfo.GetUnitCount()
    if (unit_count <= 0):
        return
        
    weap_list = []
    
    for k in range(0, unit_count):
        UI = GroupInfo.GetPlatformInterface(k)
        nCount = UI.GetLauncherCount()
        for n in range(0, nCount):
            if (UI.IsDatumLaunch(n)): 
                weap_name = UI.GetLauncherWeaponName(n)
                weap_qty = UI.GetLauncherQuantity(n)
                weap_list.append([weap_name, weap_qty])
                
    weap_list = sorted(weap_list, key=operator.itemgetter(0))
    nWeap = len(weap_list)
    if (nWeap <= 0):
        return
    
    merged_list = []
    merged_list.append(weap_list[0])

    merge_idx = 0
    for k in range(1, nWeap):
        if (weap_list[k][0] == merged_list[merge_idx][0]):
            merged_list[merge_idx][1] = merged_list[merge_idx][1] + weap_list[k][1] # accumulate quantity
        else:
            merge_idx = merge_idx + 1
            merged_list.append(weap_list[k])
            
        
    GroupMenu.AddItem('Engage datum with','')
    GroupMenu.BeginSubMenu()
    for k in range(0, len(merged_list)):
        GroupMenu.AddItemUIWithTextParam('%s [%d]' % (merged_list[k][0], merged_list[k][1]), 'LaunchDatumGroup', 'Datum', merged_list[k][0])
    

    GroupMenu.EndSubMenu()      


def BuildGroupTargetMenu(GroupMenu, GroupInfo):
    anyTargets = 0
    unit_count = GroupInfo.GetUnitCount()
    for n in range(0,unit_count):
        UI = GroupInfo.GetPlatformInterface(n)
        if (UI.GetTarget() != -1):
            anyTargets = 1
        
    GroupMenu.AddItem('Target','')
    GroupMenu.BeginSubMenu()
    GroupMenu.AddItemUI('Select','SelectTargetGroup','Target')
    GroupMenu.AddItem('Clear','ClearTargetGroup')
    
    if (anyTargets != 0):
        GroupMenu.AddItem('Attack', 'AttackTargetGroup')
    GroupMenu.EndSubMenu()
    
    
