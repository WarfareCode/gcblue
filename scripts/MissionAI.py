from UnitCommands import *
from Landing import *
import math

VALID_ROE = 100


def GetMessageParam(BB, messageName):
    msg = BB.ReadMessage(messageName)
    if (msg == ''):
        return 0
    else:
        return float(msg)

def RadarOn(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    n_sensors = UI.GetSensorCount()
    for n in range(0, n_sensors):
        sens_info = UI.GetSensorInfo(n)
        # 1 radar, 2 ESM, 4 passive sonar, 8 active sonar, 16 optical, 0 error
        if (sens_info.type == 1): 
            UI.SetSensorState(n, 1)
    TI.EndTask()

# intermittent so that radar is on about 25% of the time within group, not synchronized
# across group so this isn't ideal
def RadarRandom(TI):
    UI = TI.GetPlatformInterface()
    TI.SetUpdateInterval(90.0)
    
    nGroup = 1
    mission = UI.GetMissionInfo()
    if (mission.IsValid()):
        nGroup = mission.GetMissionAircraftCount()
        
    p_on = 0.25 / float(nGroup)
    
    state = UI.Rand() < p_on
    
    n_sensors = UI.GetSensorCount()
    for n in range(0, n_sensors):
        sens_info = UI.GetSensorInfo(n)
        # 1 radar, 2 ESM, 4 passive sonar, 8 active sonar, 16 optical, 0 error
        if (sens_info.type == 1): 
            UI.SetSensorState(n, state)
    
    
                
def RadarOff(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    n_sensors = UI.GetSensorCount()
    for n in range(0, n_sensors):
        sens_info = UI.GetSensorInfo(n)
        # 1 radar, 2 ESM, 4 passive sonar, 8 active sonar, 16 optical, 0 error
        if (sens_info.type == 1): 
            UI.SetSensorState(n, 0)
    TI.EndTask()   
    
def ActiveSonarOn(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    n_sensors = UI.GetSensorCount()
    for n in range(0, n_sensors):
        sens_info = UI.GetSensorInfo(n)
        # 1 radar, 2 ESM, 4 passive sonar, 8 active sonar, 16 optical, 0 error
        if (sens_info.type == 8): 
            UI.SetSensorState(n, 1)
    TI.EndTask()         
                
def ActiveSonarOff(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    n_sensors = UI.GetSensorCount()
    for n in range(0, n_sensors):
        sens_info = UI.GetSensorInfo(n)
        # 1 radar, 2 ESM, 4 passive sonar, 8 active sonar, 16 optical, 0 error
        if (sens_info.type == 8): 
            UI.SetSensorState(n, 0)
    TI.EndTask()   

def WaitForGroup(TI):
    BB = TI.GetBlackboardInterface()
    if (not GetConnControl(BB)):
        TI.EndTask() # cant get controls so just end
        return
        
    TI.SetUpdateInterval(30.0)
    UI = TI.GetPlatformInterface()
    alt_m = UI.GetAltitude()
    cruise_speed = UI.GetCruiseSpeedForAltitude(alt_m)
    UI.SetSpeed(0.8*cruise_speed)
        
    UI.SetHeading(UI.GetHeading() + 90)

    
    iteration = TI.GetMemoryValue(1)
    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)
    
    mission = UI.GetMissionInfo()
    if (mission.IsValid()):
        lagging_waypoint = mission.GetSmallestWaypointIndex()
        my_waypoint = UI.GetCurrentWaypoint()
        if ((lagging_waypoint == my_waypoint) or (iteration > 100)): # dont wait more than about 50 min
            UI.SetSpeed(cruise_speed)
            TI.EndTask()
    else:
        TI.EndTask()  
 
    
# randomly move throughout area
def AirPatrolArea(TI):
    BB = TI.GetBlackboardInterface()
    if (not GetConnControl(BB)):
        #UI.DisplayMessage('High priority task has control')
        TI.EndTask() # cant get controls so just end
        return
        
    UI = TI.GetPlatformInterface()
    if (not UI.IsAir()):
        #UI.DisplayMessage('Not an aircraft')
        TI.EndTask()
        return
        
    state = TI.GetMemoryValue(2) # 0 - uninit, 1 - moving to new waypoint
    if (state == 0):
        TI.SetMemoryValue(2, 1)
        patrol_point = UI.GetRandomPatrolPoint()
        if ((patrol_point.lon == 0) and (patrol_point.lat == 0)):
            UI.DisplayMessage('No patrol area')
            TI.EndTask() # probably dont have a patrol area defined
            return
        TI.SetMemoryValue(11, patrol_point.lon)
        TI.SetMemoryValue(12, patrol_point.lat)
        
    lon_rad = TI.GetMemoryValue(11)
    lat_rad = TI.GetMemoryValue(12)

    range_km = UI.GetRangeToDatum(lon_rad, lat_rad)
    
    if (range_km < 2): # set new patrol point
        patrol_point = UI.GetRandomPatrolPoint()
        TI.SetMemoryValue(11, patrol_point.lon)
        TI.SetMemoryValue(12, patrol_point.lat)
        lon_rad = patrol_point.lon
        lat_rad = patrol_point.lat
    elif (range_km < 25):
        TI.SetUpdateInterval(15.0)
    else:
        TI.SetUpdateInterval(45.0)
    
        
    hdg_deg = UI.GetHeadingToDatum(lon_rad, lat_rad)  
    UI.SetHeading(hdg_deg)
    
    
    
# For ASW helicopter, randomly move throughout area, stopping to drop sonobuoys and use dipping sonar
def ASWPatrolArea(TI):
    BB = TI.GetBlackboardInterface()
    if (not GetConnControl(BB)):
        TI.EndTask() # cant get controls so just end
        return
        
    UI = TI.GetPlatformInterface()
 
    state = TI.GetMemoryValue(2) # 0 - uninit, 1 - moving to new waypoint, 2 - coming to hover, 3 - drop buoy, 4 - attack target, listen
    if (state == 0):
        if (not UI.IsHelo()):
            TI.EndTask()
            return
        UI.SetAllSensorState(1)
        TI.SetMemoryValue(2, 1)
        patrol_point = UI.GetRandomPatrolPoint()
        if ((patrol_point.lon == 0) and (patrol_point.lat == 0)):
            TI.EndTask() # probably dont have a patrol area defined
            return
        TI.SetMemoryValue(11, patrol_point.lon)
        TI.SetMemoryValue(12, patrol_point.lat)
        TI.SetMemoryValue(50, HasSonar(UI))
        state = 1
    
    # check for bingo fuel and cancel task if so, 18DEC2010 commented out, should use RTB task to do this
    # t = UI.GetTime()
    # last_bingo_check = TI.GetMemoryValue(20)
    # if ((t - last_bingo_check) > 60):
        # TI.SetMemoryValue(20, t)
        # if (CheckBingo(UI, BB)):
            # cruise_alt = UI.GetCruiseAltitude()
            # UI.SetAltitude(cruise_alt)
            # UI.SetSpeed(UI.GetCruiseSpeedForAltitude(cruise_alt))
            # ReleaseConnControl(BB)
            # TI.EndTask()
            # return
    has_sonar = TI.GetMemoryValue(50)
    my_track = UI.GetTrackById(UI.GetPlatformId())
    buoy_spacing_km = 6.0
    
    if (state == 1):
        # check for a sub target to attack
        best_target, best_launcher = GetSubTarget(UI) 
        if (best_target != -1):
            tgt_track = UI.GetTargetTrackInfo()
            TI.SetMemoryValue(11, tgt_track.Lon)
            TI.SetMemoryValue(12, tgt_track.Lat)
            #UI.DisplayMessage('sub %d, %f,%f' % (tgt_track.ID, tgt_track.Lon, tgt_track.Lat))

        lon_rad = TI.GetMemoryValue(11)
        lat_rad = TI.GetMemoryValue(12)
        range_km = UI.GetRangeToDatum(lon_rad, lat_rad)
        if (range_km < 0.3): # reached waypoint
            # pick next search waypoint
            patrol_point = UI.GetRandomPatrolPoint()
            TI.SetMemoryValue(11, patrol_point.lon)
            TI.SetMemoryValue(12, patrol_point.lat)
            TI.SetMemoryValue(2, 2)
        elif (range_km < 3):
            TI.SetUpdateInterval(15.0)
            UI.SetSpeed(0.5*UI.GetMaxSpeed())
        else:
            TI.SetUpdateInterval(45.0)
            UI.SetSpeed(0.8*UI.GetMaxSpeed())
            
        hdg_deg = UI.GetHeadingToDatum(lon_rad, lat_rad)  
        UI.SetHeading(hdg_deg)
        UI.SetAltitude(500)
        
        # check how far we are from last buoy drop and drop another if far enough
        last_lon_rad = TI.GetMemoryValue(61)
        last_lat_rad = TI.GetMemoryValue(62)
        if ((last_lon_rad != 0) and (UI.GetRangeToDatum(last_lon_rad, last_lat_rad) >= 5.0)):
            TI.SetMemoryValue(2, 5)
        return
    
    if (state == 2):
        TI.SetUpdateInterval(30.0)
        if (has_sonar):
            goal_alt_m = 50
            goal_speed_kts = 3
        else:
            goal_alt_m = 300
            goal_speed_kts = 40
        UI.SetAltitude(goal_alt_m)
        UI.SetSpeed(goal_speed_kts)
        if ((UI.GetAltitude() > (goal_alt_m+1)) or (UI.GetSpeed() > goal_speed_kts)):
            return
        TI.SetMemoryValue(2, 3)
        state = 3
        
    if (state == 3):
        nLaunchers = UI.GetLauncherCount()
        for n in range(0, nLaunchers):
            launcher_info = UI.GetLauncherInfo(n)
            if (launcher_info.LaunchMode == 11): # sonobuoy
                if (not IsSonobuoyWithin(UI, buoy_spacing_km)):
                    lon_rad = TI.GetMemoryValue(11)
                    lat_rad = TI.GetMemoryValue(12)
                    UI.SendDatumToLauncher(lon_rad, lat_rad, 0, n)
                    UI.Launch(n, 1)
                    # update last drop point
                    TI.SetMemoryValue(61, my_track.Lon)
                    TI.SetMemoryValue(62, my_track.Lat)
                break
        n_sensors = UI.GetSensorCount()
        for n in range(0, n_sensors):
            sens_info = UI.GetSensorInfo(n)
            # 1 radar, 2 ESM, 4 passive sonar, 8 active sonar, 16 optical, 0 error
            if ((sens_info.type == 4) or (sens_info.type == 8)): 
                UI.SetSensorState(n, 1)
        TI.SetMemoryValue(2, 4)
        TI.SetUpdateInterval(10.0)
        return
        
    if (state == 4):          
        # check for a sub target to attack
        target_id, launcher_idx = GetSubTarget(UI) 
        if ((target_id != -1) and (launcher_idx != -1)):
            UI.SetTarget(target_id) # double check target is set
            range_km = UI.GetRangeToTarget()
            if (range_km < 4):
                target_info = UI.GetTargetTrackInfo()
                UI.SendDatumToLauncher(target_info.Lon, target_info.Lat, target_info.Alt, launcher_idx)
                UI.Launch(launcher_idx, 1)
            else:
                TI.SetUpdateInterval(10.0)  # reposition to get closer to target        
        else:
            if (has_sonar):
                TI.SetUpdateInterval(240.0) # hover for a while if helo has sonar
            else:
                TI.SetUpdateInterval(10.0)
        TI.SetMemoryValue(2, 1)
    
    if (state == 5): # drop a buoy while flying leg to next point
        # drop buoy
        nLaunchers = UI.GetLauncherCount()
        for n in range(0, nLaunchers):
            launcher_info = UI.GetLauncherInfo(n)
            if (launcher_info.LaunchMode == 11): # sonobuoy
                if (not IsSonobuoyWithin(UI, buoy_spacing_km)):
                    lon_rad = TI.GetMemoryValue(11)
                    lat_rad = TI.GetMemoryValue(12)
                    UI.SendDatumToLauncher(lon_rad, lat_rad, 0, n)
                    UI.Launch(n, 1)
                break
        # update last drop point
        TI.SetMemoryValue(61, my_track.Lon)
        TI.SetMemoryValue(62, my_track.Lat)
        
        # return to state 1
        TI.SetUpdateInterval(10.0)
        TI.SetMemoryValue(2, 1)

# For fixed-wing aircraft, randomly move throughout area, dropping sonobuoys
def ASWPatrolAreaFW(TI):
    BB = TI.GetBlackboardInterface()
    if (not GetConnControl(BB)):
        TI.EndTask() # cant get controls so just end
        return
        
    UI = TI.GetPlatformInterface()

    state = TI.GetMemoryValue(2) # 0 - uninit, 1 - moving to new waypoint, 2 - coming to hover, 3 - drop buoy, 4 - attack target, listen
    if (state == 0):
        if (UI.IsHelo()):
            TI.EndTask() # fixed-wing only for this task
            return
        UI.SetAllSensorState(1)
        TI.SetMemoryValue(2, 1)
        patrol_point = UI.GetRandomPatrolPoint()
        if ((patrol_point.lon == 0) and (patrol_point.lat == 0)):
            TI.EndTask() # probably dont have a patrol area defined
            return
        TI.SetMemoryValue(11, patrol_point.lon)
        TI.SetMemoryValue(12, patrol_point.lat)
        state = 1
    
    buoy_spacing_km = 5.0
    my_track = UI.GetTrackById(UI.GetPlatformId())
    
    if (state == 1):
        cruise_kts = UI.GetCruiseSpeedForAltitude(UI.GetAltitude())
        UI.SetSpeed(cruise_kts)
        UI.SetAltitude(2000)
        
        # check for a sub target to attack
        best_target, best_launcher = GetSubTarget(UI) 
        if (best_target != -1):
            tgt_track = UI.GetTargetTrackInfo()
            TI.SetMemoryValue(11, tgt_track.Lon)
            TI.SetMemoryValue(12, tgt_track.Lat)
            #UI.DisplayMessage('sub %d, %f,%f' % (tgt_track.ID, tgt_track.Lon, tgt_track.Lat))

        lon_rad = TI.GetMemoryValue(11)
        lat_rad = TI.GetMemoryValue(12)
        range_km = UI.GetRangeToDatum(lon_rad, lat_rad)
        if (range_km < 1.0): # reached waypoint
            # pick next search waypoint
            patrol_point = UI.GetRandomPatrolPoint()
            TI.SetMemoryValue(11, patrol_point.lon)
            TI.SetMemoryValue(12, patrol_point.lat)
            TI.SetMemoryValue(2, 3) # drop a buoy at waypoint
        elif (range_km < 5.0):
            TI.SetUpdateInterval(15.0)
        else:
            TI.SetUpdateInterval(45.0)
            
        hdg_deg = UI.GetHeadingToDatum(lon_rad, lat_rad)  
        UI.SetHeading(hdg_deg)
        
        # check how far we are from last buoy drop and drop another if far enough
        last_lon_rad = TI.GetMemoryValue(61)
        last_lat_rad = TI.GetMemoryValue(62)
        if ((last_lon_rad != 0) and (UI.GetRangeToDatum(last_lon_rad, last_lat_rad) >= 5.0)):
            TI.SetMemoryValue(2, 5) # drop a buoy
        return
        
    if (state == 3):
        nLaunchers = UI.GetLauncherCount()
        for n in range(0, nLaunchers):
            launcher_info = UI.GetLauncherInfo(n)
            if (launcher_info.LaunchMode == 11): # sonobuoy
                if (not IsSonobuoyWithin(UI, buoy_spacing_km)):
                    lon_rad = TI.GetMemoryValue(11)
                    lat_rad = TI.GetMemoryValue(12)
                    UI.SendDatumToLauncher(lon_rad, lat_rad, 0, n)
                    UI.Launch(n, 1)
                    # update last drop point
                    TI.SetMemoryValue(61, my_track.Lon)
                    TI.SetMemoryValue(62, my_track.Lat)
                break
        TI.SetMemoryValue(2, 4) # look for sub target
        TI.SetUpdateInterval(10.0)
        return
        
    if (state == 4):          
        # check for a sub target to attack
        target_id, launcher_idx = GetSubTarget(UI) 
        if ((target_id != -1) and (launcher_idx != -1)):
            UI.SetTarget(target_id) # double check target is set
            range_km = UI.GetRangeToTarget()
            if (range_km < 4):
                target_info = UI.GetTargetTrackInfo()
                UI.SendDatumToLauncher(target_info.Lon, target_info.Lat, target_info.Alt, launcher_idx)
                UI.Launch(launcher_idx, 1)
            else:
                TI.SetUpdateInterval(10.0)  # reposition to get closer to target        
        else:

            TI.SetUpdateInterval(10.0)
        TI.SetMemoryValue(2, 1) # back to search
    
    if (state == 5): # drop a buoy while flying leg to next point
        # drop buoy
        nLaunchers = UI.GetLauncherCount()
        for n in range(0, nLaunchers):
            launcher_info = UI.GetLauncherInfo(n)
            if (launcher_info.LaunchMode == 11): # sonobuoy
                if (not IsSonobuoyWithin(UI, buoy_spacing_km)):
                    lon_rad = TI.GetMemoryValue(11)
                    lat_rad = TI.GetMemoryValue(12)
                    UI.SendDatumToLauncher(lon_rad, lat_rad, 0, n)
                    UI.Launch(n, 1)
                break
        # update last drop point
        TI.SetMemoryValue(61, my_track.Lon)
        TI.SetMemoryValue(62, my_track.Lat)
        
        # return to state 1
        TI.SetUpdateInterval(10.0)
        TI.SetMemoryValue(2, 1)        
        
# move between current waypoint and previous
def BarrierPatrol(TI):
    BB = TI.GetBlackboardInterface()
        
    UI = TI.GetPlatformInterface()
    if (not UI.IsAir()):
        TI.EndTask()
        return
    
    state = TI.GetMemoryValue(2) # 0 - uninit, 1 - initialized
    if (state == 0):
        UI.SetAllSensorState(1)
        TI.SetMemoryValue(2, 1)
        current_waypoint = UI.GetCurrentWaypoint()
        TI.SetMemoryValue(11, current_waypoint)

        
    # check for bingo fuel and cancel task if so
    t = UI.GetTime()
    last_bingo_check = TI.GetMemoryValue(20)
    if ((t - last_bingo_check) > 60):
        TI.SetMemoryValue(20, t)
        if (CheckBingo(UI, BB)):
            cruise_alt = UI.GetCruiseAltitude()
            UI.SetAltitude(cruise_alt)
            UI.SetSpeed(UI.GetCruiseSpeedForAltitude(cruise_alt))
            ReleaseConnControl(BB)
            TI.EndTask()
            return
    
    start_waypoint = TI.GetMemoryValue(11)
    current_waypoint = UI.GetCurrentWaypoint()
    if (current_waypoint > start_waypoint+1):
        UI.SetCurrentWaypoint(int(start_waypoint))

            
# Look for nearby sub target to engage
def GetSubTarget(UI):
    # anAffiliation: UNKNOWN = 0, FRIENDLY = 1, NEUTRAL = 2, HOSTILE = 3
    #
    # anClassMask:
    # PTYPE_SURFACE 0x0010
    # PTYPE_AIR 0x0020
    # PTYPE_MISSILE 0x0040
    # PTYPE_SUBSURFACE 0x0080
    # PTYPE_SUBMARINE 0x0081
    # PTYPE_FIXED 0x0100
    # int anClassMask, float afMaxRange_km, UINT8 anAffiliation
    track_list = UI.GetTrackList(0x0081, 100, VALID_ROE)

    current_time = UI.GetTime()
    nTracks = track_list.Size()
    best_range = 1e6
    best_target = -1
    best_launcher = -1
    best_engaged_count = 99
    
    for n in range(0, nTracks):
        track_info = track_list.GetTrack(n)
        track_id = track_info.ID
        is_destroyed = track_info.IsDestroyed()
        track_error_km = track_info.TrackErrorKm()
        engaged_count = track_info.GetEngagedCount()

        if ((engaged_count < 1) and (track_error_km < 2) and (not is_destroyed)):
            UI.SetTarget(track_id)
            launcher_info = UI.GetBestLauncher()
            launcher_idx = launcher_info.Launcher
            #UI.DisplayMessage('Best launcher %d' % launcher_idx)
            if (launcher_idx != -1):
                target_range = UI.GetRangeToTarget()
                launch_range = launcher_info.Range_km  # reference max range, use for launch decision

                is_better = (target_range <= launch_range) and (engaged_count < best_engaged_count)
                is_better = is_better or ((engaged_count == best_engaged_count) and (target_range < best_range))
                
                if (is_better):
                    best_range = target_range
                    best_target = track_id
                    best_launcher = launcher_idx
                    best_engaged_count = engaged_count
                
    UI.SetTarget(best_target)
    return (best_target, best_launcher)            
            
            
# @return 1 if within box of range_km on a half side
def IsSonobuoyWithin(UI, range_km):  
    track_list = UI.GetTrackList(0x0084, range_km, 1)
    return (track_list.Size() > 0)
            
            
            


