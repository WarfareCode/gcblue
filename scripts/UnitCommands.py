import os, sys
from os.path import dirname, abspath, join, normpath
sys.path.append(abspath(join(dirname(__file__), 'Amram_Script_Data')))
from MissionTemplates import *
from Amram_Utilities import *
import math


deg_to_rad = 0.01745329252


def SetFormationLeader(UI, id):
    UI.SetFormationLeader(id)
    UI.UpdateMissionEditGraphics() # so formation graphics appear without rehook
    #UI.DisplayMessage('Form leader: %d' % id)

def EnableFormationEdit(UI):
    UI.SetFormationEdit(1)
    
def DisableFormationEdit(UI):
    UI.SetFormationEdit(0)
    
def SetFormationMode(UI, mode_id):
    UI.SetFormationMode(mode_id)
    
def ActivateAllSensors(UI):
    UI.SetAllSensorState(1)

def ActivatePassiveSensors(UI):
    nSensors = UI.GetSensorCount()
    for n in range(0, nSensors):
        sensor_info = UI.GetSensorInfo(n)
        if (sensor_info.IsPassive()):
            UI.SetSensorState(n, 1)

def GetConnControl(BB):
    return BB.Write('ConnLock', '')

def ReleaseConnControl(BB):
    if (BB.ReadAuthor('ConnLock') == BB.author):
        BB.Erase('ConnLock')

def GetSensorControl(BB):
    return BB.Write('SensorLock', '')

def ReleaseSensorControl(BB):
    BB.Erase('SensorLock')

def TakeControl(UI):
    UI.TakeControl()

def ReleaseControl(UI):
    UI.ReleaseControl()

def AddEngageAllOrder(UI):
    UI.AddTask('EngageAll', 2.0, 0)

def ToggleEngageAll(UI):
    if (UI.TaskExists('EngageAllAir')):
        UI.DeleteTask('EngageAllAir')
        UI.AddTask('EngageAll', 2.0, 0)
    elif (UI.TaskExists('EngageAll')):
        UI.DeleteTask('EngageAll')
    else:
        UI.AddTask('EngageAllAir', 2.0, 0)
		
def AddTaskByName(UI, taskName):
	UI.AddTask(taskName, 3.0, 0)
	
def AddBombTargetTask(UI):
    UI.AddTask('BombTarget', 3.0, 0)

def AddBombDatumTask(UI, lon, lat):
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLongitude', '%f' % lon)
    BB.Write('DatumLatitude', '%f' % lat)
    UI.AddTask('BombDatum', 3.0, 0)

def AddBombDatumTaskDeg(UI, lon, lat):
    BB = UI.GetBlackboardInterface()
    deg_to_rad = 0.01745329252
    BB.Write('DatumLongitude', '%f' % (deg_to_rad*lon))
    BB.Write('DatumLatitude', '%f' % (deg_to_rad*lat))
    UI.AddTask('BombDatum', 3.0, 0)

# version that uses target_id to automatically get the coordinates
def AddBombDatumTaskTargetID(UI, target_id):
    target_track = UI.GetTrackById(target_id)
    if (not target_track.IsValid()):
        return

    lon = target_track.Lon
    lat = target_track.Lat
    
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLongitude', '%f' % lon)
    BB.Write('DatumLatitude', '%f' % lat)
    UI.AddTask('BombDatum', 3.0, 0)

def AddInterceptTask(UI):
    UI.AddTask('IntC', 2.0, 0)
    
# @param bingo_fuel return to base when fuel is less than this fuel fraction
# @param rtb_time return to base when indicated sim time has elapsed
def AddRTBtask(UI, home_name, bingo_fuel, rtb_time):
    BB = UI.GetBlackboardInterface()
    current_time = UI.GetTime()
    if (not BB.KeyExists('Home')):
        BB.Write('Home', home_name)
    BB.Write('Bingo', '%f' % bingo_fuel)
    BB.Write('RTBtime', '%f' % (current_time + rtb_time))
    UI.AddTask('RTB', 2.0, 0)


def AddAirFormationTaskTarget(UI):
    target = UI.GetTarget()
    AddAirFormationTaskId(UI, target)
    
def AddAirFormationTaskId(UI, id):
    track = UI.GetTrackById(id)
    if (not track.IsAir() or not UI.IsAir()):
        return
    
    BB = UI.GetBlackboardInterface()
    BB.Write('FormationLeader', '%d' % id)
    UI.AddTask('AirFormation', 2.0, 0)
    
def BreakAirFormation(UI):
    UI.SetFormationLeader(-1)
    
def AddRefuelTask(UI, target):
    UI.StartRefuelWith(target) #  direct call for now, need task
    
# for new first waypoint for helo, automatically increase speed if helo was slow
# do the same for ground vehicles
def ApplyHeloWaypointLogic(UI):
    if ((UI.IsHelo() or UI.IsGroundVehicle()) and not UI.TaskExists('Nav')):
        speed_kts = UI.GetSpeed()
        maxSpeed_kts = UI.GetMaxSpeed()
        if (speed_kts < 0.25*maxSpeed_kts):
            UI.SetSpeed(0.75*maxSpeed_kts)
            
    
def AddWaypointOrder(UI, lon, lat):
    if (not UI.HasFlightPort()):
        ApplyHeloWaypointLogic(UI)
        UI.AddNavWaypoint(lon, lat)
    else:
        FP = UI.GetFlightPortInfo()
        editMission = FP.GetEditMissionId()
        if (editMission == 0):
            UI.AddNavWaypoint(lon, lat)
        else:
            FP.AddMissionWaypoint(editMission, lon, lat)
            
            
def AddMissionWaypointAdvanced(UI, mission_id, lon, lat, alt_m, speed_kts):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.AddMissionWaypointAdvanced(mission_id, lon, lat, alt_m, speed_kts)


def AddWaypointOrderDeg(UI, lon_deg, lat_deg):
    deg_to_rad = 0.01745329252
    ApplyHeloWaypointLogic(UI)
    UI.AddNavWaypoint(deg_to_rad*lon_deg, deg_to_rad*lat_deg)

# version that sets altitude and speed too
def AddWaypointOrderDeg2(UI, lon_deg, lat_deg, alt_m, speed_kts):
    deg_to_rad = 0.01745329252
    UI.AddNavWaypointAdvanced(deg_to_rad*lon_deg, deg_to_rad*lat_deg, alt_m, speed_kts)
    

def EditWaypoint(UI, idx, lon, lat):
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = UI.GetPlatformId()
        group = False
    except:
        group = True
    if group:
        GI = UI
        for n in xrange(GI.GetUnitCount()):
            UI = GI.GetPlatformInterface(n)
            UI.EditNavWaypoint(idx, lon, lat)
    else:
        UI.EditNavWaypoint(idx, lon, lat)

def EditWaypointAdvanced(UI, idx, lon, lat, alt_m, speed_kts):
    UI.EditNavWaypointAdvanced(idx, lon, lat, alt_m, speed_kts)

def EditWaypointReferencePlatform(UI, referencePlatformId, waypoint_idx, referenceMode):
    UI.EditNavWaypointReference(waypoint_idx, referenceMode, referencePlatformId)
     
    
# insert nav waypoint before waypoint at idx
def InsertWaypoint(UI, idx, lon, lat):
    UI.InsertNavWaypoint(idx, lon, lat)    
    
# insert mission waypoint before waypoint at idx
def InsertMissionWaypoint(UI, mission_id, idx, lon, lat):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.InsertMissionWaypoint(mission_id, idx, lon, lat)      
    
# delete nav waypoint
def DeleteWaypoint(UI, idx):
    UI.DeleteNavWaypoint(idx)    
    
# delete mission waypoint
def DeleteMissionWaypoint(UI, mission_id, idx):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.DeleteMissionWaypoint(mission_id, idx)       
    
    
# version for flightport mission
def EditMissionWaypoint(UI, mission_id, idx, lon, lat):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.EditMissionWaypoint(mission_id, idx, lon, lat)
    
# version for flightport mission
def EditMissionWaypointAdvanced(UI, mission_id, idx, lon, lat, alt_m, speed_kts):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.EditMissionWaypointAdvanced(mission_id, idx, lon, lat, alt_m, speed_kts)
    
def EditMissionWaypointReferencePlatform(UI, referencePlatformId, mission_id, waypoint_idx, referenceMode):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.EditMissionWaypointReference(mission_id, waypoint_idx, referenceMode, referencePlatformId)    
    
# version with idx starting from current waypoint
def EditActiveWaypoint(UI, idx, lon, lat):
    EditWaypoint(UI, idx + UI.GetCurrentWaypoint(), lon, lat)
    
def EditActiveWaypointAdvanced(UI, idx, lon, lat, alt_m, speed_kts):
    EditWaypointAdvanced(UI, idx + UI.GetCurrentWaypoint(), lon, lat, alt_m, speed_kts)

def SetNavWaypointTasks(UI, idx, task_list):
    UI.SetNavWaypointTasks(idx, task_list)

def SetMissionWaypointTasks(UI, mission_id, idx, task_list):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.SetMissionWaypointTasks(mission_id, idx, task_list)

def SetMissionDatum(UI, lon_rad, lat_rad, mission_id):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.SetMissionDatum(mission_id, lon_rad, lat_rad)
    UI.UpdateMissionEditGraphics()
    
def SetTargetDatum(UI, lon_rad, lat_rad):
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLongitude', '%.7f' % lon_rad)
    BB.Write('DatumLatitude', '%.7f' % lat_rad)
    UI.UpdateMissionEditGraphics()

def ClearTargetDatum(UI):
    BB = UI.GetBlackboardInterface()
    BB.Erase('DatumLongitude')
    BB.Erase('DatumLatitude')
    UI.UpdateMissionEditGraphics()        
    
def SetMissionLandingTarget(UI, target_id, mission_id):
    if ((not UI.HasFlightPort()) or (target_id == -1)):
        return
    FP = UI.GetFlightPortInfo()
    base_name = UI.LookupFriendlyName(target_id)
    FP.SetMissionLandingTarget(mission_id, base_name)    

def SetMissionLaunchTime(UI, mission_id, time_string):
    if ((not UI.HasFlightPort()) or (mission_id == -1)):
        return
    FP = UI.GetFlightPortInfo()
    FP.SetMissionLaunchTime(mission_id, time_string)
  
def SetMissionType(UI, mission_id, type_string):
    if ((not UI.HasFlightPort()) or (mission_id == -1)):
        return
    FP = UI.GetFlightPortInfo()
    FP.SetMissionType(mission_id, type_string)
  
    
def SetNavLoopState(UI, state):
    UI.SetNavLoopState(state) # 1 to loop waypoints, 0 no loop
    
def AddPatrolOrder(UI):
    if (UI.IsSub()):
        UI.AddTask('SubPatrol', 1.0, 0)
    else:
        UI.AddTask('Patrol', 1.0, 0)

def AddPatrolStation(UI, lon, lat):
    UI.AddTask('PatrolCircle', 1.0, 0)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLongitude', '%f' % lon)
    BB.Write('StationLatitude', '%f' % lat)
    #BB.Write('StationAltitude', '%f' % UI.GetAlt())

def AddPatrolStationDeg(UI, lon, lat):
    UI.AddTask('PatrolCircle', 1.0, 0)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLongitude', '%f' % (deg_to_rad*lon))
    BB.Write('StationLatitude', '%f' % (deg_to_rad*lat))
    BB.Write('StationAltitude', '%f' % UI.GetAlt())

def AddLandingOrder(UI, dest_id):
    if (not UI.IsAir()):
        return
    
    UI.ClearTasks()
    if (UI.IsHelo()):
        UI.AddTask('LandHelo', 3.0, 0)
    else:
        UI.AddTask('Land', 3.0, 0)
        
    dest_name = UI.LookupFriendlyName(dest_id)
    BB = UI.GetBlackboardInterface()
    BB.Write('LandTarget', dest_name)

def AddMissileWarnTask(UI):
    UI.AddTask('MissileWarning', 0.0, 0)

def AddNamedTask(UI, task_name):
    UI.AddTask(task_name, 3.0, 0)
    
def ClearTasks(UI):
    UI.ClearTasks()

def ClearWaypoints(interface):
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        UI = interface
        UI.DeleteTask('Nav')
    except:
        GI = interface
        for n in xrange(GI.GetUnitCount()):
            UI = GI.GetPlatformInterface(n)
            UI.DeleteTask('Nav')

        
# gets info on closest (known) enemy or unknown platform within search range
def ClosestOfType(UI, class_mask, search_range_km):
    track_list = UI.GetTrackList(class_mask, search_range_km, 100)

    current_time = UI.GetTime()
    nTracks = track_list.Size()
    closest_range = 1e6
    closest_id = -1
    
    for n in range(0, nTracks):
        track_info = track_list.GetTrack(n)
        track_id = track_info.ID
        staleness = current_time - track_info.Time
        range_km = UI.GetRangeToTrack(track_info)

        if ((staleness <= 20.0) and (range_km < closest_range)):
            closest_range = range_km
            closest_id = track_id
        
    return (closest_id, closest_range)
    

# gets info on closest (known) enemy or unknown platform within search range
def ClosestOfTypeUnengaged(UI, class_mask, search_range_km):
    track_list = UI.GetTrackList(class_mask, search_range_km, 100)

    current_time = UI.GetTime()
    nTracks = track_list.Size()
    closest_range = 1e6
    closest_id = -1
    closest_bearing = 0
    
    for n in range(0, nTracks):
        track_info = track_list.GetTrack(n)
        track_id = track_info.ID
        nEngaged = track_info.GetEngagedCount()
        staleness = current_time - track_info.Time
        range_km = UI.GetRangeToTrack(track_info)

        if ((nEngaged == 0) and (staleness <= 20.0) and (range_km < closest_range)):
            closest_range = range_km
            closest_id = track_id
            closest_bearing = UI.GetHeadingToDatum(track_info.Lon, track_info.Lat)

       
    return (closest_id, closest_range, closest_bearing)



# clears all orders, moves to location and starts patrol
def MoveToAndPatrol(UI, lon, lat):
    ClearTasks(UI)
    UI.AddTask('Patrol', 1.0, 0)
    UI.AddTask('Nav', 2.0, 0)
    UI.AddTask('EngageAll', 3.0, 0)
    AddWaypointOrder(UI, lon, lat)


	
def SetPatrolArea(UI, lon1, lat1, lon2, lat2):
    BB = UI.GetBlackboardInterface()
    hasPatrol = BB.KeyExists('PatrolArea')
    if (not hasPatrol):
        UI.DeleteTask('Nav')
        if (not UI.IsHelo()):
            if (not HasSonobuoys(UI)):
                UI.AddTask('AirPatrolArea', 1.0, 0)
            else:
                UI.AddTask('ASWPatrolAreaFW', 1.0, 0)
        else:
            UI.AddTask('ASWPatrolArea', 1.0, 0)
    
    #area_string = '%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,' % (lon-0.001, lat+0.001, lon+0.001, lat+0.001, lon+0.001, lat-0.001, lon-0.001, lat-0.001)
    area_string = '%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,' % (lon1, lat1, lon2, lat1, lon2, lat2, lon1, lat2)
    SetPatrolAreaString(UI, area_string)
    
def SetMissionPatrolArea(UI, lon, lat, mission_id):
    BB = UI.GetBlackboardInterface()
    area_string = '%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,%.7f,' % (lon-0.001, lat+0.001, lon+0.001, lat+0.001, lon+0.001, lat-0.001, lon-0.001, lat-0.001)
    SetMissionPatrolAreaString(UI, mission_id, area_string)
    
def SetPatrolAreaString(UI, area_string):
    BB = UI.GetBlackboardInterface()
    BB.Write('PatrolArea', area_string)
    UI.UpdateMissionEditGraphics() # so area graphics appear without rehook
    
def SetMissionPatrolAreaString(UI, mission_id, area_string):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.SetMissionPatrolArea(mission_id, area_string) 
    UI.UpdateMissionEditGraphics()
    
def SetPatrolAnchor(UI, anchor_unit, anchor_mode):
    # look up position of anchor_unit (must be friendly unit)
    id = UI.LookupFriendlyId(anchor_unit)
    track = UI.GetTrackById(id)
    if (not track.IsValid()):
        return
    #anchor_string = '%s,%.7f,%.7f,%d' % (anchor_unit, track.Lon, track.Lat, anchor_mode)
    anchor_string = '%s,%d' % (anchor_unit, anchor_mode)
 
    BB = UI.GetBlackboardInterface()
    BB.Write('PatrolAnchor', anchor_string)
    UI.UpdateMissionEditGraphics() # so area graphics appear without rehook
    
def SetMissionPatrolAnchor(UI, mission_id, anchor_unit, anchor_mode):
    if (not UI.HasFlightPort()):
        return
    
    # look up position of anchor_unit (must be friendly unit) normally this is the flightport
    id = UI.LookupFriendlyId(anchor_unit)
    track = UI.GetTrackById(id)
    if ((not track.IsValid()) and (anchor_mode != 0)):
        return
    FP = UI.GetFlightPortInfo()
    FP.SetMissionPatrolAnchor(mission_id, anchor_unit, anchor_mode) 
    UI.UpdateMissionEditGraphics()    
    
    
def ClearPatrolArea(UI):
    BB = UI.GetBlackboardInterface()
    BB.Erase('PatrolArea')
    UI.UpdateMissionEditGraphics()
    
def ClearMissionPatrolArea(UI):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.SetMissionPatrolArea(mission_id, '')  
    UI.UpdateMissionEditGraphics()
    
def LaunchDatum(UI, lon, lat, launcher_num):
    datum_alt = UI.GetMapTerrainElevation(lon, lat)
    if (datum_alt < 5.0):
        datum_alt = 0.0
    UI.SendDatumToLauncher(lon,lat,datum_alt + 0.0,launcher_num)
    UI.Launch(launcher_num, 1)

# this version uses altitude provided instead of doing lookup of ground height
def LaunchDatum3D(UI, lon, lat, alt, launcher_num):
    UI.SendDatumToLauncher(lon,lat,alt,launcher_num)
    UI.Launch(launcher_num, 1)
    
def SetDatum(UI, lon, lat, launcher_num):
    datum_alt = UI.GetMapTerrainElevation(lon, lat)
    if (datum_alt < 5.0):
        datum_alt = 0.0
    UI.SendDatumToLauncher(lon,lat,datum_alt + 5.0,launcher_num)


def TargetAndEngageWith(UI, target_id, launcher):
    UI.SetTarget(target_id)
    if (UI.IsLauncherEffective(launcher)):
        LaunchTarget(UI, launcher)
    else:
        UI.SetTarget(-1)   # launcher is not effective vs. target, clear target
        UI.DisplayMessage('Canceling launch, not effective vs. target.')  

def LaunchTarget(UI, launcher):
    target_id = UI.GetTarget()
    if (target_id == -1):
        return   # return if no target selected
    if UI.IsDatumLaunch(launcher):
        track_info = UI.GetTargetTrackInfo()
        tti_s = UI.GetLauncherInterceptTime(launcher, track_info)
        predicted_track = track_info.PredictAhead(tti_s)
        lat = predicted_track.Lat
        lon = predicted_track.Lon

        if ((track_info.IsAir()) and ((track_info.Flags & 0x01) != 0)):
            alt = track_info.Alt
            UI.HandoffTargetToLauncher(launcher) # so that intended target is set
            LaunchDatum3D(UI, lon, lat, alt, launcher)
            return
        #UI.DisplayMessage('tti: %.1f' % tti_s)
        UI.HandoffTargetToLauncher(launcher) # so that intended target is set
        LaunchDatum(UI, lon, lat, launcher)
    else:  # handoff to active seeker
        target_accepted = UI.HandoffTargetToLauncher(launcher)
        if (target_accepted):
            UI.Launch(launcher,1)
        else:
            UI.DisplayMessage('Handoff failed, may not be in seeker coverage.') 

def LaunchChaffAndFlare(UI):
    if ((not UI.IsAir()) and (not UI.IsSurface())):
        return
    
    nLaunchers = UI.GetLauncherCount()
    for n in range(0, nLaunchers):
        info = UI.GetLauncherInfo(n)
        # LaunchMode == 10 is chaff or flare
        if (info.LaunchMode == 10) and (info.Quantity > 0): 
            UI.Launch(n, 1)

# launch any CM with minimum lifetime, returns number of CM launched
def LaunchShipCM(UI, minLifeTime_s):
    if (not UI.IsSurface()):
        return 0
    
    launch_count = 0
    nLaunchers = UI.GetLauncherCount()
    for n in range(0, nLaunchers):
        info = UI.GetLauncherInfo(n)
        # LaunchMode == 10 is chaff or flare
        if (info.LaunchMode == 10) and (info.Quantity > 0) and (info.LifeTime_s >= minLifeTime_s): 
            UI.Launch(n, 1)
            launch_count = launch_count + 1
            
    return launch_count

def GetCMLifeSpan(UI):
    if ((not UI.IsAir()) and (not UI.IsSurface())):
        return
    
    nLaunchers = UI.GetLauncherCount()
    for n in range(0, nLaunchers):
        info = UI.GetLauncherInfo(n)
        # LaunchMode == 10 is chaff or flare
        if (info.LaunchMode == 10) and (info.Quantity > 0): 
            UI.Launch(n, 1)
    
    
def PrintTargetInterceptParams(UI):
    # Get target id (-1 is no target)
    tgt_id = UI.GetTarget()
    if tgt_id == -1:
        UI.DisplayMessage('No target')
        return

    # Get track data on target
    track = UI.GetTrackById(tgt_id)

    track_heading_rad = track.Heading_rad
    track_speed_kts = track.Speed
    track_bearing_deg = UI.GetHeadingToDatum(track.Lon, track.Lat) # returns in units of deg

    my_heading_deg = UI.GetHeading() # returns in units of deg
    my_speed_kts = UI.GetSpeed()

    # Print info to console
    rad_to_deg = 57.29578
    display_string = 'Tgt hdg: %.0f deg, speed: %.0f kts, brg: %.0f deg, '  \
                     'own hdg: %.0f deg, speed: %.0f kts' % \
                     (rad_to_deg*track_heading_rad, track_speed_kts, track_bearing_deg, \
                      my_heading_deg, my_speed_kts)
                     
    UI.DisplayMessage(display_string)

# select new target and attack
def SelectAttackTarget(UI, target_id):
    UI.SetTarget(target_id)
    UI.AddTask('InterceptTarget', 2.0, 0)

# attack current target
def AttackTarget(UI):
    UI.AddTask('InterceptTarget', 2.0, 0)    
    
def SelectTarget(UI, target_id):
    UI.SetTarget(target_id)
   # trackinfo = UI.GetTargetTrackInfo()

def ClearTarget(UI):
    UI.SetTarget(-1)

def SpeedAB(UI):
    # 2.0 is max afterburner, 1.5 would be half afterburner
    SetFractionalSpeed(UI, 2.0)
    
def Speed100(UI):
    SetFractionalSpeed(UI, 1.0)

def Speed80(UI):
    SetFractionalSpeed(UI, 0.8)

def Speed50(UI):
    SetFractionalSpeed(UI, 0.5)

def Speed30(UI):
    SetFractionalSpeed(UI, 0.3)

def SpeedCruise(UI):
    alt_m = UI.GetAltitude()
    cruise_kts = UI.GetCruiseSpeedForAltitude(alt_m)
    if (cruise_kts > 0):
        UI.SetSpeed(cruise_kts)

def AltitudeHigh(UI):
    max_altitude = UI.GetMaxAlt()
    if (max_altitude >= 10000):
        SetAlt(UI, 10000)
    else:
        SetAlt(UI, max_altitude)

def AltitudeMedium(UI):
    SetAlt(UI, 4000)

def AltitudeLow(UI):
    SetAlt(UI, 150)

def AltitudeVeryLow(UI):
    SetAlt(UI, 50)


def DepthSurface(UI):
    if (not UI.IsSub()):
        return
    SetAlt(UI, 0)

def DepthPeriscope(UI):
    if (not UI.IsSub()):
        return
    SetAlt(UI, 0)
    
    SubInterface = UI.GetSubInterface()
    SubInterface.GoToPeriscopeDepth()

def DepthMedium(UI):
    if (not UI.IsSub()):
        return
    SetAlt(UI, -100)

def DepthDeep(UI):
    if (not UI.IsSub()):
        return
    SubInterface = UI.GetSubInterface()
    max_depth = SubInterface.GetMaxDepth()
    SetAlt(UI, -max_depth + 50)

def SetPeriscope(UI, state):
    if (not UI.IsSub()):
        return
    SubInterface = UI.GetSubInterface()
    if (state == 0):
        SubInterface.LowerPeriscope()
    else:
        SubInterface.RaisePeriscope()

def SetRadarMast(UI, state):
    if (not UI.IsSub()):
        return
    SubInterface = UI.GetSubInterface()  
    if (state == 0):
        SubInterface.LowerRadarMast()
    else:
        SubInterface.RaiseRadarMast()

def SetSnorkel(UI, state):
    if (not UI.IsSub()):
        return
    SubInterface = UI.GetSubInterface()
    if (state == 0):
        SubInterface.SetSnorkelState(0)
    else:
        SubInterface.SetSnorkelState(1)

# first char of s is assumed to be launcher_idx (only works
# for launchers 0-9)
# no longer true, reworked by Amram, now permits ANY launcher number, ex: '1337~Mk-46 Mod5',
# idx 1337, item Mk-46 Mod5
def ReloadLauncher(UI, s):
    #assume s is 'id~weapon'
    #use split to retrieve.
    idx, item = s.split('~')
    UI.LoadLauncher(int(idx), item)
    
def Reload0(UI, weap_name):
    UI.LoadLauncher(0, weap_name)

def Reload1(UI, weap_name):
    UI.LoadLauncher(1, weap_name)

def Reload2(UI, weap_name):
    UI.LoadLauncher(2, weap_name)

def Reload3(UI, weap_name):
    UI.LoadLauncher(3, weap_name)

def Reload4(UI, weap_name):
    UI.LoadLauncher(4, weap_name)

def Reload5(UI, weap_name):
    UI.LoadLauncher(5, weap_name)
    
def Reload6(UI, weap_name):
    UI.LoadLauncher(6, weap_name)    

def Reload7(UI, weap_name):
    UI.LoadLauncher(7, weap_name)        
    
def Unload(UI, launcher):
    UI.UnloadLauncher(launcher)
    
def SetFractionalSpeed(UI, k, dispMessage=0):
    # use throttle setting for units with throttle, throttle of > 1 is
    # afterburners 
    if (UI.HasThrottle()):
        UI.SetThrottle(k)
        if (dispMessage):
            if (k <= 1):
                UI.DisplayMessage('Set throttle to %2.0f%% military' % (100.0*k))
            else:
                UI.DisplayMessage('Set throttle to afterburn')
    else:
        if (k > 1):
            k = 1.0
        if UI.IsSub():
            max_speed = float(UI.QueryDatabase('sub', UI.GetPlatformClass(), 'MaxSpeed_kts').GetRow(0).GetString(0))
        else:
            max_speed = UI.GetMaxSpeed()
        UI.SetSpeed(k*max_speed)


def SetHeading(interface,h):
    try:
        UI = interface
        UI.DeleteTask('AutoLoiter')
        UI.SetHeadingRad(h)
    except:
        GI = interface
        unit_count = GI.GetUnitCount()
        for n in range(0, unit_count):
            UnitInfo = GI.GetPlatformInterface(n)
            UnitInfo.DeleteTask('AutoLoiter')
            SetHeading(UnitInfo, h)


def Altitude(UI):
    SetAlt(UI, 2345)

def ShowFlightPanel(UI):
    UI.SendCommand('ShowFlightPanel')

def ShowStoresPanel(UI):
    UI.SendCommand('ShowStoresPanel')

def ShowPlatformPanel(UI):
    UI.SendCommand('ShowPlatformPanel')

def ToggleRadars(UI):
    n_sensors = UI.GetSensorCount()
    for n in range(0, n_sensors):
        sens_info = UI.GetSensorInfo(n)

        # 1 radar, 2 ESM, 4 passive sonar, 8 active sonar, 16 optical, 0 error
        if (sens_info.type == 1): 
            if (sens_info.isActive):
                UI.SetSensorState(n, 0)
            else:
                UI.SetSensorState(n, 1)
                UI.PlaySound('Ping')
				
# 28DEC2010, added for check if helo has dipping sonar
def HasSonar(UI):
    n_sensors = UI.GetSensorCount()
    for n in range(0, n_sensors):
        sens_info = UI.GetSensorInfo(n)
        # 1 radar, 2 ESM, 4 passive sonar, 8 active sonar, 16 optical, 0 error
        if ((sens_info.type == 4) or (sens_info.type == 8)): 
            return 1
    return 0

                
# return 1 if unit has gravity bombs, 0 otherwise
def HasGravityBombs(UI):
    nLaunchers = UI.GetLauncherCount()
    for n in range(0, nLaunchers):
        info = UI.GetLauncherInfo(n)
        # LaunchMode == 3 is gravity bomb
        if (info.LaunchMode == 3) and (info.Quantity > 0): 
            return 1
    return 0
    
# return 1 if unit has sonobuoys, 0 otherwise
def HasSonobuoys(UI):
    nLaunchers = UI.GetLauncherCount()
    for n in range(0, nLaunchers):
        info = UI.GetLauncherInfo(n)
        # LaunchMode == 11 is sonobuoy
        if (info.LaunchMode == 11) and (info.Quantity > 0): 
            return 1
    return 0    

# TLL - added.  'v' in hotkey menu
def ReverseOurCourse(UI):
    current_heading = UI.GetHeading() + 180
    if (current_heading >= 360):
        current_heading = current_heading - 360
    UI.SetHeading(current_heading)

def EraseLastOrder(UI):
    task_list = UI.GetTaskList()
    if (task_list.Size() > 0):
        UI.DeleteTask(task_list.GetString(task_list.Size()-1))


def AddCAPMission(UI, lon, lat):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.AddCAPMission(lon, lat)

def AddASWMission(UI, lon, lat):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.AddASWMission(lon, lat)    

def AddAEWMission(UI, lon, lat):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.AddAEWMission(lon, lat)        
    
def AddAttackMission(UI, targetId):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.AddAttackMission(targetId)

def SetEditMissionId(UI, mission_id):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.SetEditMissionId(mission_id)
    
def AddMissionWaypoint(UI, lon_rad, lat_rad, mission_id):
    if (not UI.HasFlightPort()):
        return
    FP = UI.GetFlightPortInfo()
    FP.AddMissionWaypoint(mission_id, lon_rad, lat_rad)

def ReportBestLauncherForTarget(UI):
    launcher_info = UI.GetBestLauncher()
    launcher_idx = launcher_info.Launcher
    
    if (launcher_idx != -1):
        target_range = UI.GetRangeToTarget()
        launch_range = launcher_info.Range_km  # reference max range, use for launch decision
        UI.DisplayMessage('Best launcher %d, launch range %f' % (launcher_idx, launch_range))
    else:
        UI.DisplayMessage('No valid launcher')
        
        
def UpdateWeaponTargetDatum(WI, lon_rad, lat_rad):
    WI.UpdateTargetPosition(lon_rad, lat_rad)

    
def SetPitch(UI, theta, rate = 9, uncontrolled = True):
    BB = UI.GetBlackboardInterface()
    if uncontrolled:
        if not BB.KeyExists('uncontrolled_dive'):
            BB.Write('uncontrolled_dive', '1')
    Fast = True
    if abs(UI.GetClimbDeg() - theta) <= (rate*2):
        UI.SetClimbDeg(theta)
        Fast = False
    elif theta - UI.GetClimbDeg() > rate:
        UI.SetClimbDeg(UI.GetClimbDeg() + rate)
    elif UI.GetClimbDeg() - theta > rate:
        UI.SetClimbDeg(UI.GetClimbDeg() - rate)
    else:
        UI.SetClimbDeg(theta)
        Fast = False
    return Fast            

def cruiseclimb(TI):
    UI = TI.GetPlatformInterface()
    BB = UI.GetBlackboardInterface()
    update = 0.2
    TI.SetUpdateInterval(update)
    #assumes full throttle climb
    #achieves cruise speed, then pitched up, and tries to manipulate pitch to maintain cruise speed and climb rate to within 5%
    #later development should also attempt to obey maxclimbrate.
    #later development should also accept desired altitude inputs so we can level off when we get there.
    #do everything in absolute values as relative differences, then invert to negative for descent if necessary.
   
    try:
        alt = float(BB.ReadMessage('ClimbInitAlt'))
    except:
        TI.EndTask()
        return
    if alt == -1:
        alt = UI.GetCruiseAlt()
    if alt <  UI.GetTerrainElevation():
        alt = UI.GetTerrainElevation() + 50
    do_pitch = False
    if alt < UI.GetAlt() - 5:
        UI.SetAlt(alt)
        TI.EndTask()
        return
    elif alt > UI.GetAlt() + 5:
        do_pitch = True
    else:
        throttle = float(BB.ReadMessage('ClimbInitThrottle'))
        if throttle == -1:
            SpeedCruise(UI)
        else:
            UI.SetThrottle(throttle)
            
        alt = float(BB.ReadMessage('ClimbInitAlt'))
        if alt == -1:
            alt = UI.GetCruiseAlt()

        BB.Erase('Last_Speed')
        BB.Erase('ClimbInitThrottle')
        BB.Erase('ClimbInitAlt')
        TI.EndTask()
        UI.SetClimbDeg(0.0)
        UI.SetAlt(alt)
        return
    if do_pitch:
        if BB.KeyExists('Last_Speed'):
            last_speed = float(BB.ReadMessage('Last_Speed'))
        else:
            last_speed = UI.GetSpeed()

        pitch = UI.GetClimbDeg()
        rate_mod = 3
        
        want_pitch = math.degrees(math.atan((alt - UI.GetAlt()) / 1500))
        if want_pitch < -67:
            want_pitch = -67

        cruise_spd = UI.GetCruiseSpeedForAltitude(UI.GetAlt()) + 10
        gravity_losses = math.sin(math.radians(pitch)) * 9.80665
        accel_mod = ((1-(cruise_spd / UI.GetSpeed())) / 0.4) / update
        accel_mod2 = ((1-((cruise_spd+20) / UI.GetSpeed())) / 0.4) / update
        acceleration = (UI.GetSpeed() - last_speed) / update
        if alt > UI.GetAlt():
            if accel_mod2 > 0:
                UI.SetAlt(alt)
                return
            else:
                new_gravity_losses = gravity_losses + accel_mod + acceleration
                if new_gravity_losses < 0:
                    new_gravity_losses = 0
                rate_mod = max(abs(acceleration) / 10 + 0.5,0.5)
                if new_gravity_losses < 0:
                    new_gravity_losses = 0
                if new_gravity_losses > 9.80665:
                    new_gravity_losses = 9.80665
        elif alt < UI.GetAlt():
            new_gravity_losses = -9.02707
            if new_gravity_losses < -9.02707:
                new_gravity_losses = -9.02707
            if new_gravity_losses > 0:
                new_gravity_losses = 0
            
        new_pitch = math.degrees(math.asin(new_gravity_losses/9.80665))
        if want_pitch < 0:
            new_pitch = want_pitch
        else:
            if new_pitch > want_pitch:
                new_pitch = want_pitch
    
        SetPitch(UI, new_pitch, rate=rate_mod, uncontrolled=False)
        write_speed = str(UI.GetSpeed())
        BB.Write('Last_Speed',write_speed)

def SetAlt(UI, alt):
    UI.SetAlt(alt)
    if UI.HasThrottle():
        #then we can use my advanced climb until 1.26 resolved this.
        if UI.GetSpeed() == UI.GetCruiseSpeedForAltitude(UI.GetAlt()):
            throttle = -1
        else:
            throttle = UI.GetThrottle()
        if throttle < 1.0 and alt > UI.GetAlt():
            UI.SetThrottle(1.0)
        OptionHandler(UI,'ClimbInitThrottle|Set|%s;ClimbInitAlt|Set|%s;cruiseclimb|Task|Start~0.2~-1' % (throttle, alt))

        
def Check_Status(UI, launcher, mode):
        # 0 = LAUNCHER_READY
        # 1 = BAD_LAUNCHER              ///< launcher index does not exist
        # 2 = LAUNCHER_EMPTY
        # 3 = LAUNCHER_BUSY             ///< launcher auto reloading
        # 4 = NO_DATUM
        # 5 = NO_TARGET
        # 6 = NOT_DETECTED_FC           ///< fire control sensor can't detect target (could be off)
        # 7 = NOT_DETECTED_SEEKER       ///< seeker can't detect target
        # 8 = FC_BUSY                   ///< fire control sensor has no free tracks
        # 9 = LAUNCHER_ERROR
        #10 = LAUNCHER_INACTIVE
        #11 = NO_FIRECONTROL
        #12 = TOO_DEEP                  ///< too deep for sub launch
        #13 = TOO_LOW                   ///< too low for aircraft missile launch
        #14 = TOO_HIGH                  ///< too high for aircraft missile launch
        #15 = DAMAGED                   ///< cannot operate due to damage
        #16 = INVALID_TARGET            ///< not effective vs. target type
        #17 = OUT_OF_RANGE              ///< target is beyond max range
        #18 = INVALID_FUEL_OPERATION    ///< invalid op for external fuel tank
        #19 = LAUNCHER_LOADING          ///< added for multiplayer, loading from magazine
        #20 = LAUNCHER_UNLOADING        ///< added for multiplayer, unloading to magazine
        #21 = OUT_OF_FOV                ///< target is outside of field of view of this launcher
        #22 = TOO_CLOSE                 ///< target is inside minimum range
        #23 = LAUNCHER_EMPTY_AUTORELOAD ///< empty, try autoreload when ready, workaround to delay auto-reload until after launch
        #24 = ROE_HOLD                  ///< ready, but launch violates ROE
    
    status_num = launcher.Status

    if status_num:
        status_strings = [
            'Launcher ready to fire...',
            'Launcher does not exist',
            'Launcher empty',
            'Launcher busy',
            'no datum',
            'no target',
            'FC does not detect target',
            'seeker does not detect target',
            'all FC channels busy',
            'Unknown launcher error',
            'Launcher inactive',
            'No Firecontrol',
            'Too deep',
            'Too low for launch',
            'Too high for launch',
            'Launcher is damaged',
            'Invalid target',
            'Target out of range',
            'Invalid Fuel Operation',
            'Launcher is Loading',
            'Launcher is unLoading',
            'target/datum outside FoV',
            'Too close',
            'Empty, Autoreload expected',
            'ROE restrictions, holding fire']
        excuse = status_strings[status_num]
        return False, excuse
    else:
        excuse = 'firing as ordered'
        return True, excuse

def Use_Launcher_On_Target_Amram(UI, launcher, launch_type, *target):
    #dependency on current set target removed.  Must now be handed target criteria.
    launcher = UI.GetLauncherInfo(launcher)
    if launcher.Status != 0:
        return False
    
    launch_mode = launcher.LaunchMode
    isdatum = False
    if len(target) == 2:
        datum = target
        isdatum = True
    elif len(target) == 1:
        target_info = UI.GetTrackById(target[0])
    else:
        #use the assigned target
        if UI.GetTarget() != -1:
            target_info = UI.GetTargetTrackInfo()
        
    launch_qty = 1 # only launch one at a time for spacing
    
    if launch_type == -2:
        #we need to determine our launch_type now.
        weapon_name = UI.GetLauncherWeaponName(launcher.Launcher)
        if UI.QueryDatabase('torpedo',weapon_name,'ClassificationId').GetRow(0).GetString(0) == '130':
            #its a torpedo
            launch_type = 2
        elif UI.QueryDatabase('missile',weapon_name,'ClassificationId').GetRow(0).GetString(0) == '64':
             #its a missile
             launch_type = 0
        elif UI.QueryDatabase('ballistic',weapon_name,'BallisticType').GetRow(0).GetString(0) == '5':  #rocket
            #its a rocket
            launch_type = 3
        else:
            #must be a ballistic if we get here
            launch_type = 1
            if not UI.IsAir():
                #then we know they aren't bombs.
                launch_qty = 5
    
    if launch_mode == 0:  # datum launch
        if launch_type == 2:  #torpedo
            if isdatum:
                lon, lat = datum
                alt = UI.GetMapTerrainElevation(datum[0], datum[1])
                if alt < 0:
                    alt = 0
            else:
                #is target, determine lead
                range_km = UI.GetRangeToTrack(target_info)
                speed1 = float(UI.QueryDatabase('torpedo',UI.GetLauncherWeaponName(launcher.Launcher),'preEnableSpeed_kts').GetRow(0).GetString(0))
                speed2 = float(UI.QueryDatabase('torpedo',UI.GetLauncherWeaponName(launcher.Launcher),'maxSpeed_kts').GetRow(0).GetString(0))
                accel = float(UI.QueryDatabase('torpedo',UI.GetLauncherWeaponName(launcher.Launcher),'acceleration_ktps').GetRow(0).GetString(0))
                if UI.QueryDatabase('torpedo',UI.GetLauncherWeaponName(launcher.Launcher),'SensorClass').GetRow(0).GetString(0) != '':
                    seeker=True
                    UI.DisplayMessage('seeker = %s' % UI.QueryDatabase('torpedo',UI.GetLauncherWeaponName(launcher.Launcher),'SensorClass').GetRow(0).GetString(0)) != ''
                else:
                    seeker=False
                    UI.DisplayMessage('seeker = %s' % UI.QueryDatabase('torpedo',UI.GetLauncherWeaponName(launcher.Launcher),'SensorClass').GetRow(0).GetString(0)) != ''
                range_m = range_km * 1000
                launch_speed = UI.GetSpeed()
                accel_time1 = abs(speed1 - launch_speed) / accel
                accel_dist1 = 0.5 * (speed1 + launch_speed) * accel_time1
                travel_time1 = (range_m - accel_dist1) / speed1 + accel_time1
                accel_time2 = abs(speed1 - speed2) / accel
                accel_dist2 = 0.5 * (speed1 + speed2) * accel_time1
                travel_time2 = (range_m - accel_dist2) / speed2 + accel_time2
                if seeker:
                    travel_time2 *= 0.07  #add 7% for snaking
                travel_time_s = travel_time1 + travel_time2
                UI.DisplayMessage('travel_time = %s' % travel_time)
                target_info = target_info.PredictAhead(travel_time_s)
                lat = target_info.Lat
                lon = target_info.Lon
                alt = target_info.Alt
        elif launch_type == 1 or launch_type == 3:  #gun, rocket
            # if the Speed_mps is non-zero in launcher info, then adjust datum based on expected travel time and target speed and heading
            if isdatum:
                lon, lat = datum
                alt = UI.GetMapTerrainElevation(datum[0], datum[1])
                if alt < 0: alt = 0
            else:
                range_km = UI.GetRangeToTrack(target_info)
                if (launcher.Speed_mps > 0):
                    travel_time_s = 1000.0 * range_km / launcher.Speed_mps
                    travel_time_s = travel_time_s + 10.0 # add a little time for launch and altitude adjustment
                    target_info = target_info.PredictAhead(travel_time_s)
                lat = target_info.Lat
                lon = target_info.Lon
                alt = target_info.Alt
                if alt < 0: alt = 0
        else:  #launch_type = 0, missile
            #confirm the missile is the type its supposed to be.....
            if isdatum:
                lon, lat = datum
                alt = UI.GetMapTerrainElevation(datum[0], datum[1])
                if alt < 0: alt = 0
            else:
                flag = int(UI.QueryDatabase('missile',UI.GetLauncherWeaponName(launcher.Launcher),'targetFlags').GetRow(0).GetString(0))
                if target_info.IsSurface() and flag != 'Error':
                    
                    if not has_target_flag(flag, 1):
                        return False
                elif target_info.IsGround() and flag != 'Error':
                    if not has_target_flag(flag, 4):
                        return False
                range_km = UI.GetRangeToTrack(target_info)
                lat = target_info.Lat
                lon = target_info.Lon
                alt = target_info.Alt
        if not isdatum:
            UI.HandoffTargetToLauncher(launcher.Launcher) # to store intended target
        UI.SendDatumToLauncher(lon, lat, alt, launcher.Launcher)
        UI.Launch(launcher.Launcher, launch_qty)
        return True
    elif (launch_mode == 1) or (launch_mode == 2) or (launch_mode == 4):  # handoff to active seeker
        if launch_type == 3:
            if (launcher.Speed_mps > 0):
                range_km = UI.GetRangeToTrack(target_info)
                travel_time_s = 1000.0 * range_km / launcher.Speed_mps
                travel_time_s = travel_time_s + 10.0 # add a little time for launch and altitude adjustment
                target_info = target_info.PredictAhead(travel_time_s)
            lat = target_info.Lat
            lon = target_info.Lon
            alt = target_info.Alt
            if alt < 0: alt = 0
            UI.SendDatumToLauncher(lon, lat, alt, launcher.Launcher)
            UI.Launch(launcher.Launcher, launch_qty)
            return True
        elif launch_type is 0 or launch_type is 1:
            UI.HandoffTargetToLauncher(launcher.Launcher)
            UI.Launch(launcher.Launcher, launch_qty)
            return True
        else:
            return False
    else:
        UI.DisplayMessage('Unrecognized launch mode: %d' % launch_mode)
        return False
        