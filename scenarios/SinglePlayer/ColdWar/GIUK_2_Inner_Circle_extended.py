# Created on 11/08/14 23:13:18
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
    SM.SetStartTheater(-22.470835, 62.470837) # (lon, lat) in degrees, negative is West or South
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
    SM.SetFlightDeckUnitLoadout('HMS Boxer', 'Type 22 B2 Lynx 1', '1 A-244S;1 A-244S;')
    
    SM.AddUnitToFlightDeck('HMS Boxer', 'Lynx HAS.Mk.2', 'Type 22 B2 Lynx 2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Boxer', 'Type 22 B2 Lynx 2', '1 A-244S;1 A-244S;')
    
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
    unit.className = 'SSN 688 Los Angeles (1985)'
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
    SM.SetUnitLauncherItem(unit.unitName, 4, 'UGM-109A', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'UGM-109A', 6)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Providence", 'Mk-48 Mod1/3/4', 12)
    SM.AddToUnitMagazine("USS Providence", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSN 637 Sturgeon'
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
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip(USA)'
    unit.unitName = "AB Kevlavik"
    unit.SetPosition(-22.605763, 63.985466, 0.0)
    unit.heading = 153.09
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("AB Kevlavik", 'Fuel', 1007154)
    SM.AddToUnitMagazine("AB Kevlavik", 'Chaff-1', 10300)
    SM.AddToUnitMagazine("AB Kevlavik", 'Flare-1', 9700)
    SM.AddToUnitMagazine("AB Kevlavik", 'DICASS (80) Sonobuoy', 80)
    SM.AddToUnitMagazine("AB Kevlavik", 'LOFAR (80) Sonobuoy', 80)
    SM.AddToUnitMagazine("AB Kevlavik", 'DIFAR (80) Sonobuoy', 240)
    SM.AddToUnitMagazine("AB Kevlavik", 'Mk-46 Mod5', 64)
    SM.AddToUnitMagazine("AB Kevlavik", 'AGM-84C Harpoon', 42)
    SM.AddToUnitMagazine("AB Kevlavik", 'AIM-7F', 226)
    SM.AddToUnitMagazine("AB Kevlavik", '20mm PGU', 8)
    SM.AddToUnitMagazine("AB Kevlavik", '600 gallon tank', 80)
    SM.AddToUnitMagazine("AB Kevlavik", 'AIM-9L', 226)
    SM.AddToUnitMagazine("AB Kevlavik", '300 gallon wing tank', 100)
    SM.AddToUnitMagazine("AB Kevlavik", 'AGM-45B', 92)
    SM.AddToUnitMagazine("AB Kevlavik", '370 gallon wing tank', 4)
    SM.AddToUnitMagazine("AB Kevlavik", 'GBU-10/B', 160)
    SM.AddToUnitMagazine("AB Kevlavik", 'GBU-24B/B', 50)
    SM.AddToUnitMagazine("AB Kevlavik", 'Mk-81', 50)
    SM.AddToUnitMagazine("AB Kevlavik", 'Mk-82', 50)
    SM.AddToUnitMagazine("AB Kevlavik", 'Mk-83', 50)
    SM.AddToUnitMagazine("AB Kevlavik", 'Mk-84', 50)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('129_EngageLimit', '1')
    BB.Write('16_EngageLimit', '4')
    BB.Write('17_EngageLimit', '6')
    BB.Write('18_EngageLimit', '12')
    BB.Write('22_EngageLimit', '24')
    BB.Write('256_EngageLimit', '2')
    BB.Write('257_EngageLimit', '24')
    BB.Write('258_EngageLimit', '2')
    BB.Write('32_EngageLimit', '1')
    BB.Write('33_EngageLimit', '1')
    BB.Write('34_EngageLimit', '1')
    BB.Write('64_EngageLimit', '1')
    BB.Write('InvMulti', '1')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "Alt+": 0, "Speed+": 0, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 0, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 0, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {}}')
    BB.Write('loadouts_dict', '{"Air to Air": {"F-4G": {"AW1  2004": {"AIM-9X": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-7P": 4}, "AW1E  1985": {"370 gallon wing tank": 2, "AIM-9M": 4, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "600 gallon centerline tank": 1}, "AW1E  1968": {"AIM-9H": 4, "370 gallon wing tank": 2, "Chaff-1": 30, "AIM-7E": 4, "Flare-1": 30, "600 gallon centerline tank": 1}, "AW1E  1975": {"AIM-9H": 4, "370 gallon wing tank": 2, "AIM-7F": 4, "Chaff-1": 30, "Flare-1": 30, "600 gallon centerline tank": 1}, "AW1E  1989": {"370 gallon wing tank": 2, "AIM-9M": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-7P": 4, "600 gallon centerline tank": 1}, "AW1E  1964": {"370 gallon wing tank": 2, "Chaff-1": 30, "AIM-9E": 4, "AIM-7E": 4, "Flare-1": 30, "600 gallon centerline tank": 1}, "AW1E  1984": {"AIM-7F": 4, "370 gallon wing tank": 2, "AIM-9M": 4, "Chaff-1": 30, "Flare-1": 30, "600 gallon centerline tank": 1}, "AW1E  1978": {"AIM-7F": 4, "370 gallon wing tank": 2, "AIM-9J": 4, "Chaff-1": 30, "Flare-1": 30, "600 gallon centerline tank": 1}, "AW1E  1980": {"AIM-7F": 4, "370 gallon wing tank": 2, "AIM-9L": 4, "Chaff-1": 30, "Flare-1": 30, "600 gallon centerline tank": 1}, "AW1E  1963": {"370 gallon wing tank": 2, "AIM-9B": 4, "AIM-7C": 4, "Chaff-1": 30, "Flare-1": 30, "600 gallon centerline tank": 1}, "AW1  1964": {"AIM-7E": 4, "Chaff-1": 30, "AIM-9E": 4, "Flare-1": 30}, "AW1E  2004": {"370 gallon wing tank": 2, "Chaff-1": 30, "Flare-1": 30, "AIM-9X": 4, "AIM-7P": 4, "600 gallon centerline tank": 1}, "AW1  1989": {"Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30, "AIM-7P": 4}, "AW1  1975": {"AIM-9H": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-7F": 4}, "AW1  1963": {"Chaff-1": 30, "AIM-9B": 4, "AIM-7C": 4, "Flare-1": 30}, "AW1  1980": {"AIM-7F": 4, "Chaff-1": 30, "AIM-9L": 4, "Flare-1": 30}, "AW1  1978": {"AIM-7F": 4, "AIM-9J": 4, "Chaff-1": 30, "Flare-1": 30}, "AW1  1968": {"AIM-9H": 4, "AIM-7E": 4, "Chaff-1": 30, "Flare-1": 30}, "AW1  1984": {"AIM-7F": 4, "Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30}, "AW1  1985": {"AIM-7M": 4, "Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30}}, "A-7E(79)": {"AW1E 1980": {"20mm PGU-28/B": 48, "Chaff-1": 30, "300 gallon tank": 4, "AIM-9P4": 2, "Flare-1": 30}, "AW1E 1978": {"AIM-9P": 2, "20mm PGU-28/B": 48, "Chaff-1": 30, "300 gallon tank": 4, "Flare-1": 30}, "AW1E 1979": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 4, "AIM-9L": 2}, "AW1E 1975": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 4, "AIM-9N": 2}, "AW1E 1971": {"AIM-9H": 2, "20mm PGU-28/B": 48, "Chaff-1": 30, "300 gallon tank": 4, "Flare-1": 30}, "AW1E 1973": {"20mm PGU-28/B": 48, "AIM-9J": 2, "Chaff-1": 30, "300 gallon tank": 4, "Flare-1": 30}, "AW1  1973": {"20mm PGU-28/B": 48, "AIM-9J": 2, "Chaff-1": 30, "Flare-1": 30}, "AW1  1971": {"AIM-9H": 2, "Chaff-1": 30, "Flare-1": 30, "20mm PGU-28/B": 48}, "AW1  1975": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "AIM-9N": 2}, "AW1  1980": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "AIM-9P4": 2}, "AW1  1978": {"AIM-9P": 2, "Chaff-1": 30, "Flare-1": 30, "20mm PGU-28/B": 48}, "AW1  1979": {"20mm PGU-28/B": 48, "Chaff-1": 30, "AIM-9L": 2, "Flare-1": 30}, "AW1  1984": {"20mm PGU-28/B": 48, "Chaff-1": 30, "AIM-9M": 2, "Flare-1": 30}, "AW1E 1984": {"20mm PGU-28/B": 48, "Chaff-1": 30, "AIM-9M": 2, "300 gallon tank": 4, "Flare-1": 30}}, "F-15A": {"AW1 2010": {"20mm PGU": 46, "AIM-120D": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-9X": 4}, "AWE1 2010": {"20mm PGU": 46, "AIM-120D": 4, "Chaff-1": 60, "600 gallon tank": 3, "AIM-9X": 4}, "AWE2 1978": {"Chaff-1": 60, "AIM-7F": 4, "20mm PGU": 46, "AIM-9J": 4, "600 gallon tank": 3}, "AWE2 1975": {"20mm PGU": 46, "AIM-7F": 4, "Chaff-1": 60, "600 gallon tank": 3, "AIM-9H": 4}, "AWE2 1974": {"20mm PGU": 46, "AIM-9H": 4, "AIM-7E": 4, "Chaff-1": 60, "600 gallon tank": 3}, "AWE2 2004": {"20mm PGU": 46, "AIM-9X": 4, "Chaff-1": 60, "600 gallon tank": 3, "AIM-7P": 4}, "AW1 2004": {"20mm PGU": 46, "AIM-9X": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-120C5": 4}, "AW1 2006": {"20mm PGU": 46, "AIM-9X": 4, "Chaff-1": 30, "AIM-120C7": 4, "Flare-1": 30}, "AW1 2002": {"20mm PGU": 46, "Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30, "AIM-120C5": 4}, "AW2 1984": {"20mm PGU": 46, "AIM-7F": 4, "Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30}, "AW2 1985": {"20mm PGU": 46, "AIM-7M": 4, "Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30}, "AWE1 1998": {"20mm PGU": 46, "600 gallon tank": 3, "Chaff-1": 60, "AIM-9M": 4, "AIM-120C": 4}, "AWE1 2002": {"20mm PGU": 46, "600 gallon tank": 3, "Chaff-1": 60, "AIM-9M": 4, "AIM-120C5": 4}, "AW2 1980": {"20mm PGU": 46, "AIM-7F": 4, "Chaff-1": 30, "AIM-9L": 4, "Flare-1": 30}, "AWE1 2004": {"20mm PGU": 46, "AIM-9X": 4, "Chaff-1": 60, "600 gallon tank": 3, "AIM-120C5": 4}, "AWE1 2006": {"20mm PGU": 46, "AIM-9X": 4, "Chaff-1": 60, "AIM-120C7": 4, "600 gallon tank": 3}, "AWE1 1991": {"20mm PGU": 46, "AIM-9M": 4, "Chaff-1": 60, "AIM-120A": 4, "600 gallon tank": 3}, "AW2 1989": {"20mm PGU": 46, "Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30, "AIM-7P": 4}, "AWE1 1995": {"20mm PGU": 46, "600 gallon tank": 3, "Chaff-1": 60, "AIM-9M": 4, "AIM-120B": 4}, "AW1 1998": {"20mm PGU": 46, "Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30, "AIM-120C": 4}, "AW1 1991": {"20mm PGU": 46, "AIM-9M": 4, "Chaff-1": 30, "AIM-120A": 4, "Flare-1": 30}, "AW1 1995": {"20mm PGU": 46, "Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30, "AIM-120B": 4}, "AWE2 1980": {"20mm PGU": 46, "AIM-7F": 4, "Chaff-1": 60, "600 gallon tank": 3, "AIM-9L": 4}, "AW2 1978": {"20mm PGU": 46, "AIM-7F": 4, "AIM-9J": 4, "Chaff-1": 30, "Flare-1": 30}, "AWE2 1984": {"20mm PGU": 46, "AIM-7F": 4, "Chaff-1": 60, "AIM-9M": 4, "600 gallon tank": 3}, "AWE2 1985": {"20mm PGU": 46, "600 gallon tank": 3, "AIM-7M": 4, "Chaff-1": 60, "AIM-9M": 4}, "AW2 2004": {"20mm PGU": 46, "AIM-9X": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-7P": 4}, "AWE2 1989": {"20mm PGU": 46, "600 gallon tank": 3, "Chaff-1": 60, "AIM-9M": 4, "AIM-7P": 4}, "AW2 1975": {"20mm PGU": 46, "AIM-7F": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-9H": 4}, "AW2 1974": {"20mm PGU": 46, "AIM-9H": 4, "AIM-7E": 4, "Chaff-1": 30, "Flare-1": 30}}}, "Unknown": {"P-3C II Orion": {"AG1 92": {"AGM-65D": 4, "LOFAR (90) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 14, "DICASS (90) Sonobuoy": 17, "DIFAR (90) Sonobuoy": 50}, "AS1 97": {"DICASS (95) Sonobuoy": 17, "DIFAR (95) Sonobuoy": 50, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 14, "LOFAR (95) Sonobuoy": 17}, "AG5 07": {"Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-54": 14}, "AG1 02": {"AGM-65D": 4, "DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 14, "DIFAR (100) Sonobuoy": 50}, "AS1 92": {"LOFAR (90) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 14, "DICASS (90) Sonobuoy": 17, "AGM-84E SLAM": 4, "DIFAR (90) Sonobuoy": 50}, "AG1 97": {"AGM-65D": 4, "DICASS (95) Sonobuoy": 17, "DIFAR (95) Sonobuoy": 50, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 14, "LOFAR (95) Sonobuoy": 17}, "AS5 07": {"Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-54": 14}, "AG5 04": {"AGM-65D": 4, "DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "DIFAR (100) Sonobuoy": 50, "Mk-54": 14}, "AG4 06": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DIFAR (100) Sonobuoy": 50, "Mk-54": 12, "Mk-50": 2}, "AG4 07": {"Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-54": 12, "Mk-50": 2}, "AG2 06": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "Mk-46 Mod5": 12, "DIFAR (100) Sonobuoy": 50, "Mk-50": 2}, "AG2 07": {"Mk-46 Mod5": 12, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-50": 2}, "AG2 02": {"AGM-65D": 4, "DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "DIFAR (100) Sonobuoy": 50, "Mk-50": 2}, "AG5 06": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DIFAR (100) Sonobuoy": 50, "Mk-54": 14}, "AS4 04": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "DIFAR (100) Sonobuoy": 50, "Mk-54": 12, "Mk-50": 2}, "AG3 07": {"Mk-46 Mod5": 12, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-54": 2}, "AS5 04": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "DIFAR (100) Sonobuoy": 50, "Mk-54": 14}, "AG1 87": {"AGM-65D": 4, "DICASS (85) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 14, "LOFAR (85) Sonobuoy": 17, "DIFAR (85) Sonobuoy": 50}, "AG1 12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DICASS (110) Sonobuoy": 17, "Mk-46 Mod5": 14, "DIFAR (110) Sonobuoy": 50}, "AS3 12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 12, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50, "Mk-54": 2}, "AS4 12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50, "Mk-54": 12, "Mk-50": 2}, "AS1 96": {"LOFAR (90) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 14, "DICASS (90) Sonobuoy": 17, "DIFAR (90) Sonobuoy": 50}, "AS2 02": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 12, "DIFAR (100) Sonobuoy": 50, "Mk-50": 2}, "AS2 07": {"Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 12, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-50": 2}, "AG3 06": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "Mk-46 Mod5": 12, "DIFAR (100) Sonobuoy": 50, "Mk-54": 2}, "AS1 07": {"Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 14, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17}, "AG4 04": {"AGM-65D": 4, "DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "DIFAR (100) Sonobuoy": 50, "Mk-54": 12, "Mk-50": 2}, "AS1 02": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 14, "DIFAR (100) Sonobuoy": 50}, "AS5 12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50, "Mk-54": 14}, "AS1 87": {"DICASS (85) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 14, "LOFAR (85) Sonobuoy": 17, "AGM-84E SLAM": 4, "DIFAR (85) Sonobuoy": 50}, "AG5 12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50, "Mk-54": 14}, "AG3 12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DICASS (110) Sonobuoy": 17, "Mk-46 Mod5": 12, "DIFAR (110) Sonobuoy": 50, "Mk-54": 2}, "AS1 82": {"DICASS (80) Sonobuoy": 17, "LOFAR (80) Sonobuoy": 17, "Chaff-1": 30, "DIFAR (80) Sonobuoy": 50, "Flare-1": 30, "Mk-46 Mod5": 14, "AGM-84E SLAM": 4}, "AG2 12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DICASS (110) Sonobuoy": 17, "Mk-46 Mod5": 12, "DIFAR (110) Sonobuoy": 50, "Mk-50": 2}, "AG4 12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50, "Mk-54": 12, "Mk-50": 2}, "AS3 07": {"Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 12, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-54": 2}, "AS2 96": {"LOFAR (90) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 12, "DICASS (90) Sonobuoy": 17, "DIFAR (90) Sonobuoy": 50, "Mk-50": 2}, "AS3 04": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 12, "DIFAR (100) Sonobuoy": 50, "Mk-54": 2}, "AG2 97": {"AGM-65D": 4, "DICASS (95) Sonobuoy": 17, "DIFAR (95) Sonobuoy": 50, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "LOFAR (95) Sonobuoy": 17, "Mk-50": 2}, "AS2 92": {"LOFAR (90) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "DICASS (90) Sonobuoy": 17, "AGM-84E SLAM": 4, "DIFAR (90) Sonobuoy": 50, "Mk-50": 2}, "AS2 97": {"DICASS (95) Sonobuoy": 17, "DIFAR (95) Sonobuoy": 50, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 12, "LOFAR (95) Sonobuoy": 17, "Mk-50": 2}, "AS1 79": {"DIFAR (75) Sonobuoy": 50, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 14, "AGM-84A Harpoon": 4, "LOFAR (75) Sonobuoy": 17, "DICASS (75) Sonobuoy": 17}, "AG2 92": {"AGM-65D": 4, "LOFAR (90) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "DICASS (90) Sonobuoy": 17, "DIFAR (90) Sonobuoy": 50, "Mk-50": 2}, "AS1 77": {"DIFAR (75) Sonobuoy": 50, "Mk-44": 14, "Chaff-1": 30, "Flare-1": 30, "AGM-84A Harpoon": 4, "LOFAR (75) Sonobuoy": 17, "DICASS (75) Sonobuoy": 17}, "AS4 07": {"Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-54": 12, "Mk-50": 2}, "AG1 07": {"Mk-46 Mod5": 14, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17}, "AG1 06": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "AGM-65J": 4, "Mk-46 Mod5": 14, "DIFAR (100) Sonobuoy": 50}, "AG3 04": {"AGM-65D": 4, "DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "DIFAR (100) Sonobuoy": 50, "Mk-54": 2}, "AS1 12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 14, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50}, "AS2 12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "AGM-84H SLAM-ER": 4, "Flare-1": 30, "Mk-46 Mod5": 12, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50, "Mk-50": 2}}, "A-7E(79)": {"MN8  1968": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Mk-40 DST": 10, "Flare-1": 30}, "MN8  1967": {"20mm PGU-28/B": 48, "Mk-36 DST": 18, "Chaff-1": 30, "Flare-1": 30}, "MN5E 1900": {"20mm PGU-28/B": 48, "Chaff-1": 30, "300 gallon tank": 2, "Mk-36 Mod2 Mine": 2, "Flare-1": 30}, "MN2  1900": {"20mm PGU-28/B": 48, "Mk-10 Mod6 Mine": 6, "Chaff-1": 30, "Flare-1": 30}, "MN4E 1900": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 2, "Mk-36 Mod1 Mine": 2}, "MN2E 1900": {"20mm PGU-28/B": 48, "Mk-10 Mod6 Mine": 2, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}, "MN9E 1968": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Mk-41 DST": 2, "300 gallon tank": 2, "Flare-1": 30}, "MN6E 1900": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Mk-39 Mine": 2, "300 gallon tank": 2, "Flare-1": 30}, "MN6  1900": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Mk-39 Mine": 4, "Flare-1": 30}, "MN3E 1900": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "Mk-25 Mine": 2, "300 gallon tank": 2}, "MN1  1900": {"20mm PGU-28/B": 48, "Mk-10 Mod5 Mine": 6, "Chaff-1": 30, "Flare-1": 30}, "MN5  1900": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "Mk-36 Mod2 Mine": 4}, "MN4  1900": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "Mk-36 Mod1 Mine": 4}, "MN3  1900": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Mk-25 Mine": 4, "Flare-1": 30}, "MN8E 1968": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "Mk-40 DST": 6, "300 gallon tank": 2}, "MN9  1968": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Mk-41 DST": 4, "Flare-1": 30}, "MN8E 1967": {"20mm PGU-28/B": 48, "Mk-36 DST": 10, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}, "MN10E 1968": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 2, "Mk-59 DST": 6}, "MN10 1968": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "Mk-59 DST": 12}, "MN7E 1900": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 2, "Mk-56 Mine": 2}, "MN1E 1900": {"20mm PGU-28/B": 48, "Mk-10 Mod5 Mine": 2, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}, "MN7  1900": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "Mk-56 Mine": 4}}}, "Torpedoes": {"P-3C II Orion": {"T1  82": {"DICASS (80) Sonobuoy": 17, "LOFAR (80) Sonobuoy": 17, "Chaff-1": 30, "DIFAR (80) Sonobuoy": 50, "Flare-1": 30, "Mk-46 Mod5": 18}, "T1  87": {"DICASS (85) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 18, "LOFAR (85) Sonobuoy": 17, "DIFAR (85) Sonobuoy": 50}, "T4  07": {"Chaff-1": 30, "Flare-1": 30, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-54": 12, "Mk-50": 6}, "T4  04": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "DIFAR (100) Sonobuoy": 50, "Mk-54": 12, "Mk-50": 6}, "T2  12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50, "Mk-50": 6}, "T3  04": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "DIFAR (100) Sonobuoy": 50, "Mk-54": 6}, "T3  07": {"Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-54": 6}, "T5  12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50, "Mk-54": 18}, "T2  97": {"DICASS (95) Sonobuoy": 17, "DIFAR (95) Sonobuoy": 50, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "LOFAR (95) Sonobuoy": 17, "Mk-50": 6}, "T2  92": {"LOFAR (90) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "DICASS (90) Sonobuoy": 17, "DIFAR (90) Sonobuoy": 50, "Mk-50": 6}, "T1  12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 18, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50}, "T1  97": {"DICASS (95) Sonobuoy": 17, "DIFAR (95) Sonobuoy": 50, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 18, "LOFAR (95) Sonobuoy": 17}, "T1  92": {"LOFAR (90) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 18, "DICASS (90) Sonobuoy": 17, "DIFAR (90) Sonobuoy": 50}, "T1  79": {"DIFAR (75) Sonobuoy": 50, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 18, "LOFAR (75) Sonobuoy": 17, "DICASS (75) Sonobuoy": 17}, "T1  77": {"DIFAR (75) Sonobuoy": 50, "Mk-44": 18, "Chaff-1": 30, "Flare-1": 30, "LOFAR (75) Sonobuoy": 17, "DICASS (75) Sonobuoy": 17}, "T4  12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50, "Mk-54": 12, "Mk-50": 6}, "T3  12": {"LOFAR (110) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "DICASS (110) Sonobuoy": 17, "DIFAR (110) Sonobuoy": 50, "Mk-54": 6}, "T2  02": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "DIFAR (100) Sonobuoy": 50, "Mk-50": 6}, "T2  07": {"Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 12, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-50": 6}, "T5  07": {"Chaff-1": 30, "Flare-1": 30, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17, "Mk-54": 18}, "T1  02": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 18, "DIFAR (100) Sonobuoy": 50}, "T5  04": {"DICASS (100) Sonobuoy": 17, "LOFAR (100) Sonobuoy": 17, "Chaff-1": 30, "Flare-1": 30, "DIFAR (100) Sonobuoy": 50, "Mk-54": 18}, "T1  07": {"Chaff-1": 30, "Flare-1": 30, "Mk-46 Mod5": 18, "DIFAR (105) Sonobuoy": 50, "DICASS (105) Sonobuoy": 17, "LOFAR (105) Sonobuoy": 17}}}, "Close Support": {"A-7E(79)": {"CS2E 1900": {"20mm PGU-28/B": 48, "300 gallon tank": 2, "Chaff-1": 30, "Flare-1": 30, "Mk 71 Zuni WAFAR": 16, "Mk-82": 12}, "CS1  1900": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "Mk-82": 12, "Mk 16 Zuni FFAR": 24}, "CS3E 1900": {"20mm PGU-28/B": 48, "300 gallon tank": 2, "Chaff-1": 30, "Flare-1": 30, "50mm (2in) FFAR Rockets": 70, "Mk-82": 12}, "CS2  1900": {"20mm PGU-28/B": 48, "Mk 71 Zuni WAFAR": 24, "Chaff-1": 30, "Flare-1": 30, "Mk-82": 12}, "CS3  1900": {"20mm PGU-28/B": 48, "50mm (2in) FFAR Rockets": 108, "Chaff-1": 30, "Flare-1": 30, "Mk-82": 12}, "CS1E 1900": {"20mm PGU-28/B": 48, "300 gallon tank": 2, "Chaff-1": 30, "Flare-1": 30, "Mk-82": 12, "Mk 16 Zuni FFAR": 16}}}, "Suppression of Air Defences": {"F-4G": {"SD2  1971": {"AGM-78C": 2, "AIM-7E": 4, "Chaff-1": 30, "Flare-1": 30}, "SD2  1970": {"AGM-78B": 2, "AIM-7E": 4, "Chaff-1": 30, "Flare-1": 30}, "SD2  1975": {"AIM-7F": 4, "Chaff-1": 30, "Flare-1": 30, "AGM-78D": 2}, "SD2  1974": {"AIM-7E": 4, "Chaff-1": 30, "Flare-1": 30, "AGM-78D": 2}, "SD1  1975": {"AGM-45B": 2, "AIM-7F": 4, "Chaff-1": 30, "Flare-1": 30}, "SD2E  1969": {"370 gallon wing tank": 2, "AGM-78A": 2, "Chaff-1": 30, "AIM-7E": 4, "Flare-1": 30, "600 gallon centerline tank": 1}, "SD1  1973": {"AGM-45B": 2, "AIM-7E": 4, "Chaff-1": 30, "Flare-1": 30}, "SD2E  1985": {"370 gallon wing tank": 2, "AGM-45B": 2, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "600 gallon centerline tank": 1}, "SD1E  1973": {"370 gallon wing tank": 2, "AGM-45B": 2, "Chaff-1": 30, "AIM-7E": 4, "Flare-1": 30, "600 gallon centerline tank": 1}, "SD1E  1975": {"AIM-7F": 4, "370 gallon wing tank": 2, "AGM-45B": 2, "Chaff-1": 30, "Flare-1": 30, "600 gallon centerline tank": 1}, "SD3E  1987": {"370 gallon wing tank": 2, "AIM-7M": 4, "Chaff-1": 30, "AGM-88A": 2, "Flare-1": 30, "600 gallon centerline tank": 1}, "SD3E  1989": {"370 gallon wing tank": 2, "Chaff-1": 30, "Flare-1": 30, "AGM-88B": 2, "AIM-7P": 4, "600 gallon centerline tank": 1}, "SD3E  1988": {"370 gallon wing tank": 2, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "AGM-88B": 2, "600 gallon centerline tank": 1}, "SD1E  1985": {"370 gallon wing tank": 2, "AGM-45B": 2, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "600 gallon centerline tank": 1}, "SD2  1969": {"AIM-7E": 4, "AGM-78A": 2, "Chaff-1": 30, "Flare-1": 30}, "SD2  1985": {"AGM-45B": 2, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30}, "SD2E  1971": {"370 gallon wing tank": 2, "AGM-78C": 2, "Chaff-1": 30, "AIM-7E": 4, "Flare-1": 30, "600 gallon centerline tank": 1}, "SD2E  1970": {"370 gallon wing tank": 2, "AGM-78B": 2, "Chaff-1": 30, "AIM-7E": 4, "Flare-1": 30, "600 gallon centerline tank": 1}, "SD1E  1989": {"370 gallon wing tank": 2, "AGM-45B": 2, "Chaff-1": 30, "Flare-1": 30, "AIM-7P": 4, "600 gallon centerline tank": 1}, "SD2E  1974": {"370 gallon wing tank": 2, "Chaff-1": 30, "AIM-7E": 4, "AGM-78D": 2, "Flare-1": 30, "600 gallon centerline tank": 1}, "SD3  1993": {"Chaff-1": 30, "Flare-1": 30, "AGM-88C": 2, "AIM-7P": 4}, "SD1  1985": {"AGM-45B": 2, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30}, "SD2E  1975": {"AIM-7F": 4, "370 gallon wing tank": 2, "Chaff-1": 30, "Flare-1": 30, "AGM-78D": 2, "600 gallon centerline tank": 1}, "SD1  1989": {"AGM-45B": 2, "Chaff-1": 30, "Flare-1": 30, "AIM-7P": 4}, "SD1  1965": {"AIM-7E": 4, "AGM-45A": 2, "Chaff-1": 30, "Flare-1": 30}, "SD3  1989": {"AIM-7P": 4, "Chaff-1": 30, "Flare-1": 30, "AGM-88B": 2}, "SD3  1988": {"AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "AGM-88B": 2}, "SD3  1987": {"AIM-7M": 4, "Chaff-1": 30, "AGM-88A": 2, "Flare-1": 30}, "SD1E  1965": {"370 gallon wing tank": 2, "AGM-45A": 2, "Chaff-1": 30, "AIM-7E": 4, "Flare-1": 30, "600 gallon centerline tank": 1}, "SD3E  1993": {"370 gallon wing tank": 2, "Chaff-1": 30, "Flare-1": 30, "AGM-88C": 2, "AIM-7P": 4, "600 gallon centerline tank": 1}}, "A-7E(79)": {"SD1E 1988": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 2, "AGM-88B": 4}, "SD1E 1993": {"20mm PGU-28/B": 48, "Chaff-1": 30, "300 gallon tank": 2, "AGM-88C": 4, "Flare-1": 30}, "SD1E 1985": {"20mm PGU-28/B": 48, "Chaff-1": 30, "AGM-88A": 4, "300 gallon tank": 2, "Flare-1": 30}, "SD1  1993": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "AGM-88C": 6}, "SD1  1985": {"20mm PGU-28/B": 48, "Chaff-1": 30, "AGM-88A": 6, "Flare-1": 30}, "SD1  1988": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "AGM-88B": 6}}}, "Guided Bombs": {"A-7E(79)": {"GB9  1987": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "GBU-27/B": 4}, "GB9E 1987": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 2, "GBU-27/B": 2}, "GB2E 1976": {"GBU-10/B": 2, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 2, "20mm PGU-28/B": 48}, "GB8  1983": {"GBU-24B/B": 4, "Chaff-1": 30, "Flare-1": 30, "20mm PGU-28/B": 48}, "GB3  1976": {"GBU-11/B": 2, "20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30}, "GB2  1976": {"GBU-10/B": 4, "Chaff-1": 30, "Flare-1": 30, "20mm PGU-28/B": 48}, "GB7E 1983": {"GBU-24/B": 2, "20mm PGU-28/B": 48, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}, "GB4  1970": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "GBU-12/B": 6}, "GB4E 1970": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 2, "GBU-12/B": 4}, "GB7  1983": {"GBU-24/B": 4, "20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30}, "GB8E 1983": {"GBU-24B/B": 2, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 2, "20mm PGU-28/B": 48}, "GB5  1970": {"20mm PGU-28/B": 48, "Chaff-1": 30, "GBU-15/B": 6, "Flare-1": 30}, "GB3E 1976": {"GBU-11/B": 2, "20mm PGU-28/B": 48, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}, "GB1  1976": {"20mm PGU-28/B": 48, "GBU-1/B": 6, "Chaff-1": 30, "Flare-1": 30}, "GB5E 1970": {"20mm PGU-28/B": 48, "Chaff-1": 30, "GBU-15/B": 4, "300 gallon tank": 2, "Flare-1": 30}, "GB1E 1976": {"20mm PGU-28/B": 48, "GBU-1/B": 4, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}, "GB6  1970": {"20mm PGU-28/B": 48, "GBU-16/B": 6, "Chaff-1": 30, "Flare-1": 30}, "GB6E 1970": {"20mm PGU-28/B": 48, "GBU-16/B": 4, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}}}, "Unguided Rockets": {"F-4G": {"UR1  1975": {"AIM-7F": 4, "Chaff-1": 30, "Mk-40 FFAR": 285, "Flare-1": 30}, "UR1E  1985": {"600 gallon centerline tank": 1, "AIM-7M": 4, "Chaff-1": 30, "Mk-40 FFAR": 228, "Flare-1": 30}, "UR2E  1973": {"Chaff-1": 30, "AIM-7E": 4, "Mk 71 Zuni WAFAR": 48, "600 gallon centerline tank": 1, "Flare-1": 30}, "UR1E  1989": {"600 gallon centerline tank": 1, "Chaff-1": 30, "Mk-40 FFAR": 228, "Flare-1": 30, "AIM-7P": 4}, "UR1  1963": {"AIM-7C": 4, "Chaff-1": 30, "Mk-40 FFAR": 285, "Flare-1": 30}, "UR2E  1975": {"Chaff-1": 30, "AIM-7F": 4, "Mk 71 Zuni WAFAR": 48, "600 gallon centerline tank": 1, "Flare-1": 30}, "UR2  1985": {"AIM-7M": 4, "Mk 71 Zuni WAFAR": 60, "Chaff-1": 30, "Flare-1": 30}, "UR2  1964": {"AIM-7E": 4, "Chaff-1": 30, "Flare-1": 30, "Mk 16 Zuni FFAR": 60}, "UR1E  1963": {"600 gallon centerline tank": 1, "AIM-7C": 4, "Chaff-1": 30, "Mk-40 FFAR": 228, "Flare-1": 30}, "UR2  1989": {"Mk 71 Zuni WAFAR": 60, "Chaff-1": 30, "Flare-1": 30, "AIM-7P": 4}, "UR1E  1964": {"600 gallon centerline tank": 1, "AIM-7E": 4, "Chaff-1": 30, "Mk-40 FFAR": 228, "Flare-1": 30}, "UR2  1963": {"Chaff-1": 30, "AIM-7C": 4, "Flare-1": 30, "Mk 16 Zuni FFAR": 60}, "UR1  1985": {"AIM-7M": 4, "Chaff-1": 30, "Mk-40 FFAR": 285, "Flare-1": 30}, "UR1  1989": {"Chaff-1": 30, "Mk-40 FFAR": 285, "Flare-1": 30, "AIM-7P": 4}, "UR1  1964": {"AIM-7E": 4, "Chaff-1": 30, "Mk-40 FFAR": 285, "Flare-1": 30}, "UR2E  1964": {"AIM-7E": 4, "Chaff-1": 30, "600 gallon centerline tank": 1, "Flare-1": 30, "Mk 16 Zuni FFAR": 48}, "UR2E  1963": {"600 gallon centerline tank": 1, "Chaff-1": 30, "AIM-7C": 4, "Flare-1": 30, "Mk 16 Zuni FFAR": 48}, "UR2E  1985": {"Chaff-1": 30, "AIM-7M": 4, "Mk 71 Zuni WAFAR": 48, "600 gallon centerline tank": 1, "Flare-1": 30}, "UR2  1973": {"AIM-7E": 4, "Mk 71 Zuni WAFAR": 60, "Chaff-1": 30, "Flare-1": 30}, "UR2E  1989": {"Chaff-1": 30, "Mk 71 Zuni WAFAR": 48, "600 gallon centerline tank": 1, "Flare-1": 30, "AIM-7P": 4}, "UR2  1975": {"AIM-7F": 4, "Mk 71 Zuni WAFAR": 60, "Chaff-1": 30, "Flare-1": 30}, "UR1E  1975": {"600 gallon centerline tank": 1, "AIM-7F": 4, "Chaff-1": 30, "Mk-40 FFAR": 228, "Flare-1": 30}}, "A-7E(79)": {"UR2E 1900": {"20mm PGU-28/B": 48, "Mk 71 Zuni WAFAR": 24, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}, "UR1E 1900": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 2, "Mk 16 Zuni FFAR": 24}, "UR3  1900": {"20mm PGU-28/B": 48, "50mm (2in) FFAR Rockets": 146, "Chaff-1": 30, "Flare-1": 30}, "UR2  1900": {"20mm PGU-28/B": 48, "Mk 71 Zuni WAFAR": 32, "Chaff-1": 30, "Flare-1": 30}, "UR3E 1900": {"20mm PGU-28/B": 48, "50mm (2in) FFAR Rockets": 108, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}, "UR1  1900": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "Mk 16 Zuni FFAR": 32}}}, "Nuclear": {"F-4G": {"X2  1964": {"AIM-7E": 4, "AIM-9B": 4, "Chaff-1": 30, "B-57 Mod5 20kT": 1, "Flare-1": 30}, "X1E  2004": {"370 gallon wing tank": 2, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "Flare-1": 30, "AIM-9X": 4, "AIM-7P": 4}, "X2  1968": {"AIM-9H": 4, "AIM-7E": 4, "Chaff-1": 30, "B-57 Mod5 20kT": 1, "Flare-1": 30}, "X2  1984": {"AIM-7F": 4, "Chaff-1": 30, "AIM-9M": 4, "B-57 Mod5 20kT": 1, "Flare-1": 30}, "X2  1985": {"AIM-7M": 4, "Chaff-1": 30, "AIM-9M": 4, "B-57 Mod5 20kT": 1, "Flare-1": 30}, "X1  1975": {"AIM-9H": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "Flare-1": 30, "AIM-7F": 4}, "X2  1980": {"AIM-7F": 4, "Flare-1": 30, "Chaff-1": 30, "AIM-9L": 4, "B-57 Mod5 20kT": 1}, "X2  1989": {"Flare-1": 30, "Chaff-1": 30, "AIM-9M": 4, "B-57 Mod5 20kT": 1, "AIM-7P": 4}, "X1  1978": {"Chaff-1": 30, "AIM-7F": 4, "AIM-9J": 4, "B-57 Mod1 10kT": 1, "Flare-1": 30}, "X2  1963": {"Chaff-1": 30, "AIM-9B": 4, "AIM-7C": 4, "B-57 Mod5 20kT": 1, "Flare-1": 30}, "X1E  1963": {"370 gallon wing tank": 2, "AIM-9B": 4, "AIM-7C": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "Flare-1": 30}, "X2E  2004": {"370 gallon wing tank": 2, "Chaff-1": 30, "Flare-1": 30, "AIM-9X": 4, "AIM-7P": 4, "B-57 Mod5 20kT": 1}, "X1E  1964": {"370 gallon wing tank": 2, "AIM-9B": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "AIM-7E": 4, "Flare-1": 30}, "X1E  1968": {"AIM-9H": 4, "370 gallon wing tank": 2, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "AIM-7E": 4, "Flare-1": 30}, "X2E  1975": {"AIM-9H": 4, "370 gallon wing tank": 2, "AIM-7F": 4, "Chaff-1": 30, "Flare-1": 30, "B-57 Mod5 20kT": 1}, "X2  1978": {"AIM-7F": 4, "AIM-9J": 4, "Chaff-1": 30, "B-57 Mod5 20kT": 1, "Flare-1": 30}, "X1  2004": {"AIM-9X": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "Flare-1": 30, "AIM-7P": 4}, "X2  2004": {"AIM-9X": 4, "Flare-1": 30, "Chaff-1": 30, "B-57 Mod5 20kT": 1, "AIM-7P": 4}, "X2  1975": {"AIM-9H": 4, "Flare-1": 30, "Chaff-1": 30, "B-57 Mod5 20kT": 1, "AIM-7F": 4}, "X2E  1978": {"AIM-7F": 4, "370 gallon wing tank": 2, "AIM-9J": 4, "Chaff-1": 30, "Flare-1": 30, "B-57 Mod5 20kT": 1}, "X1E  1989": {"370 gallon wing tank": 2, "AIM-9M": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "Flare-1": 30, "AIM-7P": 4}, "X1  1968": {"AIM-9H": 4, "AIM-7E": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "Flare-1": 30}, "X1E  1980": {"AIM-7F": 4, "370 gallon wing tank": 2, "AIM-9L": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "Flare-1": 30}, "X1  1963": {"Chaff-1": 30, "B-57 Mod1 10kT": 1, "AIM-9B": 4, "AIM-7C": 4, "Flare-1": 30}, "X1E  1985": {"370 gallon wing tank": 2, "AIM-9M": 4, "AIM-7M": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "Flare-1": 30}, "X1  1964": {"B-57 Mod1 10kT": 1, "AIM-7E": 4, "Chaff-1": 30, "AIM-9E": 4, "Flare-1": 30}, "X1E  1984": {"AIM-7F": 4, "370 gallon wing tank": 2, "AIM-9M": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "Flare-1": 30}, "X2E  1989": {"370 gallon wing tank": 2, "AIM-9M": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-7P": 4, "B-57 Mod5 20kT": 1}, "X2E  1980": {"AIM-7F": 4, "370 gallon wing tank": 2, "AIM-9L": 4, "Chaff-1": 30, "Flare-1": 30, "B-57 Mod5 20kT": 1}, "X2E  1984": {"AIM-7F": 4, "370 gallon wing tank": 2, "AIM-9M": 4, "Chaff-1": 30, "Flare-1": 30, "B-57 Mod5 20kT": 1}, "X2E  1985": {"370 gallon wing tank": 2, "AIM-9M": 4, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "B-57 Mod5 20kT": 1}, "X1E  1975": {"AIM-9H": 4, "370 gallon wing tank": 2, "AIM-7F": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "Flare-1": 30}, "X1  1985": {"B-57 Mod1 10kT": 1, "AIM-7M": 4, "Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30}, "X1  1984": {"B-57 Mod1 10kT": 1, "AIM-7F": 4, "Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30}, "X1  1980": {"AIM-7F": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "AIM-9L": 4, "Flare-1": 30}, "X1E  1978": {"AIM-7F": 4, "370 gallon wing tank": 2, "AIM-9J": 4, "Chaff-1": 30, "B-57 Mod1 10kT": 1, "Flare-1": 30}, "X1  1989": {"B-57 Mod1 10kT": 1, "Chaff-1": 30, "AIM-9M": 4, "Flare-1": 30, "AIM-7P": 4}, "X2E  1964": {"370 gallon wing tank": 2, "Chaff-1": 30, "AIM-9B": 4, "Flare-1": 30, "B-57 Mod5 20kT": 1, "AIM-7E": 4}, "X2E  1963": {"370 gallon wing tank": 2, "AIM-9B": 4, "AIM-7C": 4, "Chaff-1": 30, "Flare-1": 30, "B-57 Mod5 20kT": 1}, "X2E  1968": {"AIM-9H": 4, "370 gallon wing tank": 2, "Chaff-1": 30, "Flare-1": 30, "B-57 Mod5 20kT": 1, "AIM-7E": 4}}}, "Unguided Bombs": {"F-4G": {"IB2E  1989": {"Chaff-1": 30, "Flare-1": 30, "AIM-7P": 4, "Mk-84": 2, "600 gallon centerline tank": 1, "Mk-83": 6}, "IB2  1963": {"Mk-84": 3, "Chaff-1": 30, "AIM-7C": 4, "Flare-1": 30, "Mk-83": 6}, "IB2  1964": {"Mk-84": 3, "AIM-7E": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-83": 6}, "IB2E  1985": {"AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-84": 2, "600 gallon centerline tank": 1, "Mk-83": 6}, "IB1E  1989": {"M117": 12, "Chaff-1": 30, "600 gallon centerline tank": 1, "Flare-1": 30, "AIM-7P": 4}, "IB3E  1964": {"AIM-7E": 4, "Chaff-1": 30, "600 gallon centerline tank": 1, "Flare-1": 30, "Mk-83": 12}, "IB3E  1963": {"600 gallon centerline tank": 1, "Chaff-1": 30, "AIM-7C": 4, "Flare-1": 30, "Mk-83": 12}, "IB4E  1963": {"600 gallon centerline tank": 1, "Chaff-1": 30, "AIM-7C": 4, "Flare-1": 30, "Mk-82": 18}, "IB3  1963": {"Chaff-1": 30, "AIM-7C": 4, "Flare-1": 30, "Mk-83": 15}, "IB3  1964": {"AIM-7E": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-83": 15}, "IB1E  1985": {"M117": 12, "Chaff-1": 30, "600 gallon centerline tank": 1, "AIM-7M": 4, "Flare-1": 30}, "IB2E  1975": {"AIM-7F": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-84": 2, "600 gallon centerline tank": 1, "Mk-83": 6}, "IB2  1985": {"Mk-84": 3, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-83": 6}, "IB4E  1975": {"AIM-7F": 4, "Chaff-1": 30, "600 gallon centerline tank": 1, "Flare-1": 30, "Mk-82": 18}, "IB2  1989": {"Mk-84": 3, "AIM-7P": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-83": 6}, "IB3E  1989": {"Chaff-1": 30, "AIM-7P": 4, "600 gallon centerline tank": 1, "Flare-1": 30, "Mk-83": 12}, "IB1E  1964": {"M117": 12, "Chaff-1": 30, "600 gallon centerline tank": 1, "AIM-7E": 4, "Flare-1": 30}, "IB4E  1964": {"AIM-7E": 4, "Chaff-1": 30, "600 gallon centerline tank": 1, "Flare-1": 30, "Mk-82": 18}, "IB1E  1963": {"600 gallon centerline tank": 1, "M117": 12, "Chaff-1": 30, "AIM-7C": 4, "Flare-1": 30}, "IB3E  1985": {"AIM-7M": 4, "Chaff-1": 30, "600 gallon centerline tank": 1, "Flare-1": 30, "Mk-83": 12}, "IB4  1975": {"AIM-7F": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-82": 24}, "IB1  1964": {"M117": 17, "Chaff-1": 30, "AIM-7E": 4, "Flare-1": 30}, "IB1  1963": {"M117": 17, "Chaff-1": 30, "AIM-7C": 4, "Flare-1": 30}, "IB1  1985": {"M117": 17, "Chaff-1": 30, "AIM-7M": 4, "Flare-1": 30}, "IB4  1963": {"Chaff-1": 30, "AIM-7C": 4, "Flare-1": 30, "Mk-82": 24}, "IB2  1975": {"Mk-84": 3, "AIM-7F": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-83": 6}, "IB4  1989": {"Chaff-1": 30, "Flare-1": 30, "Mk-82": 24, "AIM-7P": 4}, "IB4  1964": {"AIM-7E": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-82": 24}, "IB4  1985": {"AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-82": 24}, "IB1  1989": {"M117": 17, "Chaff-1": 30, "Flare-1": 30, "AIM-7P": 4}, "IB3  1975": {"AIM-7F": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-83": 15}, "IB2E  1963": {"AIM-7C": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-84": 2, "600 gallon centerline tank": 1, "Mk-83": 6}, "IB2E  1964": {"AIM-7E": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-84": 2, "600 gallon centerline tank": 1, "Mk-83": 6}, "IB1E  1975": {"AIM-7F": 4, "M117": 12, "Chaff-1": 30, "600 gallon centerline tank": 1, "Flare-1": 30}, "IB4E  1985": {"AIM-7M": 4, "Chaff-1": 30, "600 gallon centerline tank": 1, "Flare-1": 30, "Mk-82": 18}, "IB3  1985": {"AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-83": 15}, "IB4E  1989": {"Chaff-1": 30, "600 gallon centerline tank": 1, "Flare-1": 30, "Mk-82": 18, "AIM-7P": 4}, "IB3  1989": {"AIM-7P": 4, "Chaff-1": 30, "Flare-1": 30, "Mk-83": 15}, "IB1  1975": {"AIM-7F": 4, "M117": 17, "Chaff-1": 30, "Flare-1": 30}, "IB3E  1975": {"AIM-7F": 4, "Chaff-1": 30, "600 gallon centerline tank": 1, "Flare-1": 30, "Mk-83": 12}}, "A-7E(79)": {"IB3E 1960": {"20mm PGU-28/B": 48, "300 gallon tank": 2, "Chaff-1": 30, "Flare-1": 30, "Mk-84": 2, "Mk-83": 2}, "IB6  1960": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Mk-81": 12, "Flare-1": 30}, "IB1  1960": {"20mm PGU-28/B": 48, "M117": 4, "Chaff-1": 30, "M118": 2, "Flare-1": 30}, "IB2  1960": {"20mm PGU-28/B": 48, "M117": 12, "Chaff-1": 30, "Flare-1": 30}, "IB4E 1960": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "300 gallon tank": 2, "Mk-83": 6}, "IB2E 1960": {"20mm PGU-28/B": 48, "M117": 8, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}, "IB1E 1960": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "M118": 2, "300 gallon tank": 2}, "IB4  1960": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "Mk-83": 10}, "IB5  1960": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "Mk-82": 12}, "IB3  1960": {"Mk-84": 4, "20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30}, "IB6E 1960": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "Mk-81": 12, "300 gallon tank": 2}, "IB5E 1960": {"20mm PGU-28/B": 48, "Chaff-1": 30, "300 gallon tank": 2, "Mk-82": 12, "Flare-1": 30}}}, "Air to Ground Missile": {"F-4G": {"GM1E  1964": {"370 gallon wing tank": 2, "Chaff-1": 30, "AGM-12B": 2, "AIM-7E": 4, "Flare-1": 30, "600 gallon centerline tank": 1}, "GM1  1963": {"600 gallon centerline tank": 1, "AIM-7C": 4, "Chaff-1": 30, "AGM-12B": 4, "Flare-1": 30}, "GM1  1964": {"600 gallon centerline tank": 1, "AIM-7E": 4, "Chaff-1": 30, "AGM-12B": 4, "Flare-1": 30}, "GM1E  1963": {"370 gallon wing tank": 2, "AIM-7C": 4, "Chaff-1": 30, "AGM-12B": 2, "Flare-1": 30, "600 gallon centerline tank": 1}}, "A-7E(79)": {"GM3E 1976": {"20mm PGU-28/B": 48, "Chaff-1": 30, "300 gallon tank": 2, "AGM-65B": 12, "Flare-1": 30}, "GM3  1989": {"20mm PGU-28/B": 48, "AGM-65F": 18, "Chaff-1": 30, "Flare-1": 30}, "GM3  1976": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "AGM-65B": 18}, "GM3E 1973": {"20mm PGU-28/B": 48, "Flare-1": 30, "Chaff-1": 30, "AGM-65A": 12, "300 gallon tank": 2}, "GM3  1973": {"20mm PGU-28/B": 48, "Chaff-1": 30, "AGM-65A": 18, "Flare-1": 30}, "GM3E 1990": {"20mm PGU-28/B": 48, "AGM-65G": 12, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}, "GM2E 1975": {"20mm PGU-28/B": 48, "Chaff-1": 30, "AGM-62 mk23": 2, "300 gallon tank": 2, "Flare-1": 30}, "GM3  1986": {"AGM-65D": 18, "20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30}, "GM1E 1975": {"20mm PGU-28/B": 48, "Chaff-1": 30, "300 gallon tank": 2, "AGM-62 mk21": 6, "Flare-1": 30}, "GM3E 1986": {"AGM-65D": 12, "20mm PGU-28/B": 48, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}, "GM1  1975": {"20mm PGU-28/B": 48, "Chaff-1": 30, "Flare-1": 30, "AGM-62 mk21": 8}, "GM3  1990": {"20mm PGU-28/B": 48, "AGM-65G": 18, "Chaff-1": 30, "Flare-1": 30}, "GM2  1975": {"20mm PGU-28/B": 48, "Chaff-1": 30, "AGM-62 mk23": 4, "Flare-1": 30}, "GM3E 1989": {"20mm PGU-28/B": 48, "AGM-65F": 12, "Chaff-1": 30, "300 gallon tank": 2, "Flare-1": 30}}}}')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'P-3C II Orion', 'Sea Lion-1', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Sea Lion-1', '17 DICASS (80) Sonobuoy;17 LOFAR (80) Sonobuoy;50 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 AGM-84C Harpoon;2 AGM-84C Harpoon;2 Mk-46 Mod5;2 Mk-36 DST;6 Mk-36 DST;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'P-3C II Orion', 'Sea Lion-2', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Sea Lion-2', '17 DICASS (80) Sonobuoy;17 LOFAR (80) Sonobuoy;50 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 AGM-84C Harpoon;2 AGM-84C Harpoon;2 Mk-46 Mod5;2 Mk-36 DST;6 Mk-36 DST;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-15A', 'Ambush-1', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Ambush-1', '4 AIM-7F;2 AIM-9L;2 AIM-9L;3 600 gallon tank;30 Chaff-1;30 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-15A', 'Ambush-2', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Ambush-2', '4 AIM-7F;2 AIM-9L;2 AIM-9L;3 600 gallon tank;30 Chaff-1;30 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-15A', 'Ambush-3', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Ambush-3', '4 AIM-7F;2 AIM-9L;2 AIM-9L;3 600 gallon tank;30 Chaff-1;30 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-15A', 'Ambush-4', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Ambush-4', '4 AIM-7F;2 AIM-9L;2 AIM-9L;3 600 gallon tank;30 Chaff-1;30 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'A-7E(79)', 'Thunder-5', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Thunder-5', '6 AGM-65B;2 AGM-65B;6 AGM-65B;2 AIM-9L;48 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'A-7E(79)', 'Thunder-6', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Thunder-6', '6 AGM-65B;2 AGM-65B;6 AGM-65B;2 AIM-9L;48 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'A-7E(79)', 'Thunder-7', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Thunder-7', '6 AGM-65B;2 AGM-65B;6 AGM-65B;2 AIM-9L;48 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'A-7E(79)', 'Thunder-8', 1)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Thunder-8', '0 Empty;2 AGM-65B;6 AGM-65B;2 AIM-9L;48 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-4G', 'Blinder-1', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Blinder-1', '2 AGM-45B;2 AGM-45B;2 AIM-7F;2 AIM-7F;1 600 gallon centerline tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'F-4G', 'Blinder-2', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Blinder-2', '2 AGM-45B;2 AGM-45B;2 AIM-7F;2 AIM-7F;1 600 gallon centerline tank;30 Chaff-1;30 Flare-1;')
    
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
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'KC-130F', 'Milk-1', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Milk-1', '')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'KC-130F', 'Milk-2', 2)
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
    UI.AddTask('AvoidCav', 3.000000, 3)
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
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RUR-5 Mod4 ASROC', 4)
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
    BB.Write('129_EngageLimit', '1')
    BB.Write('16_EngageLimit', '4')
    BB.Write('17_EngageLimit', '6')
    BB.Write('18_EngageLimit', '12')
    BB.Write('22_EngageLimit', '24')
    BB.Write('256_EngageLimit', '2')
    BB.Write('257_EngageLimit', '24')
    BB.Write('258_EngageLimit', '2')
    BB.Write('32_EngageLimit', '1')
    BB.Write('33_EngageLimit', '1')
    BB.Write('34_EngageLimit', '1')
    BB.Write('64_EngageLimit', '1')
    BB.Write('InvMulti', '1')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"127mm mk 41 AAC": 120, "RUR-5 Mod4 ASROC": 0, "RGM-84*": 0, "RUR-5 ASROC": 0, "MU-90": 0, "Mk-46 Mod5": 36, "Mk-54": 0, "127mm mk 41 HC": 340, "20mm Mark 149-4": 485, "Stingray": 0, "RUM-139 Mod4 ASROC": 0, "Mk-15 Mod0": 0, "Mk-44": 0, "Mk-50": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 0, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"RUR-5 Mod4 ASROC": [4, 4], "127mm mk 41 HC": [40, 40], "20mm Mark 149-4": [90, 90], "Mk-46 Mod5": [4, 4], "RGM-84D Harpoon": [4, 4]}}')
    BB.Write('loadouts_dict', '{}')
    
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
    SM.AddToUnitMagazine("SA-8B (2)", '9M33M2', 36)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    BB.Write('129_EngageLimit', '1')
    BB.Write('16_EngageLimit', '4')
    BB.Write('17_EngageLimit', '6')
    BB.Write('18_EngageLimit', '12')
    BB.Write('22_EngageLimit', '24')
    BB.Write('256_EngageLimit', '2')
    BB.Write('257_EngageLimit', '24')
    BB.Write('258_EngageLimit', '2')
    BB.Write('32_EngageLimit', '1')
    BB.Write('33_EngageLimit', '1')
    BB.Write('34_EngageLimit', '1')
    BB.Write('64_EngageLimit', '1')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "Alt+": 0, "Speed+": 0, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"9M33M2": 144}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 1, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 0, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"EngageAll": 1}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M33M2": [24, 24]}}')
    
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
    SM.AddToUnitMagazine("SA-8B (1)", '9M33M2', 36)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    BB.Write('129_EngageLimit', '1')
    BB.Write('16_EngageLimit', '4')
    BB.Write('17_EngageLimit', '6')
    BB.Write('18_EngageLimit', '12')
    BB.Write('22_EngageLimit', '24')
    BB.Write('256_EngageLimit', '2')
    BB.Write('257_EngageLimit', '24')
    BB.Write('258_EngageLimit', '2')
    BB.Write('32_EngageLimit', '1')
    BB.Write('33_EngageLimit', '1')
    BB.Write('34_EngageLimit', '1')
    BB.Write('64_EngageLimit', '1')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "Alt+": 0, "Speed+": 0, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"9M33M2": 144}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 1, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 0, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"EngageAll": 1}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M33M2": [24, 24]}}')
    
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
    UI.AddTask('AvoidCav', 3.000000, 3)
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
    SM.SetUnitLauncherItem(unit.unitName, 7, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 8, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 9, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 10, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 11, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 12, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 13, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 14, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 15, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 16, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 17, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 18, '', 0)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Kiev", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Kiev", 'FAB-500', 100)
    SM.AddToUnitMagazine("Kiev", 'FAB-250', 500)
    SM.AddToUnitMagazine("Kiev", 'R-60M', 150)
    SM.AddToUnitMagazine("Kiev", 'AT-2M', 100)
    SM.AddToUnitMagazine("Kiev", 'APR-2E', 300)
    SM.AddToUnitMagazine("Kiev", 'DIFAR (75) Sonobuoy', 200)
    SM.AddToUnitMagazine("Kiev", 'LOFAR (75) Sonobuoy', 200)
    SM.AddToUnitMagazine("Kiev", 'DICASS (75) Sonobuoy', 100)
    SM.AddToUnitMagazine("Kiev", '23mm AM-23', 400)
    SM.AddToUnitMagazine("Kiev", 'Kh-23', 50)
    SM.AddToUnitMagazine("Kiev", 'R-60MK', 50)
    SM.AddToUnitMagazine("Kiev", 'VTT-1', 50)
    SM.AddToUnitMagazine("Kiev", 'S-8K 80mm', 50)
    SM.AddToUnitMagazine("Kiev", 'S-8B 80mm', 50)
    SM.AddToUnitMagazine("Kiev", 'S-5M Rocket', 50)
    SM.AddToUnitMagazine("Kiev", 'S-5K Rocket', 50)
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
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix1', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix2', 2)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix2', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix3', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix3', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix4', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix4', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix5', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix5', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix6', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix6', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix7', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix7', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix8', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix8', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix9', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix9', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix10', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix10', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix11', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix11', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix12', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix12', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix13', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix13', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix14', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix14', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix15', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix15', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix16', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix16', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix17', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix17', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix18', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix18', '5 DICASS (75) Sonobuoy;5 DICASS (75) Sonobuoy;14 DICASS (75) Sonobuoy;2 APR-2E;')
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
    UI.AddTask('AvoidCav', 3.000000, 3)
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
    UI.AddTask('AvoidCav', 3.000000, 3)
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
    unit.className = 'Airstrip (Russia)'
    unit.unitName = "Forward Airbase"
    unit.SetPosition(-7.176468, 62.274840, -0.0)
    unit.heading = 270.56
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Forward Airbase", 'Fuel', 1307704)
    SM.AddToUnitMagazine("Forward Airbase", '1150 Liter Tank', 26)
    SM.AddToUnitMagazine("Forward Airbase", '1520 Liter Tank', 1)
    SM.AddToUnitMagazine("Forward Airbase", '30mm NR-30 HEI', 259)
    SM.AddToUnitMagazine("Forward Airbase", 'Chaff-1', 2663)
    SM.AddToUnitMagazine("Forward Airbase", 'FAB-100', 56)
    SM.AddToUnitMagazine("Forward Airbase", 'FAB-250', 56)
    SM.AddToUnitMagazine("Forward Airbase", 'FAB-500', 313)
    SM.AddToUnitMagazine("Forward Airbase", 'Flare-1', 2463)
    SM.AddToUnitMagazine("Forward Airbase", 'KAB-500KRU', 6)
    SM.AddToUnitMagazine("Forward Airbase", 'KAB-500Kr', 9)
    SM.AddToUnitMagazine("Forward Airbase", 'Kh-22', 8)
    SM.AddToUnitMagazine("Forward Airbase", 'Kh-22M', 70)
    SM.AddToUnitMagazine("Forward Airbase", 'Kh-22MP', 62)
    SM.AddToUnitMagazine("Forward Airbase", 'Kh-22N', 2)
    SM.AddToUnitMagazine("Forward Airbase", 'R-27R', 43)
    SM.AddToUnitMagazine("Forward Airbase", 'R-27T', 19)
    SM.AddToUnitMagazine("Forward Airbase", 'R-60M', 67)
    SM.AddToUnitMagazine("Forward Airbase", 'R-60MK', 67)
    SM.AddToUnitMagazine("Forward Airbase", 'R-73', 45)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('129_EngageLimit', '1')
    BB.Write('16_EngageLimit', '4')
    BB.Write('17_EngageLimit', '6')
    BB.Write('18_EngageLimit', '12')
    BB.Write('22_EngageLimit', '24')
    BB.Write('256_EngageLimit', '2')
    BB.Write('257_EngageLimit', '24')
    BB.Write('258_EngageLimit', '2')
    BB.Write('32_EngageLimit', '1')
    BB.Write('33_EngageLimit', '1')
    BB.Write('34_EngageLimit', '1')
    BB.Write('64_EngageLimit', '1')
    BB.Write('InvMulti', '1')
    BB.Write('MagTonnage', '35')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "Alt+": 0, "Speed+": 0, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 0, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 0, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {}}')
    BB.Write('loadouts_dict', '{}')
    
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
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-1', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-2', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-2', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-3', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-3', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-4', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-4', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-5', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-5', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-6', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-6', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-7', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-7', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-8', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-8', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-9', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-9', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-10', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-10', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-11', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-11', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'Tu-22ME', 'Terminator-12', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Terminator-12', '1 Kh-22M;1 Kh-22M;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-1', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-1', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-2', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-2', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-3', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-3', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-4', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-4', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-5', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-5', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-6', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-6', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-7', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-7', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-8', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-8', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-9', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-9', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-10', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-10', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-11', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-11', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Forward Airbase', 'MiG-29SM', 'Shepherd-12', 1)
    SM.SetFlightDeckUnitLoadout('Forward Airbase', 'Shepherd-12', '1 1520 Liter Tank;2 R-27T;2 R-73;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
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
    FP.AddMissionWaypointAdvanced(mission_id, -0.1242530, 1.0879010, 6000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3243400, 1.0882310, 5000.0, 300.0)
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
    FP.AddMissionWaypointAdvanced(mission_id, -0.1242530, 1.0879010, 6000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3933900, 1.0760070, 5000.0, 300.0)
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
    FP.AddMissionWaypointAdvanced(mission_id, -0.1242530, 1.0879010, 12000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3494660, 1.0997220, 12000.0, 200.0)
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
    FP.AddMissionWaypointAdvanced(mission_id, -0.1242530, 1.0879010, 12000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.2823060, 1.0918390, 12000.0, 200.0)
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
    FP.AddMissionWaypointAdvanced(mission_id, -0.1242530, 1.0879010, 14000.0, 500.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3783540, 1.1106640, 14000.0, 250.0)
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
    UI.AddTask('AvoidCav', 3.000000, 3)
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
    lon_deg = 57.296*leader_track.Lon + -0.0064
    lat_deg = 57.296*leader_track.Lat + -0.0117
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
    UI.SetFormationMode(2)
    UI.SetFormationPosition(1.757, 0.500, -1.610, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "BDK-100"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0087
    lat_deg = 57.296*leader_track.Lat + 0.0212
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
    UI.SetFormationMode(2)
    UI.SetFormationPosition(1.936, 0.425, 1.203, 0.161)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "BDK-10"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0329
    lat_deg = 57.296*leader_track.Lat + 0.0027
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
    UI.SetFormationMode(2)
    UI.SetFormationPosition(1.715, 0.531, 3.028, 0.277)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135 Burevestnik'
    unit.unitName = "Zadornyy"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1604
    lat_deg = 57.296*leader_track.Lat + 0.0044
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
    lon_deg = 57.296*leader_track.Lon + 0.0833
    lat_deg = 57.296*leader_track.Lat + 0.0038
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
    lon_deg = 57.296*leader_track.Lon + -0.0707
    lat_deg = 57.296*leader_track.Lat + 0.0049
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
    UI.SetFormationMode(2)
    UI.SetFormationPosition(3.467, 0.500, -0.147, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Moskva', 'Ka-27A', 'Atlant Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Moskva', 'Atlant Ka-27 1', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 APR-2E;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135M Burevestnik-M'
    unit.unitName = "Gromkiy"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0348
    lat_deg = 57.296*leader_track.Lat + -0.0082
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
    lon_deg = 57.296*leader_track.Lon + -0.0420
    lat_deg = 57.296*leader_track.Lat + 0.0216
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
    goal_2_0 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_2_0)
    
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
