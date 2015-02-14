# Created on 05/22/11 22:03:59
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Convoy\n\nA scenario for Global Conflicts 2.\n\nWritten by Ralf Koelbach.\nrkoelbach@yahoo.com\n\nConvoy is a classical Cold War scenario putting first line Soviet \nsubmarines against an small, heavily escorted Nato convoy.\n\nYou are to defend your convoy at all costs. \n\nComments and critiques welcome!\n\nHave fun!\nRalf\n\nJanuary 2011\n\n\n""")
    SM.SetScenarioName("""Convoy""")
    SM.CreateAlliance(1, 'USA')
    SM.SetAllianceDefaultCountry(1, 'USA')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 0)
    SM.CreateAlliance(3, 'Neutrals')
    SM.SetAllianceDefaultCountry(3, 'Neutrals')
    SM.SetAlliancePlayable(3, 0)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(1)

    SM.SetDateTime(1990,8,4,12,0,0)
    SM.SetStartTheater(-39.970833, 42.237499) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(1)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """TASKING ORDERS FOR CMDR US OPERATIONS\n\nINTELLIGENCE\n\nSupply is critical in order to win the war. Therefore our convoys are \nprimary targets for hostile subs. \n\nYou are escorting a small but extremely important convoy. All three \nmerchant ships carry technical and chemical equipment of the highest \nvalue. \n\nMISSION\n\nYou are to bring all three merchants in a guarded position around 45 N \n37 W. \n\nEXECUTION\n\nConduct aggressive ASW ops with your assets. Don't let any sub slip \nthrough your screen.\n\nCOMMAND AND SIGNAL\n\nUSS Paul F. Foster\n\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """TASKING ORDERS:\n\n\nNO ADDITIONAL INTELLIGENCE AVAILABLE.\n""")

    ####################
    SM.SetSimpleBriefing(3, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Sturgeon'
    unit.unitName = "USS Gurnard"
    unit.SetPosition(-38.888651, 42.644389, -400.0)
    unit.heading = 90.00
    unit.speed = 12.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'UGM-84C Harpoon', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Decoy-1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Decoy-1', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Gurnard", 'Mk-48 Mod5', 12)
    SM.AddToUnitMagazine("USS Gurnard", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.676898, 0.748201, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.670775, 0.747866, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.674755, 0.753797, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.666795, 0.754245, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.672612, 0.761519, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.662968, 0.760959, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.667407, 0.766891, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.658682, 0.767002, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.661284, 0.772486, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.653477, 0.772486, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.648885, 0.782558, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SH-60B'
    unit.unitName = "Scout 2"
    unit.SetPosition(-39.275455, 42.783217, 50.0)
    unit.heading = 90.00
    unit.speed = 127.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-46 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '120 gallon tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-46 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'LOFAR (85) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'DICASS (85) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'DIFAR (85) Sonobuoy', 15)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.692599, 0.746310, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.687082, 0.751318, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.672711, 0.764871, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.661078, 0.776872, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SH-60B'
    unit.unitName = "Scout 1"
    unit.SetPosition(-38.354540, 42.158292, 50.0)
    unit.heading = 90.00
    unit.speed = 127.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-46 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '120 gallon tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-46 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'LOFAR (85) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'DICASS (85) Sonobuoy', 5)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'DIFAR (85) Sonobuoy', 15)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.671334, 0.727626, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.657710, 0.739852, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.648679, 0.759437, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.641025, 0.776645, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Los Angeles (1988)'
    unit.unitName = "USS Alaxandria"
    unit.SetPosition(-37.422395, 44.515383, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod5', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'UGM-84C Harpoon', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'UGM-109A', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'UGM-109A', 6)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Alaxandria", 'Mk-48 Mod5', 12)
    SM.AddToUnitMagazine("USS Alaxandria", 'UGM-84C Harpoon', 4)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Spruance DDG VLS'
    unit.unitName = "USS Paul F. Foster"
    unit.SetPosition(-39.184526, 42.390741, 0.0)
    unit.heading = 32.09
    unit.speed = 16.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RUM-139 Mod4 ASROC', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'BGM-109 TASM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'BGM-109 TLAM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'RGM-84D Harpoon', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Paul F. Foster", 'Fuel', 65176)
    SM.AddToUnitMagazine("USS Paul F. Foster", 'Mk-46 Mod5', 29)
    SM.AddToUnitMagazine("USS Paul F. Foster", '120 gallon tank', 4)
    SM.AddToUnitMagazine("USS Paul F. Foster", 'AGM-114 Hellfire', 16)
    SM.AddToUnitMagazine("USS Paul F. Foster", 'Chaff-1', 100)
    SM.AddToUnitMagazine("USS Paul F. Foster", 'Flare-1', 100)
    SM.AddToUnitMagazine("USS Paul F. Foster", 'LOFAR (85) Sonobuoy', 263)
    SM.AddToUnitMagazine("USS Paul F. Foster", 'DICASS (85) Sonobuoy', 263)
    SM.AddToUnitMagazine("USS Paul F. Foster", 'DIFAR (85) Sonobuoy', 788)
    SM.AddToUnitMagazine("USS Paul F. Foster", 'RUM-139 Mod4 ASROC', 15)
    SM.AddToUnitMagazine("USS Paul F. Foster", 'BGM-109 TASM', 5)
    SM.AddToUnitMagazine("USS Paul F. Foster", 'BGM-109 TLAM', 38)
    SM.AddToUnitMagazine("USS Paul F. Foster", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Paul F. Foster", '127mm mk 80 HE-PD mk 67', 1200)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.645984, 0.785249, 0.000000, 0.000000)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS Paul F. Foster', 'SH-60B', 'Spruance VLS DDG Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Paul F. Foster', 'Spruance VLS DDG Seahawk 1', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Paul F. Foster', 'SH-60B', 'Spruance VLS DDG Seahawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Paul F. Foster', 'Spruance VLS DDG Seahawk 2', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 42 DDG Batch 1'
    unit.unitName = "HMS Cardiff"
    UI = SM.GetUnitInterface('USS Paul F. Foster')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2939
    lat_deg = 57.296*leader_track.Lat + -0.0757
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 1, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Sea Dart Mod2', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, '114mm N4A1 HE', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Cardiff", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Cardiff", 'Stingray', 20)
    SM.AddToUnitMagazine("HMS Cardiff", 'Sea Skua', 8)
    SM.AddToUnitMagazine("HMS Cardiff", 'LOFAR (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Cardiff", 'DICASS (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Cardiff", 'DIFAR (85) Sonobuoy', 405)
    SM.AddToUnitMagazine("HMS Cardiff", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Cardiff", '20mm Mark 149-4', 970)
    SM.AddToUnitMagazine("HMS Cardiff", 'Sea Dart Mod2', 22)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Paul F. Foster')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(25.460, 2.340, -2.471, 0.143)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('HMS Cardiff', 'Lynx HAS.Mk.2', 'Type 42 B1 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Cardiff', 'Type 42 B1 Lynx 1', '2 Stingray;2 Stingray;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oliver Hazard Perry FFGHM'
    unit.unitName = "USS Rentz"
    UI = SM.GetUnitInterface('USS Paul F. Foster')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0183
    lat_deg = 57.296*leader_track.Lat + -0.2319
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66L', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Rentz", 'Fuel', 28098)
    SM.AddToUnitMagazine("USS Rentz", 'Mk-46 Mod5', 22)
    SM.AddToUnitMagazine("USS Rentz", 'AGM-114 Hellfire', 8)
    SM.AddToUnitMagazine("USS Rentz", '120 gallon tank', 2)
    SM.AddToUnitMagazine("USS Rentz", 'Chaff-1', 50)
    SM.AddToUnitMagazine("USS Rentz", 'Flare-1', 50)
    SM.AddToUnitMagazine("USS Rentz", 'DICASS (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Rentz", 'LOFAR (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Rentz", 'DIFAR (85) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS Rentz", 'RIM-66L', 35)
    SM.AddToUnitMagazine("USS Rentz", 'RGM-84D Harpoon', 4)
    SM.AddToUnitMagazine("USS Rentz", '20mm mark 244-0 ELC', 523)
    SM.AddToUnitMagazine("USS Rentz", '76mm HE-MOM', 240)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Paul F. Foster')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(25.431, 2.515, 2.648, 0.147)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Rentz', 'SH-60B', 'Perry FFG Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Rentz', 'Perry FFG Seahawk 1', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oliver Hazard Perry FFGHM'
    unit.unitName = "USS Nicholas"
    UI = SM.GetUnitInterface('USS Paul F. Foster')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.3235
    lat_deg = 57.296*leader_track.Lat + -0.2406
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 29.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66L', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Nicholas", 'Fuel', 28098)
    SM.AddToUnitMagazine("USS Nicholas", 'Mk-46 Mod5', 22)
    SM.AddToUnitMagazine("USS Nicholas", 'AGM-114 Hellfire', 8)
    SM.AddToUnitMagazine("USS Nicholas", '120 gallon tank', 2)
    SM.AddToUnitMagazine("USS Nicholas", 'Chaff-1', 50)
    SM.AddToUnitMagazine("USS Nicholas", 'Flare-1', 50)
    SM.AddToUnitMagazine("USS Nicholas", 'DICASS (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Nicholas", 'LOFAR (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("USS Nicholas", 'DIFAR (85) Sonobuoy', 315)
    SM.AddToUnitMagazine("USS Nicholas", 'RIM-66L', 35)
    SM.AddToUnitMagazine("USS Nicholas", 'RGM-84D Harpoon', 4)
    SM.AddToUnitMagazine("USS Nicholas", '20mm mark 244-0 ELC', 523)
    SM.AddToUnitMagazine("USS Nicholas", '76mm HE-MOM', 240)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Paul F. Foster')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(37.137, 3.690, -2.922, 0.072)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Nicholas', 'SH-60B', 'Perry FFG Seahawk 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Nicholas', 'Perry FFG Seahawk 101', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;15 DIFAR (85) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'General Cargo'
    unit.unitName = "Sea Lion"
    UI = SM.GetUnitInterface('USS Paul F. Foster')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2316
    lat_deg = 57.296*leader_track.Lat + -0.1681
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Paul F. Foster')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(25.737, 3.315, -2.922, 0.128)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Daphne"
    UI = SM.GetUnitInterface('USS Paul F. Foster')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1517
    lat_deg = 57.296*leader_track.Lat + -0.1175
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Paul F. Foster')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(17.867, 1.349, -2.952, 0.128)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Chemical Tanker'
    unit.unitName = "Morning Sun"
    UI = SM.GetUnitInterface('USS Paul F. Foster')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0835
    lat_deg = 57.296*leader_track.Lat + -0.0669
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Paul F. Foster')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(9.940, 1.269, -2.943, 0.188)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641B Som'
    unit.unitName = "B-312"
    unit.SetPosition(-37.564259, 44.349970, 0.0)
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
    SM.AddToUnitMagazine("B-312", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-312", '53-65M', 6)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.658070, 0.777858, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.648426, 0.774389, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877M Paltus'
    unit.unitName = "B-800"
    unit.SetPosition(-38.730858, 42.996300, -190.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M32M Strela 3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-800", '53-65M', 12)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.656639, 0.778230, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.645617, 0.775853, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877M Paltus'
    unit.unitName = "B-808"
    unit.SetPosition(-37.333186, 44.634672, -190.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M32M Strela 3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-808", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-808", '53-65M', 6)
    SM.AddToUnitMagazine("B-808", '9M32M Strela 3', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.656639, 0.778230, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.645617, 0.775853, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671 Yorzh'
    unit.unitName = "K-462"
    unit.SetPosition(-38.420716, 43.791451, -270.0)
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
    SM.AddToUnitMagazine("K-462", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-462", '53-65M', 6)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.678430, 0.760679, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.662510, 0.757524, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.661132, 0.769129, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.645213, 0.782648, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Russian Air Base"
    unit.SetPosition(-22.398009, 63.939111, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Russian Air Base", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Russian Air Base", 'Chaff-1', 10000)
    SM.AddToUnitMagazine("Russian Air Base", 'Flare-1', 10000)
    SM.AddToUnitMagazine("Russian Air Base", 'AIM-9M', 100)
    SM.AddToUnitMagazine("Russian Air Base", 'AIM-120C', 100)
    UI.SetSensorState(0, 1)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-1', 2)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-1', '24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-2', 2)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-2', '24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-3', 2)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-3', '24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-4', 2)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-4', '24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-5', 2)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-5', '24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-6', 2)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-6', '24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-7', 2)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-7', '24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-8', 2)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-8', '24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-9', 1)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-9', '24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-10', 1)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-10', '24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-11', 1)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-11', '24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Russian Air Base', 'Tu-95RT', 'Sniffer-12', 1)
    SM.SetFlightDeckUnitLoadout('Russian Air Base', 'Sniffer-12', '24 Flare-1;48 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Sniffer-1')
    FP.AddAircraftToMission(mission_id, 'Sniffer-2')
    FP.AddAircraftToMission(mission_id, 'Sniffer-3')
    FP.SetMissionLaunchTime(mission_id, '13:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.7911270,0.7635365,-0.5721273,0.7482895,-0.5291495,0.7869326,-0.7974802,0.7998136,')
    FP.AddMissionWaypointAdvanced(mission_id, -0.3899190, 1.1169480, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.7018080, 0.7969220, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Sniffer-4')
    FP.AddAircraftToMission(mission_id, 'Sniffer-5')
    FP.AddAircraftToMission(mission_id, 'Sniffer-6')
    FP.SetMissionLaunchTime(mission_id, '13:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.3342433,-0.1042446,0.3535170,-0.0923414,0.3409712,-0.0841614,0.3245844,-0.0942721,')
    FP.SetMissionPatrolAnchor(mission_id, 'Russian Air Base', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.3899190, 1.1169480, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.5926350, 0.7859080, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Sniffer-7')
    FP.AddAircraftToMission(mission_id, 'Sniffer-8')
    FP.AddAircraftToMission(mission_id, 'Sniffer-9')
    FP.AddAircraftToMission(mission_id, 'Sniffer-10')
    FP.AddAircraftToMission(mission_id, 'Sniffer-11')
    FP.AddAircraftToMission(mission_id, 'Sniffer-12')
    FP.SetMissionLaunchTime(mission_id, '13:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2848176,-0.0832755,0.3325501,-0.0905751,0.3164271,-0.1203244,0.2686946,-0.1113720,')
    FP.SetMissionPatrolAnchor(mission_id, 'Russian Air Base', 2)
    FP.AddMissionWaypointAdvanced(mission_id, -0.3899190, 1.1169480, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, -0.6087850, 0.8411970, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Tu-95RT'
    unit.unitName = "Bear 1"
    unit.SetPosition(-40.478036, 44.158774, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Flare-1', 24)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Chaff-1', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(2, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.718785, 0.754291, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.704190, 0.727454, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.658234, 0.720817, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.639102, 0.751261, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.659023, 0.767709, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.695906, 0.769585, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.343199)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 670M Chayka'
    unit.unitName = "K-209"
    unit.SetPosition(-37.453278, 41.803115, -300.0)
    unit.heading = 90.00
    unit.speed = 17.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'P-120 Malakhit', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-209", 'SET-65', 8)
    SM.AddToUnitMagazine("K-209", '53-65M', 4)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.656792, 0.742569, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.645770, 0.783211, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671 Yorzh'
    unit.unitName = "K-53"
    unit.SetPosition(-39.773584, 42.731708, -270.0)
    unit.heading = 90.00
    unit.speed = 17.6
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-53", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-53", '53-65M', 6)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.680671, 0.753211, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.648832, 0.782306, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 705 Lira'
    unit.unitName = "K-316"
    unit.SetPosition(-39.687526, 41.900289, -750.0)
    unit.heading = 90.00
    unit.speed = 24.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-316", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-316", '53-65M', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.674395, 0.751060, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.653730, 0.768154, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.647148, 0.783551, 0.000000, 0.000000)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 671 Yorzh'
    unit.unitName = "K-147"
    unit.SetPosition(-38.316667, 42.808828, -270.0)
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
    SM.AddToUnitMagazine("K-147", 'SET-65M', 12)
    SM.AddToUnitMagazine("K-147", '53-65M', 6)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.675161, 0.753551, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.663833, 0.750607, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Generic submarine'
    unit.unitName = "Neutral Sub"
    unit.SetPosition(-38.721691, 42.554550, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MK-T1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'UGM-84C Harpoon', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Neutral Sub", 'MK-T1', 15)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(-0.682517, 0.743192, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.676012, 0.748513, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.667939, 0.743134, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.672641, 0.738334, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.673190, 0.754297, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.676012, 0.758981, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.670760, 0.760774, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(-0.667390, 0.757304, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.AreaGoal()
    goal_temp.SetTargetList('Daphne, Morning Sun, Sea Lion')
    goal_temp.SetTimeObjective(300.000000)
    goal_temp.SetLogicAny(0)
    goal_temp.AddPointDeg(-36.51304, 45.29395)
    goal_temp.AddPointDeg(-36.65557, 44.86866)
    goal_temp.AddPointDeg(-37.34625, 44.95692)
    goal_temp.AddPointDeg(-37.30240, 45.41432)
    goal_0_0 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_0_0)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.DestroyGoal('Sea Lion')
    goal_1_0 = goal_temp

    goal_temp = SM.DestroyGoal('Morning Sun')
    goal_1_1 = goal_temp

    goal_temp = SM.DestroyGoal('Daphne')
    goal_1_2 = goal_temp

    goal_temp = SM.CompoundGoal(1)
    goal_temp.AddGoal(goal_1_0)
    goal_temp.AddGoal(goal_1_1)
    goal_temp.AddGoal(goal_1_2)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Alliance 3 goals
    ##############################

    goal_temp = SM.DestroyGoal('Sea Lion')
    goal_2_0 = goal_temp

    goal_temp = SM.DestroyGoal('Morning Sun')
    goal_2_1 = goal_temp

    goal_temp = SM.DestroyGoal('Daphne')
    goal_2_2 = goal_temp

    goal_temp = SM.CompoundGoal(1)
    goal_temp.AddGoal(goal_2_0)
    goal_temp.AddGoal(goal_2_1)
    goal_temp.AddGoal(goal_2_2)
    
    SM.SetAllianceGoal(3, goal_temp)

    SM.SetAllianceROEByType(3, 0, 0, 0, 0)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
