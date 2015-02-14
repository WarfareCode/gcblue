# Created on 09/18/11 14:14:57
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Backfires and Condors\nVersion 2.0 of 2010/06/24\n\nA scenario for Global Conflicts 2.\n\nWritten by Ralf Koelbach.\nrkoelbach@yahoo.com\n\nBackfires and Condors is a classical Cold War scenario putting the Soviet \nNaval Aviation against an US CVBG near Iceland.\n\nYou are to defend your carrier group against those huge, supersonic \nRussian killer missiles.\n\nComments and critiques welcome!\n\nHave fun!\nRalf\n\n\n\n\n\n\n""")
    SM.SetScenarioName("""Backfires""")
    SM.CreateAlliance(1, 'USA')
    SM.SetAllianceDefaultCountry(1, 'USA')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 1)
    SM.CreateAlliance(3, 'Sweden')
    SM.SetAllianceDefaultCountry(3, 'Sweden')
    SM.SetAlliancePlayable(3, 1)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(1)

    SM.SetDateTime(1989,8,14,12,0,8)
    SM.SetStartTheater(-20.970835, 59.737499) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """ORDERS FOR CMDR US OPERATIONS\n\nINTELLIGENCE\n\nThe control of the GIUK Gap is vital for our efforts to win the war. At \nfirst we must neutralize Iceland, then retake it.\n\nMISSION\n\nMake best speed towards Iceland. Destroy all hostile units on your way \nand the Soviet facilities at Iceland.\n\nEXECUTION\n\nProceed with care. Expect heavy air resistance. Sub threat unknown.\n\nGOALS:\n\nProtect your carrier and destroy both the Russians HQ at Kevlavik and \nReykjavik.\n\nCOMMAND AND SIGNAL\n\nCVN Nimitz \n\n\n\n\n\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """This scenario was designed for playing US side.\n\n""")

    ####################
    SM.SetSimpleBriefing(3, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Los Angeles (1988)'
    unit.unitName = "USS Toledo "
    unit.SetPosition(-19.123006, 62.378531, -80.0)
    unit.heading = 72.69
    unit.speed = 7.1
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'UGM-84C Harpoon', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'UGM-109A', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'UGM-109A', 6)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Toledo ", 'Mk-48 Mod5', 12)
    SM.AddToUnitMagazine("USS Toledo ", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.369496, 1.094147, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Los Angeles (1988)'
    unit.unitName = "USS Columbus "
    unit.SetPosition(-21.899943, 60.849539, -80.0)
    unit.heading = 72.69
    unit.speed = 7.6
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'UGM-84C Harpoon', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'UGM-109A', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'UGM-109A', 6)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Columbus ", 'Mk-48 Mod5', 12)
    SM.AddToUnitMagazine("USS Columbus ", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.380798, 1.076128, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-3A'
    unit.unitName = "Dragon Fires 9"
    unit.SetPosition(-21.408123, 59.239447, 4000.0)
    unit.heading = 354.82
    unit.speed = 100.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'LOFAR (85) Sonobuoy', 12)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DICASS (85) Sonobuoy', 12)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DIFAR (85) Sonobuoy', 36)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.374773, 1.036805, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.362703, 1.034594, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'USS Carl Vinson')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-3A'
    unit.unitName = "Dragon Fires 10"
    unit.SetPosition(-21.092840, 60.266264, 4000.0)
    unit.heading = 304.76
    unit.speed = 214.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'LOFAR (85) Sonobuoy', 12)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DICASS (85) Sonobuoy', 12)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DIFAR (85) Sonobuoy', 36)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.373832, 1.051218, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.375400, 1.046598, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.359333, 1.046400, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.360900, 1.051021, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'USS Carl Vinson')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Nimitz CVN-70 USS Carl Vinson'
    unit.unitName = "USS Carl Vinson"
    unit.SetPosition(-20.873797, 59.772865, 0.0)
    unit.heading = -11.19
    unit.speed = 16.5
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
    SM.AddToUnitMagazine("USS Carl Vinson", 'AIM-9M', 239)
    SM.AddToUnitMagazine("USS Carl Vinson", 'AIM-7M', 272)
    SM.AddToUnitMagazine("USS Carl Vinson", 'AIM-54C', 14)
    SM.AddToUnitMagazine("USS Carl Vinson", 'AGM-45B', 88)
    SM.AddToUnitMagazine("USS Carl Vinson", 'AGM-88B', 96)
    SM.AddToUnitMagazine("USS Carl Vinson", 'AGM-84C Harpoon', 44)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Mk-46 Mod5', 127)
    SM.AddToUnitMagazine("USS Carl Vinson", 'M117', 1168)
    SM.AddToUnitMagazine("USS Carl Vinson", 'M118', 287)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Mk-82', 1833)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Mk-83', 1114)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Mk-84', 377)
    SM.AddToUnitMagazine("USS Carl Vinson", 'GBU-24/B', 47)
    SM.AddToUnitMagazine("USS Carl Vinson", 'GBU-24B/B', 73)
    SM.AddToUnitMagazine("USS Carl Vinson", 'B-57 Mod1 10kT', 4)
    SM.AddToUnitMagazine("USS Carl Vinson", 'B-57 Mod5 20kT', 2)
    SM.AddToUnitMagazine("USS Carl Vinson", 'FPU-6', 3)
    SM.AddToUnitMagazine("USS Carl Vinson", '370 gallon wing tank', 28)
    SM.AddToUnitMagazine("USS Carl Vinson", '20mm PGU', 1438)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Chaff-1', 3154)
    SM.AddToUnitMagazine("USS Carl Vinson", 'Flare-1', 3154)
    SM.AddToUnitMagazine("USS Carl Vinson", 'LOFAR (85) Sonobuoy', 491)
    SM.AddToUnitMagazine("USS Carl Vinson", 'DICASS (85) Sonobuoy', 491)
    SM.AddToUnitMagazine("USS Carl Vinson", 'DIFAR (85) Sonobuoy', 1473)
    SM.AddToUnitMagazine("USS Carl Vinson", 'RIM-7P(v1)', 94)
    SM.AddToUnitMagazine("USS Carl Vinson", '20mm mark 244-0 ELC', 2092)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.388189, 1.100971, 0.000000, 0.000000)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 1', 3)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 1', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 2', 3)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 2', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 1', 3)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 1', '')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'S-3A', 'Dragon Fires 1', 3)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Dragon Fires 1', '12 DICASS (85) Sonobuoy;12 LOFAR (85) Sonobuoy;36 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 3', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 3', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 4', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 4', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 5', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 5', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'F-14A', 'Eagle 6', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Eagle 6', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-7P;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 1', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 1', '6 AGM-65B;6 AGM-65B;6 AGM-65B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 2', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 2', '6 AGM-65B;6 AGM-65B;6 AGM-65B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E(78)', 'Viceroy 3', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 3', '2 AGM-84D Harpoon;2 AGM-84D Harpoon;1 300 gallon tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E(78)', 'Viceroy 4', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 4', '2 AGM-84D Harpoon;2 AGM-84D Harpoon;1 300 gallon tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E(78)', 'Viceroy 5', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 5', '2 AGM-88B;2 AGM-88B;1 300 gallon tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E(78)', 'Viceroy 6', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 6', '2 AGM-88B;2 AGM-88B;1 300 gallon tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'KA-6D', 'Viceroy 103', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 103', '2 300 gallon tank;2 300 gallon tank;1 300 gallon tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 2', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 2', '')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'S-3A', 'Dragon Fires 2', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Dragon Fires 2', '12 DICASS (85) Sonobuoy;12 LOFAR (85) Sonobuoy;36 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'S-3A', 'Dragon Fires 3', 2)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Dragon Fires 3', '12 DICASS (85) Sonobuoy;12 LOFAR (85) Sonobuoy;36 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;')
    
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
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 1', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 2', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 3', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 4', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 5', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 6', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 7', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 8', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 9', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 10', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 11', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Warhawk 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Warhawk 12', '0 Empty;2 GBU-24B/B;2 GBU-24B/B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 3', '6 AGM-65B;6 AGM-65B;6 AGM-65B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 4', '6 AGM-65B;6 AGM-65B;6 AGM-65B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 5', '6 AGM-65B;6 AGM-65B;6 AGM-65B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 6', '6 AGM-65B;6 AGM-65B;6 AGM-65B;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 7', '6 Mk-82;6 Mk-82;2 300 gallon tank;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 8', '6 Mk-82;6 Mk-82;2 300 gallon tank;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 9', '6 Mk-82;6 Mk-82;2 300 gallon tank;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 10','6 Mk-82;6 Mk-82;2 300 gallon tank;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 11','6 Mk-82;6 Mk-82;2 300 gallon tank;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-7E(79)', 'Mace 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Mace 12','6 Mk-82;6 Mk-82;2 300 gallon tank;0 Empty;48 20mm PGU-28/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E(78)', 'Viceroy 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 1', '2 AGM-84D Harpoon;2 AGM-84D Harpoon;1 300 gallon tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'A-6E(78)', 'Viceroy 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 2', '2 AGM-84D Harpoon;2 AGM-84D Harpoon;1 300 gallon tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'KA-6D', 'Viceroy 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 101', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'KA-6D', 'Viceroy 102', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Viceroy 102', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;')
    
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
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 3', '')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 4', '')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 5', '')
    
    SM.AddUnitToFlightDeck('USS Carl Vinson', 'E-2C Group 0', 'Hormel Hogs 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Carl Vinson', 'Hormel Hogs 6', '')
    
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oliver Hazard Perry FFGHM'
    unit.unitName = "USS Rentz"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.3405
    lat_deg = 57.296*leader_track.Lat + -0.0534
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -11.19
    unit.speed = 3.0
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
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(20.002, 4.934, 2.100, 0.322)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Rentz', 'SH-60B', 'Perry FFG Seahawk 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Rentz', 'Perry FFG Seahawk 101', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Flare-1;25 Chaff-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ticonderoga CG Baseline 3'
    unit.unitName = "USS Princeton"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1650
    lat_deg = 57.296*leader_track.Lat + 0.0177
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -11.19
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Princeton", 'Fuel', 56161)
    SM.AddToUnitMagazine("USS Princeton", 'Mk-46 Mod5', 46)
    SM.AddToUnitMagazine("USS Princeton", 'AGM-114 Hellfire', 16)
    SM.AddToUnitMagazine("USS Princeton", '120 gallon tank', 4)
    SM.AddToUnitMagazine("USS Princeton", 'Chaff-1', 75)
    SM.AddToUnitMagazine("USS Princeton", 'Flare-1', 75)
    SM.AddToUnitMagazine("USS Princeton", 'LOFAR (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("USS Princeton", 'DICASS (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("USS Princeton", 'DIFAR (85) Sonobuoy', 608)
    SM.AddToUnitMagazine("USS Princeton", 'RIM-66M', 119)
    SM.AddToUnitMagazine("USS Princeton", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Princeton", '127mm mk 80 HE-PD mk 67', 1200)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(9.511, 1.481, 1.563, 0.290)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Princeton', 'SH-60B', 'Tico Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Princeton', 'Tico Seahawk 1', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Flare-1;25 Chaff-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Princeton', 'SH-60B', 'Tico Seahawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Princeton', 'Tico Seahawk 2', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Flare-1;25 Chaff-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oliver Hazard Perry FFGHM'
    unit.unitName = "USS McInerney"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0756
    lat_deg = 57.296*leader_track.Lat + 0.1754
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -11.19
    unit.speed = 3.0
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
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(19.986, 4.455, -0.002, 0.356)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS McInerney', 'SH-60B', 'Perry FFG Seahawk 201', 1)
    SM.SetFlightDeckUnitLoadout('USS McInerney', 'Perry FFG Seahawk 201', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Flare-1;25 Chaff-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ticonderoga CG Baseline 2'
    unit.unitName = "USS Antietam"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1639
    lat_deg = 57.296*leader_track.Lat + -0.0172
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -11.19
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Antietam", 'Fuel', 56161)
    SM.AddToUnitMagazine("USS Antietam", 'Mk-46 Mod5', 46)
    SM.AddToUnitMagazine("USS Antietam", 'AGM-114 Hellfire', 16)
    SM.AddToUnitMagazine("USS Antietam", '120 gallon tank', 4)
    SM.AddToUnitMagazine("USS Antietam", 'Chaff-1', 75)
    SM.AddToUnitMagazine("USS Antietam", 'Flare-1', 75)
    SM.AddToUnitMagazine("USS Antietam", 'LOFAR (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("USS Antietam", 'DICASS (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("USS Antietam", 'DIFAR (85) Sonobuoy', 608)
    SM.AddToUnitMagazine("USS Antietam", 'RIM-66M', 119)
    SM.AddToUnitMagazine("USS Antietam", '20mm Mark 149-4', 1046)
    SM.AddToUnitMagazine("USS Antietam", '127mm mk 80 HE-PD mk 67', 1200)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(9.460, 1.713, -1.564, 0.285)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Antietam', 'SH-60B', 'Tico Seahawk 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Antietam', 'Tico Seahawk 101', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Flare-1;25 Chaff-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Antietam', 'SH-60B', 'Tico Seahawk 102', 1)
    SM.SetFlightDeckUnitLoadout('USS Antietam', 'Tico Seahawk 102', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Flare-1;25 Chaff-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Sacramento AOEHM'
    unit.unitName = "USS Sacramento"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0432
    lat_deg = 57.296*leader_track.Lat + 0.0072
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 348.81
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-7P(v1)', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Sacramento", '20mm mark 244-0 ELC', 1046)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(2.900, 3.200, 1.433, 0.385)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oliver Hazard Perry FFGHM'
    unit.unitName = "USS Duncan"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2653
    lat_deg = 57.296*leader_track.Lat + -0.1191
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -11.19
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66L', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Duncan", 'Fuel', 28080)
    SM.AddToUnitMagazine("USS Duncan", 'Mk-46 Mod5', 25)
    SM.AddToUnitMagazine("USS Duncan", 'AGM-114 Hellfire', 8)
    SM.AddToUnitMagazine("USS Duncan", '120 gallon tank', 2)
    SM.AddToUnitMagazine("USS Duncan", 'Chaff-1', 50)
    SM.AddToUnitMagazine("USS Duncan", 'Flare-1', 50)
    SM.AddToUnitMagazine("USS Duncan", 'DICASS (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Duncan", 'LOFAR (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Duncan", 'DIFAR (85) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS Duncan", 'RIM-66L', 35)
    SM.AddToUnitMagazine("USS Duncan", 'RGM-84D Harpoon', 4)
    SM.AddToUnitMagazine("USS Duncan", '20mm mark 244-0 ELC', 523)
    SM.AddToUnitMagazine("USS Duncan", '76mm HE-MOM', 240)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(20.026, 3.861, -2.094, 0.341)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Duncan', 'SH-60B', 'Perry FFG Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Duncan', 'Perry FFG Seahawk 1', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Flare-1;25 Chaff-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Spruance DDG ABL'
    unit.unitName = "USS Merrill"
    UI = SM.GetUnitInterface('USS Carl Vinson')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0244
    lat_deg = 57.296*leader_track.Lat + -0.0488
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -11.19
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 2, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'RUM-139 Mod4 ASROC', 8)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'BGM-109 TLAM', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'BGM-109 TLAM', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Merrill", 'Fuel', 65139)
    SM.AddToUnitMagazine("USS Merrill", 'Mk-46 Mod5', 31)
    SM.AddToUnitMagazine("USS Merrill", '120 gallon tank', 2)
    SM.AddToUnitMagazine("USS Merrill", 'AGM-114 Hellfire', 16)
    SM.AddToUnitMagazine("USS Merrill", 'Chaff-1', 100)
    SM.AddToUnitMagazine("USS Merrill", 'Flare-1', 100)
    SM.AddToUnitMagazine("USS Merrill", 'LOFAR (85) Sonobuoy', 253)
    SM.AddToUnitMagazine("USS Merrill", 'DICASS (85) Sonobuoy', 253)
    SM.AddToUnitMagazine("USS Merrill", 'DIFAR (85) Sonobuoy', 758)
    SM.AddToUnitMagazine("USS Merrill", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Merrill", '127mm mk 80 HE-PD mk 67', 1200)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Carl Vinson')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(5.639, 3.194, 3.146, 0.571)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Merrill', 'SH-60B', 'Spruance ABL DDG Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Merrill', 'Spruance ABL DDG Seahawk 1', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Flare-1;25 Chaff-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Merrill', 'SH-60B', 'Spruance ABL DDG Seahawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Merrill', 'Spruance ABL DDG Seahawk 2', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Flare-1;25 Chaff-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 949A Antey'
    unit.unitName = "K-148 Krasnodar"
    unit.SetPosition(-21.749936, 63.431814, -71.7)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M45 Granit', 24)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, '65-76 Kit', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-148 Krasnodar", 'SET-65M', 8)
    SM.AddToUnitMagazine("K-148 Krasnodar", '65-76 Kit', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.390969, 1.104553, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.370938, 1.110084, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.388578, 1.110532, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Russian HQ Reykjavik"
    unit.SetPosition(-21.565616, 64.095586, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200D Dubna'
    unit.unitName = "S-200 (1)"
    unit.SetPosition(-21.578450, 64.102863, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-880M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("S-200 (1)", 'V-880M', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V Shilka'
    unit.unitName = "ZSU-23 (6)"
    unit.SetPosition(-21.537025, 64.066136, 183.7)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V Shilka'
    unit.unitName = "ZSU-23 (5)"
    unit.SetPosition(-21.614203, 64.065677, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fuel Tanks'
    unit.unitName = "Fuel Tanks Reykjavik"
    unit.SetPosition(-21.551120, 64.097247, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Dump Reykjavik"
    unit.SetPosition(-21.604806, 64.096789, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-125 Pechora-M'
    unit.unitName = "S-125 (3)"
    unit.SetPosition(-21.575242, 64.116728, 549.6)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-601PD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-125 Pechora-M'
    unit.unitName = "S-125 (2)"
    unit.SetPosition(-21.497262, 64.086590, 320.6)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-601PD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("S-125 (2)", 'V-601PD', 16)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-125 Pechora-M'
    unit.unitName = "S-125 (4)"
    unit.SetPosition(-21.641475, 64.083611, 180.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-601PD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("S-125 (4)", 'V-601PD', 16)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-125 Pechora-M'
    unit.unitName = "S-125 (1)"
    unit.SetPosition(-21.572950, 64.060979, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-601PD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-601PD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("S-125 (1)", 'V-601PD', 16)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZIL-157 Truck'
    unit.unitName = "Truck"
    unit.SetPosition(-22.181202, 63.937850, -0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Generic Mobile Artillery 155mm'
    unit.unitName = "MA 155mm SP (1)"
    unit.SetPosition(-22.221595, 63.939970, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '12.7mm B-32 APi', 17)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Gen155ART', 40)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-80 MBT'
    unit.unitName = "T-80 MBT (5)"
    unit.SetPosition(-22.175186, 63.930918, 784.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-80 MBT'
    unit.unitName = "T-80 MBT (4)"
    unit.SetPosition(-22.224632, 63.931261, 550.2)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-80 MBT'
    unit.unitName = "T-80 MBT (3)"
    unit.SetPosition(-22.201141, 63.943583, 384.5)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-80 MBT'
    unit.unitName = "T-80 MBT (2)"
    unit.SetPosition(-22.199937, 63.919800, 201.9)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-80 MBT'
    unit.unitName = "T-80 MBT (1)"
    unit.SetPosition(-22.202458, 63.932006, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4M4 Biryusa'
    unit.unitName = "ZSU-23 (4)"
    unit.SetPosition(-22.303700, 63.914130, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Russian HQ Kevlavik"
    unit.SetPosition(-22.319628, 63.915562, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4M4 Biryusa'
    unit.unitName = "ZSU-23 (3)"
    unit.SetPosition(-22.368387, 63.860787, 121.9)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4M4 Biryusa'
    unit.unitName = "ZSU-23 (2)"
    unit.SetPosition(-21.992469, 63.843713, 81.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4M4 Biryusa'
    unit.unitName = "ZSU-23 (1)"
    unit.SetPosition(-22.336588, 63.884737, -0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Communications Station'
    unit.unitName = "Communications Stations"
    unit.SetPosition(-22.293043, 63.916135, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-3(36)'
    unit.unitName = "SSC-5"
    unit.SetPosition(-21.976541, 63.846406, 117.7)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'P-20K', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SSC-5", 'P-20K', 36)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-3(36)'
    unit.unitName = "SSC-4"
    unit.SetPosition(-21.623370, 63.844172, 117.7)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'P-20K', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SSC-4", 'P-20K', 36)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-3(36)'
    unit.unitName = "SSC-3"
    unit.SetPosition(-22.348792, 63.866231, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'P-20K', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'P-20K', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SSC-3", 'P-20K', 36)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fuel Tanks'
    unit.unitName = "Fuel Tanks"
    unit.SetPosition(-22.356527, 63.920318, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Dump"
    unit.SetPosition(-22.338593, 63.921750, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PMU'
    unit.unitName = "SA-10 Site 2"
    unit.SetPosition(-21.582002, 63.940772, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55RUD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10 Site 2", '5V55RUD', 70)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Reykjavik"
    unit.SetPosition(-21.578507, 64.086705, -0.0)
    unit.heading = 270.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Reykjavik", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Reykjavik", '2000 liter tank', 500)
    SM.AddToUnitMagazine("Reykjavik", '23mm AM-23', 400)
    SM.AddToUnitMagazine("Reykjavik", 'Chaff-1', 400)
    SM.AddToUnitMagazine("Reykjavik", 'Flare-1', 400)
    SM.AddToUnitMagazine("Reykjavik", 'R-33', 200)
    SM.AddToUnitMagazine("Reykjavik", 'R-40T', 200)
    SM.AddToUnitMagazine("Reykjavik", 'R-60', 200)
    SM.AddToUnitMagazine("Reykjavik", 'R-27R', 256)
    SM.AddToUnitMagazine("Reykjavik", 'R-73M', 100)
    SM.AddToUnitMagazine("Reykjavik", 'Kh-31P', 726)
    SM.AddToUnitMagazine("Reykjavik", 'R-77', 300)
    SM.AddToUnitMagazine("Reykjavik", 'Kh-29T', 300)
    UI.SetSensorState(0, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-1', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-1', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-2', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-2', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-3', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-3', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-4', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-4', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-5', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-5', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-6', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-6', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-7', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-7', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-8', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-8', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-9', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-9', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-10', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-10', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-11', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-11', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-12', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-12', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-13', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-13', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-14', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-14', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-15', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-15', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-16', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-16', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-17', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-17', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-18', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-18', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-19', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-19', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-20', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-20', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-21', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-21', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-22', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-22', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-23', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-23', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'MiG-31', 'Foxhound-24', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Foxhound-24', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-1', 2)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-1', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-2', 2)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-2', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-3', 2)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-3', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-4', 2)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-4', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-5', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-5', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-6', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-6', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-7', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-7', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-8', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-8', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-9', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-9', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-10', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-10', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-11', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-11', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-12', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-12', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-13', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-13', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-14', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-14', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-15', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-15', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-16', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-16', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-17', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-17', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-18', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-18', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-19', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-19', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-20', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-20', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-21', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-21', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-22', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-22', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-23', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-23', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-24', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-24', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-25', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-25', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-26', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-26', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'Su-27', 'Curtain-27', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'Curtain-27', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'A-50', 'AEW Reykjavik-1', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'AEW Reykjavik-1', '')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'A-50', 'AEW Reykjavik-2', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'AEW Reykjavik-2', '')
    
    SM.AddUnitToFlightDeck('Reykjavik', 'A-50', 'AEW Reykjavik-3', 1)
    SM.SetFlightDeckUnitLoadout('Reykjavik', 'AEW Reykjavik-3', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'AEW Reykjavik-1')
    FP.AddAircraftToMission(mission_id, 'AEW Reykjavik-2')
    FP.AddAircraftToMission(mission_id, 'AEW Reykjavik-3')
    FP.SetMissionLaunchTime(mission_id, '13:00:08+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0011194,-0.0011487,0.0005687,-0.0009476,0.0005604,0.0003021,0.0011687,0.0004100,')
    FP.SetMissionPatrolAnchor(mission_id, 'Reykjavik', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.3758280, 1.1189780, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3771100, 1.1188869, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Curtain-1')
    FP.AddAircraftToMission(mission_id, 'Curtain-2')
    FP.AddAircraftToMission(mission_id, 'Curtain-3')
    FP.AddAircraftToMission(mission_id, 'Curtain-4')
    FP.AddAircraftToMission(mission_id, 'Curtain-5')
    FP.AddAircraftToMission(mission_id, 'Curtain-6')
    FP.AddAircraftToMission(mission_id, 'Curtain-7')
    FP.AddAircraftToMission(mission_id, 'Curtain-8')
    FP.AddAircraftToMission(mission_id, 'Curtain-9')
    FP.AddAircraftToMission(mission_id, 'Curtain-10')
    FP.AddAircraftToMission(mission_id, 'Curtain-11')
    FP.AddAircraftToMission(mission_id, 'Curtain-12')
    FP.AddAircraftToMission(mission_id, 'Curtain-13')
    FP.AddAircraftToMission(mission_id, 'Curtain-14')
    FP.AddAircraftToMission(mission_id, 'Curtain-15')
    FP.AddAircraftToMission(mission_id, 'Curtain-16')
    FP.AddAircraftToMission(mission_id, 'Curtain-17')
    FP.AddAircraftToMission(mission_id, 'Curtain-18')
    FP.AddAircraftToMission(mission_id, 'Foxhound-1')
    FP.AddAircraftToMission(mission_id, 'Foxhound-2')
    FP.AddAircraftToMission(mission_id, 'Foxhound-3')
    FP.AddAircraftToMission(mission_id, 'Foxhound-4')
    FP.AddAircraftToMission(mission_id, 'Foxhound-5')
    FP.AddAircraftToMission(mission_id, 'Foxhound-6')
    FP.AddAircraftToMission(mission_id, 'Foxhound-7')
    FP.AddAircraftToMission(mission_id, 'Foxhound-8')
    FP.AddAircraftToMission(mission_id, 'Foxhound-9')
    FP.AddAircraftToMission(mission_id, 'Foxhound-10')
    FP.AddAircraftToMission(mission_id, 'Foxhound-11')
    FP.AddAircraftToMission(mission_id, 'Foxhound-12')
    FP.SetMissionLaunchTime(mission_id, '13:00:08+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 6)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.3846892,1.1138377,-0.3695370,1.1137897,-0.3693123,1.1122327,-0.3850102,1.1125697,')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3756160, 1.1195240, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3778050, 1.1141660, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Foxhound-13')
    FP.AddAircraftToMission(mission_id, 'Foxhound-14')
    FP.AddAircraftToMission(mission_id, 'Foxhound-15')
    FP.AddAircraftToMission(mission_id, 'Foxhound-16')
    FP.AddAircraftToMission(mission_id, 'Foxhound-17')
    FP.AddAircraftToMission(mission_id, 'Foxhound-18')
    FP.AddAircraftToMission(mission_id, 'Foxhound-19')
    FP.AddAircraftToMission(mission_id, 'Foxhound-20')
    FP.AddAircraftToMission(mission_id, 'Foxhound-21')
    FP.AddAircraftToMission(mission_id, 'Foxhound-22')
    FP.AddAircraftToMission(mission_id, 'Foxhound-23')
    FP.AddAircraftToMission(mission_id, 'Foxhound-24')
    FP.SetMissionLaunchTime(mission_id, '13:00:08+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.3802805,1.1183320,-0.3722472,1.1166679,-0.3738498,1.1163906,-0.3800956,1.1175718,')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3756160, 1.1195240, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3768290, 1.1176130, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Curtain-19')
    FP.AddAircraftToMission(mission_id, 'Curtain-20')
    FP.AddAircraftToMission(mission_id, 'Curtain-21')
    FP.AddAircraftToMission(mission_id, 'Curtain-22')
    FP.AddAircraftToMission(mission_id, 'Curtain-23')
    FP.AddAircraftToMission(mission_id, 'Curtain-24')
    FP.AddAircraftToMission(mission_id, 'Curtain-25')
    FP.AddAircraftToMission(mission_id, 'Curtain-26')
    FP.AddAircraftToMission(mission_id, 'Curtain-27')
    FP.SetMissionLaunchTime(mission_id, '13:00:08+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 9)
    FP.SetMissionType(mission_id, 'Standby-ASuW')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Shipwreck 2-17"
    unit.SetPosition(-22.330991, 63.902230, 10.0)
    unit.heading = 164.16
    unit.speed = 485.6
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22MP', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.429478, 1.050304, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.300895, 1.067299, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.066276')
    BB.Write('StationLongitude', '-0.365281')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Shipwreck 2-18"
    unit.SetPosition(-22.332575, 63.902033, 10.0)
    unit.heading = 165.82
    unit.speed = 485.8
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22MP', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.415181, 1.089890, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.332888, 1.086096, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.370116, 1.097985, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.067410')
    BB.Write('StationLongitude', '-0.361880')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Shipwreck 2-19"
    unit.SetPosition(-22.354776, 63.903298, 10.0)
    unit.heading = 205.47
    unit.speed = 485.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22MP', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.405384, 1.097732, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.332398, 1.098238, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.051256')
    BB.Write('StationLongitude', '-0.427064')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Shipwreck 2-20"
    unit.SetPosition(-22.315363, 63.906996, 3337.8)
    unit.heading = 129.48
    unit.speed = 485.8
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22MP', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.425468, 1.095961, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.331908, 1.094696, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.068260')
    BB.Write('StationLongitude', '-0.287627')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Shadow-1"
    unit.SetPosition(-22.326439, 63.901946, 10.0)
    unit.heading = 158.81
    unit.speed = 562.1
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.408323, 1.098491, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.369626, 1.098238, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.077329')
    BB.Write('StationLongitude', '-0.381719')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Shipwreck 1-19"
    unit.SetPosition(-22.358976, 63.904503, 10.0)
    unit.heading = 214.75
    unit.speed = 485.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22MP', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.412242, 1.093938, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.337786, 1.095961, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.047572')
    BB.Write('StationLongitude', '-0.437267')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Shadow-4"
    unit.SetPosition(-22.320282, 63.903540, 10.0)
    unit.heading = 145.01
    unit.speed = 561.6
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.072228')
    BB.Write('StationLongitude', '-0.333540')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Shadow-5"
    unit.SetPosition(-22.309154, 63.909874, 10.0)
    unit.heading = 114.64
    unit.speed = 562.1
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.057491')
    BB.Write('StationLongitude', '-0.287627')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Shadow-6"
    unit.SetPosition(-22.322147, 63.902964, 10.0)
    unit.heading = 150.39
    unit.speed = 562.1
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.071094')
    BB.Write('StationLongitude', '-0.359613')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Shadow-7"
    unit.SetPosition(-22.332528, 63.901040, 10.0)
    unit.heading = 166.69
    unit.speed = 562.2
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.067410')
    BB.Write('StationLongitude', '-0.363581')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Shadow-9"
    unit.SetPosition(-22.358212, 63.903078, 10.0)
    unit.heading = 210.36
    unit.speed = 561.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.074779')
    BB.Write('StationLongitude', '-0.420263')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Shadow-10"
    unit.SetPosition(-22.311060, 63.908172, 10.0)
    unit.heading = 122.07
    unit.speed = 561.1
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.055790')
    BB.Write('StationLongitude', '-0.246250')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Shadow-12"
    unit.SetPosition(-22.349090, 63.901255, 10.0)
    unit.heading = 193.04
    unit.speed = 561.1
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.053523')
    BB.Write('StationLongitude', '-0.398723')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Shadow-13"
    unit.SetPosition(-22.328796, 63.901551, 10.0)
    unit.heading = 161.06
    unit.speed = 561.2
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.067977')
    BB.Write('StationLongitude', '-0.359046')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Shadow-14"
    unit.SetPosition(-22.342112, 63.900723, 10.0)
    unit.heading = 180.75
    unit.speed = 561.3
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    BB.Write('StationLatitude', '1.102269')
    BB.Write('StationLongitude', '-0.378885')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Fulcrum 8"
    unit.SetPosition(-22.686536, 62.576364, 4000.0)
    unit.heading = 94.57
    unit.speed = 237.2
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.090046')
    BB.Write('StationLongitude', '-0.388112')
    UI.SetThrottle(0.189654)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Fulcrum 7"
    unit.SetPosition(-23.156456, 62.607014, 4000.0)
    unit.heading = 94.60
    unit.speed = 237.2
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.088441')
    BB.Write('StationLongitude', '-0.413788')
    UI.SetThrottle(0.189654)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Fulcrum 6"
    unit.SetPosition(-20.581955, 63.107612, 50.0)
    unit.heading = 94.60
    unit.speed = 230.1
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.097535')
    BB.Write('StationLongitude', '-0.357800')
    UI.SetThrottle(0.189654)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Fulcrum 5"
    unit.SetPosition(-21.154027, 63.148470, 50.0)
    unit.heading = 94.53
    unit.speed = 230.1
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.099139')
    BB.Write('StationLongitude', '-0.374561')
    UI.SetThrottle(0.189654)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'A-50'
    unit.unitName = "Sharp Eye 2"
    unit.SetPosition(-20.989851, 63.693939, 10000.0)
    unit.heading = 94.60
    unit.speed = 100.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.372247, 1.109279, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.362767, 1.109304, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.109659')
    BB.Write('StationLongitude', '-0.375987')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'A-50'
    unit.unitName = "Sharp Eye 1"
    unit.SetPosition(-22.999329, 63.536784, 10000.0)
    unit.heading = 94.50
    unit.speed = 100.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.413856, 1.108093, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.390344, 1.108240, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.102170')
    BB.Write('StationLongitude', '-0.410579')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Fulcrum 4"
    unit.SetPosition(-20.985444, 62.633379, 4000.0)
    unit.heading = 94.50
    unit.speed = 237.2
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.089154')
    BB.Write('StationLongitude', '-0.362793')
    UI.SetThrottle(0.189654)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Fulcrum 3"
    unit.SetPosition(-21.480976, 62.663110, 4000.0)
    unit.heading = 94.57
    unit.speed = 237.2
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.089511')
    BB.Write('StationLongitude', '-0.375987')
    UI.SetThrottle(0.189654)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Fulcrum 2"
    unit.SetPosition(-22.869076, 61.751308, 4000.0)
    unit.heading = 94.53
    unit.speed = 237.2
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.075425')
    BB.Write('StationLongitude', '-0.391678')
    UI.SetThrottle(0.189654)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-29'
    unit.unitName = "Fulcrum 1"
    unit.SetPosition(-23.265512, 61.741395, 4000.0)
    unit.heading = 94.53
    unit.speed = 237.2
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1520 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'R-73M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm NR-30 HEI', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.072572')
    BB.Write('StationLongitude', '-0.405229')
    UI.SetThrottle(0.189654)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 670 Skat'
    unit.unitName = "K-313"
    unit.SetPosition(-22.721245, 61.097742, -76.7)
    unit.heading = 121.60
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'P-70 Ametist', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-313", 'SET-65', 8)
    SM.AddToUnitMagazine("K-313", '53-65M', 4)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(2, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.353112, 1.068079, 0.000000, 10.000000)
    UI.AddNavWaypointAdvanced(-0.421442, 1.072985, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.378554, 1.104787, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877M Paltus'
    unit.unitName = "B-459"
    boxes = [[-20.9063, -20.8663, 60.3468, 60.3868],[-20.9063, -20.8663, 60.3468, 60.3868]]
    box = boxes[int(2*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -310.2)
    unit.heading = 242.25
    unit.speed = 6.3
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Igla-M SAM', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-459", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-459", '53-65M', 6)
    SM.AddToUnitMagazine("B-459", 'Igla-M SAM', 4)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.377827, 1.050087, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.365106, 1.075711, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.387640, 1.109512, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Kevlavik"
    unit.SetPosition(-22.339453, 63.910749, -0.0)
    unit.heading = 168.97
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Kevlavik", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Kevlavik", 'Kh-22MP', 610)
    SM.AddToUnitMagazine("Kevlavik", 'Chaff-1', 400)
    SM.AddToUnitMagazine("Kevlavik", 'FAB-500', 400)
    SM.AddToUnitMagazine("Kevlavik", 'Flare-1', 400)
    SM.AddToUnitMagazine("Kevlavik", 'Kh-31P', 407)
    SM.AddToUnitMagazine("Kevlavik", '1520 Liter Tank', 300)
    SM.AddToUnitMagazine("Kevlavik", 'FAB-100', 300)
    SM.AddToUnitMagazine("Kevlavik", 'FAB-250', 300)
    SM.AddToUnitMagazine("Kevlavik", 'Kh-22M', 300)
    SM.AddToUnitMagazine("Kevlavik", 'R-27R', 884)
    SM.AddToUnitMagazine("Kevlavik", 'R-73', 292)
    SM.AddToUnitMagazine("Kevlavik", 'R-77', 200)
    UI.SetSensorState(0, 1)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Kevlavik', 'MiG-29', 'Shadow-3', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shadow-3', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73M;20 30mm NR-30 HEI;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'MiG-29', 'Shadow-2', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shadow-2', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73M;20 30mm NR-30 HEI;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'MiG-29', 'Shadow-8', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shadow-8', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73M;20 30mm NR-30 HEI;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'MiG-29', 'Shadow-11', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shadow-11', '1 1520 Liter Tank;2 R-27R;2 R-73;2 R-73M;20 30mm NR-30 HEI;25 Chaff-1;25 Flare-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-15', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-15', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-6', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-6', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-7', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-7', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-8', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-8', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-9', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-9', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-10', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-10', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-11', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-11', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-12', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-12', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-13', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-13', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-14', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-14', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-15', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-15', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-16', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-16', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-17', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-17', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-18', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-18', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-16', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-16', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 1-20', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 1-20', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-1', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-1', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-2', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-2', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-3', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-3', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-4', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-4', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-5', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-5', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-6', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-6', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-7', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-7', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-8', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-8', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-9', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-9', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-10', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-10', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-11', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-11', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-12', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-12', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-13', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-13', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Tu-22ME', 'Shipwreck 2-14', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Shipwreck 2-14', '2 Kh-22MP;1 Kh-22MP;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-1', 2)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-1', '4 R-27R;2 R-77;4 R-27R;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-2', 2)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-2', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-3', 2)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-3', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-4', 2)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-4', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-5', 2)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-5', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-6', 2)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-6', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-7', 2)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-7', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-8', 2)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-8', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-9', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-9', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-10', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-10', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-11', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-11', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-12', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-12', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-13', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-13', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-14', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-14', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-15', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-15', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-16', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-16', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-17', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-17', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-18', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-18', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-19', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-19', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-20', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-20', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-21', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-21', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-22', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-22', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-23', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-23', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Kevlavik', 'Su-27', 'Wall-24', 1)
    SM.SetFlightDeckUnitLoadout('Kevlavik', 'Wall-24', '3 Kh-31P;2 R-77;4 Kh-31P;25 Flare-1;25 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Wall-1')
    FP.AddAircraftToMission(mission_id, 'Wall-2')
    FP.AddAircraftToMission(mission_id, 'Wall-3')
    FP.AddAircraftToMission(mission_id, 'Wall-4')
    FP.AddAircraftToMission(mission_id, 'Wall-5')
    FP.AddAircraftToMission(mission_id, 'Wall-6')
    FP.AddAircraftToMission(mission_id, 'Wall-7')
    FP.AddAircraftToMission(mission_id, 'Wall-8')
    FP.AddAircraftToMission(mission_id, 'Wall-9')
    FP.AddAircraftToMission(mission_id, 'Wall-10')
    FP.AddAircraftToMission(mission_id, 'Wall-11')
    FP.AddAircraftToMission(mission_id, 'Wall-12')
    FP.SetMissionLaunchTime(mission_id, '13:00:08+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.3966131,1.1144481,-0.3817177,1.1139344,-0.3817177,1.1113020,-0.3957142,1.1115075,')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3888970, 1.1164531, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3895190, 1.1136150, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Wall-13')
    FP.AddAircraftToMission(mission_id, 'Wall-14')
    FP.AddAircraftToMission(mission_id, 'Wall-15')
    FP.AddAircraftToMission(mission_id, 'Wall-16')
    FP.AddAircraftToMission(mission_id, 'Wall-17')
    FP.AddAircraftToMission(mission_id, 'Wall-18')
    FP.AddAircraftToMission(mission_id, 'Wall-19')
    FP.AddAircraftToMission(mission_id, 'Wall-20')
    FP.AddAircraftToMission(mission_id, 'Wall-21')
    FP.AddAircraftToMission(mission_id, 'Wall-22')
    FP.AddAircraftToMission(mission_id, 'Wall-23')
    FP.AddAircraftToMission(mission_id, 'Wall-24')
    FP.SetMissionLaunchTime(mission_id, '13:00:08+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0035024,0.0001601,0.0035684,-0.0008994,-0.0032615,0.0005575,-0.0024091,0.0014547,')
    FP.SetMissionPatrolAnchor(mission_id, 'Kevlavik', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.3888970, 1.1164531, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3901000, 1.1150531, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-15')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-6')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-7')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-8')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-9')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-10')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-11')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-12')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-13')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-14')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-15')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-16')
    FP.SetMissionLaunchTime(mission_id, '13:00:08+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, 'Standby-ASuW')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-16')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 1-20')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-1')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-2')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-3')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-4')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-5')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-6')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-7')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-8')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-9')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-10')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-11')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-12')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-13')
    FP.AddAircraftToMission(mission_id, 'Shipwreck 2-14')
    FP.SetMissionLaunchTime(mission_id, '12:00:08+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 8)
    FP.SetMissionType(mission_id, 'Standby-ASuW')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 1"
    unit.SetPosition(-32.584050, 55.516823, 14000.0)
    unit.heading = 66.29
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.030556')
    BB.Write('StationLongitude', '-0.392433')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 2"
    unit.SetPosition(-32.168371, 55.198724, 14000.0)
    unit.heading = 66.29
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.028579')
    BB.Write('StationLongitude', '-0.377806')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 4"
    unit.SetPosition(-32.128469, 55.697659, 14000.0)
    unit.heading = 66.29
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.036880')
    BB.Write('StationLongitude', '-0.400791')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 3"
    unit.SetPosition(-31.673336, 55.422092, 14000.0)
    unit.heading = 66.29
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.032137')
    BB.Write('StationLongitude', '-0.404274')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 7"
    unit.SetPosition(-16.107389, 55.375940, 14000.0)
    unit.heading = 312.62
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.030348')
    BB.Write('StationLongitude', '-0.333093')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 5"
    unit.SetPosition(-16.225302, 54.909432, 14000.0)
    unit.heading = 312.62
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.026914')
    BB.Write('StationLongitude', '-0.337174')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 8"
    unit.SetPosition(-15.432983, 55.408261, 14000.0)
    unit.heading = 312.62
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.033322')
    BB.Write('StationLongitude', '-0.301887')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 6"
    unit.SetPosition(-15.233573, 54.814413, 14000.0)
    unit.heading = 312.62
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.025417')
    BB.Write('StationLongitude', '-0.294922')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 11"
    unit.SetPosition(-9.785666, 64.295426, 14000.0)
    unit.heading = 253.54
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.066212')
    BB.Write('StationLongitude', '-0.358760')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 9"
    unit.SetPosition(-9.529320, 64.052962, 14000.0)
    unit.heading = 253.54
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.063091')
    BB.Write('StationLongitude', '-0.357678')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 10"
    unit.SetPosition(-9.056117, 63.989523, 14000.0)
    unit.heading = 253.54
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.061956')
    BB.Write('StationLongitude', '-0.340381')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Hammer 12"
    unit.SetPosition(-9.117420, 64.294177, 14000.0)
    unit.heading = 253.54
    unit.speed = 877.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '1.067347')
    BB.Write('StationLongitude', '-0.342543')
    UI.SetThrottle(0.338669)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Shipwreck 1-1"
    unit.SetPosition(-22.333016, 63.902860, 2196.9)
    unit.heading = 166.10
    unit.speed = 467.6
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22MP', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.428529, 1.095929, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.407465, 1.097644, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Shipwreck 1-2"
    unit.SetPosition(-22.331662, 63.903010, 2200.2)
    unit.heading = 163.35
    unit.speed = 468.1
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22MP', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.333010, 1.095685, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.366809, 1.097399, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Shipwreck 1-3"
    unit.SetPosition(-22.331827, 63.902989, 2200.2)
    unit.heading = 163.69
    unit.speed = 468.1
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22MP', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.401097, 1.097154, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.335459, 1.095685, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Shipwreck 1-4"
    unit.SetPosition(-22.331335, 63.903067, 2201.7)
    unit.heading = 162.66
    unit.speed = 467.6
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22MP', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.424120, 1.092256, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.366319, 1.088827, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-22ME'
    unit.unitName = "Shipwreck 1-5"
    unit.SetPosition(-22.333956, 63.901631, 10.0)
    unit.heading = 168.97
    unit.speed = 494.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-22M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Kh-22MP', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.416772, 1.099113, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.334479, 1.094950, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Kevlavik')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 971 Shchuka-B'
    unit.unitName = "K-284 Puma"
    unit.SetPosition(-23.432720, 63.459222, -100.0)
    unit.heading = 142.04
    unit.speed = 3.0
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
    SM.AddToUnitMagazine("K-284 Puma", 'SET-65M', 8)
    SM.AddToUnitMagazine("K-284 Puma", '65-76 Kit', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.379901, 1.107412, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.361914, 1.106360, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.396739, 1.104638, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 945 Barrakuda'
    unit.unitName = "K-239 Karp"
    boxes = [[-18.4605, -18.4205, 62.6356, 62.6756]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -700.0)
    unit.heading = 231.61
    unit.speed = 27.2
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'RPK-7 Veter', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RPK-7 Veter', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-239 Karp", 'SET-65M', 6)
    SM.AddToUnitMagazine("K-239 Karp", '65-76 Kit', 6)
    SM.AddToUnitMagazine("K-239 Karp", 'RPK-7 Veter', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(5, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.367369, 1.068139, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.409465, 1.099591, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671RTMK Shchuka'
    unit.unitName = "K-448"
    unit.SetPosition(-20.816359, 58.863220, -350.0)
    unit.heading = 356.71
    unit.speed = 22.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '65-76 Kit', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-448", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-448", '53-65M', 6)
    UI.SetSensorState(6, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.365433, 1.062333, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.382369, 1.107816, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 956 Sarych'
    unit.unitName = "DDG Sovremenny"
    unit.SetPosition(-21.049097, 60.881672, 0.0)
    unit.heading = -17.88
    unit.speed = 16.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 22)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 22)
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
    SM.AddToUnitMagazine("DDG Sovremenny", 'Fuel', 45900)
    SM.AddToUnitMagazine("DDG Sovremenny", 'AT-1', 22)
    SM.AddToUnitMagazine("DDG Sovremenny", 'DICASS (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("DDG Sovremenny", 'LOFAR (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("DDG Sovremenny", 'DIFAR (80) Sonobuoy', 378)
    SM.AddToUnitMagazine("DDG Sovremenny", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("DDG Sovremenny", '130mm F-44 HE', 1000)
    SM.AddToUnitMagazine("DDG Sovremenny", '53-65M', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.376449, 1.079130, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.374741, 1.111940, 0.000000, 0.000000)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('DDG Sovremenny', 'Ka-27A', 'Sarych Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('DDG Sovremenny', 'Sarych Ka-27 1', '5 LOFAR (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DIFAR (80) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PMU'
    unit.unitName = "SA-10 Site 1"
    unit.SetPosition(-22.553051, 63.875283, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55RUD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10 Site 1", '5V55RUD', 72)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-125 Pechora-2M'
    unit.unitName = "S-125 Reykjavik (1)"
    unit.SetPosition(-21.537312, 64.082465, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-601P', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("S-125 Reykjavik (1)", 'V-601P', 16)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-125 Pechora-2M'
    unit.unitName = "S-125 Reykjavik (2)"
    unit.SetPosition(-21.566533, 64.045738, 204.5)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-601P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-601P', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("S-125 Reykjavik (2)", 'V-601P', 16)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K37 Buk'
    unit.unitName = "SA-11 Kevlavik (1)"
    unit.SetPosition(-22.342833, 63.933439, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M38', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M38', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M38', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M38', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-11 Kevlavik (1)", '9M38', 48)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Kevlavik 2"
    unit.SetPosition(-22.324155, 63.921693, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Kevlavik 2", 'R-73', 100)
    SM.AddToUnitMagazine("Kevlavik 2", 'Kh-22M', 200)
    SM.AddToUnitMagazine("Kevlavik 2", 'Kh-22MP', 200)
    SM.AddToUnitMagazine("Kevlavik 2", 'Kh-29T', 100)
    SM.AddToUnitMagazine("Kevlavik 2", 'R-77', 100)
    SM.AddToUnitMagazine("Kevlavik 2", 'Kh-31P', 100)
    SM.AddToUnitMagazine("Kevlavik 2", 'R-73M', 100)
    SM.AddToUnitMagazine("Kevlavik 2", 'R-27R', 100)
    SM.AddToUnitMagazine("Kevlavik 2", 'R-60', 100)
    SM.AddToUnitMagazine("Kevlavik 2", 'R-40T', 100)
    SM.AddToUnitMagazine("Kevlavik 2", 'R-33', 100)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Generic submarine'
    unit.unitName = "Swedish Sub"
    unit.SetPosition(-25.241260, 62.169770, -100.0)
    unit.heading = 88.49
    unit.speed = 16.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MK-T1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'UGM-84C Harpoon', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.310398, 1.087291, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.295234, 1.052913, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.415467, 1.040089, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.507537, 1.065736, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('USS Carl Vinson')
    goal_temp.SetQuantity(1)
    goal_0_0 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Russian HQ Kevlavik')
    goal_temp.SetQuantity(1)
    goal_0_1 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Russian HQ Reykjavik')
    goal_temp.SetQuantity(1)
    goal_0_2 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_0_0)
    goal_temp.AddGoal(goal_0_1)
    goal_temp.AddGoal(goal_0_2)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('USS Carl Vinson')
    goal_temp.SetQuantity(1)
    goal_1_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Russian HQ Reykjavik')
    goal_temp.SetQuantity(1)
    goal_1_1 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Russian HQ Kevlavik')
    goal_temp.SetQuantity(1)
    goal_1_2 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_1_0)
    goal_temp.AddGoal(goal_1_1)
    goal_temp.AddGoal(goal_1_2)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Alliance 3 goals
    ##############################

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(599940.0)
    goal_temp.SetFailTimeout(599940.0)
    SM.SetAllianceGoal(3, goal_temp)

    SM.SetAllianceROEByType(3, 0, 0, 0, 0)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
    SM.SetIncludeProbability('B-459', 1.000000)
    SM.AddRandomBox('B-459', -20.9063, -20.8663, 60.3468, 60.3868)
    SM.AddRandomBox('B-459', -20.9063, -20.8663, 60.3468, 60.3868)
    SM.SetIncludeProbability('K-239 Karp', 1.000000)
    SM.AddRandomBox('K-239 Karp', -18.4605, -18.4205, 62.6356, 62.6756)
