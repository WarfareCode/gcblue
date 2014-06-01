##########################################
# Sub tactics
##########################################

from UnitCommands import *

# zig-zag patrol task
def SubPatrol(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryValue(2, UI.GetHeading())
        TI.SetMemoryValue(3, 0) # 0 is turn left next zig-zag, 1 turn right
        TI.SetMemoryValue(4, 255.0 + 90.0 * UI.Rand()) # random turn interval in seconds
        TI.SetMemoryText('Description', 'Perform surveillance along a zig-zag course')
        if (not UI.IsSub()):
            TI.EndTask()

    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)

    # activate all passive sensors
    # can_radiate = GetSensorControl(BB)

    ActivatePassiveSensors(UI)

    # return if conn is not available
    if (not GetConnControl(BB)):   
        return 

    # if at periscope depth and battery is not fully charged, activate snorkel and set speed slow
    # if at periscope depth and battery is fully charged, stop snorkeling, and set depth to deep
    # if deep and battery is nearly empty, set depth to periscope depth

    SI = UI.GetSubInterface() # get sub interface object

    bottomDepth = -UI.GetTerrainElevation()
    maxPatrolDepth = SI.GetMaxDepth() - 30
    if (bottomDepth > 210):
        patrolDepth = 300
    else:
        patrolDepth = bottomDepth - 30

    if (patrolDepth > maxPatrolDepth):
        patrolDepth = maxPatrolDepth
    
    UI.SetSpeed(5) # default patrol speed
    updateInterval = TI.GetMemoryValue(4)


    if (SI.IsDieselElectric()):
        battery = SI.GetBatteryFraction()
        if (SI.IsAtPeriscopeDepth()):
            if (battery < 0.99):
                SI.SetSnorkelState(1)
                UI.SetSpeed(3)
            else:
                SI.SetSnorkelState(0)
                UI.SetSpeed(5)
                UI.SetAlt(-patrolDepth)
        elif (battery < 0.2):
            SI.GoToPeriscopeDepth()
            UI.SetSpeed(5)
            updateInterval = 0.5 * updateInterval
    else: # nuclear sub
        UI.SetAlt(-patrolDepth)




    if (TI.GetMemoryValue(3) == 0):
        new_heading = TI.GetMemoryValue(2) - 30
        TI.SetMemoryValue(3, 1)
    else:
        new_heading = TI.GetMemoryValue(2) + 30
        TI.SetMemoryValue(3, 0)

    UI.SetHeading(new_heading)
    TI.SetUpdateInterval(updateInterval)
    UI.SetActionText('Patrol')


# torpedo evasion tactics
def EvadeTorpedoes(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryText('Description', 'Evade incoming torpedoes') 

    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)


    # find closest torpedo within 12 km (or bearing-only torpedo track with longest track life)
    # if any found, take conn control, set depth deep, set speed to max, set course to evade
    # (when available) if any found that are within 1 km(?), release countermeasure
    # if no torpedoes found and have conn control, release conn control

        
def SubEvade(TI):
    UI = TI.GetPlatformInterface()
    
    for n in range(0,UI.GetSensorCount()):
        sensor = UI.GetSensorInfo(n)
#        UI.DisplayMessage('Sensor Type %d' % sensor.type)
        if sensor.type == 4:
            UI.SetSensorState(n, 1)

    threatExists, track = GetClosestTorpedoThreat(UI)

    #track = UI.GetClosestTrack(15, 130, 3, 0)  # 15 km range, 130 is torpedo class, 3 is hostile, 0 ignores "engagement count"
    if (not threatExists):
        TI.SetUpdateInterval(15.0)
        if (TI.GetMemoryValue(1) > 0): # previously was evading, resume speed, heading, alt
            if ((UI.GetTime() - TI.GetMemoryValue(5)) > 120.0): # wait some time before stopping evade
                TI.SetMemoryValue(1, 0)
                UI.SetSpeed(TI.GetMemoryValue(2)) 
                UI.SetHeading(TI.GetMemoryValue(3))
                UI.SetAlt(TI.GetMemoryValue(4))
        return

    if (TI.GetMemoryValue(1) == 0):
        TI.SetMemoryValue(1, 1)
        TI.SetMemoryValue(2, UI.GetSpeed())
        TI.SetMemoryValue(3, UI.GetHeading())
        TI.SetMemoryValue(4, UI.GetAlt())
        TI.SetMemoryValue(5, UI.GetTime())
        
    TI.SetUpdateInterval(3.0)
    
    range_km = UI.GetRangeToTrack(track)
    bearing_deg = UI.GetHeadingToDatum(track.Lon, track.Lat)

    #UI.DisplayMessage('Missile %.1f km' % range_km)
    
    if (range_km < 1.0):
        # break left or right to force high turn rate from torpedo
        dRight_deg = 90 + bearing_deg - UI.GetHeading()
        if (dRight_deg > 180):
            dRight_deg = dRight_deg - 360
        elif (dRight_deg < -180):
            dRight_deg = dRight_deg + 360

        if (abs(dRight_deg) < 90):
            UI.SetHeading(bearing_deg + 90)
        else:
            UI.SetHeading(bearing_deg - 90)    
    elif (range_km < 10.0):
        UI.SetHeading(bearing_deg + 180) # run from torpedo
        
    terrain_m = UI.GetTerrainElevation()
    UI.SetSpeedToMax()
    UI.SetAlt(terrain_m + 15) # go deep
        
def GetClosestTorpedoThreat(UI):
    threatTrack = []
    threatExists = 0
    maxRange_km = 15
    minBearingRate_radps = 0.0003 # 0.5 deg over 30 sec
    closestRange_km = 9999
    trackList = UI.GetTrackList(130, maxRange_km, 3)
    nTracks = trackList.Size()
    for n in range(0, nTracks):
        track_info = trackList.GetTrack(n)
        
        trackLife_s = track_info.GetTrackLife()
        if (track_info.IsBearingOnly()):
            range_km = 5
            lowBearingRate = track_info.IsBearingRateValid() and (abs(track_info.BearingRate_radps) <= minBearingRate_radps)
        else:
            range_km = UI.GetRangeToTrack(track_info)
            heading_valid = (track_info.Flags & 0x04) != 0
            if (heading_valid):
                bearingToPlatform_rad = track_info.BearingToRad(UI.GetLongitude(), UI.GetLatitude())
                if (cos(track_info.Heading_rad-bearingToPlatform_rad) > 0.966): # within 15 deg
                    lowBearingRate = 1
                else:
                    lowBearingRate = 0
            else:
                lowBearingRate = (range_km < 2)
            
        if ((trackLife_s > 15.0) and (range_km < closestRange_km) and lowBearingRate and (not track_info.IsStale())):
            threatTrack = track_info
            closestRange_km = range_km
            threatExists = 1
            
    return (threatExists, threatTrack)
        
# surface and charge battery when necessary
def SubBattery(TI):
    UI = TI.GetPlatformInterface()
    
    SI = UI.GetSubInterface()
    if ((not SI.IsValid()) or (not SI.IsDieselElectric())):
        TI.EndTask()
        return
        
    TI.SetUpdateInterval(100.0)
        
    battery_fraction = SI.GetBatteryFraction()
    if (battery_fraction < 0.05):
        if (SI.IsAtPeriscopeDepth()):
            SI.SetSnorkelState(1)
            UI.SetSpeed(4.0)
        else:
            TI.SetMemoryValue(1, UI.GetAlt())
            SI.GoToPeriscopeDepth()
    elif (battery_fraction >= 1.0):
        if (SI.IsSnorkeling()):
            SI.SetSnorkelState(0)
            alt_m = TI.GetMemoryValue(1)
            if (alt_m < 0):
                UI.SetAlt(alt_m)
                
# set speed to avoid cavitation
def AvoidCav(TI):
    UI = TI.GetPlatformInterface()
    SI = UI.GetSubInterface()
    if (not SI.IsValid()):
        TI.EndTask()
        return
        
    threatExists, track = GetClosestTorpedoThreat(UI)
    if (threatExists):
        return
    
    climb_deg = UI.GetClimbDeg()
    
    if (climb_deg < 0.1):
        TI.SetUpdateInterval(50.0)
        maxQuiet_kts = SI.GetCavitatingSpeed(-UI.GetAltitude()) - 0.5
    else:
        TI.SetUpdateInterval(10.0)
        upcomingDepth_m = -UI.GetAltitude() - (0.135 * UI.GetSpeed() * climb_deg ) # 0.135 is about 15 sec of depth change
        maxQuiet_kts = SI.GetCavitatingSpeed(upcomingDepth_m) - 0.5
        
    if (UI.GetSpeed() > maxQuiet_kts):
        UI.SetSpeed(maxQuiet_kts)
