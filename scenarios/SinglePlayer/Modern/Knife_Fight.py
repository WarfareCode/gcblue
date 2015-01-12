from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Knife Fight\n\nA scenario for Global Conflicts Blue 2\n2011/03/27\n\nThis scenario is most basical: sub vs. sub. \n\nThe storyline is based on Michael Palmer's book 'The War that never \nwas'.  The Order of Battle is according to James DeGoey, 'Harpoon \nBattlebook'.\n\n\n""")
    SM.SetScenarioName("""Knife Fight""")
    SM.CreateAlliance(1, 'UK')
    SM.SetAllianceDefaultCountry(1, 'UK')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 1)
    SM.SetUserAlliance(1)

    SM.SetDateTime(1996,8,4,12,0,0)
    SM.SetStartTheater(-6.883333, 66.949997) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(1)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """ORDERS  FOR CMDR UK OPERATIONS\n\n1) INTELLIGENCE:\n\nThere is at least one hostile sub in your patrol zone.\n\n2) MISSION:\n\nFind and destroy any hostile sub in the area.\n\n3) EXECUTION:\n\nProceed with care. It is by no means sure what you are up against. You \nhave 8 hours to fulfill your mission.\n\nROE: Weapons free.\n\nEMCON: Passive\n\nGood luck!\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """ORDERS  FOR CMDR RUSSIAN OPERATIONS\n\n1) INTELLIGENCE:\n\nAt least one hostile sub is in your patrol area.\n\n2) MISSION:\n\nFind and sink any hostile sub. \n\n3) EXECUTION:\n\nBe careful. You have 8 hours for your mission.\n\nROE: Weapons free. \n\nEMCON: Passive\n\nGood luck!\n \n \n\n\n""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Trafalgar SSN'
    unit.unitName = "HMS Talent"
    unit.SetPosition(-4.325774, 67.079323, -453.3)
    unit.heading = 45.00
    unit.speed = 4.9
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Spearfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Spearfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Spearfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Spearfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Spearfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Noisemaker-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Noisemaker-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Talent", 'Spearfish', 12)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(5, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.102145, 1.185074, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.071649, 1.184028, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.069856, 1.162053, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.103042, 1.163100, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.082413, 1.178198, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Victor III 671RTMK SSN'
    unit.unitName = "B-448 Tambov"
    unit.SetPosition(-5.206296, 67.319220, -466.7)
    unit.heading = 139.76
    unit.speed = 4.8
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'USET-80', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'USET-80', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'USET-80', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'USET-80', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'RPK-7 Veter', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RPK-7 Veter', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-448 Tambov", 'USET-80', 20)
    UI.SetSensorState(0, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.088691, 1.185822, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.057299, 1.185373, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.057299, 1.155027, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.092279, 1.155177, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.092578, 1.173713, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('B-448 Tambov')
    goal_20_0 = goal_temp

    goal_temp = SM.ProtectGoal('HMS Talent')
    goal_20_1 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(28800.0)
    goal_temp.SetFailTimeout(28800.0)
    goal_20_2 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_20_0)
    goal_temp.AddGoal(goal_20_1)
    goal_temp.AddGoal(goal_20_2)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.DestroyGoal('HMS Talent')
    goal_21_0 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(28800.0)
    goal_temp.SetFailTimeout(28800.0)
    goal_21_1 = goal_temp

    goal_temp = SM.ProtectGoal('B-448 Tambov')
    goal_21_2 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_21_0)
    goal_temp.AddGoal(goal_21_1)
    goal_temp.AddGoal(goal_21_2)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
