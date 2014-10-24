import random, time, csv, os, math, Landing, sys
from os.path import dirname, abspath, join, normpath
sys.path.append(abspath(join(dirname(__file__), 'Amram_Script_Data')))
from Amram_Utilities import *
from Menu import *
from decimal import Decimal
from UnitCommands import *
import json
    

#sets an offsert lead based on number of bombs.
#if offset is false, 
#Attempts to center a capret bombing on the target.
def bombing_lead(UI, track, offset=False):
    """
    bombing_lead(UI, track, offset=False)
    Returns appropriate Lead
    
    if Offset==True:
        Returns an offset in meters to begin dopping bombs early.
        Useful in centering a carpet bombing run on a target.
    else:
        Returns a predicted track position using the estimated time of fall for the weapon.
        Predicted position is where the track should be when the bomb gets there.
    """
    if offset:
        maxbombs = DropBombs_Amram(UI, 0, 0, 0, 0)
        offset = maxbombs / 2 * 0.1 - 0.05
        return offset
    else:
        leadTime = LoftedRange(UI, track.Lon, track.Lat, 2)
        track_lead = track.PredictAhead(leadTime)
        return track_lead
    
def basic_track_lead(UI, track):
    """
    basic_track_lead(UI, track)
    Returns a predicted track position based upon time to intercept the target track.
    """
    track_m = round(UI.GetRangeToTrack(track) * 1000,9)
    leadTime = track_m / (UI.GetSpeed() * 0.514444)
    track_lead = track.PredictAhead(leadTime)
    return track_lead
    
def Lawndart_detection(TI):
    """
    Lawndart_detection(TI)
    Task script, prevents pitch orders from causing controlled flight into terrain
    
    GCB will not prevent a pitch order from slamming an aircraft into the ground,
    and the bombing routine was not scripted to be wary of ground level.  This Script
    will watch for sink rates that are dangerous and may commandeer the aircraft.
    Typically idles until BB.KeyExists('uncontrolled_dive'), or positive climb angle
    Will only idle if no fuel, or Land/landHelo exists
    """
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
            
def SetPitch(UI, theta, rate=9, uncontrolled=True):
    """
    SetPitch(UI, theta, rate=9, uncontrolled=True):
    Takes desired pitch angles and controls the transition to them
    
    UI.SetClimbDeg is supposed to throttle its response, but this has proven untrue
    140 degree pitch changes in 1/10 of a second have been witnessed.
    rate is a multiplier, 9 seems reasonable for most applications.  Higher values
    result in faster pitch rates being applied.
    if uncontrolled==True:
        Will create BB.Key('uncontrolled_dive') if it does not exist.
        This serves to alert Lawndart detection so that it will prevent controlled
        flight into terrain
    else:
        it will not alert Lawndart Detection, only set uncontrolled=False if the calling
        script has its own means to prevent controlled flight into terrain
    """
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
    """
    cruiseclimb(TI)
    A script to modulate the pitch of a climbing aircraft to keep its speed up.
    
    Both 1.25 and 1.26 throw caution to the wind and attempt to achieve the DB climbrate
    at all times when ordered to climb, this means that with decreasing thrust as altitude
    increases and speed decreases, GCB is not easing its climbrate to prevent stalls
    
    This script will attempt to hold cruise speed all the way to whatever altitude you request.
    it is unable to intercept climbs ordered by using the hud interface, and so they remain prone to stalls
    """
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
    
        SetPitch(UI, new_pitch, rate=rate_mod, uncontrolled=False)
        write_speed = str(UI.GetSpeed())
        BB.Write('Last_Speed',write_speed)

def Flight_State(TI, reset = False):
    """
    Flight_State(TI, reset = False):
    Saves or restores the current flight state when called.
    
    Intended for use with the bombing routines to return the aircraft to its previous flight conditions.
    if reset==True:
        It will read the saved altitude, speed, throttle, and heading.  It will attempt to restore these
        conditions with one alteration, it will reverse the heading to leave the target area.
    else:
        It will save the speed, throttle if available, heading, and altitude for later recall.
    """
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
    """
    BombRun(TI):
    Replacement for the stock Bombing routine.  Capable of lofting, diving, and carpet bombing.
    Very math heavy, very high update rate.
    
    if BB.KeyExists('BombDatum'):
        it will proceed with a datum bombing run, setting or ordering a new bombing target will
        have no effect if this key is not deleted as it will continue towards bombing this datum.
        Currently drops every bomb it has and only terminates the attack once all are dropped.
    else:
        It will bomb the currently assigned target.  Setting a new target WILL trigger a change in
        heading to proceed to and bomb the newly designated target. No target or an invalid(dead)
        target will trigger self termination of the script, otherwise termination of the attack will
        occur once it is killed or all bombs are dropped.
        
    if BB.KeyExists('Style'):
        Setting the Style yourself allows player control over whether or not it will dive, loft, or carpet
        bomb the target.  This must be set prior to initial operation of the script.
    else:
        The script will evaulate the target and its current conditions and attempt to determine the correct
        style of attack.
    """
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

    if Lawndart_detection(TI) or UI.TaskExists('Lawndart_Correction'):
        return

        
    current_speed = UI.GetSpeed() * 0.514444
    max_speed = max(UI.GetMaxSpeedForAltitude(UI.GetAlt()), UI.GetMaxSpeedForAltitudeAB(UI.GetAlt())) * 0.514444
    offset_m = current_speed * offset

    
    #perform restoration of previous flight condition
    if BB.KeyExists('Bombing_Complete'):
        BB.WriteGlobal('Flight_State', 'reset')
        newspeed, newthrottle, newalt, speed, throttle, alt, restored = Flight_State(TI)
        if restored:
            BB.Erase('Bombing_Complete')
            TI.EndTask()
        if UI.TaskExists('AI_Pilot'):
            return
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
        if UI.QueryDatabase('air', UI.GetPlatformClass(),'Designation').GetString(0) == 'Bomber' or UI.QueryDatabase('simpleair', UI.GetPlatformClass(),'Designation').GetString(0) == 'Bomber':
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
    """
    Intercept(TI)
    A replacement script for the stock IntC.  Does not rely on formation functions to complete its intercept.
    
    Comes in hot, full throttle, does not attempt to match the target flight, merely tries to run it over
    in order to line up for a gun shot in as little time as possible.  Will perform a lag pursuit within 5km
    and match the target altitude if its able.
    """
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
                #alt, 0 is cruise alt, 1 is within +30/-45 deg angular, 2 is match
                #heading type 0 is lag, 1 is intercept, 2 is mach2 offset lead, 3 is calculated gun lead
                   #range_km    Heading_Type
                             #Alt-      Update
    range_rates = [
                   [  0.00,    2,    2,  0.15],
                   [  1.50,    2,    2,  0.2],
                   [  2.00,    2,    2,  0.3],
                   [  2.50,    2,    2,  0.6],
                   [  5.00,    2,    2,  1.0],
                   [  8.00,    1,    2,  2.0],
                   [ 15.00,    1,    2,  3.5],
                   [ 23.00,    0,    1,  5.0],
                   [ 60.00,    0,    1,  5.0],
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
    """
    DropBombs_Amram(UI, tgt_lon, tgt_lat, tgt_alt, qty):
    Provided target co-ordinate, drops the specified quantity of bombs.  Returns true when complete.
    """
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
    """
    LoftedRange(UI, Lon, Lat, getTheta):
    Computs trajectories.  May return level, loft, dive ranges, trajectories to hit target range, and bomb lead time
    
    if getTheta==1:
        returns the two angles which will result in hitting the target distance.
            returns [dive theta,loft theta] if possible to reach target distance, returns 90 if not.
    elif getTheta==0:
        returns ranges for current flight conditions: float(dive_m), float(level_m), float(loft_m), float(loft_max_m)
            dive assumes -70 degrees dive angle
            level assumes 0 degrees pitch angle
            loft_m assumes current pitch angle
            loft_max assumes optimum pitch angle
    elif getTheta==2:
        returns a solution of the quadratic formula for time, result may be negative, result should be rejected if so.
        Provides lead time for dive bombing.
    elif getTheta==3:
        returns a solution of the quadratic formula for time, result may be negative, result should be rejected if so.
        Provides lead time for loft bombing.
    """
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
        gy2 = Decimal(2) * g * y
        loft_m = ((v * cosx) / g) * (v * sinx + (v2 * sinx2 + gy2).sqrt())

        sinx = Decimal(sin(0))
        cosx = Decimal(cos(0))
        level_m = sqrt(0.20394324 * float(y)) * float(v)

        x = radians(-70)
        sinx = Decimal(sin(x))
        cosx = Decimal(cos(x))
        dive_m = ((v * cosx) / g) * (v * sinx + (v2 * sinx2 + gy2).sqrt())

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
    """
    CruiseEnforcement(TI, Speed_Only = False):
    Script Task, Ensures the aircraft reaches a cruise condition, terminates when finished.
    
    GCB has a tendancy to overshoot altitude changes.  As a result, it may climb at full throttle, 
    level off, moss its altitude, set cruise, descend to correct altitude, overshoot again, climb, 
    set full throttle, reach altitude.  Result is a failure to cruise, your left at full throttle.
    
    if Speed_Only==True:
        Orders cruising speed, doesn't check or order altitude changes.
        Special condition for SR-71, 100% throttle.
        Self terminates once cruise speed is reached.
    else:
        Orders cruising altitude and cruising speed.  Waits for altitude to stabilize before re-ordering
        cruising speed to ensure cruise speed is effectively set.
        Special condition for SR-71, 100% throttle, 27500m.
        Self terminates once cruise speed and altitude have been reached.
    """
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
    """
    GlideSlope(TI):
    Rudimentary anti-stall script for aircraft that have run out of fuel.
    
    It looks up the aircraft stall speed, and uses twice that if available.
    and controls pitch to assure that the speed remains at that level.
    """
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
    
    stall_speed = UI.GetStallSpeedForAltitude(UI.GetAlt())
    descent_speed = stall_speed * 2.2

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
