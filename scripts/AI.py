from AIcommon import *
from UnitCommands import *
from GroupCommands import *
from SubTactics import *
from Landing import *
from AirManagement import *
from AirMissions import *
from MissionAI import *
from GroundStrike import *
from EditMenu import *
from Amram_AI_Scripts import *
import math

    
    

def TestTask(TI):
    UI = TI.GetPlatformInterface()
    UI.SetHeading(UI.GetHeading() + 5)

    # test memory functions
    iteration = TI.GetMemoryValue(1)
    if (iteration == 0):
        TI.SetMemoryText('test', UI.GetName())
    elif (iteration == 1):
        memory_name = TI.GetMemoryText('test')
        UI.DisplayMessage('%s: mem name is %s' % (memory_name, UI.GetName()))
    

    # test blackboard
    BB = TI.GetBlackboardInterface()
    if (iteration == 0):
        BB.Write('TestInfo', 'test info here')
    
    if (iteration == 2):
        bb_item = BB.Read('TestInfo')
        UI.DisplayMessage('%s: %s %d %f' % (UI.GetName(), bb_item.message, bb_item.author, bb_item.priority))

    if (iteration == 3):
        bb_msg = BB.ReadMessage('TestInfo')
        bb_auth = BB.ReadAuthor('TestInfo')
        bb_pri = BB.ReadPriority('TestInfo')
        UI.DisplayMessage('%s: %s %d %f' % (UI.GetName(), bb_msg, bb_auth, bb_pri))

    # increment iteration
    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)

def AirEvade(TI):
    UI = TI.GetPlatformInterface()

    track = UI.GetClosestMissileTrack(20, 4, 0) # 4 for all non-friendly affiliations
    if (not track.IsValid()):
        TI.SetUpdateInterval(15.0)
        return

    TI.SetUpdateInterval(2.0)
    
    range_km = UI.GetRangeToTrack(track)
    bearing_deg = UI.GetHeadingToDatum(track.Lon, track.Lat)

    #UI.DisplayMessage('Missile %.1f km' % range_km)

    if (range_km < 4.0):
        LaunchChaffAndFlare(UI)
        
        # figure out direction to break
        dRight_deg = 90 + bearing_deg - UI.GetHeading()
        if (dRight_deg > 180):
            dRight_deg = dRight_deg - 360
        elif (dRight_deg < -180):
            dRight_deg = dRight_deg + 360

        if (abs(dRight_deg) < 90):
            UI.SetHeading(bearing_deg + 90)
        else:
            UI.SetHeading(bearing_deg - 90)

# patrol task, roughly circles same point, stays within 10 km of station
def PatrolCircle(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryValue(2, UI.GetHeading())
        TI.SetMemoryValue(3, 0) # 1 is heading to station, 0 patroling
        TI.SetMemoryValue(4, 30.0 + 15.0 * UI.Rand()) # random turn interval in seconds
        TI.SetMemoryText('Description', 'Perform surveillance along a zig-zag course') 

        station_lon = GetMessageParam(BB, 'StationLongitude')
        station_lat = GetMessageParam(BB, 'StationLatitude')
        station_alt = GetMessageParam(BB, 'StationAltitude')
        station_speed = GetMessageParam(BB, 'StationSpeed') # in kts
        TI.SetMemoryValue(10, station_lon)
        TI.SetMemoryValue(11, station_lat)
        TI.SetMemoryValue(12, station_alt)
        TI.SetMemoryValue(13, station_speed)
        Name = UI.GetName()
        ID = UI.LookupFriendlyId(UI.GetName())
        

    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)
    
    # activate all sensors
    can_radiate = GetSensorControl(BB)
    if (can_radiate and not UI.IsSub()):
        ActivateAllSensors(UI)
    else:
        ActivatePassiveSensors(UI)

    # return if conn is not available
    if (not GetConnControl(BB)):   
        return 

    station_lon = TI.GetMemoryValue(10)
    station_lat = TI.GetMemoryValue(11)
    station_alt = TI.GetMemoryValue(12)
    station_speed = TI.GetMemoryValue(13)

    if (UI.IsAir()):
        if (station_alt > 0):
        	UI.SetAlt(station_alt)

    if (station_speed > 0):
        UI.SetSpeed(station_speed)

    if ((station_lon != 0) or (station_lat != 0)):
        station_range = UI.GetRangeToDatum(station_lon, station_lat)
    else:
        station_range = 0  # effectively ignore station range if missing station info

    isTravelingToStation = TI.GetMemoryValue(3)
    if (isTravelingToStation):
        range_thresh = 1.0
        UI.SetSpeedToMax()
    else:
        range_thresh = 10.0

    if (UI.IsAir()):
        range_thresh = range_thresh * 4.0

    if (station_range > range_thresh):
        new_heading = UI.GetHeadingToDatum(station_lon, station_lat)
        TI.SetMemoryValue(3, 1)  # to indicate traveling to station
        UI.SetActionText('>Station')
        TI.SetUpdateInterval(10.0)
    else: 
        new_heading = UI.GetHeading() + 30
        TI.SetMemoryValue(3, 0)  # to indicate traveling to station
        UI.SetActionText('Patrol-Circ')
        TI.SetUpdateInterval(TI.GetMemoryValue(4))

    UI.SetHeading(new_heading)
    UI.SetMaxTurnRate(1.0)
    #tacking on a piece to try and read a message set by a tanker customer, to boost the speed of a tanker to accomodate them.  Should give tankers a dedicated patrol task eventually

    Name = UI.GetName()
    ID = UI.LookupFriendlyId(UI.GetName())
        
# warn if non-friendly missiles nearby
def MissileWarning(TI):
    UI = TI.GetPlatformInterface()
#    if (UI.IsPlayerControlled()):
#        TI.EndTask()
    BB = TI.GetBlackboardInterface()

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryText('Description', 'Warn if missiles nearby') 
        TI.SetMemoryValue(2, 0.0)  # last warning time
        TI.SetMemoryValue(3, 0.0) # last countermeasure (chaff/flare) launch time
        TI.SetMemoryValue(10, 0) # flag for EngageAll was active
        
    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)

    closest_id, closest_range = ClosestOfType(UI, 0x0040, 120)

    if (closest_id == -1):
        BB.Erase('MissileWarning')
        TI.SetUpdateInterval(15.0)
        return
    elif (closest_range > 40):
        # missiles between 40 km and 80 km, increase update rate
        BB.Erase('MissileWarning')
        TI.SetUpdateInterval(5.0)
        track = UI.GetTrackById(closest_id)
        if track.TrackErrorKm() > 5:
            for n in range(0,UI.GetSensorCount()):
                sensor = UI.GetSensorInfo(n)
                if sensor.type != 8:
                    UI.SetSensorState(n, 1)
        return
    else:
        for n in range(0,UI.GetSensorCount()):
            sensor = UI.GetSensorInfo(n)
            if sensor.type != 8:
                UI.SetSensorState(n, 1)

    TI.SetUpdateInterval(5.0)
    
    BB.Write('MissileWarning', '%.0f' % closest_range)
    
    if (UI.TaskExists('EngageAll')):
        TI.SetMemoryValue(10, 1) # set this to 1 to reload EngageAll when missiles clear

    if (not UI.TaskExists('EngageAllAir')):
        UI.AddTask('EngageAllAir', 4.0, 0)
        
    UI.SetAllSensorState(1)
    
    current_time = UI.GetTime()
    # if the missile is close or if it is inbound, launch any CM that will stay aloft long enough
    last_cm = TI.GetMemoryValue(3)
    
    if ((current_time - last_cm) > 30.0):
        missile_track = UI.GetTrackById(closest_id)
        range_km = UI.GetRangeToTrack(missile_track)
        headingError_rad = 99
        minLifeTime_s = 10
        cmLaunched = 0
        if ((missile_track.Flags & 0x04) != 0): # heading valid
            bearingFromMissile_rad = missile_track.BearingToRad(UI.GetLongitude(), UI.GetLatitude())
            headingError_rad = missile_track.Heading_rad - bearingFromMissile_rad
            if (headingError_rad > 3.1415):
                headingError_rad = headingError_rad - 6.283185
            elif (headingError_rad < -3.1415):
                headingError_rad = headingError_rad + 6.283185
        if ((missile_track.Flags & 0x02) != 0): #  speed valid, calc what lifespan we need out of CM
            minLifeTime_s = (range_km / (0.1 + missile_track.Speed * 0.000514)) - 5.0
        if ((range_km < 10) or (abs(headingError_rad) < 0.35)):
            cmLaunched = LaunchShipCM(UI, minLifeTime_s)
        if (cmLaunched > 0):
            TI.SetMemoryValue(3, current_time) # update cm launch time
 
 
    
#    last_warning = TI.GetMemoryValue(2)

#    if (UI.IsPlayerControlled() and (current_time - last_warning > 30.0)):
#        TI.SetMemoryValue(2, current_time)
#        UI.PlaySound('Alarm')
#        UI.DisplayPopupMessage('Missile alert')
       
# shoot hostiles and unknowns within range, but do not intercept.
# Turn if necessary to position launchers
def EngageAll(TI):
    UI = TI.GetPlatformInterface()
    if (UI.TaskExists('EngageAllAir')):
        UI.DeleteTask('EngageAllAir')
    EngageAllWrapper(TI, 'all')
            
def EngageAllAir(TI):
    UI = TI.GetPlatformInterface()
    if (UI.TaskExists('EngageAll')):
        UI.DeleteTask('EngageAll')
    EngageAllWrapper(TI, 'air')

# shoot hostiles and unknowns within range, but do not intercept.
# Turn if necessary to position launchers
# type: 'all' everything, 'air' just engage aircraft
def EngageAllWrapper(TI, type):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryText('Description', 'Engage hostiles and unknowns within range, but do not intercept') 

    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)

    # engage_mode values:
    # 0 - searching, 1 - turning to place target within launch sector, 2 - following/keeping target within semiactive sector
    engage_mode = TI.GetMemoryValue(2)

    # memory values
    # 10: target id
    # 11: launcher index
    # 12: launch/follow sector center
    # 13: launch/follow sector width
    # 14: formation leaderrr
    
    if (engage_mode == 0): # searching
        fcinfo = UI.GetFireControlInfo()
        if (not fcinfo.radarGuidanceActive):
            ReleaseConnControl(BB) # maintain control if FC radar guidance is active, otherwise release
            
        TI.SetMemoryValue(14, float(UI.GetFormationLeader())) # save formation leader to resume formation after attack
        if (type == 'air'):
            best_target, best_launcher = GetImmediateAirTarget(UI)
        else:
            best_target, best_launcher = GetImmediateTarget(UI)
            
        if (best_target != -1):
            #UI.DisplayMessage('%s: targ: %d, lau: %d' % (UI.GetName(), best_target, best_launcher))
            launcher_info = UI.GetLauncherInfo(best_launcher)
            if (launcher_info.IsValid()):
                TI.SetMemoryValue(10, best_target)
                TI.SetMemoryValue(11, best_launcher)
                TI.SetMemoryValue(12, launcher_info.SectorCenter)
                TI.SetMemoryValue(13, launcher_info.SectorWidth)
                TI.SetMemoryValue(2, 1)
                engage_mode = 1
                TI.SetUpdateInterval(5.0) 
            else:
                TI.SetMemoryValue(2, 0)
        else:
            # check for nearby missiles
            closest_id, closest_range = ClosestOfType(UI, 0x0040, 75)
            if (closest_id == -1):
                TI.SetUpdateInterval(25)
            else:
                if (closest_range < 20):
                    TI.SetUpdateInterval(1)
                else:
                    TI.SetUpdateInterval(5)
                if (not UI.IsSub()):
                    UI.SetAllSensorState(1)

    if (engage_mode == 1): # turn to target
        fcinfo = UI.GetFireControlInfo()
        
        target_id = long(TI.GetMemoryValue(10))
        target_track = UI.GetTargetTrackInfo()
        launcher = long(TI.GetMemoryValue(11))
        if ((target_id == -1) or (not target_track.IsValid()) or (target_track.IsDestroyed()) or (launcher == -1)): 
            TI.SetMemoryValue(2, 0)
            RejoinFormation(TI, UI)
            return
        UI.SetTarget(target_id)
        launcher = long(TI.GetMemoryValue(11))
        launcher_angle = TI.GetMemoryValue(12)
        sector_width = TI.GetMemoryValue(13)
        target_bearing = GetTargetBearing(UI)
        launcher_info = UI.GetLauncherInfo(launcher)
        heading_deg = UI.GetHeading()
        
        if (fcinfo.radarGuidanceActive):
            dh_deg = target_bearing-launcher_angle-heading_deg
            if (dh_deg > 180):
                dh_deg = dh_deg - 360
            elif (dh_deg < -180):
                dh_deg = dh_deg + 360
            dh_deg = min(dh_deg, fcinfo.maxRight_deg - 5.0)
            dh_deg = max(dh_deg, fcinfo.maxLeft_deg + 5.0)
            goal_heading = heading_deg + dh_deg
        else:
            goal_heading = target_bearing-launcher_angle
            
            
        if (GetConnControl(BB)):
            if UI.IsSurface():
                pass
            else:
                UI.SetHeading(goal_heading)
                alt_m = UI.GetAltitude()
                if (alt_m < launcher_info.MinLaunchAlt_m):
                    UI.SetAltitude(launcher_info.MinLaunchAlt_m + 1.0)
                    return
                elif (alt_m > launcher_info.MaxLaunchAlt_m):
                    UI.SetAltitude(launcher_info.MaxLaunchAlt_m - 1.0)
                    return
                if (UI.IsAir() and target_track.IsAir() and (target_track.Alt > 0)):
                    range_km = UI.GetRangeToTarget()
                    if (alt_m < target_track.Alt):
                        UI.SetAltitude(target_track.Alt)
                    elif (alt_m > (target_track.Alt + 200*range_km)):
                        UI.SetAltitude(target_track.Alt)
  
        engagement_angle = target_bearing - UI.GetHeading() - launcher_angle
        engagement_angle = ((engagement_angle + 180) % 360) - 180 # force to -180 to 180
        
        if (engagement_angle <= 0.5 * sector_width):
            #UI.DisplayMessage('Engaging target with launcher %d' % launcher)
            EngageTargetWithLauncher(UI, launcher)
            TI.SetMemoryValue(2, 0)
            RejoinFormation(TI, UI)
            TI.SetUpdateInterval(1.0) # wait 1 seconds
            UI.SetActionText('')
            #ReleaseConnControl(BB) # don't release conn control until after verifying that radar guidance is not needed in search state
        else:
            pass
            #UI.DisplayMessage('Out of sector')

# Used by Engage tasks
def RejoinFormation(TI, UI):
    formation_leader = long(TI.GetMemoryValue(14))
    if (formation_leader != -1):
        UI.SetFormationLeader(formation_leader)

# Adjust heading toward target, maintain altitude and speed to release point, 
# release ALL bombs at release point, and then reverse course
def BombTarget(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryText('Description', 'Head to and bomb target')
        TI.SetMemoryValue(2, 1) # state: 1 - fly to release, 2 - release, 3 - turn away
        if (not UI.IsAir()):
            TI.EndTask()
            return
        SetBombingAltitudeAndSpeed(UI)
        TI.SetMemoryValue(1, 1)
        return
        
    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)

    if (not GetConnControl(BB)):
        return


    track_info = UI.GetTargetTrackInfo()
    tgt_lat = track_info.Lat
    tgt_lon = track_info.Lon
    tgt_alt = UI.GetMapTerrainElevation(tgt_lon, tgt_lat) # since we're bombing a ground target (does track have same altitude value?)


    bomb_state = TI.GetMemoryValue(2)

    if (bomb_state == 2):
        DropAllBombs(UI, tgt_lon, tgt_lat, tgt_alt)
        TI.SetMemoryValue(2, 3)
        TI.SetUpdateInterval(4.0)
        return
    
    if (bomb_state == 3):
        UI.SetHeading(UI.GetHeading() + 180)
        # if we have any bombs left, turn for another run after 2 min, otherwise end task
        if (HasGravityBombs(UI)):
            TI.SetMemoryValue(2, 1) # back to state 1
            TI.SetUpdateInterval(120.0)
            UI.SetActionText('Repos')
        else:
            UI.SetActionText('')
            TI.EndTask()
        return    

    SetBombingAltitudeAndSpeed(UI)

    # adjust heading to target
    tgt_bearing = UI.GetHeadingToDatum(tgt_lon,tgt_lat)
    UI.SetHeading(tgt_bearing)

    tgt_range_m = 1000 * UI.GetRangeToTrack(track_info)  # horizontal range in m
    tgt_range_m = tgt_range_m - 10  # move in a little to spread bombs on either side
    own_speed_mps = 0.51444444 * UI.GetSpeed() # get speed in m/s
    own_alt_m = UI.GetAlt()
    d_alt_m = own_alt_m - tgt_alt
    if (d_alt_m < 0):
        TI.EndTask()
        return

    t_flight = math.sqrt(0.20394324 * (own_alt_m - tgt_alt))
    release_range_m = t_flight * own_speed_mps
    range_left_m = tgt_range_m - release_range_m
    if (range_left_m < 0):
        UI.SetSpeedToMax()
        UI.SetHeading(UI.GetHeading() + 180)
        TI.SetUpdateInterval(120.0) # try flying 2 min in opposite direction to open up range
        TI.SetMemoryValue(2, 1)    
        #UI.DisplayMessage('Bomb run failed. Too close, too fast or too high')
        return

    # calculate time to release
    t_release = range_left_m / own_speed_mps
    if (t_release < 10):
        TI.SetUpdateInterval(t_release)
        TI.SetMemoryValue(2, 2)  # release all bombs next update
        UI.SetActionText('Away %.0f s' % t_release)
    else:
        TI.SetUpdateInterval(9.0)
        UI.SetActionText('Bomb %.0f s' % t_release)

# Version that bombs a datum without requiring a target based on a sensor map track
def BombDatum(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    if (not GetConnControl(BB)):
        return

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryText('Description', 'Head to and bomb datum')
        TI.SetMemoryValue(2, 1) # state: 1 - fly to release, 2 - release, 3 - turn away
        datum_lon = GetMessageParam(BB, 'DatumLongitude')
        datum_lat = GetMessageParam(BB, 'DatumLatitude')
        TI.SetMemoryValue(10, datum_lon)
        TI.SetMemoryValue(11, datum_lat)
        if ((not UI.IsAir()) or ((datum_lon == 0) and (datum_lat == 0))):
            TI.EndTask()
            return
        if (not HasGravityBombs(UI)):
            TI.EndTask()
            return
        SetBombingAltitudeAndSpeed(UI)
        TI.SetMemoryValue(1, 1)
        return

    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)

    tgt_lon = TI.GetMemoryValue(10)
    tgt_lat = TI.GetMemoryValue(11)
    tgt_alt = UI.GetMapTerrainElevation(tgt_lon, tgt_lat) # since we're bombing a ground target (does track have same altitude value?)
    tgt_alt = max(tgt_alt, 0)

    bomb_state = TI.GetMemoryValue(2)
    if (bomb_state == 2):
        DropBombs(UI, tgt_lon, tgt_lat, tgt_alt, 8)
        TI.SetMemoryValue(2, 3)
        TI.SetUpdateInterval(4.0)
        UI.SetActionText('')
        return
    
    if (bomb_state == 3):
        UI.SetHeading(UI.GetHeading() + 180)
        # if we have any bombs left, turn for another run after 2 min, otherwise end task
        if (HasGravityBombs(UI)):
            TI.SetMemoryValue(2, 1) # back to state 1
            TI.SetUpdateInterval(120.0)
            UI.SetActionText('Repos')
        else:
            TI.EndTask()
        return

    SetBombingAltitudeAndSpeed(UI)
    
    # adjust heading to target
    tgt_bearing = UI.GetHeadingToDatum(tgt_lon, tgt_lat)
    UI.SetHeading(tgt_bearing)

    tgt_range_m = 1000 * UI.GetRangeToDatum(tgt_lon, tgt_lat)  # horizontal range in m
    tgt_range_m = tgt_range_m - 10  # move in a little to spread bombs on either side

    own_speed_mps = 0.51444444 * UI.GetSpeed() # get speed in m/s
    own_alt_m = UI.GetAlt()
    d_alt_m = own_alt_m - tgt_alt
    
    if (d_alt_m < 0):
        TI.EndTask()
        return

    t_flight = math.sqrt(0.20394324 * (own_alt_m - tgt_alt))
    release_range_m = t_flight * own_speed_mps
    range_left_m = tgt_range_m - release_range_m
    if (range_left_m < 0):
        UI.SetSpeedToMax()
        UI.SetHeading(UI.GetHeading() + 180)
        TI.SetUpdateInterval(120.0) # try flying 2 min in opposite direction to open up range
        TI.SetMemoryValue(2, 1)
        #UI.DisplayMessage('Bomb run failed. Too close, too fast or too high')
        return

    # calculate time to release
    t_release = range_left_m / own_speed_mps
    if (t_release < 10):
        TI.SetUpdateInterval(t_release)
        TI.SetMemoryValue(2, 2)  # release bombs next update
        UI.SetActionText('Away %.0f s' % t_release)
    else:
        TI.SetUpdateInterval(9.0)
        UI.SetActionText('Bomb %.0f s' % t_release)

# Version that dive bombs
def BombDatumDive(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    if (not GetConnControl(BB)):
        return

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryText('Description', 'Head to and bomb datum')
        TI.SetMemoryValue(2, 1) # state: 1 - fly to dive point, 2 - adjust dive for solution, 3 - drop, 4 - turn away and re-attack
        datum_lon = GetMessageParam(BB, 'DatumLongitude')
        datum_lat = GetMessageParam(BB, 'DatumLatitude')
        if ((datum_lon == 0) and (datum_lat == 0)):
            targetTrack = UI.GetTargetTrackInfo()
            if (targetTrack.IsValid()):
                datum_lon = targetTrack.Lon
                datum_lat = targetTrack.Lat
        
        TI.SetMemoryValue(10, datum_lon)
        TI.SetMemoryValue(11, datum_lat)
        if ((not UI.IsAir()) or ((datum_lon == 0) and (datum_lat == 0))):
            TI.EndTask()
            return
        if (not HasGravityBombs(UI)):
            TI.EndTask()
            return
        SetBombingAltitudeAndSpeed(UI)
        TI.SetMemoryValue(1, 1)
        return

    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)

    tgt_lon = TI.GetMemoryValue(10)
    tgt_lat = TI.GetMemoryValue(11)
    tgt_alt = UI.GetMapTerrainElevation(tgt_lon, tgt_lat) # since we're bombing a ground target (does track have same altitude value?)
    tgt_alt = max(tgt_alt, 0)

    bomb_state = TI.GetMemoryValue(2)
    if (bomb_state == 2): # diving to target
        TI.SetUpdateInterval(0.5)
        elGoal_deg = UI.CalculateBombElevationDeg(tgt_lon, tgt_lat)
        elCurrent_deg = UI.GetClimbDeg()
        if (abs(elGoal_deg - elCurrent_deg) < 0.1):
            TI.SetMemoryValue(2, 3) # drop bombs
            TI.SetUpdateInterval(0.1)
            return
        UI.SetClimbDeg(elGoal_deg)
        return
    
    if (bomb_state == 3):
        DropBombs(UI, tgt_lon, tgt_lat, tgt_alt, 8)
        TI.SetMemoryValue(2, 4)
        TI.SetUpdateInterval(3.0)
        UI.SetActionText('')
        return
    
    
    if (bomb_state == 4):
        UI.SetHeading(UI.GetHeading() + 180)
        UI.SetClimbDeg(0) # cancel dive command
        UI.SetAltitude(3000)
        # if we have any bombs left, turn for another run after 2 min, otherwise end task
        if (HasGravityBombs(UI)):
            TI.SetMemoryValue(2, 1) # back to state 1
            TI.SetUpdateInterval(120.0)
            UI.SetActionText('Repos')
        else:
            TI.EndTask()
        return

    # bomb state == 1
    TI.SetUpdateInterval(15.0)
    SetBombingAltitudeAndSpeed(UI)
    
    # adjust heading to target
    tgt_bearing = UI.GetHeadingToDatum(tgt_lon, tgt_lat)
    UI.SetHeading(tgt_bearing)

    tgt_range_m = 1000 * UI.GetRangeToDatum(tgt_lon, tgt_lat)  # horizontal range in m
    tgt_range_m = tgt_range_m - 10  # move in a little to spread bombs on either side

    own_speed_mps = 0.51444444 * UI.GetSpeed() # get speed in m/s
    own_alt_m = UI.GetAlt()
    d_alt_m = own_alt_m - tgt_alt
    
    if (d_alt_m < 0):
        TI.EndTask()
        return

    t_flight = math.sqrt(0.20394324 * (own_alt_m - tgt_alt)) # level drop
    release_range_m = (t_flight * own_speed_mps) + 200.0 # overfly slightly
    range_left_m = tgt_range_m - release_range_m
    if (range_left_m <= 0):
        TI.SetMemoryValue(2, 2) # start dive
        TI.SetUpdateInterval(1.0)
        return
    elif (range_left_m < 3000.0):
        TI.SetUpdateInterval(5.0)

def DropAllBombs(UI, tgt_lon, tgt_lat, tgt_alt):
    DropBombs(UI, tgt_lon, tgt_lat, tgt_alt, 99)

def DropBombs(UI, tgt_lon, tgt_lat, tgt_alt, qty):
    UI.DisplayMessage('Dropping bombs')
    nLaunchers = UI.GetLauncherCount()

    for n in range(0, nLaunchers):
        launcher_info = UI.GetLauncherInfo(n)
        if (launcher_info.LaunchMode == 3):
            if (launcher_info.IsNuclear == 1):
                qty = 1 # force qty to 1 if nuclear
            UI.SendDatumToLauncher(tgt_lon,tgt_lat,tgt_alt,n)
            UI.Launch(n, qty)

def SetBombingAltitudeAndSpeed(UI):
    min_alt_m = 0
    max_alt_m = 99999
    
    if (not UI.IsPlayerControlled()):
        max_alt_m = 6000 # AI bombs lower for better accuracy
    
    nLaunchers = UI.GetLauncherCount()
    for n in range(0, nLaunchers):
        launcher_info = UI.GetLauncherInfo(n)
        if (launcher_info.LaunchMode == 3):
            min_alt_m = max(launcher_info.MinLaunchAlt_m, min_alt_m)
            max_alt_m = min(launcher_info.MaxLaunchAlt_m, max_alt_m)
    
    alt_m = UI.GetAltitude()
    if (alt_m < min_alt_m):
        UI.SetAltitude(min_alt_m + 50)
    elif (alt_m > max_alt_m):
        UI.SetAltitude(max_alt_m - 50)
    
    
    speed_kts = UI.GetSpeed()
    if (speed_kts > 600):
        UI.SetSpeed(575)
    elif (speed_kts < 200):
        UI.SetSpeed(200)
        
def FireAutoCannon(UI):
    UI.DisplayMessage('Autocannon')

    nLaunchers = UI.GetLauncherCount()

    for n in range(0, nLaunchers):
        launcher_info = UI.GetLauncherInfo(n)
        if (launcher_info.LaunchMode == 4):
            UI.Launch(n, 2)

# return max range and classification mask based on loaded weapon capability
def MaxRangeForNonAir(UI):
    maxRange_km = 0
    targetFlags = 0
    
    nLaunchers = UI.GetLauncherCount()
    for n in range(0, nLaunchers):
        launcher_info = UI.GetLauncherInfo(n)
        if ((launcher_info.TargetFlags & 0x05) != 0):
            targetFlags = targetFlags | launcher_info.TargetFlags
            maxRange_km = max(maxRange_km, launcher_info.MaxRange_km)
    
    return (maxRange_km, targetFlags)
            
# returns id of closest target that is in-range, engageable, not already
# overwhelmingly engaged, and not a stale track
# returns -1 if none
# modified to avoid wasting all missiles on first target of stream raid
def GetImmediateTarget(UI):

    # run air target version to check for close air and missile targets
    best_air_target, best_air_launcher = GetImmediateAirTarget(UI)

    # target flags: 1 surface, 2 air, 4 land, 8 missile, 16 sub
    maxRange_km, targetFlags = MaxRangeForNonAir(UI)
    classMask = 0
    if ((targetFlags & 1) != 0):
        classMask = classMask | 0x0010
    if ((targetFlags & 4) != 0):
        classMask = classMask | 0x0100    
    if ((targetFlags & 16) != 0):
        classMask = classMask | 0x0080    
    
    #UI.DisplayMessage('MR: %f, TF:%d' % (maxRange_km, targetFlags))
    
    # anAffiliation: UNKNOWN = 0, FRIENDLY = 1, NEUTRAL = 2, HOSTILE = 3, ALL NONFRIENDLY = 4, VALID ROE ONLY = 100
    #
    # anClassMask:
    # PTYPE_SURFACE 0x0010
    # PTYPE_AIR 0x0020
    # PTYPE_MISSILE 0x0040
    # PTYPE_SUBSURFACE 0x0080
    # PTYPE_FIXED 0x0100
    # int anClassMask, float afMaxRange_km, UINT8 anAffiliation
    
    track_list = UI.GetTrackList(classMask, maxRange_km, 100)

    current_time = UI.GetTime()
    nTracks = track_list.Size()

    # if there's a current target, use that to initialize best target params
    current_target = UI.GetTarget()
    if (current_target != -1):
        launcher_info = UI.GetBestLauncher()
        target_track = UI.GetTargetTrackInfo()
        launcher_idx = launcher_info.Launcher
        
        best_range = UI.GetRangeToTarget()
        best_target = current_target
        best_launcher = launcher_idx
        best_engaged_count = target_track.GetEngagedCount()
    else:
        best_range = 1e6
        best_target = -1
        best_launcher = -1
        best_engaged_count = 99
    
    for n in range(0, nTracks):
        track_info = track_list.GetTrack(n)
        track_id = track_info.ID
        staleness = current_time - track_info.Time
        is_destroyed = track_info.IsDestroyed()
        bearing_only = track_info.IsBearingOnly() or (track_info.TrackErrorKm() > 20)
        engaged_count = track_info.GetEngagedCount()
        
        max_engaged_count = GetEngageLimit(track_info)
        max_staleness = GetStaleLimit(track_info)
        is_air_target = track_info.IsAir() or track_info.IsMissile()
        
        # check for crossing missile case
        missile_reject = 0
        if (track_info.IsMissile()):
            track_heading_valid = (track_info.Flags & 0x04) != 0
            if (track_heading_valid):
                cos_dhdg_rad = cos(track_info.BearingToRad(UI.GetLongitude(), UI.GetLatitude()) - track_info.Heading_rad)
                missile_reject = (cos_dhdg_rad < 0.866) # > about 30 deg
            else:
                missile_reject = 1
            
        #UI.DisplayMessage('AI815 Track %d, %.0f/%d/%d' % (track_id, staleness, bearing_only, engaged_count))

        if ((engaged_count < max_engaged_count) and (staleness < max_staleness) and (not bearing_only) and (not is_destroyed)):
            UI.SetTarget(track_id)
            launcher_info = UI.GetBestLauncher()
            launcher_idx = launcher_info.Launcher
            #UI.DisplayMessage('Best launcher %d' % launcher_idx)
            if (launcher_idx != -1):
                target_range = UI.GetRangeToTarget()
                launch_range = launcher_info.Range_km  # reference max range, use for launch decision

                is_better = (target_range <= launch_range) and (engaged_count < best_engaged_count)
                is_better = is_better or ((engaged_count == best_engaged_count) and (target_range < 0.9*best_range))
                is_better = is_better and (not missile_reject) # don't engage crossing missiles
                
                if (is_better):
                    best_range = target_range
                    best_target = track_id
                    best_launcher = launcher_idx
                    best_engaged_count = engaged_count
                    
                # Clear best if there is another unengaged air target close to the launch zone
                near_launch_range = (target_range > launch_range) and (target_range < 1.75*launch_range)
                if (near_launch_range and is_air_target and (launcher_idx == best_launcher) and \
                    (best_engaged_count > 0) and (engaged_count == 0) and (not missile_reject)):
                    best_range = 1e6
                    best_target = -1
                    best_launcher = -1
                    best_engaged_count = 99
                
    UI.SetTarget(best_target)
    
    return (best_target, best_launcher)

# returns id of closest target that is in-range, engageable, not already
# overwhelmingly engaged, and not a stale track
# returns -1 if none
# modified to avoid wasting all missiles on first target of stream raid
#
# version that only gets air and missile targets
def GetImmediateAirTarget(UI):

    # anAffiliation: UNKNOWN = 0, FRIENDLY = 1, NEUTRAL = 2, HOSTILE = 3
    #
    # anClassMask:
    # PTYPE_SURFACE 0x0010
    # PTYPE_AIR 0x0020
    # PTYPE_MISSILE 0x0040
    # PTYPE_SUBSURFACE 0x0080
    # PTYPE_FIXED 0x0100
    # int anClassMask, float afMaxRange_km, UINT8 anAffiliation
    track_list = UI.GetTrackList(0x0060, 150, 100)

    current_time = UI.GetTime()
    nTracks = track_list.Size()
    best_range = 1e6
    best_target = -1
    best_launcher = -1
    best_engaged_count = 99
    #UI.DisplayMessage('%s nTracks: %d' % (UI.GetName(), nTracks))
    
    for n in range(0, nTracks):
        track_info = track_list.GetTrack(n)
        track_id = track_info.ID
        staleness = current_time - track_info.Time
        is_destroyed = track_info.IsDestroyed()
        bearing_only = track_info.IsBearingOnly()
        engaged_count = track_info.GetEngagedCount()
        is_air_target = track_info.IsAir() or track_info.IsMissile()
        if (is_air_target or track_info.IsSub()):
            max_engaged_count = 2
        else:
            max_engaged_count = 5
        #UI.DisplayMessage('Track %d, %.0f/%d/%d' % (track_id, staleness, bearing_only, engaged_count))

        if ((engaged_count < max_engaged_count) and (staleness < 15.0) and (not bearing_only) and (not is_destroyed)):
            UI.SetTarget(track_id)
            launcher_info = UI.GetBestLauncher()
            launcher_idx = launcher_info.Launcher
            #UI.DisplayMessage('Best launcher %d' % launcher_idx)
            if (launcher_idx != -1):
                # check for crossing missile case
                missile_reject = 0
                if (track_info.IsMissile()):
                    track_heading_valid = (track_info.Flags & 0x04) != 0
                    if (track_heading_valid):
                        cos_dhdg_rad = cos(track_info.BearingToRad(UI.GetLongitude(), UI.GetLatitude()) - track_info.Heading_rad)
                        missile_reject = (cos_dhdg_rad < 0.866) # > about 30 deg
                    else:
                        missile_reject = 1
            
                target_range = UI.GetRangeToTarget()
                launch_range = launcher_info.Range_km  # reference max range, use for launch decision
                #UI.DisplayMessage('L%d TR: %.1f km, LR: %.1f km, MR: %d' % (launcher_idx, target_range, launch_range, missile_reject))
                is_better = (target_range <= launch_range) and (engaged_count < best_engaged_count)
                is_better = is_better or ((engaged_count == best_engaged_count) and (target_range < best_range))
                is_better = is_better and (not missile_reject)
                
                if (is_better):
                    best_range = target_range
                    best_target = track_id
                    best_launcher = launcher_idx
                    best_engaged_count = engaged_count
                    
                # Clear best if there is another unengaged air target close to the launch zone
                near_launch_range = (target_range > launch_range) and (target_range < 1.75*launch_range)
                if (near_launch_range and is_air_target and (launcher_idx == best_launcher) and \
                    (best_engaged_count > 0) and (engaged_count == 0) and (not missile_reject)):
                    best_range = 1e6
                    best_target = -1
                    best_launcher = -1
                    best_engaged_count = 99
                
    UI.SetTarget(best_target)
    
    return (best_target, best_launcher)
    
def Emcon(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    # take control of (active) sensors
    if (not GetSensorControl(BB)):
        return

    nSensors = UI.GetSensorCount()
    for n in range(0, nSensors):
        sensor_info = UI.GetSensorInfo(n)
        if (not sensor_info.IsPassive()):  # deactivate active sensors
            UI.SetSensorState(n, 0)

def AirPatrol(TI):
    UI = TI.GetPlatformInterface()

def SAM_Defense(UI):
    UI = TI.GetPlatformInterface()
    targetid = UI.GetTarget()
    if targetid != -1:
        InterceptTarget(UI)
        return
    UI.SetVar(0,0)  # set user variable 0 to zero
    # patrol box
    UI.SetAllSensorState(1)
    heading = UI.GetHeading()
    heading = heading + 45.0
    if (heading >= 360.0):
        heading = heading - 360.0
    UI.SetHeading(heading)
    TI.SetUpdateInterval(30.0)
    # engage hostiles in range

    missile_score, missile_id = GetSuitableTargetAll(UI, 64) 
    if (missile_score >= 3.0):
        best_id = missile_id
    else:
        surf_score, surf_id = GetSuitableTargetAll(UI, 16)
        air_score, air_id = GetSuitableTargetAll(UI, 32)

        if (air_score > surf_score):
            best_id = air_id
        else:
            best_id = surf_id

    #track_id = GetSuitableTarget(UI)
    if (best_id != -1):
        UI.SetTarget(best_id)
        UI.SetHeadingToInterceptTarget()
        TI.SetUpdateInterval(4.0)

def AvoidGround(UI):
    if (UI.IsAir()):
        terrainElevation = UI.GetTerrainElevation()
        if (terrainElevation < 0):
            terrainElevation = 0
        alt = UI.GetAlt()
        if ((alt - terrainElevation) < 80):
           UI.SetAlt(terrainElevation + 100)

# abs() of difference between two radian headings
def RadianHeadingDiff(h1, h2):
    delta = h1 - h2
    if (delta < -3.14159):
        delta = delta + 6.28318
    elif (delta > 3.14159):
        delta = delta - 6.28318
    if (delta < 0):
        delta = -delta
    return delta

# Run from hostile missiles (will run from supersonic antiship missiles too!)
# return 1 if evading, 0 otherwise
def EvadeMissiles(UI):
    if (UI.IsAir()==0):
        return 0  # only evade with air platforms

    max_range = 100  # max range in km to look for missile threats
    track_list = UI.GetTrackList(64, max_range, 3) # 64 returns missiles, 3 hostiles
    nMissiles = track_list.Size()
    closest_range = 10000
    foundThreat = 0
    flee_heading = 0
    for n in range(0, nMissiles):
        missile_track = track_list.GetTrack(n)
        hasAAMspeed = (missile_track.Speed > 600)  # ignore subsonic missiles
        track_range = UI.GetRangeToTrack(missile_track)
        isClosestThreat = (track_range < closest_range) or (~foundThreat)
        if hasAAMspeed and isClosestThreat:
            int_heading = UI.GetInterceptHeadingToTrack(missile_track)
            heading_diff = RadianHeadingDiff(int_heading, UI.GetHeadingRad())
            diff_thresh = 15/track_range   # 90 deg at 10 km
            if (heading_diff < diff_thresh): 
                foundThreat = 1
                closest_range = track_range
                flee_heading = int_heading + 3.14
                threat_track = missile_track
    
    if (foundThreat==0):
        return 0

    if (threat_track.IsValid()):
        UI.SetHeadingRad(flee_heading)  # run from missile
        if (UI.GetFuel() > 0.2):
            SetFractionalSpeed(UI, 2.0)
        else:
            SetFractionalSpeed(UI, 1.0)
        UI.SetUpdate(6.0)
        return 1
    else:
        return 0

# Task script automatically added to all jets after takeoff
def JetTakeoff(TI):
    UI = TI.GetPlatformInterface()
    if (not UI.IsAir()):
        TI.EndTask()
        return
    
    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryText('Description', 'Jet takeoff script') 
        TI.SetUpdateInterval(30.0)
        SetFractionalSpeed(UI, 2.0)  # activate max AB
        UI.SetAlt(3000) # about 10000 ft
        UI.SetPitchLimit(5)
        
    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)
    
    if (iteration >= 2): # run task for 2 iterations (1 minute)
        UI.SetPitchLimit(85.0)
        if (UI.GetThrottle() > 1.0):
            SetFractionalSpeed(UI, 1.0)  # shut off AB, set speed back to 100% mil
        TI.EndTask()
        return
        
# this version iterates through all tracks
def GetSuitableTargetAll(UI, class_mask):
    # anAffiliation: UNKNOWN = 0, FRIENDLY = 1, NEUTRAL = 2, HOSTILE = 3, ALL NONFRIENDLY = 4, VALID ROE = 100
    #
    # anClassMask:
    # PTYPE_SURFACE 0x0010
    # PTYPE_AIR 0x0020
    # PTYPE_MISSILE 0x0040
    # PTYPE_SUBSURFACE 0x0080
    # PTYPE_FIXED 0x0100
    # int anClassMask, float afMaxRange_km, UINT8 anAffiliation
    track_list = UI.GetTrackList(class_mask, 150, 100)
    nTracks = track_list.Size()
    best_score = 0
    best_target = -1
    info_string = ''
    for n in range(0, nTracks):
        track_info = track_list.GetTrack(n)
        track_id = track_info.ID
        engaged_count = track_info.GetEngagedCount()
        UI.SetTarget(track_id)
        score = ScoreTarget(UI, track_info)
        if (score > best_score):
            best_score = score
            best_target = track_id
            
        #info_string = '%s %d (%.1f %d)' % (info_string, track_id, score, engaged_count)
                
    #UI.DisplayMessage('%d: %s\n' % (class_mask, info_string))
    return (best_score, best_target)

# Just air tracks
def GetSuitableTarget(UI):
    air_track = UI.GetClosestAirTrack(150,100,1)
    UI.SetTarget(air_track.ID) # can be -1
    air_rating = ConsiderTarget(UI)
    
    surface_track = UI.GetClosestSurfaceTrack(200,100,4)  # surface first considers surface tracks
    UI.SetTarget(surface_track.ID)  
    surface_rating = ConsiderTarget(UI)

    if (air_rating > surface_rating):
        return air_track.ID
    elif (surface_rating > 0):
        return surface_track.ID
    else:
        return -1
            
# get target bearing in deg
def GetTargetBearing(UI):
    track_info = UI.GetTargetTrackInfo()
    lat = track_info.Lat
    lon = track_info.Lon
    bearing = UI.GetHeadingToDatum(lon,lat)
    return bearing

# set heading relative to target bearing
def SetHeadingOffTarget(UI, heading_offset):
    heading = GetTargetBearing(UI)
    
    heading = heading + heading_offset
    if (heading > 360.0):
        heading = heading - 360.0
    elif (heading < -180):
        heading = heading + 360.0
        
    UI.SetHeading(heading)
    return

# return 0 if no weapons are available that are effective vs. target
# return 1 if weapon avail, but not in range
# return 2 if weap avail and in range
def ConsiderTarget(UI):
    target_id = UI.GetTarget()
    if target_id == -1:
        return

    # check if effective weapon is available
    target_info = UI.GetTargetTrackInfo()
    launcher_info = UI.GetBestLauncher()
    launcher = launcher_info.Launcher
    if (launcher == -1):   # if (no effective launcher is available)
        return 0
    engaged_count = target_info.GetEngagedCount()
    UI.DisplayMessage('target id: %d, engaged count: %d\n' % (target_id, engaged_count))
    launch_range = launcher_info.Range_km  # reference max range, use for launch decision
    target_range = UI.GetRangeToTarget()
    if (target_range > launch_range):
        return 1
    else:
        return 2

def ScoreTarget(UI, target_info):
    target_id = target_info.ID
    if target_id == -1:
        return 0

    # check if effective weapon is available
    launcher_info = UI.GetBestLauncher()
    launcher = launcher_info.Launcher
    if (launcher == -1):   # if (no effective launcher is available)
        return 0
    engaged_count = target_info.GetEngagedCount()
    if ((engaged_count > 2) or target_info.IsDestroyed()):
        return 0
    
    launch_range = launcher_info.Range_km  # reference max range, use for launch decision
    target_range = UI.GetRangeToTarget()
    if (target_range > launch_range):
        score = 1 + 0.001 * (target_range - launch_range)
    else:
        score = 3 + 0.001 * target_range
        
    score = score * 0.2 * (5-engaged_count)
    return score

def InterceptTarget(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryText('Description', 'Close distance and engage target') 
        TI.SetMemoryValue(2, 0)  # 0 if target not engaged, 1 otherwise
        TI.SetMemoryValue(4, 0)  # launcher is fire and forget (flee after attack)
        TI.SetUpdateInterval(15.0)
    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)

    
    targetid = UI.GetTarget()
    if targetid == -1:
        TI.EndTask()
        return

    target_info = UI.GetTargetTrackInfo()
    if (not target_info.IsValid()):
        UI.DisplayMessage('Ending attack, lost target')
        TI.EndTask()
        return

    if (target_info.IsDestroyed()):
        UI.DisplayMessage('Ending attack, target destroyed')
        TI.EndTask()
        return
        
    if (target_info.IsGround() and UI.IsAir()):
        UI.AddTask('GroundStrike', 3.0, 0)
        BB.WriteGlobal('DatumLongitude', '%f' % target_info.Lon)
        BB.WriteGlobal('DatumLatitude', '%f' % target_info.Lat)
        TI.EndTask()
        return

    
    # check if effective weapon is available
    launcher_info = UI.GetBestLauncher()
    launcher = launcher_info.Launcher
    if (launcher == -1):   # if (no effective launcher is available)
        UI.DisplayMessage('Aborting attack, no effective weapons')
        UI.SetTarget(-1)   # clear target
        TI.EndTask()
        return

    # debug_file = open('log/pydebug.txt', 'a')
    # debug_file.write('target: %d, engaged: %d\n' % (targetid, target_info.GetEngagedCount()) )
    # debug_file.close()
               
    
    # if sub, check launch depth requirements
    adjust_depth = 0
    if (UI.IsSub()):
        if (-UI.GetAlt() > launcher_info.MaxDepth_m):
            adjust_depth = 1
            
    
    # use weapon if in range
    launch_range = launcher_info.Range_km  # reference max range, use for launch decision
    targetrange = UI.GetRangeToTarget()
    if (targetrange > launch_range):
        TTI = UI.SetHeadingToInterceptTarget()
        if (UI.IsSub()):
            SetFractionalSpeed(UI, 0.5)
        elif (UI.IsAir() and target_info.IsSub()):
            SetFractionalSpeed(UI, 0.5)
        elif (UI.HasThrottle() and (UI.GetFuel() > 0.5)):
            UI.SetThrottle(1.1) # use AB if enough fuel left           
        else:
            UI.SetSpeedToMax()
        UI.SetActionText('Int %d (%3.0f s)' % (targetid, TTI))
        if (targetrange - launch_range > 2.0):
            TI.SetUpdateInterval(15.0)
        else:
            TI.SetUpdateInterval(8.0)
    elif (adjust_depth):
        UI.SetAlt(-launcher_info.MaxDepth_m + 1)
    else:
        target_is_engaged = TI.GetMemoryValue(2)
        if target_is_engaged:
            # wait to re-engage until all engaging weapons are gone
            if (target_info.GetEngagedCount() > 0):
                UI.SetActionText('Atk-wait')
                
                if UI.IsAir():
                    if (TI.GetMemoryValue(4) == 1): # flee target if fire-and-forget weapon
                        SetHeadingOffTarget(UI, 180.0)  # set heading 180 deg from current target bearing
                        SetFractionalSpeed(UI, 1.0)
                    else:
                        SetHeadingOffTarget(UI, 30.0)  # set heading 30 deg from current target bearing
                        SetFractionalSpeed(UI, 0.5)
                return
            else:
                TI.SetMemoryValue(2, 0)     # re-engage target
                if UI.IsAir():
                    SetFractionalSpeed(UI, 1.0)
                
        # attack target
        can_radiate = GetSensorControl(BB)
        if (can_radiate and not UI.IsSub()):
            ActivateAllSensors(UI)
        else:
            ActivatePassiveSensors(UI)

        range_km = 0.0

        launch_mode = launcher_info.LaunchMode   # 0 - datum, 1 - seeker FF, 2 - seeker non-FF, 3 - bomb, 4 - error

        engage_limit = GetEngageLimit(target_info)
        launch_qty = engage_limit - target_info.GetEngagedCount()
            
        if launch_mode == 0:  # datum launch
            lat = target_info.Lat
            lon = target_info.Lon
            alt = target_info.Alt
            UI.HandoffTargetToLauncher(launcher) # to store intended target
            UI.SendDatumToLauncher(lon,lat,alt,launcher)
            UI.Launch(launcher, launch_qty)
            TI.SetMemoryValue(2, 1)
            TI.SetMemoryValue(4, 1) # fire and forget
            UI.SetActionText('Launch D')
        elif (launch_mode == 1) or (launch_mode == 2):  # handoff to weapon seeker
            target_accepted = UI.HandoffTargetToLauncher(launcher)
            if (target_accepted):
                UI.Launch(launcher, launch_qty)
                TI.SetMemoryValue(2, 1)
                if (launch_mode == 1):
                    TI.SetMemoryValue(4, 1) # fire and forget
                else:
                    TI.SetMemoryValue(4, 0) # need platform guidance
                    
                UI.SetActionText('Launch H')
        elif (launch_mode == 3):
            UI.DisplayMessage('Starting bomb run')
            AddBombTargetTask(UI)
            TI.EndTask()
        elif (launch_mode == 4):
            UI.DisplayMessage('No support for aircraft gun attack')
            TI.EndTask()
        else:
            UI.DisplayMessage('Bad launch mode (%d), aborting attack' % launch_mode)
            TI.EndTask()

# move to close range and form air formation
def AirFormation(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    
    leader = BB.ReadMessage('FormationLeader')
    #UI.DisplayMessage('Leader is %s' % leader)
    
    UI.SetFormationLeader(long(leader))
    UI.SetFormationPosition(0.2, 0.05, 3.1416, 0.05)
    UI.SetFormationMode(1) # 1 is follow, 2 is sprint-drift
    TI.EndTask()
    
# intercept and close with target, lining up on tail for easy gun shot
def IntC(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    TI.SetUpdateInterval(8.0)
    
    targetid = UI.GetTarget()
    if targetid == -1:
        TI.EndTask()
        return
        
    target_track = UI.GetTargetTrackInfo()
    if ((not target_track.IsValid()) or (target_track.IsDestroyed())):
        UI.SetSpeed(300)
        TI.EndTask()
        return
    
    range_km = UI.GetRangeToTarget()
    
    if ((range_km < 1.25) and (UI.GetFormationLeader() != targetid)): 
        UI.SetFormationLeader(targetid) # enter non-coop "formation" with target
        UI.SetFormationPosition(0.25, 0.2, 3.14, 0.2)
        UI.SetFormationMode(1) # 1 is follow, 2 is sprint-drift
        return
        
    goal_speed = target_track.Speed
    if (range_km > 3):
        TI.SetUpdateInterval(8.0)
        target_track.Offset(-0.5, target_track.Heading_rad)
        goal_speed = target_track.Speed + 100 + 40*(range_km - 3)
        UI.SetHeadingToInterceptTrack(target_track)
    elif (range_km > 0.5):
        TI.SetUpdateInterval(3.0)
        target_track.Offset(-0.5, target_track.Heading_rad)
        goal_speed = target_track.Speed + 50 + 20*(range_km - 0.5)
        UI.SetHeadingToInterceptTrack(target_track)
    elif (range_km > 0.25):
        TI.SetUpdateInterval(2.0)
        goal_speed = target_track.Speed
        hdg_deg = UI.GetHeadingToDatum(target_track.Lon, target_track.Lat)
        UI.SetHeading(hdg_deg)
    else:
        goal_speed = target_track.Speed - 25
        hdg_deg = UI.GetHeadingToDatum(target_track.Lon, target_track.Lat)
        UI.SetHeading(hdg_deg)
        
    UI.SetSpeed(goal_speed)
    
    if ((target_track.Flags & 1) != 0):
        UI.SetAltitude(target_track.Alt)

# return max simultaneous weapon count to engage target with
def GetEngageLimit(target_info):
    if target_info.IsAir():
        return 1
    elif target_info.IsMissile():
        return 1
    elif target_info.IsSurface():
        return 15
    elif target_info.IsGround():
        return 20
    else:
        return 1

def GetStaleLimit(target_info):
    if target_info.IsAir():
        return 60
    elif target_info.IsMissile():
        return 45
    elif target_info.IsSurface():
        return 300
    elif target_info.IsGround():
        return 99999
    elif target_info.IsSub():
        return 300
    else:
        return 45        
        
# return 1 if launched, 0 otherwise
def EngageTargetWithLauncher(UI, launcher):
    launcher_info = UI.GetLauncherInfo(launcher)
    if (not launcher_info.IsValid()):
        return 0

    launch_mode = launcher_info.LaunchMode   # 0 - datum, 1 - seeker, 2 - bomb, 3 - other
    target_info = UI.GetTargetTrackInfo()

    engaged_count = target_info.GetEngagedCount()
    engage_limit = GetEngageLimit(target_info)
    launch_qty = engage_limit - engaged_count
    if (launch_qty <= 0):
        return 0
        
    launch_qty = 1 # only launch one at a time for spacing
        
    if launch_mode == 0:  # datum launch
        # if the Speed_mps is non-zero in launcher info, then adjust datum based on expected travel time and target speed and heading
        if (launcher_info.Speed_mps > 0):
            range_km = UI.GetRangeToTrack(target_info)
            travel_time_s = 1000.0 * range_km / launcher_info.Speed_mps
            travel_time_s = travel_time_s + 10.0 # add a little time for launch and altitude adjustment
            target_info = target_info.PredictAhead(travel_time_s)
        lat = target_info.Lat
        lon = target_info.Lon
        alt = target_info.Alt
        UI.HandoffTargetToLauncher(launcher) # to store intended target
        UI.SendDatumToLauncher(lon,lat,alt,launcher)
        UI.Launch(launcher, launch_qty)
        UI.SetActionText('Launch(D)')
        return 1
    elif (launch_mode == 1) or (launch_mode == 2) or (launch_mode == 4):  # handoff to active seeker
        target_accepted = UI.HandoffTargetToLauncher(launcher)
        if (target_accepted):
            UI.Launch(launcher, launch_qty)
            UI.SetActionText('Launch(H)')
            return 1
        else:
            return 0
    else:    
        UI.DisplayMessage('Unrecognized launch mode: %d' % launch_mode)
        return 0

# this task automatically added if task ends and unit is no longer tasks/needs orders
def AutoLoiter(TI):
    UI = TI.GetPlatformInterface()
    TI.SetUpdateInterval(30.0)
    if (UI.IsAir()):
        UI.SetHeading(UI.GetHeading() + 30.0)
        if (not UI.IsHelo()):
            alt_m = UI.GetAltitude()
            cruise_speed_kts = UI.GetCruiseSpeedForAltitude(alt_m)
            UI.SetSpeed(cruise_speed_kts)
        else:
            UI.SetSpeed(60.0)
    else:
        TI.SetUpdateInterval(300.0)
        if (UI.IsSub()):
            UI.SetSpeed(3.0)
            UI.SetHeading(UI.GetHeading() + 90.0)
        else:
            UI.SetHeading(UI.GetHeading() + 10.0)
    
def TestClimbCmd(TI):
    UI = TI.GetPlatformInterface()
    TI.SetUpdateInterval(30.0)
    
    iteration = TI.GetMemoryValue(1)
    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)
    
    if (UI.IsAir()):
        angle_deg = 10.0 * ((iteration % 10) - 1)
        UI.SetClimbDeg(angle_deg)
    else:
        TI.EndTask()
