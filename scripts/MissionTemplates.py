from math import *

deg_to_rad = 0.01745329252

# find closest corner of patrol area
def GetClosestCorner(lon1, lat1, lon2, lat2, base_track):
    dlon1 = abs(lon1-base_track.Lon)
    if (dlon1 > pi):
        dlon1 = 2*pi - dlon1
    dlon2 = abs(lon2-base_track.Lon)
    if (dlon2 > pi):
        dlon2 = 2*pi - dlon2
    if (dlon1 < dlon2):
        lon_closest = lon1
    else:
        lon_closest = lon2
    dlat1 = abs(lat1-base_track.Lat)
    dlat2 = abs(lat2-base_track.Lat)
    if (dlat1 < dlat2):
        lat_closest = lat1
    else:
        lat_closest = lat2
    return (lon_closest, lat_closest)
    
    
def SetAreaPatrolMission(UI, lon1, lat1, lon2, lat2, mission_id):    
    if ((not UI.HasFlightPort()) or (mission_id == -1)):
        return
    FP = UI.GetFlightPortInfo()
    mission_type = FP.GetMissionType(mission_id)
    if (mission_type == 'ASW-Helo'):
        SetASWHeloPatrolMission(UI, lon1, lat1, lon2, lat2, mission_id)
        return
    
    FP.ClearMissionWaypoints(mission_id)
    
    area_string = '%f,%f,%f,%f,%f,%f,%f,%f' % (lon1, lat1, lon1, lat2, lon2, lat2, lon2, lat1)
    FP.SetMissionPatrolArea(mission_id, area_string)
    
    base_id = UI.GetPlatformId()
    base_track = UI.GetTrackById(base_id)
    
    # find closest corner of patrol area
    lonc, latc = GetClosestCorner(lon1, lat1, lon2, lat2, base_track)

    FP.AddMissionWaypointAdvanced(mission_id, base_track.Lon+0.001, base_track.Lat+0.001, 2000, 200)
    FP.AddMissionWaypointTask(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointTask(mission_id, 0, 'EngageAll')
    
    FP.AddMissionWaypointAdvanced(mission_id, lonc, latc, 3000, 300)
    FP.AddMissionWaypointTask(mission_id, 1, 'AirPatrolArea')
    FP.AddMissionWaypointTask(mission_id, 1, 'EngageAll')
    
    
    # if base is surface ship, then set all waypoints relative to base
    if (UI.IsSurface()):
        FP.SetMissionPatrolAnchor(mission_id, UI.GetName(), 2)
        FP.TransformToRelativePatrolArea(mission_id)
        nWaypoints = FP.GetMissionWaypointCount(mission_id)
        for n in range(0, nWaypoints):
            FP.EditMissionWaypointReference(mission_id, n, 2, base_id)
    
    UI.UpdateMissionEditGraphics()
    

def SetASWHeloPatrolMission(UI, lon1, lat1, lon2, lat2, mission_id):    
    if ((not UI.HasFlightPort()) or (mission_id == -1)):
        return
    FP = UI.GetFlightPortInfo()
    mission_type = FP.GetMissionType(mission_id)
    
    FP.ClearMissionWaypoints(mission_id)
    
    area_string = '%f,%f,%f,%f,%f,%f,%f,%f' % (lon1, lat1, lon1, lat2, lon2, lat2, lon2, lat1)
    FP.SetMissionPatrolArea(mission_id, area_string)
    
    base_id = UI.GetPlatformId()
    base_track = UI.GetTrackById(base_id)
    
    # find closest corner of patrol area
    lonc, latc = GetClosestCorner(lon1, lat1, lon2, lat2, base_track)

    FP.AddMissionWaypointAdvanced(mission_id, base_track.Lon+0.001, base_track.Lat+0.001, 500, 100)
    FP.AddMissionWaypointTask(mission_id, 0, 'EngageAll')
    
    FP.AddMissionWaypointAdvanced(mission_id, lonc, latc, 300, 100)
    FP.AddMissionWaypointTask(mission_id, 1, 'ASWPatrolArea')
    FP.AddMissionWaypointTask(mission_id, 1, 'EngageAll')
    
    
    # if base is surface ship, then set all waypoints relative to base
    if (UI.IsSurface()):
        FP.SetMissionPatrolAnchor(mission_id, UI.GetName(), 2)
        FP.TransformToRelativePatrolArea(mission_id)
        nWaypoints = FP.GetMissionWaypointCount(mission_id)
        for n in range(0, nWaypoints):
            FP.EditMissionWaypointReference(mission_id, n, 2, base_id)
    
    UI.UpdateMissionEditGraphics()

    
def SetBarrierPatrolMission(UI, lon1, lat1, lon2, lat2, mission_id):    
    if ((not UI.HasFlightPort()) or (mission_id == -1)):
        return
    FP = UI.GetFlightPortInfo()
    FP.ClearMissionWaypoints(mission_id)
    
    FP.SetMissionPatrolArea(mission_id, '') # clear patrol area
    
    base_id = UI.GetPlatformId()
    base_track = UI.GetTrackById(base_id)
    
    # find closest corner of patrol area
    lonc, latc = GetClosestCorner(lon1, lat1, lon2, lat2, base_track)

    FP.AddMissionWaypointAdvanced(mission_id, base_track.Lon+0.001, base_track.Lat+0.001, 2000, 200)
    FP.AddMissionWaypointTask(mission_id, 0, 'WaitForGroup')
    
    FP.AddMissionWaypointAdvanced(mission_id, lon1, lat1, 2000, 300)
    FP.AddMissionWaypointTask(mission_id, 1, 'BarrierPatrol')
    FP.AddMissionWaypointTask(mission_id, 1, 'EngageAll')
    FP.AddMissionWaypointTask(mission_id, 1, 'RTB')
    
    FP.AddMissionWaypointAdvanced(mission_id, lon2, lat2, 2000, 300)
    
    FP.AddMissionWaypointAdvanced(mission_id, lon1, lat1, 2000, 300)
    
    FP.AddMissionWaypointAdvanced(mission_id, lonc+0.0002, latc, 10000, 300)
    FP.AddMissionWaypointTask(mission_id, 4, 'Land')
    
    # if base is surface ship, then set all waypoints relative to base
    if (UI.IsSurface()):
        FP.SetMissionPatrolAnchor(mission_id, UI.GetName(), 2)
        nWaypoints = FP.GetMissionWaypointCount(mission_id)
        for n in range(0, nWaypoints):
            FP.EditMissionWaypointReference(mission_id, n, 2, base_id)
    
    UI.UpdateMissionEditGraphics()
    
       
def SetFerryMission(UI, destination_id, mission_id):    
    if ((not UI.HasFlightPort()) or (mission_id == -1)):
        return
    FP = UI.GetFlightPortInfo()
    FP.ClearMissionWaypoints(mission_id)
    
    FP.SetMissionPatrolArea(mission_id, '') # clear patrol area
    
    base_id = UI.GetPlatformId()
    base_track = UI.GetTrackById(base_id)
    base_track.Offset(30, base_track.Heading_rad)
    
    destination_track = UI.GetTrackById(destination_id)
    landing_target = UI.LookupFriendlyName(destination_id)
    FP.SetMissionLandingTarget(mission_id, landing_target)
    
    FP.AddMissionWaypointAdvanced(mission_id, base_track.Lon, base_track.Lat, 9000, 500)
    FP.EditMissionWaypointReference(mission_id, 0, 2, base_id) # set first waypoint relative to launching base
    
    destination_track.Offset(30, destination_track.Heading_rad + 3.1415)
    FP.AddMissionWaypoint(mission_id, destination_track.Lon, destination_track.Lat)
    FP.EditMissionWaypointReference(mission_id, 1, 2, destination_id) # set second waypoint relative to landing base
    FP.AddMissionWaypointTask(mission_id, 1, 'Land')
    
    UI.UpdateMissionEditGraphics()    
    

def SetStrikeMission(UI, target_id, mission_id):    
    if ((not UI.HasFlightPort()) or (mission_id == -1)):
        return
    FP = UI.GetFlightPortInfo()
    FP.ClearMissionWaypoints(mission_id)
    
    FP.SetMissionPatrolArea(mission_id, '') # clear patrol area
    
    base_id = UI.GetPlatformId()
    base_track = UI.GetTrackById(base_id)
    waypoint_track = base_track
    waypoint_track.Offset(30, base_track.Heading_rad+0.785) # form up 30 km away
    
    FP.AddMissionWaypointAdvanced(mission_id, waypoint_track.Lon, waypoint_track.Lat, 6000, 300)
    FP.AddMissionWaypointTask(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointTask(mission_id, 0, 'EngageAllAir')
    FP.AddMissionWaypointTask(mission_id, 0, 'RadarRandom')
    if (UI.IsSurface()):
        FP.EditMissionWaypointReference(mission_id, 0, 2, base_id)
    
    target_track = UI.GetTrackById(target_id)
    FP.SetMissionDatum(mission_id, target_track.Lon, target_track.Lat)
    range_km = waypoint_track.RangeToKm(target_track.Lon, target_track.Lat)
    bearing_rad = waypoint_track.BearingToRad(target_track.Lon, target_track.Lat)
    
    if (range_km > 60.0):
        waypoint_track.Offset(range_km-30.0, bearing_rad)
    else:
        waypoint_track.Offset(0.5*range_km, bearing_rad)
        
    FP.AddMissionWaypointAdvanced(mission_id, waypoint_track.Lon, waypoint_track.Lat, 6000, 500)
    FP.AddMissionWaypointTask(mission_id, 1, 'GroundStrike')
    FP.AddMissionWaypointTask(mission_id, 1, 'RadarOn')
    
    waypoint_track = base_track
    waypoint_track.Offset(30, base_track.Heading_rad-0.785)
    FP.AddMissionWaypointAdvanced(mission_id, waypoint_track.Lon, waypoint_track.Lat, 6000, 300)
    FP.AddMissionWaypointTask(mission_id, 2, 'Land')
    
    
    UI.UpdateMissionEditGraphics()        
    
    
    