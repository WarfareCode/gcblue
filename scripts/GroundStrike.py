from AIcommon import *
from UnitCommands import *
import math

ground_engage_limit = 20


# returns id of closest target to specified position, matching targetFlags
# returns -1 if none
def GetTargetNear(UI, lon_rad, lat_rad, targetFlags, maxRange_km):
    # target flags: 1 surface, 2 air, 4 land, 8 missile, 16 sub
    classMask = 0
    if ((targetFlags & 1) != 0):
        classMask = classMask | 0x0010
    if ((targetFlags & 4) != 0):
        classMask = classMask | 0x0100    
    if ((targetFlags & 16) != 0):
        classMask = classMask | 0x0080
    
    searchRange_km = 200
    track_list = UI.GetTrackList(classMask, searchRange_km, 100) # 100 for "valid by ROE"

    current_time = UI.GetTime()
    nTracks = track_list.Size()

    best_range = 1e6
    best_target = -1
    best_engaged_count = 99
    
    for n in range(0, nTracks):
        track_info = track_list.GetTrack(n)
        track_id = track_info.ID
        staleness = current_time - track_info.Time
        is_destroyed = track_info.IsDestroyed()
        bearing_only = track_info.IsBearingOnly() or (track_info.TrackErrorKm() > 20)
        engaged_count = track_info.GetEngagedCount()
        rangeFromTarget_km = track_info.RangeToKm(lon_rad, lat_rad)
        
        max_engaged_count = 20
        max_staleness = 99999.0
        #UI.DisplayMessage('Track %d, %.0f/%d/%d' % (track_id, staleness, bearing_only, engaged_count))

        if ((rangeFromTarget_km <= maxRange_km) and (engaged_count < max_engaged_count) and (staleness < max_staleness) and (not bearing_only) and (not is_destroyed)):
            is_better = (engaged_count < best_engaged_count)
            is_better = is_better or ((engaged_count == best_engaged_count) and (rangeFromTarget_km < 0.9*best_range))
            
            if (is_better):
                best_range = rangeFromTarget_km
                best_target = track_id
                best_engaged_count = engaged_count

    return best_target


def SetAltitudeAndSpeedForLauncher(UI, launcher_idx):
    min_alt_m = UI.GetTerrainElevation() + 300
    max_alt_m = 99999

    launcher_info = UI.GetLauncherInfo(launcher_idx)
    if (not launcher_info.IsValid()):
        return

    min_alt_m = max(launcher_info.MinLaunchAlt_m, min_alt_m)
    max_alt_m = min(launcher_info.MaxLaunchAlt_m, max_alt_m)
    
    alt_m = UI.GetAltitude()
    if (alt_m < min_alt_m):
        UI.SetAltitude(min_alt_m + 50)
    elif (alt_m > max_alt_m):
        UI.SetAltitude(max_alt_m - 50)
    
    if (launcher_info.LaunchMode == 4): # gun strafe or rocket attack
        if (launcher_info.MaxRange_km > 3.0):
            UI.SetAltitude(min_alt_m + 100*(launcher_info.MaxRange_km - 3.0))
        else:
            UI.SetAltitude(min_alt_m)
    
    if (UI.HasThrottle() and (launcher_info.LaunchMode == 3)):
        UI.SetThrottle(max(UI.GetThrottle(), 0.75)) # use 75% throttle for dumb bomb runs
    else:
        UI.SetSpeedToMax()
        
            
def IsTargetInRange(UI, lon_rad, lat_rad, launcher_idx):
    #bool IsTargetInRange(int nLauncher, float lon_rad, float lat_rad, float alt_m, float targetHeading_rad, float targetSpeed_kts);
    alt_m = UI.GetMapTerrainElevation(lon_rad, lat_rad) # since we're attacking a ground target
    alt_m = max(alt_m, 0)
    targetHeading_rad = 0.0 # doesnt matter for non-moving ground target
    targetSpeed_kts = 0.0
    return UI.IsTargetInRange(int(launcher_idx), lon_rad, lat_rad, alt_m, targetHeading_rad, targetSpeed_kts)

def AttackDatum(UI, lon_rad, lat_rad, launcher_idx):
    launcher_info = UI.GetLauncherInfo(launcher_idx)
    launch_mode = launcher_info.LaunchMode
    launch_qty = 10
    searchRange_km = 3.0
    target_id = GetTargetNear(UI, lon_rad, lat_rad, 4, searchRange_km)
    if (target_id != -1):
        UI.SetTarget(target_id)
    if launch_mode == 0:  # datum launch
        lat = lat_rad
        lon = lon_rad
        alt_m = UI.GetMapTerrainElevation(lon, lat) # since we're attacking a ground target
        alt_m = max(alt_m, 0)
        UI.SendDatumToLauncher(lon,lat,alt_m,launcher_idx)
        UI.Launch(launcher_idx, launch_qty)
        UI.SetActionText('Launch-D')
    elif (launch_mode == 1) or (launch_mode == 2):  # handoff to weapon seeker
        target_accepted = UI.HandoffTargetToLauncher(launcher_idx)
        if (target_accepted):
            UI.Launch(launcher_idx, launch_qty)
            UI.SetActionText('Launch-H')
    elif (launch_mode == 3):
        UI.DisplayMessage('Need bomb run')
    elif (launch_mode == 4):
        lat = lat_rad
        lon = lon_rad
        alt_m = UI.GetMapTerrainElevation(lon, lat) # since we're attacking a ground target
        alt_m = max(alt_m, 0)
        UI.SendDatumToLauncher(lon,lat,alt_m,launcher_idx)
        UI.Launch(launcher_idx, launch_qty)
        UI.SetActionText('Strafe')    
        
def DropBombs2(UI, tgt_lon, tgt_lat, tgt_alt, qty):
    UI.DisplayMessage('Dropping bombs')
    nLaunchers = UI.GetLauncherCount()

    for n in range(0, nLaunchers):
        launcher_info = UI.GetLauncherInfo(n)
        if (launcher_info.LaunchMode == 3):
            if (launcher_info.IsNuclear == 1):
                qty = 1 # force qty to 1 if nuclear
            UI.SendDatumToLauncher(tgt_lon,tgt_lat,tgt_alt,n)
            UI.Launch(n, qty)

# return maximum range of ground weapon in km (0 if none) and corresponding launcher_idx
def GroundWeaponMaxRangeKm(UI):
    maxRange_km = 0
    nLaunchers = UI.GetLauncherCount()
    launcher_idx = -1
    for n in range(0, nLaunchers):
        info = UI.GetLauncherInfo(n)
        # TargetFlags 0x04 is effective vs land flag
        if ((info.TargetFlags & 4) != 0) and (info.Quantity > 0) and (info.MaxRange_km > maxRange_km):
            if (info.LaunchMode < 5):
                maxRange_km = info.MaxRange_km
                launcher_idx = n
        
    return (maxRange_km, launcher_idx)

def GetHeadingError(UI, target_heading_deg):
    current_heading = UI.GetHeading() # deg
    heading_error = target_heading_deg - current_heading
    if (heading_error < -180):
        heading_error = heading_error + 360
    elif (heading_error > 180):
        heading_error = heading_error - 360
    return heading_error
    
# more general version of BombDatum, attacks datum and targets near datum with ground weapons
def GroundStrike(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    if (not GetConnControl(BB)):
        return

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryText('Description', 'Ground strike')
        TI.SetMemoryValue(2, 1) # state: 1 - search and close, 2 - guided weapon attack, 3 - turn away/maintain fire control, 4 - gravity bomb run approach, 5 - gravity bomb release
        datum_lon = GetMessageParam(BB, 'DatumLongitude')
        datum_lat = GetMessageParam(BB, 'DatumLatitude')
        TI.SetMemoryValue(10, datum_lon)
        TI.SetMemoryValue(11, datum_lat)
        if ((not UI.IsAir()) or ((datum_lon == 0) and (datum_lat == 0))):
            TI.EndTask()
            return
        else:
            UI.SetSpeedToMax()
        TI.SetMemoryValue(1, 1)
        return

    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)

    tgt_lon = TI.GetMemoryValue(10)
    tgt_lat = TI.GetMemoryValue(11)
    attack_state = TI.GetMemoryValue(2)
    
    tgt_alt = UI.GetMapTerrainElevation(tgt_lon, tgt_lat) # since we're bombing a ground target (does track have same altitude value?)
    tgt_alt = max(tgt_alt, 0)
    
    if (attack_state == 1): # search and close to target
        UI.SetActionText('Searching')   
        # search for a sensor target near datum
        search_range_km = 20 # go after targets within this range of strike coordinates
        target_id = GetTargetNear(UI, tgt_lon, tgt_lat, 4, search_range_km)
        if (target_id != -1):
            target_track = UI.GetTrackById(target_id)
            tgt_lon = target_track.Lon
            tgt_lat = target_track.Lat
        else: # no targets found
            UI.DisplayMessage('No target found')
            TI.EndTask()
            return
        TI.SetMemoryValue(20, tgt_lon) # set current best target coords
        TI.SetMemoryValue(21, tgt_lat)
               
        # adjust heading to target
        tgt_bearing = UI.GetHeadingToDatum(tgt_lon, tgt_lat)
        UI.SetHeading(tgt_bearing)

        targetRange_km = UI.GetRangeToDatum(tgt_lon, tgt_lat)  # horizontal range in km
        maxRange_km, launcher_idx = GroundWeaponMaxRangeKm(UI)
        TI.SetMemoryValue(22, launcher_idx)
        if (maxRange_km == 0):
            TI.EndTask()
            return
        
        #UI.DisplayMessage('max range is %f km, launcher %d' % (maxRange_km, launcher_idx))
        SetAltitudeAndSpeedForLauncher(UI, launcher_idx)
        
        if (targetRange_km > (maxRange_km + 5.0)):
            own_speed_kmps = 0.00051444444 * UI.GetSpeed() # get speed in km/s
            timeLeft_s = (targetRange_km - maxRange_km - 5.0) / own_speed_kmps
            TI.SetUpdateInterval(min(timeLeft_s, 40.0))
            next_attack_state = 1 # continue search
        else:
            info = UI.GetLauncherInfo(launcher_idx)
            TI.SetUpdateInterval(20.0)
            if (info.LaunchMode == 3):
                next_attack_state = 4 # start gravity bomb run
            elif (info.LaunchMode == 4):
                next_attack_state = 6 # strafe or rocket attack
            else:
                next_attack_state = 2
        TI.SetMemoryValue(2, next_attack_state)
        return
    if (attack_state == 2): # guided weapon attack
        tgt_lon = TI.GetMemoryValue(20) # get current best target coords
        tgt_lat = TI.GetMemoryValue(21)
        launcher_idx = int(TI.GetMemoryValue(22))
        tgt_bearing = UI.GetHeadingToDatum(tgt_lon, tgt_lat)
        UI.SetHeading(tgt_bearing)
        if (IsTargetInRange(UI, tgt_lon, tgt_lat, launcher_idx)):
            AttackDatum(UI, tgt_lon, tgt_lat, launcher_idx)
            next_attack_state = 3
            TI.SetUpdateInterval(2.0)
        else:
            next_attack_state = 2
            TI.SetUpdateInterval(10.0) # try again in 10 sec
        TI.SetMemoryValue(2, next_attack_state)
        return
    if (attack_state == 3): # turn away/maintain fire control
        fireControlInfo = UI.GetFireControlInfo()
        if (fireControlInfo.weaponsOut > 0):
            next_attack_state = 3
        else:
            next_attack_state = 1
        tgt_lon = TI.GetMemoryValue(20) # get current best target coords
        tgt_lat = TI.GetMemoryValue(21)
        tgt_bearing = UI.GetHeadingToDatum(tgt_lon, tgt_lat) # returns deg
        UI.SetHeading(tgt_bearing + 90) # rough circle on target
        UI.SetSpeed(UI.GetCruiseSpeedForAltitude(UI.GetAlt()))
        TI.SetUpdateInterval(45.0)
        TI.SetMemoryValue(2, next_attack_state)
        return
    if (attack_state == 4): # bombing run approach
        tgt_lon = TI.GetMemoryValue(20) # get current best target coords
        tgt_lat = TI.GetMemoryValue(21)       
        launcher_idx = int(TI.GetMemoryValue(22))
        info = UI.GetLauncherInfo(launcher_idx)
        if ((info.LaunchMode != 3) or (info.Quantity == 0)):
            UI.DisplayMessage('Aborting bomb run, no gravity bombs')
            next_attack_state = 1
            TI.SetMemoryValue(2, next_attack_state)
            return
            
        tgt_alt = UI.GetMapTerrainElevation(tgt_lon, tgt_lat) # since we're bombing a ground target (does track have same altitude value?)
        tgt_alt = max(tgt_alt, 0)
        tgt_range_m = 1000 * UI.GetRangeToDatum(tgt_lon, tgt_lat)  # horizontal range in m
        tgt_range_m = tgt_range_m - 10  # move in a little to spread bombs on either side
        own_speed_mps = 0.51444444 * UI.GetSpeed() # get speed in m/s
        own_alt_m = UI.GetAlt()
        d_alt_m = own_alt_m - tgt_alt
    
        if (d_alt_m < 0):  # normally should not happen
            SetAlt(UI, tgt_alt + 2000.0)
            UI.SetHeading(UI.GetHeading() + 180)
            TI.SetUpdateInterval(180.0) # try search again in 3 min
            next_attack_state = 1
            TI.SetMemoryValue(2, next_attack_state)
            return

        t_flight = math.sqrt(0.20394324 * (own_alt_m - tgt_alt))
        release_range_m = t_flight * own_speed_mps
        range_left_m = tgt_range_m - release_range_m
        if (range_left_m < 0):
            UI.DisplayMessage('Aborting bomb run. Too close, too fast or too high')
            UI.SetHeading(UI.GetHeading() + 180)
            TI.SetUpdateInterval(180.0) # try search again in 3 min
            next_attack_state = 1
            TI.SetMemoryValue(2, next_attack_state)
            return
        # calculate time to release
        t_release = range_left_m / own_speed_mps
        if (t_release < 10):
            TI.SetUpdateInterval(t_release)
            next_attack_state = 5 # release bombs next update
            UI.SetActionText('Away %.0f s' % t_release)
            TI.SetMemoryValue(2, next_attack_state)
        else:
            TI.SetUpdateInterval(9.0)
            UI.SetActionText('Bomb %.0f s' % t_release)
        return
    if (attack_state == 5): # gravity bomb release
        tgt_lon = TI.GetMemoryValue(20) # get current best target coords
        tgt_lat = TI.GetMemoryValue(21)
        tgt_alt = UI.GetMapTerrainElevation(tgt_lon, tgt_lat) # since we're bombing a ground target (does track have same altitude value?)
        tgt_alt = max(tgt_alt, 0)        
        DropBombs2(UI, tgt_lon, tgt_lat, tgt_alt, 8)
        next_attack_state = 3
        TI.SetMemoryValue(2, next_attack_state)
        UI.SetActionText('')
        return
    if (attack_state == 6): # gun or rocket strafe attack
        tgt_lon = TI.GetMemoryValue(20) # get current best target coords
        tgt_lat = TI.GetMemoryValue(21)
        launcher_idx = int(TI.GetMemoryValue(22))
        info = UI.GetLauncherInfo(launcher_idx)
        fov_deg = info.SectorWidth
        
        tgt_bearing = UI.GetHeadingToDatum(tgt_lon, tgt_lat) # deg
        heading_error = GetHeadingError(UI, tgt_bearing)
        abs_heading_error = abs(heading_error)
        UI.SetHeading(tgt_bearing)
        
        if (abs_heading_error > 90): # need to reposition and reattack
            UI.SetHeading(tgt_bearing + 180)
            next_attack_state = 1
            TI.SetMemoryValue(2, next_attack_state)
            TI.SetUpdateInterval(90.0)
            return

        if (abs_heading_error < (0.4*fov_deg)) and (IsTargetInRange(UI, tgt_lon, tgt_lat, launcher_idx)):
            AttackDatum(UI, tgt_lon, tgt_lat, launcher_idx)
            next_attack_state = 1
            TI.SetUpdateInterval(90.0)
        else:
            next_attack_state = 6
            TI.SetUpdateInterval(3.0) # wait and try again
        TI.SetMemoryValue(2, next_attack_state)
        return




