# Created on 01/09/15 06:57:31
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Harrier Rules\n\nA scenario for Global Conflicts Blue\nCold War Battleset\n\nHarrier Rules is a Cold War scenario putting the Bristish \nNaval Aviation against an Soviet outpost in Norway.\n\nYou are to fight your way through heavy resistance and then to \ndestroy the hostile beachhead at Orland.\n\nThe Harrier is your primary asset.\n\nThis scenario is dedicated to naval wargamer Roberto Yeager, the \nultimate Harrier fan. \n\n\n""")
    SM.SetScenarioName("""Harrier Rules""")
    SM.CreateAlliance(1, 'UK')
    SM.SetAllianceDefaultCountry(1, 'UK')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 0)
    SM.CreateAlliance(3, 'Sweden')
    SM.SetAllianceDefaultCountry(3, 'Sweden')
    SM.SetAlliancePlayable(3, 1)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(1)

    SM.SetDateTime(1985,6,15,4,0,0)
    SM.SetStartTheater(-1.383335, 55.883339) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """TASKING ORDERS FOR CMDR BRITISH OPERATIONS\n\nINTELLIGENCE\n\nThe Soviets have taken Orland AB. This is a major setback for Nato and \ncannot be tolerated. \n\nMISSION\n\nYou are to destroy all hostile facilities at Orland as soon as possible. We \ncannot afford to lose time since the Soviets bring in more ressources by \nthe day. \n\nEXECUTION\n\nFirst, get a clear picture about what is going on there. Use your AEW \nbirds to the utmost.\n\nThen plough way for your carrier battle group.\n\nPrepare you air strikes carefully. Destroy as many land facilities as \npossible.\n\nThere are at least two Russian LSTs close to the coast. You must find \nand sink them.\n\nYou must not lose one of your carriers.\n\nTime to fulfill your mission: 24 hours\n\nCOMMAND AND SIGNAL\n\nHMS Invincible\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """This side is not human playable.\n""")

    ####################
    SM.SetSimpleBriefing(3, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "RAF Kinloss"
    unit.SetPosition(-3.304821, 57.368603, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("RAF Kinloss", 'Fuel', 1003980)
    SM.AddToUnitMagazine("RAF Kinloss", '27mm BK27 27x145mm', 4562)
    SM.AddToUnitMagazine("RAF Kinloss", '300 gallon tank', 5)
    SM.AddToUnitMagazine("RAF Kinloss", '330 gallon wing tank', 32)
    SM.AddToUnitMagazine("RAF Kinloss", 'AGM-45B', 106)
    SM.AddToUnitMagazine("RAF Kinloss", 'AGM-78D', 20)
    SM.AddToUnitMagazine("RAF Kinloss", 'AGM-88A', 34)
    SM.AddToUnitMagazine("RAF Kinloss", 'AIM-9L', 111)
    SM.AddToUnitMagazine("RAF Kinloss", 'AIM-9M', 423)
    SM.AddToUnitMagazine("RAF Kinloss", 'Chaff-1', 14142)
    SM.AddToUnitMagazine("RAF Kinloss", 'Flare-1', 14142)
    SM.AddToUnitMagazine("RAF Kinloss", 'Skyflash', 831)
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
    BB.Write('MagTonnage', '25')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "Alt+": 0, "Speed+": 0, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 0, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 0, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {}}')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'E-3C', 'Sentry-2', 2)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Sentry-2', '')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'EA-6B', 'Flash-2', 2)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Flash-2', '2 AGM-45A;2 AGM-45A;1 Mk-84;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'KC-767A', 'Milk-7', 2)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Milk-7', '')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'KC-767A', 'Milk-8', 2)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Milk-8', '')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'Tornado F.Mk.3', 'Arrow-9', 2)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Arrow-9', '2 AIM-9L;2 330 gallon wing tank;4 Skyflash;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'Tornado F.Mk.3', 'Arrow-10', 2)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Arrow-10', '2 AIM-9L;2 330 gallon wing tank;4 Skyflash;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'Tornado F.Mk.3', 'Arrow-11', 2)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Arrow-11', '2 AIM-9L;2 330 gallon wing tank;4 Skyflash;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'Tornado F.Mk.3', 'Arrow-12', 2)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Arrow-12', '2 AIM-9L;2 330 gallon wing tank;4 Skyflash;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'Tornado F.Mk.3', 'Arrow-13', 1)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Arrow-13', '2 AIM-9L;2 330 gallon wing tank;4 Skyflash;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'Tornado F.Mk.3', 'Arrow-14', 1)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Arrow-14', '2 AIM-9L;2 330 gallon wing tank;4 Skyflash;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'Tornado F.Mk.3', 'Arrow-15', 1)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Arrow-15', '2 AIM-9L;2 330 gallon wing tank;4 Skyflash;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('RAF Kinloss', 'Tornado F.Mk.3', 'Arrow-16', 1)
    SM.SetFlightDeckUnitLoadout('RAF Kinloss', 'Arrow-16', '2 AIM-9L;2 330 gallon wing tank;4 Skyflash;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Kobben'
    unit.unitName = "HNoMS Skolpen"
    unit.SetPosition(9.104529, 63.789225, -100.0)
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
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Type-612 Torpedo', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HNoMS Skolpen", 'Type-612 Torpedo', 12)
    UI.SetSensorState(3, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Swiftsure SSN'
    unit.unitName = "HMS Splendid"
    unit.SetPosition(9.264613, 63.932866, -100.0)
    unit.heading = 90.00
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
    SM.AddToUnitMagazine("HMS Splendid", 'mk-24 Tigerfish', 20)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oberon SS'
    unit.unitName = "HMS Otus"
    unit.SetPosition(8.280501, 63.756280, -50.0)
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
    SM.AddToUnitMagazine("HMS Otus", 'mk-24 Tigerfish', 13)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Lynx HAS.Mk.2'
    unit.unitName = "Type 22 B1 Lynx 102"
    unit.SetPosition(6.853779, 63.869270, 510.2)
    unit.heading = 92.36
    unit.speed = 100.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Stingray', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AS 12', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.123959, 1.114610, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.126528, 1.113069, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.125661, 1.111175, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'HMS Battleaxe')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'CV (R05/6/7) Invincible'
    unit.unitName = "HMS Invincible"
    unit.SetPosition(6.783133, 63.746887, 0.0)
    unit.heading = 90.00
    unit.speed = 8.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Sea Dart Mod0', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm PGU-14/B API', 79)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm PGU-14/B API', 79)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm PGU-14/B API', 79)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Invincible", 'Fuel', 2000000)
    SM.AddToUnitMagazine("HMS Invincible", 'Sea Dart Mod0', 40)
    SM.AddToUnitMagazine("HMS Invincible", '30mm PGU-13/B HE-I', 578)
    SM.AddToUnitMagazine("HMS Invincible", 'AIM-9L', 284)
    SM.AddToUnitMagazine("HMS Invincible", '68mm SNEB Rockets', 13500)
    SM.AddToUnitMagazine("HMS Invincible", 'Mk-83', 1520)
    SM.AddToUnitMagazine("HMS Invincible", 'Mk-82', 2660)
    SM.AddToUnitMagazine("HMS Invincible", 'Mk-81', 2660)
    SM.AddToUnitMagazine("HMS Invincible", 'GBU-1/B', 300)
    SM.AddToUnitMagazine("HMS Invincible", 'GBU-12/B', 440)
    SM.AddToUnitMagazine("HMS Invincible", 'GBU-16/B', 300)
    SM.AddToUnitMagazine("HMS Invincible", 'BAe Sea Eagle', 160)
    SM.AddToUnitMagazine("HMS Invincible", '100 gallon wing tank', 64)
    SM.AddToUnitMagazine("HMS Invincible", '190 gallon wing tank', 64)
    SM.AddToUnitMagazine("HMS Invincible", '300 gallon wing tank', 64)
    SM.AddToUnitMagazine("HMS Invincible", 'Chaff-1', 10560)
    SM.AddToUnitMagazine("HMS Invincible", 'Flare-1', 10560)
    SM.AddToUnitMagazine("HMS Invincible", 'Stingray', 600)
    SM.AddToUnitMagazine("HMS Invincible", 'DICASS (80) Sonobuoy', 2100)
    SM.AddToUnitMagazine("HMS Invincible", 'LOFAR (80) Sonobuoy', 2100)
    SM.AddToUnitMagazine("HMS Invincible", 'DIFAR (80) Sonobuoy', 6100)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.133460, 1.112672, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.141967, 1.114337, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.150557, 1.116489, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.153687, 1.115586, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.160107, 1.112115, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Hornet-3', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hornet-3', '2 AIM-9L;2 BAe Sea Eagle;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Hornet-4', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hornet-4', '2 AIM-9L;2 BAe Sea Eagle;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Hornet-5', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hornet-5', '2 AIM-9L;2 100 gallon wing tank;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Hornet-6', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hornet-6', '2 AIM-9L;2 100 gallon wing tank;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Hornet-7', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hornet-7', '2 AIM-9L;2 100 gallon wing tank;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea Harrier FRS.Mk.1 (85)', 'Hornet-8', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hornet-8', '2 AIM-9L;2 100 gallon wing tank;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Harrier GR.Mk.3 (82)', 'Hammer-1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hammer-1', '36 68mm SNEB Rockets;4 GBU-16/B;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Harrier GR.Mk.3 (82)', 'Hammer-2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hammer-2', '36 68mm SNEB Rockets;4 GBU-16/B;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Harrier GR.Mk.3 (82)', 'Hammer-3', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hammer-3', '36 68mm SNEB Rockets;4 GBU-16/B;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Harrier GR.Mk.3 (82)', 'Hammer-4', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hammer-4', '36 68mm SNEB Rockets;4 GBU-16/B;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Harrier GR.Mk.3 (82)', 'Hammer-5', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hammer-5', '36 68mm SNEB Rockets;36 68mm SNEB Rockets;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Harrier GR.Mk.3 (82)', 'Hammer-6', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hammer-6', '36 68mm SNEB Rockets;36 68mm SNEB Rockets;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Harrier GR.Mk.3 (82)', 'Hammer-7', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hammer-7', '36 68mm SNEB Rockets;36 68mm SNEB Rockets;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Harrier GR.Mk.3 (82)', 'Hammer-8', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Hammer-8', '36 68mm SNEB Rockets;36 68mm SNEB Rockets;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Shark Hunter-1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Shark Hunter-1', '2 Stingray;2 Stingray;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Shark Hunter-2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Shark Hunter-2', '2 Stingray;2 Stingray;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Shark Hunter-3', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Shark Hunter-3', '2 Stingray;2 Stingray;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King HAS.Mk.2', 'Shark Hunter-4', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Shark Hunter-4', '2 Stingray;2 Stingray;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King AEW.Mk.2A', 'Guard-1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Guard-1', '')
    
    SM.AddUnitToFlightDeck('HMS Invincible', 'Sea King AEW.Mk.2A', 'Guard-2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Invincible', 'Guard-2', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'EA-6B'
    unit.unitName = "Flash-1"
    unit.SetPosition(9.206000, 61.878414, 10.0)
    unit.heading = 90.00
    unit.speed = 566.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AGM-88A', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AGM-45A', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-84', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
    UI.SetSensorState(2, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'RAF Kinloss')
    UI.SetThrottle(2.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'E-3C'
    unit.unitName = "Sentry-1"
    unit.SetPosition(-0.259493, 59.053044, 10000.0)
    unit.heading = 90.00
    unit.speed = 461.0
    unit.cost = 270000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'RAF Kinloss')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'KC-767A'
    unit.unitName = "Milk-5"
    unit.SetPosition(2.567195, 60.708259, 10000.0)
    unit.heading = 90.00
    unit.speed = 495.0
    unit.cost = 175000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'RAF Kinloss')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'KC-767A'
    unit.unitName = "Milk-6"
    unit.SetPosition(1.537704, 63.147401, 10000.0)
    unit.heading = 90.00
    unit.speed = 495.0
    unit.cost = 175000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'RAF Kinloss')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tornado F.Mk.3'
    unit.unitName = "Escort 1"
    unit.SetPosition(0.271525, 59.640038, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    unit.cost = 15000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AIM-9L', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '330 gallon wing tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Skyflash', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '27mm BK27 27x145mm', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 45)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 45)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'RAF Kinloss')
    UI.SetThrottle(0.298478)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tornado F.Mk.3'
    unit.unitName = "Escort 3"
    unit.SetPosition(2.614120, 63.577059, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    unit.cost = 15000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AIM-9L', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '330 gallon wing tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Skyflash', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '27mm BK27 27x145mm', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 45)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 45)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'RAF Kinloss')
    UI.SetThrottle(0.521962)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Sea Harrier FRS.Mk.1 (85)'
    unit.unitName = "Hornet 1"
    unit.SetPosition(7.160540, 63.757540, 4000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    unit.cost = 15000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AIM-9L', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'BAe Sea Eagle', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-83', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.128332, 1.114944, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.134191, 1.112657, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.127289, 1.110330, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.692308)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Sea Harrier FRS.Mk.1 (85)'
    unit.unitName = "Hornet 2"
    UI = SM.GetUnitInterface('Hornet 1')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0138
    lat_deg = 57.296*leader_track.Lat + 0.0525
    unit.SetPosition(lon_deg, lat_deg, 50.0)
    unit.heading = 90.00
    unit.speed = 200.0
    unit.cost = 15000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AIM-9L', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'BAe Sea Eagle', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-83', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Hornet 1')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(6.071, 0.500, -1.689, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    UI.SetThrottle(0.275427)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Knox FFG'
    unit.unitName = "USS Donald B. Beary"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1648
    lat_deg = 57.296*leader_track.Lat + 0.0363
    unit.SetPosition(lon_deg, lat_deg, 0.0)
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
    SM.AddToUnitMagazine("USS Donald B. Beary", 'Fuel', 21698)
    SM.AddToUnitMagazine("USS Donald B. Beary", 'Mk-46 Mod5', 18)
    SM.AddToUnitMagazine("USS Donald B. Beary", 'DICASS (80) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Donald B. Beary", 'LOFAR (80) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Donald B. Beary", 'DIFAR (80) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS Donald B. Beary", '20mm Mark 149-4', 485)
    SM.AddToUnitMagazine("USS Donald B. Beary", '127mm mk 41 HC', 340)
    SM.AddToUnitMagazine("USS Donald B. Beary", '127mm mk 41 AAC', 120)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(8.886, 1.761, -0.449, 0.165)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Donald B. Beary', 'SH-2F', 'Knox Seasprite 1', 2)
    SM.SetFlightDeckUnitLoadout('USS Donald B. Beary', 'Knox Seasprite 1', '2 Mk-46 Mod5;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 22 FF Batch 1'
    unit.unitName = "HMS Battleaxe"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1412
    lat_deg = 57.296*leader_track.Lat + 0.0692
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 125000000.0
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
    SM.AddToUnitMagazine("HMS Battleaxe", 'Fuel', 28314)
    SM.AddToUnitMagazine("HMS Battleaxe", 'Stingray', 29)
    SM.AddToUnitMagazine("HMS Battleaxe", 'Sea Skua', 16)
    SM.AddToUnitMagazine("HMS Battleaxe", 'LOFAR (80) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Battleaxe", 'DICASS (80) Sonobuoy', 404)
    SM.AddToUnitMagazine("HMS Battleaxe", 'DIFAR (80) Sonobuoy', 1218)
    SM.AddToUnitMagazine("HMS Battleaxe", 'AS 12', 8)
    SM.AddToUnitMagazine("HMS Battleaxe", 'DICASS (100) Sonobuoy', 48)
    SM.AddToUnitMagazine("HMS Battleaxe", 'Sea Wolf', 40)
    SM.AddToUnitMagazine("HMS Battleaxe", '30mm/75 GCM-AO3-2 APDS', 1660)
    SM.AddToUnitMagazine("HMS Battleaxe", '20mm/85  GAM-B01 HE-I', 500)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(10.197, 1.137, -2.324, 0.189)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Battleaxe', 'Lynx HAS.Mk.2', 'Type 22 B1 Lynx 101', 1)
    SM.SetFlightDeckUnitLoadout('HMS Battleaxe', 'Type 22 B1 Lynx 101', '2 AS 12;2 AS 12;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 22 FF Batch 1'
    unit.unitName = "HMS Brilliant"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0157
    lat_deg = 57.296*leader_track.Lat + -0.0997
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 125000000.0
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
    SM.AddToUnitMagazine("HMS Brilliant", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Brilliant", 'Stingray', 25)
    SM.AddToUnitMagazine("HMS Brilliant", 'Sea Skua', 16)
    SM.AddToUnitMagazine("HMS Brilliant", 'LOFAR (80) Sonobuoy', 154)
    SM.AddToUnitMagazine("HMS Brilliant", 'DICASS (80) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Brilliant", 'DIFAR (80) Sonobuoy', 609)
    SM.AddToUnitMagazine("HMS Brilliant", 'AS 12', 8)
    SM.AddToUnitMagazine("HMS Brilliant", 'Sea Wolf', 40)
    SM.AddToUnitMagazine("HMS Brilliant", '30mm/75 GCM-AO3-2 APDS', 1660)
    SM.AddToUnitMagazine("HMS Brilliant", '20mm/85  GAM-B01 HE-I', 500)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(10.817, 0.788, 1.515, 0.083)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Brilliant', 'Lynx HAS.Mk.2', 'Type 22 B1 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Brilliant', 'Type 22 B1 Lynx 1', '1 Stingray;1 Stingray;')
    
    SM.AddUnitToFlightDeck('HMS Brilliant', 'Lynx HAS.Mk.2', 'Type 22 B1 Lynx 2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Brilliant', 'Type 22 B1 Lynx 2', '1 Stingray;1 Stingray;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'CV (R05/6/7) Invincible'
    unit.unitName = "HMS Illustrious"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0457
    lat_deg = 57.296*leader_track.Lat + 0.0423
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Sea Dart Mod0', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm PGU-14/B API', 79)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm PGU-14/B API', 79)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm PGU-14/B API', 79)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Illustrious", 'Fuel', 2000000)
    SM.AddToUnitMagazine("HMS Illustrious", 'Sea Dart Mod0', 40)
    SM.AddToUnitMagazine("HMS Illustrious", '30mm PGU-13/B HE-I', 578)
    SM.AddToUnitMagazine("HMS Illustrious", 'AIM-9L', 284)
    SM.AddToUnitMagazine("HMS Illustrious", '68mm SNEB Rockets', 13500)
    SM.AddToUnitMagazine("HMS Illustrious", 'Mk-83', 1520)
    SM.AddToUnitMagazine("HMS Illustrious", 'Mk-82', 2660)
    SM.AddToUnitMagazine("HMS Illustrious", 'Mk-81', 2660)
    SM.AddToUnitMagazine("HMS Illustrious", 'GBU-1/B', 300)
    SM.AddToUnitMagazine("HMS Illustrious", 'GBU-12/B', 440)
    SM.AddToUnitMagazine("HMS Illustrious", 'GBU-16/B', 300)
    SM.AddToUnitMagazine("HMS Illustrious", 'BAe Sea Eagle', 160)
    SM.AddToUnitMagazine("HMS Illustrious", '100 gallon wing tank', 64)
    SM.AddToUnitMagazine("HMS Illustrious", '190 gallon wing tank', 64)
    SM.AddToUnitMagazine("HMS Illustrious", '300 gallon wing tank', 64)
    SM.AddToUnitMagazine("HMS Illustrious", 'Chaff-1', 10560)
    SM.AddToUnitMagazine("HMS Illustrious", 'Flare-1', 10560)
    SM.AddToUnitMagazine("HMS Illustrious", 'Stingray', 600)
    SM.AddToUnitMagazine("HMS Illustrious", 'DICASS (80) Sonobuoy', 2100)
    SM.AddToUnitMagazine("HMS Illustrious", 'LOFAR (80) Sonobuoy', 2100)
    SM.AddToUnitMagazine("HMS Illustrious", 'DIFAR (80) Sonobuoy', 6100)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(5.081, 0.500, -1.118, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea Harrier FRS.Mk.1 (85)', 'Dart-1', 2)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Dart-1', '2 AIM-9L;2 BAe Sea Eagle;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea Harrier FRS.Mk.1 (85)', 'Dart-2', 2)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Dart-2', '2 AIM-9L;2 BAe Sea Eagle;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea Harrier FRS.Mk.1 (85)', 'Dart-3', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Dart-3', '2 AIM-9L;2 BAe Sea Eagle;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea Harrier FRS.Mk.1 (85)', 'Dart-4', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Dart-4', '2 AIM-9L;2 BAe Sea Eagle;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea Harrier FRS.Mk.1 (85)', 'Dart-5', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Dart-5', '2 AIM-9L;2 100 gallon wing tank;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea Harrier FRS.Mk.1 (85)', 'Dart-6', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Dart-6', '2 AIM-9L;2 100 gallon wing tank;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea Harrier FRS.Mk.1 (85)', 'Dart-7', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Dart-7', '2 AIM-9L;2 100 gallon wing tank;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea Harrier FRS.Mk.1 (85)', 'Dart-8', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Dart-8', '2 AIM-9L;2 100 gallon wing tank;1 Mk-83;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Harrier GR.Mk.3 (82)', 'Ambush-1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Ambush-1', '36 68mm SNEB Rockets;4 GBU-16/B;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Harrier GR.Mk.3 (82)', 'Ambush-2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Ambush-2', '36 68mm SNEB Rockets;4 GBU-16/B;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Harrier GR.Mk.3 (82)', 'Ambush-3', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Ambush-3', '36 68mm SNEB Rockets;4 GBU-16/B;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Harrier GR.Mk.3 (82)', 'Ambush-4', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Ambush-4', '36 68mm SNEB Rockets;4 GBU-16/B;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Harrier GR.Mk.3 (82)', 'Ambush-5', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Ambush-5', '36 68mm SNEB Rockets;36 68mm SNEB Rockets;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Harrier GR.Mk.3 (82)', 'Ambush-6', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Ambush-6', '36 68mm SNEB Rockets;36 68mm SNEB Rockets;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Harrier GR.Mk.3 (82)', 'Ambush-7', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Ambush-7', '36 68mm SNEB Rockets;36 68mm SNEB Rockets;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Harrier GR.Mk.3 (82)', 'Ambush-8', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Ambush-8', '36 68mm SNEB Rockets;36 68mm SNEB Rockets;1 GBU-12/B;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea King HAS.Mk.2', 'Lion-1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Lion-1', '2 Stingray;2 Stingray;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea King HAS.Mk.2', 'Lion-2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Lion-2', '2 Stingray;2 Stingray;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea King HAS.Mk.2', 'Lion-3', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Lion-3', '2 Stingray;2 Stingray;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea King HAS.Mk.2', 'Lion-4', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Lion-4', '2 Stingray;2 Stingray;10 DICASS (80) Sonobuoy;10 LOFAR (80) Sonobuoy;30 DIFAR (80) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea King AEW.Mk.2A', 'Spy-1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Spy-1', '')
    
    SM.AddUnitToFlightDeck('HMS Illustrious', 'Sea King AEW.Mk.2A', 'Spy-2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Illustrious', 'Spy-2', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 42 DDG Batch 1'
    unit.unitName = "HMS Glasgow"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1893
    lat_deg = 57.296*leader_track.Lat + -0.0519
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 1, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Sea Dart Mod0', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, '114mm N4A1 HE', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Glasgow", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Glasgow", 'Stingray', 20)
    SM.AddToUnitMagazine("HMS Glasgow", 'Sea Skua', 8)
    SM.AddToUnitMagazine("HMS Glasgow", 'LOFAR (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Glasgow", 'DICASS (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Glasgow", 'DIFAR (80) Sonobuoy', 405)
    SM.AddToUnitMagazine("HMS Glasgow", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Glasgow", '20mm Mark 149-4', 970)
    SM.AddToUnitMagazine("HMS Glasgow", 'Sea Dart Mod0', 22)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(9.638, 3.119, 0.595, 0.304)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Glasgow', 'Lynx HAS.Mk.2', 'Type 42 B1 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Glasgow', 'Type 42 B1 Lynx 1', '2 AS 12;2 AS 12;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 42 DDG Batch 1'
    unit.unitName = "HMS Newcastle"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1753
    lat_deg = 57.296*leader_track.Lat + 0.0814
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 1, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Sea Dart Mod0', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, '114mm N4A1 HE', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Newcastle", 'Fuel', 28600)
    SM.AddToUnitMagazine("HMS Newcastle", 'Stingray', 20)
    SM.AddToUnitMagazine("HMS Newcastle", 'Sea Skua', 8)
    SM.AddToUnitMagazine("HMS Newcastle", 'LOFAR (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Newcastle", 'DICASS (80) Sonobuoy', 270)
    SM.AddToUnitMagazine("HMS Newcastle", 'DIFAR (80) Sonobuoy', 810)
    SM.AddToUnitMagazine("HMS Newcastle", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Newcastle", '20mm Mark 149-4', 970)
    SM.AddToUnitMagazine("HMS Newcastle", 'Sea Dart Mod0', 22)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(12.174, 2.469, -0.809, 0.228)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Newcastle', 'Lynx HAS.Mk.2', 'Type 42 B1 Lynx 101', 1)
    SM.SetFlightDeckUnitLoadout('HMS Newcastle', 'Type 42 B1 Lynx 101', '2 AS 12;2 AS 12;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 42 DDG Batch 1'
    unit.unitName = "HMS Birmingham"
    UI = SM.GetUnitInterface('HMS Invincible')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0920
    lat_deg = 57.296*leader_track.Lat + 0.0024
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 1, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Sea Dart Mod0', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, '114mm N4A1 HE', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Birmingham", 'Fuel', 24368)
    SM.AddToUnitMagazine("HMS Birmingham", 'Stingray', 20)
    SM.AddToUnitMagazine("HMS Birmingham", 'Sea Skua', 8)
    SM.AddToUnitMagazine("HMS Birmingham", 'LOFAR (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Birmingham", 'DICASS (80) Sonobuoy', 405)
    SM.AddToUnitMagazine("HMS Birmingham", 'DIFAR (80) Sonobuoy', 1215)
    SM.AddToUnitMagazine("HMS Birmingham", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Birmingham", '20mm Mark 149-4', 970)
    SM.AddToUnitMagazine("HMS Birmingham", 'Sea Dart Mod0', 22)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Invincible')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(4.818, 0.771, -3.130, 0.307)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Birmingham', 'Lynx HAS.Mk.2', 'Type 42 B1 Lynx 201', 1)
    SM.SetFlightDeckUnitLoadout('HMS Birmingham', 'Type 42 B1 Lynx 201', '2 AS 12;2 AS 12;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tornado F.Mk.3'
    unit.unitName = "Escort 2"
    UI = SM.GetUnitInterface('Escort 1')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.8394
    lat_deg = 57.296*leader_track.Lat + -0.3255
    unit.SetPosition(lon_deg, lat_deg, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    unit.cost = 15000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AIM-9L', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '330 gallon wing tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Skyflash', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '27mm BK27 27x145mm', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 45)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 45)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'RAF Kinloss')
    leader_id = UI.LookupFriendlyId('Escort 1')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(59.628, 12.808, 0.629, 0.307)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    UI.SetThrottle(0.298136)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tornado F.Mk.3'
    unit.unitName = "Escort 4"
    UI = SM.GetUnitInterface('Escort 3')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1499
    lat_deg = 57.296*leader_track.Lat + -0.4568
    unit.SetPosition(lon_deg, lat_deg, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    unit.cost = 15000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AIM-9L', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '330 gallon wing tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Skyflash', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '27mm BK27 27x145mm', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 45)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Chaff-1', 45)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'RAF Kinloss')
    leader_id = UI.LookupFriendlyId('Escort 3')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(47.447, 15.991, 1.407, 0.203)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    UI.SetThrottle(0.521962)
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'A-50'
    unit.unitName = "Albatross"
    unit.SetPosition(9.232928, 63.374747, 9726.0)
    unit.heading = 90.00
    unit.speed = 200.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.162131, 1.106714, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.160960, 1.105841, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.161679, 1.105163, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-21F'
    unit.unitName = "Archer 2"
    unit.SetPosition(9.110029, 63.353090, 9932.5)
    unit.heading = 90.00
    unit.speed = 270.0
    unit.cost = 1800000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-100', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PTB-400', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm NR-30 HEI x2', 60)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-100', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.160922, 1.107453, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.157359, 1.106201, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.160023, 1.104692, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.181742)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammunition Bunker"
    unit.SetPosition(9.401149, 63.375607, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 11351 Nerey'
    unit.unitName = "Menzhinskiy"
    unit.SetPosition(9.299105, 63.804065, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RPK-6 Vodopod', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'USET-80', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M33M', 20)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Menzhinskiy", 'Fuel', 22950)
    SM.AddToUnitMagazine("Menzhinskiy", 'AT-1', 20)
    SM.AddToUnitMagazine("Menzhinskiy", 'DICASS (75) Sonobuoy', 131)
    SM.AddToUnitMagazine("Menzhinskiy", 'LOFAR (75) Sonobuoy', 105)
    SM.AddToUnitMagazine("Menzhinskiy", 'DIFAR (75) Sonobuoy', 294)
    SM.AddToUnitMagazine("Menzhinskiy", '30mm OF-83 HE-FRAG', 4000)
    SM.AddToUnitMagazine("Menzhinskiy", '53-65M', 8)
    SM.AddToUnitMagazine("Menzhinskiy", '100mm OF-58 FRAG', 350)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.158081, 1.112562, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.162109, 1.113072, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Menzhinskiy', 'Ka-27A', 'Nerey Ka-27 101', 1)
    SM.SetFlightDeckUnitLoadout('Menzhinskiy', 'Nerey Ka-27 101', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 11351 Nerey'
    unit.unitName = "Dzernhinskiy"
    unit.SetPosition(9.147271, 63.761895, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RPK-6 Vodopod', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'SAET-60M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M33M', 20)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Dzernhinskiy", 'Fuel', 22950)
    SM.AddToUnitMagazine("Dzernhinskiy", 'AT-1', 18)
    SM.AddToUnitMagazine("Dzernhinskiy", 'DICASS (75) Sonobuoy', 105)
    SM.AddToUnitMagazine("Dzernhinskiy", 'LOFAR (75) Sonobuoy', 105)
    SM.AddToUnitMagazine("Dzernhinskiy", 'DIFAR (75) Sonobuoy', 294)
    SM.AddToUnitMagazine("Dzernhinskiy", '30mm OF-83 HE-FRAG', 4000)
    SM.AddToUnitMagazine("Dzernhinskiy", '53-65M', 8)
    SM.AddToUnitMagazine("Dzernhinskiy", '100mm OF-58 FRAG', 350)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.158081, 1.112562, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.161679, 1.113099, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Dzernhinskiy', 'Ka-27A', 'Nerey Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Dzernhinskiy', 'Nerey Ka-27 1', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 61 Kashin'
    unit.unitName = "Smetlivy"
    boxes = [[7.3684, 7.6161, 63.5729, 63.9273]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 9.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-600', 16)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-600', 16)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Kh-35', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Smetlivy", '53-65M', 30)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.131099, 1.114018, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.137476, 1.114589, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.145330, 1.116032, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.151036, 1.116670, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.153788, 1.115697, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.155936, 1.114186, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.160568, 1.112038, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.161575, 1.111904, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671 Yorzh'
    unit.unitName = "K-38"
    boxes = [[9.1500, 9.2916, 63.7151, 63.7981]]
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
    SM.AddToUnitMagazine("K-38", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-38", '53-65M', 6)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671RTMK Shchuka'
    unit.unitName = "B-355"
    boxes = [[7.1634, 7.3485, 63.5319, 63.8851]]
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
    SM.SetUnitLauncherItem(unit.unitName, 4, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '65-76 Kit', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-355", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-355", '53-65M', 6)
    UI.SetSensorState(6, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.127528, 1.114683, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.127098, 1.111380, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641B Som'
    unit.unitName = "B-498"
    boxes = [[9.1885, 9.2507, 63.6423, 63.7272]]
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
    SM.AddToUnitMagazine("B-498", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-498", '53-65M', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.160390, 1.111676, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.162377, 1.111622, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 670 Skat'
    unit.unitName = "K-25"
    boxes = [[7.7179, 7.9801, 63.5777, 63.6980]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -100.0)
    unit.heading = 90.00
    unit.speed = 3.0
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
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.137785, 1.114226, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.138000, 1.111649, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fuel Tanks'
    unit.unitName = "Fuel Tanks"
    unit.SetPosition(9.415415, 63.348334, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZIL-157 Truck'
    unit.unitName = "ZIL-157 Truck (2)"
    unit.SetPosition(9.382470, 63.331260, 439.5)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZIL-157 Truck'
    unit.unitName = "ZIL-157 Truck (1)"
    unit.SetPosition(9.364766, 63.397780, -0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V Shilka'
    unit.unitName = "ZSU-23 (1)"
    unit.SetPosition(9.268337, 63.382540, 790.6)
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
    unit.SetPosition(9.433865, 63.343006, 790.6)
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
    unit.unitName = "ZSU-23 (4)"
    unit.SetPosition(9.393414, 63.394514, 342.2)
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
    unit.unitName = "ZSU-23 (2)"
    unit.SetPosition(9.314288, 63.344839, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Army HQ Bunker"
    unit.SetPosition(9.351645, 63.346904, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Communications Station'
    unit.unitName = "Communications  Station"
    unit.SetPosition(9.370037, 63.379963, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 775  Ropucha'
    unit.unitName = "BDK-56 Konstantin Olshanskiy"
    unit.SetPosition(9.175518, 63.610348, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 2, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 3, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M32 Strela 2', 32)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("BDK-56 Konstantin Olshanskiy", '57mm Tracer-FRAG', 2800)
    SM.AddToUnitMagazine("BDK-56 Konstantin Olshanskiy", '30mm OF-84 HE-FRAG AK-630M', 472)
    SM.AddToUnitMagazine("BDK-56 Konstantin Olshanskiy", '9M32 Strela 2', 64)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 775  Ropucha'
    unit.unitName = "BDK-45 Georgiy Pobedonosets"
    unit.SetPosition(9.223704, 63.610634, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 2, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 3, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M32 Strela 2', 32)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("BDK-45 Georgiy Pobedonosets", '57mm Tracer-FRAG', 2800)
    SM.AddToUnitMagazine("BDK-45 Georgiy Pobedonosets", '30mm OF-84 HE-FRAG AK-630M', 472)
    SM.AddToUnitMagazine("BDK-45 Georgiy Pobedonosets", '9M32 Strela 2', 64)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "AF Orland"
    unit.SetPosition(9.387226, 63.353605, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("AF Orland", 'Fuel', 1000000)
    SM.AddToUnitMagazine("AF Orland", 'FAB-500', 644)
    SM.AddToUnitMagazine("AF Orland", 'Flare-1', 200)
    SM.AddToUnitMagazine("AF Orland", 'KAB-500L', 176)
    SM.AddToUnitMagazine("AF Orland", 'Kh-29T', 204)
    SM.AddToUnitMagazine("AF Orland", 'Kh-59MK', 152)
    SM.AddToUnitMagazine("AF Orland", 'R-60', 476)
    SM.AddToUnitMagazine("AF Orland", 'TN-1000', 100)
    SM.AddToUnitMagazine("AF Orland", 'VTT-1', 200)
    SM.AddToUnitMagazine("AF Orland", 'Yu-7', 100)
    SM.AddToUnitMagazine("AF Orland", 'AT-1', 400)
    SM.AddToUnitMagazine("AF Orland", '23mm AM-23', 200)
    SM.AddToUnitMagazine("AF Orland", '3000 liter tank', 248)
    SM.AddToUnitMagazine("AF Orland", 'Chaff-1', 200)
    SM.AddToUnitMagazine("AF Orland", 'DICASS (75) Sonobuoy', 150)
    SM.AddToUnitMagazine("AF Orland", 'LOFAR (75) Sonobuoy', 150)
    SM.AddToUnitMagazine("AF Orland", 'DIFAR (75) Sonobuoy', 450)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('AF Orland', 'MiG-21F', 'Fishbed-1', 2)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Fishbed-1', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'MiG-21F', 'Fishbed-2', 2)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Fishbed-2', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'MiG-21F', 'Fishbed-3', 2)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Fishbed-3', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'MiG-21F', 'Fishbed-4', 2)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Fishbed-4', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'MiG-21F', 'Fishbed-5', 2)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Fishbed-5', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'MiG-21F', 'Fishbed-6', 2)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Fishbed-6', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'MiG-21F', 'Fishbed-7', 2)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Fishbed-7', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'MiG-21F', 'Fishbed-8', 2)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Fishbed-8', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'MiG-21F', 'Fishbed-9', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Fishbed-9', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'MiG-21F', 'Fishbed-10', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Fishbed-10', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'A-50', 'Eye-1', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Eye-1', '')
    
    SM.AddUnitToFlightDeck('AF Orland', 'A-50', 'Eye-2', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Eye-2', '')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Ka-27A', 'Hunter-5', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Hunter-5', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Ka-27A', 'Hunter-6', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Hunter-6', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Ka-27A', 'Hunter-7', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Hunter-7', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Ka-27A', 'Hunter-8', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Hunter-8', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Ka-27A', 'Hunter-9', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Hunter-9', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Ka-27A', 'Hunter-10', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Hunter-10', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Ka-27A', 'Hunter-11', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Hunter-11', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Ka-27A', 'Hunter-12', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Hunter-12', '5 DICASS (75) Sonobuoy;5 LOFAR (75) Sonobuoy;14 DIFAR (75) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-1', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-1', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-2', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-2', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-3', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-3', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-4', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-4', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-5', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-5', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-6', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-6', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-7', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-7', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-8', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-8', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-9', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-9', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-10', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-10', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-11', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-11', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-12', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-12', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-13', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-13', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-14', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-14', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-15', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-15', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-16', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-16', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-17', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-17', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-18', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-18', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-19', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-19', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-20', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-20', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-21', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-21', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-22', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-22', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-23', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-23', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AF Orland', 'Su-24M', 'Thunder-24', 1)
    SM.SetFlightDeckUnitLoadout('AF Orland', 'Thunder-24', '2 R-60;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Eye-1')
    FP.AddAircraftToMission(mission_id, 'Eye-2')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.1611244,1.1077020,0.1580731,1.1047943,0.1600506,1.1047943,0.1622030,1.1075993,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1648380, 1.1067290, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1621050, 1.1070160, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Fishbed-9')
    FP.AddAircraftToMission(mission_id, 'Fishbed-10')
    FP.AddAircraftToMission(mission_id, 'Fishbed-1')
    FP.AddAircraftToMission(mission_id, 'Fishbed-2')
    FP.AddAircraftToMission(mission_id, 'Fishbed-3')
    FP.AddAircraftToMission(mission_id, 'Fishbed-4')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.1606325,1.1091321,0.1537087,1.1050743,0.1562358,1.1037902,0.1628309,1.1089883,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1648380, 1.1067290, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1598350, 1.1062820, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Thunder-1')
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
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 6)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.1343591,1.1104294,0.1319514,1.1158668,0.1210366,1.1128170,0.1289418,1.1101084,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1648380, 1.1067290, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1336370, 1.1131380, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Fishbed-5')
    FP.AddAircraftToMission(mission_id, 'Fishbed-6')
    FP.AddAircraftToMission(mission_id, 'Fishbed-7')
    FP.AddAircraftToMission(mission_id, 'Fishbed-8')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.1309884,1.1099077,0.1264940,1.1100683,0.1269756,1.1154454,0.1317107,1.1152648,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1648380, 1.1067290, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1319510, 1.1129370, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Thunder-13')
    FP.AddAircraftToMission(mission_id, 'Thunder-14')
    FP.AddAircraftToMission(mission_id, 'Thunder-15')
    FP.AddAircraftToMission(mission_id, 'Thunder-16')
    FP.AddAircraftToMission(mission_id, 'Thunder-17')
    FP.AddAircraftToMission(mission_id, 'Thunder-18')
    FP.AddAircraftToMission(mission_id, 'Thunder-19')
    FP.AddAircraftToMission(mission_id, 'Thunder-20')
    FP.AddAircraftToMission(mission_id, 'Thunder-21')
    FP.AddAircraftToMission(mission_id, 'Thunder-22')
    FP.AddAircraftToMission(mission_id, 'Thunder-23')
    FP.AddAircraftToMission(mission_id, 'Thunder-24')
    FP.SetMissionLaunchTime(mission_id, '04:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 6)
    FP.SetMissionType(mission_id, 'Standby-ASuW')
    FP.SetMissionPatrolArea(mission_id, '0.1294234,1.1159470,0.1265743,1.1104294,0.1340782,1.1094061,0.1360445,1.1154855,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1648380, 1.1067290, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1358440, 1.1136400, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Hunter-5')
    FP.AddAircraftToMission(mission_id, 'Hunter-6')
    FP.AddAircraftToMission(mission_id, 'Hunter-7')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1648380, 1.1067290, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1600930, 1.1115880, 2000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'BarrierPatrol,EngageAll,RTB')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1600930, 1.1115880, 2000.0, 300.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.1600930, 1.1115880, 2000.0, 300.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.1620930, 1.1115741, 10000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 4, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Hunter-8')
    FP.AddAircraftToMission(mission_id, 'Hunter-9')
    FP.AddAircraftToMission(mission_id, 'Hunter-10')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, 'Standby-ASW')
    FP.SetMissionPatrolArea(mission_id, '0.1555919,1.1133635,0.1616528,1.1131371,0.1615090,1.1136507,0.1546674,1.1138154,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1648380, 1.1067290, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1584070, 1.1131580, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Hunter-11')
    FP.AddAircraftToMission(mission_id, 'Hunter-12')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.1590847,1.1119459,0.1601530,1.1116172,0.1644265,1.1122643,0.1633992,1.1126444,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1648380, 1.1067290, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1622490, 1.1119050, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135 Burevestnik'
    unit.unitName = "Bezukoriznennyy"
    unit.SetPosition(8.295914, 63.803093, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
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
    SM.AddToUnitMagazine("Bezukoriznennyy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.142940, 1.115489, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.143477, 1.111756, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-125 Neva'
    unit.unitName = "S-125"
    unit.SetPosition(9.321336, 63.386493, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-600', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-600', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-600', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-600', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("S-125", 'V-600', 16)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-25'
    unit.unitName = "Kondor 1"
    unit.SetPosition(7.357580, 63.583762, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    unit.cost = 25000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'R-40R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-40R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.129136, 1.111712, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.127291, 1.114681, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.135597, 1.112133, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.136597, 1.113133, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.140255, 1.113582, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.159319, 1.107138, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.135203)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MiG-21F'
    unit.unitName = "Archer 1"
    UI = SM.GetUnitInterface('Archer 2')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0092
    lat_deg = 57.296*leader_track.Lat + -0.0323
    unit.SetPosition(lon_deg, lat_deg, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    unit.cost = 1800000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-100', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PTB-400', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm NR-30 HEI x2', 60)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-100', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Archer 2')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(3.681, 0.500, 1.679, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    UI.SetThrottle(0.195471)
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Generic submarine'
    unit.unitName = "Swedish Sub (1)"
    boxes = [[7.2044, 7.6407, 63.6023, 63.7341]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -100.0)
    unit.heading = 90.00
    unit.speed = 6.2
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MK-T1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'UGM-84C Harpoon', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Swedish Sub (1)", 'MK-T1', 15)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.127305, 1.111114, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.133485, 1.109368, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.139986, 1.109549, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.141751, 1.112739, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.136936, 1.114906, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.132321, 1.112177, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Generic submarine'
    unit.unitName = "Swedish Sub (2)"
    boxes = [[9.2051, 9.3397, 63.7493, 63.7766]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -100.0)
    unit.heading = 90.00
    unit.speed = 5.7
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MK-T1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'UGM-84C Harpoon', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Swedish Sub (2)", 'MK-T1', 16)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.157883, 1.112378, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.160732, 1.111595, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.163300, 1.111896, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.164103, 1.112598, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.161013, 1.113220, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.158324, 1.112478, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Destroyer'
    unit.unitName = "Swedish DD (1)"
    boxes = [[6.9998, 7.3096, 63.4874, 63.6180]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 11.1
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SAM-I', 10)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SSM-I', 10)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Shell-1', 100)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.119360, 1.109067, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.137217, 1.109328, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.142634, 1.112498, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.126743, 1.110411, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Destroyer'
    unit.unitName = "Swedish DD (2)"
    boxes = [[7.8394, 8.1695, 63.8516, 63.9272]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 11.1
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SAM-I', 10)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SSM-I', 10)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Shell-1', 100)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.134087, 1.115207, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.132650, 1.113659, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.145090, 1.114000, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.147818, 1.117973, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.141197, 1.115726, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Destroyer'
    unit.unitName = "Swedish DD (3)"
    boxes = [[9.0396, 9.2478, 63.8746, 63.9203]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 8.1
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SAM-I', 10)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SSM-I', 10)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Shell-1', 100)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.156004, 1.114522, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.158452, 1.113659, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.163027, 1.114361, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.161221, 1.115124, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('HMS Invincible')
    goal_temp.SetQuantity(1)
    goal_0_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('HMS Illustrious')
    goal_temp.SetQuantity(1)
    goal_0_1 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('BDK-56 Konstantin Olshanskiy')
    goal_temp.SetQuantity(1)
    goal_0_2 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('BDK-45 Georgiy Pobedonosets')
    goal_temp.SetQuantity(1)
    goal_0_3 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('ZSU-23 (1)')
    goal_temp.AddTarget('S-125')
    goal_temp.AddTarget('AF Orland')
    goal_temp.AddTarget('Communications  Station')
    goal_temp.AddTarget('Army HQ Bunker')
    goal_temp.AddTarget('ZSU-23 (2)')
    goal_temp.AddTarget('ZSU-23 (4)')
    goal_temp.AddTarget('ZSU-23 (3)')
    goal_temp.AddTarget('ZIL-157 Truck (1)')
    goal_temp.AddTarget('ZIL-157 Truck (2)')
    goal_temp.AddTarget('Fuel Tanks')
    goal_temp.AddTarget('Ammunition Bunker')
    goal_temp.SetQuantity(8)
    goal_0_4 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(5999940.0)
    goal_temp.SetFailTimeout(86400.0)
    goal_0_5 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_0_0)
    goal_temp.AddGoal(goal_0_1)
    goal_temp.AddGoal(goal_0_2)
    goal_temp.AddGoal(goal_0_3)
    goal_temp.AddGoal(goal_0_4)
    goal_temp.AddGoal(goal_0_5)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(86400.0)
    goal_temp.SetFailTimeout(5999940.0)
    goal_1_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('ZSU-23 (1)')
    goal_temp.AddTarget('S-125')
    goal_temp.AddTarget('AF Orland')
    goal_temp.AddTarget('Communications  Station')
    goal_temp.AddTarget('Army HQ Bunker')
    goal_temp.AddTarget('ZSU-23 (2)')
    goal_temp.AddTarget('ZSU-23 (4)')
    goal_temp.AddTarget('ZSU-23 (3)')
    goal_temp.AddTarget('ZIL-157 Truck (1)')
    goal_temp.AddTarget('ZIL-157 Truck (2)')
    goal_temp.AddTarget('Fuel Tanks')
    goal_temp.AddTarget('Ammunition Bunker')
    goal_temp.SetQuantity(5)
    goal_1_1 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('HMS Invincible')
    goal_temp.AddTarget('HMS Illustrious')
    goal_temp.SetQuantity(1)
    goal_1_2 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('BDK-56 Konstantin Olshanskiy')
    goal_temp.AddTarget('BDK-45 Georgiy Pobedonosets')
    goal_temp.SetQuantity(1)
    goal_1_3 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_1_0)
    goal_temp.AddGoal(goal_1_1)
    goal_temp.AddGoal(goal_1_2)
    goal_temp.AddGoal(goal_1_3)
    
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
    SM.SetIncludeProbability('B-355', 1.000000)
    SM.AddRandomBox('B-355', 7.1634, 7.3485, 63.5319, 63.8851)
    SM.SetIncludeProbability('B-498', 1.000000)
    SM.AddRandomBox('B-498', 9.1885, 9.2507, 63.6423, 63.7272)
    SM.SetIncludeProbability('K-25', 1.000000)
    SM.AddRandomBox('K-25', 7.7179, 7.9801, 63.5777, 63.6980)
    SM.SetIncludeProbability('K-38', 1.000000)
    SM.AddRandomBox('K-38', 9.1500, 9.2916, 63.7151, 63.7981)
    SM.SetIncludeProbability('Smetlivy', 1.000000)
    SM.AddRandomBox('Smetlivy', 7.3684, 7.6161, 63.5729, 63.9273)
    SM.SetIncludeProbability('Swedish DD (1)', 1.000000)
    SM.AddRandomBox('Swedish DD (1)', 6.9998, 7.3096, 63.4874, 63.6180)
    SM.SetIncludeProbability('Swedish DD (2)', 1.000000)
    SM.AddRandomBox('Swedish DD (2)', 7.8394, 8.1695, 63.8516, 63.9272)
    SM.SetIncludeProbability('Swedish DD (3)', 1.000000)
    SM.AddRandomBox('Swedish DD (3)', 9.0396, 9.2478, 63.8746, 63.9203)
    SM.SetIncludeProbability('Swedish Sub (1)', 1.000000)
    SM.AddRandomBox('Swedish Sub (1)', 7.2044, 7.6407, 63.6023, 63.7341)
    SM.SetIncludeProbability('Swedish Sub (2)', 1.000000)
    SM.AddRandomBox('Swedish Sub (2)', 9.2051, 9.3397, 63.7493, 63.7766)
