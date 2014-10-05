import csv, os
from os.path import dirname, abspath, join, normpath
from Weapon_Stock_Rates import *
from Amram_Utilities import *
from service_period import *

def MagLoadData():
    #load our files in
    path = 'scripts/Amram_Script_Data/CSVs/'
    
    air_path                = path + 'air.csv'
    simpleair_path          = path + 'simpleair.csv'
    launcher_config_path    = path + 'launcher_configuration.csv'
    platform_path           = path + 'platform_launcher.csv'
    ballistic_path          = path + 'ballistic.csv'
    missile_path            = path + 'missile.csv'
    torpedo_path            = path + 'torpedo.csv'
    fueltank_path           = path + 'fueltank.csv'
    cms_path                = path + 'cm.csv'
    sonobuoy_path           = path + 'sonobuoy.csv'
    stores_path             = path + 'stores.csv'
    ship_path               = path + 'ship.csv'
    ground_path             = path + 'ground.csv'
    magazine_path           = path + 'platform_magazine.csv'
    stores_path             = path + 'stores.csv'
    

    
    files_dict = {'air':[air_path,simpleair_path],'platform':[platform_path],'launchers':[launcher_config_path],'ballistic':[ballistic_path],'missile':[missile_path],'torpedo':[torpedo_path],
                  'fueltank':[fueltank_path],'cms':[cms_path],'sonobuoy':[sonobuoy_path],'stores':[stores_path],'ship':[ship_path],'magazines':[magazine_path],'ground':[ground_path]}
    #read in the files, and compose dictionaries.
    
    data_dict = {}
    for key in files_dict:
        data_dict[key] = {}
        path_list = files_dict[key]
        for path in path_list:
            file_path = normpath(join(os.getcwd(), path))
            datafile = open(file_path, 'r')
            datareader = csv.reader(datafile)
            for row in datareader:
                #reading in the file, now we pluck our data to keep what we want, and build out result dictionaries
                if row[0] != 'DatabaseClass text primary key' and row[0] != 'DatabaseClass text':
                    name = row[0]
                    try:
                        test = data_dict[key][name]
                    except:
                        data_dict[key][name] = {}
                    if key == 'platform':
                        data_dict[key][name][row[2]] = {}
                        data_dict[key][name][row[2]]['name'] = row[1]
                        data_dict[key][name][row[2]]['reloadable'] = row[10]
                    elif key == 'launchers':
                        #launcher config
                        data_dict[key][name][row[1]] = row[2]
                    elif key == 'air':
                        data_dict[key][name]['mass'] = row[5]
                        try:
                            date1 = float(row[12])
                        except:
                            #simple air
                            date1 = float(row[7])
                        try:
                            date2 = float(row[13])
                        except:
                            #simple air
                            date2 = float(row[8])
                        data_dict[key][name]['date1'] = date1
                        data_dict[key][name]['date2'] = date2
                        if len(row) == 46:
                            data_dict[key][name]['designation'] = row[10]
                        else:
                            data_dict[key][name]['designation'] = row[15]
                        data_dict[key][name]['fuelcap'] = row[19]
                        data_dict[key][name]['mass2'] = row[35]
                    elif key == 'fueltank':
                        #data_dict[key][name]['mass'] = float(row[5]) + float(row[16])
                        data_dict[key][name]['mass'] = float(row[5])
                        data_dict[key][name]['date1'] = row[7]
                        data_dict[key][name]['date2'] = row[8]
                    elif key == 'cms' or key == 'sonobuoy':
                        data_dict[key][name]['mass'] = row[5]
                        data_dict[key][name]['date1'] = row[7]
                        data_dict[key][name]['date2'] = row[8]
                    elif key == 'stores':
                        data_dict[key][name]['Max Weight'] = row[19]
                        data_dict[key][name]['Max Volume'] = row[18]
                        data_dict[key][name]['Max Items'] = row[17]
                        class1 = row[21].split(';')
                        class2 = row[22].split(';')
                        class3 = row[23].split(';')
                        class4 = row[24].split(';')
                        classlist = []
                        for itemlist in [class1, class2, class3, class4]:
                            for item in itemlist:
                                if item not in classlist and item != '':
                                    classlist.append(item)
                        data_dict[key][name]['classes'] = classlist
                    elif key == 'ship':
                        data_dict[key][name]['date1'] = row[7]
                        data_dict[key][name]['date2'] = row[8]
                    elif key == 'ground':
                        data_dict[key][name]['date1'] = row[7]
                        data_dict[key][name]['date2'] = row[8]
                    elif key == 'magazines':
                        data_dict[key][name][row[2]] = row[1]
                    else:
                        data_dict[key][name]['mass'] = row[5]
                        data_dict[key][name]['date1'] = row[7]
                        data_dict[key][name]['date2'] = row[8]
                        data_dict[key][name]['mass2'] = row[35]
    return data_dict

def TrimData(data_dict):
    #trim by exclusion, simply put, read the relevant data, and form a new dict
    #read the dict to get the aircraft names.
    #associate the launcher names
    air_dict = {}
    item_dict = {}
    unit_dict = {}
    for key in data_dict:
        if key in ['missile','ballistic','ballistic_missile','torpedo','cms','items', 'fueltank', 'sonobuoy']:
            for subkey in data_dict[key]:
                item_dict[subkey] = data_dict[key][subkey]
    for aircraft in sorted(data_dict['air'].keys()):
        #iterate through aircraft, append data
        air_dict[aircraft] = {}
        air_dict[aircraft]['date1'] = data_dict['air'][aircraft]['date1']
        air_dict[aircraft]['date2'] = data_dict['air'][aircraft]['date2']
        air_dict[aircraft]['designation'] = data_dict['air'][aircraft]['designation']
        payload = float(data_dict['air'][aircraft]['mass2']) - float(data_dict['air'][aircraft]['mass']) - float(data_dict['air'][aircraft]['fuelcap'])
        air_dict[aircraft]['payload'] = payload
        if aircraft in data_dict['platform']:
            for launcher_num in data_dict['platform'][aircraft]:
                #iterate through relevant launcher names and append
                launcher = data_dict['platform'][aircraft][launcher_num]['name']
                air_dict[aircraft][launcher_num] = {}
                for item in data_dict['launchers'][launcher]:
                    #iterate through launcher names and append items
                    if '*' in item:
                        #wild card item, expand wildcard
                        wild_list = expand_wildcard(item, item_dict)
                        qty = data_dict['launchers'][launcher][item]
                        for wild_item in wild_list:
                            air_dict[aircraft][launcher_num][wild_item] = qty
                    else:
                        qty = data_dict['launchers'][launcher][item]
                        air_dict[aircraft][launcher_num][item] = qty
    unit_list = sorted(data_dict['ship'].keys() + data_dict['ground'].keys())
    for unit in unit_list:
        #associate magazines and setups.
        if unit in data_dict['ship'].keys():
            category = 'ship'
        else:
            category = 'ground'
        unit_dict[unit] = {}
        unit_dict[unit]['date1'] = data_dict[category][unit]['date1']
        unit_dict[unit]['date2'] = data_dict[category][unit]['date2']
        unit_dict[unit]['setup'] = {}
        unit_dict[unit]['launchers'] = {}
        unit_dict[unit]['launcher_count'] = {}
        if unit in data_dict['platform']:
            for launcher_num in data_dict['platform'][unit]:
                launcher = data_dict['platform'][unit][launcher_num]['name']
                launcher_reloadable = data_dict['platform'][unit][launcher_num]['reloadable']
                if launcher_reloadable:
                    if launcher in unit_dict[unit]['launcher_count']:
                        unit_dict[unit]['launcher_count'][launcher] += 1
                    else:
                        unit_dict[unit]['launcher_count'][launcher] = 1
                unit_dict[unit]['launchers'][launcher_num] = data_dict['launchers'][launcher]
            
        unit_dict[unit]['magazines'] = {}
        limited = []
        unlimited = []
        if unit in data_dict['magazines']:
            for magazine in data_dict['magazines'][unit]:
                magazine_name = data_dict['magazines'][unit][magazine]
                unit_dict[unit]['magazines'][magazine] = {}
                classes = data_dict['stores'][magazine_name]['classes']
                unit_dict[unit]['magazines'][magazine]['classes'] = classes
                unit_dict[unit]['magazines'][magazine]['Max Weight'] = data_dict['stores'][magazine_name]['Max Weight']
                unit_dict[unit]['magazines'][magazine]['Max Items'] = data_dict['stores'][magazine_name]['Max Items']
                if classes == [''] or classes == []:
                    unlimited.append(magazine)
                else:
                    limited.append(magazine)
            unit_dict[unit]['magazines']['limited_mags'] = limited
            unit_dict[unit]['magazines']['unlimited_mags'] = unlimited
                
    return air_dict, item_dict, unit_dict

def get_aircraft_date_compatible_items(air_data, item_dict):
    date1 = air_data['date1'] #start date
    date2 = air_data['date2'] #end date
    
    valid_item_dict = {}
    for item in item_dict:
        item_date1 = item_dict[item]['date1']
        item_date2 = item_dict[item]['date2']
        if date2 > item_date1 or date1 < item_date2:
            valid_item_dict[item] = item_dict[item]
    item_list = []
    for launcher in air_data:
        if launcher not in ['date1', 'date2', 'payload']:
            for item in air_data[launcher]:
                if item not in item_list:
                    item_list.append(item)
    compliant_item_dict = {}
    for item in item_list:
        if item in valid_item_dict:
            compliant_item_dict[item] = valid_item_dict[item]
    return compliant_item_dict

def expand_wildcard(wild, item_dict):
    #strip the wildcard character out
    wild2 = ''
    for char in wild:
        if char != '*':
            wild2+=char
    wild = wild2
    item_list = item_dict.keys()
    wildcard_items = []
    for item in item_list:
        if wild in item:
            wildcard_items.append(item)
    return wildcard_items

def flatten(xs):
    res = []
    def loop(ys):
        for i in ys:
            if isinstance(i, list):
                loop(i)
            else:
                res.append(i)
    loop(xs)
    return res

def Get_Aircraft_Weapon_Stocks(aircraft, air_dict, item_dict, current_year, data_dict):
    air_data = air_dict[aircraft]
    aircraft_weapon_list = {}
    designation = air_dict[aircraft]['designation']
    for entry in air_data:
        if entry not in ['date1', 'date2', 'payload', 'designation']:
            for item in air_data[entry]:
                if '*' in item:
                    #its a wildcard!
                    items = expand_wildcard(item, item_dict)
                else:
                    items = [item]
                for item2 in items:
                    item_date1 = float(item_dict[item2]['date1'])
                    item_date2 = float(item_dict[item2]['date2'])
                    if item2 in role_ratios:
                        role_ratio = role_ratios[item2][designation]
                    else:
                        role_ratio = 0
                    if role_ratio > 0:
                        if not item_date1 > current_year and not item_date2 < current_year:
                            qty = float(air_data[entry][item2])
                            item_mass = float(item_dict[item2]['mass'])
                            item_qty = role_ratio * qty
                            item_mass = item_mass * item_qty
                            if item2 in aircraft_weapon_list:
                                aircraft_weapon_list[item2] += item_qty
                            else:
                                aircraft_weapon_list[item2] = item_qty
    return aircraft_weapon_list

def check_limits(item_dict, stocks):
    mass = 0
    qty = 0
    for item in stocks:
        if item != 'mass':
            item_qty = float(stocks[item])
            if item_qty < 1:
                item_qty = 1
            else:
                item_qty = int(item_qty)
            qty += item_qty
            if item == 'Fuel':
                item_mass = 1.0
            else:
                item_mass = float(item_dict[item]['mass'])
            mass += item_mass * item_qty
    return qty, mass

def Get_Weapon_Service_Mod(item, item_dict, year, date1, date2):
    if year >= item_date1:
        #we're in service now
        mod1a = (year - item_date1 + 2) / 6  #entering service modifier
        mod1b = (item_date2 - year) / 4  #exiting service modifier
        mod2a = (year - item_date1) / 100
        mod2b = 0

        if mod1a > 0 and mod1a < mod1b:
            mod1 = mod1a
        elif mod1b > 0 and mod1a > mod1b:
            mod1 = mod1b
        else:
            mod1 = 0
        if mod1 > 1:
            mod1 = 1

        if mod2a > 0 and mod2a < 0.1:
            mod2 = mod2a
        elif mod2a >= 0.1:
            mod2 = 0.1
        else:
            mod2 = 0
        mod = mod1 + mod2
    else:
        mod = 0
    if mod < 0:
        mod = 0
    return mod

def Get_Own_Stock(unit, unit_dict, data_dict, item_dict, current_year):
    #configure launcher loadout too based on this data.
    own_stock_list = {}
    loadout_entry = {}
    for launcher_num in unit_dict[unit]['launchers']:
        #iterate over the ships launchers
        launcher_name = data_dict['platform'][unit][launcher_num]['name']
        if launcher_name in unit_dict[unit]['launcher_count']:
            reloadable = 1
        else:
            reloadable = 0

        launcher_items = {}
        #get the launcher items and modify their qty by service date.
        for item in unit_dict[unit]['launchers'][launcher_num]:
            item_date1 = float(item_dict[item]['date1'])
            item_date2 = float(item_dict[item]['date2'])
            if not item_date1 > current_year and not item_date2 < current_year:
                qty = float(unit_dict[unit]['launchers'][launcher_num][item]) * Get_Weapon_Service_Mod(item, item_dict, current_year)
                launcher_items[item] = qty
        #keep the item with the highest stock value, load that.
        high_val = 0
        for item in launcher_items:
            if launcher_items[item] > high_val:
                high_val = launcher_items[item]
                load_item = item

        #build reload stock list
        load_item_qty = float(unit_dict[unit]['launchers'][launcher_num][item])
        if reloadable:
            if load_item in data_dict['torpedo']:
                stock = 4
            elif load_item in data_dict['ballistic']:
                stock = 5
            elif load_item in data_dict['missile']:
                stock = 3
            else:
                stock = 5
            qty = load_item_qty * stock
            if load_item in own_stock_list:
                own_stock_list[load_item] += qty
            else:
                own_stock_list[load_item] = qty
                
        #build loadout list
        loadout_entry[launcher_num] = [load_item, load_item_qty]
    return own_stock_list, loadout_entry

def airwing_stock(airwing, unit, ship_dict, air_dict, item_dict, current_year, data_dict, country):
    airwing_stock = {}
    for aircraft in airwing:
        airwing_qty = airwing[aircraft]
        aircraft_weapon_list = Get_Aircraft_Weapon_Stocks(aircraft, air_dict, item_dict, current_year, data_dict)
        for item in aircraft_weapon_list:
            if item in airwing_stock:
                airwing_stock[item] += float(aircraft_weapon_list[item]) * airwing_qty
            else:
                airwing_stock[item] = float(aircraft_weapon_list[item]) * airwing_qty
    for item in airwing_stock:
        if country in servicekit:
            if item in servicekit[country]:
                date1 = float(servicekit[country][item]['Entry'])
                date2 = float(servicekit[country][item]['Exit'])
                service_mod = Get_Weapon_Service_Mod(item, item_dict, current_year, date1, date2)
            else:
                service_mod = 0
        else:
            date1 = float(item_dict[item]['date1'])
            date2 = float(item_dict[item]['date2'])
            service_mod = Get_Weapon_Service_Mod(item, item_dict, current_year, date1, date2)
        if 'buoy' in item or item in data_dict['fueltank']:
            service_mod = 1
        airwing_stock[item] = airwing_stock[item] * service_mod
    return airwing_stock
    
def generate_airwing(UI):
    airwing = {}
    FP = UI.GetFlightPortInfo()
    for n in xrange(FP.GetUnitCount()):
        UIn = FP.GetUnitPlatformInterface(n)
        name = UIn.GetPlatformClass()
        if name in airwing:
            airwing[name] += 1
        else:
            airwing[name] = 1
    return airwing
    
def MagGenerator(UI, mag_date):
    BB = UI.GetBlackboardInterface()
    
    launcher_count = UI.GetLauncherCount()
    
    data_dict = MagLoadData()
    air_dict, item_dict, unit_dict = TrimData(data_dict)
    current_year = DateString_DecimalYear(mag_date)
    set_mag_items = float(100000000000000000000)
    set_mag_tonnage = float(100000000000000000000)
    if BB.KeyExists('MagTonnage'):
        set_mag_tonnage = float(BB.ReadMessage('MagTonnage')) * 1000
        if UI.HasFlightPort():
            FP = UI.GetFlightPortInfo()
            set_mag_tonnage *= FP.GetUnitCount()
    elif BB.KeyExists('MagItems'):
        set_mag_items = float(BB.ReadMessage('MagItems'))
    elif not UI.IsSurface():
        #how did we even get here?
        return
    
    #get a ship to work on
    unit = UI.GetPlatformClass()
    
    has_magazine = False
    if unit in data_dict['magazines']:
        has_magazine = True

    plat_setups = {}
    plat_setups[unit] = {}
        
    if has_magazine:
        airwing = generate_airwing(UI)
        #get our country:
        if UI.IsSurface():
            country = UI.QueryDatabase('ship', unit, 'Country')
            country = country.GetString(0)
        elif UI.IsGroundVehicle() or UI.IsFixed():
            country = UI.QueryDatabase('ground', unit, 'Country')
            country = country.GetString(0)
        airwing_stock_list = airwing_stock(airwing, unit, unit_dict, air_dict, item_dict, current_year, data_dict, country)
        if launcher_count > 0:
            own_stock_list, loadout_entry = Get_Own_Stock(unit, unit_dict, data_dict, item_dict, current_year)
        #split stock lists into magazine assignments.
        mag_assignments = {}
        assigned_items = []
        #limited magazine stock
        for mag in unit_dict[unit]['magazines']['limited_mags']:
            classes = unit_dict[unit]['magazines'][mag]['classes']
            mag_assignments[mag] = {}
            mag_assignments[mag]['Max Items'] = unit_dict[unit]['magazines'][mag]['Max Items']
            mag_assignments[mag]['Max Weight'] = unit_dict[unit]['magazines'][mag]['Max Weight']
            mag_assignments[mag]['items'] = {}
            for item in airwing_stock_list:
                if item in classes:
                    #then we put it here.
                    mag_assignments[mag]['items'][item] = airwing_stock_list[item]
                    assigned_items.append(item)
            if launcher_count > 0:
                for item in own_stock_list:
                    if item in classes:
                        #then we put it here.
                        mag_assignments[mag]['items'][item] = own_stock_list[item]
                        assigned_items.append(item)
        #unlimited magazine stock
        for mag in unit_dict[unit]['magazines']['unlimited_mags']:
            mag_assignments[mag] = {}
            if BB.KeyExists('MaxTonnage'):
                mag_assignments[mag]['Max Weight'] = mag_tonnage
            else:
                mag_assignments[mag]['Max Weight'] = unit_dict[unit]['magazines'][mag]['Max Weight']
            if BB.KeyExists('MaxItems'):
                mag_assignments[mag]['Max Items'] = mag_items
            else:
                mag_assignments[mag]['Max Items'] = unit_dict[unit]['magazines'][mag]['Max Items']
            mag_assignments[mag]['items'] = {}
            for item in airwing_stock_list:
                if item not in assigned_items:
                    #then we put it here.
                    mag_assignments[mag]['items'][item] = airwing_stock_list[item]
            if launcher_count > 0:
                for item in own_stock_list:
                    if item not in assigned_items:
                        #then we put it here.
                        mag_assignments[mag]['items'][item] = own_stock_list[item]
        #stock assigned, check for over qty, or over weight
        mag_stock_mod = {}
        for mag in mag_assignments:
            mag_weight_limit = float(mag_assignments[mag]['Max Weight'])
            mag_item_limit = float(mag_assignments[mag]['Max Items'])
            mag_items, mag_weight = check_limits(item_dict, mag_assignments[mag]['items'])
            if mag_weight_limit == 0:
                #unrestricted, set it to something absurdly huge
                mag_weight_limit = float(1e20)
            if mag_item_limit == 0:
                #unrestricted, set it to something absurdly huge
                mag_item_limit = float(1e20)
            if mag_weight_limit > set_mag_tonnage and mag in unit_dict[unit]['magazines']['unlimited_mags']:
                mag_weight_limit = set_mag_tonnage
            if mag_item_limit > set_mag_items and mag in unit_dict[unit]['magazines']['unlimited_mags']:
                mag_item_limit = set_mag_items
            if mag_items > mag_item_limit:
                over_qty = True
            else:
                over_qty = False
            if mag_weight > mag_weight_limit:
                over_mass = True
            else:
                over_mass = False
                
            if min(abs(1- mag_weight / mag_weight_limit), abs(1- mag_items / mag_item_limit)) == abs(1- mag_items / mag_item_limit):
                #we're closest with item limit.
                limit_closest = 'items'
            else:
                limit_closest = 'mass'

            if not over_qty and not over_mass:
                if limit_closest == 'items':
                    #reduce by item qty
                    if mag_items == 0:
                        stock_mod = 0
                    else:
                        stock_mod = mag_item_limit / mag_items
                else:
                    #reduce by item mass
                    if mag_weight == 0:
                        stock_mod = 0
                    else:
                        stock_mod = (mag_weight_limit * 0.95) / mag_weight
            elif over_qty and over_mass:
                if limit_closest == 'mass':
                    #reduce by item qty
                    if mag_items == 0:
                        stock_mod = 0
                    else:
                        stock_mod = mag_item_limit / mag_items
                else:
                    #reduce by item mass
                    if mag_weight == 0:
                        stock_mod = 0
                    else:
                        stock_mod = (mag_weight_limit * 0.95) / mag_weight
            elif over_qty and not over_mass:
                if mag_items == 0:
                    stock_mod = 0
                else:
                    stock_mod = mag_item_limit / mag_items
            elif not over_qty and over_mass:
                if mag_weight == 0:
                    stock_mod = 0
                else:
                    stock_mod = (mag_weight_limit * 0.95) / mag_weight
            mag_stock_mod[mag] = stock_mod
   
        mag_loads = []
        #begin creating the magazine entry lines
        for mag_num in mag_assignments:
            stock_mod = mag_stock_mod[mag_num]
            
            for item in mag_assignments[mag_num]['items']:
                if item in data_dict['sonobuoy'] or item in data_dict['fueltank']:
                    item_qty = int(mag_assignments[mag_num]['items'][item])
                else:
                    item_qty = int(mag_assignments[mag_num]['items'][item] * stock_mod)
                if item_qty < 1:
                    item_qty = 0
                if launcher_count > 0:
                    if item in own_stock_list and item_qty < own_stock_list[item]:
                        item_qty = int(own_stock_list[item])
                if item_qty > 0:
                    mag_load = (mag_num, item, item_qty)
                    mag_loads.append(mag_load)
        plat_setups[unit]['mag_content'] = mag_loads
        
    elif launcher_count > 0:
        own_stock_list, loadout_entry = Get_Own_Stock(unit, unit_dict, data_dict, item_dict, current_year)
    else:
        #no magazine to store items, no launchers to configure either, wtf are we doing?  Terminate now.
        return

    loads = []
    if launcher_count > 0:
        for launcher_num in loadout_entry:
            item = loadout_entry[launcher_num][0]
            item_qty = loadout_entry[launcher_num][1]
            loadline = (launcher_num, item, item_qty)
            loads.append(loadline)
        plat_setups[unit]['launcher_content'] = loads

        #set loadout 
        for unit in sorted(plat_setups):
            loads = plat_setups[unit]['launcher_content']
            for line in sorted(loads):
                Lnum = int(line[0])
                item = line[1]
                UI.LoadLauncher(Lnum, item)
                
    if has_magazine:
        #set magazine
        for unit in sorted(plat_setups):
            name = UI.GetPlatformName()
            mag_contents = plat_setups[unit]['mag_content']
            for line in sorted(mag_contents):
                Mnum = int(line[0])
                item = line[1]
                qty = int(line[2])
                UI.AddItemToMagazine(item, qty)
                