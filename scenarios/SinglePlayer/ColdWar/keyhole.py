# Created on 07/30/11 17:26:20
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Keyhole\n\nA Cold War scenario for GCB2.\n\nIn the World War 3 environment, there would have been many small \nbattles for the control over the Greenland-Iceland-United Kingdom \n(GIUK) Gap.\n\nHere is one of them. You are in control over a small British force, \nconsisting of two submarines and one surface vessel.\n\nYour job is to prevent Soviet subs from passing the British Channel.\n\nGood luck, commander!\n""")
    SM.SetScenarioName("""Keyhole""")
    SM.CreateAlliance(1, 'UK')
    SM.SetAllianceDefaultCountry(1, 'UK')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 0)
    SM.CreateAlliance(3, 'Neutral Shipping')
    SM.SetAllianceDefaultCountry(3, 'Neutral Shipping')
    SM.SetAlliancePlayable(3, 0)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(1)

    SM.SetDateTime(1988,8,2,5,0,0)
    SM.SetStartTheater(1.029166, 50.737499) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """TASKING ORDERS FOR CMDR BRITISH OPERATIONS\n\nINTELLIGENCE\n\nSupply is critical in order to win the war. Therefore our convoys are \nprimary targets for hostile subs. \n\nThe Soviets try to move large numbers of subs into the North Atlantic. \nThus the control over the GIUK Gap is critical. \n\nWe got intelligence that several subs try to break through the \nEnglish Channel. \n\nMISSION\n\nSink at least three  Russian subs. \n\nEXECUTION\n\nConduct aggressive ASW ops with your assets. Don't let any sub slip \nthrough your screen.\n\nOne of your sub carries the new Spearfish torpedo. Make it count. \n\nCOMMAND AND SIGNAL\n\nHMS Gloucester\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """TASKING ORDERS:\n\n\nNO ADDITIONAL INTELLIGENCE AVAILABLE.\n""")

    ####################
    SM.SetSimpleBriefing(3, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Type 42 DDG Batch 3'
    unit.unitName = "HMS Gloucester"
    unit.SetPosition(0.855197, 50.632166, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Sea Dart Mod2', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, '114mm N4A1 HE', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Gloucester", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Gloucester", 'Stingray', 20)
    SM.AddToUnitMagazine("HMS Gloucester", 'Sea Skua', 8)
    SM.AddToUnitMagazine("HMS Gloucester", 'LOFAR (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Gloucester", 'DICASS (80) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Gloucester", 'DIFAR (80) Sonobuoy', 405)
    SM.AddToUnitMagazine("HMS Gloucester", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Gloucester", '20mm Mark 149-4', 475)
    SM.AddToUnitMagazine("HMS Gloucester", 'Sea Dart Mod2', 40)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('HMS Gloucester', 'Lynx HAS.Mk.2', 'Type 42 B3 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Gloucester', 'Type 42 B3 Lynx 1', '2 Sea Skua;2 Sea Skua;5 DICASS (80) Sonobuoy;5 LOFAR (80) Sonobuoy;14 DIFAR (80) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Trafalgar SSN'
    unit.unitName = "HMS Turbulent"
    unit.SetPosition(1.236901, 50.721547, -15.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Spearfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Spearfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Spearfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Spearfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Spearfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Decoy-1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Turbulent", 'Spearfish', 20)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Swiftsure SSN'
    unit.unitName = "HMS Sceptre"
    unit.SetPosition(1.068509, 50.846739, -15.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'mk-24 Tigerfish', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Decoy-1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Sceptre", 'mk-24 Tigerfish', 20)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 670M Chayka'
    unit.unitName = "K-479"
    boxes = [[1.3183, 1.5278, 50.9593, 51.0173]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -10.9)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'P-120 Malakhit', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-479", 'SET-65', 8)
    SM.AddToUnitMagazine("K-479", '53-65M', 4)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.023130, 0.887710, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.021437, 0.884459, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.017111, 0.881770, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.009724, 0.876875, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641B Som'
    unit.unitName = "B-307"
    boxes = [[1.1276, 1.2971, 50.7459, 50.8381]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -13.1)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-307", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-307", '53-65M', 6)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.015168, 0.886546, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.009838, 0.885342, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.011731, 0.877115, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671RTMK Shchuka'
    unit.unitName = "B-244"
    boxes = [[1.1088, 1.2830, 50.9586, 51.0115]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -14.9)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '65-76 Kit', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-244", 'SET-65M', 24)
    SM.AddToUnitMagazine("B-244", '53-65M', 12)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.018616, 0.888191, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.013788, 0.885302, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.011919, 0.877798, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671RTMK Shchuka'
    unit.unitName = "B-247"
    boxes = [[1.2194, 1.4316, 50.8291, 50.9169]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -12.6)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '65-76 Kit', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-247", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-247", '53-65M', 6)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.023945, 0.884379, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.020748, 0.880928, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.009086, 0.878440, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.010100, 0.878359, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Chemical Tanker'
    unit.unitName = "Apollo"
    unit.SetPosition(1.265664, 50.590168, 0.0)
    unit.heading = 90.00
    unit.speed = 18.5
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.016675, 0.884335, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.005310, 0.882149, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.018829, 0.878820, 0.000000, 0.000000)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'General Cargo'
    unit.unitName = "Seagull"
    unit.SetPosition(1.106840, 50.934745, 0.0)
    unit.heading = 90.00
    unit.speed = 15.8
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.018869, 0.885478, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.011659, 0.883640, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.014440, 0.879813, 0.000000, 0.000000)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Chemical Tanker'
    unit.unitName = "Morning Star"
    unit.SetPosition(1.415550, 50.934745, 0.0)
    unit.heading = 90.00
    unit.speed = 20.8
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.020672, 0.886522, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.016675, 0.885031, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.013421, 0.878770, 0.000000, 0.000000)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(59940.0)
    goal_temp.SetFailTimeout(10800.0)
    goal_8_0 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('B-244')
    goal_temp.AddTarget('B-247')
    goal_temp.AddTarget('B-307')
    goal_temp.AddTarget('K-479')
    goal_temp.SetQuantity(3)
    goal_8_1 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_8_0)
    goal_temp.AddGoal(goal_8_1)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('K-479')
    goal_temp.AddTarget('B-244')
    goal_temp.AddTarget('B-247')
    goal_temp.AddTarget('B-307')
    goal_temp.SetQuantity(2)
    goal_9_0 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(10800.0)
    goal_temp.SetFailTimeout(5999940.0)
    goal_9_1 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_9_0)
    goal_temp.AddGoal(goal_9_1)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Alliance 3 goals
    ##############################

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(59940.0)
    goal_temp.SetFailTimeout(59940.0)
    SM.SetAllianceGoal(3, goal_temp)

    SM.SetAllianceROEByType(3, 2, 2, 2, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
    SM.SetIncludeProbability('B-244', 1.000000)
    SM.AddRandomBox('B-244', 1.1088, 1.2830, 50.9586, 51.0115)
    SM.SetIncludeProbability('B-247', 1.000000)
    SM.AddRandomBox('B-247', 1.2194, 1.4316, 50.8291, 50.9169)
    SM.SetIncludeProbability('B-307', 1.000000)
    SM.AddRandomBox('B-307', 1.1276, 1.2971, 50.7459, 50.8381)
    SM.SetIncludeProbability('K-479', 1.000000)
    SM.AddRandomBox('K-479', 1.3183, 1.5278, 50.9593, 51.0173)
