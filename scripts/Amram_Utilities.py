#relocating my utility scripts.  i'm beginning to have a few of them, and would like to try and avoid having to constantly refer back and forth between my files, and overgrow my core files.
import sys, os, math, re, datetime
from os.path import dirname, abspath, join, normpath
sys.path.append(abspath(join(dirname(__file__), '..', 'bin', 'lib')))
from UnitCommands import *
import json, csv 


#once I can step fully away from 1.25, I can proceed with eliminating most of the input handlers, the option handler ~can~ do it, if it can take string params.

def flatten(xs):
    """
    flatten(xs):
    expand_wildcard causes lists to become nested lists.  Flatten() flattens them again.
    """
    res = []
    def loop(ys):
        for i in ys:
            if isinstance(i, list):
                loop(i)
            else:
                res.append(i)
    loop(xs)
    return res

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
    elif method == 'DictSet':
        temp_dict = Read_Message_Dict(BB, variable)
        key_val = [float(x) for x in value.split('~')]
        temp_dict[key_val[0]] = key_val[1]
        Write_Message_List(BB, temp_dict, variable)
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
                BB.WriteGlobal('Cruise_Speed_Only','1')
                AddTask(UI,'CruiseEnforcement', 5,-1)
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
            UI.DeleteNavWaypoint(idx)
    else:
        UI = interface
        UI.DeleteNavWaypoint(idx)

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
        
def determine_item_table(UI, item):
    if UI.QueryDatabase('missile',item,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a missile
        return 'missile'
    elif UI.QueryDatabase('ballistic',item,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a ballistic
        return 'ballistic'
    elif UI.QueryDatabase('torpedo',item,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a torpedo
        return 'torpedo'
    elif UI.QueryDatabase('fueltank',item,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a fueltank
        return 'fueltank'
    elif UI.QueryDatabase('sonobuoy',item,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a sonobuoy
        return 'sonobuoy'
    elif UI.QueryDatabase('cm',item,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a cm
        return 'cm'
    elif UI.QueryDatabase('ballistic_missile',item,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a ballistic missile
        return 'ballistic_missile'
    elif UI.QueryDatabase('item',item,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its an item
        return 'item'

def determine_unit_table(UI, unit):
    if UI.QueryDatabase('air',unit,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a complex air
        return 'air'
    elif UI.QueryDatabase('ground',unit,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a ground
        return 'ground'
    elif UI.QueryDatabase('ship',unit,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a ship
        return 'ship'
    elif UI.QueryDatabase('simpleair',unit,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a simple air
        return 'simpleair'
    elif UI.QueryDatabase('sub',unit,'ModelClassId').GetRow(0).GetString(0) != 'Error':
        #its a sub
        return 'sub'

def queryDB(UI, table, name, fields):
    """
    queryDB(UI, table, name, fields, additive = False)
    a wrapper for UI.QueryDatabase()
    it will return a string if only one item is found, or a dict if multiple are found.
    the first field will be used as the dictionary key.
    The values will be strings, unless there were more than two fields.
    """
    array = UI.QueryDatabase(table, name, fields)
    if array.Size() == 1 and ',' not in fields:
        return array.GetRow(0).GetString(0)
    else:
        info = {}
        for x in xrange(array.Size()):
            row = array.GetRow(x)
            field_count = row.Size()
            if field_count == 1:
                info[row.GetString(0)] = ''
            elif field_count == 2:
                key = row.GetString(0)
                if key in info:
                    try:
                        info[key] += float(row.GetString(1))
                    except:
                        info[key] = row.GetString(1)
                else:
                    try:
                        info[key] = float(row.GetString(1))
                    except:
                        info[key] = row.GetString(1)
            elif field_count > 2:
                field_info = []
                for y in xrange(row.Size()):
                    field_info.append(row.GetString(y))
                title = field_info.pop(0)
                info[title] = field_info
        return info

def get_compatible_items(UI):
    """
    get_compatible_items(UI)
    returns a list of all valid items for the platform belonging to the given UI, 
    this is not date filtered but contains the info needed to filter it further.
    """
    launchers = queryDB(UI, 'platform_launcher', UI.GetPlatformClass(), 'LauncherId, LauncherClass, IsReloadable')
    
    #reform it into just what info I sought from it.
    
    #iterate over the launchers, and get a list of all items, expand wildcards as encountered
    compatible_items = {}
    for launcher in launchers:
        launcher_class = launchers[launcher][0]
        items = queryDB(UI, 'launcher_configuration', launcher_class, 'ChildClass, ChildCapacity')
        for x in items:
            item = items[x][0]
            qty = float(items[x][1])
            if '*' in item:
                #wildcard
                wild_names.append(item)
                wild_list = expand_wildcard(item, Wild_Items)
            else:
                wild_list = [item]
            for item in wild_list:
                if qty > 0:
                    try:
                        compatible_items[item] += qty
                    except KeyError:
                        compatible_items[item] = qty
    return compatible_items
    
def get_loadouts(UI, tgt_names, filter, filter_list):
    """
    get_loadouts(tgt_names, filter, filter_list)
    a QueryDatabase version of my loadouts listing, eliminates the need for external csv.
    filter is a boolean toggle for date restricting the loadouts.
    """
    loadouts_dict = {}
    #armament names.
    menu_list = [ 
        [1, 'AW', 'AAW', 2], 
        [2, 'GM', 'AGM', 2], 
        [3, 'SM', 'ASM', 2], 
        [4, 'IB', 'Bombs', 2], 
        [5, 'GB', 'Guided Bombs', 2], 
        [6, 'UR', 'Rockets', 2], 
        [7, 'T', 'Torpedoes', 1], 
        [8, ['N', 'X'], 'Nuclear', 1], 
        [9, 'SD', 'Anti Radar', 2], 
        [10, 'CS', 'Close Support', 2]]
    for item in menu_list:
        identifier = item[1]
        category = item[2]
        offset = item[3]
        for unit in tgt_names:
            loadouts = queryDB(UI, 'platform_setup', unit, 'SetupName, LauncherLoadout')
            for setup_name in loadouts:
                if (filter and setup_name in filter_list.keys()) or not filter:
                    if setup_name[:offset] in identifier:
                        if loadouts[setup_name] != 'Error':
                            #this loadout belongs to this category.
                            loadout_items = queryDB(UI, 'launcher_loadout', loadouts[setup_name], 'Item, Quantity')
                            if loadout_items.keys() != ['Error']:
                                try:
                                    loadouts_dict[category][unit][setup_name] += loadout_items
                                except KeyError:
                                    try:
                                        loadouts_dict[category][unit][setup_name] = loadout_items
                                    except KeyError:
                                        try:
                                            loadouts_dict[category][unit] = {setup_name:loadout_items}
                                        except KeyError:
                                            loadouts_dict[category] = {unit:{setup_name:loadout_items}}

    return loadouts_dict
    #dict{
        #category{
                    #unit{
                            #setup{
                                    #item{qty}
                                    #item{qty}
    
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

def modification_date(filename):
    t = os.path.getctime(filename)
    t = datetime.datetime.fromtimestamp(t)
    t = t.strftime("%y/%m/%d %H:%M:%S")
    return t
        
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
    
def expand_wildcard(wildstring, items):
    """
    expand_wildcard(wild, item_dict):
    takes a wildcard entry, and iterates over the entire list of possible
    items to find all of the items for which it may stand.
    """
    if type(items) == type([]) or type(items) == type(()):
        #already an iterable list/tuple
        stringlist = items
    elif type(items) == type({}):
        #its a dict
        stringlist = items.keys()
    searchstring = ''
    for character in wildstring:
        if character == '*':
            searchstring += '[A-Za-z0-9_]*'
        else:
            searchstring += character
    wildcard_items = []
    if type(items) == type(''):
        #we only got a string, so test if that string is a match
        return re.match(searchstring, items)
    else:
        #we got a list, return all matches found.
        for item in stringlist:
            if re.match(searchstring, item):
                wildcard_items.append(item)
        return wildcard_items
        
def CombatLimitsInputHandler(interface, input, param):
    input = ''.join([x for x in input if ord(x) < 128])
    if param < 12:
        params = {0:16,1:17,2:18,3:22,4:32,5:33,6:34,7:64,8:129,9:256,10:258,11:257}
        OptionHandler(interface, '%s_EngageLimit|Set|%s' % (params[param],input))
    elif param is 12:
        #group function
        GI = interface
        for n in xrange(GI.GetUnitCount()):
            UI = GI.GetPlatformInterface(n)
            BB = UI.GetBlackboardInterface()
            target = UI.GetTarget()
            temp_dict = Read_Message_Dict(BB, 'ID_EngageLimit')
            temp_dict[target] = input
            Write_Message_List(BB, temp_dict, 'ID_EngageLimit')
    elif param is 13:
        #individual function
        UI = interface
        BB = UI.GetBlackboardInterface()
        target = UI.GetTarget()
        temp_dict = Read_Message_Dict(BB, 'ID_EngageLimit')
        temp_dict[target] = input
        Write_Message_List(BB, temp_dict, 'ID_EngageLimit')
    BB.WriteGlobal('UseOwnRules','')

def IdEngageLimitHandler(interface,limit):
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
    if group:
        GI = interface
        for n in xrange(GI.GetUnitCount()):
            UI = GI.GetPlatformInterface(n)
            track = UI.GetTargetTrackInfo()
            id = track.ID
            OptionHandler(interface, 'ID_EngageLimit|DictSet|%s~%s' % (ID,limit))
    else:
            UI = interface
            track = UI.GetTargetTrackInfo()
            id = track.ID
            OptionHandler(interface, 'ID_EngageLimit|DictSet|%s~%s' % (ID,limit))
    BB.WriteGlobal('UseOwnRules','')
            
def CoOrdsEngageLimitHandler(interface,*params):
    param = params[-1]
    params = params[0],params[1],params[2],params[3]

    if param is 1:
        #Box, Include
        include = True
    elif param is 2:
        #Box, Exclude
        include = False

    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
    if group:
        GI = interface
        for n in xrange(GI.GetUnitCount()):
            UI = GI.GetPlatformInterface(n)
            BB = UI.GetBlackboardInterface()
            engage_zones = Read_Message_Dict(BB, 'Engagement_Zones')
            taken_keys = []
            x = ['Include','Exclude']
            for set in x:
                if set in engage_zones:
                    for key in engage_zones[set]:
                        taken_keys.append(int(float(str(key))))
            for n in xrange(1000):
                if n not in taken_keys:
                    try:
                        if include:
                            engage_zones['Include'][n] = params
                            break
                        else:
                            engage_zones['Exclude'][n] = params
                            break
                    except KeyError:
                        if include:
                            engage_zones['Include'] = {n:params}
                            break
                        else:
                            engage_zones['Exclude'] = {n:params}
                            break
            Write_Message_List(BB, 'Engagement_Zones', engage_zones)
    else:
        UI = interface
        BB = UI.GetBlackboardInterface()
        engage_zones = Read_Message_Dict(BB, 'Engagement_Zones')
        taken_keys = []
        x = ['Include','Exclude']
        for set in x:
            if set in engage_zones:
                for key in engage_zones[set]:
                    taken_keys.append(int(float(str(key))))
        for n in xrange(1000):
            if n not in taken_keys:
                try:
                    if include:
                        engage_zones['Include'][n] = params
                        break
                    else:
                        engage_zones['Exclude'][n] = params
                        break
                except KeyError:
                    if include:
                        engage_zones['Include'] = {n:params}
                        break
                    else:
                        engage_zones['Exclude'] = {n:params}
                        break
        Write_Message_List(BB, 'Engagement_Zones', engage_zones)
    BB.WriteGlobal('UseOwnRules','')

def DefaultCombatLimitInputs(interface, param):
    #used to zero out various combat targeting limitations.
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
        
    if param in ['EngageLimits','All']:
        for num in [16,17,18,22,32,33,34,64,129,256,258,257]:  #unit classification id's
            limit = {32:1,33:1,34:1,256:2,258:2,257:24,64:1,16:4,17:6,18:12,22:24,129:1}
            OptionHandler(interface, '%s_EngageLimit|Set|%s' % (num,limit[num]))
    if param in ['IdLimits','All']:
        if group:
            GI = interface
            for n in xrange(GI.GetUnitCount()):
                UI = GI.GetPlatformInterface(n)
                BB = UI.GetBlackboardInterface()
                newdict = {}
                Write_Message_List(BB,'ID_EngageLimit',newdict)
        else:
                UI = interface
                BB = UI.GetBlackboardInterface()
                newdict = {}
                Write_Message_List(BB,'ID_EngageLimit',newdict)
    if param in ['Zones','All']:
        if group:
            GI = interface
            for n in xrange(GI.GetUnitCount()):
                UI = GI.GetPlatformInterface(n)
                BB = UI.GetBlackboardInterface()
                newdict = {}
                Write_Message_List(BB,'Engagement_Zones',newdict)
        else:
                UI = interface
                BB = UI.GetBlackboardInterface()
                newdict = {}
                Write_Message_List(BB,'Engagement_Zones',newdict)
    BB.WriteGlobal('UseOwnRules','')
        
def classify_item(UI, item):
    if UI.QueryDatabase('torpedo',item,'ClassificationId').GetRow(0).GetString(0) == '130':  #torpedo
        return True, 'torpedo'
    elif UI.QueryDatabase('torpedo',item,'ClassificationId').GetRow(0).GetString(0) == '138':  #mine
        return True, 'torpedo'
    elif UI.QueryDatabase('missile',item,'ClassificationId').GetRow(0).GetString(0) == '64':  #missile
        return True, 'missile'
    elif UI.QueryDatabase('ballistic',item,'BallisticType').GetRow(0).GetString(0) != 'Error':
        return True, 'ballistic'
    elif UI.QueryDatabase('cm',item,'ClassificationId').GetRow(0).GetString(0) != 'Error':  #gun cm, air cm, water cm
        return True, 'cm'
    elif UI.QueryDatabase('sonobuoy',item,'ClassificationId').GetRow(0).GetString(0) != 'Error':
        return True, 'sonobuoy'
    elif UI.QueryDatabase('fueltank',item,'ClassificationId').GetRow(0).GetString(0) != 'Error':
        return True, 'fueltank'
    else:
        return False, ''


