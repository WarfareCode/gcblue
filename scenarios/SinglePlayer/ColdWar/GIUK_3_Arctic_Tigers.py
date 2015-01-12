# Created on 12/01/12 20:13:43
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""GIUK Part 3 Arctic Tigers\nRelease Version of 2012/12/01\n\nA scenario for Global Conflicts 2.\n\nIn the first days of the war, Soviet subs try to reach the open Atlantic in \norder to wait for the convoys Nato troops in Europe need to survive. \n\nIn this scenario You have to stop a bunch of Soviet subs coming \nfrom the very North and now heading like hungry tigers for our \nNorth Atlantic Sea Lanes.\n\nComments and critiques welcome!\n\n\n""")
    SM.SetScenarioName("""GIUK Part 3 Arctic Tigers""")
    SM.CreateAlliance(1, 'UK')
    SM.SetAllianceDefaultCountry(1, 'UK')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 0)
    SM.SetUserAlliance(1)

    SM.SetDateTime(1985,8,4,14,0,0)
    SM.SetStartTheater(-9.750003, 55.883335) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1511.807983,60.959999,1505.102417,304.800018,1501.444824,609.600037,1491.691162,914.400024,1484.985596,1219.200073,1487.119263,2362.199951,1502.664063,2743.199951,1507.235962,3962.400146,1527.657593,5181.600098,1548.079224')

    ####################
    SM.SetSimpleBriefing(1, """ORDERS FOR CMDR ROYAL NAVY OPERATIONS\n\n\nINTELLIGENCE\n\nIt is not enough to stop the enemy in the GIUK Gap. we need to stop his \nsub squadrons earlier, far more to the North.\n\nAlthough Nato subs normally operate alobne, this time we have \ncoordinated two modern SSNs.\n\n\nMISSION\n\nThere are at least three subs approaching from the North. Ambush \nthem. \n\n\nEXECUTION\n\nSink three Soviet subs.\n\n\nCOMMAND AND SIGNAL\n\nHMS Superb\n\n\n\n\n\n\n\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """TASKING ORDERS:\n\n\nNO ADDITIONAL INTELLIGENCE AVAILABLE.\n""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Swiftsure SSN'
    unit.unitName = "HMS Superb"
    unit.SetPosition(-5.238782, 68.784275, -305.0)
    unit.heading = 90.00
    unit.speed = 31.0
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
    SM.AddToUnitMagazine("HMS Superb", 'mk-24 Tigerfish', 20)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Swiftsure SSN'
    unit.unitName = "HMS Splendid"
    unit.SetPosition(-3.504439, 68.371054, -305.0)
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
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671RT Syomga'
    unit.unitName = "K-467"
    unit.SetPosition(-4.099742, 69.913113, -270.0)
    unit.heading = 90.00
    unit.speed = 16.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RPK-6 Vodopod', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '65-76 Kit', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-467", 'SET-65M', 9)
    SM.AddToUnitMagazine("K-467", '65-76 Kit', 6)
    SM.AddToUnitMagazine("K-467", 'RPK-6 Vodopod', 3)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.148694, 1.134291, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 670M Chayka'
    unit.unitName = "K-503"
    unit.SetPosition(-1.676245, 69.710858, -240.0)
    unit.heading = 90.00
    unit.speed = 17.4
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'P-120 Malakhit', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-503", 'SET-65', 4)
    SM.AddToUnitMagazine("K-503", '53-65M', 2)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.085314, 1.132106, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 675'
    unit.unitName = "K-35"
    unit.SetPosition(-2.377488, 70.249324, -190.0)
    unit.heading = 90.00
    unit.speed = 17.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-6', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'UMGT-1M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'UMGT-1M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-35", 'SET-65', 6)
    SM.AddToUnitMagazine("K-35", '53-65M', 2)
    SM.AddToUnitMagazine("K-35", 'UMGT-1M', 2)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.105858, 1.134510, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671RTMK Shchuka'
    unit.unitName = "B-305"
    unit.SetPosition(-2.803253, 69.285151, -100.0)
    unit.heading = 90.00
    unit.speed = 17.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RPK-6 Vodopod', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '65-76 Kit', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-305", 'SET-65M', 9)
    UI.SetSensorState(6, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.126839, 1.134291, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('B-305')
    goal_temp.AddTarget('K-35')
    goal_temp.AddTarget('K-503')
    goal_temp.AddTarget('K-467')
    goal_temp.SetQuantity(3)
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.AreaGoal()
    goal_temp.SetTargetList('Sub')
    goal_temp.SetTimeObjective(0.000000)
    goal_temp.SetLogicAny(1)
    goal_temp.SetQuantity(2)
    goal_temp.AddPointDeg(-4.01162, 65.92924)
    goal_temp.AddPointDeg(-4.01162, 64.02590)
    goal_temp.AddPointDeg(-10.02217, 64.01337)
    goal_temp.AddPointDeg(-9.94704, 65.95427)
    goal_20_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('K-467')
    goal_temp.AddTarget('K-503')
    goal_temp.AddTarget('K-35')
    goal_temp.AddTarget('B-305')
    goal_temp.SetQuantity(2)
    goal_20_1 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_20_0)
    goal_temp.AddGoal(goal_20_1)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
