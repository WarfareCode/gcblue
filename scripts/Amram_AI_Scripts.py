import random, time, csv, os, math, Landing, sys
from os.path import dirname, abspath, join, normpath
sys.path.append(abspath(join(dirname(__file__), 'Amram_Script_Data')))
from Amram_AI_Weapon_Lists import *
from Amram_Utilities import *
from Menu import *
from decimal import Decimal
from UnitCommands import *
import json
    

def bombing_lead(UI, track, offset = False):
    if offset:
        maxbombs = DropBombs_Amram(UI, 0, 0, 0, 0)
        offset = maxbombs / 2 * 0.1 - 0.05
        return offset
    else:
        leadTime = LoftedRange(UI, track.Lon, track.Lat, 2)
        track_lead = track.PredictAhead(leadTime)
        return track_lead
    
def basic_track_lead(UI, track):
    track_m = round(UI.GetRangeToTrack(track) * 1000,9)
    leadTime = track_m / (UI.GetSpeed() * 0.514444)
    track_lead = track.PredictAhead(leadTime)
    return track_lead
    
def Lawndart_detection(TI):
    #always active on aircraft, helps ensure they do not crash when diving under SetPitch
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    
    if not BB.KeyExists('uncontrolled_dive') or UI.GetFuel() == 0 or UI.TaskExists('Land') or UI.TaskExists('LandHelo') or UI.GetClimbDeg() > 0:
        #nothing to do, we either are not descending, want to descend until touchdown, or cannot prevent a crashlanding.
        return
    
    speed = UI.GetSpeed() * 0.514444
    vertical_rate = speed * sin(radians(UI.GetClimbDeg()))
    if vertical_rate == 0:
        vertical_rate = 0.0000000000001   #just to prevent a div/zero error when the aircraft is currently flying level with a null vert rate.
    alt = UI.GetAlt()
    
    
    Lawndart = BB.KeyExists('Lawndart')
    protective_rate = (alt / (speed/2))  * 0.75
    TI.SetUpdateInterval(protective_rate)
    
    
    if Lawndart:
        TI.SetUpdateInterval(0.2)
    elif UI.GetClimbDeg() < 0:
        #then we are diving, this just got much more critical, advance to a much higher update interval
        critical_rate = max(0.2, (alt / vertical_rate) / 2)
        TI.SetUpdateInterval(critical_rate)

        
    if UI.GetAlt() < 2000 and UI.GetClimbDeg() < 0 and not Lawndart:
        terrain = UI.GetMapTerrainElevation(UI.GetLongitude(), UI.GetLatitude())
        min_alt = max(terrain,0)
        if abs((alt - min_alt) / vertical_rate) < 3 and vertical_rate < 0:   #needs to be negative....
            BB.Write('Lawndart', '1')
        
        
    if Lawndart:
        if UI.GetClimbDeg() < 9.9:
            SetPitch(UI, 10)
        else:
            SetAlt(UI, UI.GetAlt() + 500)
            BB.Erase('Lawndart')
            
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
    if alt > UI.GetAlt() + 5 or alt < UI.GetAlt() - 5:
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
        SetAlt(UI, alt)
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
                SetAlt(UI, alt)
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
    
    

        #current_climb_rate = (UI.GetSpeed() * 0.514444) * math.sin(math.radians(abs(pitch)))
        #UI.DisplayMessage('alt %0.1f, Rate %0.1f, Pitch %0.1f' % (alt, current_climb_rate, pitch))
        #UI.DisplayMessage('Alt %0.1f, cruise %0.2f, current %0.2f' % (UI.GetAlt(), cruise_spd, UI.GetSpeed()))
        #UI.DisplayMessage('GLos %0.2f, amod %0.2f, acel %0.2f' % (gravity_losses, accel_mod, acceleration))
        
        
        SetPitch(UI, new_pitch, rate=rate_mod, uncontrolled=False)
        write_speed = str(UI.GetSpeed())
        BB.Write('Last_Speed',write_speed)

def Flight_State(TI, reset = False):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    #uses BB messages to secure an ongoing reset, or optional argument to temporarily reset flight state.
    
    newspeed = False
    newthrottle = False
    newalt = False
    restored = False
    speed = -1
    throttle = -1
    alt = -1
    if BB.KeyExists('Flight_State'):
        if BB.ReadMessage('Flight_State') == 'reset' or reset:
            if BB.KeyExists('originalThrottle') or BB.KeyExists('originalAlt') or BB.KeyExists('originalSpeed'):
                if UI.HasThrottle():
                    if abs(UI.GetThrottle() - float(BB.ReadMessage('originalThrottle'))) < 0.01 and abs(UI.GetAlt() - float(BB.ReadMessage('originalAlt'))) < 1 and UI.GetClimbDeg() == 0:
                        #We reset our throttle, our altitude, and are done climbing/descending, we're finished.
                        if BB.KeyExists('originalThrottle'):
                            BB.Erase('originalThrottle')
                        BB.Erase('originalAlt')
                        BB.Erase('Flight_State')
                        restored = True
                    else:
                        #we haven't finished resetting, so do that.
                        if BB.KeyExists('originalThrottle'):
                            throttle = float(BB.ReadMessage('originalThrottle'))
                            newthrottle = True
                        if BB.KeyExists('originalAlt'):
                            alt = float(BB.ReadMessage('originalAlt'))
                            newalt = True
                else:
                    if abs(UI.GetSpeed() - float(BB.ReadMessage('originalSpeed'))) < 0.1 and abs(UI.GetAlt() - float(BB.ReadMessage('originalAlt'))) < 1 and UI.GetClimbDeg() == 0:
                        #We reset our throttle, our altitude, and are done climbing/descending, we're finished.
                        if BB.KeyExists('originalSpeed'):
                            BB.Erase('originalSpeed')
                        BB.Erase('originalAlt')
                        BB.Erase('Flight_State')
                        restored = True
                    else:
                        #we haven't finished resetting, so do that.
                        if BB.KeyExists('originalSpeed'):
                            newspeed = True
                            speed = float(BB.ReadMessage('originalSpeed'))
                        if BB.KeyExists('originalAlt'):
                            alt = float(BB.ReadMessage('originalAlt'))
                            newalt = True
            else:
                #we don't have the original throttle or altitude, so screw it, just end now.

                restored = True
    else:
        BB.WriteGlobal('Flight_State', 'saved')
        if not BB.KeyExists('originalAlt'):
            BB.WriteGlobal('originalAlt', '%s' % str(UI.GetAlt()))
        if UI.HasThrottle():
            if not BB.KeyExists('originalThrottle'):
                BB.WriteGlobal('originalThrottle', '%s' % str(UI.GetThrottle()))
        else:
            if not BB.KeyExists('originalSpeed'):
                BB.WriteGlobal('originalSpeed', '%s' % str(UI.GetSpeed()))
    return newspeed, newthrottle, newalt, speed, throttle, alt, restored
        
def BombRun(TI):
    #may be called by another script and will report what it wants
    #alternatively, may be launched as its own task and will control the aircraft accordingly
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()

    update = 10
    nodatum = True
    target = False
    if BB.KeyExists('BombDatum'):
        datum = Read_Message_List(BB, 'BombDatum')
        nodatum = False
    else:
        track = UI.GetTargetTrackInfo()
        id = track.ID
        if id == -1:
            #no target end the run
            TI.EndTask()
            return
        else:
            target = True
            
    
    init = TI.GetMemoryValue(1)
    if init != 1:
        #not initialised yet, do so
        TI.SetMemoryValue(1,1)
        if BB.KeyExists('Bombing_Complete'):
            BB.Erase('Bombing_Complete')
        maxbombs = DropBombs_Amram(UI, 0, 0, 0, 0)
        offset = maxbombs / 2 * 0.1 - 0.05
        TI.SetMemoryValue(2, offset)
    
    offset = TI.GetMemoryValue(2)
    newheading = False
    newpitch = False
    newalt = False
    newthrottle = False
    newspeed = False
    newupdate = False
    SetAngle = False
    heading = -1000
    pitch = -1000
    alt = -1000
    throttle = -1000
    speed = -1000

    if Lawndart_detection(TI) or UI.TaskExists('Lawndart_Correction'):
        return newheading, newpitch, newalt, newthrottle, newspeed, update, heading, pitch, alt, throttle, speed

        
    current_speed = UI.GetSpeed() * 0.514444
    max_speed = UI.GetMaxSpeed() * 0.514444
    offset_m = current_speed * offset

    
    #perform restoration of previous flight condition
    if BB.KeyExists('Bombing_Complete'):
        BB.WriteGlobal('Flight_State', 'reset')
        newspeed, newthrottle, newalt, speed, throttle, alt, restored = Flight_State(TI)
        if restored:
            BB.Erase('Bombing_Complete')
            TI.EndTask()
        if UI.TaskExists('AI_Pilot'):
            return newheading, newpitch, newalt, newthrottle, newspeed, update, heading, pitch, alt, throttle, speed
        else:
            #contains a copy of the final block here as well
            #since this section self terminates each run of the script at this point
            #so it needs control from here as well.
            TI.SetUpdateInterval(update)
            if newheading:
                UI.SetHeading(heading)
            if newpitch:
                SetPitch(UI, pitch)
            if newthrottle:
                UI.SetThrottle(throttle)
            elif newspeed:
                UI.SetSpeed(speed)
            if newalt:
                SetAlt(UI, alt)
            return
        
    if target:
        datum = [track.Lon, track.Lat]
        
    datum_alt = UI.GetMapTerrainElevation(datum[0], datum[1])
    if datum_alt < 0:
        datum_alt = 0

    dive_m, level_m, loft_m, loft_max_m = LoftedRange(UI, datum[0], datum[1], 0)
    
    #define the track range
    range_m = round(UI.GetRangeToDatum(datum[0], datum[1]) * 1000,9)
    #determine style of strike if necessary
    if BB.KeyExists('Style'):
        style = BB.ReadMessage('Style')
    else:
        if isBomber(UI, UI.GetPlatformClass()):
            style = 'level'
        else:
            if target:
                if track.IsGround():
                    if track.Classification == 257: #airfield
                        if UI.GetAlt() > 500 and UI.GetClimbDeg == 0:
                            style = 'level'
                        else:
                            style = 'loft'
                    elif track.Classification == 258: #ground vehicle, maybe mobile sam
                        style = 'loft'
                    else : #building, or sam site, or...etc
                        style = 'loft'
                elif track.IsSurface() and (UI.GetAlt() - datum_alt) > 1000:
                    style = 'dive'
                else:
                    style = 'loft'
            else:
                if (UI.GetAlt() > 500 and UI.GetClimbDeg == 0) or UI.GetAlt() > 8000:
                    style = 'level'
                elif UI.GetAlt() - datum_alt > 1000:
                    style = 'dive'
                else:
                    style = 'loft'
        if style == 'loft' and UI.GetAlt() - datum_alt > 4000:
            style = 'dive'
        BB.WriteGlobal('Style', style)
    #define the style of the strike, and validate the strike
    if range_m < loft_max_m + offset + (max_speed * 20):
        if target:
            track_lead = bombing_lead(UI, track)
            range_m = round(UI.GetRangeToDatum(track_lead.Lon, track_lead.Lat) * 1000,9)
            heading = UI.GetHeadingToDatum(track_lead.Lon, track_lead.Lat)
        else:
            range_m = round(UI.GetRangeToDatum(datum[0], datum[1]) * 1000,9)
            heading = UI.GetHeadingToDatum(datum[0], datum[1])
        newheading = True
        #we can reach the target, so attack it.
        #begin the actual pitch adjustment/bombing run.
        #must modularise this piece.
        
        Continue_Engagement = True
        while Continue_Engagement:
            #using while to allow mid block breakouts as warranted.
            pre_loft = range_m - loft_max_m
            pre_level = (range_m - level_m) - offset_m
            dive_range = max(abs(UI.GetAlt() - datum_alt) / 2.5, 800)
            pre_dive = range_m - dive_range
            if style == 'dive' and range_m < level_m:
                if range_m < dive_range:
                    SetAngle = True
                elif pre_dive < current_speed * 3:
                    update = min(3,max(0.1,(pre_dive / current_speed) / 2))
                else:
                    update = 3
            if style == 'level' and current_speed * 15 > pre_level:
                update = min(1,max(0.1,((pre_level / current_speed) / 2) - 0.1))
            if style == 'level' and range_m < loft_max_m:
                if range_m - offset_m < level_m:
                    if target:
                        complete = DropBombs_Amram(UI, track_lead.Lon, track_lead.Lat, track_lead.Alt, 'all')
                    else:
                        complete = DropBombs_Amram(UI, datum[0], datum[1], datum_alt, 'all')
                    if complete:
                        heading = UI.GetHeading() + 180
                        newheading = True
                        BB.WriteGlobal('Bombing_Complete','True')
                        Continue_Engagement = False
            if style == 'loft' and range_m + (current_speed * 5) > loft_max_m:
                update = pre_loft / current_speed
            if style == 'loft' and range_m < loft_max_m:
                update = 0.1
                SetAngle = True
            if UI.GetHeading() < 0:
                ownheading = UI.GetHeading() + 360
            else:
                ownheading = UI.GetHeading()
            if target:
                if UI.GetHeadingToDatum(track_lead.Lon, track_lead.Lat) < 0:
                    ownbearing = UI.GetHeadingToDatum(track_lead.Lon, track_lead.Lat) + 360
                else:
                    ownbearing = UI.GetHeadingToDatum(track_lead.Lon, track_lead.Lat)
            else:
                if UI.GetHeadingToDatum(datum[0], datum[1]) < 0:
                    ownbearing = UI.GetHeadingToDatum(datum[0], datum[1]) + 360
                else:
                    ownbearing = UI.GetHeadingToDatum(datum[0], datum[1])
                
            if SetAngle and abs(ownheading - ownbearing) < 5:
                if target:
                    pitch = LoftedRange(UI, track_lead.Lon, track_lead.Lat, 1)
                else:
                    pitch = LoftedRange(UI, datum[0], datum[1], 1)
                if type(pitch) == type([]):
                    if style == 'dive':
                        pitch = min(pitch[0], pitch[1])
                    elif style == 'loft':
                        UI.SetPitchLimit(89.99)
                        pitch = max(pitch[0], pitch[1])
                    newpitch = True
                    update = 0.1

                    lastpitch = TI.GetMemoryValue(318)
                    TI.SetMemoryValue(318, pitch)
                    lastclimb = TI.GetMemoryValue(319)
                    TI.SetMemoryValue(319, UI.GetClimbDeg())
                    
                    if pitch > lastpitch and UI.GetClimbDeg() == lastclimb and lastclimb > 0 and lastpitch > 0:
                        #we just got stuck with an inability to pitch high enough
                        style = 'dive'
                        BB.WriteGlobal('Style', style)
                        if UI.GetAlt() < 4000:
                            newalt = True
                            alt = 4000
                    if abs(range_m - loft_m) < 30 and abs(ownheading - ownbearing) < 0.15:
                        if target:
                            complete = DropBombs_Amram(UI, track_lead.Lon, track_lead.Lat, track_lead.Alt, 'all')
                        else:
                            complete = DropBombs_Amram(UI, datum[0], datum[1], datum_alt, 'all')
                        if complete:
                            BB.WriteGlobal('Bombing_Complete','True')
                            BB.WriteGlobal('Flight_State', 'reset')
                            heading = UI.GetHeading() + 180
                            newheading = True
                            Continue_Engagement = False
            Continue_Engagement = False
    else:
        if target:
            track_lead = basic_track_lead(UI, track)
            range_m = round(UI.GetRangeToDatum(track_lead.Lon, track_lead.Lat) * 1000,9)
            heading = UI.GetHeadingToDatum(track_lead.Lon, track_lead.Lat)
        else:
            range_m = round(UI.GetRangeToDatum(datum[0], datum[1]) * 1000,9)
            heading = UI.GetHeadingToDatum(datum[0], datum[1])
        newheading = True

    if style == 'loft' and range_m - loft_max_m < 10000 and UI.HasThrottle() and UI.GetClimbDeg() == 0:
        if UI.HasThrottle():
            if UI.GetThrottle() < 0.85:
                throttle = 0.85
                newthrottle = True
        else:
            if UI.GetSpeed() / UI.GetMaxSpeed() < 0.85:
                speed = UI.GetMaxSpeed() * 0.85
                newspeed = True
        
    elif style == 'dive' and UI.GetClimbDeg() < 0:
        throttle = 0
        newthrottle = True
    
    if newpitch or newalt or newspeed or newthrottle:
        Flight_State(TI)
        
    if style == 'dive':
        time_s = (range_m - dive_m) / (UI.GetSpeed() * 0.514444)
    elif style == 'loft':
        time_s = (range_m - loft_max_m) / (UI.GetSpeed() * 0.514444)
    else:
        time_s = (range_m - offset_m - level_m) / (UI.GetSpeed() * 0.514444)
    UI.SetActionText('%sbomb target %ds' % (style, time_s))
        
    if UI.TaskExists('AI_Pilot'):
        return newheading, newpitch, newalt, newthrottle, newspeed, update, heading, pitch, alt, throttle, speed
    else:
        TI.SetUpdateInterval(update)
        if newheading:
            UI.SetHeading(heading)
        if newpitch:
            SetPitch(UI, pitch)
        if newthrottle:
            UI.SetThrottle(throttle)
        elif newspeed:
            UI.SetSpeed(speed)
        if newalt:
            SetAlt(UI, alt)
            
def Intercept(TI):
    UI = TI.GetPlatformInterface()
    BB = TI.GetBlackboardInterface()
    #control the aircraft to achieve a firing position for any sort of weapon
    #at long range simply close in efficiently, but quickly.  Cruise alt, but 0.8 to 1.00 throttle, maybe more
    #at short ranges, stay within a set angular separation, ascend/descend as necessary
    #at very short ranges, calculate and line up for a gunshot
    #
    #do NOT use slow/tame approach schemes, come in HOT.
    #

    newheading = False 
    newthrottle = False
    newspeed = False
    newalt = False
    newpitch = False
    update = 1
    heading = -1000
    speed = -1000
    throttle = -1000
    alt = -1000
    
    track = UI.GetTargetTrackInfo()
    id = track.ID
    if track.ID == -1:
        #track is dead, or we deselected the target, end task
        TI.EndTask()
        Flight_State(TI, reset = True)
        return newheading, newthrottle, newspeed, newalt, update, heading, speed, throttle, alt

    track.Range = UI.GetRangeToTrack(track)
                #returns the largest item that is smaller than the given range
                #alt, 0 is maintain, 1 is within +30/-45 deg angular, 2 is match
                #heading type 0 is lag, 1 is intercept, 2 is mach2 offset lead, 3 is calculated gun lead
                   #range_km    Heading_Type
                             #Alt-      Update
    range_rates = [
                   [  0.00,    2,    2,  0.15],
                   [  1.50,    2,    2,  0.2],
                   [  2.00,    2,    2,  0.3],
                   [  2.50,    2,    2,  0.6],
                   [  5.00,    1,    2,  1.0],
                   [  8.00,    1,    2,  2.0],
                   [ 15.00,    1,    2,  3.5],
                   [ 23.00,    1,    1,  5.0],
                   [ 60.00,    1,    1,  5.0],
                   [120.00,    0,    0,  5.0],
                   [100000,    0,    0,  5.0]
                   ]
    range_indexes = []
    for i in range(0,len(range_rates)):     #for length of rangerates, which is currently 9
        range_indexes.append(range_rates[i][0])  #should be appending the first entry of each sublist, the range values
    range_indexes.sort()
    range_index = -1
    iter = -0
    if (track.Range < range_indexes[1]):
        range_index = range_indexes[0]
    else:
        while (range_index <= track.Range):#loop should end before iter can get too high so it calls the right index
            iter += 1     #should be zero on first loop
            range_index = range_indexes[iter]


    update = range_rates[iter][3]

    bearing_deg = UI.GetHeadingToDatum(track.Lon, track.Lat)    #bearing to the tanker.
    if (bearing_deg < 0):
        bearing_match = bearing_deg + 360   #GCB uses negative values for bearings 180.0001 through 359.9999, this makes negative bearings into their positive counterparts.
    else:
        bearing_match = bearing_deg
    ownheading = UI.GetHeading()
    if ownheading <0:
        ownheading += 360
        
    if UI.IsAir() and track.IsAir:
        alt_ = range_rates[iter][1]
        if alt_ == 0:
            #cruise
            alt = Landing.GetCruiseAltitude(UI)
            newalt = True
        elif alt_ == 1:
            min_alt = track.Alt - (tan(0.523598) * (track.Range * 1000))
            if UI.GetAlt() < min_alt:
                alt = min_alt+200
                newalt = True
        elif alt_ == 2:
            alt = track.Alt
            newalt = True
    elif UI.IsAir() and not track.IsAir:
        if track.IsGound:
            max_range = max(Try_Read_Message(BB, 'land_max_range', 0), Try_Read_Message(BB, 'land_max_range_guns', 0))
        elif track.IsSurface:
            max_range = max(Try_Read_Message(BB, 'sea_max_range', 0), Try_Read_Message(BB, 'sea_max_range_guns', 0))
        if (UI.GetAlt() - track.Alt) > (max_range * 600):
            alt = track.Alt + (max_range * 500)
            newalt = True
        

    heading_mode = range_rates[iter][2]
    if heading_mode == 0:
        heading = bearing_deg
        newheading = True
    elif heading_mode == 1:
        heading = degrees(UI.GetInterceptHeadingToTrack(track))
        newheading = True
    elif heading_mode == 2:
        offset_s = min(track.Range, 1)
        offset_km = (track.Speed * offset_s)/1000
        track.Offset(offset_km, track.Heading_rad)
        heading = UI.GetHeadingToDatum(track.Lon, track.Lat)
        newheading = True
    elif heading_mode == 3:
        track2 = track

        if abs(track.Heading_rad - UI.GetHeadingRad()) < 0.7854:   #45 degrees, in radians
            track.Offset(0.2, track.Heading_rad)
            track.Offset(0.3, track.Heading_rad + (track.Heading_rad - UI.GetHeadingRad()))
            #offset the track if we are mostly behind it and in a pursuit position.

        heading1 = UI.GetHeadingToDatum(track.Lon, track.Lat) - UI.GetHeading()
        heading2 = UI.GetHeadingToDatum(track2.Lon, track2.Lat) - UI.GetHeading()

        if max(abs(heading1), abs(heading2)) == abs(heading2) and abs(heading2 - UI.GetHeading()) < 60:
            heading = degrees(track.Heading_rad) + heading2
            newheading = True
        else:
            heading = degrees(track.Heading_rad) + heading1
            newheading = True

    if UI.IsAir() and track.IsAir:
        if track.Range < 0.2:
            throttle = UI.GetThrottle() * 0.9
            newthrottle = True
        elif track.Range > 5 or abs(UI.GetHeadingToDatum(track.Lon, track.Lat)) > 5:
            throttle = 0.8
            newthrottle = True
        else:
            throttle = 1
            newthrottle = 1
        
    if newheading or newthrottle or newspeed or newalt:
        Flight_State(TI)
        
    if UI.TaskExists('AI_Pilot'):
        return newheading, newthrottle, newspeed, newalt, update, heading, speed, throttle, alt
    else:
        TI.SetUpdateInterval(update)
        if newheading:
            UI.SetHeading(heading)
        if newpitch:
            SetPitch(UI, pitch)
        if newthrottle:
            UI.SetThrottle(throttle)
        elif newspeed:
            UI.SetSpeed(speed)
        if newalt:
            SetAlt(UI, alt)
            
def DropBombs_Amram(UI, tgt_lon, tgt_lat, tgt_alt, qty):
    #use qty to organise the drop into grouping/sets
    if qty == 'all':
        carpet = True
    else:
        carpet = False
        try:
            qty = int(qty)
        except:
            qty = 10000

    maxbombs = 0
    launchers = 0
    noBombs = True
    
    if carpet:
        #determine qty per launcher, if we find a nuke, drop it and return true to end the run.
        for n in range(0, UI.GetLauncherCount()):
            launcher = UI.GetLauncherInfo(n)
            #quickly catalog to sort them out.
            if (launcher.LaunchMode == 3):
                noBombs = False  #we found some bombs
                if launcher.Quantity > maxbombs:
                    maxbombs = launcher.Quantity
                launchers = launchers + 1
                if launcher.IsNuclear:
                    UI.SendDatumToLauncher(tgt_lon,tgt_lat,tgt_alt,n)
                    status, excuse = Check_Status(UI, launcher, 1)
                    if status:
                        UI.SetActionText('Dropping Nukes')
                        UI.Launch(n, 1)
                        return True
        if noBombs:
            UI.SetActionText('')
            return True  #we have no bombs, return true to end the run.
        elif qty == 0:   #then we only wanted a count
            return maxbombs
        else:
            #we gave a quick cataloging skim of the launcher counts.
            #now we iterate over the launchers yet again, and for each relevant launcher, we release a weapon.
            for n in range(0, UI.GetLauncherCount()):
                launcher = UI.GetLauncherInfo(n)
                #quickly catalog to sort them out.
                if (launcher.LaunchMode == 3):
                    if launcher.Quantity > (maxbombs / 2) - 1:
                        #should make it so that only launchers with more than two more bombs that any other launcher are used
                        #if all launchers are equal, or the launcher only has one fewer than the maximum, then it gets used now as well.
                        UI.SendDatumToLauncher(tgt_lon,tgt_lat,tgt_alt,n)
                        status, excuse = Check_Status(UI, launcher, 1)
                        if status:
                            UI.SetActionText('Dropping Bombs')
                            UI.Launch(n, 1)
    else:
        for n in range(0, UI.GetLauncherCount()):
            launcher = UI.GetLauncherInfo(n)
            if (launcher.LaunchMode == 3) and qty != 0:
                noBombs = False
                UI.SendDatumToLauncher(tgt_lon,tgt_lat,tgt_alt,n)
                status, excuse = Check_Status(UI, launcher, 1)
                if status:
                    if (launcher.IsNuclear == 1):
                        UI.SetActionText('Dropping Nukes')
                        UI.Launch(n, 1)
                        return True
                    else:
                        UI.SetActionText('Dropping Bombs')
                        UI.Launch(n, 1)
            else:
                if launcher.Quantity > maxbombs:
                    maxbombs = launcher.Quantity
                return maxbombs
        if noBombs:
            return True
        else:
            return False
                   
def LoftedRange(UI, Lon, Lat, getTheta):
    v = Decimal(UI.GetSpeed() * 0.514444)
    try:
        alt = UI.GetMapTerrainElevation(Lon, Lat)
        if alt < 0:
            alt = 0
        y = Decimal(UI.GetAlt() - alt)
    except:
        y = Decimal(UI.GetAlt())
    
    #script doesn't like bombing a target above you yet, so the fix is to 'correct' negative y values
    #there is a modification to this that operates just fine with negative altitudes, someday.....
    
    g = Decimal(9.80665)
    
    if getTheta == 1:
        r = Decimal(UI.GetRangeToDatum(Lon, Lat) * 1000)
        v2 = Decimal(pow(v,2))
        v4 = Decimal(pow(v,4))
        r2 = Decimal(pow(r,2))
        common = g * (g * r2 + 2 * -y * v2)
        if v4 < common:
            #then its not possible, as we'll have a negative value
            return 90
        else:
            theta1 = Decimal(atan( (v2 + (v4 - common).sqrt()) /(g * r) ))
            theta1 = degrees(theta1)
            theta2 = Decimal(atan( (v2 - (v4 - common).sqrt()) /(g * r) ))
            theta2 = degrees(theta2)
            theta1, theta2
            theta = [theta1, theta2]
            return theta
    elif getTheta == 0:
        if y < 0:
            y = 0
        v2 = Decimal(pow(v,2))
        x = radians(UI.GetClimbDeg())
        sinx = Decimal(sin(x))
        sinx2 = Decimal(pow(sinx,2))
        cosx = Decimal(cos(x))
        loft_m = ((v * cosx) / g) * (v * sinx + (v2 * sinx2 + Decimal(2) * g * y).sqrt())

        sinx = Decimal(sin(0))
        cosx = Decimal(cos(0))
        level_m = sqrt(0.20394324 * float(y)) * float(v)

        x = radians(-70)
        sinx = Decimal(sin(x))
        cosx = Decimal(cos(x))
        dive_m = ((v * cosx) / g) * (v * sinx + (v2 * Decimal(pow(sinx,2)) + Decimal(2) * g * y).sqrt())

        v = Decimal(UI.GetMaxSpeed() * 0.54444)
        v2 = Decimal(pow(v,2))
        v4 = Decimal(pow(v,4))
        loft_max_m = Decimal((v4 - 2 * g * -y * v2) / (g * g)).sqrt()

        return float(dive_m), float(level_m), float(loft_m), float(loft_max_m)
    elif getTheta == 2:
        if y < 0:
            y = 0
        x = Decimal(radians(UI.GetClimbDeg()))
        sinx = Decimal(sin(x))
        time2 = ((-v * sinx) - (Decimal(pow(v * sinx,2)) - (Decimal(2)*-g*y)).sqrt())/-g
        return float(time2)
    elif getTheta == 3:
        if y < 0:
            y = 0
        x = Decimal(radians(UI.GetClimbDeg()))
        sinx = Decimal(sin(x))
        time1 = ((-v * sinx) + (Decimal(pow(v * sinx,2)) - (Decimal(2)*-g*y)).sqrt())/-g
        return float(time1)

def CruiseEnforcement(TI, Speed_Only = False):
    UI = TI.GetPlatformInterface()
    TI.SetUpdateInterval(5)
    if not(UI.TaskExists('CruiseEnforcement')):
        AddTask('CruiseEnforcement', 5,-1)
    if not(UI.TaskExists('TakeOff')):
        if UI.TaskExists('AutoLoiter'):
            DeleteHiddenTask(UI, 'AutoLoiter')
    if Speed_Only:
        if UI.GetClimbDeg() == 0:
            if UI.GetPlatformClass() == 'SR-71':
                UI.SetThrottle(1.0)
            else:
                UI.SetSpeed(UI.GetCruiseSpeedForAltitude(Landing.GetCruiseAltitude(UI)))
            TI.EndTask()
    else:
        if abs(UI.GetAlt() == Landing.GetCruiseAltitude(UI)) < 5 and UI.GetClimbDeg() == 0:  #matched altitude to within 5m, and have stopped changing altitude
            if UI.GetPlatformClass() == 'SR-71':
                UI.SetThrottle(1.0)
            else:
                UI.SetSpeed(UI.GetCruiseSpeedForAltitude(Landing.GetCruiseAltitude(UI)))
            TI.EndTask()
            
        if UI.GetPlatformClass() == 'SR-71':        
            SetAlt(UI, 27000)
        else:
            SetAlt(UI, Landing.GetCruiseAltitude(UI))
            
def GlideSlope(TI):
    UI = TI.GetPlatformInterface()
    TI.SetUpdateInterval(3)
    if UI.GetFuel() > 0:
        return  #do nothing until we run out of fuel.
    TI.SetUpdateInterval(0.25)
    
    init = TI.GetMemoryValue(174)
    if not init:
        UI.DisplayPopupMessage('Ditching')
        DeleteTask(UI, 'Lawndart_detection')
        TI.SetUpdateInterval(0.5)
        TI.SetMemoryValue(174,1)
        UI.SetClimbDeg(UI.GetClimbDeg() - 2)
        TI.SetMemoryValue(175,UI.GetSpeed())
    
        #alt,   Rho,    Mach,   Rho.D, Mach.D
    Atmo = {
        -500  :(1.225, 340.300,  0,      0),
        0     :(1.225, 340.300,  0,      0),
        500   :(1.167, 338.400, -0.058, -1.900),
        1000  :(1.112, 336.400, -0.056, -2.000),
        1500  :(1.058, 334.500, -0.054, -1.900),
        2000  :(1.006, 332.500, -0.052, -2.000),
        2500  :(0.957, 330.600, -0.050, -1.900),
        3000  :(0.909, 328.600, -0.048, -2.000),
        3500  :(0.863, 326.600, -0.046, -2.000),
        4000  :(0.819, 324.600, -0.044, -2.000),
        4500  :(0.777, 322.600, -0.042, -2.000),
        5000  :(0.736, 320.600, -0.041, -2.000),
        5500  :(0.697, 318.500, -0.039, -2.100),
        6000  :(0.660, 316.500, -0.037, -2.000),
        6500  :(0.624, 314.400, -0.036, -2.100),
        7000  :(0.590, 312.300, -0.034, -2.100),
        7500  :(0.557, 310.200, -0.033, -2.100),
        8000  :(0.526, 308.100, -0.031, -2.100),
        8500  :(0.496, 306.000, -0.030, -2.100),
        9000  :(0.467, 303.900, -0.029, -2.100),
        9500  :(0.440, 301.700, -0.027, -2.200),
        10000 :(0.413, 299.500, -0.026, -2.200),
        10500 :(0.389, 297.400, -0.025, -2.100),
        11000 :(0.365, 295.200, -0.024, -2.200),
        11500 :(0.337, 295.100, -0.027, -0.100),
        12000 :(0.312, 295.100, -0.025, 0),
        12500 :(0.288, 295.100, -0.024, 0),
        13000 :(0.267, 295.100, -0.022, 0),
        13500 :(0.246, 295.100, -0.020, 0),
        14000 :(0.228, 295.100, -0.019, 0),
        14500 :(0.211, 295.100, -0.017, 0),
        15000 :(0.195, 295.100, -0.016, 0),
        15500 :(0.180, 295.100, -0.015, 0),
        16000 :(0.166, 295.100, -0.014, 0),
        16500 :(0.154, 295.100, -0.013, 0),
        17000 :(0.142, 295.100, -0.012, 0),
        17500 :(0.132, 295.100, -0.011, 0),
        18000 :(0.122, 295.100, -0.010, 0),
        18500 :(0.112, 295.100, -0.009, 0),
        19000 :(0.104, 295.100, -0.008, 0),
        19500 :(0.096, 295.100, -0.008, 0),
        20000 :(0.089, 295.100, -0.007, 0),
        20500 :(0.082, 295.400, -0.007, 0.300),
        21000 :(0.076, 295.700, -0.006, 0.300),
        21500 :(0.070, 296.000, -0.006, 0.300),
        22000 :(0.065, 296.400, -0.005, 0.400),
        22500 :(0.060, 296.700, -0.005, 0.300),
        23000 :(0.055, 297.000, -0.005, 0.300),
        23500 :(0.051, 297.400, -0.004, 0.400),
        24000 :(0.047, 297.700, -0.004, 0.300),
        24500 :(0.043, 298.100, -0.004, 0.400),
        25000 :(0.040, 298.400, -0.003, 0.300),
        25500 :(0.037, 298.700, -0.003, 0.300),
        26000 :(0.034, 299.100, -0.003, 0.400),
        26500 :(0.032, 299.400, -0.003, 0.300),
        27000 :(0.029, 299.700, -0.002, 0.300),
        27500 :(0.027, 300.100, -0.002, 0.400),
        28000 :(0.025, 300.400, -0.002, 0.300),
        28500 :(0.023, 300.700, -0.002, 0.300),
        29000 :(0.021, 301.000, -0.002, 0.300),
        29500 :(0.020, 301.400, -0.002, 0.400),
        30000 :(0.018, 301.700, -0.001, 0.300),
        30500 :(0.017, 302.000, -0.001, 0.300),
        31000 :(0.016, 302.400, -0.001, 0.400),
        31500 :(0.015, 302.700, -0.001, 0.300),
        32000 :(0.014, 303.000, -0.001, 0.300),
        32500 :(0.013, 303.800, -0.001, 0.800),
        33000 :(0.012, 304.700, -0.001, 0.900),
        33500 :(0.011, 305.600, -0.001, 0.900),
        34000 :(0.010, 306.500, -0.001, 0.900),
        34500 :(0.009, 307.400, -0.001, 0.900),
        35000 :(0.008, 308.300, -0.001, 0.900),
        35500 :(0.008, 309.200, -0.001, 0.900),
        36000 :(0.007, 310.100, -0.001, 0.900),
        36500 :(0.007, 311.000, -0.001, 0.900),
        37000 :(0.006, 311.900, 0, 0.900),
        37500 :(0.006, 312.800, 0, 0.900),
        38000 :(0.005, 313.700, 0, 0.900),
        38500 :(0.005, 314.500, 0, 0.800),
        39000 :(0.005, 315.400, 0, 0.900),
        39500 :(0.004, 316.300, 0, 0.900),
        40000 :(0.004, 317.200, 0, 0.900),
        40500 :(0.004, 318.000, 0, 0.800),
        41000 :(0.003, 318.900, 0, 0.900),
        41500 :(0.003, 319.800, 0, 0.900),
        42000 :(0.003, 320.700, 0, 0.900),
        42500 :(0.003, 321.500, 0, 0.800),
        43000 :(0.003, 322.400, 0, 0.900),
        43500 :(0.002, 323.200, 0, 0.800),
        44000 :(0.002, 324.100, 0, 0.900),
        44500 :(0.002, 325.000, 0, 0.900),
        45000 :(0.002, 325.800, 0, 0.800),
        45500 :(0.002, 326.700, 0, 0.900),
        46000 :(0.002, 327.500, 0, 0.800),
        46500 :(0.002, 328.400, 0, 0.900),
        47000 :(0.001, 329.200, 0, 0.800),
        47500 :(0.001, 329.800, 0, 0.600),
        48000 :(0.001, 329.800, 0, 0),
        48500 :(0.001, 329.800, 0, 0),
        49000 :(0.001, 329.800, 0, 0),
        49500 :(0.001, 329.800, 0, 0),
        50000 :(0.001, 329.800, 0, 0)}

    Alt_lower = int(UI.GetAlt()/500)*500
    Alt_upper = (int(UI.GetAlt()/500)*500)+500
    Atmo_lower = Atmo.get(Alt_lower)
    Atmo_upper = Atmo.get(Alt_upper)
    Atmo_delta = float(UI.GetAlt()%500) / 500
    Rho = Atmo_lower[0] + (Atmo_upper[2] * Atmo_delta)
    cruise_mod = pow(Rho / 1.225,0.25)
    
    aircraft = UI.GetPlatformClass()
    if Aircraft_Speed(UI, aircraft) > 700:
        cruise_min = 240 / cruise_mod
    elif Aircraft_Speed(UI, aircraft) > 500:
        cruise_min = 195 / cruise_mod
    elif Aircraft_Speed(UI, aircraft) > 300:
        cruise_min = 150 / cruise_mod
    elif Aircraft_Speed(UI, aircraft) > 150:
        cruise_min = 120 / cruise_mod
    descent_speed = max(UI.GetCruiseSpeedForAltitude(UI.GetAlt()), cruise_min)
    
    ##cruisemin is inverted, it starts FAR too low at altitude, and increases with descent
    ##should begin large and shrink with descent.
    
    
    last_speed = TI.GetMemoryValue(175)
    TI.SetMemoryValue(175, UI.GetSpeed())
    if last_speed < UI.GetSpeed():
        accelerating = True
    else:
        accelerating = False
    
    if UI.GetClimbDeg() < 0:
        descending = True
    else:
        descending = False
    
    toofast = False
    tooslow = False
    if UI.GetSpeed() > descent_speed:
        toofast = True
    elif UI.GetSpeed() < descent_speed:
        tooslow = True
    
    if descending and toofast and accelerating:
        #pitch up to slow our descent rate to delay the crash
        UI.SetClimbDeg(UI.GetClimbDeg() + 1)
    if tooslow and not accelerating:
        #pitch down to increase speed to prevent stalling
        UI.SetClimbDeg(UI.GetClimbDeg() - 1)

    if descending:
        UI.SetActionText('Ditching: %3.0fs' % abs((UI.GetAlt() / (asin(radians(UI.GetClimbDeg())) * UI.GetSpeed()))))

#
#
