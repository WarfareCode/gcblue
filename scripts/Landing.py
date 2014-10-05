from UnitCommands import *
from SubTactics import *
from GCBcommon import *
import math

from Amram_Utilities import *

#  added aerial refueling scripts to this, 
# so now has both landing and aerial refueling with tanker aircraft


# call to cancel tasks like InterceptTarget when landing
# workaround for now, need smarter way to cancel existing tasks
def CancelTasksForLanding(UI):
    UI.SetLandingState(0)
    UI.SetPitchLimit(85.0)
    UI.SetMaxTurnRate(360.0)
    UI.SetFormationLeader(-1) # leave formation if in formation
    kill_list = [   'Nav',
                    'InterceptTarget',
                    'IntC',
                    'PatrolCircle',
                    'AirPatrolArea',
                    'ASWPatrolArea',
                    'BarrierPatrol',
                    'GroundStrike',
                    'BombDatum', 
                    'BombRun', 
                    'Strafing', 
                    'AirIntercept',
                    'Air_Patrol']

    nKill = len(kill_list)
    for n in range(0, nKill):
        if (UI.TaskExists(kill_list[n])):
            UI.DeleteTask(kill_list[n])
            
# for non-helo aircraft
def Land(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    if (UI.IsHelo()):
        UI.AddTask('LandHelo', 4.0, 0)
        TI.EndTask()
        return
    
    #if (not GetConnControl(BB)):
    #    return

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryText('Description', 'Land at designated airbase')
        TI.SetMemoryValue(2, 0) # 0 - init, 1 - distant, 2 - init approach, 3 - final approach
        dest_name = BB.ReadMessage('LandTarget')
        dest_id = UI.LookupFriendlyId(dest_name)
        if (dest_id == -1):
            # try home base
            home_base = GetHomeBase(UI)
            dest_id = UI.LookupFriendlyId(home_base)
            if (dest_id == -1):
                UI.DisplayMessage('Bad landing target (%s)' % dest_name)
                UI.DisplayPopupMessage('Need alternate landing field')
                TI.EndTask()
                return
        TI.SetMemoryValue(3, dest_id)
        CancelTasksForLanding(UI)
        UI.SetLandingState(0)
        UI.SetPitchLimit(85)
        cruise_alt_m = GetCruiseAltitude(UI)
        TI.SetMemoryValue(15, cruise_alt_m)

    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)
    
    

    land_state = TI.GetMemoryValue(2)
    dest_id = long(TI.GetMemoryValue(3))
    track_info = UI.GetTrackById(dest_id)
    cruise_alt_m = TI.GetMemoryValue(15)
    
    alt_m = track_info.Alt
    if (track_info.ID == -1):
        dest_name = BB.ReadMessage('LandTarget')
        UI.DisplayMessage('Bad track ID for landing (%d, %s)' % (dest_id, dest_name))
        TI.EndTask()
        return # invalid id

    landing_data = UI.GetLandingData(dest_id)
    if (landing_data.ID == -1):
        UI.DisplayMessage('Invalid landing destination')
        TI.EndTask()
        return # invalid id

    track_info.Lat = landing_data.Lat
    track_info.Lon = landing_data.Lon
    track_info.Alt = landing_data.Alt
    
    # adjust track location based on approach state
    if (land_state <= 1):
        if (land_state == 0):
            base_name = UI.LookupFriendlyName(track_info.ID)
            UI.DisplayMessage('Landing %s' % base_name)
        UI.SetPitchLimit(15)
        UI.SetThrottle(0.7)
        TI.SetMemoryValue(2, 1)
        track_info.Offset(6, landing_data.Heading_rad + 3.1416)  # final approach
        track_info.Offset(6, landing_data.Heading_rad + 1.5708)  # base leg
        range_km = UI.GetRangeToDatum(track_info.Lon, track_info.Lat)
        if (range_km > 50):
            goal_alt_m = cruise_alt_m
        else:
            goal_alt_m = 80*range_km + 1000 + alt_m
        SetAlt(UI, goal_alt_m)
        if (UI.GetAltitude() > (goal_alt_m - 300)):
            cruiseSpeed_kts = UI.GetCruiseSpeedForAltitude(goal_alt_m)
            UI.SetSpeed(cruiseSpeed_kts)
        elif (UI.HasThrottle()):
            UI.SetThrottle(1.0)
        else:
            UI.SetSpeed(UI.GetMaxSpeed())
        
    elif (land_state == 2):       
        track_info.Offset(6, landing_data.Heading_rad + 3.1416)
        SetAlt(UI, 300 + alt_m)
        UI.SetPitchLimit(6)
        UI.SetThrottle(0.7)
        SetFractionalSpeed(UI,0.5)
    elif (land_state >= 3):
        SetAlt(UI, 18 + alt_m)
        UI.SetPitchLimit(5)
        SetFractionalSpeed(UI,0.4)
        UI.SetThrottle(0.5)
        if(UI.GetLandingState()==0):
            UI.SetLandingState(1)   # gear down        

    #UI.DisplayMessage('Landing state is %d, alt_m: %f' % (land_state, alt_m)) 
    
    TTI = UI.SetHeadingToInterceptTrack(track_info)

    if (TTI <= 5):
        TI.SetMemoryValue(2, land_state+1)  # move to next landing state
        TI.SetUpdateInterval(3) 
    elif (TTI <= 20):
        TI.SetUpdateInterval(3)
    else:
        TI.SetUpdateInterval(10)

# modified this to adjust altitude based on altitude of landing
# site
def LandHelo(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    if (not GetConnControl(BB)):
        return

    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        TI.SetMemoryText('Description', 'Land at designated airbase')
        TI.SetMemoryValue(2, 0) # 0 - init, 1 - distant, 2 - init approach, 3 - final approach
        dest_name = BB.ReadMessage('LandTarget')
        dest_id = UI.LookupFriendlyId(dest_name)
        if (dest_id == -1):
            # try home base
            home_base = GetHomeBase(UI)
            dest_id = UI.LookupFriendlyId(home_base)
            if (dest_id == -1):
                UI.DisplayMessage('Bad landing target (%s)' % dest_name)
                TI.EndTask()
                return
        TI.SetMemoryValue(3, dest_id)
        CancelTasksForLanding(UI)
    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)
    

    if (not UI.IsHelo()):
        UI.DisplayMessage('LandHelo called with non-helo unit')
        TI.EndTask()
        return
    
    # 0 - init, 1 - distant, 2 - init approach, 3 - final approach
    land_state = TI.GetMemoryValue(2)
    dest_id = long(TI.GetMemoryValue(3))
    track_info = UI.GetTrackById(dest_id)

    alt_m = track_info.Alt
    if (track_info.ID == -1):
        UI.DisplayMessage('Bad track ID for landing')
        TI.EndTask()
        return # invalid id

    landing_data = UI.GetLandingData(dest_id)
    if (landing_data.ID == -1):
        UI.DisplayMessage('Invalid landing platform')
        TI.EndTask()
        return # invalid id

    track_info.Lat = landing_data.Lat
    track_info.Lon = landing_data.Lon
    track_info.Alt = landing_data.Alt


    alt_m = track_info.Alt

    # adjust track location based on approach state
    if (land_state <= 1):
        track_info.Offset(3, landing_data.Heading_rad + 3.1416)  # enter pattern at 3 km final
        range_km = UI.GetRangeToDatum(track_info.Lon, track_info.Lat)
        range_km = min(range_km, 10)
        SetAlt(UI, 50*range_km + 500 + alt_m) 
        #if (land_state == 0):
        #    UI.DisplayMessage('Landing helo on platform %d' % track_info.ID) 

        SetFractionalSpeed(UI, 0.7)
        TI.SetMemoryValue(2, 1)
    elif (land_state == 2):
        range_km = UI.GetRangeToDatum(track_info.Lon, track_info.Lat)
        range_km = min(range_km, 1)
        SetAlt(UI, 100*range_km + 100 + alt_m) 
        UI.SetSpeed(track_info.Speed + 10 + 40*range_km)
    elif (land_state >= 3):  
        #UI.DisplayMessage('Final descent, platform %d' % track_info.ID)      
        SetAlt(UI, 50 + alt_m)
        UI.SetSpeed(track_info.Speed + 2)
        if(UI.GetLandingState()==0):
            UI.SetLandingState(1)   # gear down  

    
    TTI = UI.SetHeadingToInterceptTrack(track_info)

    if (TTI <= 10):
        if (land_state == 1):
            land_state = 2
        elif (land_state == 2):
            land_state = 3
        TI.SetMemoryValue(2, land_state)
        TI.SetUpdateInterval(1) 
    elif (TTI <= 20):
        TI.SetUpdateInterval(3)
    else:
        TI.SetUpdateInterval(10)

def CheckBingo(UI, BB):
    if (not UI.IsAir()):
        return 0
    dest_name = BB.ReadMessage('LandTarget')
    dest_id = UI.LookupFriendlyId(dest_name)
    if (dest_id == -1):
        # try home base
        home_base = GetHomeBase(UI)
        dest_id = UI.LookupFriendlyId(home_base)
        if (dest_id == -1):
            return 0 # no landing base, kamikaze
    base_track = UI.GetTrackById(dest_id)
    base_range_km = UI.GetRangeToDatum(base_track.Lon, base_track.Lat)

    cruise_alt_m = UI.GetCruiseAltitude()
    cruise_range_km = UI.GetCruiseRangeForAltitude(cruise_alt_m)
    # calculate reserve range based on 25 minutes of time at cruise speed
    reserve_range_km = UI.GetCruiseSpeedForAltitude(cruise_alt_m) - 75  #set a 75km reserve.
    if ((cruise_range_km - reserve_range_km) < base_range_km):
        return 1 # bingo fuel
    else:
        return 0

def GetCruiseAltitude(UI):
    if UI.HasThrottle():
        if UI.GetPlatformClass() == 'SR-71':
            cruise_alt_m = 27500
        else:
            cruise_alt_m = UI.GetCruiseAltitude()
    elif (UI.IsHelo()):
        cruise_alt_m = 2000.0
    else:
        cruise_alt_m = 10000.0
    return cruise_alt_m
    
def ReturnToBase(TI):
	UI = TI.GetPlatformInterface()
	UI.AddTask('RTB', 2.0, 0)
	TI.EndTask()

# For aircraft, return to home base when at bingo fuel or after specified time
def RTB(TI):
    #given how much functionality has been replaced by other little functions for repurposing and modularising for the pilot script
    #im just going to rewrite RTB entirely.  i pretty much have already, I just need to use the stuff I wrote in here too.
    UI = TI.GetPlatformInterface()
    TI.SetUpdateInterval(5)
    if not UI.IsAir():
        TI.EndTask()
        return

    if UI.TaskExists('Land') or UI.TaskExists('LandHelo'):
        return
    else:
        bingo, range_km = BingoFuel(UI)
        if bingo == 1:
            GoRefuel(UI, range_km)
        elif bingo == 2:
            GoHome(UI)
        
# return name of home airfield or '' if none
def GetHomeBase(UI):
    BB = UI.GetBlackboardInterface()
    return BB.ReadMessage('Home')
    
def LandAtNamed(UI, base_name):
    BB = UI.GetBlackboardInterface()
    BB.Write('LandTarget', base_name)

    if (UI.IsHelo()):
        UI.AddTask('LandHelo', 3.0, 0)
    else:
        UI.AddTask('Land', 3.0, 0)

def CancelLanding(UI):
    if (UI.TaskExists('Land')):
        UI.SetLandingState(0)
        UI.DeleteTask('Land')

class RangeName:
    range_km = 0
    name = ''

# compare function for two track_info objects for sorting
def RangeNameCompare (x, y):
    return cmp(x.range_km, y.range_km)

def SetAlternateHomeBase(UI):
    BB = UI.GetBlackboardInterface()
    base_list = GetNearbyAirfields(UI)
    
    
    if (len(base_list) == 0):
        UI.DisplayMessage('%s needs home base' % UI.GetPlatformName())
    else:
        BB = UI.GetBlackboardInterface()
        BB.Write('Home', base_list[0].name)
        UI.DisplayMessage('%s switching home base to %s (%.0f km)' % (UI.GetPlatformName(), base_list[0].name, base_list[0].range_km))

def GetNearbyAirfields(UI):
    range_km = 500.0
    track_list = UI.GetFriendlyTrackList(0, range_km, 'airbases')

    # first load list of range name pairs
    rangename_list = [];
    nTracks = track_list.Size()
    for n in range(0, nTracks):
        track_info = track_list.GetTrack(n)
        info_n = RangeName()
        info_n.name = UI.LookupFriendlyName(track_info.ID)
        info_n.range_km = UI.GetRangeToTrack(track_info)
        rangename_list.append(info_n)

    # sort list by range
    rangename_list.sort(RangeNameCompare)

    return rangename_list    
        
def GetNearbyTankers(UI):
    range_km = 10000.0
    track_list = UI.GetFriendlyTrackList(0, range_km, 'tankers')

    # first load list of range name pairs
    rangename_list = [];
    nTracks = track_list.Size()
    for n in range(0, nTracks):
        track_info = track_list.GetTrack(n)
        info_n = RangeName()
        info_n.name = UI.LookupFriendlyName(track_info.ID)
        info_n.range_km = UI.GetRangeToTrack(track_info)
        rangename_list.append(info_n)

    # sort list by range
    rangename_list.sort(RangeNameCompare)

    return rangename_list
    
def AddRefuelOrder(UI, dest_id):
    if (not UI.IsAir() or UI.IsHelo()):
        return
    
    UI.ClearTasks()
    UI.AddTask('Refuel', 2.0, 0)
        
    dest_name = UI.LookupFriendlyName(dest_id)
    BB = UI.GetBlackboardInterface()
    BB.Write('RefuelTarget', dest_name)    
    
def RefuelFromNamed(UI, tanker_name):
    BB = UI.GetBlackboardInterface()
    BB.Write('RefuelTarget', tanker_name)

    UI.AddTask('Refuel', 2.0, 0)

def CancelRefuel(UI):
    if (UI.TaskExists('Refuel')):
        UI.DeleteTask('Refuel')

def Refuel(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    
    iteration = TI.GetMemoryValue(1) # will return 0 first time
    if (iteration == 0):  # do initialization
        cruise_km = UI.GetCruiseRangeForAltitude(GetCruiseAltitude(UI))
        cruiseSpeed_kts = UI.GetCruiseSpeedForAltitude(GetCruiseAltitude(UI))   
        TI.SetMemoryValue(2,GetCruiseAltitude(UI))
        TI.SetMemoryValue(3,cruiseSpeed_kts)
        TI.SetMemoryValue(137,iteration) #used to check if we are several iterations past the last check
        TI.SetMemoryText('Description', 'Refuel from tanker')
        dest_name = BB.ReadMessage('RefuelTarget')
        dest_id = UI.LookupFriendlyId(dest_name)
        if (dest_id == -1):
            UI.DisplayMessage('Bad refuel target (%s)' % dest_name)
            TI.EndTask()
            return
        if (not UI.IsTankerAircraft(dest_id)):
            UI.DisplayMessage('Not a tanker (%s)' % dest_name)
            TI.EndTask()
            return
        if (not UI.CanRefuelInFlight()):
            UI.DisplayMessage('Not refuel capable')
            TI.EndTask()
            return
        GetConnControl(BB)
        TI.SetMemoryValue(4, dest_id)
    
    iteration = iteration + 1
    TI.SetMemoryValue(1, iteration)
    
    dest_id = long(TI.GetMemoryValue(4))
    track_info = UI.GetTrackById(dest_id)
    range_km = UI.GetRangeToTrack(track_info)
    # IsTankerAircraft also returns false if tanker is out of fuel

    if (not UI.IsTankerAircraft(dest_id)):
        UI.DisplayMessage('Tanker dry (%s)' % dest_id)
        if (UI.GetFormationLeader() == dest_id):
            UI.SetFormationLeader(-1)
        TI.EndTask()
        return

        #check if stil need fuel, end task if not
    if (UI.GetFuel() > 0.98):#before we bother with the closure and position keeping, see if we are already full, if we are, just end the task now
        UI.SetAltitude(TI.GetMemoryValue(2))#return to cruise altitude until further notice
        UI.SetFormationLeader(-1)
        UI.SetHeadingRad(UI.GetHeadingRad() + 0.05)
        ReleaseConnControl(BB)
        TI.EndTask()  # done
    else:
                      #range_km   Heading_Type    Speed+      Cruise
                                 #Alt-      Update      Formation
        range_rates = [
                       [  0.00,   15,    1,  0.3,    0  ,   1,   0],
                       [  0.14,   15,    1,  0.5,    23 ,   0,   0],
                       [  0.20,   15,    1,  0.5,    35 ,   0,   0],
                       [  0.50,   15,    1,  1.0,    70 ,   0,   0],
                       [  2.00,   15,    1,  1.0,    70 ,   0,   0],
                       [  3.50,   15,    1,  2.0,    105,   0,   0],
                       [  5.00,   15,    0,  2.0,    105,   0,   0],
                       [ 10.00,   15,    0,  2.0,    105,   0,   0],
                       [ 15.00,  0.0,    0,  2.0,    160,   0,   0],
                       [ 20.00,  0.0,    0,  3.0,    160,   0,   0],
                       [ 50.00,  0.0,    0,  3.0,    160,   0,   1],
                       [100000,  0.0,    0,  6.0,    160,   0,   1]
                       ]
        range_indexes = []
        for i in range(0,len(range_rates)):     #for length of rangerates, which is currently 9
            range_indexes.append(range_rates[i][0])  #should be appending the first entry of each sublist, the range values
        range_indexes.sort()
        range_index = -1
        iter = -0
        if (range_km < range_indexes[1]):
            range_index = range_indexes[0]
        else:
            while (range_index <= range_km):#loop should end before iter can get too high so it calls the right index
                iter += 1     #should be zero on first loop
                range_index = range_indexes[iter]

        modifier = tanking_approach_modifier(UI)
        
        if (range_km <5):
            TI.SetMemoryValue(138,1) #prevents oddness like climbing to cruise altitude because we got a few meters too far away
        TI.SetUpdateInterval(range_rates[iter][3])
            
        alt_offset = range_rates[iter][1]
        heading_type = range_rates[iter][2]
        spd_offset = range_rates[iter][4]
        formation = range_rates[iter][5]
        cruise = range_rates[iter][6]
        

        #set heading
        if (TI.GetMemoryValue(132) == 1):
            track_info.Offset(0.05,track_info.Heading_rad)
            #offset the tanker for bearing purposes, creates lead point 100m ahead, reduces oscillation when in close.
        bearing_deg = UI.GetHeadingToDatum(track_info.Lon, track_info.Lat)    #bearing to the tanker.
        
        if (bearing_deg < 0):
            bearing_match = bearing_deg + 360   #GCB uses negative values for bearings 180.0001 through 359.9999, this makes negative bearings into their positive counterparts.
        else:
            bearing_match = bearing_deg

        if ((heading_type == 0) or (UI.GetMaxSpeed() - track_info.Speed <70)):
        #if heading mode 0, then Intercept
        #if heading mode 1, then enter lag pursuit
        #also, if tanker is too fast, just do lag pursuit
            UI.SetHeadingToInterceptTrack(track_info)
        else:
            UI.SetHeading(bearing_deg)

            #set speed
            #now includes a modifier, defaults to 1 if aircraft classname is not setup
        if (spd_offset == 0):
            goal = (((range_km - 0.0601) / 0.0375 * 10) * modifier) + track_info.Speed  #should match speed at 40m behind the tanker
        elif (cruise == 0):
            goal = track_info.Speed + (spd_offset * modifier)
        else:
            goal = TI.GetMemoryValue(3)
            #need to convert this next check to use closure rate, and not actual speed.
            if(goal < track_info.Speed + ((0.5*spd_offset) * modifier)):  #if the tanker's really moving, then apply the offset anyways.
                goal = track_info.Speed + ((spd_offset*0.5) * modifier)
        UI.SetSpeed(goal)
        
        heading = UI.GetHeading()
        if heading <0:
            heading += 360

        if ((TI.GetMemoryValue(131) == 1) and (abs(heading - bearing_match) > 45)):
            UI.SetSpeed(track_info.Speed * 0.8)
        
        if (UI.GetSpeed() > goal + 3):
            if UI.HasThrottle():
                UI.SetThrottle(0)
            else:
                UI.SetSpeed(track_info.Speed * 0.8)
            
            
            #set altitude
        if ((alt_offset == 0) and (TI.GetMemoryValue(138) != 1)):
            UI.SetAltitude(TI.GetMemoryValue(2))  #cruise alt
        else:
            UI.SetAltitude(track_info.Alt - alt_offset)

        
            #create formation
        if ((abs(heading - bearing_match) < 5) and (abs(UI.GetSpeed() - track_info.Speed) < 5) and (formation == 1)):
            #if we aren't approximately the same speed and heading, don't enter formation, and don't receive fuel
            UI.StartRefuelWith(dest_id)
            UI.SetFormationLeader(dest_id)
            UI.SetFormationPosition(0.08, 0.05, 3.14, 0.05)
            UI.SetFormationAltitudeOffset(-15.0)
            UI.SetFormationMode(1) # 1 is follow, 2 is sprint-drift

            #break formation
        if (UI.GetFormationLeader() != -1):
            #only bother with this is we are in formation.
            heading = UI.GetHeading()
            if heading < 0:
                heading += 360
            if ((track_info.Alt - UI.GetAlt() >20) or (abs(heading - bearing_match) > 5) or (UI.GetSpeed() > goal + 5)):
                #if we are too low, out of position, or too fast, break formation and get back into possition
                UI.SetFormationLeader(-1)
                UI.SetHeadingToInterceptTrack(track_info)
            UI.SetActionText('%1.4f Refueling' % UI.GetFuel())
        else:
            slant_range = math.sqrt(math.pow(range_km*1000,2) + math.pow(UI.GetAltitude() - track_info.Alt,2))/1000
            #set the action text
            if slant_range > 10:
                UI.SetActionText('%1.2f Refuel %0.0fkm' %(UI.GetFuel(),slant_range))
            elif slant_range > 2:
                UI.SetActionText('%1.2f Refuel %0.1fkm' %(UI.GetFuel(),slant_range))
            elif slant_range < 2:
                if (abs(UI.GetHeadingRad() - track_info.Heading_rad) < 0.2618):
                    TI.SetMemoryValue(131,1)
                    TI.SetMemoryValue(132,1)
                UI.SetActionText('%1.2f Refuel %dm' %(UI.GetFuel(),int(slant_range*1000)))

def tanking_approach_modifier(UI):
    aircraft = {'F-117':0.67,
                'default':1}
                #you can easily add more aircraft to this, it does not have to be in any order either.
          #     'name':value
    modifier = aircraft.get(UI.GetClass())
    try:
        test = modifier + 1
    except:
        #if the test fails, then we didn't get a number back
        #so its not in the list, feed 1 as default.
        modifier = 1
    return modifier
    
def BingoFuel(UI):
    BB = UI.GetBlackboardInterface()
    
    if UI.GetFuel() == 0:
        return -1, 0
        
    home_base = BB.ReadMessage('Home')
    home_id = UI.LookupFriendlyId(home_base)
    if (home_id == -1):
        if not BB.KeyExists('HomeBaseSpam'):
            SetAlternateHomeBase(UI)
            home_base = BB.ReadMessage('Home')
            home_id = UI.LookupFriendlyId(home_base)
            BB.WriteGlobal('HomeBaseSpam', '1')
    reserve = UI.GetCruiseRangeForAltitude(GetCruiseAltitude(UI)) * 0.04 / UI.GetFuel()
        
    home_track = UI.GetTrackById(home_id)
    
    bingo = 0
    cruiseRange_km = UI.GetCruiseRangeForAltitude(GetCruiseAltitude(UI)) - 85 - reserve# 85km reserve range, further 4% reserve
    if home_track.IsValid():
        #yes, I know its separate from the previous block, and could easily be an else:
        #I want this to run in the same pass in case we get a valid home_track from that previous block.
        homeRange_km = UI.GetRangeToTrack(home_track)
        if ((homeRange_km >= cruiseRange_km - reserve - 75) 
            and (UI.CanRefuelInFlight()) and (not UI.TaskExists('Refuel')) 
            and (not UI.TaskExists('Land')) and (not UI.IsTankerAircraft(UI.LookupFriendlyId(UI.GetName())))
            ):
            #go find a tanker if you can
            bingo = 1
        if ((homeRange_km >= cruiseRange_km - reserve) and (not UI.TaskExists('Refuel'))):
            #go home
            bingo = 2
    if UI.GetFuel() < 0.05:
        AddTask(UI, 'GlideSlope', 1, -1)
    return bingo, cruiseRange_km
        
def GoRefuel(UI, cruiseRange_km):
    if not UI.TaskExists('Refuel'):
        dest_name = GetNearbyTankers(UI)
        if (len(dest_name) != 0):
            tanker_name = dest_name[0].name
            tanker_range = dest_name[0].range_km
            dest_id = UI.LookupFriendlyId(tanker_name)
            if (tanker_range < cruiseRange_km):
                UI.DisplayPopupMessage('Tanking')
                AddRefuelOrder(UI, dest_id)

def GoHome(UI):
    if not UI.TaskExists('Land'):
        UI.DisplayPopupMessage('RTB')
        BB = UI.GetBlackboardInterface()
        home_base = BB.ReadMessage('Home')
        dest_id = UI.LookupFriendlyId(home_base)
        if dest_id != -1:
            BB_global = UI.GetBlackboardInterface() # so msg isn't erased on endtask
            BB_global.Write('LandTarget', home_base)
            AddTask(UI, 'Land')
            CancelTasksForLanding(UI)    
