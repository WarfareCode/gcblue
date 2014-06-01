
from UnitCommands import *
from Landing import *

deg_to_rad = 0.01745329252

 
    
def AddWaypointOrderGroup(GI, lon, lat):
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UnitInfo = GI.GetPlatformInterface(n)
        AddWaypointOrder(UnitInfo, lon, lat)

def AddPatrolOrderGroup(GI):
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UnitInfo = GI.GetPlatformInterface(n)
        AddPatrolOrder(UnitInfo)

def ClearTasksGroup(GI):
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UnitInfo = GI.GetPlatformInterface(n)
        ClearTasks(UnitInfo)

def GroupSpeed100(GI):
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UnitInfo = GI.GetPlatformInterface(n)
        Speed100(UnitInfo)     

def GroupSpeed80(GI):
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UnitInfo = GI.GetPlatformInterface(n)
        Speed80(UnitInfo)     

def GroupSpeed50(GI):
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UnitInfo = GI.GetPlatformInterface(n)
        Speed50(UnitInfo)

def SetHeadingGroup(GI, h):
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UnitInfo = GI.GetPlatformInterface(n)
        UnitInfo.DeleteTask('AutoLoiter')
        SetHeading(UnitInfo, h)

# Group menu functions from Ben "Mnfe" 20061217 post
# Updated with 20061220 post
def RelGroupSpeedMax(GI):
    RelGroupSpeed(GI, 999.0)

def RelGroupSpeed100(GI):
    RelGroupSpeed(GI, 1.0)

def RelGroupSpeed80(GI):
    RelGroupSpeed(GI, 0.8)

def RelGroupSpeed50(GI):
    RelGroupSpeed(GI, 0.5)

def RelGroupSpeed30(GI):
    RelGroupSpeed(GI, 0.3)
            
# set group speed relative to maximum speed of slowest member
def RelGroupSpeed(GI, speed_fraction):            
    unit_count = GI.GetUnitCount()
    max_speed = 9999
    for n in range(0,unit_count):
        UI = GI.GetPlatformInterface(n)
        this_speed = UI.GetMaxSpeed()
        if(this_speed < max_speed):
            max_speed = this_speed
    for n in range(0,unit_count):
        UI = GI.GetPlatformInterface(n)
        UI.SetSpeed(speed_fraction * max_speed)

            
def AddEngageAllOrderGroup(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UnitInfo=GI.GetPlatformInterface(n)
        if(not UnitInfo.TaskExists('EngageAll')):
            AddEngageAllOrder(UnitInfo) 

def GroupAllSensors(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UnitInfo=GI.GetPlatformInterface(n)
        UnitInfo.SetAllSensorState(1)

def GroupPassiveSensors(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UnitInfo=GI.GetPlatformInterface(n)
        nSensors = UnitInfo.GetSensorCount()
        for n in range(0, nSensors):
            sensor_info = UnitInfo.GetSensorInfo(n)
            if (sensor_info.IsPassive()):
                UnitInfo.SetSensorState(n, 1)
            else:
                UnitInfo.SetSensorState(n, 0)

def GroupOfflineSensors(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UnitInfo=GI.GetPlatformInterface(n)
        UnitInfo.SetAllSensorState(0)


def GroupHeloAltitudeMedium(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UI=GI.GetPlatformInterface(n)
        if(UI.IsHelo()):
            AltitudeMedium(UI)

def GroupHeloAltitudeLow(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UI=GI.GetPlatformInterface(n)
        if(UI.IsHelo()):
            AltitudeLow(UI)

def GroupHeloAltitudeVeryLow(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UI=GI.GetPlatformInterface(n)
        if(UI.IsHelo()):
            AltitudeVeryLow(UI)

def GroupAltitudeHigh(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UI=GI.GetPlatformInterface(n)
        if(UI.IsAir() and not UI.IsHelo()):
            AltitudeHigh(UI)

def GroupAltitudeMedium(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UI=GI.GetPlatformInterface(n)
        if(UI.IsAir() and not UI.IsHelo()):
            AltitudeMedium(UI)

def GroupAltitudeLow(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UI=GI.GetPlatformInterface(n)
        if(UI.IsAir() and not UI.IsHelo()):
            AltitudeLow(UI)

def GroupAltitudeVeryLow(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UI=GI.GetPlatformInterface(n)
        if(UI.IsAir() and not UI.IsHelo()):
            AltitudeVeryLow(UI)

def GroupAddLandingOrder(GI,dest_id):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UI=GI.GetPlatformInterface(n)
        AddLandingOrder(UI,dest_id)

def GroupAddLandingHBOrder(GI):
    unit_count=GI.GetUnitCount()
    for n in range(0,unit_count):
        UI=GI.GetPlatformInterface(n)
        BB = UI.GetBlackboardInterface()
        homebase = BB.ReadMessage('Home')
        if (homebase != ''):
            if (UI.IsHelo()):
                UI.AddTask('LandHelo', 3.0, 0)
            else:
                UI.AddTask('Land', 3.0, 0)
            BB.Write('LandTarget', homebase)
            
# return true if not multiplayer or if group is fully controlled
def IsGroupControlled(GI):
    unit_count=GI.GetUnitCount()
    if (unit_count > 0):
        UnitInfo=GI.GetPlatformInterface(0)
        if (not UnitInfo.IsMultiplayerActive()):
            return 1
    else:
        return 1
    
    for n in range(0,unit_count):
        UnitInfo=GI.GetPlatformInterface(n)
        if (not UnitInfo.IsPlayerControlled()):
            return 0
    
    return 1

def TakeControlGroup(GI):
    GI.TakeControl()
        
        
def ReleaseControlGroup(GI):
    GI.ReleaseControl()

    
def SelectTargetGroup(GI, target_id):
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UI = GI.GetPlatformInterface(n)
        UI.SetTarget(target_id)

def ClearTargetGroup(GI):
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UI = GI.GetPlatformInterface(n)
        UI.SetTarget(-1)

def AttackTargetGroup(GI):
    unit_count = GI.GetUnitCount()
    for n in range(0, unit_count):
        UI = GI.GetPlatformInterface(n)
        if (UI.GetTarget() != -1):
            UI.AddTask('InterceptTarget', 2.0, 0)
        


def LaunchDatumGroup(GI, lon, lat, child_class):
    unit_count = GI.GetUnitCount()
    for k in range(0, unit_count):
        UI = GI.GetPlatformInterface(k)
        nCount = UI.GetLauncherCount()
        for n in range(0, nCount):
            if (UI.IsDatumLaunch(n)): 
                weap_name = UI.GetLauncherWeaponName(n)
                if (weap_name == child_class):
                    LaunchDatum(UI, lon, lat, n)

def GroupFormOn(GI, leader_name):
    leader_idx = GI.LookupUnitIdx(leader_name)
    if (leader_idx == -1):
        return
    UI_leader = GI.GetPlatformInterface(leader_idx)
    UI_leader.SetFormationLeader(-1)
    leader_id = UI_leader.GetPlatformId()
    
    follow_pos = 0
    unit_count = GI.GetUnitCount()
    for k in range(0, unit_count):
        UI = GI.GetPlatformInterface(k)
        if (UI.GetPlatformId() != leader_id):
            UI.SetFormationLeader(leader_id)
            form_range_km = 0.2 + 0.2*follow_pos
            form_bearing_rad = 3.1 + 0.05*follow_pos
            UI.SetFormationPosition(form_range_km, 0.1, form_bearing_rad, 0.1)
            follow_pos = follow_pos + 1
            
def GroupRefuelOn(GI, tanker_name):
    tanker_id = GI.LookupUnit(tanker_name)
    if (tanker_id == -1):
        return
        
    unit_count = GI.GetUnitCount()
    for k in range(0, unit_count):
        UI = GI.GetPlatformInterface(k)
        if ((UI.GetPlatformId() != tanker_id) and (not UI.IsTankerAircraft(UI.GetPlatformId()))):
            RefuelFromNamed(UI, tanker_name)






    
        
