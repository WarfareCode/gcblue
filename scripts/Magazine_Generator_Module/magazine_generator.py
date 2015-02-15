import csv, os
from os.path import dirname, abspath, join, normpath
from Weapon_Stock_Rates import *
from Amram_Utilities import *
from service_period import *
from wildcard_items_list import *


def Get_Aircraft_Weapon_Stocks(UI, aircraft, airwing, current_year):
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
                items = expand_wildcard(item, Wild_Items)
            else:
                items = [item]
            for item2 in items:
                role_ratio = stock_rate(UI, aircraft, item2)
                if role_ratio > 0:
                    qty = float(airwing[aircraft]['launchers'][launcher][item])
                    item_mass = float(UI.QueryDatabase(determine_item_table(UI, item2),item2,'Weight_kg').GetString(0))
                    item_qty = role_ratio * qty
                    item_mass = item_mass * item_qty
                    if item2 in aircraft_weapon_list:
                        aircraft_weapon_list[item2] += item_qty
                    else:
                        aircraft_weapon_list[item2] = item_qty
                else:
                    aircraft_weapon_list[item2] = 0
    return aircraft_weapon_list

def check_limits(UI, stocks):
    """
    check_limits(UI, stocks):
    totals and returns the total quantity of items, and the total mass of those items.
    """
    mass = 0
    qty = 0
    volume = 0
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
                    item_volume = 0.32906
                else:
                    table = determine_item_table(UI, item)
                    item_mass = float(UI.QueryDatabase(table,item,'Weight_kg').GetRow(0).GetString(0))
                    item_volume = float(UI.QueryDatabase(table,item,'Volume_m3').GetRow(0).GetString(0))
                mass += item_mass * item_qty
                volume += item_volume * item_qty
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
                item_volume = 0.32906
            else:
                table = determine_item_table(UI, item)
                item_mass = float(UI.QueryDatabase(table,item,'Weight_kg').GetRow(0).GetString(0))
                item_volume = float(UI.QueryDatabase(table,item,'Volume_m3').GetRow(0).GetString(0))
            mass += item_mass * item_qty
            volume += item_volume * item_qty
    return qty, mass, volume

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

def Get_Own_Stock(UI, unit, current_year, country):
    """
    Get_Own_Stock(unit, current_year):
    determines an appropriate loadout, and the stock needed to reload it, returns the results.
    """
    table = determine_unit_table(UI, unit)
    #configure launcher loadout too based on this data.
    load_item = ''
    own_stock_list = {}
    loadout_entry = {}
    own_launchers = UI.QueryDatabase('platform_launcher', unit, 'LauncherId, LauncherClass, IsReloadable')
    for launcher_num in xrange(own_launchers.Size()):
        if own_launchers.GetRow(launcher_num).GetString(0) != "Error":
            LauncherId = own_launchers.GetRow(launcher_num).GetString(0)
            LauncherClass = own_launchers.GetRow(launcher_num).GetString(1)
            Reloadable = int(own_launchers.GetRow(launcher_num).GetString(2))
            Launcher_Config = UI.GetCompatibleItemList(launcher_num)
            launcher_items = {}
            wild_names = []
            for item_x in xrange(Launcher_Config.Size()):
                #item = Launcher_Config.GetRow(item_x).GetString(0)
                item = Launcher_Config.GetString(item_x)
                #item may be a wildcard, check for that now!
                if '*' in item:
                    #wildcard
                    wild_names.append(item)
                    wild_list = expand_wildcard(item, Wild_Items)
                else:
                    wild_list = [item]
                for item in wild_list:
                    if country in servicekit:
                        if item in servicekit[country]:
                            date1 = float(servicekit[country][item]['Entry'])
                            date2 = float(servicekit[country][item]['Exit'])
                            service_mod = Get_Weapon_Service_Mod(item, current_year, date1, date2)
                        else:
                            date1 = 2999
                            date2 = 1900
                            service_mod = 0
                    else:
                        table = determine_item_table(UI, item)
                        date1 = float(UI.QueryDatabase(table,item,'InitialYear').GetRow(0).GetString(0))
                        date2 = float(UI.QueryDatabase(table,item,'FinalYear').GetRow(0).GetString(0))
                        if table in ['fueltank']:
                            service_mod = 1
                        else:
                            service_mod = Get_Weapon_Service_Mod(item, current_year, date1, date2)        
                
                    if not date1 > current_year and not date2 < current_year:
                        qty = float(UI.GetItemCapacityForLauncher(launcher_num, item)) * service_mod
                        launcher_items[item] = qty

            #keep the item with the highest stock value, load that for now
            #need to make something better for choosing stock to load.
            high_val = 0
            has_load_item = False
            for item in launcher_items:
                if launcher_items[item] > high_val:
                    high_val = launcher_items[item]
                    load_item = item
                    has_load_item = True

            #build reload stock list
            is_wild = False
            for wild_name in wild_names:
                if wild_name in load_item:
                    #then we were a wildcard in the launcher config, not the full name, so lookup the wildcard name
                    is_wild = True
                    for item_x in xrange(Launcher_Config.Size()):
                        item = Launcher_Config.GetString(item_x)
                        if item == wild_name:
                            load_item_qty = int(UI.GetItemCapacityForLauncher(launcher_num, item))
                            break
                    break
            if not is_wild:
                for item_x in xrange(Launcher_Config.Size()):
                    item = Launcher_Config.GetString(item_x)
                    if item == load_item:
                        load_item_qty = int(UI.GetItemCapacityForLauncher(launcher_num, item))
                        break
                        
            if has_load_item:
                #build loadout list
                loadout_entry[launcher_num] = [load_item, load_item_qty]
                #Add stock if reloadable
                if Reloadable:
                    stock_lvl = {'torpedo':4,'ballistic':5,'missile':3}
                    stock = stock_lvl.get(determine_item_table(UI, load_item),5)
                    qty = float(load_item_qty) * stock
                    if load_item in own_stock_list:
                        own_stock_list[load_item] += qty
                    else:
                        own_stock_list[load_item] = qty

    return own_stock_list, loadout_entry

def airwing_stock(UI, airwing, current_year, country):
    """
    airwing_stock(airwing, item_dict, current_year, country):
    iterates over all the present aircraft, and compiles a list of all the items needed and their quantities.
    Returns the resulting dictionary.
    """
    airwing_stock = {}
    for aircraft in airwing:
        airwing_qty = airwing[aircraft]['count']
        aircraft_weapon_list = Get_Aircraft_Weapon_Stocks(UI, aircraft, airwing, current_year)
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
            if table in ['fueltank']:
                service_mod = 1
            else:
                service_mod = Get_Weapon_Service_Mod(item, current_year, date1, date2)
        airwing_stock[item] *= service_mod
    return airwing_stock
    
def generate_airwing(UI):
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
                table = 'air'
            else:
                table = 'simpleair'
                
            aircraft_data = UI.QueryDatabase(table,name, 'InitialYear, FinalYear, FuelCapacity_kg, Weight_kg, MaxTakeoffWeight_kg, Designation').GetRow(0)
            if aircraft_data.GetString(0) != 'Error' and aircraft_data.Size() == 6:
                airwing[name]['date1'] = aircraft_data.GetString(0)
                airwing[name]['date2'] = aircraft_data.GetString(1)
                airwing[name]['fuelcap'] = aircraft_data.GetString(2)
                airwing[name]['mass'] = aircraft_data.GetString(3)
                airwing[name]['MTOW'] = aircraft_data.GetString(4)
                airwing[name]['designation'] = aircraft_data.GetString(5)
                
                airwing[name]['payload'] = float(airwing[name]['MTOW']) - float(airwing[name]['mass']) - float(airwing[name]['fuelcap'])

                #replace dependence on data_dict with QueryDatabase when able to perform multi-line lookup
                airwing[name]['launchers'] = {}
                
                #own_launchers = UI.QueryDatabase('platform_launcher', name, 'LauncherClass')
                for launcher_num in xrange(UIn.GetLauncherCount()):
                    airwing[name]['launchers'][launcher_num] = {}
                    try:
                        Reloadable = int(own_launchers.GetRow(launcher_num).GetString(2))
                    except:
                        Reloadable = 0
                    launcher_items = UIn.GetCompatibleItemList(launcher_num)
                    #Launcher_Config = UI.QueryDatabase('launcher_configuration',LauncherClass,'ChildClass, ChildCapacity')
                    wild_names = []
                    for item_x in xrange(launcher_items.Size()):
                        item = launcher_items.GetString(item_x)
                        #iterate through launcher names and append items
                        qty = UIn.GetItemCapacityForLauncher(launcher_num, item)
                        airwing[name]['launchers'][launcher_num][item] = qty
    return airwing
    
def GetMagClasses(UI, magname):
    class1 = UI.QueryDatabase('stores',magname,'Class1').GetRow(0).GetString(0).split(';')
    class2 = UI.QueryDatabase('stores',magname,'Class2').GetRow(0).GetString(0).split(';')
    class3 = UI.QueryDatabase('stores',magname,'Class3').GetRow(0).GetString(0).split(';')
    class4 = UI.QueryDatabase('stores',magname,'Class4').GetRow(0).GetString(0).split(';')
    classlist = []
    for itemlist in [class1, class2, class3, class4]:
        for item in itemlist:
            if item not in classlist and item != '':
                classlist.append(item)
    return classlist

def get_mag_stock_mod(UI, mag, mag_items, mag_weight, mag_volume, mag_weight_limit, mag_item_limit, mag_volume_limit):
    if mag_weight > 0:
        weight_mod = (0.95 * mag_weight_limit) / mag_weight
    else:
        weight_mod = 4.29e9
    if mag_items > 0:
        qty_mod = mag_item_limit / mag_items
    else:
        qty_mod = 4.29e9
    if mag_volume > 0:
        volume_mod = mag_volume_limit / mag_volume
    else:
        volume_mod = 4.29e9
        
    return min(weight_mod, qty_mod, volume_mod)
    
def MagGenerator(UI):
    """
    MagGenerator(UI):
    Takes a date, and in return will load the launchers, and stock the magazines with date appropriate gear.
    
    This is not group capable, nothing prevents calling it from a group capable handler.
    """
    BB = UI.GetBlackboardInterface()
    SM = UI.GetScenarioInterface()
    mag_date = SM.GetScenarioDateAsString()
    current_year = DateString_DecimalYear(mag_date)
    
    launcher_count = UI.GetLauncherCount()
    
    unit = UI.GetPlatformClass()
    name = UI.GetPlatformName()
    UI.DisplayMessage('Configuring %s for year %0.3f' % (name, current_year))
    set_mag_items = float(4.29e9)
    set_mag_tonnage = float(4.29e9)
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
        
    if UI.QueryDatabase('platform_magazine',unit,'MagazineClass').GetRow(0).GetString(0) != 'Error':
        airwing = generate_airwing(UI)
        #get our country:
        if UI.IsSurface():
            table = 'ship'
        elif UI.IsGroundVehicle() or UI.IsFixed():
            table = 'ground'
        country = UI.QueryDatabase(table, unit, 'Country').GetRow(0).GetString(0)
        mag_info = UI.QueryDatabase('platform_magazine', unit, 'MagazineId, MagazineClass')
        magazines = {}
        magazines['limited'] = {}
        magazines['unlimited'] = {}
        all_items = UI.GetMagazineItems()
        for mag in xrange(mag_info.Size()):
            magname = mag_info.GetRow(mag).GetString(1)
            mag_id = mag_info.GetRow(mag).GetString(0)
            classes = GetMagClasses(UI, magname)
            if classes == []:
                magazines['unlimited'][mag_id] = magname
            else:
                magazines['limited'][mag_id] = magname
            
        airwing_stock_list = airwing_stock(UI, airwing, current_year, country)
        if launcher_count > 0:
            own_stock_list, loadout_entry = Get_Own_Stock(UI, unit, current_year, country)

        #split stock lists into magazine assignments.
        mag_assignments = {}
        assigned_items = []
        
        #limited magazine stock
        for mag in magazines['limited']:
            magname = magazines['limited'][mag]
            classes = GetMagClasses(UI, magname)
            mag_assignments[mag] = {}
            mag_assignments[mag]['Max Items'] = UI.QueryDatabase('stores',magname,'Capacity').GetRow(0).GetString(0)
            mag_assignments[mag]['Max Weight'] = UI.QueryDatabase('stores',magname,'MaxWeight_kg').GetRow(0).GetString(0)
            mag_assignments[mag]['Max Volume'] = UI.QueryDatabase('stores',magname,'MaxVolume_m3').GetRow(0).GetString(0)
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
        for mag in magazines['unlimited']:
            magname = magazines['unlimited'][mag]
            mag_assignments[mag] = {}
            if BB.KeyExists('MagTonnage'):
                mag_assignments[mag]['Max Weight'] = set_mag_tonnage
            else:
                mag_assignments[mag]['Max Weight'] = UI.QueryDatabase('stores',magname,'MaxWeight_kg').GetRow(0).GetString(0)
            if BB.KeyExists('MaxItems'):
                mag_assignments[mag]['Max Items'] = set_mag_items
            else:
                mag_assignments[mag]['Max Items'] = UI.QueryDatabase('stores',magname,'Capacity').GetRow(0).GetString(0)
            if BB.KeyExists('MaxVolume'):
                mag_assignments[mag]['Max Volume'] = set_mag_volume
            else:
                mag_assignments[mag]['Max Volume'] = UI.QueryDatabase('stores',magname,'MaxVolume_m3').GetRow(0).GetString(0)
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
            mag_volume_limit = float(mag_assignments[mag]['Max Volume'])
            for n in xrange(all_items.Size()):
                item = all_items.GetString(n)
                qty = UI.GetMagazineIdQuantity(item, int(mag))
                if qty > 0:
                    mag_assignments[mag]['items'][item] = qty
            mag_items, mag_weight, mag_volume = check_limits(UI, mag_assignments[mag]['items'])
            if float(mag_weight_limit) == 0:  mag_weight_limit = float(4.29e9)
            if float(mag_item_limit)   == 0:  mag_item_limit = float(4.29e9)
            if float(mag_volume_limit) == 0:  mag_volume_limit = float(4.29e9)
            
            if mag in magazines['unlimited']:
                mag_weight_limit = min(mag_weight_limit, set_mag_tonnage)
                mag_item_limit = min(mag_weight_limit, set_mag_items)
            
            mag_stock_mod[mag] = get_mag_stock_mod(UI, mag, mag_items, mag_weight, mag_volume, mag_weight_limit, mag_item_limit, mag_volume_limit)
        mag_loads = {}
        #begin creating the magazine entry lines
        for mag_num in mag_assignments:
            stock_mod = mag_stock_mod[mag_num]
            for item in mag_assignments[mag_num]['items']:
                item_table = determine_item_table(UI, item)
                if item_table in ['fueltank']:
                    item_qty = int(mag_assignments[mag_num]['items'][item])
                else:
                    item_qty = int(mag_assignments[mag_num]['items'][item] * stock_mod)
                if item_qty < 1:
                    item_qty = 0
                if 'Nuclear' in UI.QueryDatabase(item_table,item,'DamageModel').GetRow(0).GetString(0) and not BB.KeyExists('MagGenAllowNukes'):
                    item_qty = 0
#                if launcher_count > 0:
#                    if item in own_stock_list and item_qty < own_stock_list[item]:
#                        item_qty += int(own_stock_list[item])
                if item_qty > 0:
                    try:
                        mag_loads[mag_num][item] = item_qty
                    except KeyError:
                        mag_loads[mag_num] = {item:item_qty}
        #set magazine
        stocked = {}
        for magazine in sorted(mag_loads.keys()):
            UI.SetMagazineEmpty(int(magazine))
            for item in mag_loads[magazine]:
                qty = int(mag_loads[magazine][item])
                UI.AddItemToMagazine(item, qty)
                UI.DisplayMessage('%s : %s' % (item, qty))
                stocked[item]=qty
        
    elif launcher_count > 0:
        own_stock_list, loadout_entry = Get_Own_Stock(unit, unit_dict, current_year)
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
    #tonnage = 0
    #for mag in mag_loads:
    #    tonnage += check_limits(UI, mag_loads[mag])[1]/1000
    tonnage = check_limits(UI, stocked)[1]/1000
    UI.DisplayMessage('%0.1f tons of munitions provided to <%d> %s (%s)' % (tonnage, UI.GetPlatformId(), UI.GetPlatformName(), unit))

def stock_rate(UI, aircraft, item):
    qty = 0
    sortie = 0
    item_table = determine_item_table(UI, item)

    if UI.QueryDatabase('air', aircraft, 'InitialYear').GetRow(0).GetString(0) != 'Error':
        unit_role = UI.QueryDatabase('air', aircraft,'Designation').GetRow(0).GetString(0)
    else:
        unit_role = UI.QueryDatabase('simpleair', aircraft,'Designation').GetRow(0).GetString(0)

    try:
        sortie = int(sorties[unit_role])
    except KeyError:
        return 0
    
    if item_table == 'cm':
        qty = cm.get(unit_role,2)
    elif item_table == 'fueltank':
        qty = tank.get(unit_role,1)
    elif item_table == 'sonobuoy':
        qty = buoy.get(unit_role,0)
    elif item_table == 'ballistic':
        if 'Nuclear' in UI.QueryDatabase(item_table,item,'DamageModel').GetRow(0).GetString(0):
            qty = nuke_bomb.get(unit_role,0)
        elif UI.QueryDatabase(item_table,item,'BallisticType').GetRow(0).GetString(0) == '5':  #rockets
            qty = rockets.get(unit_role,0)
        elif (UI.QueryDatabase(item_table,item,'BallisticType').GetRow(0).GetString(0) == '0' or
            UI.QueryDatabase(item_table,item,'BallisticType').GetRow(0).GetString(0) == '2'):  #gun round, autocannon round
            qty = gun.get(unit_role,1)
        elif UI.QueryDatabase(item_table,item,'BallisticType').GetRow(0).GetString(0) == '1':  #unguided bomb
            if UI.QueryDatabase('torpedo',UI.QueryDatabase('ballistic',item,'Payload').GetRow(0).GetString(0),'weight_kg').GetRow(0).GetString(0) != 'Error':
                if UI.QueryDatabase('torpedo',item,'ClassificationId').GetRow(0).GetString(0) == '138':  #mine
                    qty = mine_bomb.get(unit_role,0)
                elif UI.QueryDatabase('torpedo',item,'WeaponType').GetRow(0).GetString(0) == '2':
                    qty = DC.get(unit_role,0)
            mass = float(UI.QueryDatabase(item_table, item,'Weight_kg').GetRow(0).GetString(0))
            if mass < 125:
                qty = ib_125.get(unit_role,0)
            elif mass < 250:
                qty = ib_250.get(unit_role,0)
            elif mass < 500:
                qty = ib_500.get(unit_role,0)
            elif mass < 750:
                qty = ib_750.get(unit_role,0)
            elif mass < 1000:
                qty = ib_1000.get(unit_role,0)
            elif mass < 2000:
                qty = ib_2000.get(unit_role,0)
            elif mass < 3000:
                qty = ib_3000.get(unit_role,0)
        elif UI.QueryDatabase(item_table,item,'BallisticType').GetRow(0).GetString(0) == '3':  #guided bomb
            mass = float(UI.QueryDatabase(item_table, item,'Weight_kg').GetRow(0).GetString(0))
            if mass < 125:
                qty = gb_125.get(unit_role,0)
            elif mass < 250:
                qty = gb_250.get(unit_role,0)
            elif mass < 500:
                qty = gb_500.get(unit_role,0)
            elif mass < 750:
                qty = gb_750.get(unit_role,0)
            elif mass < 1000:
                qty = gb_1000.get(unit_role,0)
            elif mass < 2000:
                qty = gb_2000.get(unit_role,0)
    elif item_table == 'torpedo':
        if UI.QueryDatabase(item_table,item,'WeaponType').GetRow(0).GetString(0) == '1':
            qty = torpedo.get(unit_role,0)
        elif UI.QueryDatabase(item_table,item,'WeaponType').GetRow(0).GetString(0) == '2':
            qty = DC.get(unit_role,0)
        else:
            qty = mine.get(unit_role,0)
    elif item_table == 'missile':
        if 'Nuclear' in UI.QueryDatabase(item_table,item,'DamageModel').GetRow(0).GetString(0):
            qty = nuke_mis.get(unit_role,0)
        else:
            targets = bin(int(UI.QueryDatabase(item_table,item,'targetFlags').GetRow(0).GetString(0)))[2:]
            surface = int(targets[-1])
            if len(targets) > 1:
                air = int(targets[-2])
            else:
                air = 0
            if len(targets) > 2:
                land = int(targets[-3])
            else:
                land = 0
            if len(targets) > 3:
                missile = int(targets[-4])
            else:
                missile = 0
            if len(targets) > 4:
                sub = int(targets[-5])
            else:
                sub = 0
            
            mass = float(UI.QueryDatabase(item_table, item,'Weight_kg').GetRow(0).GetString(0))
            
            if air:
                range_km = float(UI.QueryDatabase(item_table, item,'MaxRange_km').GetRow(0).GetString(0))
                year = float(UI.QueryDatabase(item_table, item,'InitialYear').GetRow(0).GetString(0))
                year -= 1950
                if UI.QueryDatabase('optical', UI.QueryDatabase(item_table, item,'SensorClass').GetRow(0).GetString(0),'Cost').GetRow(0).GetString(0) != 'Error':  #its ir
                    short_ir = year / 5 * 0.08 * 16
                    medium_ir = year / 5 * 0.08 * 24
                    long_ir = year / 5 * 0.08 * 32
                    
                    if range_km < short_ir:
                        qty = ir_sraam.get(unit_role,0)
                    elif range_km < medium_ir:
                        qty = ir_mraam.get(unit_role,0)
                    elif range_km < long_ir:
                        qty = ir_lraam.get(unit_role,0)
                    else:
                        qty = ir_vlraam.get(unit_role,0)
                elif UI.QueryDatabase('esm', UI.QueryDatabase(item_table, item,'SensorClass').GetRow(0).GetString(0),'Cost').GetRow(0).GetString(0) != 'Error':  #its esm
                    qty = ir_vlraam.get(unit_role,0)  #just using the longest of the actives for now.
                else:  #its radar
                    short_radar = year / 5.0 * 0.08 * 50.0
                    medium_radar = year / 5.0 * 0.08 * 100.0
                    long_radar = year / 5.0 * 0.08 * 200.0
                    very_long_radar = year / 5.0 * 0.08 * 200.0
                    semiactive = int(UI.QueryDatabase('radar', UI.QueryDatabase(item_table, item,'SensorClass').GetRow(0).GetString(0),'IsSemiactive').GetRow(0).GetString(0))
                    if range < short_radar:
                        if semiactive:
                            qty = sr_sraam.get(unit_role,0)
                        else:
                            qty = ar_sraam.get(unit_role,0)
                    elif range < medium_radar:
                        if semiactive:
                            qty = sr_mraam.get(unit_role,0)
                        else:
                            qty = ar_mraam.get(unit_role,0)
                    elif range < long_radar:
                        if semiactive:
                            qty = sr_lraam.get(unit_role,0)
                        else:
                            qty = ar_lraam.get(unit_role,0)
                    else:
                        if semiactive:
                            qty = sr_vlraam.get(unit_role,0)
                        else:
                            qty = ar_vlraam.get(unit_role,0)
            elif UI.QueryDatabase('esm', UI.QueryDatabase(item_table, item,'SensorClass').GetRow(0).GetString(0),'Cost').GetRow(0).GetString(0) != 'Error':  #its esm
                if mass < 50:
                    qty = usarm.get(unit_role,0)
                elif mass < 150:
                    qty = vsarm.get(unit_role,0)
                elif mass < 400:
                    qty = sarm.get(unit_role,0)
                elif mass < 1000:
                    qty = arm.get(unit_role,0)
                elif mass > 1000:
                    qty = larm.get(unit_role,0)
                elif mass > 2500:
                    qty = vlarm.get(unit_role,0)
            elif surface and land:
                if mass < 50:
                    qty = usagsm.get(unit_role,0)
                elif mass < 150:
                    qty = vsagsm.get(unit_role,0)
                elif mass < 400:
                    qty = sagsm.get(unit_role,0)
                elif mass < 1000:
                    qty = agsm.get(unit_role,0)
                elif mass > 1000:
                    qty = lagsm.get(unit_role,0)
                elif mass > 2500:
                    qty = vlagsm.get(unit_role,0)
            elif surface:
                if mass < 50:
                    qty = usasm.get(unit_role,0)
                elif mass < 150:
                    qty = vsasm.get(unit_role,0)
                elif mass < 400:
                    qty = sasm.get(unit_role,0)
                elif mass < 1000:
                    qty = asm.get(unit_role,0)
                elif mass > 1000:
                    qty = lasm.get(unit_role,0)
                elif mass > 2500:
                    qty = vlasm.get(unit_role,0)
            elif land:
                if mass < 50:
                    qty = usagm.get(unit_role,0)
                elif mass < 150:
                    qty = vsagm.get(unit_role,0)
                elif mass < 400:
                    qty = sagm.get(unit_role,0)
                elif mass < 1000:
                    qty = agm.get(unit_role,0)
                elif mass > 1000:
                    qty = lagm.get(unit_role,0)
                elif mass > 2500:
                    qty = vlagm.get(unit_role,0)
                
    #return float(sortie) * float(qty)
    return float(qty)