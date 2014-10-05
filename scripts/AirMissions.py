
from GCBcommon import *
from UnitCommands import *

import math



# patrol relative to airbase or carrier location
def CAP(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryValue(2, UI.GetHeading())
        TI.SetMemoryValue(3, 0) # 1 is heading to station, 0 patroling
        TI.SetMemoryValue(4, 30.0 + 15.0 * UI.Rand()) # random turn interval in seconds
        TI.SetMemoryText('Description', 'Perform surveillance along a zig-zag course') 

        patrol_range_km = GetMessageParam(BB, 'PatrolRange_km')
        patrol_az_rad = deg_to_rad * GetMessageParam(BB, 'PatrolAzimuth_deg') # rel to north
        anchor_id = GetMessageParam(BB, 'AnchorPlatformId') # platform id to center patrol about
        
        TI.SetMemoryValue(10, patrol_range_km)
        TI.SetMemoryValue(11, patrol_az_rad)
        TI.SetMemoryValue(12, anchor_id)
        

    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)

    # if low on fuel or out of ammo, rtb
    if ((UI.GetFuel() < 0.55) or (not UI.IsEquippedForTargetType(0x0020))):
        UI.DeleteTask('EngageAll')
        TI.EndTask()
        AddRTBtask(UI, '', 0.55, 0)
        return
    
    # activate all sensors
    can_radiate = GetSensorControl(BB)
    if (can_radiate and not UI.IsSub()):
        ActivateAllSensors(UI)
    else:
        ActivatePassiveSensors(UI)

    # return if conn is not available
    if (not GetConnControl(BB)):   
        return 

    # check for nearby air target
    intercept_target = 0
    closest_id, closest_range, closest_bearing = ClosestOfTypeUnengaged(UI, 0x0020, 120)
    if (closest_id != -1):
        intercept_target = 1
        UI.SetHeading(closest_bearing) # lag intercept
        if (UI.GetFuel() > 0.7):
            UI.SetThrottle(1.1)
        else:
            UI.SetThrottle(1.0)
        UI.SetActionText('Intercept %d' % closest_id)
        return

    patrol_range_km = GetMessageParam(BB, 'PatrolRange_km')
    patrol_az_rad = deg_to_rad * GetMessageParam(BB, 'PatrolAzimuth_deg') # rel to north
    anchor_id = TI.GetMemoryValue(12)

    if (UI.IsAir()):
        if (UI.GetAlt() < 5500):
            UI.SetThrottle(1.0)
            SetAlt(UI, 6000)
        else:
            UI.SetThrottle(0.8)

    # calculate station point
    anchor_track = UI.GetTrackById(long(anchor_id))
    anchor_track.Offset(patrol_range_km, patrol_az_rad)
    if (not anchor_track.IsValid()):
        TI.EndTask()
        return
    
    station_lon = anchor_track.Lon
    station_lat = anchor_track.Lat


    station_range = UI.GetRangeToDatum(station_lon, station_lat)
    
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
        UI.SetActionText('-> Station')
        TI.SetUpdateInterval(10.0)
    else: 
        new_heading = UI.GetHeading() + 30
        TI.SetMemoryValue(3, 0)  # to indicate traveling to station
        UI.SetActionText('CAP')
        TI.SetUpdateInterval(TI.GetMemoryValue(4))

    UI.SetHeading(new_heading)
    




