# Created on 12/07/14 15:48:29
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Norwegian_Sea\nRelease Version of 2011/03/24\n\nA scenario for Global Conflicts 2.\n\nNorwegian Sea is a surface duel between the US and the Russian \nNavy. \n\nThe correct use of passive and active emitters is \nvital. \n\nYou have to localize and destroy the hostile surface group. \n\n\n\n""")
    SM.SetScenarioName("""Norwegian Sea""")
    SM.CreateAlliance(1, 'USA')
    SM.SetAllianceDefaultCountry(1, 'USA')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'Russia')
    SM.SetAllianceDefaultCountry(2, 'Russia')
    SM.SetAlliancePlayable(2, 1)
    SM.CreateAlliance(3, 'Sweden')
    SM.SetAllianceDefaultCountry(3, 'Sweden')
    SM.SetAlliancePlayable(3, 0)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(1)

    SM.SetDateTime(2004,8,8,8,8,8)
    SM.SetStartTheater(4.529166, 58.970829) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(1)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """TASKING ORDERS FOR CMDR US OPERATIONS\n\nINTELLIGENCE\n\nThere is a Russian Surface Action Group heading in your direction. \n\n\nMISSION\n\nYou are to sanitize the Norwegian coastline from any Russian vessel. \nFind and sink the  Russian warships.\n\nEXECUTION\n\nMove to the North. Proceed with care. Take out the whole SAG.\n\nYou must not lose the USS Conolly.\n\nCOMMAND AND SIGNAL\n\nUSS Conolly\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """TASKING ORDERS FOR CMDR RUSSIAN OPERATIONS\n\nINTELLIGENCE\n\nThere is a US Surface Action Group heading into your direction. \n\nMISSION\n\nYou are to sink all hostile warships.\n\nEXECUTION\n\nMove Southbound. Proceed with care.  You must not lose the FFHM \nVorovskiy.\n\nCOMMAND AND SIGNAL\n\nFFHM Vorovskiy\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(3, """This side is not human playable.\n""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Spruance DDG VLS 93'
    unit.unitName = "USS Cushing"
    unit.SetPosition(4.406504, 59.514616, 0.0)
    unit.heading = -1.15
    unit.speed = 16.2
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
    SM.SetUnitLauncherItem(unit.unitName, 8, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'RIM-116B RAM', 21)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Cushing", 'Fuel', 65176)
    SM.AddToUnitMagazine("USS Cushing", 'Mk-46 Mod5', 5)
    SM.AddToUnitMagazine("USS Cushing", 'Mk-50', 1)
    SM.AddToUnitMagazine("USS Cushing", 'Mk-54', 19)
    SM.AddToUnitMagazine("USS Cushing", '120 gallon tank', 4)
    SM.AddToUnitMagazine("USS Cushing", 'AGM-114 Hellfire', 16)
    SM.AddToUnitMagazine("USS Cushing", 'AGM-119B', 4)
    SM.AddToUnitMagazine("USS Cushing", 'Flare-1', 100)
    SM.AddToUnitMagazine("USS Cushing", 'Chaff-1', 100)
    SM.AddToUnitMagazine("USS Cushing", 'LOFAR (100) Sonobuoy', 263)
    SM.AddToUnitMagazine("USS Cushing", 'DICASS (100) Sonobuoy', 263)
    SM.AddToUnitMagazine("USS Cushing", 'DIFAR (100) Sonobuoy', 788)
    SM.AddToUnitMagazine("USS Cushing", 'RUM-139 Mod4 ASROC', 15)
    SM.AddToUnitMagazine("USS Cushing", 'BGM-109 TASM', 5)
    SM.AddToUnitMagazine("USS Cushing", 'BGM-109 TLAM', 38)
    SM.AddToUnitMagazine("USS Cushing", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Cushing", 'RIM-116B RAM', 42)
    SM.AddToUnitMagazine("USS Cushing", '127mm mk 80 HE-PD mk 67', 1200)
    UI.SetSensorState(6, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.077021, 1.045687, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.076826, 1.055827, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.073103, 1.062979, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS Cushing', 'SH-60B', 'Spruance VLS 93 DDG Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Cushing', 'Spruance VLS 93 DDG Seahawk 1', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;15 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Cushing', 'SH-60B', 'Spruance VLS 93 DDG Seahawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Cushing', 'Spruance VLS 93 DDG Seahawk 2', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;15 DIFAR (100) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SH-60B'
    unit.unitName = "Eye"
    unit.SetPosition(4.385419, 59.601648, 50.0)
    unit.heading = 90.00
    unit.speed = 127.5
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AGM-119B', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '120 gallon tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-46 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'LOFAR (100) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'DICASS (100) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'DIFAR (100) Sonobuoy', 15)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.071990, 1.042471, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.080643, 1.043811, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.069357, 1.045023, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.082461, 1.046810, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.066974, 1.047959, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oliver Hazard Perry FFGHM'
    unit.unitName = "USS McInerney"
    UI = SM.GetUnitInterface('USS Cushing')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0829
    lat_deg = 57.296*leader_track.Lat + 0.0514
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66L', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-54', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-54', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS McInerney", 'Fuel', 28092)
    SM.AddToUnitMagazine("USS McInerney", 'Mk-46 Mod5', 4)
    SM.AddToUnitMagazine("USS McInerney", 'Mk-50', 1)
    SM.AddToUnitMagazine("USS McInerney", 'Mk-54', 16)
    SM.AddToUnitMagazine("USS McInerney", 'AGM-114 Hellfire', 8)
    SM.AddToUnitMagazine("USS McInerney", 'AGM-119B', 2)
    SM.AddToUnitMagazine("USS McInerney", '120 gallon tank', 2)
    SM.AddToUnitMagazine("USS McInerney", 'Chaff-1', 50)
    SM.AddToUnitMagazine("USS McInerney", 'Flare-1', 50)
    SM.AddToUnitMagazine("USS McInerney", 'DICASS (100) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS McInerney", 'LOFAR (100) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS McInerney", 'DIFAR (100) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS McInerney", 'RIM-66L', 35)
    SM.AddToUnitMagazine("USS McInerney", 'RGM-84F Harpoon', 4)
    SM.AddToUnitMagazine("USS McInerney", '20mm mark 244-0 ELC', 523)
    SM.AddToUnitMagazine("USS McInerney", '76mm HE-MOM', 240)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Cushing')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(7.380, 1.403, -0.671, 0.219)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS McInerney', 'SH-60B', 'Perry FFG Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS McInerney', 'Perry FFG Seahawk 1', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;15 DIFAR (100) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oliver Hazard Perry FFGHM'
    unit.unitName = "USS Hawes"
    UI = SM.GetUnitInterface('USS Cushing')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1219
    lat_deg = 57.296*leader_track.Lat + 0.0200
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66L', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-54', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-54', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Hawes", 'Fuel', 28092)
    SM.AddToUnitMagazine("USS Hawes", 'Mk-46 Mod5', 4)
    SM.AddToUnitMagazine("USS Hawes", 'Mk-50', 1)
    SM.AddToUnitMagazine("USS Hawes", 'Mk-54', 16)
    SM.AddToUnitMagazine("USS Hawes", 'AGM-114 Hellfire', 8)
    SM.AddToUnitMagazine("USS Hawes", 'AGM-119B', 2)
    SM.AddToUnitMagazine("USS Hawes", '120 gallon tank', 2)
    SM.AddToUnitMagazine("USS Hawes", 'Chaff-1', 50)
    SM.AddToUnitMagazine("USS Hawes", 'Flare-1', 50)
    SM.AddToUnitMagazine("USS Hawes", 'DICASS (100) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Hawes", 'LOFAR (100) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Hawes", 'DIFAR (100) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS Hawes", 'RIM-66L', 35)
    SM.AddToUnitMagazine("USS Hawes", 'RGM-84F Harpoon', 4)
    SM.AddToUnitMagazine("USS Hawes", '20mm mark 244-0 ELC', 523)
    SM.AddToUnitMagazine("USS Hawes", '76mm HE-MOM', 240)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Cushing')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(7.354, 1.135, 1.284, 0.197)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Hawes', 'SH-60B', 'Perry FFG Seahawk 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Hawes', 'Perry FFG Seahawk 101', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;15 DIFAR (100) Sonobuoy;')
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 11351 Nerey'
    unit.unitName = "Vorovskiy"
    unit.SetPosition(3.914562, 61.163646, 0.0)
    unit.heading = 90.00
    unit.speed = 15.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M33M', 20)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Vorovskiy", 'Fuel', 22950)
    SM.AddToUnitMagazine("Vorovskiy", 'AT-1', 18)
    SM.AddToUnitMagazine("Vorovskiy", 'DICASS (95) Sonobuoy', 105)
    SM.AddToUnitMagazine("Vorovskiy", 'LOFAR (95) Sonobuoy', 105)
    SM.AddToUnitMagazine("Vorovskiy", 'DIFAR (95) Sonobuoy', 294)
    SM.AddToUnitMagazine("Vorovskiy", '30mm OF-83 HE-FRAG', 4000)
    SM.AddToUnitMagazine("Vorovskiy", '53-65M', 8)
    SM.AddToUnitMagazine("Vorovskiy", '100mm OF-58 FRAG', 350)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.074658, 1.056084, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.077708, 1.043337, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.080090, 1.034112, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.093972, 1.028593, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "14.0": 0.0, "11.0": 0.0, "16.0": 0.0, "17.0": 0.0, "12.0": 0.0, "18.0": 0.0, "13.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 16]')
    BB.Write('Selected', '{"RotaryWing": 1, "Speed-": 50, "Alt+": 3350.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 6, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"30mm OF-84 HE-FRAG AK-630M": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "*buoy": 0, "*DICASS*": 0, "SET-65M": 0, "P-120 Malakhit": 0, "100mm OF-58 FRAG": 350, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "30mm OF-83 HE-FRAG": 8000, "TEST-71": 0, "*LOFAR*": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "30mm F-33 HE": 0, "100mm ZS-58 AA": 0, "APR-2E": 0, "*DIFAR*": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "30mm Br-83 AP": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 16}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 4, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 4, "32_EngageLimit": "1", "Tasks": {"Nav": 2, "EngageAll": 5}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"DICASS (100) Sonobuoy": [5, 5], "LOFAR (100) Sonobuoy": [5, 5], "DIFAR (100) Sonobuoy": [14, 14], "100mm OF-58 FRAG": [46, 46], "AT-1": [2, 2], "30mm OF-84 HE-FRAG AK-630M": [236, 236], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [100, 100], "P-120 Malakhit": [24, 24], "30mm OF-83 HE-FRAG": [500, 500], "53-65M": [4, 4]}}')
    
    SM.AddUnitToFlightDeck('Vorovskiy', 'Ka-27A', 'Nerey Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Vorovskiy', 'Nerey Ka-27 1', '5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;14 DIFAR (95) Sonobuoy;2 APR-2E;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ka-27A'
    unit.unitName = "Guard"
    unit.SetPosition(3.968649, 61.065957, 50.0)
    unit.heading = 90.00
    unit.speed = 93.8
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DICASS (95) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'LOFAR (95) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DIFAR (95) Sonobuoy', 14)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'AT-1', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.071994, 1.063219, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.076559, 1.060410, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.071292, 1.058654, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.079719, 1.055544, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.065674, 1.056899, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.067480, 1.063796, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "14.0": 0.0, "11.0": 0.0, "16.0": 0.0, "17.0": 0.0, "12.0": 0.0, "18.0": 0.0, "13.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 16]')
    BB.Write('Selected', '{"RotaryWing": 1, "Speed-": 50, "Alt+": 3350.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 6, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"30mm OF-84 HE-FRAG AK-630M": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "*buoy": 0, "*DICASS*": 0, "SET-65M": 0, "P-120 Malakhit": 0, "100mm OF-58 FRAG": 350, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "30mm OF-83 HE-FRAG": 8000, "TEST-71": 0, "*LOFAR*": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "30mm F-33 HE": 0, "100mm ZS-58 AA": 0, "APR-2E": 0, "*DIFAR*": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "30mm Br-83 AP": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 16}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 4, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 4, "32_EngageLimit": "1", "Tasks": {"Nav": 2, "EngageAll": 5}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"DICASS (100) Sonobuoy": [5, 5], "LOFAR (100) Sonobuoy": [5, 5], "DIFAR (100) Sonobuoy": [14, 14], "100mm OF-58 FRAG": [46, 46], "AT-1": [2, 2], "30mm OF-84 HE-FRAG AK-630M": [236, 236], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [100, 100], "P-120 Malakhit": [24, 24], "30mm OF-83 HE-FRAG": [500, 500], "53-65M": [4, 4]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12341 Ovod-1'
    unit.unitName = "Mirazh"
    UI = SM.GetUnitInterface('Vorovskiy')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0788
    lat_deg = 57.296*leader_track.Lat + -0.0311
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "14.0": 0.0, "11.0": 0.0, "16.0": 0.0, "17.0": 0.0, "12.0": 0.0, "18.0": 0.0, "13.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 16]')
    BB.Write('Selected', '{"RotaryWing": 1, "Speed-": 50, "Alt+": 3350.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 6, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"30mm OF-84 HE-FRAG AK-630M": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "*buoy": 0, "*DICASS*": 0, "SET-65M": 0, "P-120 Malakhit": 0, "100mm OF-58 FRAG": 350, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "30mm OF-83 HE-FRAG": 8000, "TEST-71": 0, "*LOFAR*": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "30mm F-33 HE": 0, "100mm ZS-58 AA": 0, "APR-2E": 0, "*DIFAR*": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "30mm Br-83 AP": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 16}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 4, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 4, "32_EngageLimit": "1", "Tasks": {"Nav": 2, "EngageAll": 5}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"DICASS (100) Sonobuoy": [5, 5], "LOFAR (100) Sonobuoy": [5, 5], "DIFAR (100) Sonobuoy": [14, 14], "100mm OF-58 FRAG": [46, 46], "AT-1": [2, 2], "30mm OF-84 HE-FRAG AK-630M": [236, 236], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [100, 100], "P-120 Malakhit": [24, 24], "30mm OF-83 HE-FRAG": [500, 500], "53-65M": [4, 4]}}')
    leader_id = UI.LookupFriendlyId('Vorovskiy')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(5.260, 1.732, 2.488, 0.308)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12341 Ovod-1'
    unit.unitName = "Shtil"
    UI = SM.GetUnitInterface('Vorovskiy')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1024
    lat_deg = 57.296*leader_track.Lat + -0.0275
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "14.0": 0.0, "11.0": 0.0, "16.0": 0.0, "17.0": 0.0, "12.0": 0.0, "18.0": 0.0, "13.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 16]')
    BB.Write('Selected', '{"RotaryWing": 1, "Speed-": 50, "Alt+": 3350.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 6, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"30mm OF-84 HE-FRAG AK-630M": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "*buoy": 0, "*DICASS*": 0, "SET-65M": 0, "P-120 Malakhit": 0, "100mm OF-58 FRAG": 350, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "30mm OF-83 HE-FRAG": 8000, "TEST-71": 0, "*LOFAR*": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "30mm F-33 HE": 0, "100mm ZS-58 AA": 0, "APR-2E": 0, "*DIFAR*": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "30mm Br-83 AP": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 16}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 4, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 4, "32_EngageLimit": "1", "Tasks": {"Nav": 2, "EngageAll": 5}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"DICASS (100) Sonobuoy": [5, 5], "LOFAR (100) Sonobuoy": [5, 5], "DIFAR (100) Sonobuoy": [14, 14], "100mm OF-58 FRAG": [46, 46], "AT-1": [2, 2], "30mm OF-84 HE-FRAG AK-630M": [236, 236], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [100, 100], "P-120 Malakhit": [24, 24], "30mm OF-83 HE-FRAG": [500, 500], "53-65M": [4, 4]}}')
    leader_id = UI.LookupFriendlyId('Vorovskiy')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(6.859, 1.606, 0.410, 0.448)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12341 Ovod-1'
    unit.unitName = "Moroz"
    UI = SM.GetUnitInterface('Vorovskiy')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0060
    lat_deg = 57.296*leader_track.Lat + -0.0410
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "14.0": 0.0, "11.0": 0.0, "16.0": 0.0, "17.0": 0.0, "12.0": 0.0, "18.0": 0.0, "13.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 16]')
    BB.Write('Selected', '{"RotaryWing": 1, "Speed-": 50, "Alt+": 3350.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 6, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"30mm OF-84 HE-FRAG AK-630M": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "*buoy": 0, "*DICASS*": 0, "SET-65M": 0, "P-120 Malakhit": 0, "100mm OF-58 FRAG": 350, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "30mm OF-83 HE-FRAG": 8000, "TEST-71": 0, "*LOFAR*": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "30mm F-33 HE": 0, "100mm ZS-58 AA": 0, "APR-2E": 0, "*DIFAR*": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "30mm Br-83 AP": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 16}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 4, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 4, "32_EngageLimit": "1", "Tasks": {"Nav": 2, "EngageAll": 5}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"DICASS (100) Sonobuoy": [5, 5], "LOFAR (100) Sonobuoy": [5, 5], "DIFAR (100) Sonobuoy": [14, 14], "100mm OF-58 FRAG": [46, 46], "AT-1": [2, 2], "30mm OF-84 HE-FRAG AK-630M": [236, 236], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [100, 100], "P-120 Malakhit": [24, 24], "30mm OF-83 HE-FRAG": [500, 500], "53-65M": [4, 4]}}')
    leader_id = UI.LookupFriendlyId('Vorovskiy')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(4.033, 0.500, 1.467, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12341 Ovod-1'
    unit.unitName = "Burun"
    UI = SM.GetUnitInterface('Vorovskiy')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0553
    lat_deg = 57.296*leader_track.Lat + -0.0581
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"15.0": 0.0, "14.0": 0.0, "11.0": 0.0, "16.0": 0.0, "17.0": 0.0, "12.0": 0.0, "18.0": 0.0, "13.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 16]')
    BB.Write('Selected', '{"RotaryWing": 1, "Speed-": 50, "Alt+": 3350.0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 6, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"30mm OF-84 HE-FRAG AK-630M": 0, "AT-1": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "*buoy": 0, "*DICASS*": 0, "SET-65M": 0, "P-120 Malakhit": 0, "100mm OF-58 FRAG": 350, "30mm OP-84 FRAG Tracer AK-630M": 0, "Yu-7": 0, "Yu-6": 0, "30mm OF-83 HE-FRAG": 8000, "TEST-71": 0, "*LOFAR*": 0, "AT-2M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "30mm F-33 HE": 0, "100mm ZS-58 AA": 0, "APR-2E": 0, "*DIFAR*": 0, "76.2mm ZS-63 AA": 0, "100mm ZS-58P AA": 0, "30mm Br-83 AP": 0, "USET-80": 0, "VTT-1": 0, "Shkval": 0, "53-65M": 16}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 4, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 4, "32_EngageLimit": "1", "Tasks": {"Nav": 2, "EngageAll": 5}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"DICASS (100) Sonobuoy": [5, 5], "LOFAR (100) Sonobuoy": [5, 5], "DIFAR (100) Sonobuoy": [14, 14], "100mm OF-58 FRAG": [46, 46], "AT-1": [2, 2], "30mm OF-84 HE-FRAG AK-630M": [236, 236], "76.2mm OS-62 FRAG": [608, 608], "9M33M": [100, 100], "P-120 Malakhit": [24, 24], "30mm OF-83 HE-FRAG": [500, 500], "53-65M": [4, 4]}}')
    leader_id = UI.LookupFriendlyId('Vorovskiy')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(6.793, 1.375, 1.175, 0.246)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'General Cargo'
    unit.unitName = "Thor"
    unit.SetPosition(3.556750, 60.595157, 0.0)
    unit.heading = 90.00
    unit.speed = 14.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.073363, 1.055589, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.078147, 1.046635, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.080060, 1.035442, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.080778, 1.028602, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.096324, 1.013181, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.118807, 1.004849, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.141529, 1.003606, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.178124, 1.027110, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Herkules"
    unit.SetPosition(4.157095, 59.791586, 0.0)
    unit.heading = 90.00
    unit.speed = 10.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.071885, 1.048893, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.071586, 1.057602, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.070091, 1.075812, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.072940, 1.089554, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.108518, 1.105101, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.145591, 1.126328, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.194811, 1.181275, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.230987, 1.195775, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.297736, 1.246335, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.332878, 1.227134, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12341 Ovod-1'
    unit.unitName = "Patrol Boat 1"
    unit.SetPosition(4.735955, 59.213868, 0.0)
    unit.heading = 90.00
    unit.speed = 33.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.081197, 1.044270, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.076414, 1.056677, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.069238, 1.073420, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.075218, 1.085230, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.039341, 1.083286, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.047712, 1.045017, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.066547, 1.025733, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.114891, 1.000004, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.161532, 1.010898, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.184254, 1.027719, 0.000000, 0.000000)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 1, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"76.2mm ZS-63 AA": 0, "30mm OP-84 FRAG Tracer AK-630M": 0, "30mm OF-84 HE-FRAG AK-630M": 0, "76.2mm OS-62 FRAG": 0, "9M33M": 0, "P-120 Malakhit": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 1}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M33M": [20, 20], "P-120 Malakhit": [6, 6], "30mm OF-84 HE-FRAG AK-630M": [59, 59], "76.2mm OS-62 FRAG": [152, 152]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12341 Ovod-1'
    unit.unitName = "Patrol Boat 2"
    unit.SetPosition(4.504021, 60.778618, 0.0)
    unit.heading = 90.00
    unit.speed = 25.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.046096, 1.059320, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.072646, 1.050241, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.049923, 1.041163, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.077668, 1.034199, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.062839, 1.023379, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.081734, 1.023130, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.084844, 1.011316, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.110675, 1.007834, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.149901, 1.010819, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.172384, 1.025991, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'General Cargo'
    unit.unitName = "Aphrodite"
    unit.SetPosition(3.578236, 60.839521, 0.0)
    unit.heading = 90.00
    unit.speed = 20.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.056388, 1.058415, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.066912, 1.037725, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.075933, 1.005286, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.070431, 0.970834, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.047873, 0.908755, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.042572, 0.894538, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'General Cargo'
    unit.unitName = "Morning Star"
    unit.SetPosition(3.394030, 60.279746, 0.0)
    unit.heading = 90.00
    unit.speed = 14.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.054468, 1.049371, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.069058, 1.041785, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.075277, 1.032955, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.080060, 1.022757, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.083169, 1.010694, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.131257, 0.939846, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Lion"
    unit.SetPosition(4.489984, 60.305011, 0.0)
    unit.heading = 90.00
    unit.speed = 12.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.067144, 1.048874, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.046336, 1.041536, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.028875, 1.034696, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.051250, 1.018032, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Seagull"
    unit.SetPosition(3.709787, 59.845326, 0.0)
    unit.heading = 90.00
    unit.speed = 14.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.070696, 1.046069, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.066511, 1.073599, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.091960, 1.099431, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.133817, 1.115576, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.169395, 1.118117, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Moroz')
    goal_temp.SetQuantity(1)
    goal_3_0 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Shtil')
    goal_temp.SetQuantity(1)
    goal_3_1 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Mirazh')
    goal_temp.SetQuantity(1)
    goal_3_2 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Vorovskiy')
    goal_temp.SetQuantity(1)
    goal_3_3 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Liven')
    goal_temp.SetQuantity(1)
    goal_3_4 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('USS Cushing')
    goal_temp.SetQuantity(1)
    goal_3_5 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(0)
    goal_temp.SetFailTimeout(1e6)
    goal_3_6 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_3_0)
    goal_temp.AddGoal(goal_3_1)
    goal_temp.AddGoal(goal_3_2)
    goal_temp.AddGoal(goal_3_3)
    goal_temp.AddGoal(goal_3_4)
    goal_temp.AddGoal(goal_3_5)
    goal_temp.AddGoal(goal_3_6)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 1, 1, 1, 1)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('USS McInerney')
    goal_temp.SetQuantity(1)
    goal_4_0 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('USS Hawes')
    goal_temp.SetQuantity(1)
    goal_4_1 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('USS Cushing')
    goal_temp.SetQuantity(1)
    goal_4_2 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Vorovskiy')
    goal_temp.SetQuantity(1)
    goal_4_3 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(0)
    goal_temp.SetFailTimeout(1e6)
    goal_4_4 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_4_0)
    goal_temp.AddGoal(goal_4_1)
    goal_temp.AddGoal(goal_4_2)
    goal_temp.AddGoal(goal_4_3)
    goal_temp.AddGoal(goal_4_4)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Alliance 3 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('USS McInerney')
    goal_temp.SetQuantity(1)
    goal_5_0 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('USS Hawes')
    goal_temp.SetQuantity(1)
    goal_5_1 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('USS Cushing')
    goal_temp.SetQuantity(1)
    goal_5_2 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Vorovskiy')
    goal_temp.SetQuantity(1)
    goal_5_3 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(0)
    goal_temp.SetFailTimeout(1e6)
    goal_5_4 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_5_0)
    goal_temp.AddGoal(goal_5_1)
    goal_temp.AddGoal(goal_5_2)
    goal_temp.AddGoal(goal_5_3)
    goal_temp.AddGoal(goal_5_4)
    
    SM.SetAllianceGoal(3, goal_temp)

    SM.SetAllianceROEByType(3, 0, 0, 0, 0)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
