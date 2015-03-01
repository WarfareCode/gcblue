# Created on 11/07/14 03:28:30
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Interception\n\nA scenario for Global Conflicts 2.\n\nInterception is a typical Cold War scenario putting Norwegian subs\nagainst an approaching Soviet landing force.\n\nYou are to sink the hostile LSTs before they take your Naval Base.\n\n\n\n\n\n""")
    SM.SetScenarioName("""Interception""")
    SM.CreateAlliance(1, 'Norway')
    SM.SetAllianceDefaultCountry(1, 'Norway')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 0)
    SM.CreateAlliance(3, 'Sweden')
    SM.SetAllianceDefaultCountry(3, 'Sweden')
    SM.SetAlliancePlayable(3, 0)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(1)

    SM.SetDateTime(1988,8,4,12,0,0)
    SM.SetStartTheater(15.029165, 68.470833) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(2)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """TASKING ORDERS FOR CMDR NORWEGIAN OPERATIONS\n\nINTELLIGENCE\n\nThe Soviets try to capture our Naval Base at Harstad. A task force is \napproaching. You have only a few assets available to stop the hostile \nforces.\n\nMISSION\n\nSink the two LSTs.\n\nEXECUTION\n\nUse your air assets to gather information. Coordinate your subs. \n\nCOMMAND AND SIGNAL\n\nHNoMS Utsira\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """TASKING ORDERS:\n\n\nNO ADDITIONAL INTELLIGENCE AVAILABLE.\n""")

    ####################
    SM.SetSimpleBriefing(3, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Airfield Harstad"
    unit.SetPosition(16.060294, 68.454419, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Airfield Harstad", 'Fuel', 1000228)
    SM.AddToUnitMagazine("Airfield Harstad", 'Mk-46 Mod5', 46)
    SM.AddToUnitMagazine("Airfield Harstad", 'DICASS (85) Sonobuoy', 120)
    SM.AddToUnitMagazine("Airfield Harstad", 'LOFAR (85) Sonobuoy', 120)
    SM.AddToUnitMagazine("Airfield Harstad", 'DIFAR (85) Sonobuoy', 360)
    SM.AddToUnitMagazine("Airfield Harstad", 'AGM-65D', 16)
    SM.AddToUnitMagazine("Airfield Harstad", 'Flare-1', 100)
    SM.AddToUnitMagazine("Airfield Harstad", 'Chaff-1', 100)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Airfield Harstad', 'P-3C II Orion', 'ASW Harstad-1', 2)
    SM.SetFlightDeckUnitLoadout('Airfield Harstad', 'ASW Harstad-1', '17 DICASS (85) Sonobuoy;17 LOFAR (85) Sonobuoy;50 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 AGM-65D;2 AGM-65D;2 Mk-46 Mod5;2 Mk-46 Mod5;8 Mk-46 Mod5;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Airfield Harstad', 'P-3C II Orion', 'ASW Harstad-2', 2)
    SM.SetFlightDeckUnitLoadout('Airfield Harstad', 'ASW Harstad-2', '17 DICASS (85) Sonobuoy;17 LOFAR (85) Sonobuoy;50 DIFAR (85) Sonobuoy;2 Mk-46 Mod5;2 AGM-65D;2 AGM-65D;2 Mk-46 Mod5;2 Mk-46 Mod5;8 Mk-46 Mod5;30 Chaff-1;30 Flare-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Communications Station'
    unit.unitName = "Harstad Naval Base"
    unit.SetPosition(16.060752, 68.441299, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Kobben'
    unit.unitName = "HNoMS Skolpen"
    unit.SetPosition(14.961361, 68.200082, -100.0)
    unit.heading = 213.69
    unit.speed = 3.9
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
    SM.AddToUnitMagazine("HNoMS Skolpen", 'Type-612 Torpedo', 6)
    SM.AddToUnitMagazine("HNoMS Skolpen", 'NT37C', 6)
    UI.SetSensorState(3, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Kobben'
    unit.unitName = "HNoMS Utsira"
    unit.SetPosition(15.284451, 68.167768, -100.0)
    unit.heading = 250.62
    unit.speed = 4.0
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
    SM.AddToUnitMagazine("HNoMS Utsira", 'Type-612 Torpedo', 6)
    SM.AddToUnitMagazine("HNoMS Utsira", 'NT37C', 6)
    UI.SetSensorState(3, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641B Som'
    unit.unitName = "B-437 Magnitogorsk"
    unit.SetPosition(14.829352, 68.030604, -200.0)
    unit.heading = 28.76
    unit.speed = 3.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-437 Magnitogorsk", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-437 Magnitogorsk", '53-65M', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.262058, 1.190724, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.265758, 1.189080, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"12": "0"}')
    BB.Write('MissionTarget', '["Target", 12]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 7, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 8, "30mm OF-84 HE-FRAG AK-630M": 12272, "TEST-68": 0, "TEST-71ME": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "130mm F-44 HE": 500, "SET-65M": 144, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "9M32 Strela 2": 48, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "Shkval": 0, "53-65M": 196}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 4, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 4, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 2, "Nav": 3, "EngageAll": 5}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"9M330 Kinzhal": [64, 64], "9M32M Strela 3": [1, 1], "5V55RM": [64, 64], "3M45 Granit": [16, 16], "9M32 Strela 2": [24, 24], "SET-65M": [8, 8], "130mm F-44 HE": [100, 100], "30mm OF-84 HE-FRAG AK-630M": [590, 590], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [80, 80], "100mm OF-58 FRAG": [92, 92], "53-65M": [26, 26], "RPK-3 Metel": [12, 12]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877M Paltus'
    unit.unitName = "B-439"
    unit.SetPosition(14.446730, 68.047276, -150.0)
    unit.heading = 74.08
    unit.speed = 5.9
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
    SM.AddToUnitMagazine("B-439", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-439", '53-65M', 6)
    SM.AddToUnitMagazine("B-439", '9M32M Strela 3', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.257382, 1.188411, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.265398, 1.190210, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.271771, 1.191623, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.278605, 1.193216, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"12": "0"}')
    BB.Write('MissionTarget', '["Target", 12]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 7, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 8, "30mm OF-84 HE-FRAG AK-630M": 12272, "TEST-68": 0, "TEST-71ME": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "130mm F-44 HE": 500, "SET-65M": 144, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "9M32 Strela 2": 48, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "Shkval": 0, "53-65M": 196}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 4, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 4, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 2, "Nav": 3, "EngageAll": 5}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"9M330 Kinzhal": [64, 64], "9M32M Strela 3": [1, 1], "5V55RM": [64, 64], "3M45 Granit": [16, 16], "9M32 Strela 2": [24, 24], "SET-65M": [8, 8], "130mm F-44 HE": [100, 100], "30mm OF-84 HE-FRAG AK-630M": [590, 590], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [80, 80], "100mm OF-58 FRAG": [92, 92], "53-65M": [26, 26], "RPK-3 Metel": [12, 12]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135 Burevestnik'
    unit.unitName = "Letuchiy"
    unit.SetPosition(14.233189, 67.882095, 0.0)
    unit.heading = 46.18
    unit.speed = 10.0
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
    SM.AddToUnitMagazine("Letuchiy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.254028, 1.187456, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.262348, 1.189906, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.270299, 1.191123, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.274493, 1.191760, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.279261, 1.193445, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"12": "0"}')
    BB.Write('MissionTarget', '["Target", 12]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 4, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"30mm OF-84 HE-FRAG AK-630M": 8496, "TEST-68": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "130mm F-44 HE": 500, "SET-65M": 0, "3M45 Granit": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "130mm ZS-44P AA": 0, "76.2mm ZS-63 AA": 0, "9M32 Strela 2": 48, "USET-80": 0, "Shkval": 0, "53-65M": 76}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 3, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 2, "Nav": 1, "EngageAll": 2}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 0, "FormModePace": 3, "WeaponList": {"130mm F-44 HE": [100, 100], "5V55RM": [64, 64], "3M45 Granit": [16, 16], "9M32 Strela 2": [24, 24], "30mm OF-84 HE-FRAG AK-630M": [354, 354], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [80, 80], "53-65M": [14, 14], "RPK-3 Metel": [4, 4]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "Nikolay Vilkov"
    UI = SM.GetUnitInterface('Letuchiy')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0607
    lat_deg = 57.296*leader_track.Lat + -0.0012
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 45.72
    unit.speed = 10.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Nikolay Vilkov", '9M32 Strela 2', 24)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"12": "0"}')
    BB.Write('MissionTarget', '["Target", 12]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 4, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"30mm OF-84 HE-FRAG AK-630M": 8496, "TEST-68": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "130mm F-44 HE": 500, "SET-65M": 0, "3M45 Granit": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "130mm ZS-44P AA": 0, "76.2mm ZS-63 AA": 0, "9M32 Strela 2": 48, "USET-80": 0, "Shkval": 0, "53-65M": 76}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 3, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 2, "Nav": 1, "EngageAll": 2}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 0, "FormModePace": 3, "WeaponList": {"130mm F-44 HE": [100, 100], "5V55RM": [64, 64], "3M45 Granit": [16, 16], "9M32 Strela 2": [24, 24], "30mm OF-84 HE-FRAG AK-630M": [354, 354], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [80, 80], "53-65M": [14, 14], "RPK-3 Metel": [4, 4]}}')
    leader_id = UI.LookupFriendlyId('Letuchiy')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(2.551, 0.358, -2.459, 0.339)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "BDK-13"
    UI = SM.GetUnitInterface('Letuchiy')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0213
    lat_deg = 57.296*leader_track.Lat + -0.0268
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 45.66
    unit.speed = 10.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("BDK-13", '9M32 Strela 2', 24)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"12": "0"}')
    BB.Write('MissionTarget', '["Target", 12]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 4, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"30mm OF-84 HE-FRAG AK-630M": 8496, "TEST-68": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "130mm F-44 HE": 500, "SET-65M": 0, "3M45 Granit": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "130mm ZS-44P AA": 0, "76.2mm ZS-63 AA": 0, "9M32 Strela 2": 48, "USET-80": 0, "Shkval": 0, "53-65M": 76}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 3, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 2, "Nav": 1, "EngageAll": 2}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 0, "FormModePace": 3, "WeaponList": {"130mm F-44 HE": [100, 100], "5V55RM": [64, 64], "3M45 Granit": [16, 16], "9M32 Strela 2": [24, 24], "30mm OF-84 HE-FRAG AK-630M": [354, 354], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [80, 80], "53-65M": [14, 14], "RPK-3 Metel": [4, 4]}}')
    leader_id = UI.LookupFriendlyId('Letuchiy')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(3.175, 0.500, 2.624, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1155 Fregat'
    unit.unitName = "Udaloy"
    UI = SM.GetUnitInterface('Letuchiy')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0780
    lat_deg = 57.296*leader_track.Lat + -0.0315
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 46.24
    unit.speed = 10.0
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
    SM.AddToUnitMagazine("Udaloy", 'Fuel', 45900)
    SM.AddToUnitMagazine("Udaloy", 'AT-1', 22)
    SM.AddToUnitMagazine("Udaloy", 'DICASS (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("Udaloy", 'LOFAR (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("Udaloy", 'DIFAR (80) Sonobuoy', 378)
    SM.AddToUnitMagazine("Udaloy", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Udaloy", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Udaloy", '53-65M', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"12": "0"}')
    BB.Write('MissionTarget', '["Target", 12]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 7, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 8, "30mm OF-84 HE-FRAG AK-630M": 12272, "TEST-68": 0, "TEST-71ME": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "130mm F-44 HE": 500, "SET-65M": 144, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "9M32 Strela 2": 48, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "Shkval": 0, "53-65M": 196}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 4, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 4, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 2, "Nav": 3, "EngageAll": 5}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"9M330 Kinzhal": [64, 64], "9M32M Strela 3": [1, 1], "5V55RM": [64, 64], "3M45 Granit": [16, 16], "9M32 Strela 2": [24, 24], "SET-65M": [8, 8], "130mm F-44 HE": [100, 100], "30mm OF-84 HE-FRAG AK-630M": [590, 590], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [80, 80], "100mm OF-58 FRAG": [92, 92], "53-65M": [26, 26], "RPK-3 Metel": [12, 12]}}')
    leader_id = UI.LookupFriendlyId('Letuchiy')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(4.837, 0.500, 3.079, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Udaloy', 'Ka-27A', 'Fregat Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Udaloy', 'Fregat Ka-27 1', '5 DICASS (80) Sonobuoy;5 LOFAR (80) Sonobuoy;14 DIFAR (80) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Udaloy', 'Ka-27A', 'Udaloy ASW-1', 2)
    SM.SetFlightDeckUnitLoadout('Udaloy', 'Udaloy ASW-1', '5 DICASS (80) Sonobuoy;5 LOFAR (80) Sonobuoy;14 DIFAR (80) Sonobuoy;2 AT-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Udaloy ASW-1')
    FP.AddAircraftToMission(mission_id, 'Fregat Ka-27 1')
    FP.SetMissionLaunchTime(mission_id, '13:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0029559,0.0023593,-0.0016718,0.0023831,-0.0014776,0.0011437,-0.0026294,0.0012958,')
    FP.SetMissionPatrolAnchor(mission_id, 'Udaloy', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.2480410, 1.1851740, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2497580, 1.1855460, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1164 Atlant'
    unit.unitName = "Moskva"
    UI = SM.GetUnitInterface('Letuchiy')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0369
    lat_deg = 57.296*leader_track.Lat + -0.0145
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 46.12
    unit.speed = 10.0
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
    SM.AddToUnitMagazine("Moskva", 'AT-1', 26)
    SM.AddToUnitMagazine("Moskva", 'DICASS (80) Sonobuoy', 175)
    SM.AddToUnitMagazine("Moskva", 'LOFAR (80) Sonobuoy', 175)
    SM.AddToUnitMagazine("Moskva", 'DIFAR (80) Sonobuoy', 490)
    SM.AddToUnitMagazine("Moskva", '30mm OF-84 HE-FRAG AK-630M', 1416)
    SM.AddToUnitMagazine("Moskva", '130mm F-44 HE', 500)
    SM.AddToUnitMagazine("Moskva", '53-65M', 30)
    UI.SetSensorState(6, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"12": "0"}')
    BB.Write('InvMulti', '1')
    BB.Write('MissionTarget', '["Target", 12]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 4, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"30mm OF-84 HE-FRAG AK-630M": 8496, "TEST-68": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "130mm F-44 HE": 500, "SET-65M": 0, "3M45 Granit": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "130mm ZS-44P AA": 0, "76.2mm ZS-63 AA": 0, "9M32 Strela 2": 48, "USET-80": 0, "Shkval": 0, "53-65M": 76}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 3, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 2, "Nav": 1, "EngageAll": 2}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 0, "FormModePace": 3, "WeaponList": {"130mm F-44 HE": [100, 100], "5V55RM": [64, 64], "3M45 Granit": [16, 16], "9M32 Strela 2": [24, 24], "30mm OF-84 HE-FRAG AK-630M": [354, 354], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [80, 80], "53-65M": [14, 14], "RPK-3 Metel": [4, 4]}}')
    BB.Write('loadouts_dict', '{"Torpedoes": {"Ka-27A": {"T 1997": {"DICASS (90) Sonobuoy": 5, "AT-1": 2, "LOFAR (90) Sonobuoy": 5, "DIFAR (90) Sonobuoy": 14}, "T CHN 1982": {"DIFAR (75) Sonobuoy": 14, "DICASS (75) Sonobuoy": 5, "Yu-7": 2, "LOFAR (75) Sonobuoy": 5}, "T CHN 1987": {"DICASS (80) Sonobuoy": 5, "LOFAR (80) Sonobuoy": 5, "DIFAR (80) Sonobuoy": 14, "Yu-7": 2}, "T 1992": {"DICASS (85) Sonobuoy": 5, "LOFAR (85) Sonobuoy": 5, "DIFAR (85) Sonobuoy": 14, "AT-1": 2}, "T CHN 1977": {"DIFAR (70) Sonobuoy": 14, "DICASS (70) Sonobuoy": 5, "Yu-7": 2, "LOFAR (70) Sonobuoy": 5}, "T CHN 1997": {"DICASS (90) Sonobuoy": 5, "LOFAR (90) Sonobuoy": 5, "Yu-7": 2, "DIFAR (90) Sonobuoy": 14}, "T CHN 1972": {"DIFAR (65) Sonobuoy": 14, "DICASS (65) Sonobuoy": 5, "LOFAR (65) Sonobuoy": 5, "Yu-7": 2}, "T CHN 1992": {"DICASS (85) Sonobuoy": 5, "LOFAR (85) Sonobuoy": 5, "DIFAR (85) Sonobuoy": 14, "Yu-7": 2}, "T 2002": {"DICASS (95) Sonobuoy": 5, "LOFAR (95) Sonobuoy": 5, "AT-1": 2, "DIFAR (95) Sonobuoy": 14}, "T 2012": {"DICASS (105) Sonobuoy": 5, "AT-1": 2, "LOFAR (105) Sonobuoy": 5, "DIFAR (105) Sonobuoy": 14}, "T 2007": {"DICASS (100) Sonobuoy": 5, "LOFAR (100) Sonobuoy": 5, "AT-1": 2, "DIFAR (100) Sonobuoy": 14}, "T CHN 2007": {"DICASS (100) Sonobuoy": 5, "LOFAR (100) Sonobuoy": 5, "Yu-7": 2, "DIFAR (100) Sonobuoy": 14}, "T CHN 2012": {"DICASS (105) Sonobuoy": 5, "AT-1": 2, "LOFAR (105) Sonobuoy": 5, "DIFAR (105) Sonobuoy": 14}, "T CHN 2002": {"DICASS (95) Sonobuoy": 5, "LOFAR (95) Sonobuoy": 5, "Yu-7": 2, "DIFAR (95) Sonobuoy": 14}, "T 1982": {"DIFAR (75) Sonobuoy": 14, "DICASS (75) Sonobuoy": 5, "AT-1": 2, "LOFAR (75) Sonobuoy": 5}, "T 1987": {"DICASS (80) Sonobuoy": 5, "LOFAR (80) Sonobuoy": 5, "DIFAR (80) Sonobuoy": 14, "AT-1": 2}}}}')
    leader_id = UI.LookupFriendlyId('Letuchiy')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(2.286, 0.632, 3.082, 0.278)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Moskva', 'Ka-27A', 'Atlant Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Moskva', 'Atlant Ka-27 1', '5 DICASS (80) Sonobuoy;5 LOFAR (80) Sonobuoy;14 DIFAR (80) Sonobuoy;2 AT-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Patrol Boat'
    unit.unitName = "Swedish Patrol Boat"
    unit.SetPosition(15.090047, 68.170519, 0.0)
    unit.heading = -116.25
    unit.speed = 20.4
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SAM-I', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.259547, 1.188854, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.252271, 1.188998, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.254573, 1.185606, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.264604, 1.188751, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.264645, 1.191259, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.250380, 1.188114, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Nikolay Vilkov')
    goal_temp.AddTarget('BDK-13')
    goal_temp.SetQuantity(2)
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.AreaGoal()
    goal_temp.SetTargetList('Nikolay Vilkov, BDK-13')
    goal_temp.SetTimeObjective(0.000000)
    goal_temp.SetLogicAny(1)
    goal_temp.SetQuantity(1)
    goal_temp.AddPointDeg(16.09006, 68.40239)
    goal_temp.AddPointDeg(16.00545, 68.33701)
    goal_temp.AddPointDeg(15.89431, 68.35856)
    goal_temp.AddPointDeg(16.02083, 68.42163)
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Alliance 3 goals
    ##############################

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(36000.0)
    goal_temp.SetFailTimeout(59940.0)
    SM.SetAllianceGoal(3, goal_temp)

    SM.SetAllianceROEByType(3, 0, 0, 0, 0)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
    SM.SetIncludeProbability('Gotland SSK (Prototype)', 0.500000)
    SM.AddRandomBox('Gotland SSK (Prototype)', 14.6166, 14.9699, 68.0056, 68.1246)
