# Created on 12/08/14 05:47:33
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""New Russia Part 1: The Lone Wolf\n\nEight weeks ago, the Russian - Ukrainian conflict escalated. Russian \ntroops invaded the Ukraine and overtook all critical facilities in two \nweeks. \n\nFour weeks ago, Russia started massing troops along their border with \nPoland.\n\nThe Crimea is under Russian control for months now and the Russians \nmoved several of their capital ships towards Sevastopol Harbor.\n\nNow it is time for a Silent Hunter to deliver a counter blow, and thus to \nregain the initiative. \n\nIt is time for the fabulous Seawolf SSN. \n\n\n\n\n\n""")
    SM.SetScenarioName("""New Russia 1 SSN Seawolf""")
    SM.CreateAlliance(1, 'Russia')
    SM.SetAllianceDefaultCountry(1, 'Russia')
    SM.SetAlliancePlayable(1, 0)
    SM.CreateAlliance(2, 'USA')
    SM.SetAllianceDefaultCountry(2, 'USA')
    SM.SetAlliancePlayable(2, 1)
    SM.CreateAlliance(3, 'Neutral Shipping')
    SM.SetAllianceDefaultCountry(3, 'Neutral Shipping')
    SM.SetAlliancePlayable(3, 0)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(2)

    SM.SetDateTime(2014,10,17,0,0,0)
    SM.SetStartTheater(32.116665, 41.883335) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """No briefing found""")

    ####################
    SM.SetSimpleBriefing(2, """TASKING ORDERS FOR CMDR US OPERATIONS\n\nINTELLIGENCE\n\nThe Ukraine has fallen. Russian troops have massed along their border \nwith Poland and are about to attack.  \n\nThe Russians must be convinced that attacking Poland would be a bad \nidea  and Nato can regain the initiative at will.  \n\nThus maybe an all out war can be prevented. \n\nMISSION\n\nYou are to send a strong, but silent message to the Russians.\n\nStrike them in their backyard with our most advanced sub. \n\nAttack their Black Sea Fleet in the Lion's dent close to Sevastopol Harbor. \n\n\nEXECUTION\n\nLocate the Russian SAG, centered around the Slava Class Cruiser \nMoskva. \n\nSink at least two ships, one of them must be the Moskva.\n\nProceed with care, expect heavy resistance. \n\nUse your land based air assets to locate the Russian warships and to \nsupport the Seawolf.\n\n\nCOMMAND AND SIGNAL\n\nSSN 21 Seawolf\n\nEMCON passive.\n\n\n""")

    ####################
    SM.SetSimpleBriefing(3, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1164 Atlant'
    unit.unitName = "Moskva"
    unit.SetPosition(33.266502, 44.449666, 0.0)
    unit.heading = -137.49
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
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
    SM.SetUnitLauncherItem(unit.unitName, 10, '53-56', 5)
    SM.SetUnitLauncherItem(unit.unitName, 11, '53-56', 5)
    SM.SetUnitLauncherItem(unit.unitName, 12, '3M45 Granit', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Moskva", 'AT-1', 28)
    SM.AddToUnitMagazine("Moskva", 'DICASS (105) Sonobuoy', 201)
    SM.AddToUnitMagazine("Moskva", 'DIFAR (105) Sonobuoy', 490)
    SM.AddToUnitMagazine("Moskva", 'Fuel', 68850)
    SM.AddToUnitMagazine("Moskva", 'LOFAR (105) Sonobuoy', 175)
    SM.AddToUnitMagazine("Moskva", '30mm OF-84 HE-FRAG AK-630M', 1416)
    SM.AddToUnitMagazine("Moskva", '130mm F-44 HE', 500)
    SM.AddToUnitMagazine("Moskva", '53-65M', 30)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.576273, 0.775771, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.583167, 0.772199, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "12.0": 0.0, "14.0": 0.0, "13.0": 0.0, "16.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 14]')
    BB.Write('Selected', '{"RotaryWing": 2, "Speed-": 100, "Alt+": 4000.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 9, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 6, "AT-2M": 0, "TEST-68": 0, "TEST-71ME": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "9M311 Kashtan": 96, "130mm F-44 HE": 1000, "*DICASS*": 0, "SET-65M": 120, "*buoy": 0, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "3M80 Moskit": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "V-611": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "APR-2E": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "*LOFAR*": 0, "*DIFAR*": 0, "30mm OF-84 HE-FRAG AK-630M": 13216, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 224}, "Air": 2, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 2, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 2, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAll": 8}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"APR-2E": [4, 4], "9M330 Kinzhal": [64, 64], "DICASS (105) Sonobuoy": [10, 10], "9M32M Strela 3": [1, 1], "3M80 Moskit": [8, 8], "5V55RM": [64, 64], "9M311 Kashtan": [16, 16], "3M45 Granit": [16, 16], "3M10 Granat": [1, 1], "DIFAR (105) Sonobuoy": [15, 15], "SET-65M": [7, 7], "130mm F-44 HE": [200, 200], "V-611": [72, 72], "LOFAR (105) Sonobuoy": [5, 5], "30mm OF-84 HE-FRAG AK-630M": [708, 708], "76.2mm OS-62 FRAG": [500, 500], "9M33M": [120, 120], "53-56": [20, 20], "100mm OF-58 FRAG": [92, 92], "53-65M": [16, 16], "RPK-3 Metel": [12, 12]}}')
    
    SM.AddUnitToFlightDeck('Moskva', 'Ka-27A', 'Atlant Ka-27 101', 1)
    SM.SetFlightDeckUnitLoadout('Moskva', 'Atlant Ka-27 101', '5 DIFAR (100) Sonobuoy;5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;2 APR-2E;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Atlant Ka-27 101')
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, 'ASW-Helo')
    FP.SetMissionPatrolArea(mission_id, '-0.0015771,0.0020704,-0.0033946,0.0029715,0.0028799,0.0031142,0.0014214,0.0021586,')
    FP.SetMissionPatrolAnchor(mission_id, 'Moskva', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.5816100, 0.7767930, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.5802787, 0.7732011, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641B Som'
    unit.unitName = "B-380 Gorkovsky Komsomolets"
    boxes = [[32.2834, 33.0489, 43.6710, 43.9938]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -100.0)
    unit.heading = 222.27
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-380 Gorkovsky Komsomolets", '53-65M', 6)
    SM.AddToUnitMagazine("B-380 Gorkovsky Komsomolets", 'SET-65M', 12)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.562933, 0.768069, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.575766, 0.762650, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "12.0": 0.0, "14.0": 0.0, "13.0": 0.0, "16.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 14]')
    BB.Write('Selected', '{"RotaryWing": 2, "Speed-": 100, "Alt+": 4000.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 9, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 6, "AT-2M": 0, "TEST-68": 0, "TEST-71ME": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "9M311 Kashtan": 96, "130mm F-44 HE": 1000, "*DICASS*": 0, "SET-65M": 120, "*buoy": 0, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "3M80 Moskit": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "V-611": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "APR-2E": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "*LOFAR*": 0, "*DIFAR*": 0, "30mm OF-84 HE-FRAG AK-630M": 13216, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 224}, "Air": 2, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 2, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 2, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAll": 8}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"APR-2E": [4, 4], "9M330 Kinzhal": [64, 64], "DICASS (105) Sonobuoy": [10, 10], "9M32M Strela 3": [1, 1], "3M80 Moskit": [8, 8], "5V55RM": [64, 64], "9M311 Kashtan": [16, 16], "3M45 Granit": [16, 16], "3M10 Granat": [1, 1], "DIFAR (105) Sonobuoy": [15, 15], "SET-65M": [7, 7], "130mm F-44 HE": [200, 200], "V-611": [72, 72], "LOFAR (105) Sonobuoy": [5, 5], "30mm OF-84 HE-FRAG AK-630M": [708, 708], "76.2mm OS-62 FRAG": [500, 500], "9M33M": [120, 120], "53-56": [20, 20], "100mm OF-58 FRAG": [92, 92], "53-65M": [16, 16], "RPK-3 Metel": [12, 12]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877V Alrossa'
    unit.unitName = "B-871 Alrossa"
    boxes = [[31.9861, 32.3177, 43.1599, 43.3017]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -150.0)
    unit.heading = 213.69
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M32M Strela 3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '3M10 Granat', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-871 Alrossa", '53-65M', 4)
    SM.AddToUnitMagazine("B-871 Alrossa", 'SET-65M', 8)
    SM.AddToUnitMagazine("B-871 Alrossa", '9M32M Strela 3', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.554453, 0.760482, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.569349, 0.754730, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.563506, 0.765401, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.579662, 0.763483, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.573818, 0.771487, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.581151, 0.770903, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "12.0": 0.0, "14.0": 0.0, "13.0": 0.0, "16.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 14]')
    BB.Write('Selected', '{"RotaryWing": 2, "Speed-": 100, "Alt+": 4000.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 9, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 6, "AT-2M": 0, "TEST-68": 0, "TEST-71ME": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "9M311 Kashtan": 96, "130mm F-44 HE": 1000, "*DICASS*": 0, "SET-65M": 120, "*buoy": 0, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "3M80 Moskit": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "V-611": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "APR-2E": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "*LOFAR*": 0, "*DIFAR*": 0, "30mm OF-84 HE-FRAG AK-630M": 13216, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 224}, "Air": 2, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 2, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 2, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAll": 8}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"APR-2E": [4, 4], "9M330 Kinzhal": [64, 64], "DICASS (105) Sonobuoy": [10, 10], "9M32M Strela 3": [1, 1], "3M80 Moskit": [8, 8], "5V55RM": [64, 64], "9M311 Kashtan": [16, 16], "3M45 Granit": [16, 16], "3M10 Granat": [1, 1], "DIFAR (105) Sonobuoy": [15, 15], "SET-65M": [7, 7], "130mm F-44 HE": [200, 200], "V-611": [72, 72], "LOFAR (105) Sonobuoy": [5, 5], "30mm OF-84 HE-FRAG AK-630M": [708, 708], "76.2mm OS-62 FRAG": [500, 500], "9M33M": [120, 120], "53-56": [20, 20], "100mm OF-58 FRAG": [92, 92], "53-65M": [16, 16], "RPK-3 Metel": [12, 12]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 11551 Fregat-M'
    unit.unitName = "Admiral Chabanenko"
    boxes = [[31.4026, 31.7581, 43.3295, 43.3669]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -135.00
    unit.speed = 15.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-65M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 6, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 7, '9M330 Kinzhal', 64)
    SM.SetUnitLauncherItem(unit.unitName, 8, '3M80 Moskit', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Admiral Chabanenko", 'Fuel', 45900)
    SM.AddToUnitMagazine("Admiral Chabanenko", 'LOFAR (100) Sonobuoy', 5)
    SM.AddToUnitMagazine("Admiral Chabanenko", 'DICASS (105) Sonobuoy', 10)
    SM.AddToUnitMagazine("Admiral Chabanenko", 'DIFAR (110) Sonobuoy', 6)
    SM.AddToUnitMagazine("Admiral Chabanenko", 'DICASS (110) Sonobuoy', 20)
    SM.AddToUnitMagazine("Admiral Chabanenko", 'LOFAR (110) Sonobuoy', 20)
    SM.AddToUnitMagazine("Admiral Chabanenko", 'AT-1', 16)
    SM.AddToUnitMagazine("Admiral Chabanenko", '30mm OF-84 HE-FRAG AK-630M', 472)
    SM.AddToUnitMagazine("Admiral Chabanenko", '9M311 Kashtan', 48)
    SM.AddToUnitMagazine("Admiral Chabanenko", '130mm F-44 HE', 500)
    SM.AddToUnitMagazine("Admiral Chabanenko", '53-65M', 24)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "12.0": 0.0, "14.0": 0.0, "13.0": 0.0, "16.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 14]')
    BB.Write('Selected', '{"RotaryWing": 2, "Speed-": 100, "Alt+": 4000.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 9, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 6, "AT-2M": 0, "TEST-68": 0, "TEST-71ME": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "9M311 Kashtan": 96, "130mm F-44 HE": 1000, "*DICASS*": 0, "SET-65M": 120, "*buoy": 0, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "3M80 Moskit": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "V-611": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "APR-2E": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "*LOFAR*": 0, "*DIFAR*": 0, "30mm OF-84 HE-FRAG AK-630M": 13216, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 224}, "Air": 2, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 2, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 2, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAll": 8}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"APR-2E": [4, 4], "9M330 Kinzhal": [64, 64], "DICASS (105) Sonobuoy": [10, 10], "9M32M Strela 3": [1, 1], "3M80 Moskit": [8, 8], "5V55RM": [64, 64], "9M311 Kashtan": [16, 16], "3M45 Granit": [16, 16], "3M10 Granat": [1, 1], "DIFAR (105) Sonobuoy": [15, 15], "SET-65M": [7, 7], "130mm F-44 HE": [200, 200], "V-611": [72, 72], "LOFAR (105) Sonobuoy": [5, 5], "30mm OF-84 HE-FRAG AK-630M": [708, 708], "76.2mm OS-62 FRAG": [500, 500], "9M33M": [120, 120], "53-56": [20, 20], "100mm OF-58 FRAG": [92, 92], "53-65M": [16, 16], "RPK-3 Metel": [12, 12]}}')
    
    SM.AddUnitToFlightDeck('Admiral Chabanenko', 'Ka-27A', 'Fregat-M Ka-27 2', 1)
    SM.SetFlightDeckUnitLoadout('Admiral Chabanenko', 'Fregat-M Ka-27 2', '5 DIFAR (110) Sonobuoy;5 LOFAR (100) Sonobuoy;5 DICASS (100) Sonobuoy;2 APR-2E;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Sevastopol AB"
    unit.SetPosition(33.572501, 44.688333, -0.0)
    unit.heading = 270.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Sevastopol AB", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Sevastopol AB", 'AT-2M', 50)
    SM.AddToUnitMagazine("Sevastopol AB", 'DIFAR (105) Sonobuoy', 200)
    SM.AddToUnitMagazine("Sevastopol AB", 'LOFAR (105) Sonobuoy', 400)
    SM.AddToUnitMagazine("Sevastopol AB", 'DICASS (105) Sonobuoy', 166)
    SM.AddToUnitMagazine("Sevastopol AB", '1150 Liter Tank', 62)
    SM.AddToUnitMagazine("Sevastopol AB", '1520 Liter Tank', 44)
    SM.AddToUnitMagazine("Sevastopol AB", 'R-27R', 124)
    SM.AddToUnitMagazine("Sevastopol AB", 'R-73M', 50)
    SM.AddToUnitMagazine("Sevastopol AB", '30mm NR-30 HEI', 80)
    SM.AddToUnitMagazine("Sevastopol AB", 'Chaff-1', 120)
    SM.AddToUnitMagazine("Sevastopol AB", 'Flare-1', 20)
    SM.AddToUnitMagazine("Sevastopol AB", 'R-73M2', 138)
    SM.AddToUnitMagazine("Sevastopol AB", 'R-77', 202)
    SM.AddToUnitMagazine("Sevastopol AB", 'R-27RE', 38)
    SM.AddToUnitMagazine("Sevastopol AB", 'R-27T', 50)
    SM.AddToUnitMagazine("Sevastopol AB", 'R-27TE', 38)
    SM.AddToUnitMagazine("Sevastopol AB", 'FAB-100', 36)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "12.0": 0.0, "14.0": 0.0, "13.0": 0.0, "16.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 14]')
    BB.Write('Selected', '{"RotaryWing": 2, "Speed-": 100, "Alt+": 4000.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 9, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 6, "AT-2M": 0, "TEST-68": 0, "TEST-71ME": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "9M311 Kashtan": 96, "130mm F-44 HE": 1000, "*DICASS*": 0, "SET-65M": 120, "*buoy": 0, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "3M80 Moskit": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "V-611": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "APR-2E": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "*LOFAR*": 0, "*DIFAR*": 0, "30mm OF-84 HE-FRAG AK-630M": 13216, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 224}, "Air": 2, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 2, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 2, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAll": 8}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"APR-2E": [4, 4], "9M330 Kinzhal": [64, 64], "DICASS (105) Sonobuoy": [10, 10], "9M32M Strela 3": [1, 1], "3M80 Moskit": [8, 8], "5V55RM": [64, 64], "9M311 Kashtan": [16, 16], "3M45 Granit": [16, 16], "3M10 Granat": [1, 1], "DIFAR (105) Sonobuoy": [15, 15], "SET-65M": [7, 7], "130mm F-44 HE": [200, 200], "V-611": [72, 72], "LOFAR (105) Sonobuoy": [5, 5], "30mm OF-84 HE-FRAG AK-630M": [708, 708], "76.2mm OS-62 FRAG": [500, 500], "9M33M": [120, 120], "53-56": [20, 20], "100mm OF-58 FRAG": [92, 92], "53-65M": [16, 16], "RPK-3 Metel": [12, 12]}}')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'Il-38', 'Hammer-1', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Hammer-1', '17 DICASS (105) Sonobuoy;17 LOFAR (105) Sonobuoy;41 DIFAR (105) Sonobuoy;4 AT-2M;')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'Il-38', 'Hammer-2', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Hammer-2', '17 DICASS (105) Sonobuoy;17 LOFAR (105) Sonobuoy;41 DIFAR (105) Sonobuoy;4 AT-2M;')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'Il-38', 'Hammer-3', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Hammer-3', '17 DICASS (105) Sonobuoy;17 LOFAR (105) Sonobuoy;41 DIFAR (105) Sonobuoy;4 AT-2M;')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'Il-38', 'Hammer-4', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Hammer-4', '17 DICASS (105) Sonobuoy;17 LOFAR (105) Sonobuoy;41 DIFAR (105) Sonobuoy;4 AT-2M;')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'MiG-29M', 'Arrow-1', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Arrow-1', '1 1520 Liter Tank;2 R-27RE;2 R-27TE;2 R-77;2 R-73M2;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'MiG-29M', 'Arrow-2', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Arrow-2', '1 1520 Liter Tank;2 R-27RE;2 R-27TE;2 R-77;2 R-73M2;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'MiG-29M', 'Arrow-3', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Arrow-3', '1 1520 Liter Tank;2 R-27RE;2 R-27TE;2 R-77;2 R-73M2;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'MiG-29M', 'Arrow-4', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Arrow-4', '1 1520 Liter Tank;2 R-27RE;2 R-27TE;2 R-77;2 R-73M2;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'MiG-29M', 'Arrow-5', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Arrow-5', '1 1520 Liter Tank;2 R-27RE;2 R-27TE;2 R-77;2 R-73M2;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'MiG-29M', 'Arrow-6', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Arrow-6', '1 1520 Liter Tank;2 R-27RE;2 R-27TE;2 R-77;2 R-73M2;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'A-50', 'Sky-1', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Sky-1', '')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'A-50', 'Sky-2', 2)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Sky-2', '')
    
    SM.AddUnitToFlightDeck('Sevastopol AB', 'A-50', 'Sky-3', 1)
    SM.SetFlightDeckUnitLoadout('Sevastopol AB', 'Sky-3', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Hammer-1')
    FP.AddAircraftToMission(mission_id, 'Hammer-2')
    FP.AddAircraftToMission(mission_id, 'Hammer-3')
    FP.AddAircraftToMission(mission_id, 'Hammer-4')
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.5869507, 0.7809585, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointAdvanced(mission_id, 0.5590360, 0.7686830, 2000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'BarrierPatrol,EngageAll,RTB')
    FP.AddMissionWaypointAdvanced(mission_id, 0.5435780, 0.7735660, 2000.0, 300.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.5558020, 0.7677130, 2000.0, 300.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.5726180, 0.7585450, 10000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 4, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Arrow-1')
    FP.AddAircraftToMission(mission_id, 'Arrow-2')
    FP.AddAircraftToMission(mission_id, 'Arrow-3')
    FP.AddAircraftToMission(mission_id, 'Arrow-4')
    FP.AddAircraftToMission(mission_id, 'Arrow-5')
    FP.AddAircraftToMission(mission_id, 'Arrow-6')
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.5658959,0.7351649,0.5000790,0.7487700,0.5218041,0.7587565,0.5555376,0.7509148,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.5869507, 0.7809585, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.5358350, 0.7476260, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Sky-1')
    FP.AddAircraftToMission(mission_id, 'Sky-2')
    FP.AddAircraftToMission(mission_id, 'Sky-3')
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m+R4.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.5563372,0.7750031,0.5480769,0.7907056,0.5664279,0.7917435,0.5691501,0.7770454,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.5869507, 0.7809585, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.5633610, 0.7780460, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ka-27A'
    unit.unitName = "Fregat-M Ka-27 1"
    unit.SetPosition(31.554849, 43.291317, 510.2)
    unit.heading = 227.36
    unit.speed = 100.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DIFAR (105) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DICASS (105) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DIFAR (105) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'APR-2E', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.546133, 0.749507, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.557133, 0.746778, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.560433, 0.750363, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.550020, 0.753734, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
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
    BB.Write('Home', 'Admiral Chabanenko')
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "12.0": 0.0, "14.0": 0.0, "13.0": 0.0, "16.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 14]')
    BB.Write('Selected', '{"RotaryWing": 2, "Speed-": 100, "Alt+": 4000.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 9, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 6, "AT-2M": 0, "TEST-68": 0, "TEST-71ME": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "9M311 Kashtan": 96, "130mm F-44 HE": 1000, "*DICASS*": 0, "SET-65M": 120, "*buoy": 0, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "3M80 Moskit": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "V-611": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "APR-2E": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "*LOFAR*": 0, "*DIFAR*": 0, "30mm OF-84 HE-FRAG AK-630M": 13216, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 224}, "Air": 2, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 2, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 2, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAll": 8}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"APR-2E": [4, 4], "9M330 Kinzhal": [64, 64], "DICASS (105) Sonobuoy": [10, 10], "9M32M Strela 3": [1, 1], "3M80 Moskit": [8, 8], "5V55RM": [64, 64], "9M311 Kashtan": [16, 16], "3M45 Granit": [16, 16], "3M10 Granat": [1, 1], "DIFAR (105) Sonobuoy": [15, 15], "SET-65M": [7, 7], "130mm F-44 HE": [200, 200], "V-611": [72, 72], "LOFAR (105) Sonobuoy": [5, 5], "30mm OF-84 HE-FRAG AK-630M": [708, 708], "76.2mm OS-62 FRAG": [500, 500], "9M33M": [120, 120], "53-56": [20, 20], "100mm OF-58 FRAG": [92, 92], "53-65M": [16, 16], "RPK-3 Metel": [12, 12]}}')
    BB.Write('StationLatitude', '0.751326')
    BB.Write('StationLongitude', '0.551780')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ka-27A'
    unit.unitName = "Berkut-B Ka-27 1"
    unit.SetPosition(33.085792, 44.406636, 506.4)
    unit.heading = 224.34
    unit.speed = 100.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DIFAR (105) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DICASS (105) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'LOFAR (105) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'APR-2E', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.572946, 0.775202, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.579175, 0.772313, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
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
    BB.Write('Home', 'Kerch')
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "12.0": 0.0, "14.0": 0.0, "13.0": 0.0, "16.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 14]')
    BB.Write('Selected', '{"RotaryWing": 2, "Speed-": 100, "Alt+": 4000.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 9, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 6, "AT-2M": 0, "TEST-68": 0, "TEST-71ME": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "9M311 Kashtan": 96, "130mm F-44 HE": 1000, "*DICASS*": 0, "SET-65M": 120, "*buoy": 0, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "3M80 Moskit": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "V-611": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "APR-2E": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "*LOFAR*": 0, "*DIFAR*": 0, "30mm OF-84 HE-FRAG AK-630M": 13216, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 224}, "Air": 2, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 2, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 2, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAll": 8}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"APR-2E": [4, 4], "9M330 Kinzhal": [64, 64], "DICASS (105) Sonobuoy": [10, 10], "9M32M Strela 3": [1, 1], "3M80 Moskit": [8, 8], "5V55RM": [64, 64], "9M311 Kashtan": [16, 16], "3M45 Granit": [16, 16], "3M10 Granat": [1, 1], "DIFAR (105) Sonobuoy": [15, 15], "SET-65M": [7, 7], "130mm F-44 HE": [200, 200], "V-611": [72, 72], "LOFAR (105) Sonobuoy": [5, 5], "30mm OF-84 HE-FRAG AK-630M": [708, 708], "76.2mm OS-62 FRAG": [500, 500], "9M33M": [120, 120], "53-56": [20, 20], "100mm OF-58 FRAG": [92, 92], "53-65M": [16, 16], "RPK-3 Metel": [12, 12]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135M Burevestnik-M'
    unit.unitName = "Pytlivyy"
    UI = SM.GetUnitInterface('Moskva')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0043
    lat_deg = 57.296*leader_track.Lat + -0.0941
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -139.40
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 1, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RPK-3 Metel', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Pytlivyy", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Pytlivyy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "12.0": 0.0, "14.0": 0.0, "13.0": 0.0, "16.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 14]')
    BB.Write('Selected', '{"RotaryWing": 2, "Speed-": 100, "Alt+": 4000.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 9, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 6, "AT-2M": 0, "TEST-68": 0, "TEST-71ME": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "9M311 Kashtan": 96, "130mm F-44 HE": 1000, "*DICASS*": 0, "SET-65M": 120, "*buoy": 0, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "3M80 Moskit": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "V-611": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "APR-2E": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "*LOFAR*": 0, "*DIFAR*": 0, "30mm OF-84 HE-FRAG AK-630M": 13216, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 224}, "Air": 2, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 2, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 2, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAll": 8}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"APR-2E": [4, 4], "9M330 Kinzhal": [64, 64], "DICASS (105) Sonobuoy": [10, 10], "9M32M Strela 3": [1, 1], "3M80 Moskit": [8, 8], "5V55RM": [64, 64], "9M311 Kashtan": [16, 16], "3M45 Granit": [16, 16], "3M10 Granat": [1, 1], "DIFAR (105) Sonobuoy": [15, 15], "SET-65M": [7, 7], "130mm F-44 HE": [200, 200], "V-611": [72, 72], "LOFAR (105) Sonobuoy": [5, 5], "30mm OF-84 HE-FRAG AK-630M": [708, 708], "76.2mm OS-62 FRAG": [500, 500], "9M33M": [120, 120], "53-56": [20, 20], "100mm OF-58 FRAG": [92, 92], "53-65M": [16, 16], "RPK-3 Metel": [12, 12]}}')
    leader_id = UI.LookupFriendlyId('Moskva')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(10.689, 3.128, 5.565, 0.239)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1134B Berkut B'
    unit.unitName = "Kerch"
    UI = SM.GetUnitInterface('Moskva')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1186
    lat_deg = 57.296*leader_track.Lat + -0.0023
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -138.01
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 8, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 9, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'RPK-3 Metel', 8)
    SM.SetUnitLauncherItem(unit.unitName, 11, '53-56', 5)
    SM.SetUnitLauncherItem(unit.unitName, 12, '53-56', 5)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Kerch", 'AT-1', 33)
    SM.AddToUnitMagazine("Kerch", 'DICASS (105) Sonobuoy', 203)
    SM.AddToUnitMagazine("Kerch", 'DIFAR (105) Sonobuoy', 567)
    SM.AddToUnitMagazine("Kerch", 'Fuel', 45900)
    SM.AddToUnitMagazine("Kerch", 'LOFAR (105) Sonobuoy', 203)
    SM.AddToUnitMagazine("Kerch", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Kerch", '53-65M', 20)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "12.0": 0.0, "14.0": 0.0, "13.0": 0.0, "16.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 14]')
    BB.Write('Selected', '{"RotaryWing": 2, "Speed-": 100, "Alt+": 4000.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 9, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"9M32M Strela 3": 6, "AT-2M": 0, "TEST-68": 0, "TEST-71ME": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "9M311 Kashtan": 96, "130mm F-44 HE": 1000, "*DICASS*": 0, "SET-65M": 120, "*buoy": 0, "100mm OF-58 FRAG": 1400, "9M330 Kinzhal": 0, "3M80 Moskit": 0, "TEST-71MKE": 0, "3M45 Granit": 0, "V-611": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "130mm ZS-44 AA": 0, "RPK-3 Metel": 0, "SET-65": 0, "TEST-71": 0, "53-56V": 0, "5V55RM": 0, "APR-2E": 0, "3M10 Granat(n)": 0, "3M10 Granat": 0, "*LOFAR*": 0, "*DIFAR*": 0, "30mm OF-84 HE-FRAG AK-630M": 13216, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "53-56": 0, "100mm ZS-58 AA": 0, "130mm ZS-44P AA": 0, "3M54E Klub Alfa": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 224}, "Air": 2, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 2, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 2, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAll": 8}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 4, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"APR-2E": [4, 4], "9M330 Kinzhal": [64, 64], "DICASS (105) Sonobuoy": [10, 10], "9M32M Strela 3": [1, 1], "3M80 Moskit": [8, 8], "5V55RM": [64, 64], "9M311 Kashtan": [16, 16], "3M45 Granit": [16, 16], "3M10 Granat": [1, 1], "DIFAR (105) Sonobuoy": [15, 15], "SET-65M": [7, 7], "130mm F-44 HE": [200, 200], "V-611": [72, 72], "LOFAR (105) Sonobuoy": [5, 5], "30mm OF-84 HE-FRAG AK-630M": [708, 708], "76.2mm OS-62 FRAG": [500, 500], "9M33M": [120, 120], "53-56": [20, 20], "100mm OF-58 FRAG": [92, 92], "53-65M": [16, 16], "RPK-3 Metel": [12, 12]}}')
    leader_id = UI.LookupFriendlyId('Moskva')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(9.520, 2.545, 0.786, 0.372)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 24)
    FP.SetMissionType(mission_id, '')
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "AB Istanbul-Ataturk"
    unit.SetPosition(28.816667, 41.000000, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'Fuel', 1000000)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", '20mm PGU', 758)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", '20mm PGU-28/B', 758)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", '600 gallon tank', 12)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'AGM-65D', 12)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'AGM-65J', 12)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'AGM-84F Harpoon', 46)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'AGM-84H SLAM-ER', 38)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'AIM-120C7', 136)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'AIM-120D', 126)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'AIM-9P4', 64)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'AIM-9X', 56)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'Chaff-1', 1066)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'DICASS (110) Sonobuoy', 187)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'DIFAR (110) Sonobuoy', 550)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'Flare-1', 1066)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'LOFAR (110) Sonobuoy', 204)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'Mk 16 Zuni FFAR', 52)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'Mk 71 Zuni WAFAR', 52)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'Mk-36 DST', 16)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'Mk-40 DST', 4)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'Mk-41 DST', 4)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'Mk-54', 272)
    SM.AddToUnitMagazine("AB Istanbul-Ataturk", 'Mk-56 Mine', 18)
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
    
    SM.AddUnitToFlightDeck('AB Istanbul-Ataturk', 'KC-130F', 'Cow-5', 2)
    SM.SetFlightDeckUnitLoadout('AB Istanbul-Ataturk', 'Cow-5', '')
    
    SM.AddUnitToFlightDeck('AB Istanbul-Ataturk', 'KC-130F', 'Cow-6', 2)
    SM.SetFlightDeckUnitLoadout('AB Istanbul-Ataturk', 'Cow-6', '')
    
    SM.AddUnitToFlightDeck('AB Istanbul-Ataturk', 'P-3C III Orion', 'Nail-1', 2)
    SM.SetFlightDeckUnitLoadout('AB Istanbul-Ataturk', 'Nail-1', '17 DICASS (100) Sonobuoy;17 LOFAR (100) Sonobuoy;50 DIFAR (100) Sonobuoy;2 AIM-9X;2 AGM-84H SLAM-ER;2 AGM-84H SLAM-ER;2 Mk-54;2 Mk-54;8 Mk-54;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Istanbul-Ataturk', 'P-3C III Orion', 'Nail-2', 2)
    SM.SetFlightDeckUnitLoadout('AB Istanbul-Ataturk', 'Nail-2', '17 DICASS (110) Sonobuoy;17 LOFAR (105) Sonobuoy;50 DIFAR (110) Sonobuoy;2 AIM-9X;2 AGM-84H SLAM-ER;2 AGM-84H SLAM-ER;2 Mk-54;2 Mk-54;8 Mk-54;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Istanbul-Ataturk', 'F-15C', 'Ambush-1', 2)
    SM.SetFlightDeckUnitLoadout('AB Istanbul-Ataturk', 'Ambush-1', '4 AIM-120D;2 AIM-9X;2 AIM-120C7;3 600 gallon tank;30 Chaff-1;30 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('AB Istanbul-Ataturk', 'F-15C', 'Ambush-2', 2)
    SM.SetFlightDeckUnitLoadout('AB Istanbul-Ataturk', 'Ambush-2', '4 AIM-120D;2 AIM-9X;2 AIM-120C7;3 600 gallon tank;30 Chaff-1;30 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('AB Istanbul-Ataturk', 'E-3D/F', 'Hole-1', 2)
    SM.SetFlightDeckUnitLoadout('AB Istanbul-Ataturk', 'Hole-1', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSN 21 Seawolf'
    unit.unitName = "USS Seawolf"
    boxes = [[30.6764, 32.3636, 42.1574, 43.0012]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -325.0)
    unit.heading = 28.30
    unit.speed = 8.6
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Seawolf", 'UGM-109C', 12)
    SM.AddToUnitMagazine("USS Seawolf", 'Mk-48 Mod6', 20)
    SM.AddToUnitMagazine("USS Seawolf", 'Decoy-1', 8)
    SM.AddToUnitMagazine("USS Seawolf", 'Noisemaker-1', 6)
    SM.AddToUnitMagazine("USS Seawolf", 'UGM-84D Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.562156, 0.754093, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Generic submarine'
    unit.unitName = "Neutral Submarine 2"
    unit.SetPosition(32.404029, 42.753251, -200.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MK-T1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'UGM-84C Harpoon', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Neutral Submarine 2", 'MK-T1', 16)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.533382, 0.754320, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.548965, 0.762721, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.608457, 0.753119, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Whale"
    unit.SetPosition(32.609263, 43.258657, 0.0)
    unit.heading = -111.80
    unit.speed = 7.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.559292, 0.749396, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.544969, 0.741047, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.525991, 0.736350, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.502538, 0.724442, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Sea Lion"
    unit.SetPosition(30.926944, 43.288566, 0.0)
    unit.heading = 90.00
    unit.speed = 11.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.605125, 0.752654, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.688556, 0.734822, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Black Sea Pearl"
    unit.SetPosition(31.829639, 43.849205, 0.0)
    unit.heading = 90.00
    unit.speed = 7.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.560545, 0.754384, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.553563, 0.735754, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.507909, 0.725640, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Generic submarine'
    unit.unitName = "Neutral Submarine 1"
    unit.SetPosition(31.922000, 43.245881, -200.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MK-T1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'UGM-84C Harpoon', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Neutral Submarine 1", 'MK-T1', 15)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.543000, 0.759308, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.588475, 0.749327, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('USS Seawolf')
    goal_temp.SetQuantity(1)
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Moskva')
    goal_temp.SetQuantity(1)
    goal_2_0 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Kerch')
    goal_temp.AddTarget('Moskva')
    goal_temp.AddTarget('Pytlivyy')
    goal_temp.SetQuantity(2)
    goal_2_1 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(0.0)
    goal_temp.SetFailTimeout(31556926.0)
    goal_2_2 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_2_0)
    goal_temp.AddGoal(goal_2_1)
    goal_temp.AddGoal(goal_2_2)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Alliance 3 goals
    ##############################

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(61200.0)
    goal_temp.SetFailTimeout(61200.0)
    SM.SetAllianceGoal(3, goal_temp)

    SM.SetAllianceROEByType(3, 2, 2, 2, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
    SM.SetIncludeProbability('Admiral Chabanenko', 1.000000)
    SM.AddRandomBox('Admiral Chabanenko', 31.4026, 31.7581, 43.3295, 43.3669)
    SM.SetIncludeProbability('B-290', 1.000000)
    SM.AddRandomBox('B-290', -9.5884, -8.2009, 63.7166, 63.7912)
    SM.SetIncludeProbability('B-319 Komsomolets Chuvashii', 1.000000)
    SM.AddRandomBox('B-319 Komsomolets Chuvashii', -12.6178, -11.9277, 61.9656, 62.2153)
    SM.SetIncludeProbability('B-355', 0.500000)
    SM.AddRandomBox('B-355', -12.3289, -11.6164, 62.3016, 62.5178)
    SM.SetIncludeProbability('B-380 Gorkovsky Komsomolets', 1.000000)
    SM.AddRandomBox('B-380 Gorkovsky Komsomolets', 32.2834, 33.0489, 43.6710, 43.9938)
    SM.SetIncludeProbability('B-871 Alrossa', 1.000000)
    SM.AddRandomBox('B-871 Alrossa', 31.9861, 32.3177, 43.1599, 43.3017)
    SM.SetIncludeProbability('HMS Spartan', 1.000000)
    SM.AddRandomBox('HMS Spartan', -13.1409, -12.7926, 62.2289, 62.3649)
    SM.AddRandomBox('HMS Spartan', -12.9717, -12.9317, 62.2864, 62.3264)
    SM.SetIncludeProbability('K-23', 1.000000)
    SM.AddRandomBox('K-23', -11.2872, -10.2008, 64.2790, 64.5533)
    SM.SetIncludeProbability('K-239 Karp', 1.000000)
    SM.AddRandomBox('K-239 Karp', -16.5736, -14.1527, 61.5195, 62.5440)
    SM.SetIncludeProbability('K-25', 1.000000)
    SM.AddRandomBox('K-25', -7.2552, -7.1306, 64.2225, 64.6639)
    SM.SetIncludeProbability('K-284 Akula', 1.000000)
    SM.AddRandomBox('K-284 Akula', -9.1701, -9.0127, 64.0996, 64.4044)
    SM.SetIncludeProbability('K-373', 1.000000)
    SM.AddRandomBox('K-373', -8.6907, -8.0384, 64.6377, 64.8625)
    SM.SetIncludeProbability('K-495', 1.000000)
    SM.AddRandomBox('K-495', -11.8708, -11.3250, 62.2400, 62.5022)
    SM.SetIncludeProbability('K-503', 0.500000)
    SM.AddRandomBox('K-503', -14.6953, -12.7976, 62.5479, 62.9397)
    SM.AddRandomBox('K-503', -10.7115, -9.5605, 63.0312, 63.1517)
    SM.SetIncludeProbability('K-508', 0.500000)
    SM.AddRandomBox('K-508', -11.8616, -10.0331, 62.0067, 62.4316)
    SM.SetIncludeProbability('Krasny Krym', 1.000000)
    SM.AddRandomBox('Krasny Krym', -6.9995, -5.9562, 64.7285, 65.0754)
    SM.SetIncludeProbability('Neutral AAW Cruiser', 1.000000)
    SM.AddRandomBox('Neutral AAW Cruiser', -10.6864, -9.9700, 63.2589, 63.6332)
    SM.SetIncludeProbability('Neutral Sub 1', 1.000000)
    SM.AddRandomBox('Neutral Sub 1', -9.1526, -8.3007, 63.9355, 64.1581)
    SM.SetIncludeProbability('Neutral Sub 2', 1.000000)
    SM.AddRandomBox('Neutral Sub 2', -13.4679, -11.6845, 62.0476, 62.1476)
    SM.SetIncludeProbability('Slavny', 1.000000)
    SM.AddRandomBox('Slavny', -11.8902, -11.4992, 64.6134, 64.9101)
    SM.SetIncludeProbability('USS Bergall', 0.500000)
    SM.AddRandomBox('USS Bergall', -10.5761, -9.2939, 63.3368, 63.8419)
    SM.SetIncludeProbability('USS Seahorse', 1.000000)
    SM.AddRandomBox('USS Seahorse', -10.2092, -9.4574, 63.2602, 63.4337)
    SM.SetIncludeProbability('USS Seawolf', 1.000000)
    SM.AddRandomBox('USS Seawolf', 30.6764, 32.3636, 42.1574, 43.0012)
