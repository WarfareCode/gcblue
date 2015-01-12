# Created on 11/08/14 05:32:23
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""GIUK Part 4 HMS Invincible\nRelease Version of 2013/10/13\n\nA scenario for Global Conflicts 2.\n\nIn the first days of the war, Soviet subs try to reach the open Atlantic in \norder to wait for the convoys Nato troops in Europe need to survive. \n\nThere is a risk that warships will follow those, at least into the GIUK Gap.\n\nIn this scenario You have to deal with a strong Soviet SAG invading the \nGap.\n\nComments and critiques welcome!\n\n\n\n""")
    SM.SetScenarioName("""GIUK Part 4 HMS Invincible""")
    SM.CreateAlliance(1, 'UK')
    SM.SetAllianceDefaultCountry(1, 'UK')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 0)
    SM.SetUserAlliance(1)

    SM.SetDateTime(1985,8,5,0,0,0)
    SM.SetStartTheater(-17.470833, 60.470833) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1511.807983,60.959999,1505.102417,304.800018,1501.444824,609.600037,1491.691162,914.400024,1484.985596,1219.200073,1487.119263,2362.199951,1502.664063,2743.199951,1507.235962,3962.400146,1527.657593,5181.600098,1548.079224')

    ####################
    SM.SetSimpleBriefing(1, """ORDERS FOR CMDR UK OPERATIONS\n\nINTELLIGENCE\n\nThe control of the GIUK Gap is vital for our efforts to win the war. \n\nMISSION\n\nFind and destroy the Soviet Surface Action Group. \n\nEXECUTION\n\nProceed with care. Expect heavy resistance. Sub threat unknown. \nProtect Your carrier at all costs. \n\nCOMMAND AND SIGNAL\n\nHMS Invincible \n\n\n\n\n\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'CV (R05/6/7) Invincible'
    unit.unitName = "HMS Invincible"
    unit.SetPosition(-17.552791, 60.557913, 0.0)
    unit.heading = 43.45
    unit.speed = 13.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Sea Dart Mod0', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm PGU-14/B API', 79)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm PGU-14/B API', 79)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm PGU-14/B API', 79)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Invincible", 'Fuel', 760000)
    SM.AddToUnitMagazine("HMS Invincible", 'Sea Dart Mod0', 40)
    SM.AddToUnitMagazine("HMS Invincible", '30mm PGU-14/B API', 578)
    SM.AddToUnitMagazine("HMS Invincible", 'AIM-9L', 868)
    SM.AddToUnitMagazine("HMS Invincible", 'BAe Sea Eagle', 150)
    SM.AddToUnitMagazine("HMS Invincible", '68mm SNEB Rockets', 4500)
    SM.AddToUnitMagazine("HMS Invincible", 'Mk-83', 770)
    SM.AddToUnitMagazine("HMS Invincible", 'Mk-82', 1320)
    SM.AddToUnitMagazine("HMS Invincible", 'Mk-81', 1320)
    SM.AddToUnitMagazine("HMS Invincible", '100 gallon wing tank', 32)
    SM.AddToUnitMagazine("HMS Invincible", '190 gallon wing tank', 32)
    SM.AddToUnitMagazine("HMS Invincible", '300 gallon wing tank', 32)
    SM.AddToUnitMagazine("HMS Invincible", 'Chaff-1', 5280)
    SM.AddToUnitMagazine("HMS Invincible", 'Flare-1', 5280)
    SM.AddToUnitMagazine("HMS Invincible", 'Stingray', 1080)
    SM.AddToUnitMagazine("HMS Invincible", 'DICASS (80) Sonobuoy', 3700)
    SM.AddToUnitMagazine("HMS Invincible", 'LOFAR (80) Sonobuoy', 3700)
    SM.AddToUnitMagazine("HMS Invincible", 'DIFAR (80) Sonobuoy', 11000)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Earl1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Earl1', '2 AIM-9L;2 BAe Sea Eagle;1 Mk-83;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Earl2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Earl2', '2 AIM-9L;2 BAe Sea Eagle;1 Mk-83;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Earl3', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Earl3', '2 AIM-9L;2 Mk-83;1 Mk-83;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Earl4', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Earl4', '2 AIM-9L;2 BAe Sea Eagle;1 Mk-83;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Earl5', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Earl5', '2 AIM-9L;2 BAe Sea Eagle;1 Mk-83;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Earl6', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Earl6', '2 AIM-9L;2 Mk-83;1 Mk-83;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Earl7', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Earl7', '2 AIM-9L;2 Mk-83;1 Mk-83;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Earl8', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Earl8', '2 AIM-9L;2 BAe Sea Eagle;1 Mk-83;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Esquire1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Esquire1', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (100) Sonobuoy;10 LOFAR (100) Sonobuoy;30 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Esquire2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Esquire2', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (100) Sonobuoy;10 LOFAR (100) Sonobuoy;30 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Esquire3', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Esquire3', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (100) Sonobuoy;10 LOFAR (100) Sonobuoy;30 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Esquire4', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Esquire4', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (100) Sonobuoy;10 LOFAR (100) Sonobuoy;30 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Esquire5', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Esquire5', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (100) Sonobuoy;10 LOFAR (100) Sonobuoy;30 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Esquire6', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Esquire6', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (100) Sonobuoy;10 LOFAR (100) Sonobuoy;30 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Esquire7', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Esquire7', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (100) Sonobuoy;10 LOFAR (100) Sonobuoy;30 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Esquire8', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Esquire8', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (100) Sonobuoy;10 LOFAR (100) Sonobuoy;30 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Esquire9', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Esquire9', '2 Mk-46 Mod5;2 Mk-46 Mod5;10 DICASS (100) Sonobuoy;10 LOFAR (100) Sonobuoy;30 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King AEW.Mk.2A', 'Knight3', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Knight3', '')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King AEW.Mk.2A', 'Knight2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Knight2', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oberon SS'
    unit.unitName = "HMS Osirus"
    unit.SetPosition(-16.587987, 61.855321, -225.0)
    unit.heading = 52.43
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
    SM.AddToUnitMagazine("HMS Osirus", 'mk-24 Tigerfish', 13)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Swiftsure SSN'
    unit.unitName = "HMS Sovereign"
    unit.SetPosition(-15.566175, 61.835267, -305.0)
    unit.heading = 49.76
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Decoy-1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Sovereign", 'mk-24 Tigerfish', 20)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Swiftsure SSN'
    unit.unitName = "HMS Spartan"
    boxes = [[-13.1409, -12.7926, 62.2289, 62.3649],[-12.9717, -12.9317, 62.2864, 62.3264]]
    box = boxes[int(2*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -305.0)
    unit.heading = 37.87
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Decoy-1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Spartan", 'mk-24 Tigerfish', 25)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Sea King AEW.Mk.2A'
    unit.unitName = "Knight1"
    unit.SetPosition(-17.540645, 60.578827, 516.0)
    unit.heading = 356.86
    unit.speed = 100.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.300739, 1.062468, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.293750, 1.053129, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'HMS Invincible')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Leander FF Batch 3B'
    unit.unitName = "HMS Diomede"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0012
    lat_deg = 57.296*leader_track.Lat + 0.0359
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 47.49
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '114mm/53 mk6 SAP', 16)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Sea Wolf', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MM-38 Exocet', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm APT percussion', 96)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm APT percussion', 96)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Stingray', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Diomede", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Diomede", 'Sea Skua', 8)
    SM.AddToUnitMagazine("HMS Diomede", 'Stingray', 20)
    SM.AddToUnitMagazine("HMS Diomede", 'LOFAR (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Diomede", 'DICASS (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Diomede", 'DIFAR (80) Sonobuoy', 405)
    SM.AddToUnitMagazine("HMS Diomede", '114mm/53 mk6 SAP', 250)
    SM.AddToUnitMagazine("HMS Diomede", 'Sea Wolf', 20)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(3.916, 0.500, -0.744, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Diomede', 'Lynx HAS.Mk.2', 'Leander FF 3B Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Diomede', 'Leander FF 3B Lynx 1', '1 A-244S;1 A-244S;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 22 FF Batch 2'
    unit.unitName = "HMS Beaver"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0742
    lat_deg = 57.296*leader_track.Lat + -0.0012
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 3.37
    unit.speed = 3.0
    unit.cost = 150000000.0
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
    SM.AddToUnitMagazine("HMS Beaver", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Beaver", 'Stingray', 29)
    SM.AddToUnitMagazine("HMS Beaver", 'Sea Skua', 16)
    SM.AddToUnitMagazine("HMS Beaver", 'LOFAR (80) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Beaver", 'DICASS (80) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Beaver", 'DIFAR (80) Sonobuoy', 609)
    SM.AddToUnitMagazine("HMS Beaver", 'Sea Wolf', 40)
    SM.AddToUnitMagazine("HMS Beaver", '30mm/75 GCM-AO3-2 APDS', 1660)
    SM.AddToUnitMagazine("HMS Beaver", '20mm/85  GAM-B01 HE-I', 500)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(4.024, 0.500, 0.885, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Beaver', 'Lynx HAS.Mk.2', 'Type 22 B2 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Beaver', 'Type 22 B2 Lynx 1', '1 A-244S;1 A-244S;')
    
    SM.AddUnitToFlightDeck('HMS Beaver', 'Lynx HAS.Mk.2', 'Type 22 B2 Lynx 2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Beaver', 'Type 22 B2 Lynx 2', '1 A-244S;1 A-244S;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 42 DDG Batch 2'
    unit.unitName = "HMS Liverpool"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0824
    lat_deg = 57.296*leader_track.Lat + -0.0020
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 52.43
    unit.speed = 3.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Sea Dart Mod0', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, '114mm N4A1 HE', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Liverpool", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Liverpool", 'Stingray', 20)
    SM.AddToUnitMagazine("HMS Liverpool", 'Sea Skua', 8)
    SM.AddToUnitMagazine("HMS Liverpool", 'LOFAR (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Liverpool", 'DICASS (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Liverpool", 'DIFAR (80) Sonobuoy', 405)
    SM.AddToUnitMagazine("HMS Liverpool", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Liverpool", '20mm Mark 149-4', 475)
    SM.AddToUnitMagazine("HMS Liverpool", 'Sea Dart Mod0', 22)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(4.567, 0.952, -2.365, 0.308)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Liverpool', 'Lynx HAS.Mk.2', 'Type 42 B2 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Liverpool', 'Type 42 B2 Lynx 1', '1 A-244S;1 A-244S;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Leander FF Batch 3A'
    unit.unitName = "HMS Jupiter"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0002
    lat_deg = 57.296*leader_track.Lat + -0.0339
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 40.24
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '114mm/53 mk6 SAP', 16)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Sea Wolf', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MM-38 Exocet', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm APT percussion', 96)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm APT percussion', 96)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Stingray', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Jupiter", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Jupiter", 'Sea Skua', 8)
    SM.AddToUnitMagazine("HMS Jupiter", 'Stingray', 20)
    SM.AddToUnitMagazine("HMS Jupiter", 'LOFAR (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Jupiter", 'DICASS (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Jupiter", 'DIFAR (80) Sonobuoy', 405)
    SM.AddToUnitMagazine("HMS Jupiter", '114mm/53 mk6 SAP', 250)
    SM.AddToUnitMagazine("HMS Jupiter", 'Sea Wolf', 20)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(3.830, 0.500, 2.399, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Jupiter', 'Lynx HAS.Mk.2', 'Leander FF 3A Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Jupiter', 'Leander FF 3A Lynx 1', '1 A-244S;1 A-244S;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 82 DDG'
    unit.unitName = "HMS Bristol"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0122
    lat_deg = 57.296*leader_track.Lat + 0.0136
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 45.00
    unit.speed = 3.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Sea Dart Mod0', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '114mm N4A1 HE(AA fuse)', 16)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm/75 GCM-AO3-2 HE', 83)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm/75 GCM-AO3-2 HE', 83)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Bristol", '30mm/75 GCM-AO3-2 HE', 1660)
    SM.AddToUnitMagazine("HMS Bristol", '114mm N4A1 HE(AA fuse)', 800)
    SM.AddToUnitMagazine("HMS Bristol", 'Sea Dart Mod0', 40)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"114mm N4A1 HE(AA fuse)": 0, "114mm N4A1 HE": 0, "30mm/75 GCM-AO3-2 APDS": 0, "114mm N4A1 HE-ER": 0, "30mm/75 GCM-AO3-2 HE": 0, "114mm N4A1 HE-ER(AA fuse)": 0, "Sea Dart Mod0": 0, "Sea Dart Mod2": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 1, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 1, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"Sea Dart Mod0": [2, 2], "114mm N4A1 HE": [16, 16], "30mm/75 GCM-AO3-2 APDS": [166, 166]}}')
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(1.494, 0.543, -0.349, 0.265)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 61 Kashin'
    unit.unitName = "Krasny Kavkaz"
    unit.SetPosition(-16.111631, 59.768723, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-600', 16)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-600', 16)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Kh-35', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Krasny Kavkaz", '53-65M', 30)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.310238, 1.053231, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.321778, 1.078932, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.264780, 1.108305, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.174563, 1.133307, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1143 Krechet'
    unit.unitName = "Novorossiysk"
    unit.SetPosition(-10.972715, 63.295851, 0.0)
    unit.heading = -97.59
    unit.speed = 12.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-500 Bazalt', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 6, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 7, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 8, '76.2mm OS-62 FRAG', 250)
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
    SM.AddToUnitMagazine("Novorossiysk", 'Fuel', 826200)
    SM.AddToUnitMagazine("Novorossiysk", 'R-60', 48)
    SM.AddToUnitMagazine("Novorossiysk", 'FAB-500', 72)
    SM.AddToUnitMagazine("Novorossiysk", 'FAB-250', 168)
    SM.AddToUnitMagazine("Novorossiysk", 'FAB-100', 288)
    SM.AddToUnitMagazine("Novorossiysk", '23mm AM-23', 1368)
    SM.AddToUnitMagazine("Novorossiysk", 'S-5K Rocket', 5376)
    SM.AddToUnitMagazine("Novorossiysk", 'S-8K 80mm', 4320)
    SM.AddToUnitMagazine("Novorossiysk", 'Kh-23', 96)
    SM.AddToUnitMagazine("Novorossiysk", 'AT-1', 312)
    SM.AddToUnitMagazine("Novorossiysk", 'DICASS (75) Sonobuoy', 2100)
    SM.AddToUnitMagazine("Novorossiysk", 'LOFAR (75) Sonobuoy', 2100)
    SM.AddToUnitMagazine("Novorossiysk", 'DIFAR (75) Sonobuoy', 5892)
    SM.AddToUnitMagazine("Novorossiysk", 'RN-28', 4)
    SM.AddToUnitMagazine("Novorossiysk", '30mm OF-84 HE-FRAG AK-630M', 6720)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.298665, 1.073306, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.269482, 1.060236, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger1', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger1', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger2', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger2', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger3', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger3', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger4', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger4', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix1', 2)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix1', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix2', 2)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix2', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix3', 2)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix3', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix4', 2)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix4', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger101', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger101', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger102', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger102', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger103', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger103', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger104', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger104', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger105', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger105', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger106', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger106', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger107', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger107', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Yak-38M', 'Forger108', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Forger108', '2 R-60;2 R-60;6 23mm AM-23;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix101', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix101', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix102', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix102', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix103', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix103', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix104', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix104', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix105', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix105', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix106', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix106', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix107', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix107', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix108', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix108', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix109', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix109', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix110', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix110', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix111', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix111', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix112', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix112', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix113', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix113', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('Novorossiysk', 'Ka-27A', 'Helix114', 1)
    SM.SetFlightDeckUnitLoadout('Novorossiysk', 'Helix114', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Forger1')
    FP.AddAircraftToMission(mission_id, 'Forger2')
    FP.AddAircraftToMission(mission_id, 'Forger3')
    FP.AddAircraftToMission(mission_id, 'Forger4')
    FP.AddAircraftToMission(mission_id, 'Forger101')
    FP.AddAircraftToMission(mission_id, 'Forger102')
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0013754,0.0022833,-0.0015558,0.0047377,-0.0026053,0.0011683,0.0006004,0.0015290,')
    FP.SetMissionPatrolAnchor(mission_id, 'Novorossiysk', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.1923220, 1.1043520, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.1959820, 1.1040291, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Forger103')
    FP.AddAircraftToMission(mission_id, 'Forger104')
    FP.AddAircraftToMission(mission_id, 'Forger105')
    FP.AddAircraftToMission(mission_id, 'Forger106')
    FP.AddAircraftToMission(mission_id, 'Forger107')
    FP.AddAircraftToMission(mission_id, 'Forger108')
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0026298,0.0001118,-0.0012400,0.0014605,0.0024197,0.0006312,0.0001602,0.0000884,')
    FP.SetMissionPatrolAnchor(mission_id, 'Novorossiysk', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.1905100, 1.1057210, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.1927520, 1.1038680, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Helix1')
    FP.AddAircraftToMission(mission_id, 'Helix2')
    FP.AddAircraftToMission(mission_id, 'Helix3')
    FP.AddAircraftToMission(mission_id, 'Helix4')
    FP.AddAircraftToMission(mission_id, 'Helix101')
    FP.AddAircraftToMission(mission_id, 'Helix102')
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'ASW-Helo')
    FP.SetMissionPatrolArea(mission_id, '0.0001533,0.0001642,-0.0011313,-0.0000573,-0.0001527,0.0010867,0.0008337,0.0003123,')
    FP.SetMissionPatrolAnchor(mission_id, 'Novorossiysk', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.1922950, 1.1047170, 500.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.1934440, 1.1045060, 300.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'ASWPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 945 Barrakuda'
    unit.unitName = "K-239 Karp"
    boxes = [[-16.5736, -14.1527, 61.5195, 62.5440]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -410.0)
    unit.heading = 219.09
    unit.speed = 9.0
    unit.cost = 0.0
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
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.308258, 1.073250, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.265737, 1.063879, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.236364, 1.075908, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 956 Sarych'
    unit.unitName = "Otlichniy"
    UI = SM.GetUnitInterface('Novorossiysk')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0460
    lat_deg = 57.296*leader_track.Lat + 0.0202
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -98.97
    unit.speed = 3.0
    unit.cost = 0.0
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
    SM.AddToUnitMagazine("Otlichniy", 'Fuel', 45900)
    SM.AddToUnitMagazine("Otlichniy", 'AT-1', 22)
    SM.AddToUnitMagazine("Otlichniy", 'DICASS (75) Sonobuoy', 135)
    SM.AddToUnitMagazine("Otlichniy", 'LOFAR (75) Sonobuoy', 135)
    SM.AddToUnitMagazine("Otlichniy", 'DIFAR (75) Sonobuoy', 378)
    SM.AddToUnitMagazine("Otlichniy", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Otlichniy", '130mm F-44 HE', 1000)
    SM.AddToUnitMagazine("Otlichniy", '53-65M', 12)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Novorossiysk')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(3.133, 0.500, 0.880, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Otlichniy', 'Ka-27A', 'Sarych Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Otlichniy', 'Sarych Ka-27 1', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "BDK-69"
    UI = SM.GetUnitInterface('Novorossiysk')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0504
    lat_deg = 57.296*leader_track.Lat + 0.0089
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -99.46
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("BDK-69", '9M32 Strela 2', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Novorossiysk')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(2.701, 0.500, 2.901, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "Nikolay Vilkov"
    UI = SM.GetUnitInterface('Novorossiysk')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0108
    lat_deg = 57.296*leader_track.Lat + 0.0209
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -96.34
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Nikolay Vilkov", '9M32 Strela 2', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Novorossiysk')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(2.365, 0.500, 1.889, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1155 Fregat'
    unit.unitName = "Admiral Zakharov"
    UI = SM.GetUnitInterface('Novorossiysk')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1572
    lat_deg = 57.296*leader_track.Lat + 0.0082
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -101.31
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
    SM.AddToUnitMagazine("Admiral Zakharov", 'Fuel', 45900)
    SM.AddToUnitMagazine("Admiral Zakharov", 'AT-1', 22)
    SM.AddToUnitMagazine("Admiral Zakharov", 'DICASS (75) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Zakharov", 'LOFAR (75) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Zakharov", 'DIFAR (75) Sonobuoy', 378)
    SM.AddToUnitMagazine("Admiral Zakharov", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Admiral Zakharov", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Admiral Zakharov", '53-65M', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Novorossiysk')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(7.879, 0.500, 3.178, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Admiral Zakharov', 'Ka-27A', 'Fregat Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Admiral Zakharov', 'Fregat Ka-27 1', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1241.1 Molniya'
    unit.unitName = "R-256 Poltavskiy Komsomolets"
    UI = SM.GetUnitInterface('Novorossiysk')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0530
    lat_deg = 57.296*leader_track.Lat + -0.0287
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -98.53
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M32 Strela 2', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("R-256 Poltavskiy Komsomolets", '76.2mm OS-62 FRAG', 152)
    SM.AddToUnitMagazine("R-256 Poltavskiy Komsomolets", '9M32 Strela 2', 16)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Novorossiysk')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(4.246, 0.500, 4.177, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135M Burevestnik-M'
    unit.unitName = "Rezvyy"
    UI = SM.GetUnitInterface('Novorossiysk')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0008
    lat_deg = 57.296*leader_track.Lat + 0.0855
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -98.97
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
    SM.AddToUnitMagazine("Rezvyy", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Rezvyy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Novorossiysk')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(9.387, 0.500, 1.685, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1134A Berkut'
    unit.unitName = "Admiral Oktyabrskiy"
    UI = SM.GetUnitInterface('Novorossiysk')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2159
    lat_deg = 57.296*leader_track.Lat + -0.0052
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -97.63
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-611', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-611', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RPK-3 Metel', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 8, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 10, '53-65M', 5)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Admiral Oktyabrskiy", 'Fuel', 45900)
    SM.AddToUnitMagazine("Admiral Oktyabrskiy", 'AT-1', 37)
    SM.AddToUnitMagazine("Admiral Oktyabrskiy", 'DICASS (75) Sonobuoy', 256)
    SM.AddToUnitMagazine("Admiral Oktyabrskiy", 'LOFAR (75) Sonobuoy', 203)
    SM.AddToUnitMagazine("Admiral Oktyabrskiy", 'DIFAR (75) Sonobuoy', 567)
    SM.AddToUnitMagazine("Admiral Oktyabrskiy", '53-65M', 20)
    SM.AddToUnitMagazine("Admiral Oktyabrskiy", '57mm Tracer-FRAG', 4000)
    SM.AddToUnitMagazine("Admiral Oktyabrskiy", 'V-611', 48)
    SM.AddToUnitMagazine("Admiral Oktyabrskiy", '30mm OF-84 HE-FRAG AK-630M', 944)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Novorossiysk')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(10.805, 0.500, 0.097, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Admiral Oktyabrskiy', 'Ka-27A', 'Berkut-A Ka-27 101', 1)
    SM.SetFlightDeckUnitLoadout('Admiral Oktyabrskiy', 'Berkut-A Ka-27 101', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1134A Berkut'
    unit.unitName = "Admiral Nakhimov"
    UI = SM.GetUnitInterface('Novorossiysk')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0127
    lat_deg = 57.296*leader_track.Lat + -0.0876
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -100.01
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-611', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-611', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RPK-3 Metel', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 8, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 10, '53-65M', 5)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Admiral Nakhimov", 'Fuel', 45900)
    SM.AddToUnitMagazine("Admiral Nakhimov", 'AT-1', 33)
    SM.AddToUnitMagazine("Admiral Nakhimov", 'DICASS (75) Sonobuoy', 203)
    SM.AddToUnitMagazine("Admiral Nakhimov", 'LOFAR (75) Sonobuoy', 203)
    SM.AddToUnitMagazine("Admiral Nakhimov", 'DIFAR (75) Sonobuoy', 567)
    SM.AddToUnitMagazine("Admiral Nakhimov", '53-65M', 20)
    SM.AddToUnitMagazine("Admiral Nakhimov", '57mm Tracer-FRAG', 4000)
    SM.AddToUnitMagazine("Admiral Nakhimov", 'V-611', 44)
    SM.AddToUnitMagazine("Admiral Nakhimov", '30mm OF-84 HE-FRAG AK-630M', 944)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Novorossiysk')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(9.876, 0.500, 4.793, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Admiral Nakhimov', 'Ka-27A', 'Berkut-A Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Admiral Nakhimov', 'Berkut-A Ka-27 1', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1164 Atlant'
    unit.unitName = "Moskva"
    UI = SM.GetUnitInterface('Novorossiysk')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0849
    lat_deg = 57.296*leader_track.Lat + -0.0321
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -97.13
    unit.speed = 3.0
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
    SM.AddToUnitMagazine("Moskva", 'DICASS (75) Sonobuoy', 175)
    SM.AddToUnitMagazine("Moskva", 'LOFAR (75) Sonobuoy', 175)
    SM.AddToUnitMagazine("Moskva", 'DIFAR (75) Sonobuoy', 490)
    SM.AddToUnitMagazine("Moskva", '30mm OF-84 HE-FRAG AK-630M', 1416)
    SM.AddToUnitMagazine("Moskva", '130mm F-44 HE', 500)
    SM.AddToUnitMagazine("Moskva", '53-65M', 30)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Novorossiysk')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(5.680, 0.500, -0.547, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Moskva', 'Ka-27A', 'Atlant Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Moskva', 'Atlant Ka-27 1', '5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DIFAR (100) Sonobuoy;2 AT-1;')
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Novorossiysk')
    goal_temp.SetQuantity(1)
    goal_0_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('HMS Invincible')
    goal_temp.SetQuantity(1)
    goal_0_1 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Moskva')
    goal_temp.AddTarget('Admiral Nakhimov')
    goal_temp.AddTarget('Admiral Oktyabrskiy')
    goal_temp.AddTarget('Rezvyy')
    goal_temp.AddTarget('R-256 Poltavskiy Komsomolets')
    goal_temp.AddTarget('Admiral Zakharov')
    goal_temp.AddTarget('Nikolay Vilkov')
    goal_temp.AddTarget('BDK-69')
    goal_temp.AddTarget('Otlichniy')
    goal_temp.AddTarget('Novorossiysk')
    goal_temp.SetQuantity(8)
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
    goal_temp.AddTarget('HMS Invincible')
    goal_temp.SetQuantity(1)
    goal_1_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Novorossiysk')
    goal_temp.SetQuantity(1)
    goal_1_1 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Admiral Oktyabrskiy')
    goal_temp.AddTarget('Moskva')
    goal_temp.AddTarget('Admiral Nakhimov')
    goal_temp.AddTarget('Rezvyy')
    goal_temp.AddTarget('R-256 Poltavskiy Komsomolets')
    goal_temp.AddTarget('Admiral Zakharov')
    goal_temp.AddTarget('Nikolay Vilkov')
    goal_temp.AddTarget('BDK-69')
    goal_temp.AddTarget('Otlichniy')
    goal_temp.AddTarget('Novorossiysk')
    goal_temp.SetQuantity(3)
    goal_1_2 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(59940.0)
    goal_temp.SetFailTimeout(3600.0)
    goal_1_3 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_1_0)
    goal_temp.AddGoal(goal_1_1)
    goal_temp.AddGoal(goal_1_2)
    goal_temp.AddGoal(goal_1_3)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
    SM.SetIncludeProbability('HMS Spartan', 1.000000)
    SM.AddRandomBox('HMS Spartan', -13.1409, -12.7926, 62.2289, 62.3649)
    SM.AddRandomBox('HMS Spartan', -12.9717, -12.9317, 62.2864, 62.3264)
    SM.SetIncludeProbability('K-239 Karp', 1.000000)
    SM.AddRandomBox('K-239 Karp', -16.5736, -14.1527, 61.5195, 62.5440)
    SM.SetIncludeProbability('K-503', 0.500000)
    SM.AddRandomBox('K-503', -15.8982, -12.6471, 62.5479, 63.1335)
