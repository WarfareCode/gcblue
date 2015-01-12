# Created on 11/08/14 07:48:19
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""GIUK, Part II\n\nThe Inner Circle\n\nA scenario for Global Conflicts 2.\n\nThe Inner Circle is the second scenario in a Cold War Battleset called \nGIUK. \n\nYour task is to stop a powerful Soviet Amphibious Task Force heading for \nIceland. In order to stop the invasio your subs have to break through \nthe outer escort circle where the LSTs are.\n\nThere, in the inner circle of the hostile formation, Iceland's face will be \ndecided. There is no way stopping those troops when their LSTs  come \nclose enough to the shore. \n\nGood Luck, Commander!\n\n\n\n""")
    SM.SetScenarioName("""GIUK Part 2 The Inner Circle""")
    SM.CreateAlliance(1, 'USA')
    SM.SetAllianceDefaultCountry(1, 'USA')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 0)
    SM.SetUserAlliance(1)

    SM.SetDateTime(1985,8,4,12,0,0)
    SM.SetStartTheater(-19.883335, 55.883339) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1511.807983,60.959999,1505.102417,304.800018,1501.444824,609.600037,1491.691162,914.400024,1484.985596,1219.200073,1487.119263,2362.199951,1502.664063,2743.199951,1507.235962,3962.400146,1527.657593,5181.600098,1548.079224')

    ####################
    SM.SetSimpleBriefing(1, """TASKING ORDERS FOR CMDR US OPERATIONS\n\nINTELLIGENCE\n\nWorld War  III is raging. The main battles are taking place on the central \nfront. Since it looks like a stalemate there, the Soviets try to outflank us \non several other hotspots.\n\nOne of those is Iceland. A large rock in the sea, but of extreme strategic \nvalue.\n\nThe Soviets have understood that and launched a mission to overrun the \n little defended island.\n\nA strong task force is underway, including three LSTs transporting the \nlanding troops.\n\n\nMISSION\n\nStop the invasion of Iceland.\n\n\nEXECUTION\n\nUse your Orions to locate the hostile task force. Close in with your subs. \nDo not waste torpedoes on the outer escorts. Proceed to the inner ring. \nBreak through and sink all three LSTs.\n\nBe careful, the LSTs are heavily guarded.\n\nYour last line of defence is the Norwegian sub assigned to your \ncommand. \n\nCOMMAND AND SIGNAL\n\nUSS Providence\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """TASKING ORDERS:\n\n\nNO ADDITIONAL INTELLIGENCE AVAILABLE.\n""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Kobben'
    unit.unitName = "HNoMS Kya"
    unit.SetPosition(-21.853871, 63.447227, -91.7)
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
    unit.className = 'Airstrip(USA)'
    unit.unitName = "AB Kevlavik"
    unit.SetPosition(-22.605763, 63.985466, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("AB Kevlavik", 'Fuel', 1001022)
    SM.AddToUnitMagazine("AB Kevlavik", 'Chaff-1', 10000)
    SM.AddToUnitMagazine("AB Kevlavik", 'Flare-1', 10000)
    SM.AddToUnitMagazine("AB Kevlavik", 'DICASS (80) Sonobuoy', 80)
    SM.AddToUnitMagazine("AB Kevlavik", 'LOFAR (80) Sonobuoy', 80)
    SM.AddToUnitMagazine("AB Kevlavik", 'DIFAR (80) Sonobuoy', 240)
    SM.AddToUnitMagazine("AB Kevlavik", 'Mk-46 Mod5', 60)
    SM.AddToUnitMagazine("AB Kevlavik", 'AGM-84C Harpoon', 46)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'P-3C II Orion', 'Sea Lion-1', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Sea Lion-1', '17 DICASS (80) Sonobuoy;17 LOFAR (80) Sonobuoy;50 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 AGM-84C Harpoon;2 Mk-46 Mod5;2 Mk-46 Mod5;2 Mk-36 DST;6 Mk-36 DST;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('AB Kevlavik', 'P-3C II Orion', 'Sea Lion-2', 2)
    SM.SetFlightDeckUnitLoadout('AB Kevlavik', 'Sea Lion-2', '17 DICASS (80) Sonobuoy;17 LOFAR (80) Sonobuoy;50 DIFAR (80) Sonobuoy;2 Mk-46 Mod5;2 AGM-84C Harpoon;2 Mk-46 Mod5;2 Mk-46 Mod5;2 Mk-36 DST;6 Mk-36 DST;30 Flare-1;30 Chaff-1;')
    
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
    
    ##############################
    ### Alliance 2 units
    ##############################

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
    SM.AddToUnitMagazine("Kiev", 'DIFAR (80) Sonobuoy', 200)
    SM.AddToUnitMagazine("Kiev", 'LOFAR (80) Sonobuoy', 200)
    SM.AddToUnitMagazine("Kiev", 'DICASS (80) Sonobuoy', 100)
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
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix1', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix2', 2)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix2', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix3', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix3', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix4', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix4', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix5', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix5', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix6', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix6', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix7', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix7', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix8', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix8', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix9', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix9', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix10', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix10', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix11', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix11', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix12', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix12', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix13', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix13', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix14', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix14', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix15', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix15', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix16', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix16', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix17', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix17', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
    
    SM.AddUnitToFlightDeck('Kiev', 'Ka-27A', 'Helix18', 1)
    SM.SetFlightDeckUnitLoadout('Kiev', 'Helix18', '5 DICASS (80) Sonobuoy;5 DICASS (80) Sonobuoy;14 DICASS (80) Sonobuoy;2 APR-2E;')
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
    FP.SetMissionLaunchTime(mission_id, '12:10:00+0m+R0.5')
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
    FP.SetMissionLaunchTime(mission_id, '12:10:00+0m+R0.5')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Standby-AAW')
    FP.SetMissionPatrolArea(mission_id, '0.0013528,0.0186580,-0.0032079,0.0100173,0.0007467,0.0084257,0.0062670,0.0095528,')
    FP.SetMissionPatrolAnchor(mission_id, 'Kiev', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.2740640, 1.0971421, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.2929350, 1.0983419, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671RTMK Shchuka'
    unit.unitName = "B-355"
    boxes = [[-19.4206, -18.3184, 62.5362, 63.0470]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -100.0)
    unit.heading = 277.44
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
    UI.AddNavWaypointAdvanced(-0.366845, 1.102714, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.392722, 1.108125, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.377823, 1.107733, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135M Burevestnik-M'
    unit.unitName = "Ryavnyy"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0411
    lat_deg = 57.296*leader_track.Lat + 0.0198
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135M Burevestnik-M'
    unit.unitName = "Gromkiy"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0339
    lat_deg = 57.296*leader_track.Lat + -0.0100
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
    unit.className = 'Pr 1164 Atlant'
    unit.unitName = "Moskva"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0698
    lat_deg = 57.296*leader_track.Lat + 0.0031
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
    SM.AddToUnitMagazine("Moskva", 'DICASS (75) Sonobuoy', 170)
    SM.AddToUnitMagazine("Moskva", 'LOFAR (75) Sonobuoy', 170)
    SM.AddToUnitMagazine("Moskva", 'DIFAR (75) Sonobuoy', 476)
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
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135 Burevestnik'
    unit.unitName = "Storozhevoy"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0842
    lat_deg = 57.296*leader_track.Lat + 0.0020
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
    unit.className = 'Pr 1135 Burevestnik'
    unit.unitName = "Zadornyy"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1595
    lat_deg = 57.296*leader_track.Lat + 0.0026
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
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "BDK-10"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0338
    lat_deg = 57.296*leader_track.Lat + 0.0009
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
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "BDK-100"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0078
    lat_deg = 57.296*leader_track.Lat + 0.0194
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
    unit.unitName = "Doneckiy shakhter"
    UI = SM.GetUnitInterface('Kiev')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0055
    lat_deg = 57.296*leader_track.Lat + -0.0135
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
    goal_0_0 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_0_0)
    
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
    SM.SetIncludeProbability('B-355', 1.000000)
    SM.AddRandomBox('B-355', -19.4206, -18.3184, 62.5362, 63.0470)
    SM.SetIncludeProbability('K-239 Karp', 0.500000)
