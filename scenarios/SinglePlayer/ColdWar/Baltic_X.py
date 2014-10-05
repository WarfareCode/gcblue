# Created on 05/22/11 20:38:54
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Cold war hypothetical in Baltic Sea\n\n""")
    SM.SetScenarioName("""Baltic X""")
    SM.CreateAlliance(1, 'NATO')
    SM.SetAllianceDefaultCountry(1, 'NATO')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 1)
    SM.SetUserAlliance(1)

    SM.SetDateTime(1982,9,1,12,0,0)
    SM.SetStartTheater(11.529166, 55.237499) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """SITUATION:\n\nSecret NATO airbase in vicinity of Karlskrona, Sweden has been \ndiscovered by Soviet forces. Soviets have protested the airbase as a \nviolation of Swedish neutrality and are believed to be preparing an air \nstrike. NATO air forces have reinforced the base. Nimitz CVBG inbound \nfor additional reinforcement.\n\nORDERS:\n\nDefend Karlskrona airbase from air strikes until Nimitz reaches her patrol \narea 20 km south of the airbase.\n\nROE:\n\nWeapons free, unidentified aircraft and subsurface contacts assumed \nhostile\n\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """TASKING ORDERS:\n\n\nNO ADDITIONAL INTELLIGENCE AVAILABLE.\n""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Nimitz CVN-68 USS Nimitz'
    unit.unitName = "USS Nimitz"
    unit.SetPosition(13.192124, 55.184717, 0.0)
    unit.heading = 90.00
    unit.speed = 30.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Nimitz", 'Fuel', 10600000)
    SM.AddToUnitMagazine("USS Nimitz", 'AIM-9L', 209)
    SM.AddToUnitMagazine("USS Nimitz", 'AIM-7F', 270)
    SM.AddToUnitMagazine("USS Nimitz", 'AIM-54A', 43)
    SM.AddToUnitMagazine("USS Nimitz", 'AGM-45B', 207)
    SM.AddToUnitMagazine("USS Nimitz", 'AGM-78B', 3)
    SM.AddToUnitMagazine("USS Nimitz", 'AGM-84A Harpoon', 47)
    SM.AddToUnitMagazine("USS Nimitz", 'Mk-46 Mod5', 139)
    SM.AddToUnitMagazine("USS Nimitz", 'M117', 1169)
    SM.AddToUnitMagazine("USS Nimitz", 'M118', 305)
    SM.AddToUnitMagazine("USS Nimitz", 'Mk-82', 1927)
    SM.AddToUnitMagazine("USS Nimitz", 'Mk-83', 1088)
    SM.AddToUnitMagazine("USS Nimitz", 'Mk-84', 401)
    SM.AddToUnitMagazine("USS Nimitz", 'B-57 Mod5 10kT', 5)
    SM.AddToUnitMagazine("USS Nimitz", 'B-57 Mod5 20kT', 3)
    SM.AddToUnitMagazine("USS Nimitz", 'FPU-6', 1)
    SM.AddToUnitMagazine("USS Nimitz", '370 gallon wing tank', 6)
    SM.AddToUnitMagazine("USS Nimitz", '300 gallon wing tank', 3)
    SM.AddToUnitMagazine("USS Nimitz", '20mm PGU', 1527)
    SM.AddToUnitMagazine("USS Nimitz", 'Chaff-1', 3536)
    SM.AddToUnitMagazine("USS Nimitz", 'Flare-1', 3536)
    SM.AddToUnitMagazine("USS Nimitz", 'LOFAR (80) Sonobuoy', 533)
    SM.AddToUnitMagazine("USS Nimitz", 'DICASS (80) Sonobuoy', 533)
    SM.AddToUnitMagazine("USS Nimitz", 'DIFAR (80) Sonobuoy', 1599)
    SM.AddToUnitMagazine("USS Nimitz", 'RIM-7P(v1)', 94)
    SM.AddToUnitMagazine("USS Nimitz", '20mm mark 244-0 ELC', 2092)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.248876, 0.964097, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.268881, 0.978076, 0.000000, 0.000000)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 1', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 2', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 3', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 4', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 5', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 6', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 7', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 8', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 9', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 10', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 11', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Fast Eagle 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Fast Eagle 12', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 1', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 2', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 3', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 4', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 5', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 6', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 7', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 8', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 9', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 10', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 11', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'F-14A', 'Victory 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Victory 12', '32 20mm PGU;4 AIM-7F;2 AIM-9L;2 AIM-54A;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 1', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 2', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 3', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 4', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 5', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 6', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 7', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 8', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 9', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 10', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 11', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Claw 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Claw 12', '6 Mk-83;2 Mk-83;2 370 gallon wing tank;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 1', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 2', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 3', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 4', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 5', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 6', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 7', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 8', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 9', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 10', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 11', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-7E Corsair II', 'Winder 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Winder 12', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9L;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-6E', 'Raygun 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Raygun 1', '3 M117;1 300 gallon wing tank;3 M117;1 300 gallon wing tank;3 M117;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-6E', 'Raygun 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Raygun 2', '3 M117;1 300 gallon wing tank;3 M117;1 300 gallon wing tank;3 M117;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-6E', 'Raygun 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Raygun 3', '3 M117;1 300 gallon wing tank;3 M117;1 300 gallon wing tank;3 M117;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-6E', 'Raygun 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Raygun 4', '1 M117;3 M117;1 M117;3 M117;3 M117;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-6E', 'Raygun 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Raygun 5', '1 M117;3 M117;1 M117;3 M117;3 M117;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'A-6E', 'Raygun 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Raygun 6', '1 M117;3 M117;1 M117;3 M117;3 M117;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'KA-6D', 'Raygun 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Raygun 101', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'KA-6D', 'Raygun 102', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Raygun 102', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'KA-6D', 'Raygun 103', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Raygun 103', '0 Empty;0 Empty;0 Empty;0 Empty')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'KA-6D', 'Raygun 104', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Raygun 104', '0 Empty;0 Empty;0 Empty;0 Empty')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'EA-6B', 'Black Ravens 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Black Ravens 1', '2 AGM-78B;2 FPU-6;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'EA-6B', 'Black Ravens 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Black Ravens 2', '2 AGM-78B;2 FPU-6;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'EA-6B', 'Black Ravens 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Black Ravens 3', '2 AGM-78B;2 FPU-6;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'EA-6B', 'Black Ravens 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Black Ravens 4', '2 AGM-78B;2 AGM-45B;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'EA-6B', 'Black Ravens 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Black Ravens 5', '2 AGM-78B;2 AGM-45B;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'EA-6B', 'Black Ravens 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Black Ravens 6', '2 AGM-78B;2 AGM-45B;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'E-2C', 'Bear Aces 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Bear Aces 1', '')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'E-2C', 'Bear Aces 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Bear Aces 2', '')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'E-2C', 'Bear Aces 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Bear Aces 3', '')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'E-2C', 'Bear Aces 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Bear Aces 4', '')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'E-2C', 'Bear Aces 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Bear Aces 5', '')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'E-2C', 'Bear Aces 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Bear Aces 6', '')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'S-3A', 'Scouts 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Scouts 1', '12 DICASS (80) Sonobuoy;12 LOFAR (80) Sonobuoy;36 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'S-3A', 'Scouts 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Scouts 2', '12 DICASS (80) Sonobuoy;12 LOFAR (80) Sonobuoy;36 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'S-3A', 'Scouts 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Scouts 3', '12 DICASS (80) Sonobuoy;12 LOFAR (80) Sonobuoy;36 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'S-3A', 'Scouts 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Scouts 4', '12 DICASS (80) Sonobuoy;12 LOFAR (80) Sonobuoy;36 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'S-3A', 'Scouts 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Scouts 5', '12 DICASS (80) Sonobuoy;12 LOFAR (80) Sonobuoy;36 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'S-3A', 'Scouts 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Scouts 6', '12 DICASS (80) Sonobuoy;12 LOFAR (80) Sonobuoy;36 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'S-3A', 'Scouts 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Scouts 7', '12 DICASS (80) Sonobuoy;12 LOFAR (80) Sonobuoy;36 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'S-3A', 'Scouts 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Scouts 8', '12 DICASS (80) Sonobuoy;12 LOFAR (80) Sonobuoy;36 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'S-3A', 'Scouts 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Scouts 9', '12 DICASS (80) Sonobuoy;12 LOFAR (80) Sonobuoy;36 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'S-3A', 'Scouts 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Scouts 10', '12 DICASS (80) Sonobuoy;12 LOFAR (80) Sonobuoy;36 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'SH-3H', 'Sea Griffons 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Sea Griffons 1', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'SH-3H', 'Sea Griffons 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Sea Griffons 2', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'SH-3H', 'Sea Griffons 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Sea Griffons 3', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'SH-3H', 'Sea Griffons 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Sea Griffons 4', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'SH-3H', 'Sea Griffons 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Sea Griffons 5', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nimitz', 'SH-3H', 'Sea Griffons 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nimitz', 'Sea Griffons 6', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Karlskrona"
    unit.SetPosition(15.416346, 56.234204, -0.0)
    unit.heading = 165.96
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Karlskrona", 'Fuel', 100000)
    SM.AddToUnitMagazine("Karlskrona", '300 liter tank', 24)
    SM.AddToUnitMagazine("Karlskrona", '370 liter tank', 48)
    SM.AddToUnitMagazine("Karlskrona", 'AIM-9L', 150)
    SM.AddToUnitMagazine("Karlskrona", 'Mk-84', 96)
    SM.AddToUnitMagazine("Karlskrona", 'Mk-83', 216)
    SM.AddToUnitMagazine("Karlskrona", 'Mk-82', 480)
    SM.AddToUnitMagazine("Karlskrona", 'Mk 71 Zuni WAFAR', 384)
    SM.AddToUnitMagazine("Karlskrona", '20mm PGU', 1104)
    SM.AddToUnitMagazine("Karlskrona", 'Chaff-1', 720)
    SM.AddToUnitMagazine("Karlskrona", 'Flare-1', 720)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-1', 2)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-1', '2 AIM-9L;2 AIM-9L;2 Mk-84;2 Mk-84;1 Mk-83;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-2', 2)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-2', '2 AIM-9L;2 AIM-9L;2 Mk-84;2 Mk-84;1 Mk-83;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-3', 2)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-3', '2 AIM-9L;2 AIM-9L;2 Mk-84;2 Mk-84;1 Mk-83;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-4', 2)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-4', '2 AIM-9L;2 AIM-9L;2 Mk-84;2 Mk-84;1 Mk-83;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-5', 1)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-5', '2 AIM-9L;2 AIM-9L;4 Mk-83;4 Mk-83;1 Mk-83;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-6', 1)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-6', '2 AIM-9L;2 AIM-9L;4 Mk-83;4 Mk-83;1 Mk-83;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-7', 1)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-7', '2 AIM-9L;2 AIM-9L;4 Mk-83;4 Mk-83;1 Mk-83;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-8', 1)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-8', '2 AIM-9L;2 AIM-9L;4 Mk-83;4 Mk-83;1 Mk-83;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-9', 1)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-9', '2 AIM-9L;2 AIM-9L;8 Mk 71 Zuni WAFAR;8 Mk 71 Zuni WAFAR;1 300 gallon wing tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-10', 1)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-10', '2 AIM-9L;2 AIM-9L;8 Mk 71 Zuni WAFAR;8 Mk 71 Zuni WAFAR;1 300 gallon wing tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-11', 1)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-11', '2 AIM-9L;2 AIM-9L;8 Mk 71 Zuni WAFAR;8 Mk 71 Zuni WAFAR;1 300 gallon wing tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Karlskrona', 'F-16A/B Blk 15', 'Falcon-12', 1)
    SM.SetFlightDeckUnitLoadout('Karlskrona', 'Falcon-12', '2 AIM-9L;2 AIM-9L;8 Mk 71 Zuni WAFAR;8 Mk 71 Zuni WAFAR;1 300 gallon wing tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Stinger Vehicle'
    unit.unitName = "Stinger-1"
    unit.SetPosition(15.522745, 56.231625, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FIM-92 Stinger', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Stinger Vehicle'
    unit.unitName = "Stinger-2"
    unit.SetPosition(15.295853, 56.211514, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FIM-92 Stinger', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Spruance DDG'
    unit.unitName = "USS Moosbrugger"
    UI = SM.GetUnitInterface('USS Nimitz')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0714
    lat_deg = 57.296*leader_track.Lat + 0.0125
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 2, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84C Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84C Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'RUM-139 Mod4 ASROC', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Moosbrugger", 'Fuel', 65095)
    SM.AddToUnitMagazine("USS Moosbrugger", 'Mk-46 Mod5', 29)
    SM.AddToUnitMagazine("USS Moosbrugger", 'LOFAR (80) Sonobuoy', 263)
    SM.AddToUnitMagazine("USS Moosbrugger", 'DICASS (80) Sonobuoy', 263)
    SM.AddToUnitMagazine("USS Moosbrugger", 'DIFAR (80) Sonobuoy', 788)
    SM.AddToUnitMagazine("USS Moosbrugger", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Moosbrugger", '127mm mk 80 HE-PD mk 67', 1200)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Nimitz')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(4.683, 0.500, -0.307, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Moosbrugger', 'SH-2F', 'Spruance DDG Seasprite 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Moosbrugger', 'Spruance DDG Seasprite 1', '2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Moosbrugger', 'SH-2F', 'Spruance DDG Seasprite 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Moosbrugger', 'Spruance DDG Seasprite 2', '2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oliver Hazard Perry FFGHM'
    unit.unitName = "USS Clark"
    UI = SM.GetUnitInterface('USS Nimitz')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1028
    lat_deg = 57.296*leader_track.Lat + -0.0312
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66B', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Clark", 'Fuel', 28058)
    SM.AddToUnitMagazine("USS Clark", 'Mk-46 Mod5', 26)
    SM.AddToUnitMagazine("USS Clark", '120 gallon tank', 2)
    SM.AddToUnitMagazine("USS Clark", 'Chaff-1', 50)
    SM.AddToUnitMagazine("USS Clark", 'Flare-1', 50)
    SM.AddToUnitMagazine("USS Clark", 'DICASS (80) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Clark", 'LOFAR (80) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Clark", 'DIFAR (80) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS Clark", 'RIM-66E', 35)
    SM.AddToUnitMagazine("USS Clark", 'RGM-84C Harpoon', 4)
    SM.AddToUnitMagazine("USS Clark", '20mm mark 244-0 ELC', 523)
    SM.AddToUnitMagazine("USS Clark", '76mm HE-MOM', 240)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Nimitz')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(7.950, 3.196, 0.420, 0.606)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Clark', 'SH-2F', 'Perry FFG Seasprite 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Clark', 'Perry FFG Seasprite 1', '2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877E Paltus'
    unit.unitName = "K-803"
    unit.SetPosition(15.384891, 55.870203, -40.0)
    unit.heading = 233.66
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Igla-M SAM', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-803", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-803", '53-65M', 6)
    SM.AddToUnitMagazine("K-803", 'Igla-M SAM', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('SubBattery', 3.000000, 0)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.973715')
    BB.Write('StationLongitude', '0.268278')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877E Paltus'
    unit.unitName = "K-802"
    unit.SetPosition(14.865619, 55.631509, -48.3)
    unit.heading = 236.07
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Igla-M SAM', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-802", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-802", '53-65M', 6)
    SM.AddToUnitMagazine("K-802", 'Igla-M SAM', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('SubBattery', 3.000000, 0)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877E Paltus'
    unit.unitName = "K-801"
    unit.SetPosition(14.410404, 55.326123, -30.0)
    unit.heading = 259.73
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Igla-M SAM', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-801", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-801", '53-65M', 6)
    SM.AddToUnitMagazine("K-801", 'Igla-M SAM', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('SubBattery', 3.000000, 0)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Chkalovsk"
    unit.SetPosition(20.395522, 54.769782, 124.9)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Chkalovsk", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Chkalovsk", 'Chaff-1', 200)
    SM.AddToUnitMagazine("Chkalovsk", 'Flare-1', 200)
    SM.AddToUnitMagazine("Chkalovsk", '23mm AM-23', 550)
    SM.AddToUnitMagazine("Chkalovsk", '3000 liter tank', 100)
    SM.AddToUnitMagazine("Chkalovsk", 'FAB-500', 110)
    SM.AddToUnitMagazine("Chkalovsk", 'KAB-500L', 200)
    SM.AddToUnitMagazine("Chkalovsk", 'Kh-22M', 94)
    SM.AddToUnitMagazine("Chkalovsk", 'Kh-22MP', 91)
    SM.AddToUnitMagazine("Chkalovsk", 'Kh-29T', 100)
    SM.AddToUnitMagazine("Chkalovsk", 'Kh-31P', 93)
    SM.AddToUnitMagazine("Chkalovsk", 'Kh-59MK', 100)
    SM.AddToUnitMagazine("Chkalovsk", 'R-27R', 108)
    SM.AddToUnitMagazine("Chkalovsk", 'R-60', 100)
    SM.AddToUnitMagazine("Chkalovsk", 'R-73M', 100)
    SM.AddToUnitMagazine("Chkalovsk", 'R-77', 100)
    UI.SetSensorState(0, 1)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-1', 2)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-1', '4 R-27R;2 R-27R;4 R-27R;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-2', 2)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-2', '4 R-27R;2 R-27R;4 R-27R;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-3', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-3', '3 Kh-31P;2 R-27R;4 Kh-31P;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-4', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-4', '4 R-27R;2 R-27R;4 R-27R;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-5', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-5', '4 R-27R;2 R-27R;4 R-27R;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-6', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-6', '4 R-27R;2 R-27R;4 R-27R;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-7', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-7', '4 R-27R;2 R-27R;4 R-27R;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-8', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-8', '4 R-27R;2 R-27R;4 R-27R;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-9', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-9', '4 R-27R;2 R-27R;4 R-27R;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-10', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-10', '4 R-27R;2 R-27R;4 R-27R;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-11', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-11', '4 R-27R;2 R-27R;4 R-27R;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-27', 'Flanker-12', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Flanker-12', '4 R-27R;2 R-27R;4 R-27R;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-1', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-1', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-2', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-2', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-3', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-3', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-4', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-4', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-5', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-5', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-6', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-6', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-7', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-7', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-8', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-8', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-9', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-9', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-10', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-10', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-11', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-11', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Su-24M', 'Fencer-12', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Fencer-12', '2 R-60;2 3000 liter tank;0 Empty;0 Empty;6 23mm AM-23;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-1', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-1', '0 Empty;30 FAB-500;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-2', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-2', '0 Empty;30 FAB-500;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-3', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-3', '0 Empty;30 FAB-500;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-4', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-4', '2 Kh-22MP;1 Kh-22MP;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-5', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-5', '2 Kh-22M;1 Kh-22M;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-6', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-6', '2 Kh-22M;1 Kh-22M;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-7', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-7', '2 Kh-22M;1 Kh-22M;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-8', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-8', '2 Kh-22M;1 Kh-22M;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-9', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-9', '2 Kh-22MP;1 Kh-22MP;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-10', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-10', '2 Kh-22MP;1 Kh-22MP;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-11', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-11', '2 Kh-22MP;1 Kh-22MP;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Chkalovsk', 'Tu-22ME', 'Backfire-12', 1)
    SM.SetFlightDeckUnitLoadout('Chkalovsk', 'Backfire-12', '2 Kh-22MP;1 Kh-22MP;25 Chaff-1;25 Flare-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Backfire-1')
    FP.AddAircraftToMission(mission_id, 'Backfire-2')
    FP.AddAircraftToMission(mission_id, 'Backfire-3')
    FP.SetMissionLaunchTime(mission_id, '12:15:00+15m+R12.0')
    FP.SetMissionDatum(mission_id, 0.2690661, 0.9814711)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 3)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3548580, 0.9656360, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3159420, 0.9782030, 1000.0, 400.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.2895280, 0.9810350, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'BombDatum')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3157080, 0.9717010, 7000.0, 300.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3439180, 0.9640430, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 4, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Flanker-1')
    FP.AddAircraftToMission(mission_id, 'Flanker-2')
    FP.AddAircraftToMission(mission_id, 'Flanker-3')
    FP.SetMissionLaunchTime(mission_id, '12:10:00+10m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 3)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2633872,0.9739003,0.2770830,0.9723722,0.2707362,0.9573296,0.2549654,0.9595469,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3370360, 0.9588490, 8000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2789690, 0.9619080, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3353390, 0.9544460, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Backfire-6')
    FP.AddAircraftToMission(mission_id, 'Backfire-7')
    FP.AddAircraftToMission(mission_id, 'Backfire-8')
    FP.AddAircraftToMission(mission_id, 'Backfire-9')
    FP.SetMissionLaunchTime(mission_id, '12:50:00+10m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3484580, 0.9502720, 500.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2578310, 0.9404830, 6000.0, 700.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'RadarOn,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2574390, 0.9548200, 0.0, 0.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.2704880, 0.9497110, 500.0, 350.0)
    FP.SetMissionWaypointTasks(mission_id, 3, 'RadarOff')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3369050, 0.9559640, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 4, 'Land')
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.AreaGoal()
    goal_temp.SetTargetList('USS Nimitz')
    goal_temp.SetTimeObjective(0.000000)
    goal_temp.SetLogicAny(1)
    goal_temp.AddPointDeg(15.60236, 56.09926)
    goal_temp.AddPointDeg(15.60432, 55.98537)
    goal_temp.AddPointDeg(15.23979, 55.98537)
    goal_temp.AddPointDeg(15.23783, 56.09926)
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.DestroyGoal('Karlskrona')
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
