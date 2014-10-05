# Created on 03/16/12 00:33:20
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Iron Fist\nV 1.0\n2010/06/26\n\nA scenario for Global Conflicts 2.\nCold War Battleset\n\nWritten by Ralf Koelbach.\nrkoelbach@yahoo.com\n\nIron Fist is a classical Cold War scenario. Subject is an US attack \nconducted by a carrier group against a Soviet beachhead in Norway.\n\nYour task is to destroy all hostile facilities.\n\nComments and critiques welcome!\n\nHave fun!\nRalf\n\nJune 2010\n\n\n\n\n\n\n""")
    SM.SetScenarioName("""Iron Fist""")
    SM.CreateAlliance(1, 'USA')
    SM.SetAllianceDefaultCountry(1, 'USA')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 0)
    SM.SetUserAlliance(1)

    SM.SetDateTime(1989,8,15,4,0,0)
    SM.SetStartTheater(3.062500, 56.470833) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """ORDERS FOR CMDR US OPERATIONS\n\nINTELLIGENCE\n\nThe control of the GIUK Gap is vital for our efforts to win the war. Thus \nthe Soviet beachhead on Norway is a thorn in our side.\n\nExpect heavy resistance, including multiple SSM and SAM sites. The \nbattle cruiser Kirov is approaching from the North. Air and Sub threat \nunknown. \n\n\nMISSION\n\nLocalize and destroy all hostile units on Norwegian soil and close to it.\n\nEXECUTION\n\nProceed step by step:\n1. First, gather information about what you are up against. \n2. Second, plan your strikes. \n3. Then conduct your offensive operations step by step.\n\nGOALS\nDestroy shore based hostile facilities. Focus on those who can harm our \nlanding force; especially SSMs.\n\nFind and sink the LST Ropucha and the AOR Boris Chilikin. \n\nSink the BCGN Kirov. \n\nYou must not lose your carrier.\n\nDanger is imminent, you have just launched a few aircraft. Use them \nwisely.\n\nCOMMAND AND SIGNAL\n\nFlag Ship:\nCVN Nimitz \n\nRecommended EMCON status:\nA No Emissions\n\nGood luck, commander\n\n\n\n\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """ORDERS FOR CMDR USSR OPERATIONS\n\nThis side is not human playable.\n\n""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'EA-6B'
    unit.unitName = "Firestreak-1"
    unit.SetPosition(2.121053, 58.429891, 516.0)
    unit.heading = 90.04
    unit.speed = 566.0
    unit.cost = 52000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FPU-8', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AGM-45A', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'USS Carl Vinson')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'F-14B'
    unit.unitName = "Black Knight-2"
    unit.SetPosition(2.121053, 58.429891, 516.0)
    unit.heading = 90.04
    unit.speed = 208.4
    unit.cost = 38000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm PGU', 32)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AIM-7M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-9M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'AIM-54C', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'USS Carl Vinson')
    UI.SetThrottle(1.100000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'F-14B'
    unit.unitName = "Black Knight-1"
    unit.SetPosition(2.121053, 58.429891, 516.0)
    unit.heading = 90.04
    unit.speed = 208.4
    unit.cost = 38000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm PGU', 32)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AIM-7M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-9M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'AIM-54C', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'USS Carl Vinson')
    UI.SetThrottle(1.100000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Nimitz CVN-70 USS Carl Vinson'
    unit.unitName = "USS Carl Vinson"
    unit.SetPosition(2.121376, 58.429778, 0.0)
    unit.heading = 70.56
    unit.speed = 8.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Fuel', 10600000)
    SM.AddToUnitMagazine("USS Carl Vinson", 'AIM-9M', 191)
    SM.AddToUnitMagazine("USS Carl Vinson", 'AIM-7M', 272)
    SM.AddToUnitMagazine("USS Carl Vinson", 'AIM-54C', 14)
    SM.AddToUnitMagazine("USS Carl Vinson", 'AGM-45B', 88)
    SM.AddToUnitMagazine("USS Carl Vinson", 'AGM-88B', 96)
    SM.AddToUnitMagazine("USS Carl Vinson", 'AGM-84C Harpoon', 44)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Mk-46 Mod5', 127)
    SM.AddToUnitMagazine("USS Carl Vinson", 'M117', 1168)
    SM.AddToUnitMagazine("USS Carl Vinson", 'M118', 287)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Mk-82', 1677)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Mk-83', 1114)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Mk-84', 377)
    SM.AddToUnitMagazine("USS Carl Vinson", 'GBU-24/B', 47)
    SM.AddToUnitMagazine("USS Carl Vinson", 'GBU-24B/B', 73)
    SM.AddToUnitMagazine("USS Carl Vinson", 'B-57 Mod1 10kT', 4)
    SM.AddToUnitMagazine("USS Carl Vinson", 'B-57 Mod5 20kT', 2)
    SM.AddToUnitMagazine("USS Carl Vinson", 'FPU-6', 3)
    SM.AddToUnitMagazine("USS Carl Vinson", '370 gallon wing tank', 4)
    SM.AddToUnitMagazine("USS Carl Vinson", '20mm PGU', 1438)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Chaff-1', 3154)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Flare-1', 3154)
    SM.AddToUnitMagazine("USS Carl Vinson", 'LOFAR (85) Sonobuoy', 491)
    SM.AddToUnitMagazine("USS Carl Vinson", 'DICASS (85) Sonobuoy', 491)
    SM.AddToUnitMagazine("USS Carl Vinson", 'DIFAR (85) Sonobuoy', 1473)
    SM.AddToUnitMagazine("USS Carl Vinson", 'RIM-7P(v1)', 94)
    SM.AddToUnitMagazine("USS Carl Vinson", '20mm mark 244-0 ELC', 2092)
    UI.SetSensorState(5, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.089928, 1.031181, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 1', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 2', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 3', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 4', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 5', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 6', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 7', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 8', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 9', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 10','32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 11', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 12', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 1', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 2', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 3', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 4', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 5', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 6', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 7', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 8', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 9', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 10', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 11', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Sundown 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Sundown 12', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 1', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 2', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 3', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 4', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 5', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 6', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 7', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 8', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 9', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 10', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 11', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Warhawk 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 12', '10 Mk-82;2 AGM-88B;2 370 gallon wing tank;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 1', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 2', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 3', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 4', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 5', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 6', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 7', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 8', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 9', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 10', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 11', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E Corsair II', 'Mace 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 12', '10 Mk-82;4 Mk-82;10 Mk-82;2 AIM-9M;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E', 'Viceroy 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 1', '1 GBU-24B/B;1 300 gallon wing tank;1 GBU-24B/B;1 300 gallon wing tank;1 GBU-24B/B;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E', 'Viceroy 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 2', '1 GBU-24B/B;1 300 gallon wing tank;1 GBU-24B/B;1 300 gallon wing tank;1 GBU-24B/B;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E', 'Viceroy 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 3', '1 GBU-24B/B;1 300 gallon wing tank;1 GBU-24B/B;1 300 gallon wing tank;1 GBU-24B/B;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E', 'Viceroy 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 4', '1 GBU-24B/B;1 300 gallon wing tank;1 GBU-24B/B;1 300 gallon wing tank;1 GBU-24B/B;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E', 'Viceroy 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 5', '1 GBU-24/B;1 GBU-24B/B;1 GBU-24/B;1 GBU-24B/B;1 GBU-24/B;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E', 'Viceroy 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 6', '1 GBU-24/B;1 GBU-24B/B;1 GBU-24/B;1 GBU-24B/B;1 GBU-24/B;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'KA-6D', 'Viceroy 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 101', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'KA-6D', 'Viceroy 102', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 102', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'KA-6D', 'Viceroy 103', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 103', '0 Empty;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'KA-6D', 'Viceroy 104', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 104', '0 Empty;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'EA-6B', 'Garudas 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Garudas 1', '2 AGM-88B;2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'EA-6B', 'Garudas 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Garudas 2', '2 AGM-88B;2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'EA-6B', 'Garudas 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Garudas 3', '2 AGM-88B;2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'EA-6B', 'Garudas 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Garudas 4', '2 AGM-88B;2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'EA-6B', 'Garudas 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Garudas 5', '2 AGM-88B;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'EA-6B', 'Garudas 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Garudas 6', '2 AGM-88B;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 1', '')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 2', '')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 3', '')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 4', '')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 5', '')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 6', '')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'S-3A', 'Dragon Fires 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Dragon Fires 1', '12 DICASS (85) Sonobuoy;12 LOFAR (85) Sonobuoy;36 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'S-3A', 'Dragon Fires 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Dragon Fires 2', '12 DICASS (85) Sonobuoy;12 LOFAR (85) Sonobuoy;36 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'S-3A', 'Dragon Fires 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Dragon Fires 3', '12 DICASS (85) Sonobuoy;12 LOFAR (85) Sonobuoy;36 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'S-3A', 'Dragon Fires 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Dragon Fires 4', '12 DICASS (85) Sonobuoy;12 LOFAR (85) Sonobuoy;36 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'S-3A', 'Dragon Fires 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Dragon Fires 5', '12 DICASS (85) Sonobuoy;12 LOFAR (85) Sonobuoy;36 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'S-3A', 'Dragon Fires 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Dragon Fires 6', '12 DICASS (85) Sonobuoy;12 LOFAR (85) Sonobuoy;36 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'S-3A', 'Dragon Fires 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Dragon Fires 7', '12 DICASS (85) Sonobuoy;12 LOFAR (85) Sonobuoy;36 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'S-3A', 'Dragon Fires 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Dragon Fires 8', '12 DICASS (85) Sonobuoy;12 LOFAR (85) Sonobuoy;36 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'SH-3H', 'Knight 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Knight 1', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (85) Sonobuoy;10 LOFAR (85) Sonobuoy;30 DIFAR (85) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'SH-3H', 'Knight 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Knight 2', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (85) Sonobuoy;10 LOFAR (85) Sonobuoy;30 DIFAR (85) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'SH-3H', 'Knight 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Knight 3', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (85) Sonobuoy;10 LOFAR (85) Sonobuoy;30 DIFAR (85) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'SH-3H', 'Knight 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Knight 4', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (85) Sonobuoy;10 LOFAR (85) Sonobuoy;30 DIFAR (85) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'SH-3H', 'Knight 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Knight 5', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (85) Sonobuoy;10 LOFAR (85) Sonobuoy;30 DIFAR (85) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'SH-3H', 'Knight 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Knight 6', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (85) Sonobuoy;10 LOFAR (85) Sonobuoy;30 DIFAR (85) Sonobuoy;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oberon SS'
    unit.unitName = "SS Onyx"
    boxes = [[4.9352, 5.1213, 58.9420, 59.0933]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -176.7)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SS Onyx", 'mk-24 Tigerfish', 13)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-3A'
    unit.unitName = "Shark Watcher 1"
    unit.SetPosition(1.568415, 58.231420, 50.0)
    unit.heading = 90.00
    unit.speed = 100.0
    unit.cost = 27000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'LOFAR (85) Sonobuoy', 12)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DICASS (85) Sonobuoy', 12)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DIFAR (85) Sonobuoy', 36)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.020667, 1.018984, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.030366, 1.012486, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-3A'
    unit.unitName = "Shark Watcher 2"
    unit.SetPosition(2.754781, 58.634438, 50.0)
    unit.heading = 90.00
    unit.speed = 100.0
    unit.cost = 27000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DIFAR Sonobuoy', 12)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DIFAR Sonobuoy', 12)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DICASS (100) Sonobuoy', 36)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-36 DST', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-36 DST', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.045355, 1.025430, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.051429, 1.020943, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'E-2C Group 0'
    unit.unitName = "Golden Hawks 6"
    unit.SetPosition(2.138336, 58.464617, 10000.0)
    unit.heading = 90.04
    unit.speed = 324.0
    unit.cost = 80000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'USS Nimitz')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tarawa LHAM'
    unit.unitName = "USS Nassau"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0348
    lat_deg = 57.296*leader_track.Lat + 0.0135
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 2, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 5, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 6, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 7, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 8, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 9, '25mm APDS', 400)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Nassau", '25mm APDS', 24000)
    SM.AddToUnitMagazine("USS Nassau", 'RIM-116A RAM', 84)
    SM.AddToUnitMagazine("USS Nassau", '20mm mark 244-0 ELC', 1046)
    UI.SetSensorState(4, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(2.481, 0.500, -0.928, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 1-1', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 1-1', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 1-2', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 1-2', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 1-3', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 1-3', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 1-4', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 1-4', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 1-5', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 1-5', '2 AIM-9X;2 AIM-9X;2 AIM-9X;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 1-6', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 1-6', '2 AIM-9X;2 AIM-9X;2 AIM-9X;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 1-7', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 1-7', '2 AIM-9X;2 AIM-9X;2 AIM-9X;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 1-8', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 1-8', '2 AIM-9X;2 AIM-9X;2 AIM-9X;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 1-9', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 1-9', '2 AIM-9X;2 AIM-9X;2 AIM-9X;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 1-10', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 1-10', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AH-64A', 'Assault Force 2-1', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 2-1', '1200 30mm M230 Chaingun Ammo;2 AGM-114 Hellfire;2 AGM-114 Hellfire;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AH-64A', 'Assault Force 2-2', 2)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 2-2', '1200 30mm M230 Chaingun Ammo;2 AGM-114 Hellfire;2 AGM-114 Hellfire;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AH-64A', 'Assault Force 2-3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 2-3', '1200 30mm M230 Chaingun Ammo;2 AGM-114 Hellfire;2 AGM-114 Hellfire;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AH-64A', 'Assault Force 2-4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 2-4', '1200 30mm M230 Chaingun Ammo;2 AGM-114 Hellfire;2 AGM-114 Hellfire;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AH-64A', 'Assault Force 2-5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 2-5', '1200 30mm M230 Chaingun Ammo;2 AGM-114 Hellfire;2 AGM-114 Hellfire;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AH-64A', 'Assault Force 2-6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 2-6', '1200 30mm M230 Chaingun Ammo;2 AGM-114 Hellfire;2 AGM-114 Hellfire;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AH-64A', 'Assault Force 2-7', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 2-7', '1200 30mm M230 Chaingun Ammo;2 AGM-114 Hellfire;2 AGM-114 Hellfire;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AH-64A', 'Assault Force 2-8', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 2-8', '1200 30mm M230 Chaingun Ammo;2 AGM-114 Hellfire;2 AGM-114 Hellfire;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AH-64A', 'Assault Force 2-9', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 2-9', '1200 30mm M230 Chaingun Ammo;2 AGM-114 Hellfire;2 AGM-114 Hellfire;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AH-64A', 'Assault Force 2-10', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 2-10', '1200 30mm M230 Chaingun Ammo;2 AGM-114 Hellfire;2 AGM-114 Hellfire;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'SH-60B', 'ASW Tarawa-1', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'ASW Tarawa-1', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'SH-60B', 'ASW Tarawa-2', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'ASW Tarawa-2', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'SH-60B', 'ASW Tarawa-3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'ASW Tarawa-3', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'SH-60B', 'ASW Tarawa-4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'ASW Tarawa-4', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'SH-60B', 'ASW Tarawa-5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'ASW Tarawa-5', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'SH-60B', 'ASW Tarawa-6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'ASW Tarawa-6', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'SH-60B', 'ASW Tarawa-7', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'ASW Tarawa-7', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'SH-60B', 'ASW Tarawa-8', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'ASW Tarawa-8', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'SH-60B', 'ASW Tarawa-9', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'ASW Tarawa-9', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'SH-60B', 'ASW Tarawa-10', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'ASW Tarawa-10', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 3-1', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 3-1', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 3-2', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 3-2', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 3-3', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 3-3', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 3-4', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 3-4', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 3-5', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 3-5', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 3-6', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 3-6', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 3-7', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 3-7', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('USS Nassau', 'AV-8B Harrier II', 'Assault Force 3-8', 1)
    SM.SetFlightDeckUnitLoadout('USS Nassau', 'Assault Force 3-8', '2 AIM-9X;0 Empty;0 Empty;0 Empty;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ticonderoga CG Baseline 1'
    unit.unitName = "USS Vincennes"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1041
    lat_deg = 57.296*leader_track.Lat + 0.0075
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-66M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 7, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Vincennes", 'Fuel', 56161)
    SM.AddToUnitMagazine("USS Vincennes", 'Mk-46 Mod5', 46)
    SM.AddToUnitMagazine("USS Vincennes", 'AGM-114 Hellfire', 16)
    SM.AddToUnitMagazine("USS Vincennes", '120 gallon tank', 4)
    SM.AddToUnitMagazine("USS Vincennes", 'Chaff-1', 75)
    SM.AddToUnitMagazine("USS Vincennes", 'Flare-1', 75)
    SM.AddToUnitMagazine("USS Vincennes", 'LOFAR (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("USS Vincennes", 'DICASS (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("USS Vincennes", 'DIFAR (85) Sonobuoy', 608)
    SM.AddToUnitMagazine("USS Vincennes", 'RIM-66L', 64)
    SM.AddToUnitMagazine("USS Vincennes", '20mm Mark 149-4', 970)
    SM.AddToUnitMagazine("USS Vincennes", '127mm mk 80 HE-PD mk 67', 1200)
    UI.SetSensorState(5, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(6.039, 1.530, 1.431, 0.279)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Vincennes', 'SH-60B', 'Tico Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Vincennes', 'Tico Seahawk 1', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Vincennes', 'SH-60B', 'Tico Seahawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Vincennes', 'Tico Seahawk 2', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;15 DICASS (100) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Spruance DDG VLS'
    unit.unitName = "USS Hayler"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0023
    lat_deg = 57.296*leader_track.Lat + 0.1064
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RUM-139 Mod4 ASROC', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'BGM-109 TASM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'BGM-109 TLAM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'RGM-84D Harpoon', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Hayler", 'Fuel', 65139)
    SM.AddToUnitMagazine("USS Hayler", 'Mk-46 Mod5', 35)
    SM.AddToUnitMagazine("USS Hayler", '120 gallon tank', 4)
    SM.AddToUnitMagazine("USS Hayler", 'AGM-114 Hellfire', 16)
    SM.AddToUnitMagazine("USS Hayler", 'Flare-1', 100)
    SM.AddToUnitMagazine("USS Hayler", 'Chaff-1', 100)
    SM.AddToUnitMagazine("USS Hayler", 'LOFAR (85) Sonobuoy', 263)
    SM.AddToUnitMagazine("USS Hayler", 'DICASS (85) Sonobuoy', 263)
    SM.AddToUnitMagazine("USS Hayler", 'DIFAR (85) Sonobuoy', 788)
    SM.AddToUnitMagazine("USS Hayler", 'RUM-139 Mod4 ASROC', 15)
    SM.AddToUnitMagazine("USS Hayler", 'BGM-109 TASM', 5)
    SM.AddToUnitMagazine("USS Hayler", 'BGM-109 TLAM', 38)
    SM.AddToUnitMagazine("USS Hayler", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Hayler", '127mm mk 80 HE-PD mk 67', 1200)
    UI.SetSensorState(5, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(11.518, 2.917, -0.005, 0.165)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Hayler', 'SH-60B', 'Spruance VLS DDG Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Hayler', 'Spruance VLS DDG Seahawk 1', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Hayler', 'SH-60B', 'Spruance VLS DDG Seahawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Hayler', 'Spruance VLS DDG Seahawk 2', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;15 DICASS (100) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oliver Hazard Perry FFGHM'
    unit.unitName = "USS Taylor"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.2075
    lat_deg = 57.296*leader_track.Lat + 0.1165
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66L', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Taylor", 'Fuel', 28080)
    SM.AddToUnitMagazine("USS Taylor", 'Mk-46 Mod5', 25)
    SM.AddToUnitMagazine("USS Taylor", 'AGM-114 Hellfire', 8)
    SM.AddToUnitMagazine("USS Taylor", '120 gallon tank', 2)
    SM.AddToUnitMagazine("USS Taylor", 'Chaff-1', 50)
    SM.AddToUnitMagazine("USS Taylor", 'Flare-1', 50)
    SM.AddToUnitMagazine("USS Taylor", 'DICASS (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Taylor", 'LOFAR (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Taylor", 'DIFAR (85) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS Taylor", 'RIM-66L', 35)
    SM.AddToUnitMagazine("USS Taylor", 'RGM-84D Harpoon', 4)
    SM.AddToUnitMagazine("USS Taylor", '20mm mark 244-0 ELC', 523)
    SM.AddToUnitMagazine("USS Taylor", '76mm HE-MOM', 240)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(17.835, 1.748, 0.757, 0.178)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Taylor', 'SH-60B', 'Perry FFG Seahawk 201', 1)
    SM.SetFlightDeckUnitLoadout('USS Taylor', 'Perry FFG Seahawk 201', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;15 DICASS (100) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ticonderoga CG Baseline 1'
    unit.unitName = "USS Yorktown"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1214
    lat_deg = 57.296*leader_track.Lat + 0.0688
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-66M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 7, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Yorktown", 'Fuel', 56161)
    SM.AddToUnitMagazine("USS Yorktown", 'Mk-46 Mod5', 46)
    SM.AddToUnitMagazine("USS Yorktown", 'AGM-114 Hellfire', 16)
    SM.AddToUnitMagazine("USS Yorktown", '120 gallon tank', 4)
    SM.AddToUnitMagazine("USS Yorktown", 'Chaff-1', 75)
    SM.AddToUnitMagazine("USS Yorktown", 'Flare-1', 75)
    SM.AddToUnitMagazine("USS Yorktown", 'LOFAR (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("USS Yorktown", 'DICASS (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("USS Yorktown", 'DIFAR (85) Sonobuoy', 608)
    SM.AddToUnitMagazine("USS Yorktown", 'RIM-66L', 64)
    SM.AddToUnitMagazine("USS Yorktown", '20mm Mark 149-4', 970)
    SM.AddToUnitMagazine("USS Yorktown", '127mm mk 80 HE-PD mk 67', 1200)
    UI.SetSensorState(5, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(10.820, 3.927, 0.799, 0.389)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Yorktown', 'SH-60B', 'Tico Seahawk 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Yorktown', 'Tico Seahawk 101', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Yorktown', 'SH-60B', 'Tico Seahawk 102', 1)
    SM.SetFlightDeckUnitLoadout('USS Yorktown', 'Tico Seahawk 102', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;15 DICASS (100) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oliver Hazard Perry FFGHM'
    unit.unitName = "USS Rentz"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.2641
    lat_deg = 57.296*leader_track.Lat + -0.0717
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66L', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Rentz", 'Fuel', 28080)
    SM.AddToUnitMagazine("USS Rentz", 'Mk-46 Mod5', 25)
    SM.AddToUnitMagazine("USS Rentz", 'AGM-114 Hellfire', 8)
    SM.AddToUnitMagazine("USS Rentz", '120 gallon tank', 2)
    SM.AddToUnitMagazine("USS Rentz", 'Chaff-1', 50)
    SM.AddToUnitMagazine("USS Rentz", 'Flare-1', 50)
    SM.AddToUnitMagazine("USS Rentz", 'DICASS (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Rentz", 'LOFAR (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Rentz", 'DIFAR (85) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS Rentz", 'RIM-66L', 35)
    SM.AddToUnitMagazine("USS Rentz", 'RGM-84D Harpoon', 4)
    SM.AddToUnitMagazine("USS Rentz", '20mm mark 244-0 ELC', 523)
    SM.AddToUnitMagazine("USS Rentz", '76mm HE-MOM', 240)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(16.399, 8.193, 2.026, 0.191)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Rentz', 'SH-60B', 'Perry FFG Seahawk 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Rentz', 'Perry FFG Seahawk 101', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;15 DICASS (100) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Spruance DDG VLS'
    unit.unitName = "USS Spruance"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1962
    lat_deg = 57.296*leader_track.Lat + 0.1243
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RUM-139 Mod4 ASROC', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'BGM-109 TASM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'BGM-109 TLAM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'RGM-84D Harpoon', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Spruance", 'Fuel', 65139)
    SM.AddToUnitMagazine("USS Spruance", 'Mk-46 Mod5', 35)
    SM.AddToUnitMagazine("USS Spruance", '120 gallon tank', 4)
    SM.AddToUnitMagazine("USS Spruance", 'AGM-114 Hellfire', 16)
    SM.AddToUnitMagazine("USS Spruance", 'Chaff-1', 100)
    SM.AddToUnitMagazine("USS Spruance", 'Flare-1', 100)
    SM.AddToUnitMagazine("USS Spruance", 'LOFAR (85) Sonobuoy', 263)
    SM.AddToUnitMagazine("USS Spruance", 'DICASS (85) Sonobuoy', 263)
    SM.AddToUnitMagazine("USS Spruance", 'DIFAR (85) Sonobuoy', 788)
    SM.AddToUnitMagazine("USS Spruance", 'RUM-139 Mod4 ASROC', 15)
    SM.AddToUnitMagazine("USS Spruance", 'BGM-109 TASM', 5)
    SM.AddToUnitMagazine("USS Spruance", 'BGM-109 TLAM', 38)
    SM.AddToUnitMagazine("USS Spruance", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Spruance", '127mm mk 80 HE-PD mk 67', 1200)
    UI.SetSensorState(5, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(17.000, 3.905, -0.791, 0.448)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Spruance', 'SH-60B', 'Spruance VLS DDG Seahawk 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Spruance', 'Spruance VLS DDG Seahawk 101', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Spruance', 'SH-60B', 'Spruance VLS DDG Seahawk 102', 1)
    SM.SetFlightDeckUnitLoadout('USS Spruance', 'Spruance VLS DDG Seahawk 102', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;15 DICASS (100) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oliver Hazard Perry FFGHM'
    unit.unitName = "USS McInerney"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2208
    lat_deg = 57.296*leader_track.Lat + -0.1040
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66L', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS McInerney", 'Fuel', 28080)
    SM.AddToUnitMagazine("USS McInerney", 'Mk-46 Mod5', 25)
    SM.AddToUnitMagazine("USS McInerney", 'AGM-114 Hellfire', 8)
    SM.AddToUnitMagazine("USS McInerney", '120 gallon tank', 2)
    SM.AddToUnitMagazine("USS McInerney", 'Chaff-1', 50)
    SM.AddToUnitMagazine("USS McInerney", 'Flare-1', 50)
    SM.AddToUnitMagazine("USS McInerney", 'DICASS (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS McInerney", 'LOFAR (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS McInerney", 'DIFAR (85) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS McInerney", 'RIM-66L', 35)
    SM.AddToUnitMagazine("USS McInerney", 'RGM-84D Harpoon', 4)
    SM.AddToUnitMagazine("USS McInerney", '20mm mark 244-0 ELC', 523)
    SM.AddToUnitMagazine("USS McInerney", '76mm HE-MOM', 240)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(16.852, 3.153, -2.394, 0.476)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS McInerney', 'SH-60B', 'Perry FFG Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS McInerney', 'Perry FFG Seahawk 1', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;15 DICASS (100) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Sacramento AOEHM'
    unit.unitName = "Sacramento AOEHM"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0091
    lat_deg = 57.296*leader_track.Lat + -0.0865
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-7P(v1)', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Sacramento AOEHM", '20mm mark 244-0 ELC', 1046)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(9.515, 1.790, 3.073, 0.211)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Sacramento AOEHM', 'SH-60B', 'Sacramento ASW-1', 2)
    SM.SetFlightDeckUnitLoadout('Sacramento AOEHM', 'Sacramento ASW-1', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('Sacramento AOEHM', 'SH-60B', 'Sacramento ASW-2', 1)
    SM.SetFlightDeckUnitLoadout('Sacramento AOEHM', 'Sacramento ASW-2', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('Sacramento AOEHM', 'SH-60B', 'Sacramento ASW-3', 1)
    SM.SetFlightDeckUnitLoadout('Sacramento AOEHM', 'Sacramento ASW-3', '0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;0 Empty;15 DICASS (100) Sonobuoy;')
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PMU'
    unit.unitName = "SA-10B"
    unit.SetPosition(5.216666, 59.193473, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55RUD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10B", '5V55RUD', 72)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Airfield Ammo Dump"
    unit.SetPosition(5.322377, 59.328920, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fuel Tanks'
    unit.unitName = "Airfield Fuel Depot"
    unit.SetPosition(5.336815, 59.320498, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-125 Pechora-2M'
    unit.unitName = "S-125"
    unit.SetPosition(5.343920, 59.332072, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-601P', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("S-125", 'V-601P', 16)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-75M Dvina'
    unit.unitName = "SA-2 (1)"
    unit.SetPosition(5.291494, 59.334650, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-750V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-750V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-750V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-750V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-750V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-750V', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-2 (1)", 'V-750V', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-125M Neva-M'
    unit.unitName = "SA-3 (1)"
    unit.SetPosition(5.281410, 59.303768, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-601', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-601', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-601', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-601', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-3 (1)", 'V-601', 16)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Forward Observation Post'
    unit.unitName = "Northern Observation Post"
    unit.SetPosition(5.430723, 59.226647, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Forward Observation Post'
    unit.unitName = "Southern Observation Post"
    unit.SetPosition(5.628279, 59.020669, 83.5)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ'
    unit.unitName = "Soviet HQ"
    unit.SetPosition(5.939567, 59.180868, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SAM Site S-300"
    unit.SetPosition(5.731240, 59.139902, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SAM Site S-300", '5V55R', 72)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-125 Pechora-2M'
    unit.unitName = "SAM Site S-125"
    unit.SetPosition(5.610346, 58.960509, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-601P', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SAM Site S-125", 'V-601P', 16)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammunition Bunker"
    unit.SetPosition(5.942604, 59.131766, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fuel Tanks'
    unit.unitName = "Fuel Depot"
    unit.SetPosition(5.911206, 59.226648, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Communications Station'
    unit.unitName = "Communications Station"
    unit.SetPosition(6.059372, 59.212782, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-3(24)'
    unit.unitName = "SSC-3"
    unit.SetPosition(5.529501, 59.062381, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'P-20K', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SSC-3", 'P-20K', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-3(36)'
    unit.unitName = "SSC-3 "
    unit.SetPosition(5.260039, 59.175769, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'P-20K', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SSC-3 ", 'P-20K', 36)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-80 MBT'
    unit.unitName = "T-80 MBT (1)"
    unit.SetPosition(5.628279, 59.122541, -0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Russian Airfield"
    unit.SetPosition(5.322434, 59.320556, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Russian Airfield", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Russian Airfield", '1520 Liter Tank', 520)
    SM.AddToUnitMagazine("Russian Airfield", 'FAB-100', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'FAB-250', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'FAB-500', 662)
    SM.AddToUnitMagazine("Russian Airfield", 'Flare-1', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'KAB-500L', 638)
    SM.AddToUnitMagazine("Russian Airfield", 'Kh-59MK', 538)
    SM.AddToUnitMagazine("Russian Airfield", 'R-27R', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'R-27T', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'R-60', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'R-60M', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'R-60MK', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'R-60T', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'R-60U', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'R-73', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'R-73M', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'R-73M2', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'R-73U', 600)
    SM.AddToUnitMagazine("Russian Airfield", 'TN-1000', 600)
    SM.AddToUnitMagazine("Russian Airfield", '3000 liter tank', 562)
    SM.AddToUnitMagazine("Russian Airfield", '23mm AM-23', 500)
    SM.AddToUnitMagazine("Russian Airfield", 'Chaff-1', 500)
    SM.AddToUnitMagazine("Russian Airfield", 'Kh-29T', 500)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-1', 2)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-1', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-2', 2)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-2', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-3', 2)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-3', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-4', 2)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-4', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-5', 2)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-5', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-6', 2)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-6', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-7', 2)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-7', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-8', 2)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-8', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-9', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-9', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-10', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-10', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-11', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-11', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-12', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-12', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-13', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-13', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-14', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-14', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-15', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-15', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-16', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-16', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-17', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-17', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-18', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-18', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-19', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-19', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-20', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-20', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-21', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-21', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-22', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-22', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-23', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-23', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'MiG-29', 'Daemon-24', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Daemon-24', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'A-50', 'Spy-1', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Spy-1', '')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'A-50', 'Spy-2', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Spy-2', '')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'A-50', 'Spy-3', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Spy-3', '')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-1', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-1', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-2', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-2', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-3', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-3', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-4', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-4', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-5', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-5', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-6', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-6', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-7', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-7', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-8', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-8', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-9', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-9', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-10', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-10', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-11', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-11', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-12', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-12', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-13', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-13', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-14', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-14', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-15', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-15', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-16', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-16', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-17', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-17', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-18', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-18', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-19', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-19', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-20', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-20', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-21', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-21', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-22', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-22', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-23', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-23', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-24', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-24', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-25', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-25', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-26', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-26', '2 KAB-500L;2 Kh-59MK;2 KAB-500L;2 KAB-500L;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-27', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-27', '2 KAB-500L;2 Kh-59MK;2 KAB-500L;2 KAB-500L;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-28', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-28', '2 KAB-500L;2 Kh-59MK;2 KAB-500L;2 KAB-500L;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-29', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-29', '2 KAB-500L;2 Kh-59MK;2 KAB-500L;2 KAB-500L;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-30', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-30', '2 KAB-500L;2 Kh-59MK;2 KAB-500L;2 KAB-500L;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Airfield', 'Su-24M', 'Thunder-31', 1)
    SM.SetFlightDeckUnitLoadout('Russian Airfield', 'Thunder-31', '2 KAB-500L;2 Kh-59MK;2 KAB-500L;2 KAB-500L;6 23mm AM-23;25 Flare-1;25 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Daemon-24')
    FP.AddAircraftToMission(mission_id, 'Daemon-23')
    FP.AddAircraftToMission(mission_id, 'Daemon-22')
    FP.AddAircraftToMission(mission_id, 'Daemon-21')
    FP.AddAircraftToMission(mission_id, 'Daemon-20')
    FP.AddAircraftToMission(mission_id, 'Daemon-19')
    FP.AddAircraftToMission(mission_id, 'Daemon-18')
    FP.AddAircraftToMission(mission_id, 'Daemon-17')
    FP.AddAircraftToMission(mission_id, 'Daemon-16')
    FP.AddAircraftToMission(mission_id, 'Daemon-15')
    FP.AddAircraftToMission(mission_id, 'Daemon-14')
    FP.AddAircraftToMission(mission_id, 'Daemon-13')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0028132,-0.0027772,0.0038155,-0.0031584,-0.0017914,-0.0058619,-0.0011941,-0.0045514,')
    FP.SetMissionPatrolAnchor(mission_id, 'Russian Airfield', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.0938940, 1.0363390, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0861880, 1.0352150, 2000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RTB')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0928640, 1.0352170, 10000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Daemon-9')
    FP.AddAircraftToMission(mission_id, 'Daemon-10')
    FP.AddAircraftToMission(mission_id, 'Daemon-11')
    FP.AddAircraftToMission(mission_id, 'Daemon-12')
    FP.AddAircraftToMission(mission_id, 'Daemon-8')
    FP.AddAircraftToMission(mission_id, 'Daemon-7')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0952162,1.0273658,0.0870534,1.0269012,0.0806091,1.0281401,0.0791484,1.0308833,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0938940, 1.0363390, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0881750, 1.0290610, 2000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RTB')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0936960, 1.0351100, 10000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Daemon-1')
    FP.AddAircraftToMission(mission_id, 'Daemon-2')
    FP.AddAircraftToMission(mission_id, 'Daemon-3')
    FP.AddAircraftToMission(mission_id, 'Daemon-4')
    FP.AddAircraftToMission(mission_id, 'Daemon-5')
    FP.AddAircraftToMission(mission_id, 'Daemon-6')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0900056,1.0343639,0.0906743,1.0328274,0.0965342,1.0310379,0.0987162,1.0318965,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0938940, 1.0363390, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0931560, 1.0335870, 2000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RTB')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0931530, 1.0351530, 10000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Spy-1')
    FP.AddAircraftToMission(mission_id, 'Spy-2')
    FP.AddAircraftToMission(mission_id, 'Spy-3')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R3.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0930051,1.0344079,0.0907395,1.0363024,0.0919273,1.0335895,0.0969205,1.0332195,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0938940, 1.0363390, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0934890, 1.0344300, 2000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RTB')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0931810, 1.0351360, 10000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Thunder-1')
    FP.AddAircraftToMission(mission_id, 'Thunder-17')
    FP.AddAircraftToMission(mission_id, 'Thunder-2')
    FP.AddAircraftToMission(mission_id, 'Thunder-3')
    FP.AddAircraftToMission(mission_id, 'Thunder-4')
    FP.AddAircraftToMission(mission_id, 'Thunder-5')
    FP.AddAircraftToMission(mission_id, 'Thunder-6')
    FP.AddAircraftToMission(mission_id, 'Thunder-7')
    FP.AddAircraftToMission(mission_id, 'Thunder-8')
    FP.AddAircraftToMission(mission_id, 'Thunder-9')
    FP.AddAircraftToMission(mission_id, 'Thunder-10')
    FP.AddAircraftToMission(mission_id, 'Thunder-11')
    FP.AddAircraftToMission(mission_id, 'Thunder-12')
    FP.AddAircraftToMission(mission_id, 'Thunder-13')
    FP.AddAircraftToMission(mission_id, 'Thunder-14')
    FP.AddAircraftToMission(mission_id, 'Thunder-15')
    FP.AddAircraftToMission(mission_id, 'Thunder-16')
    FP.AddAircraftToMission(mission_id, 'Thunder-18')
    FP.AddAircraftToMission(mission_id, 'Thunder-19')
    FP.AddAircraftToMission(mission_id, 'Thunder-20')
    FP.AddAircraftToMission(mission_id, 'Thunder-21')
    FP.AddAircraftToMission(mission_id, 'Thunder-22')
    FP.AddAircraftToMission(mission_id, 'Thunder-23')
    FP.AddAircraftToMission(mission_id, 'Thunder-24')
    FP.SetMissionLaunchTime(mission_id, '04:00:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 8)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0527773,1.0206076,0.0443912,1.0247527,0.0411261,1.0253294,0.0527430,1.0185891,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0938940, 1.0363390, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0524200, 1.0224890, 2000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RTB')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0511620, 1.0214731, 0.0, 0.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.0926490, 1.0344760, 10000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 3, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Thunder-25')
    FP.AddAircraftToMission(mission_id, 'Thunder-26')
    FP.AddAircraftToMission(mission_id, 'Thunder-27')
    FP.AddAircraftToMission(mission_id, 'Thunder-28')
    FP.AddAircraftToMission(mission_id, 'Thunder-29')
    FP.AddAircraftToMission(mission_id, 'Thunder-30')
    FP.AddAircraftToMission(mission_id, 'Thunder-31')
    FP.SetMissionLaunchTime(mission_id, '04:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0882263,1.0267341,0.0752346,1.0330738,0.0735849,1.0324026,0.0817648,1.0272639,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0938940, 1.0363390, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0807340, 1.0304250, 2000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RTB')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0931410, 1.0352629, 10000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 971 Shchuka-B'
    unit.unitName = "K-391 Kit"
    unit.SetPosition(2.872008, 58.801513, -79.9)
    unit.heading = 90.00
    unit.speed = 5.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Igla-M SAM', 18)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-391 Kit", 'SET-65M', 8)
    SM.AddToUnitMagazine("K-391 Kit", '65-76 Kit', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.045160, 1.021847, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.047805, 1.019346, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.058287, 1.019754, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.091890, 1.023940, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671 Yorzh'
    unit.unitName = "K-462"
    boxes = [[0.9290, 2.3067, 57.9327, 58.2864]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -64.5)
    unit.heading = 90.00
    unit.speed = 15.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-462", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-462", '53-65M', 6)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.031796, 1.017487, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.043356, 1.021581, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.060741, 1.024023, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.083415, 1.029191, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 945 Barrakuda'
    unit.unitName = "K-419 Kuzbass"
    boxes = [[3.8206, 4.1561, 58.8079, 59.0427]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -100.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'RPK-7 Veter', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RPK-7 Veter', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-419 Kuzbass", 'SET-65M', 6)
    SM.AddToUnitMagazine("K-419 Kuzbass", '65-76 Kit', 6)
    SM.AddToUnitMagazine("K-419 Kuzbass", 'RPK-7 Veter', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.SetSensorState(5, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.057504, 1.023838, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.044082, 1.019907, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.087874, 1.027055, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 61 Kashin'
    unit.unitName = "DDG Kashin (1)"
    unit.SetPosition(3.551250, 58.816123, 0.0)
    unit.heading = 90.00
    unit.speed = 9.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-600', 16)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-600', 16)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Kh-35', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("DDG Kashin (1)", '53-65M', 30)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.067868, 1.027590, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.086487, 1.029087, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.092627, 1.028796, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 775  Ropucha'
    unit.unitName = "Ropucha LSTM"
    unit.SetPosition(5.408149, 59.140131, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 2, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 3, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M32 Strela 2', 32)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Ropucha LSTM", '57mm Tracer-FRAG', 2800)
    SM.AddToUnitMagazine("Ropucha LSTM", '30mm OF-84 HE-FRAG AK-630M', 472)
    SM.AddToUnitMagazine("Ropucha LSTM", '9M32 Strela 2', 64)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1559V Morskoy Prostor'
    unit.unitName = "Boris Chilikin AOR"
    unit.SetPosition(5.443099, 59.149760, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 1, '57mm Tracer-FRAG', 200)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Boris Chilikin AOR", '57mm Tracer-FRAG', 2800)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Oil Tanker"
    unit.SetPosition(5.444016, 59.134290, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1144 Orlan'
    unit.unitName = "Kirov CGHMN"
    unit.SetPosition(4.928583, 59.576442, 0.0)
    unit.heading = 164.38
    unit.speed = 24.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55RM', 96)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M330 Kinzhal', 96)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 6, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 7, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 8, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 9, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 10, '3M45 Granit', 20)
    SM.SetUnitLauncherItem(unit.unitName, 11, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 12, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 13, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 14, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 15, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 16, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 17, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 18, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 19, '53-65M', 5)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Kirov CGHMN", 'Fuel', 68850)
    SM.AddToUnitMagazine("Kirov CGHMN", 'AT-1', 52)
    SM.AddToUnitMagazine("Kirov CGHMN", 'DICASS (80) Sonobuoy', 350)
    SM.AddToUnitMagazine("Kirov CGHMN", 'LOFAR (80) Sonobuoy', 350)
    SM.AddToUnitMagazine("Kirov CGHMN", 'DIFAR (80) Sonobuoy', 982)
    SM.AddToUnitMagazine("Kirov CGHMN", '30mm OF-84 HE-FRAG AK-630M', 1416)
    SM.AddToUnitMagazine("Kirov CGHMN", '9M311 Kashtan', 144)
    SM.AddToUnitMagazine("Kirov CGHMN", '130mm F-44 HE', 500)
    SM.AddToUnitMagazine("Kirov CGHMN", '53-65M', 30)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.085252, 1.036993, 12.568395, 20.000000)
    UI.AddNavWaypointAdvanced(0.087435, 1.035369, 0.000000, 15.000000)
    UI.AddNavWaypointAdvanced(0.087756, 1.032990, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.089425, 1.030627, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Kirov CGHMN', 'Ka-27A', 'Orlan Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Kirov CGHMN', 'Orlan Ka-27 1', '5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kirov CGHMN', 'Ka-27A', 'Orlan Ka-27 2', 1)
    SM.SetFlightDeckUnitLoadout('Kirov CGHMN', 'Orlan Ka-27 2', '5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kirov CGHMN', 'Ka-27A', 'Orlan Ka-27 3', 1)
    SM.SetFlightDeckUnitLoadout('Kirov CGHMN', 'Orlan Ka-27 3', '5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 APR-2E;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135M Burevestnik-M'
    unit.unitName = "Krivak II FFM"
    unit.SetPosition(5.353603, 59.118015, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 1, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RPK-3 Metel', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Krivak II FFM", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Krivak II FFM", '53-65M', 8)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.092748, 1.032172, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.093964, 1.031293, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.031687')
    BB.Write('StationLongitude', '0.092399')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877M Paltus'
    unit.unitName = "B-404"
    unit.SetPosition(5.283702, 59.097617, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M32M Strela 3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-404", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-404", '53-65M', 6)
    SM.AddToUnitMagazine("B-404", '9M32M Strela 3', 8)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.092140, 1.031986, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.093405, 1.031192, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    UI.AddTask('SubPatrol', 1.000000, 0)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.030902')
    BB.Write('StationLongitude', '0.092399')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'A-50'
    unit.unitName = "Watcher 1"
    unit.SetPosition(5.080474, 59.427125, 10000.0)
    unit.heading = 90.00
    unit.speed = 100.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.083740, 1.036736, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.081781, 1.039817, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.083583, 1.042330, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.087894, 1.041884, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.033181')
    BB.Write('StationLongitude', '0.083584')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'A-50'
    unit.unitName = "Watcher 2"
    unit.SetPosition(6.109392, 56.358421, 10000.0)
    unit.heading = 90.00
    unit.speed = 100.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.102079, 0.989267, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.102538, 0.998510, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.101161, 1.008771, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.101926, 1.016912, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.986623')
    BB.Write('StationLongitude', '0.087021')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-80 MBT'
    unit.unitName = "T-80 MBT (2)"
    unit.SetPosition(5.593443, 59.097102, 103.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ka-27A'
    unit.unitName = "Shark Hunter 1"
    unit.SetPosition(5.207212, 59.096815, 50.0)
    unit.heading = 90.00
    unit.speed = 108.8
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DICASS (80) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'LOFAR (80) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DIFAR (80) Sonobuoy', 14)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'AT-1', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.090214, 1.032113, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.090342, 1.031238, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ka-27A'
    unit.unitName = "Shark Hunter 2"
    unit.SetPosition(5.268232, 59.002392, 50.0)
    unit.heading = 90.00
    unit.speed = 108.8
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DICASS (80) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'LOFAR (80) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DIFAR (80) Sonobuoy', 14)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'AT-1', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.091755, 1.030330, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.093456, 1.030082, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ka-27A'
    unit.unitName = "Shark Hunter 3"
    unit.SetPosition(5.214374, 59.059802, 50.0)
    unit.heading = 90.00
    unit.speed = 108.8
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DICASS (80) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'LOFAR (80) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DIFAR (80) Sonobuoy', 14)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'AT-1', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.090567, 1.031172, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.091273, 1.030297, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-3(24)'
    unit.unitName = "SSC-4"
    unit.SetPosition(5.518328, 59.083122, 1.7)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'P-20K', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SSC-4", 'P-20K', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-80 MBT'
    unit.unitName = "T-80 MBT (3)"
    unit.SetPosition(5.532480, 59.101342, 114.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V Shilka'
    unit.unitName = "ZSU-23 (1)"
    unit.SetPosition(5.281124, 59.320784, -0.0)
    unit.heading = 90.00
    unit.speed = 19.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V Shilka'
    unit.unitName = "ZSU-23 (2)"
    unit.SetPosition(5.318767, 59.345650, 22.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V Shilka'
    unit.unitName = "ZSU-23 (3)"
    unit.SetPosition(5.350567, 59.321532, 32.9)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V Shilka'
    unit.unitName = "ZSI-23 (4)"
    unit.SetPosition(5.320830, 59.297121, 40.1)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-75M2 Volkhov'
    unit.unitName = "SA-2E"
    unit.SetPosition(5.897397, 59.167576, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-759', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-759', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-759', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-759', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-759', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-759', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-2E", 'V-759', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PMU-1'
    unit.unitName = "SA-20A"
    unit.SetPosition(6.015083, 59.197197, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55RUD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-20A", '5V55RUD', 72)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4MZ Biryusa'
    unit.unitName = "ZSU-23-4MZ (1)"
    unit.SetPosition(6.020984, 59.180295, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PT-1A'
    unit.unitName = "SA-10A"
    unit.SetPosition(5.322663, 59.310471, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55K', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55K', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55K', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55K', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10A", '5V55K', 72)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 61 Kashin'
    unit.unitName = "DDG Kashin (2)"
    boxes = [[-0.5057, -0.4657, 57.6711, 57.7111]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 20.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-600', 16)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-600', 16)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Kh-35', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("DDG Kashin (2)", '53-65M', 30)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.067868, 1.027590, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.086487, 1.029087, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.092627, 1.028796, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671 Yorzh'
    unit.unitName = "K-53"
    unit.SetPosition(3.311238, 58.669733, -63.3)
    unit.heading = 90.00
    unit.speed = 6.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-53", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-53", '53-65M', 6)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.053327, 1.025336, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.058715, 1.020468, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Fleet Oiler"
    UI = SM.GetUnitInterface('Kirov CGHMN')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0331
    lat_deg = 57.296*leader_track.Lat + 0.0106
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kirov CGHMN')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(2.036, 0.326, -1.632, 0.536)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1134B Berkut B'
    unit.unitName = "Kara CGHM"
    UI = SM.GetUnitInterface('Kirov CGHMN')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0016
    lat_deg = 57.296*leader_track.Lat + 0.0434
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 8, '76.2mm ZS-63 AA', 200)
    SM.SetUnitLauncherItem(unit.unitName, 9, '76.2mm ZS-63 AA', 200)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'RPK-3 Metel', 8)
    SM.SetUnitLauncherItem(unit.unitName, 11, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 12, 'SAET-60M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kirov CGHMN')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(4.591, 1.076, -2.831, 0.259)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Kara CGHM', 'Ka-27A', 'Kara ASW-1', 2)
    SM.SetFlightDeckUnitLoadout('Kara CGHM', 'Kara ASW-1', '5 DICASS Sonobuoy;0 Empty;14 DICASS (100) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kara CGHM', 'Ka-27A', 'Kara ASW-2', 1)
    SM.SetFlightDeckUnitLoadout('Kara CGHM', 'Kara ASW-2', '5 DICASS Sonobuoy;0 Empty;14 DICASS (100) Sonobuoy;2 APR-2E;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12341 Ovod-1'
    unit.unitName = "Nanuchka III FSGM"
    UI = SM.GetUnitInterface('Kirov CGHMN')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0772
    lat_deg = 57.296*leader_track.Lat + 0.0019
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Nanuchka III FSGM", '9M33M', 20)
    SM.AddToUnitMagazine("Nanuchka III FSGM", '30mm OF-84 HE-FRAG AK-630M76.2mm OS-62 FRAG', 152)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kirov CGHMN')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(4.036, 1.041, -1.235, 0.242)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1155 Fregat'
    unit.unitName = "Admiral Kharlamov"
    UI = SM.GetUnitInterface('Kirov CGHMN')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0000
    lat_deg = 57.296*leader_track.Lat + -0.0404
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M330 Kinzhal', 64)
    SM.SetUnitLauncherItem(unit.unitName, 1, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 2, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'RPK-3 Metel', 8)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Admiral Kharlamov", 'Fuel', 45900)
    SM.AddToUnitMagazine("Admiral Kharlamov", 'AT-1', 22)
    SM.AddToUnitMagazine("Admiral Kharlamov", 'DICASS (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Kharlamov", 'LOFAR (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Kharlamov", 'DIFAR (80) Sonobuoy', 378)
    SM.AddToUnitMagazine("Admiral Kharlamov", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Admiral Kharlamov", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Admiral Kharlamov", '53-65M', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kirov CGHMN')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(4.764, 1.238, 0.269, 0.453)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Admiral Kharlamov', 'Ka-27A', 'Fregat Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Admiral Kharlamov', 'Fregat Ka-27 1', '5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 APR-2E;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 956 Sarych'
    unit.unitName = "Admiral Ushakov"
    UI = SM.GetUnitInterface('Kirov CGHMN')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0771
    lat_deg = 57.296*leader_track.Lat + 0.0015
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 163.18
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M317', 22)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M317', 22)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '3M80M Moskit-M', 8)
    SM.SetUnitLauncherItem(unit.unitName, 7, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 8, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 10, '53-65M', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Admiral Ushakov", 'Fuel', 45900)
    SM.AddToUnitMagazine("Admiral Ushakov", 'AT-1', 22)
    SM.AddToUnitMagazine("Admiral Ushakov", 'DICASS (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Ushakov", 'LOFAR (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Ushakov", 'DIFAR (80) Sonobuoy', 378)
    SM.AddToUnitMagazine("Admiral Ushakov", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Admiral Ushakov", '130mm F-44 HE', 1000)
    SM.AddToUnitMagazine("Admiral Ushakov", '53-65M', 12)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kirov CGHMN')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(4.359, 0.984, 1.858, 0.474)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Admiral Ushakov', 'Ka-27A', 'Sarych Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Admiral Ushakov', 'Sarych Ka-27 1', '5 DICASS (100) Sonobuoy;5 DICASS (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 APR-2E;')
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('USS Carl Vinson')
    goal_temp.SetQuantity(1)
    goal_2_0 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Kirov CGHMN')
    goal_temp.SetQuantity(1)
    goal_2_1 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Boris Chilikin AOR')
    goal_temp.SetQuantity(1)
    goal_2_2 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Ropucha LSTM')
    goal_temp.SetQuantity(1)
    goal_2_3 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('SSC-4')
    goal_temp.SetQuantity(1)
    goal_2_4 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('SSC-3')
    goal_temp.SetQuantity(1)
    goal_2_5 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('SSC-3 ')
    goal_temp.SetQuantity(1)
    goal_2_6 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_2_0)
    goal_temp.AddGoal(goal_2_1)
    goal_temp.AddGoal(goal_2_2)
    goal_temp.AddGoal(goal_2_3)
    goal_temp.AddGoal(goal_2_4)
    goal_temp.AddGoal(goal_2_5)
    goal_temp.AddGoal(goal_2_6)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('USS Carl Vinson')
    goal_temp.SetQuantity(1)
    goal_3_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Ropucha LSTM')
    goal_temp.SetQuantity(1)
    goal_3_1 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Boris Chilikin AOR')
    goal_temp.SetQuantity(1)
    goal_3_2 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_3_0)
    goal_temp.AddGoal(goal_3_1)
    goal_temp.AddGoal(goal_3_2)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
    SM.SetIncludeProbability('DDG Kashin (2)', 1.000000)
    SM.AddRandomBox('DDG Kashin (2)', -0.5057, -0.4657, 57.6711, 57.7111)
    SM.SetIncludeProbability('K-419 Kuzbass', 1.000000)
    SM.AddRandomBox('K-419 Kuzbass', 3.8206, 4.1561, 58.8079, 59.0427)
    SM.SetIncludeProbability('K-462', 1.000000)
    SM.AddRandomBox('K-462', 0.9290, 2.3067, 57.9327, 58.2864)
    SM.SetIncludeProbability('SS Onyx', 1.000000)
    SM.AddRandomBox('SS Onyx', 4.9352, 5.1213, 58.9420, 59.0933)
    SM.SetIncludeProbability('USS Annapolis ', 0.500000)
    SM.AddRandomBox('USS Annapolis ', 3.9922, 4.9252, 58.6336, 59.4041)
