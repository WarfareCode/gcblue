from random import *
from math import *

deg_to_rad = 0.01745329252
rad_to_deg = 57.2957795131
            
def EquipLoadout(UI, loadout):
    UI.EquipLoadout(loadout)

def AutoConfigurePlatform(UI, setupName):
    UI.AutoConfigurePlatform(setupName)
            
def MovePlatform(UI, lon, lat):
    UI.MovePlatform(lon, lat)

def split_multi(s, separators):
    rr = [s]
    for sep in separators:
        s, rr = rr, []
        for seq in s:
            rr += seq.split(sep)
    return rr    
    
def MovePlatformString(UI, s):
    s = s.replace('W','-')
    s = s.replace('S','-')
    s = s.replace('E',' ')
    s = s.replace('N',' ')
    
    svect = split_multi(s, [' ',',','\'',':'])
    sfilt = []
    for k in range(0, len(svect)):
        try:
            x = float(svect[k])
            sfilt.append(x)
        except:
            pass # do nothing and skip
    if (len(sfilt) == 2): # lat DD.DDD lon DD.DDD
        lat = sfilt[0]
        lon = sfilt[1]
    elif (len(sfilt) == 4): # lat DD MM.MMM lon DD MM.MMM
        if (sfilt[0] < 0):
            lat_sign = -1
        else:
            lat_sign = 1
        lat = sfilt[0] + 0.0166666667*lat_sign*sfilt[1]
        if (sfilt[2] < 0):
            lon_sign = -1
        else:
            lon_sign = 1
        lon = sfilt[2] + 0.0166666667*lon_sign*sfilt[3]
    elif (len(sfilt) == 6): # lat DD MM SS.SSS lon DD MM SS.SSS
        if (sfilt[0] < 0):
            lat_sign = -1
        else:
            lat_sign = 1
        lat = sfilt[0] + 0.0166666667*lat_sign*sfilt[1] + 0.000277777778*lat_sign*sfilt[2]
        if (sfilt[3] < 0):
            lon_sign = -1
        else:
            lon_sign = 1        
        lon = sfilt[3] + 0.0166666667*lon_sign*sfilt[4] + 0.000277777778*lon_sign*sfilt[5]
    else:
        UI.DisplayMessage('Bad coordinate string (%s)' % s)
    if ((lat > 90) or (lat < -90) or (lon < -180.0) or (lon > 180.0)):
        UI.DisplayMessage('Bad coordinate (%.5f, %.5f)' % (lat, lon))
    else:
        UI.DisplayMessage('Moving to %.5f %.5f' % (lat, lon))
        UI.MovePlatform(deg_to_rad*lon, deg_to_rad*lat)
    
def MoveGroup(GI, lon, lat):
    unit_count = GI.GetUnitCount()
    if (unit_count < 1):
        return
    UI = GI.GetPlatformInterface(0)
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    dlon = lon-leader_track.Lon
    dlat = lat-leader_track.Lat
    for n in range(0, unit_count):
        UI = GI.GetPlatformInterface(n)
        track = UI.GetTrackById(UI.GetPlatformId())
        UI.MovePlatform(track.Lon+dlon, track.Lat+dlat)
        
def RotateGroup(GI, angle_rad):
    unit_count = GI.GetUnitCount()
    if (unit_count < 2):
        return

    # get centroid
    lat_cen = 0
    lon_cen = 0
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UI = GetPlatformOrWeaponInterface(GI, n)
        lat_cen = lat_cen + UI.GetLatitude()
        lon_cen = lon_cen + UI.GetLongitude() # won't work near 180E
    scale = 1.0 / float(unit_count)
    lat_cen = lat_cen * scale
    lon_cen = lon_cen * scale
    cos_latc = cos(lat_cen)
    inv_cos_latc = 1.0 / cos_latc
    
    for n in range(0, unit_count):
        UI = GetPlatformOrWeaponInterface(GI, n)
        lon_n = UI.GetLongitude()
        lat_n = UI.GetLatitude()
        dlon = lon_n - lon_cen
        dlat = lat_n - lat_cen
        rot_lon = lon_cen + dlon*cos(angle_rad) + inv_cos_latc*dlat*sin(angle_rad)
        rot_lat = lat_cen + dlat*cos(angle_rad) - cos_latc*dlon*sin(angle_rad)
        UI.MovePlatform(rot_lon, rot_lat)

def DeletePlatform(UI):
    UI.DeletePlatform()

def DeleteGroup(GI):
    names_to_delete = []
    UI_to_delete = [] # to work with both platform and weapon interface types
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UI = GetPlatformOrWeaponInterface(GI, n)
        names_to_delete.append(UI.GetPlatformName())
        UI_to_delete.append(UI)
    for n in range(0, len(names_to_delete)):
        UI = UI_to_delete[n]
        UI.DeletePlatform()

def RenamePlatform(UI, name):
    UI.RenamePlatform(name)
    
def SetAirGroupName(SM, name):
    SM.SetAirGroupName(name)
    
def SetAirGroupSize(SM, n):
    SM.SetAirGroupCount(int(n))   

def SetAirGroupNameUnit(UI, name):
    UI.SetAirGroupName(name)
    
def SetAirGroupSizeUnit(UI, n):
    UI.SetAirGroupCount(int(n))        

def SetMagazineAddCount(UI, n):
    UI.SetMagazineAddCount(int(n))

def AddItemToMagazine(UI, item):
    magazineAddCount = UI.GetMagazineAddCount()
    UI.AddItemToMagazine(item, magazineAddCount)

def SetSeaState(SM, sea_state):
    SM.SetSeaState(sea_state)
    
def SetSonarTemplate(SM, id):
    SM.SetSonarTemplate(id)    
    
def SetScenarioName(SM, name):
    SM.SetScenarioName(name)

def SetScenarioDescription(SM, description):
    SM.SetScenarioDescription(description)

def SetAllianceCountry(SM, name):
    user_alliance = SM.GetUserAlliance()
    SM.SetAllianceDefaultCountry(user_alliance, name)

# Imports briefing from file
def ImportBriefing(SM, filename):
    infile = open(filename, 'r')
    text = infile.read()
    infile.close()
    SM.SetSimpleBriefing(SM.GetUserAlliance(), text)

def SetBriefing(SM, text):
    SM.SetSimpleBriefing(SM.GetUserAlliance(), text)
    
def SetAllianceROE(SM, roeMode):
    # set all types to same level for backward compatibility
    SM.SetAllianceROE(SM.GetUserAlliance(), roeMode, roeMode, roeMode, roeMode)
    
def SetAllianceROEByType(SM, airMode, surfMode, subMode, landMode):
	SM.SetAllianceROE(SM.GetUserAlliance(), airMode, surfMode, subMode, landMode)

# Saves game to "Saved/<datetime string>.py"
def SaveGame(SM):
    SM.SaveGame('Saved')

# Switch user alliance to next alliance
# Assumes alliances range from 1 to 8
def ToggleAlliance(SM):
    user_alliance = SM.GetUserAlliance()
    for n in range(user_alliance+1, 8):
        if (SM.AllianceExists(n)):
            SM.SetUserAlliance(n)
            return
    
    SM.SetUserAlliance(1)

# Adds new platform at specified coordinates
def AddNewPlatform(SM, lon, lat, className):
    user_alliance = SM.GetUserAlliance()

    unit = SM.GetDefaultUnit()
    unit.className = className
    unit.unitName = SM.GetRandomPlatformName(className, 'Temp') # 'Temp %d' % int(1000*random()) # old code
    unit.SetPosition(rad_to_deg*lon, rad_to_deg*lat, 0)  # lon, lat, alt
    unit.heading = 90
    unit.speed = 3
    SM.AddUnitToAlliance(unit, user_alliance)

# Adds copy of platform at specified coordinates
def CopyPlatform(UI_ref, lon, lat):
    refName = UI_ref.GetPlatformName()
    SM = UI_ref.GetScenarioInterface()

    unit = SM.GetDefaultUnit()
    unit.className = UI_ref.GetPlatformClass()
    unit.unitName = SM.GetRandomPlatformName(unit.className, refName) # 'Temp %d' % int(1000*random()) # old code
    unit.SetPosition(rad_to_deg*lon, rad_to_deg*lat, UI_ref.GetAltitude())  # lon, lat, alt
    unit.heading = UI_ref.GetHeading() # deg
    unit.speed = UI_ref.GetSpeed() # kts
    
    try:
        unit.throttle = UI_ref.GetThrottle()
    except:
        pass
        
    
    alliance = UI_ref.GetPlatformAlliance()
    SM.AddUnitToAlliance(unit, alliance)
    
    # duplicate loadout
    try:
        nLaunchers = UI_ref.GetLauncherCount()
        for n in range(0, nLaunchers):
            SM.SetUnitLauncherItem(unit.unitName, n, UI_ref.GetLauncherWeaponName(n), UI_ref.GetLauncherQuantity(n))
        
        # duplicate magazine items
        magItems = UI_ref.GetMagazineItems()
        nItems = magItems.Size()
        for n in range(0, nItems):
            itemName = magItems.GetString(n)
            qty = UI_ref.GetMagazineQuantity(itemName)
            SM.AddToUnitMagazine(unit.unitName, itemName, qty)
            
        SM.DuplicateUnitTasking(refName, unit.unitName)
    except:
        pass

# returns platform or weapon interface based on type of unit n in group
def GetPlatformOrWeaponInterface(GI, n):
    if (GI.IsPlatform(n)):
        return GI.GetPlatformInterface(n)
    else: # assume weapon type
        return GI.GetWeaponInterface(n)
    
# Adds copy of group at specified coordinates
def CopyGroup(GI, lon, lat):
    # get centroid
    lat_cen = 0
    lon_cen = 0
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UI = GetPlatformOrWeaponInterface(GI, n)
        lat_cen = lat_cen + UI.GetLatitude()
        lon_cen = lon_cen + UI.GetLongitude() # won't work near 180E
    scale = 1.0 / float(unit_count)
    lat_cen = lat_cen * scale
    lon_cen = lon_cen * scale
    
    for n in range(0, unit_count):
        UI = GetPlatformOrWeaponInterface(GI, n)
        CopyPlatform(UI, lon+UI.GetLongitude()-lon_cen, lat+UI.GetLatitude()-lat_cen)

# changes root name of group and renumbers starting with 1
def RenameGroup(GI, new_root):
    SM = GI.GetScenarioInterface()
    SM.ConsoleText('Rename Group Called')
    parsed = SM.GetParsedUnitName(new_root)
    if (parsed.isValid):
        start_id = parsed.id
        root = parsed.root
        separator = parsed.separator
    else:
        start_id = 1
        root = new_root
        separator = '-'
    
    # increment start id until non-existing unit is found
    searching = 1
    tries = 0
    while (searching and (tries < 100)):
        unitName = '%s%s%d' % (root, separator, start_id)
        if (SM.GetUnitIdByName(unitName) != -1):
            start_id = start_id + 1
            tries = tries + 1
        else:
            searching = 0
            
    SM.ConsoleText('Renaming group with root %s' % root)
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UI = GetPlatformOrWeaponInterface(GI, n)
        UI.RenamePlatform('%s%s%d' % (root, separator, start_id+n))
        
def AddNewPlatformToFlightDeck(SM, host_id, className):
    group_name = SM.GetAirGroupName()
    group_count = SM.GetAirGroupCount()
    start_id = SM.GetAirUnitId()
    
    for n in range(0, group_count):
        hostName = SM.GetUnitNameById(host_id)
        unitName = '%s-%d' % (group_name, start_id+n)
        UI = SM.GetUnitInterface()
        BB = UI.GetBlackboardInterface()
        if BB.KeyExists('MagTonnage'):
            BB.Erase('MagTonnage')
        
        SM.AddUnitToFlightDeck(hostName, className, unitName, 3)

# version for edit mode with platform hooked
# adds group according to current group count, automatically names based on current group name
def AddToMyFlightDeck(UI, className):
    UI.AddUnitToFlightDeck(className)

def AddMapLabel(SM, lon, lat, labelText):
    SM.OverlayText(labelText, rad_to_deg*lon, rad_to_deg*lat)

def DeleteGoal(SM, goal_id):
    SM.DeleteGoalById(goal_id)    

def ChangeGoalTarget(SM, target_id, goal_id):
    goal = SM.GetGoalById(goal_id)
    unit_name = SM.GetUnitNameById(target_id)
    if (len(unit_name) < 1):
        return
    if (goal.GetTypeString() == 'Destroy'):
        destroy_goal = goal.AsDestroyGoal()
        destroy_goal.SetTargetString(unit_name)
    elif (goal.GetTypeString() == 'Protect'):
        protect_goal = goal.AsProtectGoal()
        protect_goal.SetTargetString(unit_name)

def AddCompoundGoal(SM, goal_id):
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Compound'):
        return
    compound_goal = goal.AsCompoundGoal()
    new_goal = SM.CompoundGoal(0)
    compound_goal.AddGoal(new_goal)

def AddTimeGoal(SM, goal_id):
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Compound'):
        return
    compound_goal = goal.AsCompoundGoal()
    new_goal = SM.TimeGoal()
    new_goal.SetFailTimeout(3600.0)
    new_goal.SetPassTimeout(59940.0)
    compound_goal.AddGoal(new_goal)

def AddDestroyGoal(SM, target_id, goal_id):
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Compound'):
        return
    compound_goal = goal.AsCompoundGoal()
    
    unit_name = SM.GetUnitNameById(target_id)
    new_goal = SM.DestroyGoal(unit_name)
    compound_goal.AddGoal(new_goal)

def AddProtectGoal(SM, target_id, goal_id):
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Compound'):
        return
    compound_goal = goal.AsCompoundGoal()

    unit_name = SM.GetUnitNameById(target_id) 
    new_goal = SM.ProtectGoal(unit_name)
    compound_goal.AddGoal(new_goal)

def AddAreaGoal(SM, lon, lat, goal_id):
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Compound'):
        return
    compound_goal = goal.AsCompoundGoal()

    new_goal = SM.AreaGoal()
    new_goal.AddPoint(lon + 0.001, lat + 0.001)
    new_goal.AddPoint(lon + 0.001, lat - 0.001)
    new_goal.AddPoint(lon - 0.001, lat - 0.001)
    new_goal.AddPoint(lon - 0.001, lat + 0.001)
    compound_goal.AddGoal(new_goal)
    
# versions that add as top level alliance goal
def AddCompoundGoalAlliance(SM, alliance):
    new_goal = SM.CompoundGoal(0)
    SM.SetAllianceGoal(alliance, new_goal)

def AddTimeGoalAlliance(SM, alliance):
    new_goal = SM.TimeGoal()
    new_goal.SetFailTimeout(3600.0)
    new_goal.SetPassTimeout(59940.0)
    SM.SetAllianceGoal(alliance, new_goal)

def AddDestroyGoalAlliance(SM, alliance):
    new_goal = SM.DestroyGoal('')
    SM.SetAllianceGoal(alliance, new_goal)

def AddProtectGoalAlliance(SM, alliance):
    new_goal = SM.ProtectGoal('')
    SM.SetAllianceGoal(alliance, new_goal)
    
def AddAreaGoalAlliance(SM, lon, lat, alliance):
    new_goal = SM.AreaGoal()
    new_goal.AddPoint(lon + 0.001, lat + 0.001)
    new_goal.AddPoint(lon + 0.001, lat - 0.001)
    new_goal.AddPoint(lon - 0.001, lat - 0.001)
    new_goal.AddPoint(lon - 0.001, lat + 0.001)

    SM.SetAllianceGoal(alliance, new_goal)    

def ChangePassTime(SM, time_minutes, goal_id):
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Time'):
        return
    time_goal = goal.AsTimeGoal()
    time_goal.SetPassTimeout(60.0*float(time_minutes))
    time_goal.SetFailTimeout(31556926.0)

def ChangeFailTime(SM, time_minutes, goal_id):
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Time'):
        return
    time_goal = goal.AsTimeGoal()
    time_goal.SetFailTimeout(60.0*float(time_minutes))
    time_goal.SetPassTimeout(31556926.0)

# toggle compound goal between OR and AND type
def ToggleCompoundType(SM, goal_id):
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Compound'):
        return
    compound_goal = goal.AsCompoundGoal()
    if (compound_goal.GetLogicType() == 0):
        compound_goal.SetLogicType(1)
    else:
        compound_goal.SetLogicType(0)

# param_str, first char is 0 or 1 for type, remaining is goal_id
# set state of area goal, 1 is enter type, 0 is avoid type
def SetAreaEnter(SM, param_str):
    state = int(param_str[0])
    goal_id = int(param_str[1:])
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Area'):
        return
    area_goal = goal.AsAreaGoal()
    area_goal.SetEnterGoal(state)

# param_str, first char is 0 or 1 for logic type, remaining is goal_id
# set state of area goal, 1 is ANY logic, 0 is ALL logic
def SetAreaLogic(SM, param_str):
    state = int(param_str[0])
    goal_id = int(param_str[1:])
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Area'):
        return
    area_goal = goal.AsAreaGoal()
    area_goal.SetLogicAny(state)    
    
# adds an additional named platform as 'target' for area goal
def AddAreaTarget(SM, target_id, goal_id):
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Area'):
        return
    area_goal = goal.AsAreaGoal()
    unit_name = SM.GetUnitNameById(target_id)
    if (len(unit_name) > 1):
        area_goal.AddToTargetList(unit_name)
    
# first 4 characters of string are goal id, remaining characters are  target type string
def SetAreaTargets(SM, param_str):
    goal_id = int(param_str[0:4])
    target_string = param_str[4:]
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Area'):
        return
    area_goal = goal.AsAreaGoal()
    area_goal.SetTargetList(target_string)
    
def SetAreaTimeDelay(SM, timeDelayMinutesString, goal_id):
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() != 'Area'):
        return
    area_goal = goal.AsAreaGoal()
    timeObjective_s = 60.0 * float(timeDelayMinutesString)
    area_goal.SetTimeObjective(timeObjective_s)

def AddGoalTarget(SM, target_id, goal_id):
    targetName = SM.GetUnitNameById(target_id)
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() == 'Destroy'):
        goal = goal.AsDestroyGoal()
    elif (goal.GetTypeString() == 'Protect'):
        goal = goal.AsProtectGoal()
    else:
        return
    if (len(targetName) == 0):
        return
    goal.AddTarget(targetName)

def AddGoalTargetArea(SM, lon1, lat1, lon2, lat2, goal_id):
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() == 'Destroy'):
        goal = goal.AsDestroyGoal()
    elif (goal.GetTypeString() == 'Protect'):
        goal = goal.AsProtectGoal()
    else:
        return
    unitList = SM.GetUnitList(lon1, lat1, lon2, lat2, -1)
    nUnits = unitList.Size()
    for n in range(0, nUnits):
        targetName = unitList.GetString(n)
        goal.AddTarget(targetName)
    
def RemoveGoalTarget(SM, param_str):
    goal_id = int(param_str[0:8])
    targetName = param_str[8:]
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() == 'Destroy'):
        goal = goal.AsDestroyGoal()
    elif (goal.GetTypeString() == 'Protect'):
        goal = goal.AsProtectGoal()
    else:
        return
    goal.RemoveTarget(targetName)
       
def SetGoalQuantity(SM, param_str):
    goal_id = int(param_str[0:8])
    quantity = int(param_str[8:])
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() == 'Destroy'):
        goal = goal.AsDestroyGoal()
    elif (goal.GetTypeString() == 'Protect'):
        goal = goal.AsProtectGoal()
    elif (goal.GetTypeString() == 'Area'):
        goal = goal.AsAreaGoal()        
    else:
        return
    goal.SetQuantity(quantity)
    
# version that takes input from user text box
def SetGoalQuantity2(SM, param_str, goal_id):
    quantity = int(param_str)
    goal = SM.GetGoalById(goal_id)
    if (goal.GetTypeString() == 'Destroy'):
        goal = goal.AsDestroyGoal()
    elif (goal.GetTypeString() == 'Protect'):
        goal = goal.AsProtectGoal()
    elif (goal.GetTypeString() == 'Area'):
        goal = goal.AsAreaGoal()
    else:
        return
    goal.SetQuantity(quantity)    
    
def SetIncludeProbability(UI, prob):
    UI.SetIncludeProbability(float(prob))

def AddRandomBox(UI):
    my_track = UI.GetTrackById(UI.GetPlatformId())
    lat_deg = 57.296*my_track.Lat
    lon_deg = 57.296*my_track.Lon
    UI.AddRandomBox(lon_deg+0.01, lon_deg+0.05, lat_deg-0.02, lat_deg+0.02)
    UI.UpdateMissionEditGraphics()   # avoid rehook to show box graphic     

def DeleteAllRandomBoxes(UI):
    UI.DeleteAllRandomBoxes()

def SetDateTimeString(SM, str):
    SM.SetDateTimeByString(str)

def SetAlwaysVisible(UI, state):
    UI.SetAlwaysVisible(state)
    
def SetAlliancePlayable(SM, state):
    current_side = SM.GetUserAlliance()
    SM.SetAlliancePlayable(current_side, state)

# set custom cost for this unit for scoring, string cost in millions
def SetCustomCost(UI, cost_million):
    try:
        x = 1e6 * float(cost_million)
        UI.SetCost(x)
        UI.DisplayMessage('Changed cost to %.1f M' % (1e-6 * x))
    except:
        UI.DisplayMessage('Error with cost string (%s)' % cost_million)

def SetFilterByYear(SM, state):
    SM.SetFilterByYear(state)
   
def SetFilterByCountry(SM, state):
    SM.SetFilterByCountry(state)
   
    