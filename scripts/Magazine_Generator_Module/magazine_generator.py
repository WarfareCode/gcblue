import csv, os
from os.path import dirname, abspath, join, normpath
from Weapon_Stock_Rates import *
from Amram_Utilities import *
from service_period import *

def MagLoadData():
    """
    MagLoadData():
    Reads in most of the database in csv format to provide the data necessary to generate stock for empty magazines.
    """
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
                if 'DatabaseClass' not in row[0]:
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
                    elif key == 'magazines':
                        data_dict[key][name][row[2]] = row[1]
                    else:
                        #only add to the data_dict if its something I can't retrieve directly with UI.QueryDatabase().
                        pass
    return data_dict

def TrimData(data_dict):
    """
    TrimData(data_dict):
    reforms the raw dictionary into a set of dictionaries(air, item, unit) containing only information relevant to them.
    Returns the three dictionaries.
    """
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
    unit_list = sorted(data_dict['ship'].keys() + data_dict['ground'].keys())
    for unit in unit_list:
        #associate magazines and setups.
        if unit in data_dict['ship'].keys():
            category = 'ship'
        else:
            category = 'ground'
        unit_dict[unit] = {}
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
                unit_dict[unit]['magazines'][magazine]['magname'] = magazine_name
                if classes == [''] or classes == []:
                    unlimited.append(magazine)
                else:
                    limited.append(magazine)
            unit_dict[unit]['magazines']['limited_mags'] = limited
            unit_dict[unit]['magazines']['unlimited_mags'] = unlimited
                
    return item_dict, unit_dict

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

def Get_Aircraft_Weapon_Stocks(UI, aircraft, airwing, item_dict, current_year):
    """
    Get_Aircraft_Weapon_Stocks(aircraft, airwing, item_dict, current_year):
    Iterates over loadouts an aircraft possesses, and returns the complete list
    of items this aircraft can use, filtered for the current date.
    """
    aircraft_weapon_list = {}
    designation = airwing[aircraft]['designation']
    for launcher in airwing[aircraft]['launchers']:
        for item in airwing[aircraft]['launchers'][launcher]:
            if '*' in item:
                #its a wildcard!
                items = expand_wildcard(item, item_dict)
            else:
                items = [item]
            for item2 in items:
                if item2 in role_ratios:
                    role_ratio = role_ratios[item2][designation]
                else:
                    role_ratio = 0
                if role_ratio > 0:
                    qty = float(airwing[aircraft]['launchers'][launcher][item])
                    item_mass = float(UI.QueryDatabase(determine_item_table(UI, item),item,'Weight_kg').GetString(0))
                    item_qty = role_ratio * qty
                    item_mass = item_mass * item_qty
                    if item2 in aircraft_weapon_list:
                        aircraft_weapon_list[item2] += item_qty
                    else:
                        aircraft_weapon_list[item2] = item_qty
                else:
                    aircraft_weapon_list[item2] = 0
    return aircraft_weapon_list

def determine_item_table(UI, item):
    if UI.QueryDatabase('missile',item,'ModelClassId').GetString(0) != 'Error':
        #its a missile
        return 'missile'
    elif UI.QueryDatabase('ballistic',item,'ModelClassId').GetString(0) != 'Error':
        #its a ballistic
        return 'ballistic'
    elif UI.QueryDatabase('torpedo',item,'ModelClassId').GetString(0) != 'Error':
        #its a torpedo
        return 'torpedo'
    elif UI.QueryDatabase('fueltank',item,'ModelClassId').GetString(0) != 'Error':
        #its a fueltank
        return 'fueltank'
    elif UI.QueryDatabase('sonobuoy',item,'ModelClassId').GetString(0) != 'Error':
        #its a sonobuoy
        return 'sonobuoy'
    elif UI.QueryDatabase('cm',item,'ModelClassId').GetString(0) != 'Error':
        #its a cm
        return 'cm'
    elif UI.QueryDatabase('ballistic_missile',item,'ModelClassId').GetString(0) != 'Error':
        #its a ballistic missile
        return 'ballistic_missile'
    elif UI.QueryDatabase('item',item,'ModelClassId').GetString(0) != 'Error':
        #its an item
        return 'item'

def determine_unit_table(UI, unit):
    if UI.QueryDatabase('air',item,'ModelClassId').GetString(0) != 'Error':
        #its a complex air
        return 'air'
    elif UI.QueryDatabase('ground',item,'ModelClassId').GetString(0) != 'Error':
        #its a ground
        return 'ground'
    elif UI.QueryDatabase('ship',item,'ModelClassId').GetString(0) != 'Error':
        #its a ship
        return 'ship'
    elif UI.QueryDatabase('simpleair',item,'ModelClassId').GetString(0) != 'Error':
        #its a simple air
        return 'simpleair'
    elif UI.QueryDatabase('sub',item,'ModelClassId').GetString(0) != 'Error':
        #its a sub
        return 'sub'

def check_limits(UI, stocks):
    """
    check_limits(item_dict, stocks):
    totals and returns the total quantity of items, and the total mass of those items.
    """
    mass = 0
    qty = 0
    if type(stocks) == type({}):
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
                    table = determine_item_table(UI, item)
                    item_mass = float(UI.QueryDatabase(table,item,'Weight_kg').GetString(0))
                mass += item_mass * item_qty
    else:
        for line in stocks:
            item = line[1]
            item_qty = int(line[2])
            if item_qty < 1:
                item_qty = 1
            else:
                item_qty = int(item_qty)
            qty += item_qty
            if item == 'Fuel':
                item_mass = 1.0
            else:
                table = determine_item_table(UI, item)
                item_mass = float(UI.QueryDatabase(table,item,'Weight_kg').GetString(0))
                mass += item_mass * item_qty
    return qty, mass

def Get_Weapon_Service_Mod(item, year, date1, date2):
    """
    Get_Weapon_Service_Mod(item, year, date1, date2):
    provides a multiplier for stock rates based upon the current year and weapon service period.
    
    Results in increased stock int he middile of a service period,
    dwindling stock at the end, and low stock at the beginning
    """
    if date2 >= year >= date1:
        #we're in service now
        mod1a = (year - date1 + 2) / 6  #entering service modifier
        mod1b = (date2 - year) / 4  #exiting service modifier
        mod2a = (year - date1) / 100
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

def Get_Own_Stock(UI, unit, unit_dict, data_dict, current_year, country):
    """
    Get_Own_Stock(unit, unit_dict, data_dict, current_year):
    determines an appropriate loadout, and the stock needed to reload it, returns the results.
    """
    table = determine_unit_table(UI, unit)
    #configure launcher loadout too based on this data.
    own_stock_list = {}
    loadout_entry = {}
    for launcher_num in unit_dict[unit]['launchers']:
        #iterate over the ships launchers
        launcher_name = data_dict['platform'][unit][launcher_num]['name']

        launcher_items = {}
        #get the launcher items and modify their qty by service date.
        for item in unit_dict[unit]['launchers'][launcher_num]:
            if country in servicekit:
                if item in servicekit[country]:
                    date1 = float(servicekit[country][item]['Entry'])
                    date2 = float(servicekit[country][item]['Exit'])
                    service_mod = Get_Weapon_Service_Mod(item, current_year, date1, date2)
                else:
                    service_mod = 0
            else:
                table = determine_item_table(UI, item)
                date1 = float(UI.QueryDatabase(table,item,'InitialYear').GetString(0))
                date2 = float(UI.QueryDatabase(table,item,'FinalYear').GetString(0))
                if table in ['fueltank', 'sonobuoy']:
                    service_mod = 1
                else:
                    service_mod = Get_Weapon_Service_Mod(item, current_year, date1, date2)        
        
            if not date1 > current_year and not date2 < current_year:
                qty = float(unit_dict[unit]['launchers'][launcher_num][item]) * service_mod
                launcher_items[item] = qty
        #keep the item with the highest stock value, load that.
        high_val = 0
        for item in launcher_items:
            if launcher_items[item] > high_val:
                high_val = launcher_items[item]
                load_item = item

        #build reload stock list
        load_item_qty = float(unit_dict[unit]['launchers'][launcher_num][item])
        if launcher_name in unit_dict[unit]['launcher_count']:
            stock_lvl = {'torpedo':4,'ballistic':5,'missile':3}
            stock = stock_lvl.get(determine_item_table(UI, item),5)
            qty = load_item_qty * stock
            if load_item in own_stock_list:
                own_stock_list[load_item] += qty
            else:
                own_stock_list[load_item] = qty
        #build loadout list
        loadout_entry[launcher_num] = [load_item, load_item_qty]
    return own_stock_list, loadout_entry

def airwing_stock(UI, airwing, item_dict, current_year, data_dict, country):
    """
    airwing_stock(airwing, item_dict, current_year, data_dict, country):
    iterates over all the present aircraft, and compiles a list of all the items needed and their quantities.
    Returns the resulting dictionary.
    """
    airwing_stock = {}
    for aircraft in airwing:
        airwing_qty = airwing[aircraft]['count']
        aircraft_weapon_list = Get_Aircraft_Weapon_Stocks(UI, aircraft, airwing, item_dict, current_year)
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
                service_mod = Get_Weapon_Service_Mod(item, current_year, date1, date2)
            else:
                service_mod = 0
        else:
            table = determine_item_table(UI, item)
            date1 = float(UI.QueryDatabase(table,item,'InitialYear').GetString(0))
            date2 = float(UI.QueryDatabase(table,item,'FinalYear').GetString(0))
            if table in ['fueltank', 'sonobuoy']:
                service_mod = 1
            else:
                service_mod = Get_Weapon_Service_Mod(item, current_year, date1, date2)
        airwing_stock[item] *= service_mod
    return airwing_stock
    
def generate_airwing(UI, data_dict, item_dict):
    """
    generate_airwing(UI):
    itemises the present child aircraft for use in finding needed stocks.
    """
    airwing = {}
    FP = UI.GetFlightPortInfo()
    for n in xrange(FP.GetUnitCount()):
        UIn = FP.GetUnitPlatformInterface(n)
        name = UIn.GetPlatformClass()
        if name in airwing:
            airwing[name]['count'] += 1
        else:
            airwing[name] = {}
            airwing[name]['count'] = 1
            if UIn.HasThrottle():
                airwing[name]['date1'] = UI.QueryDatabase('air',name, 'InitialYear').GetString(0)
                airwing[name]['date2'] = UI.QueryDatabase('air',name, 'FinalYear').GetString(0)
                airwing[name]['fuelcap'] = UI.QueryDatabase('air',name, 'FuelCapacity_kg').GetString(0)
                airwing[name]['mass'] = UI.QueryDatabase('air',name, 'Weight_kg').GetString(0)
                airwing[name]['MTOW'] = UI.QueryDatabase('air',name, 'MaxTakeoffWeight_kg').GetString(0)
                airwing[name]['designation'] = UI.QueryDatabase('air',name, 'Designation').GetString(0)
            else:
                airwing[name]['date1'] = UI.QueryDatabase('simpleair',name, 'InitialYear').GetString(0)
                airwing[name]['date2'] = UI.QueryDatabase('simpleair',name, 'FinalYear').GetString(0)
                airwing[name]['fuelcap'] = UI.QueryDatabase('simpleair',name, 'FuelCapacity_kg').GetString(0)
                airwing[name]['mass'] = UI.QueryDatabase('simpleair',name, 'Weight_kg').GetString(0)
                airwing[name]['MTOW'] = UI.QueryDatabase('simpleair',name, 'MaxTakeoffWeight_kg').GetString(0)
                airwing[name]['designation'] = UI.QueryDatabase('simpleair',name, 'Designation').GetString(0)
            airwing[name]['payload'] = float(airwing[name]['MTOW']) - float(airwing[name]['mass']) - float(airwing[name]['fuelcap'])

            #replace dependence on data_dict with QueryDatabase when able to perform multi-line lookup
            if name in data_dict['platform']:
                airwing[name]['launchers'] = {}
                for launcher_num in data_dict['platform'][name]:
                    #iterate through relevant launcher names and append
                    launcher = data_dict['platform'][name][launcher_num]['name']
                    airwing[name]['launchers'][launcher_num] = {}
                    for item in data_dict['launchers'][launcher]:
                        #iterate through launcher names and append items
                        qty = data_dict['launchers'][launcher][item]
                        if '*' in item:
                            #wild card item, expand wildcard
                            wild_list = expand_wildcard(item, item_dict)
                            for wild_item in wild_list:
                                airwing[name]['launchers'][launcher_num][wild_item] = qty
                        else:
                            airwing[name]['launchers'][launcher_num][item] = qty
                    #functional to here, loads items just fine per launcher, assigning wrongly?
    return airwing
    
def GetMagClasses(UI, magname):
    class1 = UI.QueryDatabase('stores',magname,'Class1').GetString(0).split(';')
    class2 = UI.QueryDatabase('stores',magname,'Class2').GetString(0).split(';')
    class3 = UI.QueryDatabase('stores',magname,'Class3').GetString(0).split(';')
    class4 = UI.QueryDatabase('stores',magname,'Class4').GetString(0).split(';')
    classlist = []
    for itemlist in [class1, class2, class3, class4]:
        for item in itemlist:
            if item not in classlist and item != '':
                classlist.append(item)
    return classlist
    
def MagGenerator(UI, mag_date):
    """
    MagGenerator(UI, mag_date):
    Takes a date, and in return will load the launchers, and stock the magazines with date appropriate gear.
    
    This is not group capable, nothing prevents calling it from a group capable handler.
    Expects date in an unformatted YYYY/MM/DD string format.
    """
    BB = UI.GetBlackboardInterface()
    
    launcher_count = UI.GetLauncherCount()
    
    unit = UI.GetPlatformClass()
    data_dict = MagLoadData()
    item_dict, unit_dict = TrimData(data_dict)
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
    
    

    plat_setup = {}
        
    if UI.QueryDatabase('platform_magazine',unit,'MagazineClass').GetString(0) != 'Error':
        airwing = generate_airwing(UI, data_dict, item_dict)
        #get our country:
        if UI.IsSurface():
            country = UI.QueryDatabase('ship', unit, 'Country')
            country = country.GetString(0)
        elif UI.IsGroundVehicle() or UI.IsFixed():
            country = UI.QueryDatabase('ground', unit, 'Country')
            country = country.GetString(0)
        airwing_stock_list = airwing_stock(UI, airwing, item_dict, current_year, data_dict, country)
        if launcher_count > 0:
            own_stock_list, loadout_entry = Get_Own_Stock(UI, unit, unit_dict, data_dict, current_year, country)
        #split stock lists into magazine assignments.
        mag_assignments = {}
        assigned_items = []
        #limited magazine stock
        for mag in unit_dict[unit]['magazines']['limited_mags']:
            magname = unit_dict[unit]['magazines'][mag]['magname']
            classes = GetMagClasses(UI, magname)
            mag_assignments[mag] = {}
            mag_assignments[mag]['Max Items'] = UI.QueryDatabase('stores',magname,'Capacity').GetString(0)
            mag_assignments[mag]['Max Weight'] = UI.QueryDatabase('stores',magname,'MaxWeight_kg').GetString(0)
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
            magname = unit_dict[unit]['magazines'][mag]['magname']
            mag_assignments[mag] = {}
            if BB.KeyExists('MagTonnage'):
                mag_assignments[mag]['Max Weight'] = set_mag_tonnage
            else:
                mag_assignments[mag]['Max Weight'] = UI.QueryDatabase('stores',magname,'Capacity').GetString(0)
            if BB.KeyExists('MaxItems'):
                mag_assignments[mag]['Max Items'] = set_mag_items
            else:
                mag_assignments[mag]['Max Items'] = UI.QueryDatabase('stores',magname,'MaxWeight_kg').GetString(0)
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
            mag_items, mag_weight = check_limits(UI, mag_assignments[mag]['items'])
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
                if determine_item_table(UI, item) in ['sonobuoy', 'fueltank']:
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
        
        #set magazine
        for line in sorted(mag_loads):
            Mnum = int(line[0])
            item = line[1]
            qty = int(line[2])
            UI.AddItemToMagazine(item, qty)
        
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
        plat_setup['launcher_content'] = loads

        #set loadout 
        for line in sorted(loads):
            Lnum = int(line[0])
            item = line[1]
            UI.LoadLauncher(Lnum, item)
    
    UI.DisplayMessage('%0.1f tons of munitions provided to %d %s (%s)' % (check_limits(UI, mag_loads)[1]/1000, UI.GetPlatformId(), UI.GetPlatformName(), unit))
