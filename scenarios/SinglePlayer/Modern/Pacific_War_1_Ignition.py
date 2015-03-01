# Created on 11/14/14 06:34:51
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Pacific War 1  Ignition\n\nThe Pacific War Battleset takes place in the year 2013 and analyzes \nwhat could happen in the Pacific. Long lasting tensions between several \nnations explode. Step by step, the big players get involved.   \n\nScenario #1 Ignition shows how it all starts. \n\nYou are in command of the Japanese Forces and try to protect several \nmerchants hunted by Chinese subs and ships.\n\nAction takes place close to the Senkaku Islands. \n\n\n""")
    SM.SetScenarioName("""Pacific War 1  Ignition""")
    SM.CreateAlliance(1, 'China')
    SM.SetAllianceDefaultCountry(1, 'China')
    SM.SetAlliancePlayable(1, 0)
    SM.CreateAlliance(2, 'Japan')
    SM.SetAllianceDefaultCountry(2, 'Japan')
    SM.SetAlliancePlayable(2, 1)
    SM.SetUserAlliance(2)

    SM.SetDateTime(2013,8,13,0,0,0)
    SM.SetStartTheater(123.029167, 24.970835) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(2)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """No briefing found""")

    ####################
    SM.SetSimpleBriefing(2, """ORDERS FOR CMDR JAPANESE OPERATIONS\n\nINTELLIGENCE\n\nPeace negotiations with the Chinese have ended without success a few \nhours ago. Chinese naval assets are taking attacking positions. It is very \nlikely that they will fight for the Senkaku Islands and try to sink our \nmerchants still in this area.\n\nA group of Chinese warships is closing from the West. Sub threat \nunknown. \n\nMISSION\n\nDefend both of Your merchants by all means and escort them till they \nhave reached safe waters.\n\n\nEXECUTION\n\nJDS Atago make best speed towards the two merchants. \nThen gather your sheep and bring them out of harms way to meeting \npoint N26 E125, where two other Harpoon armed Frigates are heading \nto with max speed.  \n\nCOMMAND AND SIGNAL\n\nJDS Atago\n\n\n\n\n\n\n\n\n\n\n\n\n\n""")

    ##############################
    ### Alliance 1 units
    ##############################

    if (SM.IncludeUnit(0.500000)):
        unit = SM.GetDefaultUnit()
        unit.className = 'Type 051G DDG(2001)'
        unit.unitName = "Zhanjiang"
        boxes = [[124.4560, 124.8409, 25.8203, 25.9276]]
        box = boxes[int(1*random())]
        lon_deg = random()*(box[1]-box[0]) + box[0]
        lat_deg = random()*(box[3]-box[2]) + box[2]
        unit.SetPosition(lon_deg, lat_deg, 0.0)
        unit.heading = 90.00
        unit.speed = 3.0
        unit.cost = 0.0
        SM.AddUnitToAlliance(unit, 1)
        SM.SetUnitLauncherItem(unit.unitName, 0, 'YJ-82', 8)
        SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-82', 8)
        SM.SetUnitLauncherItem(unit.unitName, 2, '100mm OF-58 FRAG', 26)
        SM.SetUnitLauncherItem(unit.unitName, 3, '100mm OF-58 FRAG', 26)
        SM.SetUnitLauncherItem(unit.unitName, 4, 'HQ-7', 8)
        SM.SetUnitLauncherItem(unit.unitName, 5, '37mm Type 676 HE-FRAG', 250)
        SM.SetUnitLauncherItem(unit.unitName, 6, '37mm Type 676 HE-FRAG', 250)
        SM.SetUnitLauncherItem(unit.unitName, 7, '37mm Type 676 HE-FRAG', 250)
        SM.SetUnitLauncherItem(unit.unitName, 8, '25mm HE-I-T', 400)
        SM.SetUnitLauncherItem(unit.unitName, 9, '25mm HE-I-T', 400)
        SM.SetUnitLauncherItem(unit.unitName, 10, 'Yu-7', 3)
        SM.SetUnitLauncherItem(unit.unitName, 11, 'Yu-7', 3)
        UI = SM.GetUnitInterface(unit.unitName)
        SM.AddToUnitMagazine("Zhanjiang", '37mm Type 676 HE-FRAG', 10000)
        SM.AddToUnitMagazine("Zhanjiang", '100mm OF-58 FRAG', 500)
        SM.AddToUnitMagazine("Zhanjiang", '100mm ZS-58P AA', 250)
        SM.AddToUnitMagazine("Zhanjiang", '25mm HE-I-T', 8000)
        SM.AddToUnitMagazine("Zhanjiang", 'Yu-7', 18)
        SM.AddToUnitMagazine("Zhanjiang", 'HQ-7', 16)
        UI.SetSensorState(13, 0)
        UI.AddTask('EngageAll', 2.000000, 0)
        UI.AddTask('MissileWarning', 3.000000, 3)
        UI.AddTask('Nav', 1.000000, 0)
        UI.AddNavWaypointAdvanced(2.172712, 0.451751, 0.000000, 0.000000)
        UI.AddNavWaypointAdvanced(2.176226, 0.451670, 0.000000, 0.000000)
        UI.AddNavWaypointAdvanced(2.175235, 0.450531, 0.000000, 0.000000)
        UI.SetNavLoopState(1)
        UI.AddTask('PointDefense', 3.000000, 3)
        BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 053'
    unit.unitName = "349"
    boxes = [[123.5982, 123.6742, 25.5432, 25.6307]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -125.7)
    unit.heading = 248.20
    unit.speed = 5.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, '53-56V', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("349", '53-56V', 24)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.161906, 0.447357, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181452, 0.454181, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181932, 0.453829, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181932, 0.453259, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 053'
    unit.unitName = "777"
    boxes = [[124.9165, 124.9495, 25.9183, 26.0403]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -190.0)
    unit.heading = 90.00
    unit.speed = 1.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, '53-56V', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("777", '53-56V', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.180454, 0.453606, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.182357, 0.453520, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181223, 0.453122, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181588, 0.453866, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 636 Vashavyanka(China)'
    unit.unitName = "Yuan Zheng 66 Hao"
    boxes = [[125.3879, 125.5289, 25.9828, 26.1296]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -150.0)
    unit.heading = 90.00
    unit.speed = 6.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65KE', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65KE', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Yuan Zheng 66 Hao", 'TEST-71ME', 10)
    SM.AddToUnitMagazine("Yuan Zheng 66 Hao", '53-65KE', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.188835, 0.455770, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.189451, 0.454091, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181492, 0.453849, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181972, 0.453347, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181203, 0.454212, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181223, 0.453105, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181953, 0.454230, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.182261, 0.453139, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181415, 0.454299, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181280, 0.453641, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 636 Vashavyanka(China)'
    unit.unitName = "Yuan Zheng 67 Hao"
    boxes = [[124.0954, 124.1379, 25.6695, 25.8200]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -100.0)
    unit.heading = 255.96
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65KE', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65KE', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Yuan Zheng 67 Hao", 'TEST-71ME', 8)
    SM.AddToUnitMagazine("Yuan Zheng 67 Hao", '53-65KE', 4)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.163958, 0.449698, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.164747, 0.448410, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.163733, 0.450173, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.165160, 0.447867, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 053K FFG'
    unit.unitName = "FFG Type 053K"
    unit.SetPosition(123.058441, 25.536787, 0.0)
    unit.heading = 77.47
    unit.speed = 26.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'HQ-61C', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'HQ-61C', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '37mm Type 676 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, '37mm Type 676 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 4, '37mm Type 676 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 5, '37mm Type 676 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 6, '37mm Type 676 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 7, '37mm Type 676 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 8, '100mm OF-58 FRAG', 26)
    SM.SetUnitLauncherItem(unit.unitName, 9, '100mm OF-58 FRAG', 26)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'EDS-25A ASW Mortar', 1)
    SM.SetUnitLauncherItem(unit.unitName, 11, 'EDS-25A ASW Mortar', 1)
    SM.SetUnitLauncherItem(unit.unitName, 12, 'Chn DC', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("FFG Type 053K", '37mm Type 676 HE-FRAG', 15000)
    SM.AddToUnitMagazine("FFG Type 053K", '100mm OF-58 FRAG', 600)
    SM.AddToUnitMagazine("FFG Type 053K", 'EDS-25A ASW Mortar', 12)
    SM.AddToUnitMagazine("FFG Type 053K", 'HQ-61C', 28)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Chinese Airbase"
    unit.SetPosition(119.625968, 25.955676, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Chinese Airbase", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Chinese Airbase", 'Chaff-1', 10000)
    SM.AddToUnitMagazine("Chinese Airbase", 'Flare-1', 10000)
    SM.AddToUnitMagazine("Chinese Airbase", 'YJ-6', 50)
    SM.AddToUnitMagazine("Chinese Airbase", 'GB-200', 200)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Chinese Airbase', 'H-6D', 'Eye-1', 2)
    SM.SetFlightDeckUnitLoadout('Chinese Airbase', 'Eye-1', '40 GB-200;2 YJ-6;')
    
    SM.AddUnitToFlightDeck('Chinese Airbase', 'H-6D', 'Eye-2', 2)
    SM.SetFlightDeckUnitLoadout('Chinese Airbase', 'Eye-2', '40 GB-200;2 YJ-6;')
    
    SM.AddUnitToFlightDeck('Chinese Airbase', 'H-6D', 'Eye-3', 2)
    SM.SetFlightDeckUnitLoadout('Chinese Airbase', 'Eye-3', '40 GB-200;2 YJ-6;')
    
    SM.AddUnitToFlightDeck('Chinese Airbase', 'H-6D', 'Eye-4', 2)
    SM.SetFlightDeckUnitLoadout('Chinese Airbase', 'Eye-4', '40 GB-200;2 YJ-6;')
    
    SM.AddUnitToFlightDeck('Chinese Airbase', 'H-6D', 'Eye-5', 2)
    SM.SetFlightDeckUnitLoadout('Chinese Airbase', 'Eye-5', '40 GB-200;2 YJ-6;')
    
    SM.AddUnitToFlightDeck('Chinese Airbase', 'H-6D', 'Eye-6', 2)
    SM.SetFlightDeckUnitLoadout('Chinese Airbase', 'Eye-6', '40 GB-200;2 YJ-6;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Eye-1')
    FP.AddAircraftToMission(mission_id, 'Eye-2')
    FP.AddAircraftToMission(mission_id, 'Eye-3')
    FP.AddAircraftToMission(mission_id, 'Eye-4')
    FP.AddAircraftToMission(mission_id, 'Eye-5')
    FP.AddAircraftToMission(mission_id, 'Eye-6')
    FP.SetMissionLaunchTime(mission_id, '00:20:00+5m+R4.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '2.1853907,0.4484783,2.1646934,0.4442941,2.1673217,0.4542263,2.1697621,0.4584104,')
    FP.AddMissionWaypointAdvanced(mission_id, 2.0888669, 0.4540120, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 2.1670430, 0.4543390, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877EKM Paltus(China)'
    unit.unitName = "Yuan Zhend 64 Hao"
    boxes = [[123.6007, 123.7741, 25.5132, 25.7132]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -100.0)
    unit.heading = 257.47
    unit.speed = 5.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M32M Strela 3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '3M54E Klub Alfa', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 053'
    unit.unitName = "346"
    boxes = [[124.3213, 124.6180, 25.7953, 25.9135]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, -125.7)
    unit.heading = 248.20
    unit.speed = 1.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '53-56V', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, '53-56V', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("346", '53-56V', 16)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.168016, 0.450627, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181665, 0.453137, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181377, 0.454241, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.182194, 0.454306, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.182338, 0.453289, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.181161, 0.453289, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 956E Sarych'
    unit.unitName = "Hangzhou"
    UI = SM.GetUnitInterface('FFG Type 053K')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0366
    lat_deg = 57.296*leader_track.Lat + 0.0347
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 33.0
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 1, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M80 Moskit', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M317', 24)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M317', 24)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 236)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 236)
    SM.SetUnitLauncherItem(unit.unitName, 7, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Chaff-2', 50)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'Chaff-2', 50)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(7, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('FFG Type 053K')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(4.259, 0.500, -2.395, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 956EM Sarych'
    unit.unitName = "Taizhou"
    UI = SM.GetUnitInterface('FFG Type 053K')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0234
    lat_deg = 57.296*leader_track.Lat + -0.0353
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 66.04
    unit.speed = 33.0
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3M80 Moskit', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M317', 24)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M317', 24)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M311 Kashtan', 16)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M311 Kashtan', 16)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OP-84 FRAG Tracer AK-306', 20)
    SM.SetUnitLauncherItem(unit.unitName, 7, '30mm OP-84 FRAG Tracer AK-306', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'Chaff-2', 50)
    SM.SetUnitLauncherItem(unit.unitName, 11, 'Chaff-2', 50)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(7, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('FFG Type 053K')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(3.312, 0.500, -2.802, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Harushio'
    unit.unitName = "JDS Fuyushio"
    unit.SetPosition(124.422312, 25.779147, -61.7)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Type-89 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Type-89 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Type-89 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Type-89 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Type-89 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'UGM-84C Harpoon', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("JDS Fuyushio", 'Type-89 Torpedo', 10)
    SM.AddToUnitMagazine("JDS Fuyushio", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Atago'
    unit.unitName = "JDS Atago"
    unit.SetPosition(123.533139, 25.562226, 0.0)
    unit.heading = -93.37
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SSM-1B', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SSM-1B', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-162A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '127mm mk 127 HE-CVT mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("JDS Atago", 'Fuel', 56117)
    SM.AddToUnitMagazine("JDS Atago", 'Mk-46 Mod5', 30)
    SM.AddToUnitMagazine("JDS Atago", '120 gallon tank', 4)
    SM.AddToUnitMagazine("JDS Atago", 'Chaff-1', 75)
    SM.AddToUnitMagazine("JDS Atago", 'Flare-1', 75)
    SM.AddToUnitMagazine("JDS Atago", 'DICASS (110) Sonobuoy', 130)
    SM.AddToUnitMagazine("JDS Atago", 'LOFAR (110) Sonobuoy', 130)
    SM.AddToUnitMagazine("JDS Atago", 'DIFAR (110) Sonobuoy', 390)
    SM.AddToUnitMagazine("JDS Atago", 'RIM-66M', 64)
    SM.AddToUnitMagazine("JDS Atago", 'RIM-162A', 96)
    SM.AddToUnitMagazine("JDS Atago", '20mm mark 244-0 ELC', 970)
    SM.AddToUnitMagazine("JDS Atago", '127mm mk 127 HE-CVT mk 67', 680)
    UI.SetSensorState(6, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('JDS Atago', 'SH-60J', 'Atago Helo 1', 1)
    SM.SetFlightDeckUnitLoadout('JDS Atago', 'Atago Helo 1', '1 Mk-46 Mod5;1 Mk-46 Mod5;30 Chaff-1;30 Flare-1;5 DICASS (110) Sonobuoy;5 LOFAR (110) Sonobuoy;15 DIFAR (110) Sonobuoy;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Abukuma FFG'
    unit.unitName = "JDS Ohyodo"
    unit.SetPosition(125.707857, 26.198668, 0.0)
    unit.heading = -110.56
    unit.speed = 27.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RUR-5 Mod4 ASROC', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("JDS Ohyodo", '76mm HE-MOM', 240)
    UI.SetSensorState(5, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.181622, 0.453664, 0.000000, 0.000000)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 0, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"RGM-84G Harpoon": 0, "20mm mark 244-0 ELC": 0, "MU-90": 0, "RGM-84D Harpoon": 0, "Mk-44": 0, "RUR-5 ASROC": 0, "76mm HE-MOM": 240, "RGM-84F Harpoon": 0, "Mk-46 Mod5": 0, "DART": 0, "Mk-54": 0, "RUR-5 Mod4 ASROC": 0, "RUM-139 Mod4 ASROC": 0, "RGM-84A Harpoon": 0, "Stingray": 0, "Mk-15 Mod0": 0, "RGM-84C Harpoon": 0, "Mk-50": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 0, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 1, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 1}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"20mm mark 244-0 ELC": [97, 97], "76mm HE-MOM": [80, 80], "RUR-5 Mod4 ASROC": [8, 8], "Mk-46 Mod5": [6, 6], "RGM-84D Harpoon": [8, 8]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Naha"
    unit.SetPosition(127.683351, 26.216667, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Freighter"
    unit.SetPosition(123.535434, 25.590243, 0.0)
    unit.heading = 90.00
    unit.speed = 16.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.181715, 0.453649, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Fishing Boat"
    unit.SetPosition(123.541676, 25.544751, 0.0)
    unit.heading = 90.00
    unit.speed = 14.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.181668, 0.453607, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Abukuma FFG'
    unit.unitName = "JDS Abukuma"
    UI = SM.GetUnitInterface('JDS Ohyodo')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0729
    lat_deg = 57.296*leader_track.Lat + -0.0607
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -108.43
    unit.speed = 27.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RUR-5 Mod4 ASROC', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("JDS Abukuma", '76mm HE-MOM', 240)
    UI.SetSensorState(5, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('JDS Ohyodo')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(9.487, 2.246, 4.415, 0.502)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Freighter')
    goal_temp.AddTarget('Fishing Boat')
    goal_temp.SetQuantity(1)
    goal_2_0 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_2_0)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.AreaGoal()
    goal_temp.SetTargetList('Fishing Boat, Freighter')
    goal_temp.SetTimeObjective(300.000000)
    goal_temp.SetLogicAny(1)
    goal_temp.SetQuantity(2)
    goal_temp.AddPointDeg(125.05967, 26.05434)
    goal_temp.AddPointDeg(125.05967, 25.93975)
    goal_temp.AddPointDeg(124.94509, 25.93975)
    goal_temp.AddPointDeg(124.94509, 26.05434)
    goal_3_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Fishing Boat')
    goal_temp.AddTarget('Freighter')
    goal_temp.SetQuantity(2)
    goal_3_1 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_3_0)
    goal_temp.AddGoal(goal_3_1)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
    SM.SetIncludeProbability('346', 1.000000)
    SM.AddRandomBox('346', 124.3213, 124.6180, 25.7953, 25.9135)
    SM.SetIncludeProbability('349', 1.000000)
    SM.AddRandomBox('349', 123.5982, 123.6742, 25.5432, 25.6307)
    SM.SetIncludeProbability('777', 1.000000)
    SM.AddRandomBox('777', 124.9165, 124.9495, 25.9183, 26.0403)
    SM.SetIncludeProbability('JDS Arashio', 0.500000)
    SM.AddRandomBox('JDS Arashio', 123.2186, 123.2971, 25.3902, 25.6250)
    SM.SetIncludeProbability('JDS Wakashio', 0.500000)
    SM.AddRandomBox('JDS Wakashio', 123.8304, 124.1553, 25.6133, 25.7207)
    SM.SetIncludeProbability('Yuan Zhend 64 Hao', 1.000000)
    SM.AddRandomBox('Yuan Zhend 64 Hao', 123.6007, 123.7741, 25.5132, 25.7132)
    SM.SetIncludeProbability('Yuan Zheng 66 Hao', 1.000000)
    SM.AddRandomBox('Yuan Zheng 66 Hao', 125.3879, 125.5289, 25.9828, 26.1296)
    SM.SetIncludeProbability('Yuan Zheng 67 Hao', 1.000000)
    SM.AddRandomBox('Yuan Zheng 67 Hao', 124.0954, 124.1379, 25.6695, 25.8200)
    SM.SetIncludeProbability('Zhanjiang', 0.500000)
    SM.AddRandomBox('Zhanjiang', 124.4560, 124.8409, 25.8203, 25.9276)
