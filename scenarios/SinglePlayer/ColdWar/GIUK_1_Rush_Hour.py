# Created on 01/30/12 07:06:29
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""GIUK, Part I\nRush Hour\n\nA scenario for Global Conflicts 2.\n\nRush Hour is a typicall Cold War scenario putting Soviet \nsubs against a mixed US ASW force.\n\nWe are in the opening of WW 3. Soviet subs try to reach the Atlantic in \norder to strike on Nato supply convoys.\n\nYou are to blockade the Gap.\n\n\n""")
    SM.SetScenarioName("""GIUK Part I Rush Hour""")
    SM.CreateAlliance(1, 'USA')
    SM.SetAllianceDefaultCountry(1, 'USA')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 0)
    SM.SetUserAlliance(2)

    SM.SetDateTime(1985,8,2,12,0,0)
    SM.SetStartTheater(-9.750003, 55.883335) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(2)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """TASKING ORDERS FOR CMDR US OPERATIONS\n\nINTELLIGENCE\n\nSupply is critical in order to win the war. Therefore our convoys are \nprimary targets for hostile subs. War has just begun and Soviet subs will \ntry to strike on our sea lanes, thus crippling supplies. \n\nYou are to stop a group of Soviet subs on their way towards the open \nSea.  \n\nMISSION\n\nSink at least four Soviet subs.\n\nEXECUTION\n\nConduct aggressive ASW ops with your assets. Don't let any sub slip \nthrough your line of defence.\n\nYou have 12 hours to accomplish your goal. \n\nCOMMAND AND SIGNAL\n\nUSS Elliot\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """TASKING ORDERS:\n\n\nNO ADDITIONAL INTELLIGENCE AVAILABLE.\n""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'SH-60B'
    unit.unitName = "Spruance DDG Seahawk 1"
    unit.SetPosition(-9.607687, 62.140081, 510.2)
    unit.heading = 92.36
    unit.speed = 100.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-46 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '120 gallon tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '120 gallon tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'DICASS (80) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'LOFAR (80) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'DIFAR (80) Sonobuoy', 15)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'USS Elliot')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Sturgeon'
    unit.unitName = "USS Grayling"
    unit.SetPosition(-11.320615, 62.877019, -325.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'UGM-84C Harpoon', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Decoy-1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Decoy-1', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Grayling", 'Mk-48 Mod1/3/4', 12)
    SM.AddToUnitMagazine("USS Grayling", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Los Angeles'
    unit.unitName = "USS Portsmouth"
    unit.SetPosition(-10.155219, 62.705647, -325.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'UGM-84C Harpoon', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Portsmouth", 'Mk-48 Mod1/3/4', 20)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Los Angeles'
    unit.unitName = "USS Augusta"
    unit.SetPosition(-11.869050, 63.391191, -325.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'UGM-84C Harpoon', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Augusta", 'Mk-48 Mod1/3/4', 12)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Spruance DDG'
    unit.unitName = "USS Elliot"
    unit.SetPosition(-9.606783, 62.140081, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 2, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'RUM-139 Mod4 ASROC', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Elliot", 'Fuel', 65095)
    SM.AddToUnitMagazine("USS Elliot", 'Mk-46 Mod5', 34)
    SM.AddToUnitMagazine("USS Elliot", '120 gallon tank', 4)
    SM.AddToUnitMagazine("USS Elliot", 'AGM-114 Hellfire', 20)
    SM.AddToUnitMagazine("USS Elliot", 'Chaff-1', 100)
    SM.AddToUnitMagazine("USS Elliot", 'Flare-1', 100)
    SM.AddToUnitMagazine("USS Elliot", 'LOFAR (80) Sonobuoy', 258)
    SM.AddToUnitMagazine("USS Elliot", 'DICASS (80) Sonobuoy', 258)
    SM.AddToUnitMagazine("USS Elliot", 'DIFAR (80) Sonobuoy', 773)
    SM.AddToUnitMagazine("USS Elliot", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Elliot", '127mm mk 80 HE-PD mk 67', 1200)
    UI.SetSensorState(1, 0)
    UI.SetSensorState(3, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS Elliot', 'SH-60B', 'Spruance DDG Seahawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Elliot', 'Spruance DDG Seahawk 2', '1 Mk-46 Mod5;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Flare-1;5 LOFAR (80) Sonobuoy;5 DICASS (80) Sonobuoy;15 DIFAR (80) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Knox FFG'
    unit.unitName = "USS Oullet"
    unit.SetPosition(-11.766261, 62.448561, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '127mm mk 41 HC', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RUM-139 Mod4 ASROC', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm Mark 149-4', 90)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Oullet", 'Fuel', 21698)
    SM.AddToUnitMagazine("USS Oullet", 'Mk-46 Mod5', 18)
    SM.AddToUnitMagazine("USS Oullet", 'DICASS (80) Sonobuoy', 163)
    SM.AddToUnitMagazine("USS Oullet", 'LOFAR (80) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Oullet", 'DIFAR (80) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS Oullet", '20mm Mark 149-4', 485)
    SM.AddToUnitMagazine("USS Oullet", '127mm mk 41 HC', 340)
    SM.AddToUnitMagazine("USS Oullet", '127mm mk 41 AAC', 160)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS Oullet', 'SH-2F', 'Knox Seasprite 101', 2)
    SM.SetFlightDeckUnitLoadout('USS Oullet', 'Knox Seasprite 101', '2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Knox FFG'
    unit.unitName = "USS Fanning"
    unit.SetPosition(-13.701312, 63.400760, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '127mm mk 41 HC', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RUM-139 Mod4 ASROC', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm Mark 149-4', 90)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Fanning", 'Fuel', 21698)
    SM.AddToUnitMagazine("USS Fanning", 'Mk-46 Mod5', 18)
    SM.AddToUnitMagazine("USS Fanning", 'DICASS (80) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Fanning", 'LOFAR (80) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Fanning", 'DIFAR (80) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS Fanning", '20mm Mark 149-4', 485)
    SM.AddToUnitMagazine("USS Fanning", '127mm mk 41 HC', 340)
    SM.AddToUnitMagazine("USS Fanning", '127mm mk 41 AAC', 120)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS Fanning', 'SH-2F', 'Knox Seasprite 1', 2)
    SM.SetFlightDeckUnitLoadout('USS Fanning', 'Knox Seasprite 1', '2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671 Yorzh'
    unit.unitName = "K-147"
    unit.SetPosition(-9.712494, 63.159716, -206.7)
    unit.heading = 244.15
    unit.speed = 5.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-147", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-147", '53-65M', 6)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.219442, 1.078147, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 705 Lira'
    unit.unitName = "K-123"
    unit.SetPosition(-9.160621, 63.124995, -100.0)
    unit.heading = 90.00
    unit.speed = 5.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-123", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-123", '53-65M', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641B Som'
    unit.unitName = "B-303"
    unit.SetPosition(-8.239133, 62.859716, -200.0)
    unit.heading = 251.77
    unit.speed = 4.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-303", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-303", '53-65M', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.203821, 1.075390, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 971 Shchuka-B'
    unit.unitName = "K-284 Akula"
    unit.SetPosition(-10.295708, 63.582846, -325.0)
    unit.heading = 242.26
    unit.speed = 6.5
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
    SM.AddToUnitMagazine("K-284 Akula", 'SET-65M', 8)
    SM.AddToUnitMagazine("K-284 Akula", '65-76 Kit', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.229857, 1.083354, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 670 Skat'
    unit.unitName = "K-25"
    unit.SetPosition(-11.118361, 64.168237, -240.0)
    unit.heading = 226.73
    unit.speed = 4.6
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'P-70 Ametist', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-25", 'SET-65', 8)
    SM.AddToUnitMagazine("K-25", '53-65M', 4)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.232307, 1.082742, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 670 Skat'
    unit.unitName = "K-325"
    unit.SetPosition(-9.027466, 63.600092, -240.0)
    unit.heading = 244.38
    unit.speed = 4.8
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'P-70 Ametist', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-325", 'SET-65', 8)
    SM.AddToUnitMagazine("K-325", '53-65M', 4)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.221280, 1.079679, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('K-25')
    goal_temp.AddTarget('K-147')
    goal_temp.AddTarget('K-123')
    goal_temp.AddTarget('B-303')
    goal_temp.AddTarget('K-284 Akula')
    goal_temp.AddTarget('K-325')
    goal_temp.SetQuantity(4)
    goal_2_0 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(5999940.0)
    goal_temp.SetFailTimeout(43200.0)
    goal_2_1 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_2_0)
    goal_temp.AddGoal(goal_2_1)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.AreaGoal()
    goal_temp.SetTargetList('Sub')
    goal_temp.SetTimeObjective(0.000000)
    goal_temp.SetLogicAny(1)
    goal_temp.SetQuantity(3)
    goal_temp.AddPointDeg(-14.29300, 63.38785)
    goal_temp.AddPointDeg(-7.71185, 60.52725)
    goal_temp.AddPointDeg(-12.13438, 60.51848)
    goal_temp.AddPointDeg(-15.62678, 62.65076)
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 1, 1, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
