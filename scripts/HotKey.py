from UnitCommands import *
from GroupCommands import *

# key is string created from keypress character
def ProcessHotKey(UnitInfo, key):
    #UnitInfo.DisplayMessage(key)
    if ((key == '0') and (UnitInfo.HasThrottle())):
        SpeedCruise(UnitInfo)
    elif (key == '1'):
        if (UnitInfo.IsHelo()):
            SetFractionalSpeed(UnitInfo, 0.05, 1) # near hover for helo
        else:
            # last argument set to 1 to print message
            SetFractionalSpeed(UnitInfo, 0.3, 1)   
    elif (key == '2'):
        SetFractionalSpeed(UnitInfo, 0.50, 1)
    elif (key == '3'):
        SetFractionalSpeed(UnitInfo, 0.80, 1)
    elif (key == '4'):
        SetFractionalSpeed(UnitInfo, 1.0, 1)
    elif (key == '5'):
        SetFractionalSpeed(UnitInfo, 2.0, 1)  # afterburners or emergency power
    elif (key == 'e'):
        ToggleEngageAll(UnitInfo)
    elif (key == 'h'):
        UnitInfo.GetUserInput('SetHeading','Heading')
    elif (key == 'i'):
        UnitInfo.SendCommand('ShowPlatformDatabaseInfo')
    elif (key == 'f'):
        UnitInfo.SendCommand('ShowFlightPanel')
    elif (key == 's'):
        UnitInfo.SendCommand('ShowPlatformPanel')
    elif (key == 'g'):  # toggle landing gear/landing state for air units
        if (UnitInfo.GetLandingState()):
            UnitInfo.SetLandingState(0)   # raise gear
        else:
            UnitInfo.SetLandingState(1)        
    elif (key == 'm'):
        UnitInfo.GetUserInput('MoveToAndPatrol','Datum')
    elif (key == 'R'):
        ToggleRadars(UnitInfo)
    elif (key == 'w'):
        UnitInfo.GetUserInput('CreateWaypointScript','Datum')        
    elif (key == 'x'):
        EraseLastOrder(UnitInfo)
    elif (key == 'C'):
        UnitInfo.ClearTasks()
    # Raven58's mods:
    elif (key == 'H'):
        AltitudeHigh(UnitInfo)
        if UnitInfo.HasThrottle():
            alt = 10000
            if UnitInfo.GetSpeed() == UnitInfo.GetCruiseSpeedForAltitude(UnitInfo.GetAlt()):
                throttle = -1
            else:
                throttle = UnitInfo.GetThrottle()
            if throttle < 1.0 and alt > UnitInfo.GetAlt():
                UnitInfo.SetThrottle(1.0)
            OptionHandler(UnitInfo,'ClimbInitThrottle|Set|%s;ClimbInitAlt|Set|%s;cruiseclimb|Task|Start~0.2~-1' % (throttle, alt))
    elif (key == 'L'):
        AltitudeLow(UnitInfo)
        if UnitInfo.HasThrottle():
            alt = 150
            if UnitInfo.GetSpeed() == UnitInfo.GetCruiseSpeedForAltitude(UnitInfo.GetAlt()):
                throttle = -1
            else:
                throttle = UnitInfo.GetThrottle()
            if throttle < 1.0 and alt > UnitInfo.GetAlt():
                UnitInfo.SetThrottle(1.0)
            OptionHandler(UnitInfo,'ClimbInitThrottle|Set|%s;ClimbInitAlt|Set|%s;cruiseclimb|Task|Start~0.2~-1' % (throttle, alt))
    elif (key == 'M'):
        AltitudeMedium(UnitInfo)
        if UnitInfo.HasThrottle():
            alt = 4000
            if UnitInfo.GetSpeed() == UnitInfo.GetCruiseSpeedForAltitude(UnitInfo.GetAlt()):
                throttle = -1
            else:
                throttle = UnitInfo.GetThrottle()
            if throttle < 1.0 and alt > UnitInfo.GetAlt():
                UnitInfo.SetThrottle(1.0)
            OptionHandler(UnitInfo,'ClimbInitThrottle|Set|%s;ClimbInitAlt|Set|%s;cruiseclimb|Task|Start~0.2~-1' % (throttle, alt))
    elif (key == 'v'):
        ReverseOurCourse(UnitInfo)
    elif (key == 'b'):
        UnitInfo.AddTask('BombTarget', 3.0)
    elif (key == 't'):
        if UnitInfo.GetSpeed() == UnitInfo.GetCruiseSpeedForAltitude(UnitInfo.GetAlt()):
            throttle = -1
        else:
            throttle = UnitInfo.GetThrottle()
        ToggleRadars(UnitInfo)
    elif (key == 127): # DEL
        OptionHandler(UnitInfo,'DeleteUnit|Function|Yes')
        UnitInfo.DeletePlatform() # only works in edit mode
    elif (key == ')'):
        alt = GetCruiseAltitude(UnitInfo)
        OptionHandler(UnitInfo, 'CruiseEnforcement|Task|Start~5~-1')
        UnitInfo.SetAlt(alt)
        if UnitInfo.HasThrottle():
            throttle = '-1'
            if throttle < 1.0 and alt > UnitInfo.GetAlt():
                UnitInfo.SetThrottle(1.0)
            OptionHandler(UnitInfo,'ClimbInitThrottle|Set|%s;ClimbInitAlt|Set|%s;cruiseclimb|Task|Start~0.2~-1' % (throttle, alt))
    elif (key == '0'):
        OptionHandler(UnitInfo,'SetSpeed|Function|Cruise')
    else:
        msg = 'unrecognized key: %s' % key
        UnitInfo.DisplayMessage(msg)


# key is string created from keypress character
def ProcessHotKeyGroup(GI, key):
    unit_count = GI.GetUnitCount()
    if (unit_count <= 1):
        return
    if (key == 'h'):
        GI.GetUserInput('SetHeadingGroup','Heading')
    elif (key == 'C'):
        ClearTasksGroup(GI)       
    elif (key == '1'):
        RelGroupSpeed(GI, 0.3)
    elif (key == '2'):
        RelGroupSpeed(GI, 0.5)
    elif (key == '3'):
        RelGroupSpeed(GI, 0.8)
    elif (key == '4'):
        RelGroupSpeed(GI, 1.0)
    elif (key == '5'):
        RelGroupSpeedMax(GI)
    elif (key == '0'):
        OptionHandler(UnitInfo,'SetSpeed|Function|Cruise')
    elif (key == 'w'):
        GI.GetUserInput('CreateWaypointScript','Datum')        



# Keys for non-platform object hooked, or not own alliance
# This needs to be reworked
#def ProcessHotKeyOther(key):
    

# flags : bitfield  1 - shift pressed, 2 - ctrl pressed, 4 - alt pressed
#         e.g. flags == 6 indicates ctrl and alt were pressed during dclick
def ProcessDoubleClickHook(UnitInfo, flags):
    # in multiplayer try to take control of available unit first
    if (UnitInfo.IsMultiplayerActive()):
        if (not UnitInfo.IsPlayerControlled()):
            if (UnitInfo.IsAvailable()):
                UnitInfo.TakeControl()
            return
    
    # for units with aircraft show the flight panel unless shift is pressed
    # otherwise show the platform panel
    if (UnitInfo.HasFlightPort()):
        if ((flags & 1) != 1):
            UnitInfo.SendCommand('ShowFlightPanel')
        else:
            UnitInfo.SendCommand('ShowPlatformPanel')
    else:
        UnitInfo.SendCommand('ShowPlatformPanel')




