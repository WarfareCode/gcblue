# Created on 11/05/12 10:56:33
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""by EloKa and corrected by amram\n\n""")
    SM.SetScenarioName("""SpanishAttack""")
    SM.CreateAlliance(1, 'Germany')
    SM.SetAllianceDefaultCountry(1, 'Germany')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'Spain')
    SM.SetAllianceDefaultCountry(2, 'Spain')
    SM.SetAlliancePlayable(2, 0)
    SM.CreateAlliance(3, 'Neutral')
    SM.SetAllianceDefaultCountry(3, 'Neutral')
    SM.SetAlliancePlayable(3, 0)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(1)

    SM.SetDateTime(1995,4,13,3,0,0)
    SM.SetStartTheater(13.529165, 41.470833) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(4)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """Spain is going to sink MS Terracotta caused by a not prooven suspense \nof a terroristic attack. Allthough NATO HQ told Spain that there is no \nevidence at all, they send out a set of naval units.\nGerman government decided to sent a taskforce to prevent the attack, \nafter having arguments with the spanish ambassy.\n\nSituation:\nSpanish ships are believed to be north of your taskforce, while MS \nTerracotta is approaching from south with WNWe course. No further \ndetails to positions nor speeds. \nA lot of neutral trafic is in your area, including several friedly warships \nand aircraft.\n\nSub-threat possible, an air-threat is not assumed.\n\nOrders:\nMake sure MS Terracotta remains safe for at least the next 15hours and \nuntil it reaches any position NW of 39N / 8E!\n\nROE:\nWeapons free against identified hostiles!\n\nGood luck!\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """\n""")

    ####################
    SM.SetSimpleBriefing(3, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Type 206A'
    unit.unitName = "U 23"
    unit.SetPosition(8.590184, 38.528031, -17.6)
    unit.heading = 90.00
    unit.speed = 1.8
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'DM2A3', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.176067, 0.672824, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.671516')
    BB.Write('StationLongitude', '0.150050')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 206A'
    unit.unitName = "U 17"
    unit.SetPosition(11.037173, 40.487145, -40.0)
    unit.heading = 239.04
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'DM2A3', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.178857, 0.702568, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bremen FFGHM (1993)'
    unit.unitName = "Bremen"
    unit.SetPosition(10.193640, 39.153182, 0.0)
    unit.heading = 14.93
    unit.speed = 8.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7M(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '76mm HE-MOM', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Bremen", 'Fuel', 11350)
    SM.AddToUnitMagazine("Bremen", 'Mk-46 Mod5', 15)
    SM.AddToUnitMagazine("Bremen", 'Sea Skua', 4)
    SM.AddToUnitMagazine("Bremen", 'LOFAR (90) Sonobuoy', 100)
    SM.AddToUnitMagazine("Bremen", 'DICASS (90) Sonobuoy', 100)
    SM.AddToUnitMagazine("Bremen", 'DIFAR (90) Sonobuoy', 301)
    SM.AddToUnitMagazine("Bremen", '76mm HE-MOM', 220)
    SM.AddToUnitMagazine("Bremen", 'RIM-116A RAM', 42)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.184740, 0.701762, 0.000000, 20.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Bremen', 'Sea Lynx Mk 88', 'Bremen Sea Lynx 1', 2)
    SM.SetFlightDeckUnitLoadout('Bremen', 'Bremen Sea Lynx 1', '1 Mk-46 Mod5;1 Mk-46 Mod5;5 DICASS (90) Sonobuoy;5 LOFAR (90) Sonobuoy;14 DIFAR (90) Sonobuoy;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Brandenburg FFGHM'
    unit.unitName = "Brandenburg"
    UI = SM.GetUnitInterface('Bremen')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0086
    lat_deg = 57.296*leader_track.Lat + -0.0039
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 23.20
    unit.speed = 8.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7P(v2)', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MM-40 B2 Exocet', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'MM-40 B2 Exocet', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, '76mm HE-SAPOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm Rh202 HE-T', 50)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm Rh202 HE-T', 50)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Brandenburg", 'Fuel', 23700)
    SM.AddToUnitMagazine("Brandenburg", 'Mk-46 Mod5', 26)
    SM.AddToUnitMagazine("Brandenburg", 'Sea Skua', 14)
    SM.AddToUnitMagazine("Brandenburg", 'LOFAR (90) Sonobuoy', 192)
    SM.AddToUnitMagazine("Brandenburg", 'DICASS (90) Sonobuoy', 192)
    SM.AddToUnitMagazine("Brandenburg", 'DIFAR (90) Sonobuoy', 581)
    SM.AddToUnitMagazine("Brandenburg", '76mm HE-SAPOM', 240)
    SM.AddToUnitMagazine("Brandenburg", 'RIM-116A RAM', 42)
    SM.AddToUnitMagazine("Brandenburg", '20mm Rh202 HE-T', 1000)
    SM.AddToUnitMagazine("Brandenburg", 'RIM-7P(v2)', 15)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Bremen')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(0.936, 0.374, 1.737, 0.296)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Brandenburg', 'Sea Lynx Mk 88', 'Brandenburg Sea Lynx 1', 2)
    SM.SetFlightDeckUnitLoadout('Brandenburg', 'Brandenburg Sea Lynx 1', '1 Mk-46 Mod5;2 Sea Skua;5 DICASS (90) Sonobuoy;5 LOFAR (90) Sonobuoy;14 DIFAR (90) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('Brandenburg', 'Sea Lynx Mk 88', 'Brandenburg Sea Lynx 2', 1)
    SM.SetFlightDeckUnitLoadout('Brandenburg', 'Brandenburg Sea Lynx 2', '1 Mk-46 Mod5;1 Mk-46 Mod5;5 DICASS (90) Sonobuoy;5 LOFAR (90) Sonobuoy;14 DIFAR (90) Sonobuoy;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bremen FFGHM (1993)'
    unit.unitName = "Karlsruhe"
    UI = SM.GetUnitInterface('Bremen')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0120
    lat_deg = 57.296*leader_track.Lat + 0.0034
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 15.95
    unit.speed = 8.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7M(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '76mm HE-MOM', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Karlsruhe", 'Fuel', 11350)
    SM.AddToUnitMagazine("Karlsruhe", 'Mk-46 Mod5', 15)
    SM.AddToUnitMagazine("Karlsruhe", 'Sea Skua', 4)
    SM.AddToUnitMagazine("Karlsruhe", 'LOFAR (90) Sonobuoy', 100)
    SM.AddToUnitMagazine("Karlsruhe", 'DICASS (90) Sonobuoy', 100)
    SM.AddToUnitMagazine("Karlsruhe", 'DIFAR (90) Sonobuoy', 301)
    SM.AddToUnitMagazine("Karlsruhe", '76mm HE-MOM', 220)
    SM.AddToUnitMagazine("Karlsruhe", 'RIM-116A RAM', 42)
    UI.SetSensorState(0, 1)
    UI.AddTask('MissileWarning', 3.000000, 0)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Bremen')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(1.005, 0.588, 0.918, 0.794)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Karlsruhe', 'Sea Lynx Mk 88', 'Bremen Sea Lynx 101', 3)
    SM.SetFlightDeckUnitLoadout('Karlsruhe', 'Bremen Sea Lynx 101', '1 Mk-46 Mod5;1 Mk-46 Mod5;5 DICASS (90) Sonobuoy;5 LOFAR (90) Sonobuoy;14 DIFAR (90) Sonobuoy;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Type 206'
    unit.unitName = "Submarina"
    unit.SetPosition(10.352316, 40.844842, -100.0)
    unit.heading = 172.87
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'A-184', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'A-184', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'A-184', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'A-184', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'A-184', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'A-184', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'A-184', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'A-184', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.176281, 0.695632, -18.000000, 10.000000)
    UI.AddNavWaypointAdvanced(0.175852, 0.687676, 0.000000, 0.000000)
    UI.SetNavWaypointTasks(1, 'RadarOn,ActiveSonarOn')
    UI.AddNavWaypointAdvanced(0.161287, 0.670554, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.706976')
    BB.Write('StationLongitude', '0.178530')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Small Airstrip'
    unit.unitName = "Provisoric Helo-Airfield"
    unit.SetPosition(9.429052, 42.166371, 52.9)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Provisoric Helo-Airfield", 'Fuel', 100000)
    SM.AddToUnitMagazine("Provisoric Helo-Airfield", '120 gallon tank', 6)
    SM.AddToUnitMagazine("Provisoric Helo-Airfield", 'AGM-114 Hellfire', 36)
    SM.AddToUnitMagazine("Provisoric Helo-Airfield", 'AGM-65B', 14)
    SM.AddToUnitMagazine("Provisoric Helo-Airfield", 'Mk-46 Mod5', 34)
    SM.AddToUnitMagazine("Provisoric Helo-Airfield", 'Flare-1', 50)
    SM.AddToUnitMagazine("Provisoric Helo-Airfield", 'Chaff-1', 50)
    SM.AddToUnitMagazine("Provisoric Helo-Airfield", 'AIM-9M', 6)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Provisoric Helo-Airfield', 'SH-60B', 'Helo-1', 3)
    SM.SetFlightDeckUnitLoadout('Provisoric Helo-Airfield', 'Helo-1', '2 AGM-65B;1 Mk-46 Mod5;1 Mk-46 Mod5;25 Chaff-1;25 Chaff-1;5 DICASS (90) Sonobuoy;5 LOFAR (90) Sonobuoy;15 DIFAR (90) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('Provisoric Helo-Airfield', 'SH-60B', 'Helo-2', 3)
    SM.SetFlightDeckUnitLoadout('Provisoric Helo-Airfield', 'Helo-2', '2 AGM-65B;1 Mk-46 Mod5;1 Mk-46 Mod5;25 Chaff-1;25 Chaff-1;5 DICASS (90) Sonobuoy;5 LOFAR (90) Sonobuoy;15 DIFAR (90) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('Provisoric Helo-Airfield', 'AH-64A', 'Combattante Aero-1', 2)
    SM.SetFlightDeckUnitLoadout('Provisoric Helo-Airfield', 'Combattante Aero-1', '1200 30mm M230 Chaingun Ammo;2 AIM-9M;2 AGM-114 Hellfire;')
    
    SM.AddUnitToFlightDeck('Provisoric Helo-Airfield', 'AH-64A', 'Combattante Aero-2', 2)
    SM.SetFlightDeckUnitLoadout('Provisoric Helo-Airfield', 'Combattante Aero-2', '1200 30mm M230 Chaingun Ammo;2 AGM-114 Hellfire;2 AIM-9M;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Helo-1')
    FP.AddAircraftToMission(mission_id, 'Helo-2')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+50m+R5.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, 'ASW-Helo')
    FP.SetMissionPatrolArea(mission_id, '0.1725266,0.7040057,0.1724911,0.7145318,0.1935144,0.7142931,0.1934139,0.7040057,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1673430, 0.7310780, 500.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1730390, 0.7144360, 300.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'ASWPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.SetMissionLaunchTime(mission_id, '04:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 24)
    FP.SetMissionType(mission_id, '')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Combattante Aero-2')
    FP.AddAircraftToMission(mission_id, 'Combattante Aero-1')
    FP.SetMissionLaunchTime(mission_id, '06:33:00+50m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Standby-ASuW')
    FP.SetMissionPatrolArea(mission_id, '0.1711188,0.7123303,0.1711896,0.6948867,0.1899876,0.6947806,0.1898504,0.7121674,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1655680, 0.7369420, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1711188, 0.7123303, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Descubierta FFG (1987)'
    unit.unitName = "Infanta Elena"
    unit.SetPosition(9.876325, 42.182544, 0.0)
    unit.heading = 154.98
    unit.speed = 16.7
    unit.cost = 2470000128.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7M(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm Meroka APDS-T', 120)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm Meroka APDS-T', 120)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Infanta Elena", '20mm Meroka APDS-T', 1200)
    SM.AddToUnitMagazine("Infanta Elena", '76mm HE-MOM', 240)
    SM.AddToUnitMagazine("Infanta Elena", 'RIM-7M(v1)', 16)
    SM.AddToUnitMagazine("Infanta Elena", 'Mk-46 Mod5', 12)
    UI.SetSensorState(8, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.182767, 0.715740, 0.000000, 0.000000)
    UI.SetNavWaypointTasks(0, 'RadarOn')
    UI.AddNavWaypointAdvanced(0.180110, 0.684712, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.159421, 0.670560, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Baleares FFG (1991)'
    unit.unitName = "Andalucia"
    unit.SetPosition(11.848710, 41.639480, 0.0)
    unit.heading = 156.37
    unit.speed = 19.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '127mm mk 41 AAC', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66E', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm Meroka APDS-T', 120)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm Meroka APDS-T', 120)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Andalucia", '20mm Meroka APDS-T', 1200)
    SM.AddToUnitMagazine("Andalucia", 'RIM-66E', 15)
    SM.AddToUnitMagazine("Andalucia", '127mm mk 41 AAC', 500)
    SM.AddToUnitMagazine("Andalucia", 'Mk-46 Mod5', 12)
    SM.AddToUnitMagazine("Andalucia", 'Mk-37 Mod3', 6)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.210900, 0.710470, 0.000000, 30.000000)
    UI.AddNavWaypointAdvanced(0.227414, 0.692687, 1119130094729839200000000000.000000, 25.000000)
    UI.AddNavWaypointAdvanced(0.215574, 0.678271, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.199053, 0.671916, 1119130094729839200000000000.000000, 25.000000)
    UI.SetNavWaypointTasks(3, 'RadarOn,EngageAll')
    UI.AddNavWaypointAdvanced(0.153739, 0.671947, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.142783, 0.677419, 0.000000, 0.000000)
    UI.SetNavWaypointTasks(5, 'ASWPatrolArea')
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Baleares FFG (1991)'
    unit.unitName = "Asturias"
    UI = SM.GetUnitInterface('Infanta Elena')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0070
    lat_deg = 57.296*leader_track.Lat + -0.0120
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 153.43
    unit.speed = 9.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '127mm mk 41 AAC', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66E', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm Meroka APDS-T', 120)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm Meroka APDS-T', 120)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Asturias", '20mm Meroka APDS-T', 1200)
    SM.AddToUnitMagazine("Asturias", 'RIM-66E', 15)
    SM.AddToUnitMagazine("Asturias", '127mm mk 41 AAC', 500)
    SM.AddToUnitMagazine("Asturias", 'Mk-46 Mod5', 12)
    SM.AddToUnitMagazine("Asturias", 'Mk-37 Mod3', 6)
    UI.SetSensorState(4, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.193303, 0.717804, 0.000000, 30.000000)
    UI.AddNavWaypointAdvanced(0.201033, 0.697905, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.206403, 0.668235, 0.000000, 20.000000)
    UI.SetNavWaypointTasks(2, 'RadarOn')
    UI.AddNavWaypointAdvanced(0.167147, 0.660902, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.143940, 0.675871, 0.000000, 0.000000)
    UI.SetNavWaypointTasks(4, 'ASWPatrolArea')
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Infanta Elena')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(1.946, 1.495, -2.796, 0.435)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Sabalo SSK'
    unit.unitName = "Sabalo"
    unit.SetPosition(9.148646, 39.105974, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AEG-SUT', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AEG-SUT', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AEG-SUT', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'AEG-SUT', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'AEG-SUT', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'AEG-SUT', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'AEG-SUT', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'AEG-SUT', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Sabalo", 'AEG-SUT', 6)
    UI.SetSensorState(1, 1)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.162959, 0.681694, -30.000000, 5.000000)
    UI.AddNavWaypointAdvanced(0.165804, 0.680031, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.168687, 0.681314, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.172516, 0.690056, 0.000000, 0.000000)
    UI.SetNavWaypointTasks(3, 'SubBattery,RadarOn')
    UI.AddNavWaypointAdvanced(0.183512, 0.684962, -100.000000, 3.000000)
    UI.AddNavWaypointAdvanced(0.183737, 0.678688, -50.000000, 3.000000)
    UI.SetNavWaypointTasks(5, 'ActiveSonarOn')
    UI.AddNavWaypointAdvanced(0.173036, 0.667714, 0.000000, 0.000000)
    UI.SetNavWaypointTasks(6, 'ActiveSonarOff,SubBattery')
    UI.AddNavWaypointAdvanced(0.154766, 0.666746, -75.000000, 2.000000)
    UI.SetNavWaypointTasks(7, 'ASWPatrolArea')
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tourville'
    unit.unitName = "De Grasse"
    unit.SetPosition(6.093466, 39.947246, 0.0)
    unit.heading = 124.46
    unit.speed = 32.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Matra R.440N', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MM-40 B2 Exocet', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MM-40 B2 Exocet', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, '100mm OEA F1 HE', 35)
    SM.SetUnitLauncherItem(unit.unitName, 4, '100mm OEA F1 HE', 35)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'L5 Mod4', 2)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'L5 Mod4', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("De Grasse", 'Fuel', 23700)
    SM.AddToUnitMagazine("De Grasse", 'A-244S', 29)
    SM.AddToUnitMagazine("De Grasse", 'Sea Skua', 16)
    SM.AddToUnitMagazine("De Grasse", 'LOFAR (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("De Grasse", 'DICASS (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("De Grasse", 'DIFAR (90) Sonobuoy', 609)
    SM.AddToUnitMagazine("De Grasse", 'Matra R.440N', 16)
    SM.AddToUnitMagazine("De Grasse", '100mm OEA F1 HE', 1200)
    SM.AddToUnitMagazine("De Grasse", 'L5 Mod4', 12)
    SM.AddToUnitMagazine("De Grasse", '20mm F2', 1000)
    UI.SetSensorState(1, 1)
    UI.SetSensorState(2, 1)
    UI.SetSensorState(4, 1)
    UI.SetSensorState(9, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.126904, 0.688017, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.147540, 0.668342, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.684644')
    BB.Write('StationLongitude', '0.130114')
    
    SM.AddUnitToFlightDeck('De Grasse', 'Lynx HAS.Mk.2', 'Tourville Helo2', 1)
    SM.SetFlightDeckUnitLoadout('De Grasse', 'Tourville Helo2', '1 A-244S;1 A-244S;5 DICASS (90) Sonobuoy;5 LOFAR (90) Sonobuoy;14 DIFAR (90) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Lynx HAS.Mk.2'
    unit.unitName = "Tourville Helo1"
    unit.SetPosition(7.588151, 40.941667, 510.2)
    unit.heading = 214.71
    unit.speed = 49.5
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'A-244S', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'A-244S', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DICASS (90) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'LOFAR (90) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'DIFAR (90) Sonobuoy', 14)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.171339, 0.723034, 1000.000000, 30.000000)
    UI.SetNavWaypointTasks(0, 'RadarRandom,ASWPatrolArea')
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'De Grasse')
    BB.Write('StationLatitude', '0.715820')
    BB.Write('StationLongitude', '0.130622')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 82 DDG'
    unit.unitName = "HMS Bristol"
    unit.SetPosition(13.010881, 40.050839, 0.0)
    unit.heading = -72.55
    unit.speed = 14.9
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Sea Dart Mod0', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '114mm N4A1 HE', 16)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm/75 GCM-AO3-2 APDS', 83)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm/75 GCM-AO3-2 APDS', 83)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.209503, 0.700120, 0.000000, 20.000000)
    UI.SetNavWaypointTasks(0, 'RadarRandom,EngageAll')
    UI.AddNavWaypointAdvanced(0.176019, 0.703764, 0.000000, 12.000000)
    UI.SetNavWaypointTasks(1, 'RadarOn,ActiveSonarOn')
    UI.AddNavWaypointAdvanced(0.182440, 0.731471, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Rubis AMETHYSTE'
    unit.unitName = "Amethyste"
    unit.SetPosition(11.148899, 41.662054, -70.0)
    unit.heading = -160.39
    unit.speed = 9.1
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'F-17 Mod2', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'F-17 Mod2', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'F-17 Mod2', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SM-39 Exocet', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Amethyste", 'F-17 Mod2', 8)
    SM.AddToUnitMagazine("Amethyste", 'SM-39 Exocet', 5)
    UI.SetSensorState(6, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.179063, 0.713978, 0.000000, 5.000000)
    UI.SetNavWaypointTasks(0, 'ActiveSonarOn')
    UI.AddNavWaypointAdvanced(0.173410, 0.685037, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Boat'
    unit.unitName = "Temp 0850"
    unit.SetPosition(10.433366, 39.947543, 0.0)
    unit.heading = 65.80
    unit.speed = 12.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.191895, 0.700587, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.204060, 0.694205, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.204986, 0.684075, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.224544, 0.669174, 0.000000, 0.000000)
    UI.SetNavWaypointTasks(3, 'ASWPatrolArea')
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Boat'
    unit.unitName = "Temp 851"
    unit.SetPosition(6.279664, 39.097073, 0.0)
    unit.heading = 106.22
    unit.speed = 21.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.167668, 0.669195, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.204060, 0.694205, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.204986, 0.684075, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.224544, 0.669174, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Boat'
    unit.unitName = "Temp 852"
    unit.SetPosition(6.050927, 41.160048, 0.0)
    unit.heading = -67.79
    unit.speed = 14.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.064525, 0.730935, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Temp 0895"
    unit.SetPosition(9.033753, 38.259006, 0.0)
    unit.heading = -96.81
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.011969, 0.654009, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "MS Terracotta"
    unit.SetPosition(11.924971, 37.443996, 0.0)
    unit.heading = -42.65
    unit.speed = 7.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.204887, 0.654606, 3426449664.000000, 13.000000)
    UI.SetNavWaypointTasks(0, 'RadarOn')
    UI.AddNavWaypointAdvanced(0.166740, 0.662252, 0.000000, 17.000000)
    UI.SetNavWaypointTasks(1, 'RadarOn')
    UI.AddNavWaypointAdvanced(0.136850, 0.683384, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Chemical Tanker'
    unit.unitName = "Temp 0735"
    unit.SetPosition(15.313319, 39.189871, 0.0)
    unit.heading = -92.73
    unit.speed = 10.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(5, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.209075, 0.681836, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.145055, 0.669806, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.055255, 0.670467, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Container Ship'
    unit.unitName = "Temp 0340"
    unit.SetPosition(10.973790, 41.524832, 0.0)
    unit.heading = -50.72
    unit.speed = 11.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.174610, 0.735056, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.168263, 0.749722, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.169030, 0.753487, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.171793, 0.757755, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Container Ship'
    unit.unitName = "Temp 341"
    unit.SetPosition(7.639216, 39.821826, 0.0)
    unit.heading = 163.35
    unit.speed = 11.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.143490, 0.668636, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.178271, 0.657810, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ferry'
    unit.unitName = "Temp 0065"
    unit.SetPosition(7.650256, 41.328650, 0.0)
    unit.heading = 89.81
    unit.speed = 7.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.156872, 0.721378, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.161309, 0.721469, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.165267, 0.722644, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.192972, 0.739193, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Temp 0990"
    unit.SetPosition(5.508753, 41.786149, 0.0)
    unit.heading = 60.96
    unit.speed = 5.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.113469, 0.736455, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.086850, 0.722328, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Temp 991"
    unit.SetPosition(7.751260, 42.491295, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Temp 992"
    unit.SetPosition(10.289754, 42.199572, 0.0)
    unit.heading = -44.07
    unit.speed = 7.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.176504, 0.738881, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.178903, 0.742413, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.182381, 0.743591, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Temp 993"
    unit.SetPosition(11.583946, 40.201125, 0.0)
    unit.heading = 180.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.701514')
    BB.Write('StationLongitude', '0.202178')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Temp 994"
    unit.SetPosition(10.084603, 39.125821, 0.0)
    unit.heading = 97.21
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.190458, 0.681456, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.173787, 0.680712, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.189019, 0.678944, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Temp 995"
    unit.SetPosition(10.605175, 37.684951, 0.0)
    unit.heading = 37.26
    unit.speed = 1.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.233325, 0.706929, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.201492, 0.674117, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Temp 996"
    unit.SetPosition(5.111045, 38.973470, 0.0)
    unit.heading = 85.89
    unit.speed = 5.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.096070, 0.680599, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.104225, 0.676191, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.114900, 0.677129, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Temp 0094"
    unit.SetPosition(9.047749, 39.261533, -0.0)
    unit.heading = 314.79
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Temp 0094", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Temp 0094", 'Chaff-1', 10000)
    SM.AddToUnitMagazine("Temp 0094", 'Flare-1', 10000)
    SM.AddToUnitMagazine("Temp 0094", 'AIM-9M', 100)
    SM.AddToUnitMagazine("Temp 0094", 'AIM-120B', 100)
    UI.SetSensorState(0, 1)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Temp 0094', 'Dehaviland Canada DHC-8-102', 'Temp-18', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0094', 'Temp-18', '')
    
    SM.AddUnitToFlightDeck('Temp 0094', 'Dehaviland Canada DHC-8-102', 'Temp-19', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0094', 'Temp-19', '')
    
    SM.AddUnitToFlightDeck('Temp 0094', 'Dehaviland Canada DHC-8-102', 'Temp-20', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0094', 'Temp-20', '')
    
    SM.AddUnitToFlightDeck('Temp 0094', 'Dehaviland Canada DHC-8-102', 'Temp-21', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0094', 'Temp-21', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Temp-18')
    FP.SetMissionLaunchTime(mission_id, '05:39:50+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 3)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2153260,0.6831300,0.2163260,0.6841300,0.2153260,0.6831300,0.2163260,0.6841300,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1559580, 0.6883320, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2153260, 0.6831300, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.SetMissionLaunchTime(mission_id, '04:13:50+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.1917780,0.7168290,0.1927780,0.7178290,0.1917780,0.7168290,0.1927780,0.7178290,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1559580, 0.6883320, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1917780, 0.7168290, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.SetMissionLaunchTime(mission_id, '04:35:50+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.1993960,0.6740550,0.2003960,0.6750550,0.1993960,0.6740550,0.2003960,0.6750550,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1559580, 0.6883320, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1993960, 0.6740550, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Temp 0356"
    unit.SetPosition(16.073930, 40.647861, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Temp 0356", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Temp 0356", 'Chaff-1', 10000)
    SM.AddToUnitMagazine("Temp 0356", 'Flare-1', 10000)
    SM.AddToUnitMagazine("Temp 0356", 'AIM-9M', 100)
    SM.AddToUnitMagazine("Temp 0356", 'AIM-120B', 100)
    UI.SetSensorState(0, 1)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Temp 0356', 'Boeing 747', 'Temp-17', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0356', 'Temp-17', '')
    
    SM.AddUnitToFlightDeck('Temp 0356', 'Boeing 747', 'Temp-15', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0356', 'Temp-15', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Temp-15')
    FP.AddAircraftToMission(mission_id, 'Temp-17')
    FP.SetMissionLaunchTime(mission_id, '03:50:50+763m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Temp 0793')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, 'Standby-AAW')
    FP.SetMissionPatrolArea(mission_id, '0.0012030,0.7679640,0.0012030,0.7447970,0.0419550,0.7447970,0.0419550,0.7679640,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2815430, 0.7104390, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0419550, 0.7447970, 10000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.SetMissionLaunchTime(mission_id, '08:40:50+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Temp 796')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2867423, 0.7094390, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.0564122, 0.7852366, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Temp 0793"
    unit.SetPosition(10.166907, 37.000067, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Temp 0793", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Temp 0793", 'Chaff-1', 10000)
    SM.AddToUnitMagazine("Temp 0793", 'Flare-1', 10000)
    SM.AddToUnitMagazine("Temp 0793", 'AIM-9M', 100)
    SM.AddToUnitMagazine("Temp 0793", 'AIM-120B', 100)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Temp 0793', 'F-16A/B Blk 15 OCU', 'Zapper202', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0793', 'Zapper202', '2 AIM-9M;2 AIM-120B;2 AIM-120B;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Temp 0793', 'Boeing 767', 'Temp-10', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0793', 'Temp-10', '')
    
    SM.AddUnitToFlightDeck('Temp 0793', 'Boeing 767', 'Temp-11', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0793', 'Temp-11', '')
    
    SM.AddUnitToFlightDeck('Temp 0793', 'Boeing 767', 'Temp-12', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0793', 'Temp-12', '')
    
    SM.AddUnitToFlightDeck('Temp 0793', 'Boeing 767', 'Temp-13', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0793', 'Temp-13', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Temp-10')
    FP.AddAircraftToMission(mission_id, 'Temp-11')
    FP.SetMissionLaunchTime(mission_id, '03:14:59+1m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Temp 0793')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Default')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1579290, 0.6849330, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.1771590, 0.6454650, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.SetMissionLaunchTime(mission_id, '03:14:59+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0554218,0.0243465,-0.0554218,0.0292531,-0.0507182,0.0292531,-0.0507182,0.0243465,')
    FP.SetMissionPatrolAnchor(mission_id, 'Temp 0793', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.1771791, 0.6445854, 2000.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2093460, 0.6987640, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'EngageAll,AirPatrolArea')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Temp 794"
    unit.SetPosition(2.978578, 39.614760, 760.1)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Temp 794", 'Fuel', 2000000)
    SM.AddToUnitMagazine("Temp 794", 'Chaff-1', 20000)
    SM.AddToUnitMagazine("Temp 794", 'Flare-1', 20000)
    SM.AddToUnitMagazine("Temp 794", 'AIM-9M', 200)
    SM.AddToUnitMagazine("Temp 794", 'AIM-120B', 200)
    UI.SetSensorState(0, 1)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Temp 794', 'E-2C', 'Skyeye301', 2)
    SM.SetFlightDeckUnitLoadout('Temp 794', 'Skyeye301', '')
    
    SM.AddUnitToFlightDeck('Temp 794', 'E-2C', 'Skyeye302', 2)
    SM.SetFlightDeckUnitLoadout('Temp 794', 'Skyeye302', '')
    
    SM.AddUnitToFlightDeck('Temp 794', 'E-2C', 'Skyeye303', 2)
    SM.SetFlightDeckUnitLoadout('Temp 794', 'Skyeye303', '')
    
    SM.AddUnitToFlightDeck('Temp 794', 'E-2C', 'Skyeye304', 2)
    SM.SetFlightDeckUnitLoadout('Temp 794', 'Skyeye304', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.SetMissionLaunchTime(mission_id, '07:00:00+917m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Standby-AAW')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0529860, 0.6924080, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1745550, 0.7135820, 2000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'BarrierPatrol,EngageAll,RTB')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1936280, 0.7135820, 2000.0, 300.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.1745550, 0.7135820, 2000.0, 300.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.1747550, 0.7135820, 10000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 4, 'Land')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Temp 795"
    unit.SetPosition(-2.175406, 40.630787, 760.1)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Temp 795", 'Fuel', 2000000)
    SM.AddToUnitMagazine("Temp 795", 'Chaff-1', 20000)
    SM.AddToUnitMagazine("Temp 795", 'Flare-1', 20000)
    SM.AddToUnitMagazine("Temp 795", 'AIM-9M', 200)
    SM.AddToUnitMagazine("Temp 795", 'AIM-120B', 200)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Temp 795', 'Generic aircraft', 'Temp-6', 3)
    SM.SetFlightDeckUnitLoadout('Temp 795', 'Temp-6', '4 AAM-I;4 ASM-I;')
    
    SM.AddUnitToFlightDeck('Temp 795', 'Generic aircraft', 'Temp-7', 2)
    SM.SetFlightDeckUnitLoadout('Temp 795', 'Temp-7', '4 AAM-I;4 ASM-I;')
    
    SM.AddUnitToFlightDeck('Temp 795', 'Generic aircraft', 'Temp-8', 2)
    SM.SetFlightDeckUnitLoadout('Temp 795', 'Temp-8', '4 AAM-I;4 ASM-I;')
    
    SM.AddUnitToFlightDeck('Temp 795', 'Generic aircraft', 'Temp-9', 2)
    SM.SetFlightDeckUnitLoadout('Temp 795', 'Temp-9', '4 AAM-I;4 ASM-I;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Temp-6')
    FP.SetMissionLaunchTime(mission_id, '03:16:50+1331m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Temp 0356')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, 'Default')
    FP.AddMissionWaypointAdvanced(mission_id, -0.0317703, 0.7091410, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.2803920, 0.7092690, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Temp 796"
    unit.SetPosition(4.672356, 43.466413, 0.0)
    unit.heading = 306.54
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Temp 796", 'Fuel', 2000000)
    SM.AddToUnitMagazine("Temp 796", 'Chaff-1', 20000)
    SM.AddToUnitMagazine("Temp 796", 'Flare-1', 20000)
    SM.AddToUnitMagazine("Temp 796", 'AIM-9M', 200)
    SM.AddToUnitMagazine("Temp 796", 'AIM-120B', 200)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Temp 796', 'F-16A/B Blk 15 OCU', 'Zapper501', 3)
    SM.SetFlightDeckUnitLoadout('Temp 796', 'Zapper501', '2 AIM-9M;2 AIM-120B;2 AIM-120B;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Temp 796', 'F-16A/B Blk 15 OCU', 'Zapper502', 3)
    SM.SetFlightDeckUnitLoadout('Temp 796', 'Zapper502', '2 AIM-9M;2 AIM-120B;2 AIM-120B;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Temp 796', 'E-2C', 'Skyeye504', 2)
    SM.SetFlightDeckUnitLoadout('Temp 796', 'Skyeye504', '')
    
    SM.AddUnitToFlightDeck('Temp 796', 'E-2C', 'Skyeye502', 2)
    SM.SetFlightDeckUnitLoadout('Temp 796', 'Skyeye502', '')
    
    SM.AddUnitToFlightDeck('Temp 796', 'E-2C', 'Skyeye503', 2)
    SM.SetFlightDeckUnitLoadout('Temp 796', 'Skyeye503', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Zapper501')
    FP.AddAircraftToMission(mission_id, 'Zapper502')
    FP.SetMissionLaunchTime(mission_id, '06:27:50+1m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Default')
    FP.SetMissionPatrolArea(mission_id, '0.1962638,0.7087659,0.1906382,0.7196621,0.1701937,0.7138997,0.1938290,0.6849610,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.0859930, 0.7559960, 1000.0, 80.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1701940, 0.7139000, 10000.0, 280.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RadarOn')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'E-2C'
    unit.unitName = "Skyeye204"
    unit.SetPosition(9.967013, 38.395527, 9616.6)
    unit.heading = 85.83
    unit.speed = 100.0
    unit.cost = 80000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(1, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Temp 0793')
    BB.Write('StationLatitude', '0.671227')
    BB.Write('StationLongitude', '0.174230')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Boeing 747'
    unit.unitName = "Temp-14"
    unit.SetPosition(13.731231, 40.405743, 10000.0)
    unit.heading = -103.84
    unit.speed = 246.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Land', 3.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Temp 0356')
    BB.Write('LandTarget', 'Temp 0181')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Temp 0181"
    unit.SetPosition(-0.867401, 37.749326, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Temp 0181", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Temp 0181", 'Chaff-1', 10000)
    SM.AddToUnitMagazine("Temp 0181", 'Flare-1', 10000)
    SM.AddToUnitMagazine("Temp 0181", 'AIM-9M', 100)
    SM.AddToUnitMagazine("Temp 0181", 'AIM-120B', 100)
    UI.SetSensorState(0, 1)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Temp 0181', 'F-16A/B Blk 15 OCU', 'Zapper1', 3)
    SM.SetFlightDeckUnitLoadout('Temp 0181', 'Zapper1', '2 AIM-9M;2 AIM-120B;2 AIM-120B;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Temp 0181', 'F-16A/B Blk 15 OCU', 'Zapper2', 3)
    SM.SetFlightDeckUnitLoadout('Temp 0181', 'Zapper2', '2 AIM-9M;2 AIM-120B;2 AIM-120B;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Temp 0181', 'E-2C', 'Skyeye1', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0181', 'Skyeye1', '')
    
    SM.AddUnitToFlightDeck('Temp 0181', 'E-2C', 'Skyeye2', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0181', 'Skyeye2', '')
    
    SM.AddUnitToFlightDeck('Temp 0181', 'E-2C', 'Skyeye3', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0181', 'Skyeye3', '')
    
    SM.AddUnitToFlightDeck('Temp 0181', 'E-2C', 'Skyeye4', 2)
    SM.SetFlightDeckUnitLoadout('Temp 0181', 'Skyeye4', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'E-2C'
    unit.unitName = "Skyeye501"
    unit.SetPosition(6.958632, 43.868749, 10.0)
    unit.heading = 113.92
    unit.speed = 100.0
    unit.cost = 80000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(1, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Temp 796')
    BB.Write('StationLatitude', '0.765680')
    BB.Write('StationLongitude', '0.124800')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'A-50'
    unit.unitName = "Temp 0472"
    unit.SetPosition(16.547423, 35.552375, 10000.0)
    unit.heading = -51.24
    unit.speed = 169.8
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(1, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Land', 3.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('LandTarget', 'Temp 796')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MIM-14 Nike Hercules'
    unit.unitName = "Temp 0776"
    unit.SetPosition(8.459894, 39.980021, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 11, 'MIM-14A', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MIM-14 Nike Hercules'
    unit.unitName = "Temp 777"
    unit.SetPosition(12.685228, 37.878698, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 11, 'MIM-14A', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MIM-14 Nike Hercules'
    unit.unitName = "Temp 778"
    unit.SetPosition(12.369701, 41.832338, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'MIM-14A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 11, 'MIM-14A', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Forward Observation Post'
    unit.unitName = "Temp 0263"
    unit.SetPosition(9.649469, 40.679545, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Improved Hawk PIP III'
    unit.unitName = "Temp 0520"
    unit.SetPosition(12.950565, 40.894920, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MIM-23C', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MIM-23C', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MIM-23C', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Etna (A5326)'
    unit.unitName = "Etna"
    unit.SetPosition(10.177258, 40.177935, 0.0)
    unit.heading = -166.07
    unit.speed = 21.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 1, '20mm HE-T', 50)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Etna", '20mm HE-T', 200)
    SM.AddToUnitMagazine("Etna", '76mm HE-MOM', 800)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.174175, 0.690091, 0.000000, 0.000000)
    UI.SetNavWaypointTasks(0, 'RadarRandom')
    UI.AddNavWaypointAdvanced(0.207428, 0.689284, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.207980, 0.697846, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.197932, 0.702689, 0.000000, 0.000000)
    UI.SetNavWaypointTasks(3, 'RadarOn')
    UI.AddNavWaypointAdvanced(0.185125, 0.714132, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.171348, 0.746285, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.163983, 0.760231, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Etna', 'SH-3D', 'King1', 2)
    SM.SetFlightDeckUnitLoadout('Etna', 'King1', '2 Mk-46 Mod5;10 DICASS (90) Sonobuoy;10 LOFAR (90) Sonobuoy;30 DIFAR (90) Sonobuoy;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'King1')
    FP.SetMissionLaunchTime(mission_id, '07:00:50+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'HMS Broadsword')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1845829, 0.7032990, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.2256672, 0.6971301, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 22 FF Batch 1'
    unit.unitName = "HMS Broadsword"
    UI = SM.GetUnitInterface('HMS Bristol')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0231
    lat_deg = 57.296*leader_track.Lat + -0.0076
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -73.24
    unit.speed = 13.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
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
    SM.AddToUnitMagazine("HMS Broadsword", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Broadsword", 'Stingray', 29)
    SM.AddToUnitMagazine("HMS Broadsword", 'Sea Skua', 16)
    SM.AddToUnitMagazine("HMS Broadsword", 'LOFAR (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Broadsword", 'DICASS (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Broadsword", 'DIFAR (90) Sonobuoy', 609)
    SM.AddToUnitMagazine("HMS Broadsword", 'Sea Wolf', 40)
    SM.AddToUnitMagazine("HMS Broadsword", '30mm/75 GCM-AO3-2 APDS', 1660)
    SM.AddToUnitMagazine("HMS Broadsword", '20mm/85  GAM-B01 HE-I', 500)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Bristol')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(3.764, 0.500, -0.874, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 23 FF'
    unit.unitName = "HMS Northumberland"
    UI = SM.GetUnitInterface('Etna')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0266
    lat_deg = 57.296*leader_track.Lat + -0.0129
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -159.78
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Sea Wolf', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '114mm N4A1 HE', 16)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm/75 GCM-AO3-2 APDS', 83)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm/75 GCM-AO3-2 APDS', 83)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Stingray', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Northumberland", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Northumberland", 'Stingray', 29)
    SM.AddToUnitMagazine("HMS Northumberland", 'Sea Skua', 16)
    SM.AddToUnitMagazine("HMS Northumberland", 'LOFAR (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Northumberland", 'DICASS (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Northumberland", 'DIFAR (90) Sonobuoy', 609)
    SM.AddToUnitMagazine("HMS Northumberland", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Northumberland", 'Sea Wolf', 20)
    SM.AddToUnitMagazine("HMS Northumberland", '30mm/75 GCM-AO3-2 APDS', 1660)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Etna')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(2.000, 0.500, 0.200, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Northumberland', 'Lynx HAS.Mk.2', 'Type 23 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Northumberland', 'Type 23 Lynx 1', '1 A-244S;1 A-244S;5 DICASS (90) Sonobuoy;5 LOFAR (90) Sonobuoy;14 DIFAR (90) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Northumberland', 'Lynx HAS.Mk.2', 'Type 23 Lynx 2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Northumberland', 'Type 23 Lynx 2', '1 A-244S;1 A-244S;5 DICASS (90) Sonobuoy;5 LOFAR (90) Sonobuoy;14 DIFAR (90) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 23 FF'
    unit.unitName = "HMS Marlborough"
    UI = SM.GetUnitInterface('Etna')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0134
    lat_deg = 57.296*leader_track.Lat + -0.0336
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -154.98
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Sea Wolf', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '114mm N4A1 HE', 16)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm/75 GCM-AO3-2 APDS', 83)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm/75 GCM-AO3-2 APDS', 83)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Stingray', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Marlborough", 'Fuel', 28370)
    SM.AddToUnitMagazine("HMS Marlborough", 'Stingray', 29)
    SM.AddToUnitMagazine("HMS Marlborough", 'Sea Skua', 16)
    SM.AddToUnitMagazine("HMS Marlborough", 'LOFAR (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Marlborough", 'DICASS (90) Sonobuoy', 404)
    SM.AddToUnitMagazine("HMS Marlborough", 'DIFAR (90) Sonobuoy', 1218)
    SM.AddToUnitMagazine("HMS Marlborough", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Marlborough", 'Sea Wolf', 20)
    SM.AddToUnitMagazine("HMS Marlborough", '30mm/75 GCM-AO3-2 APDS', 1660)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Etna')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(2.000, 0.500, 0.200, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Marlborough', 'Lynx HAS.Mk.2', 'Type 23 Lynx 101', 1)
    SM.SetFlightDeckUnitLoadout('HMS Marlborough', 'Type 23 Lynx 101', '1 A-244S;1 A-244S;5 DICASS (90) Sonobuoy;5 LOFAR (90) Sonobuoy;14 DIFAR (90) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Marlborough', 'Lynx HAS.Mk.2', 'Type 23 Lynx 102', 1)
    SM.SetFlightDeckUnitLoadout('HMS Marlborough', 'Type 23 Lynx 102', '1 A-244S;1 A-244S;5 DICASS (90) Sonobuoy;5 LOFAR (90) Sonobuoy;14 DIFAR (90) Sonobuoy;')
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(54000.0)
    goal_temp.SetFailTimeout(31556926.0)
    goal_24_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('MS Terracotta')
    goal_temp.SetQuantity(1)
    goal_24_1 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_24_0)
    goal_temp.AddGoal(goal_24_1)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 1, 1, 1, 1)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('MS Terracotta')
    goal_temp.SetQuantity(1)
    goal_25_0 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(31556926.0)
    goal_temp.SetFailTimeout(54000.0)
    goal_25_1 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Asturias')
    goal_temp.AddTarget('Andalucia')
    goal_temp.AddTarget('Infanta Elena')
    goal_temp.AddTarget('Submarina')
    goal_temp.SetQuantity(1)
    goal_25_2 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_25_0)
    goal_temp.AddGoal(goal_25_1)
    goal_temp.AddGoal(goal_25_2)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 1, 1, 1, 1)

    ##############################
    ### Alliance 3 goals
    ##############################

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(31556926.0)
    goal_temp.SetFailTimeout(3600000.0)
    goal_26_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('MS Terracotta')
    goal_temp.SetQuantity(1)
    goal_26_1 = goal_temp

    goal_temp = SM.AreaGoal()
    goal_temp.SetTargetList('MS Terracotta')
    goal_temp.SetTimeObjective(0.000000)
    goal_temp.SetLogicAny(1)
    goal_temp.SetQuantity(1)
    goal_temp.AddPointDeg(8.01018, 40.29494)
    goal_temp.AddPointDeg(8.01018, 39.03396)
    goal_temp.AddPointDeg(5.97402, 39.03396)
    goal_temp.AddPointDeg(5.97458, 40.29538)
    goal_26_2 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_26_0)
    goal_temp.AddGoal(goal_26_1)
    goal_temp.AddGoal(goal_26_2)
    
    SM.SetAllianceGoal(3, goal_temp)

    SM.SetAllianceROEByType(3, 1, 1, 1, 1)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
    SM.SetIncludeProbability('Bunker des Stabes', 1.000000)
    SM.AddRandomBox('Bunker des Stabes', 10.9412, 10.9812, 53.7270, 53.7670)
    SM.SetIncludeProbability('Komm', 1.000000)
    SM.AddRandomBox('Komm', 9.6808, 9.7422, 53.9603, 54.0217)
    SM.SetIncludeProbability('MS Terracotta', 1.000000)
    SM.SetIncludeProbability('Provisoric Helo-Airfield', 1.000000)
