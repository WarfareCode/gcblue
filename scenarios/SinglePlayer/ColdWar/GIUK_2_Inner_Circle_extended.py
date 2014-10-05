# Created on 02/21/12 19:11:40
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""GIUK, Part II\n\nThe Inner Circle\nExtended Version\n\nA scenario for Global Conflicts 2.\n\nThe Inner Circle is the second scenario in a Cold War Battleset called \nGIUK. \n\nYour task is to stop a powerful Soviet Amphibious Task Force heading for \nIceland. In order to stop the invasion your subs have to break through \nthe outer escort circle in order to reach the inner circle where the LSTs \nare.\n\nIn the inner circle of the hostile formation, Iceland's face will be \ndecided. There is no way stopping those troops when their LSTs  come \nclose enough to the shore. \n\nGood Luck, Commander!\n\n\n\n\n""")
    SM.SetScenarioName("""GIUK Part 2a The Inner Circle """)
    SM.CreateAlliance(1, 'USA')
    SM.SetAllianceDefaultCountry(1, 'USA')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 0)
    SM.SetUserAlliance(1)

    SM.SetDateTime(1985,8,4,12,0,0)
    SM.SetStartTheater(-15.937500, 62.470837) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1511.807983,60.959999,1505.102417,304.800018,1501.444824,609.600037,1491.691162,914.400024,1484.985596,1219.200073,1487.119263,2362.199951,1502.664063,2743.199951,1507.235962,3962.400146,1527.657593,5181.600098,1548.079224')

    ####################
    SM.SetSimpleBriefing(1, """TASKING ORDERS FOR CMDR US OPERATIONS\n\nINTELLIGENCE\n\nWorld War  III is raging. The main battles are taking place on the central \nfront. Since it looks like a stalemate there, the Soviets try to outflank us \non several other hotspots.\n\nOne of those is Iceland. A large rock in the sea, but of extreme strategic \nvalue.\n\nThe Soviets have understood that and launched a mission to overrun the \n little defended island.\n\nA strong task force is underway, including three LSTs transporting the \nlanding troops.\n\nIt is supported by air assets flying from a Soviet forward base.\n\n\nMISSION\n\nStop the invasion of Iceland.\n\n\nEXECUTION\n\nUse your Orions to locate the hostile task force. Try to deflect hostile \ndefenses with your other air assets. Then close in with your subs. \nDo not waste torpedoes on the outer escorts. Proceed to the inner ring. \nBreak through and sink all three LSTs.\n\nBe careful, the LSTs are heavily guarded.\n\nGuard your few surface vessels against Soviet killer SSMs.\n\nYour last line of defence is the Norwegian sub assigned to your \ncommand. \n\nCOMMAND AND SIGNAL\n\nUSS Providence\n\n\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """TASKING ORDERS:\n\n\nNO ADDITIONAL INTELLIGENCE AVAILABLE.\n""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Type 22 FF Batch 2'
    unit.unitName = "HMS Boxer"
    unit.SetPosition(-22.020143, 63.365867, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Sea Wolf', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Sea Wolf', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MM-38 Exocet', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm/75 GCM-AO3-2 APDS', 83)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm/75 GCM-AO3-2 APDS', 83)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm/85  GAM-B01 HE-I', 50)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm/85  GAM-B01 HE-I', 50)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Stingray', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Boxer", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Boxer", 'Stingray', 29)
    SM.AddToUnitMagazine("HMS Boxer", 'Sea Skua', 16)
    SM.AddToUnitMagazine("HMS Boxer", 'LOFAR (80) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Boxer", 'DICASS (80) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Boxer", 'DIFAR (80) Sonobuoy', 609)
    SM.AddToUnitMagazine("HMS Boxer", 'Sea Wolf', 40)
    SM.AddToUnitMagazine("HMS Boxer", '30mm/75 GCM-AO3-2 APDS', 1660)
    SM.AddToUnitMagazine("HMS Boxer", '20mm/85  GAM-B01 HE-I', 500)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('HMS Boxer', 'Lynx HAS.Mk.2', 'Type 22 B2 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Boxer', 'Type 22 B2 Lynx 1', '1 Stingray;1 Stingray;5 DICASS (80) Sonobuoy;5 LOFAR (80) Sonobuoy;14 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Boxer', 'Lynx HAS.Mk.2', 'Type 22 B2 Lynx 2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Boxer', 'Type 22 B2 Lynx 2', '1 Stingray;1 Stingray;5 DICASS (80) Sonobuoy;5 LOFAR (80) Sonobuoy;14 DIFAR (80) Sonobuoy;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Hamburg DDG 1975'
    unit.unitName = "Bayern"
    unit.SetPosition(-22.266515, 63.335844, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MM-38 Exocet', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MM-38 Exocet', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '100mm OEA F1 HE', 35)
    SM.SetUnitLauncherItem(unit.unitName, 3, '100mm OPF F4 PFHE', 35)
    SM.SetUnitLauncherItem(unit.unitName, 4, '100mm OPF F4 PFHE', 35)
    SM.SetUnitLauncherItem(unit.unitName, 5, '40 mm L70 HE x5', 24)
    SM.SetUnitLauncherItem(unit.unitName, 6, '40 mm L70 HE x5', 24)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 9, '40 mm L70 HE x5', 24)
    SM.SetUnitLauncherItem(unit.unitName, 10, '40 mm L70 HE x5', 24)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Bayern", '100mm OEA F1 HE', 900)
    SM.AddToUnitMagazine("Bayern", '100mm OPF F4 PFHE', 1500)
    SM.AddToUnitMagazine("Bayern", '40 mm L70 HE x5', 640)
    SM.AddToUnitMagazine("Bayern", 'Mk-46 Mod5', 15)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Los Angeles (1985)'
    unit.unitName = "USS Providence"
    unit.SetPosition(-19.614866, 62.978948, -346.7)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod1/3/4', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'UGM-84C Harpoon', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'UGM-109C', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'UGM-109C', 6)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Providence", 'Mk-48 Mod1/3/4', 12)
    SM.AddToUnitMagazine("USS Providence", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Sturgeon'
    unit.unitName = "USS Cavella"
    unit.SetPosition(-19.491279, 62.619532, -163.3)
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
    SM.AddToUnitMagazine("USS Cavella", 'Mk-48 Mod1/3/4', 12)
    SM.AddToUnitMagazine("USS Cavella", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "AB Kevlavik"
    unit.SetPosition(-22.605763, 63.985466, 0.0)
    unit.heading = 153.09
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("AB Kevlavik", 'Fuel', 1007154)
    SM.AddToUnitMagazine("AB Kevlavik", 'Chaff-1', 10000)
    SM.AddToUnitMagazine("AB Kevlavik", 'Flare-1', 10000)
    SM.AddToUnitMagazine("AB Kevlavik", 'DICASS (80) Sonobuoy', 34)
    SM.AddToUnitMagazine("AB Kevlavik", 'LOFAR (80) Sonobuoy', 34)
    SM.AddToUnitMagazine("AB Kevlavik", 'DIFAR (80) Sonobuoy', 100)
    SM.AddToUnitMagazine("AB Kevlavik", 'Mk-46 Mod5', 60)
    SM.AddToUnitMagazine("AB Kevlavik", 'AGM-84E SLAM', 46)
    SM.AddToUnitMagazine("AB Kevlavik", 'AIM-7F', 226)
    SM.AddToUnitMagazine("AB Kevlavik", '20mm PGU', 200)
    SM.AddToUnitMagazine("AB Kevlavik", '600 gallon tank', 80)
    SM.AddToUnitMagazine("AB Kevlavik", 'AIM-9L', 226)
    SM.AddToUnitMagazine("AB Kevlavik", 'AIM-9B', 8)
    SM.AddToUnitMagazine("AB Kevlavik", '300 gallon wing tank', 100)
    SM.AddToUnitMagazine("AB Kevlavik", 'AGM-45A', 8)
    SM.AddToUnitMagazine("AB Kevlavik", 'AGM-45B', 92)
    SM.AddToUnitMagazine("AB Kevlavik", 'AGM-65B', 42)
    SM.AddToUnitMagazine("AB Kevlavik", 'AIM-7C', 8)
    SM.AddToUnitMagazine("AB Kevlavik", 'AGM-12C', 4)
    SM.AddToUnitMagazine("AB Kevlavik", '370 gallon wing tank', 4)
    SM.AddToUnitMagazine("AB Kevlavik", 'GBU-10/B', 160)
    SM.AddToUnitMagazine("AB Kevlavik", 'GBU-24B/B', 50)
    SM.AddToUnitMagazine("AB Kevlavik", 'Mk-81', 50)
    SM.AddToUnitMagazine("AB Kevlavik", 'Mk-82', 50)
    SM.AddToUnitMagazine("AB Kevlavik", 'Mk-83', 50)
    SM.AddToUnitMagazine("AB Kevlavik", 'Mk-84', 50)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'P-3C II Orion', 'Sea Lion-1', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Sea Lion-1', '17 DICASS (80) Sonobuoy;17 LOFAR (80) Sonobuoy;50 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 AGM-84E SLAM;2 AGM-84E SLAM;2 Mk-46 Mod5;2 Mk-46 Mod5;8 Mk-46 Mod5;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'P-3C II Orion', 'Sea Lion-2', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Sea Lion-2', '17 DICASS (80) Sonobuoy;17 LOFAR (80) Sonobuoy;50 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 AGM-84E SLAM;2 AGM-84E SLAM;2 Mk-46 Mod5;2 Mk-46 Mod5;8 Mk-46 Mod5;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-15A', 'Ambush-1', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Ambush-1', '4 AIM-7F;2 AIM-9L;2 AIM-9L;3 600 gallon tank;30 Chaff-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-15A', 'Ambush-2', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Ambush-2', '4 AIM-7F;2 AIM-9L;2 AIM-9L;3 600 gallon tank;30 Chaff-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-15A', 'Ambush-3', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Ambush-3', '4 AIM-7F;2 AIM-9L;2 AIM-9L;3 600 gallon tank;30 Chaff-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-15A', 'Ambush-4', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Ambush-4', '4 AIM-7F;2 AIM-9L;2 AIM-9L;3 600 gallon tank;30 Chaff-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'A-7E Corsair II', 'Thunder-5', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Thunder-5', '2 300 gallon wing tank;2 AGM-65B;2 300 gallon wing tank;2 AIM-9L;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'A-7E Corsair II', 'Thunder-6', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Thunder-6', '2 300 gallon wing tank;2 AGM-65B;2 300 gallon wing tank;2 AIM-9L;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'A-7E Corsair II', 'Thunder-7', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Thunder-7', '2 300 gallon wing tank;2 AGM-65B;2 300 gallon wing tank;2 AIM-9L;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'A-7E Corsair II', 'Thunder-8', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Thunder-8', '2 300 gallon wing tank;2 AGM-65B;2 300 gallon wing tank;2 AIM-9L;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-4G', 'Blinder-1', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Blinder-1', '2 AGM-45B;2 AGM-45B;2 AIM-7F;2 AIM-7F;1 600 gallon centerline tank;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-4G', 'Blinder-2', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Blinder-2', '2 AGM-45B;2 AGM-45B;2 AIM-7F;2 AIM-7F;1 600 gallon centerline tank;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-111C', 'Vark-1', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Vark-1', '2 GBU-10/B;2 GBU-10/B;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-111C', 'Vark-2', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Vark-2', '2 GBU-10/B;2 GBU-10/B;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-111C', 'Vark-3', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Vark-3', '2 GBU-10/B;2 GBU-10/B;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-111C', 'Vark-4', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Vark-4', '2 GBU-10/B;2 GBU-10/B;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-111C', 'Vark-5', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Vark-5', '2 GBU-10/B;2 GBU-10/B;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-111C', 'Vark-6', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Vark-6', '2 GBU-10/B;2 GBU-10/B;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-111C', 'Vark-7', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Vark-7', '2 GBU-10/B;2 GBU-10/B;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-111C', 'Vark-8', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Vark-8', '2 GBU-10/B;2 GBU-10/B;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-111C', 'Vark-9', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Vark-9', '2 GBU-10/B;2 GBU-10/B;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-111C', 'Vark-10', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Vark-10', '2 GBU-10/B;2 GBU-10/B;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'KC-130F', 'Milk-1', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Milk-1', '')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'KC-130F', 'Milk-2', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Milk-2', '')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'KC-130F', 'Milk-3', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Milk-3', '')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'KC-130F', 'Milk-4', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Milk-4', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Kobben'
    unit.unitName = "HNoMS Kya"
    unit.SetPosition(-22.146709, 63.609949, -91.7)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'NT37C', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'NT37C', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HNoMS Kya", 'Type-612 Torpedo', 6)
    SM.AddToUnitMagazine("HNoMS Kya", 'NT37C', 6)
    UI.SetSensorState(3, 0)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Knox FFG'
    unit.unitName = "USS Stein"
    unit.SetPosition(-22.172493, 63.412333, 0.0)
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
    SM.AddToUnitMagazine("USS Stein", 'Fuel', 21698)
    SM.AddToUnitMagazine("USS Stein", 'Mk-46 Mod5', 18)
    SM.AddToUnitMagazine("USS Stein", 'DICASS (80) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Stein", 'LOFAR (80) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Stein", 'DIFAR (80) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS Stein", '20mm Mark 149-4', 485)
    SM.AddToUnitMagazine("USS Stein", '127mm mk 41 HC', 340)
    SM.AddToUnitMagazine("USS Stein", '127mm mk 41 AAC', 120)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS Stein', 'SH-2F', 'Knox Seasprite 1', 2)
    SM.SetFlightDeckUnitLoadout('USS Stein', 'Knox Seasprite 1', '2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Lutjens DDG'
    unit.unitName = "Lutjens"
    unit.SetPosition(-22.074803, 63.322206, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-66A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '127mm mk 41 AAC', 40)
    SM.SetUnitLauncherItem(unit.unitName, 2, '127mm mk 41 AAC', 40)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RUR-5 ASROC', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Lutjens", '127mm mk 41 AAC', 360)
    SM.AddToUnitMagazine("Lutjens", '127mm mk 41 HC', 140)
    SM.AddToUnitMagazine("Lutjens", 'RIM-66A', 32)
    SM.AddToUnitMagazine("Lutjens", 'RGM-84C Harpoon', 8)
    SM.AddToUnitMagazine("Lutjens", 'Mk-46 Mod5', 12)
    SM.AddToUnitMagazine("Lutjens", 'RUR-5 ASROC', 16)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = '9K33M2 OSA-AK'
    unit.unitName = "SA-8B (2)"
    unit.SetPosition(-7.204944, 62.239088, 458.5)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M2', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33M2 OSA-AK'
    unit.unitName = "SA-8B (1)"
    unit.SetPosition(-7.178015, 62.296785, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M2', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641B Som'
    unit.unitName = "B-546"
    boxes = [[-19.4401, -19.0709, 62.6856, 63.0356]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -200.0)
    unit.heading = 281.33
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-546", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-546", '53-65M', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.342201, 1.099058, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.345151, 1.103319, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.353017, 1.096845, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.353837, 1.102827, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.363998, 1.098402, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.364653, 1.103401, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.377436, 1.101024, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.376125, 1.107580, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.386614, 1.107088, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1143 Krechet'
    unit.unitName = "Kiev"
    unit.SetPosition(-15.760006, 62.804314, 0.0)
    unit.heading = -79.99
    unit.speed = 14.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-500 Bazalt', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '76.2mm ZS-63 AA', 200)
    SM.SetUnitLauncherItem(unit.unitName, 6, '76.2mm ZS-63 AA', 200)
    SM.SetUnitLauncherItem(unit.unitName, 7, '76.2mm ZS-63 AA', 200)
    SM.SetUnitLauncherItem(unit.unitName, 8, '76.2mm ZS-63 AA', 200)
    SM.SetUnitLauncherItem(unit.unitName, 9, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 10, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 11, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 12, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 13, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 14, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 15, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 16, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 17, 'SAET-60M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 18, 'SAET-60M', 5)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Kiev", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Kiev", 'FAB-500', 72)
    SM.AddToUnitMagazine("Kiev", 'FAB-250', 168)
    SM.AddToUnitMagazine("Kiev", 'FAB-100', 192)
    SM.AddToUnitMagazine("Kiev", 'R-60', 96)
    SM.AddToUnitMagazine("Kiev", 'DIFAR (75) Sonobuoy', 5892)
    SM.AddToUnitMagazine("Kiev", 'LOFAR (75) Sonobuoy', 2100)
    SM.AddToUnitMagazine("Kiev", 'DICASS (75) Sonobuoy', 2100)
    SM.AddToUnitMagazine("Kiev", '23mm AM-23', 1368)
    SM.AddToUnitMagazine("Kiev", 'R-60MK', 96)
    SM.AddToUnitMagazine("Kiev", 'AT-1', 312)
    SM.AddToUnitMagazine("Kiev", 'S-8K 80mm', 4320)
    SM.AddToUnitMagazine("Kiev", 'S-8B 80mm', 4320)
    SM.AddToUnitMagazine("Kiev", 'S-5M Rocket', 5376)
    SM.AddToUnitMagazine("Kiev", 'S-5K Rocket', 5376)
    SM.AddToUnitMagazine("Kiev", '30mm OF-84 HE-FRAG AK-630M', 6720)
    SM.AddToUnitMagazine("Kiev", '76.2mm ZS-63 AA', 16000)	
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.302355, 1.096991, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.327146, 1.097845, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.364383, 1.101709, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.389481, 1.112086, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger1', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger1', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger2', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger2', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger3', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger3', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger4', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger4', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger5', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger5', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger6', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger6', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger7', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger7', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger8', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger8', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger9', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger9', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger10', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger10', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger11', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger11', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Yak-38M', 'Forger12', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Forger12', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix1', 2)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix1', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix2', 2)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix2', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix3', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix3', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix4', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix4', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix5', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix5', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix6', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix6', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix7', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix7', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix8', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix8', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix9', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix9', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix10', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix10', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix11', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix11', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix12', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix12', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix13', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix13', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix14', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix14', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix15', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix15', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix16', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix16', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix17', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix17', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix18', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix18', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Helix1')
    FP.AddAircraftToMission(mission_id, 'Helix9')
    FP.AddAircraftToMission(mission_id, 'Helix10')
    FP.AddAircraftToMission(mission_id, 'Helix11')
    FP.AddAircraftToMission(mission_id, 'Helix12')
    FP.AddAircraftToMission(mission_id, 'Helix13')
    FP.SetMissionLaunchTime(mission_id, '12:10:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'ASW-Helo')
    FP.SetMissionPatrolArea(mission_id, '-0.0014956,0.0023209,-0.0021624,0.0034340,0.0022398,0.0031365,0.0009980,0.0024535,')
    FP.SetMissionPatrolAnchor(mission_id, 'Kiev', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.2740640, 1.0971421, 500.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.2799710, 1.0975513, 300.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'ASWPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Forger1')
    FP.AddAircraftToMission(mission_id, 'Forger2')
    FP.AddAircraftToMission(mission_id, 'Forger3')
    FP.AddAircraftToMission(mission_id, 'Forger4')
    FP.AddAircraftToMission(mission_id, 'Forger5')
    FP.AddAircraftToMission(mission_id, 'Forger6')
    FP.SetMissionLaunchTime(mission_id, '12:10:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Standby-AAW')
    FP.SetMissionPatrolArea(mission_id, '-0.0094483,0.0221601,0.0061087,0.0220708,0.0056533,0.0028308,-0.0083027,0.0029221,')
    FP.SetMissionPatrolAnchor(mission_id, 'Kiev', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.2740640, 1.0971421, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.2822120, 1.0965780, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Helix2')
    FP.AddAircraftToMission(mission_id, 'Helix3')
    FP.AddAircraftToMission(mission_id, 'Helix4')
    FP.AddAircraftToMission(mission_id, 'Helix5')
    FP.AddAircraftToMission(mission_id, 'Helix6')
    FP.AddAircraftToMission(mission_id, 'Helix7')
    FP.SetMissionLaunchTime(mission_id, '12:20:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'ASW-Helo')
    FP.SetMissionPatrolArea(mission_id, '-0.0032199,-0.0023207,-0.0035947,-0.0000131,-0.0029924,0.0012947,-0.0011162,0.0019873,')
    FP.SetMissionPatrolAnchor(mission_id, 'Kiev', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.2740640, 1.0971421, 500.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.2764029, 1.0925997, 300.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'ASWPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Helix8')
    FP.AddAircraftToMission(mission_id, 'Helix14')
    FP.AddAircraftToMission(mission_id, 'Helix15')
    FP.AddAircraftToMission(mission_id, 'Helix16')
    FP.AddAircraftToMission(mission_id, 'Helix17')
    FP.AddAircraftToMission(mission_id, 'Helix18')
    FP.SetMissionLaunchTime(mission_id, '12:20:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'ASW-Helo')
    FP.SetMissionPatrolArea(mission_id, '0.0013894,0.0029278,0.0030748,0.0012520,0.0031217,-0.0013772,0.0019390,0.0009637,')
    FP.SetMissionPatrolAnchor(mission_id, 'Kiev', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.2740640, 1.0971421, 500.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.2764031, 1.0982190, 300.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'ASWPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Forger7')
    FP.AddAircraftToMission(mission_id, 'Forger8')
    FP.AddAircraftToMission(mission_id, 'Forger9')
    FP.AddAircraftToMission(mission_id, 'Forger10')
    FP.AddAircraftToMission(mission_id, 'Forger11')
    FP.AddAircraftToMission(mission_id, 'Forger12')
    FP.SetMissionLaunchTime(mission_id, '12:10:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Default')
    FP.SetMissionPatrolArea(mission_id, '0.0013528,0.0186580,-0.0032079,0.0100173,0.0007467,0.0084257,0.0062670,0.0095528,')
    FP.SetMissionPatrolAnchor(mission_id, 'Kiev', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.2740640, 1.0971421, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.2929351, 1.0983419, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641 SSK'
    unit.unitName = "B-103"
    unit.SetPosition(-21.723179, 63.320316, -70.0)
    unit.heading = 281.16
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-103", '53-65M', 4)
    SM.AddToUnitMagazine("B-103", 'SAET-60M', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.391227, 1.107504, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.377707, 1.107914, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.386925, 1.104739, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.374634, 1.106787, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.381189, 1.102588, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.372995, 1.106378, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.389793, 1.105456, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641B Som'
    unit.unitName = "B-215"
    unit.SetPosition(-21.843042, 63.393712, -154.4)
    unit.heading = 281.33
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-215", 'SET-65M', 24)
    SM.AddToUnitMagazine("B-215", '53-65M', 12)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.342201, 1.099058, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.345151, 1.103319, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.353017, 1.096845, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.353837, 1.102827, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.363998, 1.098402, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.364653, 1.103401, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.377436, 1.101024, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.376125, 1.107580, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.386614, 1.107088, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.385499, 1.107809, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.389890, 1.106304, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.385625, 1.103732, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.381359, 1.107433, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.391898, 1.107433, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Forward Airbase"
    unit.SetPosition(-7.176468, 62.274840, -0.0)
    unit.heading = 270.56
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Forward Airbase", 'Fuel', 1142200)
    SM.AddToUnitMagazine("Forward Airbase", 'Chaff-1', 10200)
    SM.AddToUnitMagazine("Forward Airbase", 'Flare-1', 10200)
    SM.AddToUnitMagazine("Forward Airbase", 'Kh-22', 300)
    SM.AddToUnitMagazine("Forward Airbase", 'FAB-500', 272)
    SM.AddToUnitMagazine("Forward Airbase", 'Kh-22M', 200)
    SM.AddToUnitMagazine("Forward Airbase", 'Kh-22MP', 100)
    SM.AddToUnitMagazine("Forward Airbase", '1520 Liter Tank', 100)
    SM.AddToUnitMagazine("Forward Airbase", 'FAB-100', 272)
    SM.AddToUnitMagazine("Forward Airbase", 'FAB-250', 200)
    SM.AddToUnitMagazine("Forward Airbase", 'R-27R', 176)
    SM.AddToUnitMagazine("Forward Airbase", 'R-60M', 148)
    SM.AddToUnitMagazine("Forward Airbase", 'R-73U', 152)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-95G', 'Spy-1', 2)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Spy-1', '2 Kh-22;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-95G', 'Spy-2', 2)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Spy-2', '2 Kh-22;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-95G', 'Spy-3', 2)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Spy-3', '2 Kh-22;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-95G', 'Spy-4', 2)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Spy-4', '2 Kh-22;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-95RT', 'Outpost-1', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Outpost-1', '48 Chaff-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-95RT', 'Outpost-2', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Outpost-2', '48 Chaff-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-95RT', 'Outpost-3', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Outpost-3', '48 Chaff-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-95RT', 'Outpost-4', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Outpost-4', '48 Chaff-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-1', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-1', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-2', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-2', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-3', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-3', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-4', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-4', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-5', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-5', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-6', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-6', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-7', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-7', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-8', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-8', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-9', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-9', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-10', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-10', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-11', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-11', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-12', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-12', '2 Kh-22M;24 FAB-500;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-1', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-1', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-2', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-2', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-3', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-3', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-4', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-4', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-5', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-5', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-6', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-6', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-7', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-7', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-8', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-8', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-9', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-9', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-10', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-10', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-11', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-11', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29', 'Shepherd-12', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-12', '1 1520 Liter Tank;2 R-27R;2 R-73U;2 R-73U;30 Flare-1;30 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Spy-1')
    FP.AddAircraftToMission(mission_id, 'Spy-2')
    FP.AddAircraftToMission(mission_id, 'Spy-3')
    FP.AddAircraftToMission(mission_id, 'Spy-4')
    FP.SetMissionLaunchTime(mission_id, '12:00:00+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Default')
    FP.SetMissionPatrolArea(mission_id, '-0.3745278,1.0993761,-0.4094461,1.0972320,-0.3340962,1.0836016,-0.3187812,1.0960068,')
    FP.AddMissionWaypointAdvanced(mission_id, -0.1242530, 1.0879010, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3243400, 1.0882310, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Outpost-1')
    FP.AddAircraftToMission(mission_id, 'Outpost-2')
    FP.AddAircraftToMission(mission_id, 'Outpost-3')
    FP.AddAircraftToMission(mission_id, 'Outpost-4')
    FP.SetMissionLaunchTime(mission_id, '12:00:00+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, 'Default')
    FP.SetMissionPatrolArea(mission_id, '-0.5007163,1.0864480,-0.4264691,1.0858353,-0.3892229,1.0819147,-0.4024551,1.0684375,')
    FP.AddMissionWaypointAdvanced(mission_id, -0.1242530, 1.0879010, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3933830, 1.0760020, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Shepherd-1')
    FP.AddAircraftToMission(mission_id, 'Shepherd-2')
    FP.AddAircraftToMission(mission_id, 'Shepherd-3')
    FP.AddAircraftToMission(mission_id, 'Shepherd-4')
    FP.AddAircraftToMission(mission_id, 'Shepherd-5')
    FP.AddAircraftToMission(mission_id, 'Shepherd-6')
    FP.SetMissionLaunchTime(mission_id, '12:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Standby-AAW')
    FP.SetMissionPatrolArea(mission_id, '-0.3476909,1.1079538,-0.3783033,1.0974653,-0.3730842,1.0905900,-0.3484660,1.1007221,')
    FP.AddMissionWaypointAdvanced(mission_id, -0.1242530, 1.0879010, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3494660, 1.0997220, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Shepherd-7')
    FP.AddAircraftToMission(mission_id, 'Shepherd-8')
    FP.AddAircraftToMission(mission_id, 'Shepherd-9')
    FP.AddAircraftToMission(mission_id, 'Shepherd-10')
    FP.AddAircraftToMission(mission_id, 'Shepherd-11')
    FP.AddAircraftToMission(mission_id, 'Shepherd-12')
    FP.SetMissionLaunchTime(mission_id, '13:00:00+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Default')
    FP.SetMissionPatrolArea(mission_id, '-0.3182579,1.0968630,-0.2886492,1.1097856,-0.2823060,1.0918390,-0.2910329,1.0859480,')
    FP.AddMissionWaypointAdvanced(mission_id, -0.1242530, 1.0879010, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.2823060, 1.0918390, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Terminator-1')
    FP.AddAircraftToMission(mission_id, 'Terminator-2')
    FP.AddAircraftToMission(mission_id, 'Terminator-3')
    FP.AddAircraftToMission(mission_id, 'Terminator-4')
    FP.AddAircraftToMission(mission_id, 'Terminator-5')
    FP.AddAircraftToMission(mission_id, 'Terminator-6')
    FP.AddAircraftToMission(mission_id, 'Terminator-7')
    FP.AddAircraftToMission(mission_id, 'Terminator-8')
    FP.AddAircraftToMission(mission_id, 'Terminator-9')
    FP.AddAircraftToMission(mission_id, 'Terminator-10')
    FP.AddAircraftToMission(mission_id, 'Terminator-11')
    FP.AddAircraftToMission(mission_id, 'Terminator-12')
    FP.SetMissionLaunchTime(mission_id, '12:00:00+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, 'Standby-ASuW')
    FP.SetMissionPatrolArea(mission_id, '-0.3799800,1.1138431,-0.3797169,1.1113435,-0.3783540,1.1106640,-0.3773540,1.1116641,')
    FP.AddMissionWaypointAdvanced(mission_id, -0.1242530, 1.0879010, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3783540, 1.1106640, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671 Yorzh'
    unit.unitName = "K-481"
    boxes = [[-19.3474, -19.1753, 62.5250, 62.7040]]
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
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-481", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-481", '53-65M', 6)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.340373, 1.100340, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.340059, 1.091401, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.341784, 1.100340, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.343196, 1.091558, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.343196, 1.100026, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.344137, 1.091871, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.356840, 1.098144, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.391969, 1.107867, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.379423, 1.108103, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "Doneckiy shakhter"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0060
    lat_deg = 57.296*leader_track.Lat + -0.0125
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -75.96
    unit.speed = 13.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Doneckiy shakhter", '9M32 Strela 2', 24)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kiev')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(1.757, 0.500, -1.610, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "BDK-100"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0083
    lat_deg = 57.296*leader_track.Lat + 0.0204
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -75.96
    unit.speed = 14.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("BDK-100", '9M32 Strela 2', 24)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kiev')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(1.936, 0.425, 1.203, 0.161)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "BDK-10"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0333
    lat_deg = 57.296*leader_track.Lat + 0.0019
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -77.47
    unit.speed = 14.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("BDK-10", '9M32 Strela 2', 24)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kiev')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(1.715, 0.531, 3.028, 0.277)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135 Burevestnik'
    unit.unitName = "Zadornyy"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1600
    lat_deg = 57.296*leader_track.Lat + 0.0036
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -77.01
    unit.speed = 14.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 3, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RPK-3 Metel', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Zadornyy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kiev')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(8.138, 0.500, -0.179, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135 Burevestnik'
    unit.unitName = "Storozhevoy"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0837
    lat_deg = 57.296*leader_track.Lat + 0.0030
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -77.01
    unit.speed = 14.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 3, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RPK-3 Metel', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Storozhevoy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kiev')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(4.284, 0.500, 2.957, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1164 Atlant'
    unit.unitName = "Moskva"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0703
    lat_deg = 57.296*leader_track.Lat + 0.0041
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -77.01
    unit.speed = 14.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55RM', 64)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 3, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 8, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 9, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 10, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 11, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 12, '3M45 Granit', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Moskva", 'Fuel', 68850)
    SM.AddToUnitMagazine("Moskva", 'AT-1', 28)
    SM.AddToUnitMagazine("Moskva", 'DICASS (75) Sonobuoy', 175)
    SM.AddToUnitMagazine("Moskva", 'LOFAR (75) Sonobuoy', 175)
    SM.AddToUnitMagazine("Moskva", 'DIFAR (75) Sonobuoy', 490)
    SM.AddToUnitMagazine("Moskva", 'DICASS (80) Sonobuoy', 26)
    SM.AddToUnitMagazine("Moskva", '30mm OF-84 HE-FRAG AK-630M', 1416)
    SM.AddToUnitMagazine("Moskva", '130mm F-44 HE', 500)
    SM.AddToUnitMagazine("Moskva", '53-65M', 30)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kiev')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(3.467, 0.500, -0.147, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Moskva', 'Ka-27A', 'Atlant Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Moskva', 'Atlant Ka-27 1', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135M Burevestnik-M'
    unit.unitName = "Gromkiy"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0344
    lat_deg = 57.296*leader_track.Lat + -0.0090
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -76.76
    unit.speed = 13.5
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
    SM.AddToUnitMagazine("Gromkiy", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Gromkiy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kiev')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(2.090, 0.500, -0.835, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135M Burevestnik-M'
    unit.unitName = "Ryavnyy"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0416
    lat_deg = 57.296*leader_track.Lat + 0.0208
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -77.91
    unit.speed = 13.5
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
    SM.AddToUnitMagazine("Ryavnyy", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Ryavnyy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Kiev')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(2.822, 0.500, 0.582, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('BDK-10')
    goal_temp.AddTarget('BDK-100')
    goal_temp.AddTarget('Doneckiy shakhter')
    goal_temp.SetQuantity(3)
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.AreaGoal()
    goal_temp.SetTargetList('BDK-100, BDK-10, Doneckiy shakhter')
    goal_temp.SetTimeObjective(0.000000)
    goal_temp.SetLogicAny(1)
    goal_temp.SetQuantity(1)
    goal_temp.AddPointDeg(-21.87281, 63.79837)
    goal_temp.AddPointDeg(-21.67729, 63.57121)
    goal_temp.AddPointDeg(-22.66066, 63.56259)
    goal_temp.AddPointDeg(-22.72391, 63.77824)
    goal_7_0 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_7_0)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    SM.OverlayText('', -22.6058, 63.9855, '0x000000FF')
    ##############################
    ### Randomization Info
    ##############################
    SM.SetIncludeProbability('B-227', 0.500000)
    SM.AddRandomBox('B-227', -19.3143, -19.2743, 62.7683, 62.8083)
    SM.SetIncludeProbability('B-524', 0.500000)
    SM.AddRandomBox('B-524', -19.8955, -16.9916, 62.1947, 63.2690)
    SM.SetIncludeProbability('B-546', 1.000000)
    SM.AddRandomBox('B-546', -19.4401, -19.0709, 62.6856, 63.0356)
    SM.SetIncludeProbability('K-239 Karp', 0.500000)
    SM.AddRandomBox('K-239 Karp', -19.2834, -18.8817, 62.2763, 62.6756)
    SM.SetIncludeProbability('K-481', 1.000000)
    SM.AddRandomBox('K-481', -19.3474, -19.1753, 62.5250, 62.7040)
