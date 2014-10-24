#relocating my utility scripts.  i'm beginning to have a few of them, and would like to try and avoid having to constantly refer back and forth between my files, and overgrow my core files.
import sys, os, math
from os.path import dirname, abspath, join, normpath
sys.path.append(abspath(join(dirname(__file__), '..', 'bin', 'lib')))
from UnitCommands import *
import json, csv 


def DeleteTask(interface, taskname):
    """
    DeleteTask(interface, taskname):
    Deletes the named task, whether hidden or not, for entire groups or single units.
    """
    try:
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
            
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            if UI.TaskExists(taskname):
                UI.DeleteTask(taskname)
            if UI.TaskExists(taskname):  #if it still exists, it must have been hidden.
                UI.AddTask(taskname, -1, 0)   #unhides the hidden task so it can be removed.
                UI.DeleteTask(taskname)
    else:
        UI = interface
        if UI.TaskExists(taskname):
            UI.DeleteTask(taskname)
        if UI.TaskExists(taskname):  #if it still exists, it must have been hidden.
            UI.AddTask(taskname, -1, 0)   #unhides the hidden task so it can be removed.
            UI.DeleteTask(taskname)

def AddTask(interface, taskname, rate = 1, hidden = 0):
    """
    AddTask(interface, taskname, rate = 1, hidden = 0):
    Adds the named task to all selected units.
    rate is update interval, defaults to 1.
    hidden=-1 sets task as hidden on start.
    """
    try:
        test = interface.GetPlatformId()
        group = False
    except:
        group = True

    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            if UI.TaskExists(taskname):
                return
            else:
                UI.AddTask(taskname, rate, hidden)
    else:
        UI = interface
        if UI.TaskExists(taskname):
            return
        else:
            UI.AddTask(taskname, rate, hidden)
        
def DeleteHiddenTask(UI, taskname):  #Thanks to 4rk for this function
    """
    DeleteHiddenTask(UI, taskname):  #Thanks to 4rk for this function
    Unhides a task prior to attemptiong to delete it ensuring the task is deleted.
    """
    if UI.TaskExists(taskname):
        UI.AddTask(taskname, -1, 0)   #unhides the hidden task so it can be removed.
        UI.DeleteTask(taskname)
        
def Read_Message_List(BB, msg_name):
    """
    Read_Message_List(BB, msg_name):
    Reads the named BB message contents, json.loads it, and returns the resulting list.
    Returns an empty list if the message is not found or could not be read back.
    """
    try:
        msg_item = BB.ReadMessage(msg_name)
        msg_item = json.loads(msg_item)
        try:
            test = len(msg_item)
        except:
            msg_item = []
    except:
        msg_item = []
    return msg_item
    
def Read_Message_Dict(BB, msg_name):
    """
    Read_Message_Dict(BB, msg_name):
    Reads the named BB message contents, json.loads it, and returns the resulting dict.
    Returns an empty dict if the message is not found or could not be read back.
    """
    try:
        msg_item = BB.ReadMessage(msg_name)
        msg_item = json.loads(msg_item)
        try:
            test = msg_item.keys()
        except:
            msg_item = {}
    except:
        msg_item = {}
    return msg_item

def Write_Message_List(BB, arg1, arg2):
    """
    Write_Message_List(BB, arg1, arg2):
    Converts a list, tuple, or dictionary with json.dumps, then saves it to the named BB message name.
    
    arg1 or arg2 may be the message name, or the message itself.  This script type() checks arg2
    and acts accordingly.  There is a 2048 character limit on the resulting dumps string.
    """
    if type(arg2) == type(''):
        msg_list = json.dumps(arg1)
        BB.WriteGlobal(arg2, msg_list)
    elif type(arg1) == type(''):
        msg_list = json.dumps(arg2)
        BB.WriteGlobal(arg1, msg_list)
        
def Try_Read_Message(BB, msg_name, msg_type):
    """
    Try_Read_Message(BB, msg_name, msg_type):
    Reads in a BB message and returns the result formatted in the desired type.
    
    if msg_type == 0:
        returns the result formatted as a string
        returns '' if the result was invalid or the key was not found.
    elif msg_type == 1:
        returns the result formatted as an int
        returns 0 if the result was invalid or the key was not found.
    elif msg_type == 2:
        returns the result formatted as an float
        returns 0.0 if the result was invalid or the key was not found.
    """
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
            msg_item = 0.0
    return msg_item

def OptionHandler(interface, params):
    """
    OptionHandler(interface, params):
    Provides a method to issue multiple commands from a single menu item to single or groups of units.
    
    GCB's menu functions are limited to single actions, such as passing strings.  Passing strings with a set
    structure allows a measure of language to be built in, and thus, the ability to format a single string to
    contain multiple commands.
    
    It will iterate over all selected units and pass the same commands to each through the SetOption() function.
    
    example param string:
    'BombRunInitialized|Erase|1;Bombing_Complete|Erase|1;BombDatum|Erase|1;Style|Set|dive;BombRun|Task|Start~1~0'
    
    resulting command list:
    [['BombRunInitialized','Erase','1'],
    ['Bombing_Complete','Erase','1'],
    ['BombDatum','Erase','1'],
    ['Style','Set','dive'],
    ['BombRun','Task','Start~1~0']]
    """
    params = [x.split('|') for x in params.split(';')]

    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        test = interface.GetAlt()
        group = False
    except:
        group = True
        
    if group:
        for param in params:
            for unit in xrange(interface.GetUnitCount()):
                UI = interface.GetPlatformInterface(unit)
                SetOption(UI, param)
    else:
        UI = interface
        for param in params:
            SetOption(UI, param)
        
def SetOption(UI, params):
    """
    SetOption(UI, params):
    Receives single commands in the format of ['command name', 'command type', 'command content'] and applies them to
    the unit it is currently operating on.
    """
    BB = UI.GetBlackboardInterface()
    if type(params) == type(''):
        #then we got passed back to ourself, so we used getinput last pass.
        if BB.KeyExists('SetRadius'):
            BB.Erase('SetRadius')
            variable = BB.ReadMessage('temp_var')
            BB.Erase('temp_var')
            method = 'Set'
            temp_value = BB.ReadMessage('DatumTemp')
            BB.Erase('DatumTemp')
            temp2_value = temp_value + '~' + params
            value = [float(x) for x in temp2_value.split('~')]
        else:
            variable = BB.ReadMessage('temp_var')
            BB.Erase('temp_var')
            method = 'Set'
            value = params
    else:
        variable, method, value = params

    if method == 'Toggle':
        if BB.ReadMessage(variable) == '1':
            BB.WriteGlobal(variable, '0')
        else:
            BB.WriteGlobal(variable, '1')
    elif method == 'Erase':
        if BB.KeyExists(variable):
            BB.Erase(variable)
    elif method == 'Set':
        if type(value) == type([]):
            Write_Message_List(BB, value, variable)
        elif type(value) == type(''):
            BB.WriteGlobal(variable, value)
        else:
            BB.WriteGlobal(variable, str(value))
    elif method == 'Input':
        BB.WriteGlobal('temp_var', variable)
        BB.WriteGlobal('temp_meth', 'Set')
        #try to loop within ourselves by calling ourself when using GetuserInput.
        UI.GetUserInput('SetOption', 'Text %s' % value)
    elif method == 'Task' and 'Start' in value:
        if '~' not in value:
            val1 = 0.0
            val2 = 0
        else:
            tasking = value.split('~')
            value = tasking[0]
            val1 = float(tasking[1])
            val2 = int(tasking[2])
        AddTask(UI, variable, val1, val2)
    elif method == 'Task' and 'End' in value:
        if type(variable) == list:
            for task in xrange(len(variable)):
                DeleteTask(UI, variable[task])
        else:
            DeleteTask(UI, variable)
    elif method == 'Plus':
        var = Try_Read_Message(BB, variable,2)
        value = str(var + float(value))
        BB.WriteGlobal(variable, value)
    elif method == 'Minus':
        var = Try_Read_Message(BB, variable,2)
        value = str(var - float(value))
        BB.WriteGlobal(variable, value)
    elif method == 'Multiply':
        var = Try_Read_Message(BB, variable,2)
        value = str(var * float(value))
        BB.WriteGlobal(variable, value)
    elif method == 'Divide':
        var = Try_Read_Message(BB, variable,2)
        value = str(var / float(value))
        BB.WriteGlobal(variable, value)
    elif method == 'Copy':
        var = Try_Read_Message(BB, variable,0)
        BB.WriteGlobal(value, var)
    elif method == 'Datum':
        BB.WriteGlobal('temp_var', variable)
        UI.GetUserInput('OptionSetDatum', 'Datum')
    elif method == 'Box':
        BB.WriteGlobal('temp_var', variable)
        if BB.KeyExists('SetRadius'):
            BB.Erase('SetRadius')
        if BB.KeyExists('LastDatum'):
            BB.Erase('LastDatum')
        UI.GetUserInput('OptionSetBox', 'Box')
    elif method == 'Radius':
        BB.WriteGlobal('temp_var', variable)
        BB.WriteGlobal('temp_val', value)
        if BB.KeyExists('LastDatum'):
            BB.Erase('LastDatum')
        BB.WriteGlobal('SetRadius', '1')
        UI.GetUserInput('OptionSetDatum', 'Datum')
    elif method == 'SetPointRadius':
        if BB.KeyExists('SetRadius'):
            BB.WriteGlobal('temp_var', variable)
            BB.WriteGlobal('DatumTemp', value)
            temp_val = BB.ReadMessage('temp_val')
            UI.GetUserInput('SetOption', 'Text %s' % temp_val)
        points = [float(x) for x in value.split('~')]
        Write_Message_List(BB, points, variable)
    elif method == 'Function':
        if variable == 'FormationModeNR':
            UI.SetFormationUseNorthBearing(int(value))

        #Substuff
        elif variable == 'Periscope':
            SI = UI.GetSubInterface()
            value = int(value)
            if value:
                SI.RaisePeriscope()
            else:
                SI.LowerPeriscope()
        elif variable == 'Snorkel':
            SI = UI.GetSubInterface()
            value = int(value)
            SI.SetSnorkelState(value)
        elif variable == 'RadarMast':
            SI = UI.GetSubInterface()
            value = int(value)
            if value:
                SI.RaiseRadarMast()
            else:
                SI.LowerRadarMast()
            
        #speed
        elif variable == 'SetSpeed':
            if value == 'Cruise':
                BB.WriteGlobal('Cruise_Speed_Only')
                AddTask('CruiseEnforcement', 5,-1)
            else:
                UI.SetSpeed(float(value))
        elif variable == 'SetSpeed+':
            UI.SetSpeed(UI.GetSpeed() + float(value))
        elif variable == 'SetSpeed':
            UI.SetSpeed(float(value))
        elif variable == 'SetThrottle':
            UI.SetThrottle(float(value))
            
        #altitude
        elif variable == 'AltitudeMatch':
            track = UI.GetTargetTrackInfo()
            UI.SetAltitude(track.Alt)
        elif variable == 'AltitudeStandard':
            if value == 'Cruise':
                if UI.GetPlatformClass() == 'SR-71':
                    cruise_alt_m = 27500
                if (UI.HasThrottle()):
                    cruise_alt_m = UI.GetCruiseAltitude()
                elif (UI.IsHelo()):
                    cruise_alt_m = 2000.0
                else:
                    cruise_alt_m = 10000.0
                try:
                    SetAlt(UI, cruise_alt_m)
                except:
                    from UnitCommands import SetAlt
                    SetAlt(UI, cruise_alt_m)
            elif value == 'Periscope':
                if UI.IsSub():
                    SI = UI.GetSubInterface()
                    SI.GoToPeriscopeDepth()
            elif value == 'Missile':
                max_depth = []
                valid_depth = False
                for n in range(0,UI.GetLauncherCount()):
                    launcher = UI.GetLauncherInfo(n)
                    if launcher.MinLaunchAlt_m < 0 and launcher.MinLaunchAlt_m > -100:
                        depth = launcher.MinLaunchAlt_m +5
                        max_depth.append(depth)
                        valid_depth = True
                if valid_depth:
                    max_depth.sort()
                    UI.SetAlt(max_depth[0])
                else:
                    UI.DisplayMessage('No valid misisle depth')
                    UI.DisplayMessage('%s going to -27m' % UI.GetName())
                    UI.SetAlt(-27)
            elif float(value) < 0:
                SI = UI.GetSubInterface()
                depth = float(value)
                if depth < SI.GetMaxDepth() * -1:
                    depth = (SI.GetMaxDepth()) * -1
                if UI.IsSub():
                    UI.SetAlt(depth)
            else:
                alt = float(value)
                if UI.IsAir():
                    if alt > UI.GetMaxAlt():
                        alt = UI.GetMaxAlt()
                    try:
                        SetAlt(UI, alt)
                    except:
                        from UnitCommands import SetAlt
                        SetAlt(UI, alt)
        elif variable == 'AltitudeInput':
            UI.GetUserInput('AltitudeGetInput', 'Text %s' % value)
            
        #heading
        elif variable == 'HeadingStandard':
            UI.GetUserInput('SetHeading', 'Heading')
        elif variable == 'HeadingInput':
            UI.GetUserInput('HeadingGetInput', 'Text %s' % value)
        elif variable == 'HeadingSpecified':
            UI.SetHeading(float(value))
            
        #Waypoint
        #can't bring them all in here, they are a bit too complex to do so. yet
        elif variable == 'WaypointLoop':
            UI.SetNavLoopState(value)
            
        #Sensors
        elif variable == 'SensorState':
            sensor_type, sensor_state = value.split('~')
            sensor_state = int(sensor_state)
            sensor_type = int(sensor_type)
            for sensor in xrange(UI.GetSensorCount()):
                sensor_info = UI.GetSensorInfo(sensor)
                if sensor_info.type == int(sensor_type):
                    UI.SetSensorState(sensor, sensor_state)
        
        #Formation Stuff
        elif variable == 'Formation_Member':
            UI.SetFormationLeader(int(value))
        elif variable == 'Formation_Mode_RN':
            UI.SetFormationUseNorthBearing(int(value))
        elif variable == 'Formation_Mode_Sprint_Pace':
            UI.SetFormationMode(int(value))
        elif variable == 'Formation_Alt':
            UI.SetFormationAltitudeOffset(int(value))
        elif variable == 'FormationEdit':
            UI.SetFormationEdit(int(value))
            
        #special stuff, delete
        elif variable == 'DeleteUnit':
            UI.DeletePlatform()

        elif variable == 'Target':
            UI.SetTarget(int(value))

def FormationLeaderInput(interface, target):
    """
    FormationLeaderInput(interface, target):
    Receives a target track from a menu command, and forwards the result to Option handler to assign the target
    as formation leader for all selected units.
    """
    OptionHandler(interface, 'Formation_Member|Function|%s' % target)
            
def HeadingGetInput(UI, arg):
    """
    HeadingGetInput(UI, arg):
    Receives a heading from a menu command, and forwards the result to Option handler to assign the heading
    for all selected units.
    """
    params = 'HeadingSpecified|Function|%s' % arg
    #loop back into ourself after collecting the input..
    OptionHandler(UI, params)

def AltitudeGetInput(UI, arg, param):
    """
    AltitudeGetInput(UI, arg, param):
    Receives an altitude from a menmu command, and forwards the result to Option handler to assign the altitude
    for all selected units.
    
    If paramn is negative, we received a depth instead, and it will be forced negative before forwarding it.
    """
    if param == 2:
        #force it negative
        arg = str(abs(float(arg)) * -1)
    else:
        arg = str(abs(float(arg)))
    params = 'AltitudeStandard|Function|%s' % arg
    #loop back into ourself after collecting the input..
    OptionHandler(UI, params)
    
def OptionSetDatum(UI, Lon1, Lat1):
    """
    OptionSetDatum(UI, Lon1, Lat1):
    Receives a datum from a menu command, and forwards the result to Option handler to assign the datum
    for all selected units.
    
    Primarily intended for use with the currently defunct radius patrol.
    """
    BB = UI.GetBlackboardInterface()
    datum = '%0.7f~%0.7f'% (Lon1, Lat1)
    variable = BB.ReadMessage('temp_var')
    BB.Erase('temp_var')
    if BB.KeyExists('SetRadius'):
        OptionHandler(UI, '%s|SetPointRadius|%s' % (variable, datum))
    if BB.KeyExists('SetMissionDatum'):
        OptionHandler(UI, '%s|SetPoint|%s' % (variable, datum))

def OptionSetBox(UI, Lon1, Lat1, Lon2, Lat2):
    """
    OptionSetBox(UI, Lon1, Lat1, Lon2, Lat2):
    Receives a box from a menu command, and forwards the result to Option handler to assign the box
    for all selected units.
    """
    BB = UI.GetBlackboardInterface()
    box = '%0.7f~%0.7f~%0.7f~%0.7f'% (Lon1, Lat1, Lon2, Lat2)
    variable = BB.ReadMessage('temp_var')
    BB.Erase('temp_var')
    OptionHandler(UI, '%s|SetPoints|%s' % (variable, box))

def CreateWaypointScript(interface, lon, lat):
    """
    CreateWaypointScript(interface, lon, lat):
    Receives a datum from a menu command, and forwards the result to Option handler to assign the waypoint
    for all selected units.
    """
    from UnitCommands import AddWaypointOrder
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
            
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            AddWaypointOrder(UI, lon, lat)
    else:
        UI = interface
        AddWaypointOrder(UI, lon, lat)
        
def RemoveWaypointScript(interface, idx):
    """
    RemoveWaypointScript(interface, idx):
    Receives a number from a menu command, and deletes the selected waypoint for all selected units
    """
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True

    idx = int(idx)
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            DeleteWaypoint(UI, idx)
    else:
        UI = interface
        DeleteWaypoint(UI, idx)

def OptionSetTargeting(interface, *args):
    """
    OptionSetTargeting(interface, *args):
    Receives a target, datum, or box from a menu item, and forwards the result to all selected units.
    
    *args will contain the passed data.  1 arg will be a target, 2 will be a datum.
    Should be expanded to accept 4 args and pass a box someday.
    Should also be expanded to accept three args and pass a polar coordinate.
    """
    try:
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
    
    #we don't know yet if we will be given a target, or a datum.
    
    if len(args) == 1:
        #target ID
        targetID = args[0]
        target = 1
    elif len(args) == 2:
        #datum string.
        datum = [args[0], args[1]]
        target = 0
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            BB = UI.GetBlackboardInterface()
            if target:
                missiontarget = ['Target', targetID]
                Write_Message_List(BB, 'MissionTarget', missiontarget)
                UI.SetTarget(targetID)
            else:
                missiontarget = ['Datum', datum]
                Write_Message_List(BB, 'MissionTarget', missiontarget)
    else:
        UI = interface
        BB = UI.GetBlackboardInterface()
        if target:
            missiontarget = ['Target', targetID]
            Write_Message_List(BB, 'MissionTarget', missiontarget)
            UI.SetTarget(targetID)
        else:
            missiontarget = ['Datum', datum]
            Write_Message_List(BB, 'MissionTarget', missiontarget)
        
def InputHandler(interface, input, param):
    """
    InputHandler(interface, input, param):
    Takes an input and parameter and records it to the blackboard of all selected units.
    
    The parameter determines the name of the BB message given that until very recently
    MenuItemUIWithTextParam delivered broken formatting necessitating use of the integer param item.
    """
    variables = ['MissileOffenseAllowRange', 'MissileDefenseAllowAirRange', 'MissileDefenseAllowMisRange', 'MissileStrikeRange', 'error_km', 'InvMulti']
    variable = variables[param]
    input = ''.join([x for x in input if ord(x) < 128])
    
    try:
        test = interface.GetPlatformId()
        group = False
    except:
        group = True    
    
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            BB = UI.GetBlackboardInterface()
            BB.WriteGlobal(variable, input)
    else:
        UI = interface
        BB = UI.GetBlackboardInterface()
        BB.WriteGlobal(variable, input)

def LoadoutHandler(UI, param):
    """
    LoadoutHandler(UI, param):
    Handler for complex usage of loadouts in the menu's, allows for additive loadout stocking, or loadout assignment.
    
    param is a complex formatted string:
    armament, aircraft, loadout, count, InvMulti, additive = param.split('|')
    if additive=='1':
        adds the loadout content to the magazines
    else:
        assigns the loadout to the unit overwriting the launchers and stock contents
    """
    armament, aircraft, loadout, count, InvMulti, additive = param.split('|')
    #aircraft, count, InvMulti, loadout = loads(param)
    BB = UI.GetBlackboardInterface()
    
    if additive == '1':    
        loadouts_dict = Read_Message_Dict(BB, 'loadouts_dict')
        loadout = loadouts_dict[armament][aircraft][loadout]
        for weapon in loadout:
            qty = loadout[weapon] * int(count) * float(InvMulti)
            qty = int(math.ceil(qty))
            UI.AddItemToMagazine(weapon, qty)
    else:
        UI.EquipLoadout(loadout)
        
def read_loadout_file(tgt_names, filter, filter_list):
    """
    read_loadout_file(tgt_names, filter, filter_list):
    Reads in platform_setup.csv and launcher_loadout.csv, and returns a formatted dictionary of the contents
    
    This provides the information necessary to do additive loadouts, or to display the contents of a laodout
    """
    #debug = open('log/loadout.txt', 'w')
    aircraft_dict = {}
    for each_name in tgt_names:
        aircraft_dict[each_name] = {}
    #load platform setups.
    filepath = 'scripts/Amram_Script_Data/CSVs/' + 'platform_setup.csv'
    file = normpath(join(os.getcwd(), filepath))
    datafile = open(file, 'r')
    datareader = csv.reader(datafile)
    setup_names = {}
    for row in datareader:
        aircraft_name = row[0]
        simple_name = row[1]
        setup = row[6]
        reject_list = ['xit', 'nter', 'ervice', 'ntil',] # ['Exit', 'Enter', 'Service', 'Until',] dropped initial letter to avoid upper vs lower case discrimination.
        Proceed = True
        for reject in reject_list:
            if reject in aircraft_name:
                Proceed = False
            if setup in ['-L', None]:
                Proceed = False
                
        if Proceed and aircraft_name in tgt_names:
            aircraft_dict[aircraft_name][setup] = simple_name
            setup_names[setup] = None
    
    #get the loadout names
    tgt_names = []
    for entry in setup_names:
        if entry not in tgt_names:
            tgt_names.append(entry)
    
    #load launcher loadouts.
    filepath = 'scripts/Amram_Script_Data/CSVs/' + 'launcher_loadout.csv'
    file = normpath(join(os.getcwd(), filepath))
    datafile = open(file, 'r')
    datareader = csv.reader(datafile)
    load_dict = {}
    filepath = 'scripts/Amram_Script_Data/CSVs/' + 'launcher_loadout.csv'
#    filepath = 'c:/GCB2_1.25_Nov_16/scripts/Amram_Script_Data/Aircraft/launcher_loadout.csv'
    file = normpath(join(os.getcwd(), filepath))
    datafile = open(file, 'r')
    datareader = csv.reader(datafile)
    load_dict = {}
    for row in datareader:
        if row[0] in tgt_names and row[2] != '' and not row[2].isspace():
            #print row
            fail = 0
            if row[3] == '' or row[3].isspace():
                qty = 0
            else:
                qty = int(row[3])
            wpn = row[2]
            ld = row[0]
            if wpn != '' and not wpn.isspace():
                try:
                    load_dict[ld][wpn] += qty
                except:
                    try:
                        load_dict[ld][wpn] = qty
                        test = load_dict[ld]
                    except:
                        load_dict[ld] = {wpn:qty}
    #we have our platform setups, and our launcher loadouts.
    
    
    
    #time to mate them, and combine like entries for launcher loadouts.
    #also sort them for easing usage in the menu and for other purposes

    loadouts_dict = {}
    done_loadout = []
    menu_list = [ [1, 'AW', 'Air to Air', 2], [2, 'GM', 'Air to Ground Missile', 2], [3, 'SM', 'Air to Surface Missile', 2], [4, 'IB', 'Unguided Bombs', 2], [5, 'GB', 'Guided Bombs', 2], [6, 'UR', 'Unguided Rockets', 2], [7, 'T', 'Torpedoes', 1], [8, ['N', 'X'], 'Nuclear', 1], [9, 'SD', 'Suppression of Air Defences', 2], [10, 'CS', 'Close Support', 2]]
    for aircraft in aircraft_dict:
#        debug.write('%s\n' % aircraft)
        for item in menu_list:
            for platform_setup in aircraft_dict[aircraft]:
                if platform_setup != '' and not platform_setup.isspace() and platform_setup not in done_loadout:
                    simple_loadout_name = aircraft_dict[aircraft][platform_setup]
                    proceed = True
                    if filter:
#                        debug.write('%s pass filter: %s\n' % (simple_loadout_name, simple_loadout_name in filter_list))
                        if simple_loadout_name not in filter_list:
                            proceed = False
                    if simple_loadout_name[:item[3]] in item[1] and proceed:
#                        debug.write('%s proceed\n' % simple_loadout_name)
                        loadout = load_dict[platform_setup]
                        armament = item[2]
                        try:
                            loadouts_dict[armament][aircraft][simple_loadout_name] = loadout
                        except KeyError:
                            try:
                                loadouts_dict[armament][aircraft] = {simple_loadout_name:loadout}
                            except KeyError:
                                loadouts_dict[armament] = {aircraft:{simple_loadout_name:loadout}}
                        done_loadout.append(platform_setup)
        for platform_setup in aircraft_dict[aircraft]:
            if platform_setup != '' and not platform_setup.isspace() and platform_setup not in done_loadout:
                simple_loadout_name = aircraft_dict[aircraft][platform_setup]
                proceed = True
                if filter:
                    if simple_loadout_name not in filter_list:
                        proceed = False
                if proceed:
                    loadout = load_dict[platform_setup]
                    try:
                        loadouts_dict['Unknown'][aircraft][simple_loadout_name] = loadout
                    except KeyError:
                        try:
                            loadouts_dict['Unknown'][aircraft] = {simple_loadout_name:loadout}
                        except KeyError:
                            loadouts_dict['Unknown'] = {aircraft:{simple_loadout_name:loadout}}
    
    ###debut output only
#    debug.write('\n\n')
#    for aircraft in loadouts_dict:
#        debug.write('%s\n' % aircraft)
#        for armament in loadouts_dict[aircraft]:
#            debug.write('  %s\n' % armament)
#            for loadout in loadouts_dict[aircraft][armament]:
#                debug.write('    %s\n' % loadout)
#                for weapon in loadouts_dict[aircraft][armament][loadout]:
#                    debug.write('      %s   %s\n' % (weapon, loadouts_dict[aircraft][armament][loadout][weapon]))
    #dict{
        #armament{
                    #aircraft{
                    #           #setup{
                    #           #        #item{qty}
                    #           #        #item{qty}
                    #           #        #item{qty}
                    #           #        #item{qty}
                    #           #setup{
                    #                    #item{qty}
                    #                    #item{qty}
                    #                    #item{qty}
                    #                    #item{qty}
                    #aircraft{
                                #setup{
                                #        #item{qty}
                                #        #item{qty}
                                #        #item{qty}
                                #        #item{qty}
                                #setup{
                                         #item{qty}
                                         #item{qty}
                                         #item{qty}
                                         #item{qty}
     
    return loadouts_dict
#
#
#    
def DateString_DecimalYear(string):
    """
    DateString_DecimalYear(string):
    A simple function to convert a text date value into a float year value.
    YYYY/MM/DD in, YYYY.yyy out.
    """
    #string formatted as YYYY/MM/DD
    import re
    date_time = re.split('\D+', string)
    #convert the date into a decimal year:
    import datetime
    date = datetime.datetime(int(date_time[0]),int(date_time[1]),int(date_time[2]))
    dec_date = (float(date.strftime("%j"))-1) / 366 + float(date.strftime("%Y"))
    return dec_date
 
def has_target_flag(flag, val):
    while flag > 0:
        if flag ==  val:
            return True
        elif flag < val:
            return False
        else:
            if flag >= 16:
                flag -= 16
            elif flag >= 8:
                flag -= 8
            elif flag >= 4:
                flag -= 4
            elif flag >= 2:
                flag -= 2
            elif flag >= 1:
                flag -= 1
    return False