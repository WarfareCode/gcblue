#Version 0.7
#todo - ongoing little list of challenges I have ahead of me
  #helm stuff
    #write more patrol types
      #Box random
      #box spiral
      #box ladder
      #spiral ongoing
      #spiral inverted
      #spiral looped
      #waypoint
      #waypoint looped
      #waypoint inverted loop
    #test sprint drift
    #test/write zig-zag
    #build in evasive approach method to try and perform better in gunfights
  #reduce load further
    #attempt larger az_piece value  10 degrees currently
    #reduce script update rates
    #prevent unnecessary effort, scoring especially
  #branch out into other unit types
    #subs
    #aircraft
      #determine role and cater to it
      #scripts specific to:
        #air intercept
        #CAP
        #BARCAP
        #Strike
        #Escort
        #Recon
        #SEAD
        #ASW
        #ASuW
        #fueling
        #AEW
    #ground vehicles
    #ground Fixed
  #autogenerate aircraft missions
    #must wait for 1.4
    #the assignment of escorts for VIP aircraft
    #responses to hostile intrusion
    #prosecuting subs with fixed or rotary as applicable
    #striking targets
      #ships, ground
    #moving inventory
  #reach version 1.0 and officially release it.....

from AI import *
# To be able to import modules from the bin/lib directory
import sys
from os.path import dirname, abspath, join
sys.path.append(abspath(join(dirname(__file__), '..', 'bin', 'lib')))
from pickle import dumps, loads, HIGHEST_PROTOCOL
import math
from Amram_AI_Menu_Scripts import *
from Amram_AI_Weapon_Lists import *

az_piece = 10
segments = int(360 / az_piece)
segment = segments - 1#use this one for table work, since we count from 0=1 to 5=6, and not 1=1 to 6=6

    
def GetPatrolStartDatum(UI, arg1, arg2):
    BB = UI.GetBlackboardInterface()
#    debug_file = open('log/pydebug_datum.txt', 'w')
    position = [arg1,arg2]
    Write_Message_List(BB, position, 'Patrol_datum_start')
    Write_Message_List(BB, position, 'Patrol_datum_a')

def SetRadiusMax(UI, arg1):
    BB = UI.GetBlackboardInterface()
    BB.WriteGlobal('Patrol_Radius_Max', arg1)

def Spiral(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    TI.SetUpdateInterval(5)

    #if the set patrol type is not spiral, we need to shut down and stop interfering
    patrol_type = Try_Read_Message(BB, 'Patrol_Type', 0)
    if patrol_type != 'Spiral':
        TI.EndTask()    

    #we need to initialise and get our starting datum.
    initialized = TI.GetMemoryValue(99)
    if not initialized:
        TI.SetMemoryValue(99,1)#we've now initialized
#        UI.GetUserInput('GetPatrolStartDatum','Datum')
        Patrol_Radius_Max = Try_Read_Message(BB, 'Patrol_Radius_Max',2) #maximum radius for normal patrol setting.
        if Patrol_Radius_Max == 0:
            UI.GetUserInput('SetRadiusMax', 'Text Enter Maximum Spiral Radius')
#        debug_file = open('log/pydebug_spiral.txt', 'w')
#        debug_file.close
#    debug_file = open('log/pydebug_spiral.txt', 'a')


    patrol_state = Try_Read_Message(BB, 'Patrol_State',0)           #current state of patrol
    Patrol_Radius_Max = Try_Read_Message(BB, 'Patrol_Radius_Max',2) #maximum radius for normal patrol setting.
    start_point = Read_Message_List(BB, 'Patrol_datum_start')       #center datum
    next_point = Read_Message_List(BB, 'Patrol_datum_a')            #next datum
    patrol_focus = Try_Read_Message(BB, 'Patrol_Focus',0)           #patrol purpose
    patrol_direction = Try_Read_Message(BB, 'Patrol_Direction',0)   #directionality of patrol
    transit_pace = Try_Read_Message(BB, 'Patrol_Transit_Pace',2)    #pace of transit to patrol point
    patrol_pace = Try_Read_Message(BB, 'Patrol_Patrol_Pace',2)      #pace of transit to patrol point
    
    #replace me with a proper BB message setting.
#    UI.DisplayMessage('Patrol_Radius_Max : %s' % Patrol_Radius_Max)

    #confirm we have a start point, if this is our first run of the script, its very likely we do not yet.
    try:
        start_point[1]
        needStart = False
    except:
        needStart = True
        patrol_state = 'no_datum'
    
    if needStart:
        #if nextpoint hasn't been set, or for some reason has been lost, use our last point.
        if ((next_point == '') or (next_point == [])):
            next_point = start_point
#            Write_Message_List(BB, next_point, 'Patrol_datum_a')

#    debug_file.write('\npatrol_state : %s\n' % patrol_state)
    valid_states = ['in_progress', 'resume', 'transit']
    if patrol_state in valid_states:
        if not TI.GetMemoryValue(2):
            heading_rad = UI.GetHeadingRad()
            if heading_rad < 0:
                heading_rad + (math.pi * 2)
            TI.SetMemoryValue(1, heading_rad)
            TI.SetMemoryValue(2, 1)

        #providing a 16 second window in which to notice we have approached our current point and need a new one.
        if patrol_state == 'transit':
            proximity = transit_pace * 0.004115552
        elif patrol_state == 'in_progress':
            proximity = patrol_pace * 0.004115552
        
        datum_range = UI.GetRangeToDatum(next_point[0],next_point[1])
        if datum_range < Patrol_Radius_Max and patrol_state == 'transit':
            BB.WriteGlobal('Patrol_State', 'in_progress')         
            
        if datum_range < proximity:
            if patrol_focus == 'ASW':
                spacing = 5
                initial_spacing = 4
            elif patrol_focus == 'ASuW':
                if UI.IsSurface():
                    spacing = 15
                    initial_spacing = 10
                elif UI.IsAir():
                    spacing = 30
                    initial_spacing = 20
            else:
                spacing = 15
                initial_spacing = 10
            constant_width = spacing / (math.pi * 2)
            
            if patrol_direction == 'Counter-Clockwise':
                direction = -1
            else:
                direction = 1

            #retrieve angle
            if TI.GetMemoryValue(2) == -1:
                radian_angle = 0
            else:
                radian_angle = TI.GetMemoryValue(2)
            #determine new radius
            radius_new = radian_angle * constant_width + initial_spacing
            #determine angular step for next point, given radius_new
            if UI.GetRangeToDatum(start_point[0], start_point[1]) < initial_spacing * 0.6:
                radian_angle_new = 0
            else:
                radian_angle_new = (4 / radius_new)  #next point is 2km away
            radian_angle += radian_angle_new
            #save spiral angle
            TI.SetMemoryValue(2, radian_angle)
            #align to initial heading
            radian_angle += TI.GetMemoryValue(1)

            #convert to x and y offsets
            #measure 0.01 radians of latitude, and of longitude to use in setting our next point.
            #goal is to allow the game to insert its map variations into this calculation directly.
            #should result in the spiral working correctly at any latitude.
            lon_km = UI.GetRangeToDatum(UI.GetLongitude() + .01,UI.GetLatitude()) * 100
            lat_km = UI.GetRangeToDatum(UI.GetLongitude(),UI.GetLatitude() + .01) * 100
        
            new_x = cos(radian_angle) * (radius_new / lon_km) * direction
            new_y = sin(radian_angle) * (radius_new / lat_km) * direction

            #save the location
            next_point[0] = new_x + start_point[0] #lon, x
            next_point[1] = new_y + start_point[1] #lat, y
            Write_Message_List(BB, next_point, 'Patrol_datum_a')
            
def SprintDrift(TI, RoA, drift_time, pacing):   #untested
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    
    transit_drift = Try_Read_Message(BB, 'Transit_Sprint_Drift',1)
    transit_advance = Try_Read_Message(BB, 'Transit_Sprint_Advance',1)
    patrol_drift = Try_Read_Message(BB, 'Patrol_Sprint_Drift',1)
    patrol_advance = Try_Read_Message(BB, 'Patrol_Sprint_Advance',1)
    patrol_state = Try_Read_Message(BB, 'Patrol_State',0)           #current state of patrol
    
    if pacing == -2:  #relaxed
        if RoA > UI.GetMaxSpeed() * 1/3:
            pacing = -1
    if pacing == -1:  #standard
        if RoA > UI.GetMaxSpeed() * 2/3:
            pacing = 0

    if pacing == -2:
        sprint_rate = UI.GetMaxSpeed()
    elif pacing == -1:
        sprint_rate = UI.GetMaxSpeed()
    elif pacing == 0:
        sprint_rate = UI.GetMaxSpeed()
    elif pacing > 0:
        sprint_Rate = pacing
        if sprint_rate > UI.GetMaxSpeed():
            sprint_Rate = UI.GetMaxSpeed()
        
    #sprint duration = Rate of Advance / ((sprint speed - Rate Of Advance)/drift duration)
    sprint_time = RoA / ((sprint_rate - RoA)/drift_time)
    
    init = TI.GetMemoryValue(99)
    if not init:
        #set drift state
        TI.SetmemoryValue(100,1)
        
    if TI.GetMemoryValue(100) == 1:
        TI.SetUpdateInterval(sprint_time)
        UI.SetSpeed(UI.GetMaxSpeed())
        TI.SetMemoryValue(100,2)
    elif TI.GetMemoryValue(100) == 2:
        TI.SetUpdateInterval(drift_time)
        UI.SetSpeed(0)
        TI.SetMemoryValue(100,1)
        
def ZigZag(TI, RoA, distance, pacing):   #incomplete
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    
    #distance = distance to next waypoint, ZigZag is based in part on length of waypoint.
    #R0A = rate of advance
    #pacing = fractional speed for the sprint
    
    OffsetAngle = 0.524  #radians, roughly 30 degrees.

    if pacing == -2:  #relaxed
        if RoA > UI.GetMaxSpeed() * 1/3:
            pacing = -1
    if pacing == -1:  #standard
        if RoA > UI.GetMaxSpeed() * 2/3:
            pacing = 0

    if pacing == -2:
        sprint_rate = UI.GetMaxSpeed()
    elif pacing == -1:
        sprint_rate = UI.GetMaxSpeed()
    elif pacing == 0:
        sprint_rate = UI.GetMaxSpeed()
    elif pacing > 0:
        sprint_Rate = pacing
        if sprint_rate > UI.GetMaxSpeed():
            sprint_Rate = UI.GetMaxSpeed()

    #if zig-zagging, drive straight for legs not longer than 4km, not shorter than 1km
    
    #trig to find the offset distance for our leg
    angle_offset = abs(UI.GetHeadingRad() + 0.524)
    while (angle_offset > 6.28318531):
        angle_offset -= 6.28318531
    zigZag_offset = abs(leg_length * sin(angle_offset))
     
def AI_Weaponry(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    #his job is now very simple.
    #set the stage for the other sub scripts to do their thing, and be visible so we know its running.
    #when i evolve to unit specific scripting, i'll have to call them specifically from here.
    #Weapon_Officer will exist in more than one name, but they will all trigger from here
    #each core officer will be responsible for the task of launching the respective subscripts for their class type.
    
    TI.SetUpdateInterval(1)
    if UI.GetLauncherCount() == 0:
        TI.EndTask()#if we have no weapons, then a combat script is a waste of time.
    
    initialized = TI.GetMemoryValue(99)
    if not initialized:
        BB.WriteGlobal('Flagfree1', '1')
        BB.WriteGlobal('Flagfree2', '1')
        BB.WriteGlobal('Flagfree4', '0')
        BB.WriteGlobal('Flagfree8', '1')
        BB.WriteGlobal('Flagfree16', '1')
        BB.WriteGlobal('MissileStrikeAllow', '1')
        if UI.IsPlayerControlled():
            BB.WriteGlobal('MissileStrikeRange', '80')
        else:
            BB.WriteGlobal('MissileStrikeRange', '10000')
        BB.WriteGlobal('ROE', '3')
        BB.WriteGlobal('error_km', '15')
        TI.SetMemoryValue(99,1)
        DeleteHiddenTask(UI, 'PointDefense')
        DeleteHiddenTask(UI, 'MissileWarning')
        if UI.TaskExists('EngageAll'):
            UI.DeleteTask('EngageAll')
        if UI.TaskExists('EngageAllAir'):
            UI.DeleteTask('EngageAllAir')
        if (not(UI.TaskExists('AI_Navigation'))): 
            UI.AddTask('AI_Navigation', 1, 1)
        if (not(UI.TaskExists('Catalog_Launchers_Amram'))): 
            UI.AddTask('Catalog_Launchers_Amram', 1, -1)
        if (not(UI.TaskExists('Score_Targets_Amram'))): 
            UI.AddTask('Score_Targets_Amram', 5, -1)

def Msl_Attack(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    TI.SetUpdateInterval(2)

    if (not(UI.TaskExists('AI_Weaponry'))):
        TI.EndTask()   #weapon officer is not operational, we should not be
    
    #need to know missile max range, nearest missile, air max range, nearest air, sea max range, nearest sea, land max range, and nearest land.
    sea_max_range = Try_Read_Message(BB, 'sea_max_range', 2)
    air_max_range = Try_Read_Message(BB, 'air_max_range', 2)
    land_max_range = Try_Read_Message(BB, 'land_max_range', 2)
    missile_max_range = Try_Read_Message(BB, 'missile_max_range', 2)
    nearest_surface = Try_Read_Message(BB, 'nearest_surface', 2)
    nearest_air = Try_Read_Message(BB, 'nearest_air', 2)
    nearest_land = Try_Read_Message(BB, 'nearest_land', 2)
    nearest_missile = Try_Read_Message(BB, 'nearest_missile', 2)
    L12a = Read_Message_List(BB, 'L12a')
    L12m = Read_Message_List(BB, 'L12m')
    L12sm = Read_Message_List(BB, 'L12sm')
    L12lm = Read_Message_List(BB, 'L12lm')
    if (L12a == []) and (L12m == []) and (L12lm == []) and (L12sm == []):
        TI.EndTask()  #we have no launchers suitable for this task.

    if (((missile_max_range * 2 > nearest_missile) or (air_max_range > nearest_air)) or ((sea_max_range > nearest_surface) or (land_max_range > nearest_land))):
        TI.SetUpdateInterval(1)
        used_launchers = []
        launcher_catalog = Read_Message_List(BB, 'launcher_catalog')
        queued_targets = Read_Message_List(BB, 'queued_targets')
        engaged_targets = Read_Message_List(BB, 'engaged_targets')
        if ((missile_max_range * 2 > nearest_missile) or (air_max_range > nearest_air)):
            try:
                L04m = Read_Message_List(BB, 'L04m')
                max_gun_missile_range = L04m.sort()
                max_gun_missile_range = L04m[-1][0]
            except:
                max_gun_missile_range = 0
            launchers = L12m + L12a
            launchers.sort()
            aaw_target_list = Read_Message_List(BB, 'aaw_target_list')
            launcher, queued_targets = Engage_Targets_Missiles_Amram(TI, launchers, aaw_target_list, max_gun_missile_range, queued_targets, engaged_targets, used_launchers, launcher_catalog)
        if ((sea_max_range > nearest_surface) or (land_max_range > nearest_land)):
            if (sea_max_range > nearest_surface):
                asuw_target_list = Read_Message_List(BB, 'asuw_target_list')
                launcher, queued_targets = Engage_Targets_Missiles_Amram(TI, L12sm, asuw_target_list, 0, queued_targets, engaged_targets, used_launchers, launcher_catalog)
            if (land_max_range > nearest_land):
                agw_target_list = Read_Message_List(BB, 'agw_target_list')
                launcher, queued_targets = Engage_Targets_Missiles_Amram(TI, L12lm, agw_target_list, 0, queued_targets, engaged_targets, used_launchers, launcher_catalog)
        Write_Message_List(BB, queued_targets, 'queued_targets')
        Write_Message_List(BB, engaged_targets, 'engaged_targets')
    
def Gun_Attack(TI): 
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    TI.SetUpdateInterval(2)
    if (not(UI.TaskExists('AI_Weaponry'))):
        TI.EndTask()   #weapon officer is not operational, we should not be
        
    L04a = Read_Message_List(BB, 'L04a')
    L04m = Read_Message_List(BB, 'L04m')
    L04lg = Read_Message_List(BB, 'L04lg')
    L04sg = Read_Message_List(BB, 'L04sg')
    if (L04a == []) and (L04m == []) and (L04lg == []) and (L04sg == []):
        TI.EndTask()  #we have no launchers suitable for this task.    launcher_catalog = Read_Message_List(BB, 'launcher_catalog')

    used_launchers = []
    nearest_surface = Try_Read_Message(BB, 'nearest_surface', 2)
    nearest_air = Try_Read_Message(BB, 'nearest_air', 2)
    nearest_land = Try_Read_Message(BB, 'nearest_land', 2)
    nearest_missile = Try_Read_Message(BB, 'nearest_missile', 2)
    sea_max_range_gun = Try_Read_Message(BB, 'sea_max_range_gun', 2)
    air_max_range_gun = Try_Read_Message(BB, 'air_max_range_gun', 2)
    land_max_range_gun = Try_Read_Message(BB, 'land_max_range_gun', 2)
    missile_max_range_gun = Try_Read_Message(BB, 'missile_max_range_gun', 2)
    aaw_target_list_guns = Read_Message_List(BB, 'aaw_target_list_guns')
    agw_target_list = Read_Message_List(BB, 'agw_target_list')
    asuw_target_list = Read_Message_List(BB, 'asuw_target_list')
    launcher_catalog = Read_Message_List(BB, 'launcher_catalog')

    if ((missile_max_range_gun > nearest_missile) or (air_max_range_gun > nearest_air)):
        TI.SetUpdateInterval(0.2)
        aaw_target_list_guns = Read_Message_List(BB, 'aaw_target_list_guns')
        if (missile_max_range_gun > nearest_missile):
            used_launchers = Engage_Targets_Guns_Amram(TI, L04m, aaw_target_list_guns, used_launchers, launcher_catalog)
        if (air_max_range_gun > nearest_air):
            used_launchers = Engage_Targets_Guns_Amram(TI, L04a, aaw_target_list_guns, used_launchers, launcher_catalog)
    if ((sea_max_range_gun > nearest_surface) or (land_max_range_gun > nearest_land)):
        TI.SetUpdateInterval(0.2)
        if (sea_max_range_gun > nearest_surface):
            asuw_target_list = Read_Message_List(BB, 'asuw_target_list')
            used_launchers = Engage_Targets_Guns_Amram(TI, L04sg, asuw_target_list, used_launchers, launcher_catalog)
        if (land_max_range_gun > nearest_land):
            agw_target_list = Read_Message_List(BB, 'agw_target_list')
            used_launchers = Engage_Targets_Guns_Amram(TI, L04lg, agw_target_list, used_launchers, launcher_catalog)

def Trp_Attack(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    TI.SetUpdateInterval(6)

    if (not(UI.TaskExists('AI_Weaponry'))):
        TI.EndTask()   #weapon officer is not operational, we should not be
        
    used_launchers = []
    L0124tp = Read_Message_List(BB, 'L0124tp')
    if L0124tp == []:
        TI.EndTask()  #we have no torpedoes.    asw_target_list = Read_Message_List(BB, 'asw_target_list')

    launcher_catalog = Read_Message_List(BB, 'launcher_catalog')
    sub_max_range = Try_Read_Message(BB, 'sub_max_range', 2)
    nearest_sub = Try_Read_Message(BB, 'nearest_sub', 2)

    if (sub_max_range > nearest_sub):
        used_launchers = Engage_Targets_Torps_Amram(TI, L0124tp, asw_target_list, used_launchers, launcher_catalog)
           
def Engage_Targets_Guns_Amram(TI, launchers, target_list, used_launchers, launcher_catalog):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    launchers2 = []
    for x in range(0, len(launchers)):
        if launchers[x][1] not in launchers2:
            launchers2.append(launchers[x][1])
    launchers = launchers2
    
    

    launcher_catalog = Read_Message_List(BB, 'launcher_catalog')
    for n in range(0, len(launchers)):
        launcher = UI.GetLauncherInfo(launchers[n])
        if (len(launchers) == 0):
            if (not(UI.TaskExists('Catalog_Launchers_Amram'))): 
                UI.AddTask('Catalog_Launchers_Amram', 1, -1)
            return used_launchers
        elif ((UI.GetLauncherWeaponName(launcher.Launcher) != launcher_catalog[launcher.Launcher][1]) and launcher.IsValid()):  #if our loaded weapon doesn't match the catalog, then we need to take inventory again.
            if (not(UI.TaskExists('Catalog_Launchers_Amram'))): 
                UI.AddTask('Catalog_Launchers_Amram', 1, -1)
            return used_launchers
        go_for_evaluate = False
        if (not launcher.Launcher in used_launchers):
            if ((launcher.LaunchMode == 0) or (launcher.LaunchMode == 4)):
                go_for_evaluate = True
        if go_for_evaluate:
            for x in range(0, len(target_list)):
                track = UI.GetTrackById(target_list[x][1])
                if ((not track.IsDestroyed()) and (track.IsValid())):
                    track.range = UI.GetRangeToTrack(track)
                    max_range = launcher.MaxRange_km
                    
                    go_for_launch = False
                    if((launcher.LaunchMode == 0) or (launcher.LaunchMode == 4)):
                        if ((track.range < max_range) and (track.range > launcher.MinRange_km)):
                            go_for_launch = True

                    if go_for_launch:
                        center = launcher.SectorCenter
                        if (center == 0):
                            center2 = 360
                        else:
                            center2 = center
                        wide = launcher.SectorWidth
                        heading = UI.GetHeadingToDatum(track.Lon, track.Lat)
                        bearing = heading - UI.GetHeading()
                        if (bearing <0):
                            bearing += 360
                        launched = False
                        if ((abs(bearing - center)< wide / 2) or (abs(bearing - center2)< wide / 2)):
                            if (UI.GetTarget() != track.ID):
                                UI.SetTarget(track.ID)
                            if (not(UI.TaskExists('Drop_Targets'))): 
                                UI.AddTask('Drop_Targets', 0.5, -1)
                            launched = Use_Launcher_On_Target_Amram(UI, launcher.Launcher, 1)
                        if launched:
                            used_launchers.append(launcher.Launcher)
                            return used_launchers
    return used_launchers

def Engage_Targets_Torps_Amram(TI, launchers, target_list, used_launchers, launcher_catalog):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    launchers2 = []
    for x in range(0, len(launchers)):
        if launchers[x][1] not in launchers2:
            launchers2.append(launchers[x][1])
    launchers = launchers2
    
    
    for n in range(0, len(launchers)):
        launcher = UI.GetLauncherInfo(launchers[n])
        if (len(launchers) == 0):
            if (not(UI.TaskExists('Catalog_Launchers_Amram'))): 
                UI.AddTask('Catalog_Launchers_Amram', 1, -1)
            return used_launchers  #we shouldn't even try if we have no launchers to work with
        elif ((UI.GetLauncherWeaponName(launcher.Launcher) != launcher_catalog[launcher.Launcher][1]) and launcher.IsValid()):  #if our loaded weapon doesn't match the catalog, then we need to take inventory again.
            if (not(UI.TaskExists('Catalog_Launchers_Amram'))): 
                UI.AddTask('Catalog_Launchers_Amram', 1, -1)
            return used_launchers  #we shouldn't even try if our inventory is incorrect        
        go_for_evaluate = False
        #if ((not launcher.IsLoading) or (str(launcher.Launcher) not in used_launchers)):    # De Morgan's laws
#        if (not (launcher.IsLoading and (str(launcher.Launcher) in used_launchers))):    # I feel like there's a bug :4rk   -agreed, Amram
        if (not launcher.Launcher in used_launchers):    # -Use_Launcher_On_Target_Amram includes an IsLoading check.
            go_for_evaluate = True
        if go_for_evaluate:
            for x in range(0, len(target_list)):
                track = UI.GetTrackById(target_list[x][1])
                if ((not track.IsDestroyed()) and (track.IsValid())):
                    track.range = UI.GetRangeToTrack(track)
                    max_range = launcher.MaxRange_km
                    
                    go_for_launch = False
                    if ((track.range < max_range) and (track.range > launcher.MinRange_km) and (launcher.MinLaunchAlt_m < 0)):
                        max_engaged_count = Get_Engage_Limit_Amram(track)
                        target_engaged_count = track.GetEngagedCount()
                        if target_engaged_count < max_engaged_count:
                            go_for_launch = True
                    elif ((track.range < max_range) and (track.range > launcher.MinRange_km)):
                        go_for_launch = True

                    if go_for_launch:
                        center = launcher.SectorCenter
                        if (center == 0):
                            center2 = 360
                        else:
                            center2 = center
                        wide = launcher.SectorWidth
                        heading = UI.GetHeadingToDatum(track.Lon, track.Lat)
                        bearing = heading - UI.GetHeading()
                        if (bearing <0):
                            bearing += 360
                        launched = False
                        if ((abs(bearing - center)< wide / 2) or (abs(bearing - center2)< wide / 2)):
                            if (UI.GetTarget() != track.ID):
                                UI.SetTarget(track.ID)
                            if (not(UI.TaskExists('Drop_Targets'))): 
                                UI.AddTask('Drop_Targets', 0.5, -1)
                            launched = Use_Launcher_On_Target_Amram(UI, launcher.Launcher, 2)
                        if launched:
                            used_launchers.append(launcher.Launcher)
                            return used_launchers
    return used_launchers

def Engage_Targets_Missiles_Amram(TI, launchers, target_list, max_gun_missile_range, queued_targets, engaged_targets, used_launchers, launcher_catalog):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    launchers2 = []
    for x in range(0, len(launchers)):
        if launchers[x][1] not in launchers2:
            launchers2.append(launchers[x][1])
    launchers = launchers2
    
    
    for n in range(0, len(launchers)):
        launcher = UI.GetLauncherInfo(launchers[n])
        if (len(launchers) == 0):
            if (not(UI.TaskExists('Catalog_Launchers_Amram'))): 
                UI.AddTask('Catalog_Launchers_Amram', 1, -1)
            return used_launchers, queued_targets  #we shouldn't even try if we have no launchers to work with
        elif ((UI.GetLauncherWeaponName(launcher.Launcher) != launcher_catalog[launcher.Launcher][1]) and launcher.IsValid()):  #if our loaded weapon doesn't match the catalog, then we need to take inventory again.
            if (not(UI.TaskExists('Catalog_Launchers_Amram'))): 
                UI.AddTask('Catalog_Launchers_Amram', 1, -1)
            return used_launchers, queued_targets  #we shouldn't even try if our inventory is incorrect
        go_for_evaluate = False
        if (not launcher.Launcher in used_launchers):
            if not (launcher.FireControlTracks >= launcher.MaxFireControlTracks):
                go_for_evaluate = True
        if go_for_evaluate:
            for x in range(0, len(target_list)):
                track = UI.GetTrackById(target_list[x][1])
                if ((not track.IsDestroyed()) and track.IsValid()):
                    track.range = UI.GetRangeToTrack(track)
                    max_engaged_count = Get_Engage_Limit_Amram(track)

                    if track.IsMissile():
                        engage_mod = target_list[x][2]
                        closure = target_list[x][3]
                        air = target_list[x][4]
                        max_range = launcher.MaxRange_km / 0.9 * closure + launcher.MaxRange_km
                        max_engaged_count = Get_Engage_Limit_Amram(track) + engage_mod - 1
                        if (track.range < max_gun_missile_range):
                            try:
                                target_engaged_count = sum(z.count(track.ID) for z in engaged_targets)
                            except:
                                target_engaged_count = 0
                            try:
                                target_engaged_count += queued_targets.count(track.ID)
                            except:
                                target_engaged_count += 0
                        else:
                            target_engaged_count = track.GetEngagedCount()
                    elif track.IsAir():
                        engage_mod = target_list[x][2]
                        closure = target_list[x][3]
                        air = target_list[x][4]
                        max_range = launcher.MaxRange_km-((launcher.MaxRange_km/0.9)*track.Speed*0.000385833)
                        max_engaged_count = Get_Engage_Limit_Amram(track) + engage_mod - 1
                        target_engaged_count = track.GetEngagedCount()
                    else:
                        MissileStrikeAllow = Try_Read_Message(BB, 'MissileStrikeAllow',1)
                        if MissileStrikeAllow:
                            MissileStrikeRange = Try_Read_Message(BB, 'MissileStrike',1)
                            max_range = min(launcher.MaxRange_km, MissileStrikeRange)  #use the missile strike range limit to validate launch if its smaller than the weapons reach.
                        else:
                            max_range = 0
                        max_engaged_count = Get_Engage_Limit_Amram(track)
                        target_engaged_count = track.GetEngagedCount()

                    go_for_launch = False
                    if ((track.range < max_range) and (track.range > launcher.MinRange_km) and (target_engaged_count < max_engaged_count)):
                        go_for_launch = True

                    if go_for_launch:
                        center = launcher.SectorCenter
                        if (center == 0):
                            center2 = 360
                        else:
                            center2 = center
                        wide = launcher.SectorWidth
                        heading = UI.GetHeadingToDatum(track.Lon,track.Lat)
                        bearing = heading - UI.GetHeading()
                        if (bearing <0):
                            bearing += 360
                        launched = False
                        if ((abs(bearing - center)< wide / 2) or (abs(bearing - center2)< wide / 2)):
                            if (UI.GetTarget() != track.ID):
                                UI.SetTarget(track.ID)
                            if (not(UI.TaskExists('Drop_Targets'))): 
                                UI.AddTask('Drop_Targets', 0.5, -1)
                            launched = Use_Launcher_On_Target_Amram(UI, launcher.Launcher, 0)
                        if launched:
                            used_launchers.append(launcher.Launcher)
                            queued_targets.append([track.ID, launcher.Launcher, int(center), int(wide), launcher.LaunchMode])
                            if (not(UI.TaskExists('Maintain_Engaged_Targets'))): 
                                UI.AddTask('Maintain_Engaged_Targets', 0.2, -1)
                            for n in range(0,UI.GetSensorCount()):
                                sensor = UI.GetSensorInfo(n)
                                if sensor.type != 8:
                                    UI.SetSensorState(n, 1)
                            return used_launchers, queued_targets
    return used_launchers, queued_targets

def Check_Status(UI, status_num, launch_mode):
    missile_status_mode0  = [2, 3, 12, 13, 14, 15, 16, 22]
    missile_status_mode12 = [2, 3, 6, 7, 11, 12, 13, 14, 15, 16, 21, 22]
    if launch_mode == 0:
        status = missile_status_mode0
    elif launch_mode == 1:
        status = missile_status_mode12
    else:
        status = []
        
    if status_num not in status:
        return True
    else:
        return False
         
def Use_Launcher_On_Target_Amram(UI, launcher, launch_type):
    launcher = UI.GetLauncherInfo(launcher)
    if ((not launcher.IsValid()) or launcher.IsLoading):
        return False
    if not UI.IsLauncherEffective(launcher.Launcher):
        if (not(UI.TaskExists('Catalog_Launchers_Amram'))): 
            UI.AddTask('Catalog_Launchers_Amram', 1, -1)
        return False
    launch_mode = launcher.LaunchMode   # 0 - datum, 1 - seeker, 2 - bomb, 3 - other
    if not Check_Status(UI, launcher.Status, launch_mode):
        return False
    target_info = UI.GetTargetTrackInfo()
    launch_qty = 1 # only launch one at a time for spacing


    if launch_mode == 0:  # datum launch
        if launch_type == 2:  #torpedo
            speed_mps = Torpedo_Lead(UI, UI.GetLauncherWeaponName(launcher.Launcher))
            range_km = UI.GetRangeToTrack(target_info)
            travel_time_s = 1000.0 * range_km / speed_mps
            travel_time_s = travel_time_s + 10.0 # add a little time for launch and altitude adjustment
            target_info = target_info.PredictAhead(travel_time_s)
            lat = target_info.Lat
            lon = target_info.Lon
            alt = target_info.Alt
        elif launch_type == 1:  #gun
            # if the Speed_mps is non-zero in launcher info, then adjust datum based on expected travel time and target speed and heading
            if (launcher.Speed_mps > 0):
                range_km = UI.GetRangeToTrack(target_info)
                travel_time_s = 1000.0 * range_km / launcher.Speed_mps
                travel_time_s = travel_time_s + 10.0 # add a little time for launch and altitude adjustment
                target_info = target_info.PredictAhead(travel_time_s)
            lat = target_info.Lat
            lon = target_info.Lon
            alt = target_info.Alt
            if alt < 0:
                alt = 0
        else:  #launch_type = 0, missile
            #confirm the missile is the type its supposed to be.....
            if target_info.IsSurface():
                ASM = AntiShipMissile(UI, UI.GetLauncherWeaponName(launcher.Launcher))
                if not ASM:
                    return False
            elif target_info.IsGround():
                AGM = AntiLandMissile(UI, UI.GetLauncherWeaponName(launcher.Launcher))
                if not AGM:
                    return False
            range_km = UI.GetRangeToTrack(target_info)
            lat = target_info.Lat
            lon = target_info.Lon
            alt = target_info.Alt
        
        UI.HandoffTargetToLauncher(launcher.Launcher) # to store intended target
        UI.SendDatumToLauncher(lon, lat, alt, launcher.Launcher)
        UI.Launch(launcher.Launcher, launch_qty)
        return True
    elif (launch_mode == 1) or (launch_mode == 2) or (launch_mode == 4):  # handoff to active seeker
        target_accepted = UI.HandoffTargetToLauncher(launcher.Launcher)
        if (target_accepted):
            UI.Launch(launcher.Launcher, launch_qty)
            return True
        else:
            return False
    else:    
        UI.DisplayMessage('Unrecognized launch mode: %d' % launch_mode)
        return False

def Maintain_Engaged_Targets(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    TI.SetUpdateInterval(0.2)
    
    queued_targets = Read_Message_List(BB, 'queued_targets')
    engaged_targets = Read_Message_List(BB, 'engaged_targets')

    #append attacked targets to engaged list
    friendly_missile_track_list = []
    if len(queued_targets) > 0:
        missile_tracks = UI.GetTrackList(0x0040, 0.05, 1)
        nTracks = missile_tracks.Size()
        if (missile_tracks.Size() == 0):
            missile_tracks = UI.GetTrackList(0x0040, 0.25, 1)
            nTracks = missile_tracks.Size()
            if (missile_tracks.Size() == 0):
                queued_targets = []
        for n in range(0, nTracks):
            track = missile_tracks.GetTrack(n)
            range_km = UI.GetRangeToTrack(track)
            friendly_missile_track_list.append([UI.GetRangeToTrack(track), track.ID])
        friendly_missile_track_list.sort()
        friendly_missile_tracks = []
        friendly_missile_tracks2 = []
        for x in range(0, len(friendly_missile_track_list)):
            friendly_missile_tracks.append(friendly_missile_track_list[x][1])
            friendly_missile_tracks2.append(friendly_missile_track_list[x][1])
        if len(friendly_missile_track_list) > 0:
            try:
                for x in range(0, len(queued_targets)):
                    target = queued_targets.pop(-1)
                    missile = friendly_missile_tracks[0]
                    engaged_targets.append([missile, target[0], target[1], target[2], target[3], target[4]])
                    friendly_missile_tracks.pop(0)
            except:
                pass
    #trim targets no longer engaged
    if len(engaged_targets) > 0:
        trim_list = []
        for x in range(0, len(engaged_targets)):
            missile = UI.GetTrackById(engaged_targets[x][0])
            target = UI.GetTrackById(engaged_targets[x][1])
            if ((not missile.IsValid()) or (not target.IsValid())):
                trim_list.append(x)
        trim_list = sorted(trim_list, reverse = True)
        for x in range(0, len(trim_list)):
            engaged_targets.pop(trim_list[x])
            
    Write_Message_List(BB, queued_targets, 'queued_targets')
    Write_Message_List(BB, engaged_targets, 'engaged_targets')

    if ((queued_targets == []) and (engaged_targets == [])):
        TI.EndTask()
        
def Score_Targets_Amram(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    TI.SetUpdateInterval(5)
    
    if (not(UI.TaskExists('AI_Weaponry'))):
        TI.EndTask()   #weapon officer is not operational, we should not be
    
    

    Flagfree1 = Try_Read_Message(BB, 'Flagfree1', 1)
    Flagfree2 = Try_Read_Message(BB, 'Flagfree2', 1)
    Flagfree4 = Try_Read_Message(BB, 'Flagfree4', 1)
    Flagfree8 = Try_Read_Message(BB, 'Flagfree8', 1)
    Flagfree16 = Try_Read_Message(BB, 'Flagfree16', 1)
    ROE = Try_Read_Message(BB, 'ROE', 1)
    error_km = Try_Read_Message(BB, 'error_km', 1)

    sea_max_range = Try_Read_Message(BB, 'sea_max_range', 2)
    air_max_range = Try_Read_Message(BB, 'air_max_range', 2)
    land_max_range = Try_Read_Message(BB, 'land_max_range', 2)
    missile_max_range = Try_Read_Message(BB, 'missile_max_range', 2)
    sea_max_range_gun = Try_Read_Message(BB, 'sea_max_range_gun', 2)
    air_max_range_gun = Try_Read_Message(BB, 'air_max_range_gun', 2)
    land_max_range_gun = Try_Read_Message(BB, 'land_max_range_gun', 2)
    missile_max_range_gun = Try_Read_Message(BB, 'missile_max_range_gun', 2)
    sub_max_range = Try_Read_Message(BB, 'sub_max_range', 2)
   
    tracks = []
    if Flagfree1:
        sea_tracks = UI.GetTrackList(0x0010, max(sea_max_range, sea_max_range_gun) * 1.1, ROE)
        nTracks = sea_tracks.Size()
        for n in range(0, nTracks):
            track = sea_tracks.GetTrack(n)
            tracks.append(track.ID)
    if Flagfree2:
        air_tracks = UI.GetTrackList(0x0020, max(air_max_range, air_max_range_gun) * 1.05, ROE)
        nTracks = air_tracks.Size()
        for n in range(0, nTracks):
            track = air_tracks.GetTrack(n)
            tracks.append(track.ID)
    if Flagfree4:
        land_tracks = UI.GetTrackList(0x0100, max(land_max_range, land_max_range_gun), ROE)
        nTracks = land_tracks.Size()
        for n in range(0, nTracks):
            track = land_tracks.GetTrack(n)
            tracks.append(track.ID)
    if Flagfree8:
        missile_tracks = UI.GetTrackList(0x0040, max(missile_max_range, missile_max_range_gun) * 2, ROE)
        nTracks = missile_tracks.Size()
        for n in range(0, nTracks):
            track = missile_tracks.GetTrack(n)
            tracks.append(track.ID)
    if Flagfree16:
        sub_tracks = UI.GetTrackList(0x0080, sub_max_range, ROE)
        nTracks = sub_tracks.Size()
        for n in range(0, nTracks):
            track = sub_tracks.GetTrack(n)
            tracks.append(track.ID)


    #score those targets
    nearest_surface = 100000
    nearest_air = 100000
    nearest_land = 100000
    nearest_missile = 100000
    nearest_sub = 100000
    AAW_high_score = []
    AGW_high_score = []
    ASuW_high_score = []
    ASW_high_score = []
    aaw_target_list = []
    asuw_target_list = []
    agw_target_list = []
    asw_target_list = []
    for x in range(0, len(tracks)):
        track = UI.GetTrackById(tracks[x])
        if track.TrackErrorKm() < error_km:
            staleness = UI.GetTime() - track.Time
            if ((staleness < 3) and (not track.IsDestroyed()) and track.IsValid() and (track.IsMissile() or track.IsAir())):
                track.range = UI.GetRangeToTrack(track)
                track.bearing_rad = (track.BearingToRad(UI.GetLongitude(), UI.GetLatitude()))    #gets my bearing from track
                if (track.Heading_rad < 0):
                    track.heading = track.Heading_rad + 6.28318531
                else:
                    track.heading = track.Heading_rad
                track_angle_offset = abs(track.bearing_rad - track.Heading_rad)   #determines how far from directly at us its path is.
                while (track_angle_offset > 6.28318531):
                    track_angle_offset -= 6.28318531
                track.approach = abs(track.range * sin(track_angle_offset) + 0.0000001)
                if track.approach < 0.75:
                    track.approach = 0.75
                track.closure = 0.000001 + track.Speed * 0.0005144444 * cos(track_angle_offset)  #closure in km/sec, plus 1mm to prevent div/zero when speed == 0
                try:
                    track.eta = (3600 / (track.range / track.closure))
                except:
                    track.eta = 0
                if (track.IsMissile() == 1):
                    track.air = 0
                else:
                    track.air = 1
                engage_mod = 1
                if ((((track.range - 50) / track.closure < 30) or (track.range < 40)) and track.IsAir()):
                    engage_mod = 2
                elif ((((track.range - 20) / track.closure < 15)  or (track.range < 20)) and track.IsMissile()):
                    engage_mod = 2
                score1 = 1 / (track.range / 50)
                score2 = track.eta
                score3 = 1 + (track.air * 0.2)
                try:
                    score4 = 1 / (track.approach / 1360)
                except:
                    score4 = 1 / (track.range / 1360)
                score5 = 100 / (track.range)
                score7 = engage_mod
                score = (score1 * score2 * score3 * score4 + score5) * score7
                if (len(AAW_high_score) == 0):
                    if (score >= 20000):
                        AAW_high_score = [score, track.ID, track.approach, track.eta, track.range, track.closure]
                elif (score > AAW_high_score[0]):
                    if (score >= 20000):
                        AAW_high_score = [score, track.ID, track.approach, track.eta, track.range, track.closure]
                aaw_target_list.append([score, track.ID, engage_mod, track.closure, track.air])

            elif ((staleness < 10) and (not track.IsDestroyed()) and track.IsValid() and (track.IsGround() or track.IsSurface())):
                track.range = UI.GetRangeToTrack(track)
                score1 = 1 / (track.range / 5000)
                score5 = 10000 / (track.range)
                if track.IsSurface():
                    score = (score1 * 400) + score5
                    if (len(ASuW_high_score) == 0):
                        if (score >= 20000):
                            ASuW_high_score = [score, track.ID]
                    elif (score > ASuW_high_score[0]):
                        if (score >= 20000):
                            ASuW_high_score = [score, track.ID]
                    asuw_target_list.append([score, track.ID])
                elif track.IsGround():
                    score = (score1 * 350) + score5
                    if (len(AGW_high_score) == 0):
                        if (score >= 20000):
                            AGW_high_score = [score, track.ID]
                    elif (score > AGW_high_score[0]):
                        if (score >= 20000):
                            AGW_high_score = [score, track.ID]
                    agw_target_list.append([score, track.ID])

            elif ((staleness < 10) and (not track.IsDestroyed()) and track.IsValid() and track.IsSub()):
                track.range = UI.GetRangeToTrack(track)
                score1 = 1 / (track.range / 5000)
                score5 = 10000 / (track.range)
                score = (score1 * 450) + score5
                if (len(ASW_high_score) == 0):
                    if (score >= 20000):
                        ASW_high_score = [score, track.ID]
                elif (score > ASW_high_score[0]):
                    if (score >= 20000):
                        ASW_high_score = [score, track.ID]
                asw_target_list.append([score, track.ID])

            if (track.IsSurface() and (track.range < nearest_surface)):
                nearest_surface = track.range
            if (track.IsAir() and (track.range < nearest_air)):
                nearest_air = track.range
            if (track.IsGround() and (track.range < nearest_land)):
                nearest_land = track.range
            if (track.IsMissile() and (track.range < nearest_missile)):
                nearest_missile = track.range
            if (track.IsSub() and (track.range < nearest_sub)):
                nearest_sub = track.range
                    
    aaw_target_list = sorted(aaw_target_list, reverse = True)
    asuw_target_list = sorted(asuw_target_list, reverse = True)
    agw_target_list = sorted(agw_target_list, reverse = True)
    asw_target_list = sorted(asw_target_list, reverse = True)
    aaw_target_list_guns = aaw_target_list

    Write_Message_List(BB, aaw_target_list, 'aaw_target_list')
    Write_Message_List(BB, aaw_target_list_guns, 'aaw_target_list_guns')
    Write_Message_List(BB, asuw_target_list, 'asuw_target_list')
    Write_Message_List(BB, agw_target_list, 'agw_target_list')
    Write_Message_List(BB, asw_target_list, 'asw_target_list')    
    Write_Message_List(BB, AAW_high_score, 'airthreat')
    Write_Message_List(BB, ASuW_high_score, 'seathreat')
    Write_Message_List(BB, AGW_high_score, 'landthreat')
    Write_Message_List(BB, ASW_high_score, 'subthreat')
    BB.WriteGlobal('nearest_surface', str(nearest_surface))
    BB.WriteGlobal('nearest_air', str(nearest_air))
    BB.WriteGlobal('nearest_land', str(nearest_land))
    BB.WriteGlobal('nearest_missile', str(nearest_missile))
    BB.WriteGlobal('nearest_sub', str(nearest_sub))

def AI_Navigation(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    TI.SetUpdateInterval(1)
    #check the helm priority
    helm_priority = Try_Read_Message(BB, 'helm_priority', 1)
    heading_change = 0
    
    if UI.IsFixed():
        TI.EndTask()#no point running this on an airbase for example.
    
    initialized = TI.GetMemoryValue(99)
    if not initialized:
        TI.SetMemoryValue(99,1)
        DeleteHiddenTask(UI, 'PointDefense')
        DeleteHiddenTask(UI, 'MissileWarning')
        if (not(UI.TaskExists('shallows_detection'))): 
            UI.AddTask('shallows_detection', 5, -1)
        if (not(UI.TaskExists('Nav_Priority'))): 
            UI.AddTask('Nav_Priority', 5, -1)
        if (not(UI.TaskExists('Catalog_Launchers_Amram'))): 
            UI.AddTask('Catalog_Launchers_Amram', 1, -1)
        BB.WriteGlobal('nothreat', '1')
    
    if helm_priority in [1, 4, 5, 6]:
        airthreat = Read_Message_List(BB, 'airthreat')
        seathreat = Read_Message_List(BB, 'seathreat')
        subthreat = Read_Message_List(BB, 'subthreat')
        threats = [airthreat] + [seathreat] + [subthreat]
        threats.sort()
            
    if helm_priority == 1:    #CIWS in control
        nothreat = Try_Read_Message(BB, 'nothreat', 1)
        if nothreat:
            pass
        else:
            unmask_heading = unmask_weapons_heading(UI, threats)
            heading = unmask_heading
            heading_change = 1

    elif helm_priority == 2:  #avoid grounding the ship
        pass  #shouldn't trigger currently
    
    elif helm_priority == 3:  #avoid colliding with other ships
        pass  #shouldn't trigger currently
    
    elif helm_priority == 4:  #keep the FC unmasked
        nothreat = Try_Read_Message(BB, 'nothreat', 1)
        if nothreat:
            pass
        else:
            unmask_heading = unmask_weapons_heading(UI, threats)
            FC_unmask_heading = find_fc_FOV_limits(UI, BB, unmask_heading)
            heading = FC_unmask_heading
            heading_change = 1

    elif helm_priority == 5:  #keep launchers unmasked
        nothreat = Try_Read_Message(BB, 'nothreat', 1)
        if nothreat:
            pass
        else:
            unmask_heading = unmask_weapons_heading(UI, threats)
            heading = unmask_heading
            heading_change = 1
        
    elif helm_priority == 6:  #pursue targets
        pass
   
    elif helm_priority == 7:  #patrol
        #terminate waypoints, and formations and begin patrols
        patrol_state = Try_Read_Message(BB, 'Patrol_State', 0)
        valid_states = ['in_progress', 'transit']
        if patrol_state in valid_states:
            if patrol_state == 'transit':
                speed = Try_Read_Message(BB, 'Patrol_Transit_Pace',2)    #pace of transit to patrol point
            else:
                speed = Try_Read_Message(BB, 'Patrol_Patrol_Pace',2)      #pace during patrol
            next_point = Read_Message_List(BB, 'Patrol_datum_a')                 #next datum
            try:
                heading = UI.GetHeadingToDatum(next_point[0], next_point[1])
            except:
                heading = UI.GetHeading()
            heading_change = 1
        elif patrol_state == 'resume':
            BB.WriteGlobal('Patrol_State', 'transit')
        elif patrol_state == 'suspended':
            #we're suspended, so do nothing
            pass
        elif patrol_state == 'no_datum':
            pass
        elif patrol_state == '':
            BB.WriteGlobal('Patrol_State', 'transit')         
    
    elif helm_priority == 8:  #loiter/nav task/formations
        #resume formations and waypoints
        Override_Nav_Waypoint(UI, '', 'remove')
        resume_saved_formation(BB, UI)
        
    #take action now
    if ((helm_priority in [1, 2, 3, 4, 5, 6, 7]) and (heading_change == 1)):
        save_formation(BB, UI)
        if UI.TaskExists('Nav'):  #-then we have waypoints.
            if helm_priority == 7:  #on patrol- kill waypoints
                UI.DeleteTask('Nav')
            else:   #not on patrol, just need to over-rule the waypoints temporarily.
                Override_Nav_Waypoint(UI, heading, 'insert')
        try:
            #sometimes we prematurely end other sections, and they cause heading to come out as a nonetype, which breaks everything
            #so, try it, if it fails, just keep our current heading for now
            UI.SetHeading(heading)
        except:
            pass
        try:
            #sometimes we prematurely end other sections, and they cause heading to come out as a nonetype, which breaks everything
            #so, try it, if it fails, just keep our current heading for now
            UI.SetSpeed(speed)
        except:
            pass
        
def Catalog_Launchers_Amram(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
# 0 - datum, 1 - seeker, 2 - bomb, 3 - other
    if not(UI.TaskExists('AI_Weaponry')) or not(UI.TaskExists('AI_Navigation')):
        #neither nav no weapons is active, shut this down to release resources.
        TI.EndTask()

    Flagfree1 = Try_Read_Message(BB,'Flagfree1',1)
    Flagfree2 = Try_Read_Message(BB,'Flagfree2',1)
    Flagfree4 = Try_Read_Message(BB,'Flagfree4',1)
    Flagfree8 = Try_Read_Message(BB,'Flagfree8',1)
    Flagfree16 = Try_Read_Message(BB,'Flagfree16',1)
    L04a = []
    L04m = []
    L04lg = []
    L04sg = []
    L12a = []
    L12m = []
    L12lm = []
    L12sm = []
    L0124tp = []
    launcher_catalog = []
    sea_max_range = 0
    air_max_range = 0
    land_max_range = 0
    missile_max_range = 0
    sea_max_range_gun = 0
    air_max_range_gun = 0
    land_max_range_gun = 0
    missile_max_range_gun = 0
    sub_max_range = 0
    CIWS_range = 0
    HaveMissile = False
    HaveGun = False
    HaveTorp = False
    for n in range(0, UI.GetLauncherCount()):
        launcher = UI.GetLauncherInfo(n)
        weaponname = UI.GetLauncherWeaponName(launcher.Launcher)
        mode = launcher.LaunchMode
        if (AntiShipMissile(UI, weaponname) and Flagfree1):
            L12sm.append([launcher.MaxRange_km, n])
            HaveMissile = True
            if launcher.MaxRange_km > sea_max_range:
                sea_max_range = launcher.MaxRange_km
        if (AntiAirMissile(UI, weaponname) and Flagfree2):
            L12a.append([launcher.MaxRange_km, n])
            HaveMissile = True
            if launcher.MaxRange_km > air_max_range:
                air_max_range = launcher.MaxRange_km
        if (AntiLandMissile(UI, weaponname) and Flagfree4):
            L12lm.append([launcher.MaxRange_km, n])
            HaveMissile = True
            if launcher.MaxRange_km > land_max_range:
                land_max_range = launcher.MaxRange_km
        if (AntiMissileMissile(UI, weaponname) and Flagfree8):
            L12m.append([launcher.MaxRange_km, n])
            HaveMissile = True
            if launcher.MaxRange_km > missile_max_range:
                missile_max_range = launcher.MaxRange_km
        if not(AntiShipMissile(UI, weaponname) or AntiAirMissile(UI, weaponname) or AntiLandMissile(UI, weaponname) or AntiMissileMissile(UI, weaponname) or AntiSubMissile(UI, weaponname)):
            if (((launcher.TargetFlags & 1) != 0) and Flagfree1):
                L04sg.append([launcher.MaxRange_km, n])
                HaveGun = True
                if launcher.MaxRange_km > sea_max_range_gun:
                    sea_max_range_gun = launcher.MaxRange_km
            if (((launcher.TargetFlags & 2) != 0) and Flagfree2):
                L04a.append([launcher.MaxRange_km, n])
                HaveGun = True
                if launcher.MaxRange_km > air_max_range_gun:
                    air_max_range_gun = launcher.MaxRange_km
            if (((launcher.TargetFlags & 4) != 0) and Flagfree4):
                L04lg.append([launcher.MaxRange_km, n])
                HaveGun = True
                if launcher.MaxRange_km > land_max_range_gun:
                    land_max_range_gun = launcher.MaxRange_km
            if (((launcher.TargetFlags & 8) != 0) and Flagfree8):
                L04m.append([launcher.MaxRange_km, n])
                HaveGun = True
                if launcher.MaxRange_km > missile_max_range_gun:
                    missile_max_range_gun = launcher.MaxRange_km
                    if ((launcher.LaunchMode == 4) and (launcher.MaxRange_km > CIWS_range)):
                        CIWS_Range = launcher.MaxRange_km
            if (((launcher.TargetFlags & 16) != 0) and Flagfree16):
                L0124tp.append([launcher.MaxRange_km, n])
                HaveTorp = True
                if launcher.MaxRange_km > sub_max_range:
                    sub_max_range = launcher.MaxRange_km
        launcher_catalog.append([launcher.Launcher, weaponname])
    L04a.sort()
    L04m.sort()
    L12a.sort()
    L12m.sort()
    L04lg.sort()
    L04sg.sort()
    L12lm.sort()
    L12sm.sort()
    L0124tp.sort()
    Write_Message_List(BB, L04a, 'L04a')
    Write_Message_List(BB, L04m, 'L04m')
    Write_Message_List(BB, L04lg, 'L04lg')
    Write_Message_List(BB, L04sg, 'L04sg')
    Write_Message_List(BB, L12a, 'L12a')
    Write_Message_List(BB, L12m, 'L12m')
    Write_Message_List(BB, L12lm, 'L12lm')
    Write_Message_List(BB, L12sm, 'L12sm')
    Write_Message_List(BB, L0124tp, 'L0124tp')
    Write_Message_List(BB, launcher_catalog, 'launcher_catalog')
    BB.WriteGlobal('WO_done_catalog', '1')
    BB.WriteGlobal('sea_max_range', str(sea_max_range))
    BB.WriteGlobal('air_max_range', str(air_max_range))
    BB.WriteGlobal('land_max_range', str(land_max_range))
    BB.WriteGlobal('missile_max_range', str(missile_max_range))
    BB.WriteGlobal('sea_max_range_gun', str(sea_max_range_gun))
    BB.WriteGlobal('air_max_range_gun', str(air_max_range_gun))
    BB.WriteGlobal('land_max_range_gun', str(land_max_range_gun))
    BB.WriteGlobal('missile_max_range_gun', str(missile_max_range_gun))
    BB.WriteGlobal('sub_max_range', str(sub_max_range))
    BB.WriteGlobal('CIWS_range', str(CIWS_range))
    if HaveMissile and (not(UI.TaskExists('Msl_Attack'))): 
        UI.AddTask('Msl_Attack', 1, -1)
    if HaveGun and (not(UI.TaskExists('Gun_Attack'))): 
        UI.AddTask('Gun_Attack', 0.2, -1)
    if HaveTorp and (not(UI.TaskExists('Trp_Attack'))): 
        UI.AddTask('Trp_Attack', 6, -1)
    TI.EndTask()

def bearing_to_relative(UI, bearing):
    rel_tgt_bearing = bearing - UI.GetHeading()
    while rel_tgt_bearing < 0:
        rel_tgt_bearing += 360
    while rel_tgt_bearing > 360:
        rel_tgt_bearing -= 360
    return rel_tgt_bearing
    
def find_nearest_aspect(UI, rel_tgt_bearing, max_aspect_list):
    rel_tgt_bearing = round(rel_tgt_bearing/az_piece,0)
    if rel_tgt_bearing == 360/az_piece:
        rel_tgt_bearing = 0
    aspect = rel_tgt_bearing   #this is set so that if the following section doesn't change it, we pass on the current aspect.
    if rel_tgt_bearing not in max_aspect_list:
        aspect_left = []
        aspect_right = []
        for x in range(0, len(max_aspect_list)):
            if (max_aspect_list[x] < rel_tgt_bearing):
                aspect_left.append(max_aspect_list[x])
            else:
                aspect_right.append(max_aspect_list[x])
        try:
            aspect_left[0]
        except:
            aspect_left = [-10000]
        try:
            aspect_right[0]
        except:
            aspect_right = [10000]
        aspect_left = max(aspect_left)
        aspect_right = min(aspect_right)
        if(abs(rel_tgt_bearing - aspect_left) < abs(aspect_right - rel_tgt_bearing)):
            aspect = aspect_left
        elif (abs(rel_tgt_bearing - aspect_left) > abs(aspect_right - rel_tgt_bearing)):
            aspect = aspect_right
        else:
            if (rel_tgt_bearing >0):
                aspect = aspect_left
            else:
                aspect = aspect_right
    aspect = aspect * az_piece
    return aspect
    
def find_fc_FOV_limits(UI, BB, unmask_heading):
    while unmask_heading > 360:
        unmask_heading -= 360
    while unmask_heading <0:
        unmask_heading += 360
    engaged_targets = Read_Message_List(BB, 'engaged_targets')
    max_left = -360
    max_right = 360
    if len(engaged_targets) > 0:
        for x in range(0, len(engaged_targets)):
            if engaged_targets[x][5] == 2:
                track = UI.GetTrackById(engaged_targets[x][1])
                if track.IsValid():
                    if engaged_targets[x][3] > 180:
                        center = engaged_targets[x][3] - 360
                    else:
                        center = engaged_targets[x][3]
                    wide = engaged_targets[x][4] * 0.475
                    heading = UI.GetHeading()
                    bearing = UI.GetHeadingToDatum(track.Lon, track.Lat)
                    relative_bearing = bearing - heading
                    if relative_bearing < -180:
                        relative_bearing += 360
                    if relative_bearing > 180:
                        relative_bearing -= 360
                    relative_fc_bearing = relative_bearing - center
                    if relative_fc_bearing < -180:
                        relative_fc_bearing += 360
                    if relative_fc_bearing > 180:
                        relative_fc_bearing -= 360
                    fc_left = - wide + relative_fc_bearing
                    fc_right = wide + relative_fc_bearing
                    if max_left < fc_left:
                        max_left = fc_left
                    if max_right > fc_right:
                        max_right = fc_right

    #adjust heading based upon FC needs
    fc_heading = 'none'
    if ((max_left > 0) or (max_right < 0)):
        #max_left and Max_right are available headroom, so if they exceed their limits, then you MUST maneuver.
        if (max_left > 0):
            fc_heading = max_left
        elif (max_right < 0):
            fc_heading = max_right

            
    fc_heading_change = False
    if (fc_heading_change and (unmask_heading < max_left)):
        unmask_heading = max_left
    elif (fc_heading_change and (unmask_heading > max_right)):
        unmask_heading = max_right
    elif ((type(unmask_heading) is not float) and (type(fc_heading) is float)):
        unmask_heading = UI.GetHeading() + fc_heading
    
    return unmask_heading

def form_max_aspect_list(UI, track, track_type):
    capable = False
    aspects = [0] * segments 
    for L in range(0, UI.GetLauncherCount()):
        launcher = UI.GetLauncherInfo(L)
        if ((launcher.TargetFlags & track_type) != 0):
            if(((UI.GetRangeToTrack(track) >= launcher.MinRange_km) and (UI.GetRangeToTrack(track) <= (launcher.MaxRange_km + 5)))):
                capable = True
                az_list = [0] * segments 
                center = int(launcher.SectorCenter / az_piece)
                wide = int(launcher.SectorWidth / (2 * az_piece))
                left = center - wide
                right = center + wide

                if(left < 0):
                    offset = segment - left
                else:
                    offset = 0
                if(right > segment):
                    offset2 = right - segment
                else:
                    offset2 = 0
                if((round(launcher.SectorCenter-(0.5 * launcher.SectorWidth)) <= 0) or (round(launcher.SectorCenter+(0.5 * launcher.SectorWidth)) >= 360)):
                    az_list[0] = 1
                if((round(launcher.SectorCenter-(0.5 * launcher.SectorWidth)) >= 0) and (round(launcher.SectorCenter+(0.5 * launcher.SectorWidth)) < 360)):
                    az_list[-1] = 0
                while offset < 0:
                    id = offset-segment
                    az_list[id] = 1
                    offset = offset + 1
                    left = left + 1
                while offset2 > 0:
                    az_list[offset2] = 1
                    offset2 = offset2 - 1
                    right = right - 1
                offset3 = left
                while offset3 <= right:
                    az_list[offset3] = 1
                    offset3 = offset3 + 1
                for i in range(0, segments):            # See line 14
                    aspects[i] = aspects[i] + az_list[i]
    return capable, aspects
    
def unmask_weapons_heading(UI, threats):
    BB = UI.GetBlackboardInterface()
    nothreat = Try_Read_Message(BB, 'nothreat', 1)
    if nothreat == 0:
        #I keep getting errors, the script gets this far, which means it DOES have threats, yet when it gets here it throws threat related errors
        #going to do a try/except.  If it works off the hop, it proceeds, if not, it tryes to collect threat info itself instead of what it was given
        #failing that, it clears everything threat related and exits the script since it should not have been run due to no threats to work on.
        try:
            #try to get the highest threat form the threats passed to us
            #typically, this is the section that is run.
            high_threat = threats[-1]
            track = UI.GetTrackById(int(high_threat[1]))
        except:
            #failing that, get the threats ourselves, and try again
            #occasionally, due to scripts running out of sync, this is set to run, yet the threat has died, but the list not updated
            #so re-ask for the threats, and see.  Doesn't catalog the targets, just pulls the lists again and resorts it.
            airthreat = Read_Message_List(BB, 'airthreat')
            seathreat = Read_Message_List(BB, 'seathreat')
            subthreat = Read_Message_List(BB, 'subthreat')
            threats = [airthreat] + [seathreat] + [subthreat]
            threats.sort()
            try:
                high_threat = threats[-1]
                #try again to get the highest threat
                track = UI.GetTrackById(int(high_threat[1]))
                high_threat = threats[-1]
                track = UI.GetTrackById(int(high_threat[1]))
            except:
                #failing that, pass an empty list to prevent the whole block from operating.
                threats = []

            
            
    capable = False
    if len(threats)>0:
        for x in range(0, len(threats)):
            #iterate over all threats until we find the one we will work on.
            high_threat = threats[-1]
            track = UI.GetTrackById(int(high_threat[1]))
            track_type = 0
            if ((not track.IsDestroyed) or track.IsValid()):
                if track.IsSurface():
                    track_type = 1
                elif track.IsAir():
                    track_type = 2
                elif track.IsGround():
                    track_type = 4
                elif track.IsMissile():
                    track_type = 8
                elif track.IsSub():
                    track_type = 16
            capable, aspects = form_max_aspect_list(UI, track, track_type)
            if capable:  #we have a target we can respond to, in the sorted order
                         #so stop looking for more, break the for loop.
                break

        if capable:
            #discover if we must turn to unmask, and order such if needed.
            max_aspect_list = []
            max_aspect = max(aspects)
            for x in range(0, len(aspects)):
                if aspects[x] == max_aspect:
                    max_aspect_list.append(x)

            tgt_bearing = UI.GetHeadingToDatum(track.Lon, track.Lat)
            rel_tgt_bearing = bearing_to_relative(UI, tgt_bearing)

            aspect = find_nearest_aspect(UI, rel_tgt_bearing, max_aspect_list)
        
            if (aspect > 180):
                aspect -= 360
            heading = UI.GetHeading()
            if heading < 0:
                heading += 360
            unmask_heading = rel_tgt_bearing - aspect + heading
                #this is a relative target bearing, aligned to the ships heading,
                #the aspect in segments as defined at the beginning of this file, 
                #and the ships current heading, converted to a new heading which
                #puts the target bearing inside the ships best weapon arcs.        
            return unmask_heading
    else:
        #if there are no threats, then just return our current heading
        return UI.GetHeading()

def shallows_detection(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    if not(UI.TaskExists('AI_Navigation')):
        TI.EndTask()
    elif not UI.IsSurface() and not UI.IsSub():
        TI.EndTask()   

    #we CANNOT plot terrain away from the ship, so this entire block is a fail at current.
    if TI.GetMemoryValue(666) == 1:
        velocity = UI.GetSpeed()
        velocity = velocity * 0.000514444  #convert to kilometers per second
        ownship = UI.GetTargetTrackInfo(UI.SetTarget(UI.LookupFriendlyId(UI.GetName())))
        ownship = ownship.Offset(600 * velocity, 0)
        min10 = UI.GetMapTerrainElevation(ownship.Longitude, ownship.Latitude)
        ownship = ownship.Offset(300 * velocity, 0)
        min5 = UI.GetMapTerrainElevation(ownship.Lon, ownship.Lat)
        ownship = ownship.Offset(60 * velocity, 0)
        min1 = UI.GetMapTerrainElevation(ownship.Lon, ownship.Lat)
        
        init  = TI.GetMemoryValue(13)
        init2 = TI.GetMemoryValue(14)
        init3 = TI.GetMemoryValue(15)
        if min10 >-30:
            #time to be concerned, shallow water ahead
            if not init:
                UI.DisplayPopupMessage('shallow water(-30m)')
                TI.SetMemoryValue(13,1)
            TI.SetUpdateInterval(75)
        elif min5 > -20:
            #time to be VERY concerned
            if not init2:
                UI.DisplayPopupMessage('very shallow water(-20m)')
                TI.SetMemoryValue(14,1)
            TI.SetUpdateInterval(40)
        elif min1 > -20:
            if not init3:
                UI.DisplayPopupMessage('critically shallow(-20m), all stop')
                TI.SetMemoryValue(15,1)
            TI.SetUpdateInterval(20)
        else:
            #we're still deep, all is well.
            TI.SetUpdateInterval(150)
            TI.SetMemoryValue(13,0)
            TI.SetMemoryValue(14,0)
            TI.SetMemoryValue(15,0)
            
        if init2:
            #we have shallows less than 5 minutes away at current velocity, or inside 4.1km at 30kts
            #find a good angle that gets us out of the shallows to a distance of 20km or more, request that heading
            for x in range(0,35):
                angleXr = x
                spokeY = []
                angleunit = 0.174533 / 2
                for y in range(0,39):
                    ownship = UI.GetTrackById(UI.LookupFriendlyId(UI.GetName()))
                    ownship.Offset((y*0.5)+1, angleunit + (angleunit * x))
                    depthX = UI.GetMapTerrainElevation(ownship.Lon, ownship.Lat)
                    spokeY.append(depthX)
                if max(spokeY) <-99:
                    angle = angleunit + (angleunit * x)
                    break
                
                angleXl = -x
                spokeY = []
                angleunit = 0.174533 / 2
                for y in range(0,39):
                    ownship = UI.GetTrackById(UI.LookupFriendlyId(UI.GetName()))
                    ownship.Offset((y*0.5)+1, 1- (angleunit + (angleunit * x)))
                    depthX = UI.GetMapTerrainElevation(ownship.Lon, ownship.Lat)
                    spokeY.append(depthX)
                if max(spokeY) < -99:
                    angle = angle = 1- (angleunit + (angleunit * x))
                    break
            
            BB.WriteGlobal('TerrainHeading',str(angle))
    terrain = UI.GetMapTerrainElevation(UI.GetLatitude(), UI.GetLongitude())
        
    init  = TI.GetMemoryValue(13)
    init2 = TI.GetMemoryValue(14)
    init3 = TI.GetMemoryValue(15)
    if terrain >-50:
        #time to be concerned, shallow water ahead
        if not init:
            UI.DisplayPopupMessage('shallow water(-50m)')
            TI.SetMemoryValue(13,1)
        TI.SetUpdateInterval(75)
    elif terrain > -30:
        #time to be VERY concerned
        if not init2:
            UI.DisplayPopupMessage('shallow water(-30m)')
            TI.SetMemoryValue(14,1)
        TI.SetUpdateInterval(40)
    elif terrain > -20:
        if not init3:
            UI.DisplayPopupMessage('critically shallow(-20m), sll stop')
            BB.WriteGlobal('TerrainStop','1')
            TI.SetMemoryValue(15,1)
        TI.SetUpdateInterval(20)
    else:
        #we're still deep, all is well.
        TI.SetUpdateInterval(150)
        TI.SetMemoryValue(13,0)
        TI.SetMemoryValue(14,0)
        TI.SetMemoryValue(15,0)
        BB.WriteGlobal('TerrainHeading','')
        BB.WriteGlobal('TerrainStop','')

def Override_Nav_Waypoint(UI, heading, state):
    BB = UI.GetBlackboardInterface()

    active_nav_override = Try_Read_Message(BB, 'active_nav_override', 1)
    
    if state == 'insert':
        Xco = math.sin(heading) * 0.002
        Yco = math.cos(heading) * 0.002
        if active_nav_override == 0:
            UI.InsertNavWaypoint(0, UI.GetLongitude() + Xco, UI.GetLatitude() + Yco)
            BB.WriteGlobal('active_nav_override', '1')
        elif active_nav_override == 1:
            UI.EditNavWaypoint(0, UI.GetLongitude() + Xco, UI.GetLatitude() + Yco)
    elif (state == 'remove') and (active_nav_override == 1):
        BB.WriteGlobal('active_nav_override', '0')
        UI.DeleteNavWaypoint(0)
    
def Nav_Priority(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    TI.SetUpdateInterval(5)
    #handles deciding what helm should be doing at any one time, things like terrain avoidance, or chasing targets or waypoints
    if not(UI.TaskExists('AI_Navigation')):
        TI.EndTask()
    
    #get airthreat
    #if airthreat within 2x CIWS range and approaching, CIWS rules.
    engaged_targets = Read_Message_List(BB, 'engaged_targets')
    CIWS_range = BB.ReadMessage('CIWS_range')
    TerrainHeading = BB.ReadMessage('TerrainHeading')
    TerrainStop = BB.ReadMessage('TerrainStop')
    friendly_range = UI.GetSpeed() * 7 * 0.000514444 + 0.5
    friendly_ships = UI.GetTrackList(0x0010, friendly_range, 1)
    non_friendly_ships = UI.GetTrackList(0x0010, friendly_range, 4)
    nearby_ship_list = friendly_ships
    for n in range(0,non_friendly_ships.Size()):
        nearby_ship_list.append(non_friendly_ships[n])
    helm_priority = TI.GetMemoryValue(1)
    PursueTarget = BB.ReadMessage('PursueTarget')
    PatrolType = BB.ReadMessage('Patrol_Type')

    sea_max_range = max(Try_Read_Message(BB, 'sea_max_range', 2), Try_Read_Message(BB, 'sea_max_range_gun', 2))
    air_max_range = max(Try_Read_Message(BB, 'air_max_range', 2), Try_Read_Message(BB, 'air_max_range_gun', 2))
    land_max_range = max(Try_Read_Message(BB, 'land_max_range', 2), Try_Read_Message(BB, 'land_max_range_gun', 2))
    missile_max_range = max(Try_Read_Message(BB, 'missile_max_range', 2), Try_Read_Message(BB, 'missile_max_range_gun', 2))
    sub_max_range = Try_Read_Message(BB, 'sub_max_range', 2)
    nearest_surface = Try_Read_Message(BB, 'nearest_surface', 2)
    nearest_air = Try_Read_Message(BB, 'nearest_air', 2)
    nearest_land = Try_Read_Message(BB, 'nearest_land', 2)
    nearest_missile = Try_Read_Message(BB, 'nearest_missile', 2)
    nearest_sub = Try_Read_Message(BB, 'nearest_sub', 2)
    Flagfree1 = Try_Read_Message(BB, 'Flagfree1', 1)
    Flagfree2 = Try_Read_Message(BB, 'Flagfree2', 1)
    Flagfree4 = Try_Read_Message(BB, 'Flagfree4', 1)
    Flagfree8 = Try_Read_Message(BB, 'Flagfree8', 1)
    Flagfree16 = Try_Read_Message(BB, 'Flagfree16', 1)

    unmask = 0
    if    ((Flagfree1 and sea_max_range * 1.1    > nearest_surface)
        or (Flagfree2 and air_max_range * 1      > nearest_air)
        or (Flagfree4 and land_max_range         > nearest_land)
        or (Flagfree8 and missile_max_range *1.2 > nearest_missile)
        or (Flagfree16 and sub_max_range         > nearest_sub)):
        unmask = 1
        
    airthreat = Read_Message_List(BB, 'airthreat')
    seathreat = Read_Message_List(BB, 'seathreat')
    subthreat = Read_Message_List(BB, 'subthreat')
    nothreat = Read_Message_List(BB, 'nothreat')
    threatened = 0
    if ((len(airthreat)>0) or (len(seathreat)>0) or (len(subthreat)>0)):
        threats = [airthreat] + [seathreat] + [subthreat]
        threats.sort()
        BB.WriteGlobal('nothreat', '0')
        nothreat = 0
    else:
        BB.WriteGlobal('nothreat', '1')
        nothreat = 1

    
    need_fc = 0
    for n in range(0,len(engaged_targets)):
        target = engaged_targets[n]
        launcher = UI.GetLauncherInfo(target[2])
        need_fc = launcher.FireControlTracks
        if need_fc > 1:
            need_fc = 1
            break    

    helm_priority = 8
    actiontext = '8) idle'
            
    if   ((len(airthreat) > 0) and ((airthreat[4] - 3) / airthreat[5] < 8) and (airthreat[2] <2)):
        #assuming Nimitz TurnRate, and a 60 deg turn, so providing 7.5 second lead time minimum, using 8 seconds
        #8 seconds at mach1 = 6.1km, mach2 = 12.2km, mach3 = 18.3km, mach4 = 24.5km
        #airthreat4 is track range, airthreat 5 is closure rate.  Checking if 8 seconds from being 3km away.
        #if so, we have a CIWS threat situation, Priority is 0
        helm_priority = 1
        TI.SetUpdateInterval(1)
        actiontext = '1) CIWS'
    elif ((TerrainHeading != '') or (TerrainStop == '1')):
        #we have a terrain situation that needs resolving
        helm_priority = 2
        actiontext = '2) terrain'
    elif nearby_ship_list.Size() > 0:
        #checks for ships within a distance defined by current speed and turn rate.
        #want a 30deg offset from friendlies inside 1km, 15deg offset from friendlies inside 2km
        #at 8deg/sec this only requires 3.5 seconds to perform, so we check 7 seconds +500m ahead.
        for n in range(0,nearby_ship_list.Size()):
            nearby_ships = []
            track = nearby_ship_list.GetTrack(n)
            track.bearing = UI.GetHeadingToDatum(track.Lat,track.Lon)
            track.range = UI.GetRangeToTrack(track)
            if   ((track.range < 2) and (abs(track.bearing) < 15)):
                nearby_ships.append(track.range, track.ID, track.bearing,15)
            elif ((track.range < 1) and (abs(track.bearing) < 30)):
                nearby_ships.append(track.range, track.ID, track.bearing,30)
        if len(nearby_ships) > 0:
            nearby_ships.sort()
            BB.WriteGlobal('CollisionHeading',str(nearby_ships[3] + UI.GetHeading()))
            helm_priority = 3
            actiontext = '3) collision'
    elif need_fc:
        helm_priority = 4
        actiontext = '4) FC unmask'
    elif unmask:
        helm_priority = 5
        actiontext = '5) launcher unmask'
    elif PursueTarget != '':
        helm_priority = 6
        actiontext = '6) intercept'
    elif PatrolType != '':
        helm_priority = 7
        actiontext = '7) patrol'


    if ((len(airthreat) > 0) and ((airthreat[4] - 3) / airthreat[5] < 13) and (airthreat[2] <2) and (helm_priority != 1)):
        #its not time to maneuver for CIWS just yet, but it is closer than our next iteration
        #so schedule an update for just after it enters priority 1 range.
        interval = (airthreat[4] - 3) / airthreat[5] - 8.1
        TI.SetUpdateInterval(interval)
    
        
    UI.SetActionText(actiontext)
    BB.WriteGlobal('helm_priority', str(helm_priority))

def resume_saved_formation(BB, UI):
    old_formation = Read_Message_List(BB, 'old_formation')
    if old_formation != []:
        track = UI.GetTrackById(old_formation[0])
        range_km = old_formation[1] / 1000
        UI.SetFormationLeader(old_formation[0])
        UI.SetFormationPosition(range_km, 4, 0.0174532925 * old_formation[2] - track.Heading_rad, math.atan(4/range_km))
        UI.SetFormationMode(int(old_formation[3]))
        BB.WriteGlobal('old_formation', '')

def save_formation(BB, UI):
    if ((type(UI.GetFormationLeader()) is int) and (UI.GetFormationLeader() > 0) and (not UI.IsFormationLeader())):  #-seems helm really hated trying to break formation when it was formation leaders.
        track = UI.GetTrackById(long(UI.GetFormationLeader()))
        bearing = UI.GetHeadingToDatum(track.Lon, track.Lat)
        range_m = UI.GetRangeToTrack(track) * 1000
        if bearing < 0:
            bearing += 360
        formation_bearing = bearing + 180
        if formation_bearing > 360:
            formation_bearing -= 360
        old_formation = (UI.GetFormationLeader(), range_m, formation_bearing, UI.GetFormationMode(), UI.GetFormationEditId())
        Write_Message_List(BB, old_formation, 'old_formation')    
        UI.SetFormationLeader(-1)

def Drop_Targets(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    TI.SetUpdateInterval(0.5)

    #drop targets.
    if (UI.GetTarget() != -1):
        last_target_time = UI.GetTime()
        track = UI.GetTargetTrackInfo()
        max_range = 0
        if track.IsSurface():
            max_range = float(BB.ReadMessage('sea_max_range'))
        elif track.IsAir():
            max_range = float(BB.ReadMessage('air_max_range'))
        elif track.IsGround():
            max_range = float(BB.ReadMessage('land_max_range'))
        elif track.IsMissile():
            max_range = float(BB.ReadMessage('missile_max_range')) * 2
        elif track.IsSub():
            max_range = float(BB.ReadMessage('sub_max_range'))
        staleness = UI.GetTime() - track.Time
        if ((UI.GetRangeToTrack(track) > max_range) or track.IsDestroyed() or (staleness >= 5) or (not track.IsValid())):
            UI.SetTarget(UI.LookupFriendlyId(UI.GetName()))
            UI.SetTarget(-1)
        TI.SetMemoryValue(13,last_target_time)
    
    #see if we should end this task ourselves
    last_target_time = TI.GetMemoryValue(13)
    current_time = UI.GetTime()
    if current_time > last_target_time + 3:
        #if we haven't had a target for three seconds, end the task.
        TI.EndTask()

def Read_Message_List(BB, msg_name):
    try:
        msg_item = BB.ReadMessage(msg_name)
        msg_item = loads(msg_item)
    except:
        msg_item = []
    return msg_item
    
def Write_Message_List(BB, msg_list, msg_name):
    msg_list = dumps(msg_list, HIGHEST_PROTOCOL)
    BB.WriteGlobal(msg_name, msg_list)

def Try_Read_Message(BB, msg_name, msg_type):
    if msg_type == 0:  #string
        try:
            msg_item = BB.ReadMessage(msg_name)
        except:
            msg_item = ''
    elif msg_type == 1:  #int
        try:
            msg_item = int(BB.ReadMessage(msg_name))
        except:
            msg_item = 0
    elif msg_type == 2:  #float
        try:
            msg_item = float(BB.ReadMessage(msg_name))
        except:
            msg_item = 0
    return msg_item
        
def DeleteHiddenTask(UI, taskname):  #Thanks to 4rk for this function
    if(UI.TaskExists(taskname)):
        UI.AddTask(taskname, -1, 0)   #unhides the hidden task so it can be removed.
        UI.DeleteTask(taskname)

def Get_Engage_Limit_Amram(target_info):
    if target_info.IsAir():
        return 1
    elif target_info.IsMissile():
        return 1
    elif target_info.IsSurface():
        return 15
    elif target_info.IsGround():
        if target_info.Classification == 257: #airfield
            return 30
        elif target_info.Classification == 258: #ground vehicle, maybe mobile sam
            return 6
        else : #building, or sam site, or...etc
            return 16
    else:
        return 1