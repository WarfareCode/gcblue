# Created on 12/09/14 15:38:36
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""New Russia 3 Baltic Air Policing\n\nThe Baltic air-policing mission is a NATO air defence Quick Reaction Alert \n(QRA) in order to guard the airspace over the three Baltic states of \nEstonia, Latvia and Lithuania.\n\nNATO members without their own Air Policing assets are assisted by \nother NATO members. Luxembourg is covered by interceptors from \nBelgium, while Slovenia and Albania are covered by Italian aircraft.\n\nSince March 2004, when the Baltic States joined NATO, the 24/7 task of \npolicing the airspace of the Baltic States was conducted on a three-\nmonth rotation from Lithuania's First Air Base in Zokniai/Siauliai \nInternational Airport, near the northern city of Siauliai. Starting with the \nTurkish deployment, rotations changed to a four-month basis. Usual \ndeployments consist of four fighter aircraft with between 50 and 100 \nsupport personnel.\n\nSource: Wikipedia\n\n""")
    SM.SetScenarioName("""New Russia 3 Baltic Air Policing""")
    SM.CreateAlliance(1, 'NATO')
    SM.SetAllianceDefaultCountry(1, 'NATO')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'Russia')
    SM.SetAllianceDefaultCountry(2, 'Russia')
    SM.SetAlliancePlayable(2, 0)
    SM.CreateAlliance(3, 'Sweden')
    SM.SetAllianceDefaultCountry(3, 'Sweden')
    SM.SetAlliancePlayable(3, 0)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(1)

    SM.SetDateTime(2014,9,13,0,0,0)
    SM.SetStartTheater(23.616663, 53.383331) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """INTELLIGENCE\n\nDuring the 2014 Crimean crisis, the U.S. Air Force deployed six F-15C \nEagle fighter jets from US-run Lakenheath air base in eastern England to \nthe Lithuanian Air Force Base near Siauliai. These aircraft will augment \nthe present mission comprising four U.S. F 15C Eagle aircraft. The U.S. \nheightened its NATO presence to increase the strength of the Baltic Air \nPolicing mission. Another two U.S. KC 135 aerial refuelling aircraft \nbrought aircraft service personnel. In May 2014, NATO established its \nsecond air base in Estonia's Aemari near Tallinn, beginning with a Danish \ndeployment\nSource: Wikipedia\n\nIt was about time: the Russians reinforced their base, scrambling \ntogether a full regiment of SU 27 Flanker.\n\nIn the last hours, heavy activity is going on over there. It seems like the \nwhole regiment is about to launch, intentions unknown.\n\nFurthermore, more Russian aircraft are closing in from the East, \nintentions unknown. This seems to be a mixed force of fighters and \nfighter bombers. \n\nMISSION\n\nThis is for real. We cannot ignore the facts. Luckily, we have reinforced \nour air bases, too. Thus we have nearly achieved to build up a full \nfighter wing, scrambled together from several NATO air forces.\n\nMore fighters are coming in, escorting a Sentry and a tanker.\n\nIn case of attack, Your primary objective is to guard both bases.\n\nFurther goals: \n\nDown as many hostile ac as possible, thus stopping any \naggression in the tracks.\n\nDestroy the Soviet Airbase.\n\nWe must send a strong message, thus preventing an all out war.\nEXECUTION\n\nDo not shoot until You are under attack. We will not start the war.\n\n\nCOMMAND AND SIGNAL\n\nAEW Sentry.\n\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """No briefing found""")

    ####################
    SM.SetSimpleBriefing(3, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'F-15E'
    unit.unitName = "Strike Eagle-4"
    unit.SetPosition(13.108186, 58.373400, 9939.0)
    unit.heading = 83.59
    unit.speed = 334.6
    unit.cost = 29900000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '600 gallon tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AGM-65D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-120D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'GBU-12/B', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'GBU-39 SDB', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'AGM-65D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'ALE-45 Flare', 120)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'ALE-45 Chaff', 120)
    SM.SetUnitLauncherItem(unit.unitName, 8, '20mm PGU', 46)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '-1')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19800.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 4, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 4, "MagWeaponList": {"600 gallon tank": 0, "Chaff-1": 0, "AIM-7*": 0, "AIM-120*": 0, "ALE-45 Chaff": 0, "Mk-84": 0, "GBU-31C(v)4": 0, "Mk-82": 0, "AIM-9*": 0, "AGM-130": 0, "GBU-31A(v)2": 0, "Flare-1": 0, "GBU-10/B": 0, "AGM-65D": 0, "20mm PGU-28/B": 0, "GBU-39 SDB": 0, "AIM-9M": 0, "GBU-12/B": 0, "20mm PGU": 0, "AIM-9X": 0, "B-61*": 0, "ALE-45 Flare": 0, "AIM-120C": 0, "AIM-7M": 0, "AIM-7P": 0}, "Air": 4, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 1, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"AGM-65D": [8, 8], "AIM-120A": [24, 24], "GBU-12/B": [16, 16], "20mm PGU": [184, 184], "AGM-130": [8, 8], "ALE-45 Flare": [480, 480], "ALE-45 Chaff": [480, 480], "600 gallon tank": [8, 8]}}')
    UI.SetThrottle(0.251282)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'F-15E'
    unit.unitName = "Strike Eagle-3"
    unit.SetPosition(13.385153, 58.305391, 9870.9)
    unit.heading = 83.59
    unit.speed = 334.6
    unit.cost = 29900000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '600 gallon tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AGM-65D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-120D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'GBU-12/B', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'GBU-39 SDB', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'AGM-65D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'ALE-45 Flare', 120)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'ALE-45 Chaff', 120)
    SM.SetUnitLauncherItem(unit.unitName, 8, '20mm PGU', 46)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '-1')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19800.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 4, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 4, "MagWeaponList": {"600 gallon tank": 0, "Chaff-1": 0, "AIM-7*": 0, "AIM-120*": 0, "ALE-45 Chaff": 0, "Mk-84": 0, "GBU-31C(v)4": 0, "Mk-82": 0, "AIM-9*": 0, "AGM-130": 0, "GBU-31A(v)2": 0, "Flare-1": 0, "GBU-10/B": 0, "AGM-65D": 0, "20mm PGU-28/B": 0, "GBU-39 SDB": 0, "AIM-9M": 0, "GBU-12/B": 0, "20mm PGU": 0, "AIM-9X": 0, "B-61*": 0, "ALE-45 Flare": 0, "AIM-120C": 0, "AIM-7M": 0, "AIM-7P": 0}, "Air": 4, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 1, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"AGM-65D": [8, 8], "AIM-120A": [24, 24], "GBU-12/B": [16, 16], "20mm PGU": [184, 184], "AGM-130": [8, 8], "ALE-45 Flare": [480, 480], "ALE-45 Chaff": [480, 480], "600 gallon tank": [8, 8]}}')
    UI.SetThrottle(0.251282)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'F-15E'
    unit.unitName = "Strike Eagle-2"
    unit.SetPosition(13.333874, 58.486842, 9939.2)
    unit.heading = 83.59
    unit.speed = 334.6
    unit.cost = 29900000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '600 gallon tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AGM-65D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-120D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'GBU-12/B', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'GBU-39 SDB', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'AGM-65D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'ALE-45 Flare', 120)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'ALE-45 Chaff', 120)
    SM.SetUnitLauncherItem(unit.unitName, 8, '20mm PGU', 46)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '-1')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19800.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 1, "MagWeaponList": {"600 gallon tank": 0, "Chaff-1": 0, "AIM-7*": 0, "AIM-120*": 0, "ALE-45 Chaff": 0, "Mk-84": 0, "GBU-31C(v)4": 0, "Mk-82": 0, "AIM-9*": 0, "AGM-130": 0, "GBU-31A(v)2": 0, "Flare-1": 0, "GBU-10/B": 0, "AGM-65D": 0, "20mm PGU-28/B": 0, "GBU-39 SDB": 0, "AIM-9M": 0, "GBU-12/B": 0, "20mm PGU": 0, "AIM-9X": 0, "B-61*": 0, "ALE-45 Flare": 0, "AIM-120C": 0, "AIM-7M": 0, "AIM-7P": 0}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 1, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"AGM-65D": [2, 2], "AIM-120A": [6, 6], "GBU-12/B": [4, 4], "20mm PGU": [46, 46], "AGM-130": [2, 2], "ALE-45 Flare": [120, 120], "ALE-45 Chaff": [120, 120], "600 gallon tank": [2, 2]}}')
    UI.SetThrottle(0.251282)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'F-15E'
    unit.unitName = "Strike Eagle-1"
    unit.SetPosition(13.528736, 58.367724, 9866.9)
    unit.heading = 83.59
    unit.speed = 334.6
    unit.cost = 29900000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '600 gallon tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AGM-65D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-120D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'GBU-12/B', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'GBU-39 SDB', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'AGM-65D', 2)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'ALE-45 Flare', 120)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'ALE-45 Chaff', 120)
    SM.SetUnitLauncherItem(unit.unitName, 8, '20mm PGU', 46)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '-1')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19800.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 1, "MagWeaponList": {"600 gallon tank": 0, "Chaff-1": 0, "AIM-7*": 0, "AIM-120*": 0, "ALE-45 Chaff": 0, "Mk-84": 0, "GBU-31C(v)4": 0, "Mk-82": 0, "AIM-9*": 0, "AGM-130": 0, "GBU-31A(v)2": 0, "Flare-1": 0, "GBU-10/B": 0, "AGM-65D": 0, "20mm PGU-28/B": 0, "GBU-39 SDB": 0, "AIM-9M": 0, "GBU-12/B": 0, "20mm PGU": 0, "AIM-9X": 0, "B-61*": 0, "ALE-45 Flare": 0, "AIM-120C": 0, "AIM-7M": 0, "AIM-7P": 0}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 1, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"AGM-65D": [2, 2], "AIM-120A": [6, 6], "GBU-12/B": [4, 4], "20mm PGU": [46, 46], "AGM-130": [2, 2], "ALE-45 Flare": [120, 120], "ALE-45 Chaff": [120, 120], "600 gallon tank": [2, 2]}}')
    UI.SetThrottle(0.251282)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'CF-18'
    unit.unitName = "RCAF Hornet-2"
    unit.SetPosition(23.309470, 55.698889, 9866.0)
    unit.heading = 90.00
    unit.speed = 334.6
    unit.cost = 40000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1400 liter tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AIM-7P', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-7P', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'AIM-7P', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'AIM-9X', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm PGU', 46)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '-1')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 17000.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 2, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 2, "MagWeaponList": {"1400 liter tank": 0, "FPU-8": 0, "GBU-24B/B": 0, "Chaff-1": 0, "AIM-7*": 0, "AGM-88B": 0, "Mk-84": 0, "GBU-31C(v)4": 0, "Mk-81": 0, "GBU-27": 0, "Mk-83": 0, "GBU-16/B": 0, "B-83*": 0, "GBU-31A(v)2": 0, "AIM-9N": 0, "AIM-132 ASRAAM": 0, "GBU-10/B": 0, "Mk-82": 0, "20mm PGU-28/B": 0, "GBU-32A(v)2": 0, "AIM-9M": 0, "GBU-12/B": 0, "20mm PGU": 0, "B-28*": 0, "B-53*": 0, "AIM-9X": 0, "B-61*": 0, "AIM-9P": 0, "FPU-6": 0, "Flare-1": 0, "GBU-28B/B": 0, "B-39*": 0, "B-41*": 0, "AGM-88*": 0, "AIM-9*": 0, "AIM-7M": 0, "B-57*": 0, "GBU-24/B": 0, "GBU-32C(v)4": 0}, "Air": 2, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"1400 liter tank": [2, 2], "20mm PGU": [92, 92], "Chaff-1": [60, 60], "Flare-1": [60, 60], "AIM-9X": [4, 4], "AIM-7P": [12, 12]}}')
    UI.SetThrottle(0.415525)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'CF-18'
    unit.unitName = "RCAF Hornet-1"
    unit.SetPosition(23.063270, 55.703587, 9890.8)
    unit.heading = 90.00
    unit.speed = 334.6
    unit.cost = 40000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '1400 liter tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AIM-7P', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-7P', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'AIM-7P', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'AIM-9X', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm PGU', 46)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '-1')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 17000.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 2, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 2, "MagWeaponList": {"1400 liter tank": 0, "FPU-8": 0, "GBU-24B/B": 0, "Chaff-1": 0, "AIM-7*": 0, "AGM-88B": 0, "Mk-84": 0, "GBU-31C(v)4": 0, "Mk-81": 0, "GBU-27": 0, "Mk-83": 0, "GBU-16/B": 0, "B-83*": 0, "GBU-31A(v)2": 0, "AIM-9N": 0, "AIM-132 ASRAAM": 0, "GBU-10/B": 0, "Mk-82": 0, "20mm PGU-28/B": 0, "GBU-32A(v)2": 0, "AIM-9M": 0, "GBU-12/B": 0, "20mm PGU": 0, "B-28*": 0, "B-53*": 0, "AIM-9X": 0, "B-61*": 0, "AIM-9P": 0, "FPU-6": 0, "Flare-1": 0, "GBU-28B/B": 0, "B-39*": 0, "B-41*": 0, "AGM-88*": 0, "AIM-9*": 0, "AIM-7M": 0, "B-57*": 0, "GBU-24/B": 0, "GBU-32C(v)4": 0}, "Air": 2, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"1400 liter tank": [2, 2], "20mm PGU": [92, 92], "Chaff-1": [60, 60], "Flare-1": [60, 60], "AIM-9X": [4, 4], "AIM-7P": [12, 12]}}')
    UI.SetThrottle(0.415525)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'F-15C'
    unit.unitName = "Escort Eagle-4"
    unit.SetPosition(22.509507, 59.148897, 10000.0)
    unit.heading = 90.00
    unit.speed = 334.6
    unit.cost = 29900000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AIM-120D', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AIM-9X', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-9X', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm PGU', 46)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '-1')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19800.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 1, "MagWeaponList": {"20mm PGU-28/B": 0, "AIM-9*": 0, "AIM-9M": 0, "AIM-120C": 0, "20mm PGU": 0, "AIM-7M": 0, "Chaff-1": 0, "AIM-7*": 0, "AIM-120*": 0, "600 gallon tank": 0, "Flare-1": 0}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"AIM-120D": [4, 4], "20mm PGU": [46, 46], "Chaff-1": [30, 30], "Flare-1": [30, 30], "AIM-9X": [4, 4], "Empty": [0, 0]}}')
    BB.Write('loadouts_dict', '{"Air to Air": {"F-15C": {"AW4E": {"600 gallon tank": 3, "20mm PGU": 46, "AIM-7M": 6, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW2E": {"600 gallon tank": 3, "AIM-120C": 4, "20mm PGU": 46, "AIM-7M": 2, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW3E": {"600 gallon tank": 3, "AIM-120C": 2, "20mm PGU": 46, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW1E": {"600 gallon tank": 3, "AIM-120C": 6, "20mm PGU": 46, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}}}}')
    UI.SetThrottle(0.251282)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'F-15C'
    unit.unitName = "Escort Eagle-3"
    unit.SetPosition(22.484927, 59.335108, 10000.0)
    unit.heading = 90.00
    unit.speed = 334.6
    unit.cost = 29900000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AIM-120D', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AIM-9X', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-9X', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm PGU', 46)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '-1')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19800.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 1, "MagWeaponList": {"20mm PGU-28/B": 0, "AIM-9*": 0, "AIM-9M": 0, "AIM-120C": 0, "20mm PGU": 0, "AIM-7M": 0, "Chaff-1": 0, "AIM-7*": 0, "AIM-120*": 0, "600 gallon tank": 0, "Flare-1": 0}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"AIM-120D": [4, 4], "20mm PGU": [46, 46], "Chaff-1": [30, 30], "Flare-1": [30, 30], "AIM-9X": [4, 4], "Empty": [0, 0]}}')
    BB.Write('loadouts_dict', '{"Air to Air": {"F-15C": {"AW4E": {"600 gallon tank": 3, "20mm PGU": 46, "AIM-7M": 6, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW2E": {"600 gallon tank": 3, "AIM-120C": 4, "20mm PGU": 46, "AIM-7M": 2, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW3E": {"600 gallon tank": 3, "AIM-120C": 2, "20mm PGU": 46, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW1E": {"600 gallon tank": 3, "AIM-120C": 6, "20mm PGU": 46, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}}}}')
    UI.SetThrottle(0.251282)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'KC-135R'
    unit.unitName = "Cow"
    unit.SetPosition(22.755706, 59.153194, 10000.0)
    unit.heading = 90.00
    unit.speed = 252.0
    unit.cost = 39600000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
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
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19800.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 6, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 6, "MagWeaponList": {"20mm PGU-28/B": 0, "AIM-9*": 0, "AIM-9M": 0, "AIM-120C": 0, "20mm PGU": 0, "AIM-7M": 0, "Chaff-1": 0, "AIM-7*": 0, "AIM-120*": 0, "600 gallon tank": 0, "Flare-1": 0}, "Air": 6, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"AIM-120D": [8, 8], "AIM-9B": [8, 8], "AIM-120A": [16, 16], "20mm PGU": [184, 184], "Chaff-1": [120, 120], "Flare-1": [120, 120], "Empty": [0, 0]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'E-3G'
    unit.unitName = "Skyeye"
    unit.SetPosition(22.780344, 59.235528, 10000.0)
    unit.heading = 90.00
    unit.speed = 230.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
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
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19800.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 6, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 6, "MagWeaponList": {"20mm PGU-28/B": 0, "AIM-9*": 0, "AIM-9M": 0, "AIM-120C": 0, "20mm PGU": 0, "AIM-7M": 0, "Chaff-1": 0, "AIM-7*": 0, "AIM-120*": 0, "600 gallon tank": 0, "Flare-1": 0}, "Air": 6, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"AIM-120D": [8, 8], "AIM-9B": [8, 8], "AIM-120A": [16, 16], "20mm PGU": [184, 184], "Chaff-1": [120, 120], "Flare-1": [120, 120], "Empty": [0, 0]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Siauliai AB"
    unit.SetPosition(23.390333, 55.889666, -0.0)
    unit.heading = 149.74
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Siauliai AB", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Siauliai AB", '1150 Liter Tank', 4)
    SM.AddToUnitMagazine("Siauliai AB", '20mm PGU', 2059)
    SM.AddToUnitMagazine("Siauliai AB", '20mm PGU-28/B', 2243)
    SM.AddToUnitMagazine("Siauliai AB", '27mm HE', 68)
    SM.AddToUnitMagazine("Siauliai AB", '600 gallon tank', 20)
    SM.AddToUnitMagazine("Siauliai AB", 'AGM-130', 9)
    SM.AddToUnitMagazine("Siauliai AB", 'AGM-65B', 27)
    SM.AddToUnitMagazine("Siauliai AB", 'AGM-65D', 55)
    SM.AddToUnitMagazine("Siauliai AB", 'AGM-65J', 27)
    SM.AddToUnitMagazine("Siauliai AB", 'AGM-65K', 27)
    SM.AddToUnitMagazine("Siauliai AB", 'AGM-84F Harpoon', 5)
    SM.AddToUnitMagazine("Siauliai AB", 'AGM-84H SLAM-ER', 5)
    SM.AddToUnitMagazine("Siauliai AB", 'AGM-88C', 74)
    SM.AddToUnitMagazine("Siauliai AB", 'AIM-120C7', 261)
    SM.AddToUnitMagazine("Siauliai AB", 'AIM-120D', 272)
    SM.AddToUnitMagazine("Siauliai AB", 'AIM-132 ASRAAM', 28)
    SM.AddToUnitMagazine("Siauliai AB", 'AIM-9P4', 184)
    SM.AddToUnitMagazine("Siauliai AB", 'AIM-9X', 251)
    SM.AddToUnitMagazine("Siauliai AB", 'Chaff-1', 4923)
    SM.AddToUnitMagazine("Siauliai AB", 'FPU-6', 12)
    SM.AddToUnitMagazine("Siauliai AB", 'FPU-8', 12)
    SM.AddToUnitMagazine("Siauliai AB", 'Flare-1', 4923)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-10/B', 31)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-12/B', 133)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-15/B', 20)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-16/B', 17)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-24/B', 20)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-24B/B', 20)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-27', 8)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-28B/B', 14)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-30', 27)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-31A(v)2', 14)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-31C(v)4', 14)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-32A(v)2', 15)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-32C(v)4', 15)
    SM.AddToUnitMagazine("Siauliai AB", 'GBU-39 SDB', 60)
    SM.AddToUnitMagazine("Siauliai AB", 'MBDA Meteor', 89)
    SM.AddToUnitMagazine("Siauliai AB", 'Mk 16 Zuni FFAR', 183)
    SM.AddToUnitMagazine("Siauliai AB", 'Mk 71 Zuni WAFAR', 183)
    SM.AddToUnitMagazine("Siauliai AB", 'Mk-81', 77)
    SM.AddToUnitMagazine("Siauliai AB", 'Mk-82', 253)
    SM.AddToUnitMagazine("Siauliai AB", 'Mk-83', 81)
    SM.AddToUnitMagazine("Siauliai AB", 'Mk-84', 48)
    SM.AddToUnitMagazine("Siauliai AB", 'AIM-7P', 28)
    UI.SetSensorState(0, 1)
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
    BB.Write('MagTonnage', '35')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "Alt+": 0, "Speed+": 0, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 0, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 0, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {}}')
    
    SM.AddUnitToFlightDeck('Siauliai AB', 'F-16AM/BM Blk 15 MLU', 'Forca aerea Portuguesa-1', 2)
    SM.SetFlightDeckUnitLoadout('Siauliai AB', 'Forca aerea Portuguesa-1', '2 AIM-9P4;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Siauliai AB', 'F-16AM/BM Blk 15 MLU', 'Forca aerea Portuguesa-2', 2)
    SM.SetFlightDeckUnitLoadout('Siauliai AB', 'Forca aerea Portuguesa-2', '2 AIM-9P4;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Siauliai AB', 'F-16AM/BM Blk 15 MLU', 'Forca aerea Portuguesa-3', 2)
    SM.SetFlightDeckUnitLoadout('Siauliai AB', 'Forca aerea Portuguesa-3', '2 AIM-9P4;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Siauliai AB', 'F-16AM/BM Blk 15 MLU', 'Forca aerea Portuguesa-4', 2)
    SM.SetFlightDeckUnitLoadout('Siauliai AB', 'Forca aerea Portuguesa-4', '2 AIM-9P4;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Siauliai AB', 'CF-18', 'Royal Canadian Air Force-1', 1)
    SM.SetFlightDeckUnitLoadout('Siauliai AB', 'Royal Canadian Air Force-1', '1 1400 liter tank;2 AIM-7P;2 AIM-7P;2 AIM-7P;2 AIM-9P4;46 20mm PGU;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Siauliai AB', 'CF-18', 'Royal Canadian Air Force-2', 1)
    SM.SetFlightDeckUnitLoadout('Siauliai AB', 'Royal Canadian Air Force-2', '1 1400 liter tank;2 AIM-7P;2 AIM-7P;2 AIM-7P;2 AIM-9P4;46 20mm PGU;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Siauliai AB', 'CF-18', 'Royal Canadian Air Force-3', 1)
    SM.SetFlightDeckUnitLoadout('Siauliai AB', 'Royal Canadian Air Force-3', '1 1400 liter tank;2 AIM-7P;2 AIM-7P;2 AIM-7P;2 AIM-9P4;46 20mm PGU;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Siauliai AB', 'CF-18', 'Royal Canadian Air Force-4', 1)
    SM.SetFlightDeckUnitLoadout('Siauliai AB', 'Royal Canadian Air Force-4', '1 1400 liter tank;2 AIM-7P;2 AIM-7P;2 AIM-7P;2 AIM-9P4;46 20mm PGU;30 Flare-1;30 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Amari AB"
    unit.SetPosition(24.205001, 59.256167, -0.0)
    unit.heading = 273.01
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Amari AB", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Amari AB", '1150 Liter Tank', 4)
    SM.AddToUnitMagazine("Amari AB", '20mm PGU', 502)
    SM.AddToUnitMagazine("Amari AB", '20mm PGU-28/B', 502)
    SM.AddToUnitMagazine("Amari AB", '27mm HE', 41)
    SM.AddToUnitMagazine("Amari AB", 'AGM-65B', 26)
    SM.AddToUnitMagazine("Amari AB", 'AGM-65D', 26)
    SM.AddToUnitMagazine("Amari AB", 'AGM-65J', 26)
    SM.AddToUnitMagazine("Amari AB", 'AGM-65K', 26)
    SM.AddToUnitMagazine("Amari AB", 'AGM-84F Harpoon', 5)
    SM.AddToUnitMagazine("Amari AB", 'AGM-84H SLAM-ER', 5)
    SM.AddToUnitMagazine("Amari AB", 'AGM-88C', 54)
    SM.AddToUnitMagazine("Amari AB", 'AIM-120C7', 48)
    SM.AddToUnitMagazine("Amari AB", 'AIM-9P4', 32)
    SM.AddToUnitMagazine("Amari AB", 'Chaff-1', 1399)
    SM.AddToUnitMagazine("Amari AB", 'Flare-1', 1399)
    SM.AddToUnitMagazine("Amari AB", 'GBU-10/B', 10)
    SM.AddToUnitMagazine("Amari AB", 'GBU-12/B', 73)
    SM.AddToUnitMagazine("Amari AB", 'GBU-15/B', 19)
    SM.AddToUnitMagazine("Amari AB", 'GBU-24/B', 10)
    SM.AddToUnitMagazine("Amari AB", 'GBU-24B/B', 10)
    SM.AddToUnitMagazine("Amari AB", 'GBU-30', 26)
    SM.AddToUnitMagazine("Amari AB", 'GBU-31A(v)2', 5)
    SM.AddToUnitMagazine("Amari AB", 'GBU-31C(v)4', 5)
    SM.AddToUnitMagazine("Amari AB", 'GBU-32A(v)2', 8)
    SM.AddToUnitMagazine("Amari AB", 'GBU-32C(v)4', 8)
    SM.AddToUnitMagazine("Amari AB", 'GBU-39 SDB', 22)
    SM.AddToUnitMagazine("Amari AB", 'MBDA Meteor', 52)
    SM.AddToUnitMagazine("Amari AB", 'Mk 16 Zuni FFAR', 174)
    SM.AddToUnitMagazine("Amari AB", 'Mk 71 Zuni WAFAR', 174)
    SM.AddToUnitMagazine("Amari AB", 'Mk-82', 103)
    SM.AddToUnitMagazine("Amari AB", 'Mk-83', 36)
    SM.AddToUnitMagazine("Amari AB", 'Mk-84', 14)
    SM.AddToUnitMagazine("Amari AB", 'ASRAAM', 32)
    UI.SetSensorState(0, 1)
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
    BB.Write('MagTonnage', '35')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "Alt+": 0, "Speed+": 0, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 0, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 0, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {}}')
    
    SM.AddUnitToFlightDeck('Amari AB', 'Typhoon', 'Luftwaffe-1', 2)
    SM.SetFlightDeckUnitLoadout('Amari AB', 'Luftwaffe-1', '2 ASRAAM;2 MBDA Meteor;2 MBDA Meteor;4 MBDA Meteor;1 1150 Liter Tank;6 27mm HE;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Amari AB', 'Typhoon', 'Luftwaffe-2', 2)
    SM.SetFlightDeckUnitLoadout('Amari AB', 'Luftwaffe-2', '2 ASRAAM;2 MBDA Meteor;2 MBDA Meteor;4 MBDA Meteor;1 1150 Liter Tank;6 27mm HE;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Amari AB', 'Typhoon', 'Luftwaffe-3', 2)
    SM.SetFlightDeckUnitLoadout('Amari AB', 'Luftwaffe-3', '2 ASRAAM;2 MBDA Meteor;2 MBDA Meteor;4 MBDA Meteor;1 1150 Liter Tank;6 27mm HE;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Amari AB', 'Typhoon', 'Luftwaffe-4', 2)
    SM.SetFlightDeckUnitLoadout('Amari AB', 'Luftwaffe-4', '2 ASRAAM;2 MBDA Meteor;2 MBDA Meteor;4 MBDA Meteor;1 1150 Liter Tank;6 27mm HE;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Amari AB', 'F-16AM/BM Blk 15 MLU', 'Royal Netherlands Air Force-1', 2)
    SM.SetFlightDeckUnitLoadout('Amari AB', 'Royal Netherlands Air Force-1', '2 AIM-9P4;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Chaff-1;30 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Amari AB', 'F-16AM/BM Blk 15 MLU', 'Royal Netherlands Air Force-2', 2)
    SM.SetFlightDeckUnitLoadout('Amari AB', 'Royal Netherlands Air Force-2', '2 AIM-9P4;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Chaff-1;30 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Amari AB', 'F-16AM/BM Blk 15 MLU', 'Royal Netherlands Air Force-3', 1)
    SM.SetFlightDeckUnitLoadout('Amari AB', 'Royal Netherlands Air Force-3', '2 AIM-9P4;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Chaff-1;30 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Amari AB', 'F-16AM/BM Blk 15 MLU', 'Royal Netherlands Air Force-4', 1)
    SM.SetFlightDeckUnitLoadout('Amari AB', 'Royal Netherlands Air Force-4', '2 AIM-9P4;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Chaff-1;30 Flare-1;46 20mm PGU;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'F-15C'
    unit.unitName = "Escort Eagle-1"
    unit.SetPosition(23.010100, 59.314425, 10000.0)
    unit.heading = 90.00
    unit.speed = 334.6
    unit.cost = 29900000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AIM-120D', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AIM-9X', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-9X', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm PGU', 46)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '-1')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19800.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 1, "MagWeaponList": {"20mm PGU-28/B": 0, "AIM-9*": 0, "AIM-9M": 0, "AIM-120C": 0, "20mm PGU": 0, "AIM-7M": 0, "Chaff-1": 0, "AIM-7*": 0, "AIM-120*": 0, "600 gallon tank": 0, "Flare-1": 0}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"AIM-120D": [4, 4], "20mm PGU": [46, 46], "Chaff-1": [30, 30], "Flare-1": [30, 30], "AIM-9X": [4, 4], "Empty": [0, 0]}}')
    BB.Write('loadouts_dict', '{"Air to Air": {"F-15C": {"AW4E": {"600 gallon tank": 3, "20mm PGU": 46, "AIM-7M": 6, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW2E": {"600 gallon tank": 3, "AIM-120C": 4, "20mm PGU": 46, "AIM-7M": 2, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW3E": {"600 gallon tank": 3, "AIM-120C": 2, "20mm PGU": 46, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW1E": {"600 gallon tank": 3, "AIM-120C": 6, "20mm PGU": 46, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}}}}')
    UI.SetThrottle(0.251282)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'F-15C'
    unit.unitName = "Escort Eagle-2"
    unit.SetPosition(22.993713, 59.135032, 10000.0)
    unit.heading = 90.00
    unit.speed = 334.6
    unit.cost = 29900000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'AIM-120D', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'AIM-9X', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'AIM-9X', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, '', 0)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm PGU', 46)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '-1')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19800.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 1, "MagWeaponList": {"20mm PGU-28/B": 0, "AIM-9*": 0, "AIM-9M": 0, "AIM-120C": 0, "20mm PGU": 0, "AIM-7M": 0, "Chaff-1": 0, "AIM-7*": 0, "AIM-120*": 0, "600 gallon tank": 0, "Flare-1": 0}, "Air": 1, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"AIM-120D": [4, 4], "20mm PGU": [46, 46], "Chaff-1": [30, 30], "Flare-1": [30, 30], "AIM-9X": [4, 4], "Empty": [0, 0]}}')
    BB.Write('loadouts_dict', '{"Air to Air": {"F-15C": {"AW4E": {"600 gallon tank": 3, "20mm PGU": 46, "AIM-7M": 6, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW2E": {"600 gallon tank": 3, "AIM-120C": 4, "20mm PGU": 46, "AIM-7M": 2, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW3E": {"600 gallon tank": 3, "AIM-120C": 2, "20mm PGU": 46, "AIM-7M": 4, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}, "AW1E": {"600 gallon tank": 3, "AIM-120C": 6, "20mm PGU": 46, "Chaff-1": 30, "Flare-1": 30, "AIM-9M": 2}}}}')
    UI.SetThrottle(0.251282)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Typhoon'
    unit.unitName = "RAF Typhoon-1"
    unit.SetPosition(15.211113, 55.535138, 10000.0)
    unit.heading = 87.55
    unit.speed = 334.6
    unit.cost = 50000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'ASRAAM', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MBDA Meteor', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MBDA Meteor', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MBDA Meteor', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '1150 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '27mm HE', 6)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.328280, 0.995423, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '0.156130000949')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19810.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 4, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 4, "MagWeaponList": {"Chaff-1": 0, "AIM-9M": 0, "1150 Liter Tank": 0, "AIM-120C": 0, "AGM-88*": 0, "27mm HE": 0, "GBU-12/B": 0, "Flare-1": 0, "AGM-84C Harpoon": 0, "AIM-9X": 0, "ASRAAM": 0, "GBU-30": 0, "MBDA Meteor": 0}, "Air": 4, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"1150 Liter Tank": [4, 4], "27mm HE": [24, 24], "Chaff-1": [120, 120], "Flare-1": [120, 120], "ASRAAM": [8, 8], "MBDA Meteor": [32, 32]}}')
    UI.SetThrottle(0.237061)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Typhoon'
    unit.unitName = "RAF Typhoon-2"
    unit.SetPosition(15.800973, 55.535138, 10000.0)
    unit.heading = 87.55
    unit.speed = 334.6
    unit.cost = 50000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'ASRAAM', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MBDA Meteor', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MBDA Meteor', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MBDA Meteor', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '1150 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '27mm HE', 6)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.328280, 0.995423, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '0.230959996581')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19810.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 4, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 4, "MagWeaponList": {"Chaff-1": 0, "AIM-9M": 0, "1150 Liter Tank": 0, "AIM-120C": 0, "AGM-88*": 0, "27mm HE": 0, "GBU-12/B": 0, "Flare-1": 0, "AGM-84C Harpoon": 0, "AIM-9X": 0, "ASRAAM": 0, "GBU-30": 0, "MBDA Meteor": 0}, "Air": 4, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"1150 Liter Tank": [4, 4], "27mm HE": [24, 24], "Chaff-1": [120, 120], "Flare-1": [120, 120], "ASRAAM": [8, 8], "MBDA Meteor": [32, 32]}}')
    UI.SetThrottle(0.237061)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Typhoon'
    unit.unitName = "RAF Typhoon-3"
    unit.SetPosition(15.493238, 55.735502, 10000.0)
    unit.heading = 87.55
    unit.speed = 334.6
    unit.cost = 50000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'ASRAAM', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MBDA Meteor', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MBDA Meteor', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MBDA Meteor', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '1150 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '27mm HE', 6)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.328280, 0.995423, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '0.230959996581')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19810.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 4, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 4, "MagWeaponList": {"Chaff-1": 0, "AIM-9M": 0, "1150 Liter Tank": 0, "AIM-120C": 0, "AGM-88*": 0, "27mm HE": 0, "GBU-12/B": 0, "Flare-1": 0, "AGM-84C Harpoon": 0, "AIM-9X": 0, "ASRAAM": 0, "GBU-30": 0, "MBDA Meteor": 0}, "Air": 4, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"1150 Liter Tank": [4, 4], "27mm HE": [24, 24], "Chaff-1": [120, 120], "Flare-1": [120, 120], "ASRAAM": [8, 8], "MBDA Meteor": [32, 32]}}')
    UI.SetThrottle(0.237061)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Typhoon'
    unit.unitName = "RAF Typhoon-4"
    unit.SetPosition(15.454734, 55.414927, 10000.0)
    unit.heading = 87.55
    unit.speed = 334.6
    unit.cost = 50000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'ASRAAM', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MBDA Meteor', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MBDA Meteor', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MBDA Meteor', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '1150 Liter Tank', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '27mm HE', 6)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Flare-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('CruiseEnforcement', 5.000000, -1)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.328280, 0.995423, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
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
    BB.Write('ClimbInitAlt', '10000.0')
    BB.Write('ClimbInitThrottle', '0.230959996581')
    BB.Write('Cruise_Speed_Only', '1')
    BB.Write('Home', 'Siauliai AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "Alt+": 19810.0, "Speed+": 500, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 4, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 4, "MagWeaponList": {"Chaff-1": 0, "AIM-9M": 0, "1150 Liter Tank": 0, "AIM-120C": 0, "AGM-88*": 0, "27mm HE": 0, "GBU-12/B": 0, "Flare-1": 0, "AGM-84C Harpoon": 0, "AIM-9X": 0, "ASRAAM": 0, "GBU-30": 0, "MBDA Meteor": 0}, "Air": 4, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 1, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 0, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"1150 Liter Tank": [4, 4], "27mm HE": [24, 24], "Chaff-1": [120, 120], "Flare-1": [120, 120], "ASRAAM": [8, 8], "MBDA Meteor": [32, 32]}}')
    UI.SetThrottle(0.237061)
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-12"
    unit.SetPosition(28.560486, 56.405424, 9312.5)
    unit.heading = 264.20
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.193168)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-11"
    unit.SetPosition(28.775917, 56.500589, 9403.5)
    unit.heading = 264.20
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.193168)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-10"
    unit.SetPosition(28.714381, 56.293464, 9230.0)
    unit.heading = 264.20
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.193168)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-9"
    unit.SetPosition(29.052885, 56.562184, 9266.5)
    unit.heading = 264.20
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.193168)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-8"
    unit.SetPosition(28.878476, 56.198299, 9200.0)
    unit.heading = 264.20
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.193168)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-7"
    unit.SetPosition(29.022118, 56.366233, 9270.0)
    unit.heading = 264.20
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.193168)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-6"
    unit.SetPosition(29.890635, 58.218299, 9674.0)
    unit.heading = 280.24
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.193168)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-5"
    unit.SetPosition(29.746995, 58.050365, 9717.0)
    unit.heading = 280.24
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.193168)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-4"
    unit.SetPosition(29.921403, 58.414251, 9651.0)
    unit.heading = 280.24
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.193168)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-3"
    unit.SetPosition(29.582900, 58.145533, 9570.5)
    unit.heading = 280.24
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.193168)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-2"
    unit.SetPosition(29.644435, 58.352658, 9662.0)
    unit.heading = 280.24
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.193168)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-24M'
    unit.unitName = "Fencer Bomber-1"
    unit.SetPosition(29.429003, 58.257489, 9683.5)
    unit.heading = 280.24
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3000 liter tank', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'FAB-500', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '23mm AM-23', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.123385)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-12"
    unit.SetPosition(28.599838, 55.810151, 9008.7)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.186961)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-11"
    unit.SetPosition(28.525983, 55.966508, 9082.7)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.186380)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-10"
    unit.SetPosition(28.616282, 55.636425, 8912.5)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.187301)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-9"
    unit.SetPosition(28.337251, 55.697275, 9208.2)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.187021)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-8"
    unit.SetPosition(28.320866, 55.879648, 9092.7)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.186807)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-7"
    unit.SetPosition(28.033639, 55.788431, 9071.3)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.187431)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PMU-1'
    unit.unitName = "S-300 SAM Site"
    unit.SetPosition(26.366544, 53.120178, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '48N6E', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '48N6E', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '48N6E', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '48N6E', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("S-300 SAM Site", '48N6E', 72)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('EngageAllAir', -1.000000, 0)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "MisOffRange": 0, "Alt+": 0, "Sub": 0, "Speed+": 0, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 1, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 0, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"48N6E": 288, "5V55RUD": 0}, "Air": 0, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 0, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 0, "Tasks": {"EngageAllAir": 1, "EngageAll": 1}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 1, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"48N6E": [16, 16]}, "HasThrottle": 0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'A-50'
    unit.unitName = "Mainstay"
    unit.SetPosition(25.461729, 52.975793, 8164.4)
    unit.heading = 90.00
    unit.speed = 300.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.433470, 0.920630, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.469814, 0.925675, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 13700.0, "Sub": 0, "Speed+": 200, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 0, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 0, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {"Nav": 1}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {}, "HasThrottle": 1}')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-21"
    unit.SetPosition(26.308103, 53.541761, 8119.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172953143716')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-22"
    unit.SetPosition(26.227430, 53.509560, 8477.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172970890999')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-23"
    unit.SetPosition(26.368606, 53.511565, 8502.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172972247005')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-18"
    unit.SetPosition(26.321567, 53.475355, 8489.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.17297154665')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-17"
    unit.SetPosition(25.595514, 53.502686, 8196.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172956809402')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-19"
    unit.SetPosition(25.602218, 53.438742, 8118.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.17295306921')
    BB.Write('Home', 'Baranawitschy AB')
    BB.Write('LandTarget', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-20"
    unit.SetPosition(25.521545, 53.472718, 8465.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.17297026515')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-24"
    unit.SetPosition(25.669426, 53.480740, 8133.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172953799367')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-12"
    unit.SetPosition(26.261062, 53.904386, 8483.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172971233726')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-11"
    unit.SetPosition(26.381842, 53.863764, 8327.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172963187099')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-10"
    unit.SetPosition(26.198036, 53.857518, 8443.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172969117761')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-9"
    unit.SetPosition(26.313601, 53.816953, 8583.0)
    unit.heading = 356.63
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172976568341')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-4"
    unit.SetPosition(25.420706, 53.820447, 8535.0)
    unit.heading = 347.91
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172973960638')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-3"
    unit.SetPosition(25.641294, 53.782973, 8402.0)
    unit.heading = 352.41
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172967031598')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-2"
    unit.SetPosition(25.399736, 53.739256, 8591.0)
    unit.heading = 351.87
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172977000475')
    BB.Write('Home', 'Baranawitschy AB')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 19800.0, "Sub": 0, "Speed+": 50, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 0, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77": 0, "R-73M": 0, "Kh-29T": 0, "Chaff-1": 0, "Flare-1": 0, "R-27R": 0, "Kh-31P": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {"JetTakeoff": 1, "EngageAll": 1}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-77": [2, 2], "Chaff-1": [30, 30], "Flare-1": [30, 30], "R-27R": [8, 8]}, "HasThrottle": 1}')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Russian Fighter Wing-1"
    unit.SetPosition(25.552027, 53.714278, 8506.0)
    unit.heading = 351.87
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    UI.AddTask('cruiseclimb', 0.200000, -1)
    BB = UI.GetBlackboardInterface()
    BB.Write('ClimbInitAlt', '10000')
    BB.Write('ClimbInitThrottle', '0.172972410917')
    BB.Write('Home', 'Baranawitschy AB')
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Baranawitschy AB"
    unit.SetPosition(26.050000, 53.100002, -0.0)
    unit.heading = 356.63
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Baranawitschy AB", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Baranawitschy AB", 'Chaff-1', 10050)
    SM.AddToUnitMagazine("Baranawitschy AB", 'Flare-1', 10050)
    SM.AddToUnitMagazine("Baranawitschy AB", 'R-27R', 164)
    SM.AddToUnitMagazine("Baranawitschy AB", 'R-73M', 200)
    SM.AddToUnitMagazine("Baranawitschy AB", 'R-77', 208)
    SM.AddToUnitMagazine("Baranawitschy AB", 'Kh-29T', 228)
    SM.AddToUnitMagazine("Baranawitschy AB", 'Kh-31P', 100)
    SM.AddToUnitMagazine("Baranawitschy AB", '3M80 Moskit', 50)
    SM.AddToUnitMagazine("Baranawitschy AB", 'PRP-50', 300)
    SM.AddToUnitMagazine("Baranawitschy AB", 'PPI-50', 300)
    SM.AddToUnitMagazine("Baranawitschy AB", 'ALE-45 Flare', 50)
    SM.AddToUnitMagazine("Baranawitschy AB", 'ALE-45 Chaff', 50)
    SM.AddToUnitMagazine("Baranawitschy AB", 'FAB-500', 200)
    SM.AddToUnitMagazine("Baranawitschy AB", '23mm AM-23', 200)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "MisOffRange": 0, "Alt+": 0, "Sub": 0, "Speed+": 0, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 1, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 1, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 0, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 1, "Snorkel-": 0, "Launchers": 0, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {}, "Air": 0, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 0, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 0, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {}, "HasThrottle": 0}')
    
    SM.AddUnitToFlightDeck('Baranawitschy AB', 'A-50', 'Russian AEW-2', 1)
    SM.SetFlightDeckUnitLoadout('Baranawitschy AB', 'Russian AEW-2', '')
    
    SM.AddUnitToFlightDeck('Baranawitschy AB', 'A-50', 'Russian AEW-1', 1)
    SM.SetFlightDeckUnitLoadout('Baranawitschy AB', 'Russian AEW-1', '')
    
    SM.AddUnitToFlightDeck('Baranawitschy AB', 'Su-27', 'Russian Fighter Wing-14', 1)
    SM.SetFlightDeckUnitLoadout('Baranawitschy AB', 'Russian Fighter Wing-14', '0 Empty;0 Empty;4 R-27R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Baranawitschy AB', 'Su-27', 'Russian Fighter Wing-13', 1)
    SM.SetFlightDeckUnitLoadout('Baranawitschy AB', 'Russian Fighter Wing-13', '0 Empty;0 Empty;4 R-27R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Baranawitschy AB', 'Su-27', 'Russian Fighter Wing-5', 2)
    SM.SetFlightDeckUnitLoadout('Baranawitschy AB', 'Russian Fighter Wing-5', '0 Empty;0 Empty;4 R-27R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Baranawitschy AB', 'Su-27', 'Russian Fighter Wing-6', 2)
    SM.SetFlightDeckUnitLoadout('Baranawitschy AB', 'Russian Fighter Wing-6', '0 Empty;0 Empty;4 R-27R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Baranawitschy AB', 'Su-27', 'Russian Fighter Wing-7', 2)
    SM.SetFlightDeckUnitLoadout('Baranawitschy AB', 'Russian Fighter Wing-7', '0 Empty;0 Empty;4 R-27R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Baranawitschy AB', 'Su-27', 'Russian Fighter Wing-8', 2)
    SM.SetFlightDeckUnitLoadout('Baranawitschy AB', 'Russian Fighter Wing-8', '0 Empty;0 Empty;4 R-27R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Baranawitschy AB', 'Su-27', 'Russian Fighter Wing-16', 1)
    SM.SetFlightDeckUnitLoadout('Baranawitschy AB', 'Russian Fighter Wing-16', '0 Empty;0 Empty;4 R-27R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Baranawitschy AB', 'Su-27', 'Russian Fighter Wing-15', 1)
    SM.SetFlightDeckUnitLoadout('Baranawitschy AB', 'Russian Fighter Wing-15', '0 Empty;0 Empty;4 R-27R;0 Empty;0 Empty;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Russian AEW-1')
    FP.AddAircraftToMission(mission_id, 'Russian AEW-2')
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m+R3.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.4246745,0.9326387,0.4552912,0.9393101,0.4845328,0.9367947,0.4122996,0.9208270,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4556583, 0.9277698, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4361000, 0.9291120, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.4224569, 1.0342152)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4491211, 0.9234426, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAllAir,RadarRandom')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4254885, 1.0295535, 6000.0, 500.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4319415, 1.0262263, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.4082383, 0.9754587)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4491211, 0.9234426, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAllAir,RadarRandom')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4129033, 0.9711816, 6000.0, 500.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4187946, 0.9678543, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Russian Fighter Wing-5')
    FP.AddAircraftToMission(mission_id, 'Russian Fighter Wing-6')
    FP.AddAircraftToMission(mission_id, 'Russian Fighter Wing-7')
    FP.AddAircraftToMission(mission_id, 'Russian Fighter Wing-8')
    FP.SetMissionLaunchTime(mission_id, '00:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.3855502,0.9666488,0.4355372,0.9753700,0.4369695,0.9665672,0.4004460,0.9583350,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4556583, 0.9277698, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4173470, 0.9619560, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Russian Fighter Wing-13')
    FP.AddAircraftToMission(mission_id, 'Russian Fighter Wing-14')
    FP.AddAircraftToMission(mission_id, 'Russian Fighter Wing-15')
    FP.AddAircraftToMission(mission_id, 'Russian Fighter Wing-16')
    FP.SetMissionLaunchTime(mission_id, '01:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.4107943,1.0267154,0.4415886,1.0341625,0.4510776,1.0312610,0.4086459,1.0201387,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4556583, 0.9277698, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4285190, 1.0245880, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'JYL-1 Radar Post'
    unit.unitName = "AESA Site Rajon Hanzawitschy"
    unit.SetPosition(26.433334, 52.749999, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-6"
    unit.SetPosition(29.238781, 59.071605, 9665.6)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.140210)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-5"
    unit.SetPosition(29.526005, 59.162820, 9372.0)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.188151)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-4"
    unit.SetPosition(29.542392, 58.980448, 9472.8)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.188151)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-3"
    unit.SetPosition(29.821422, 58.919599, 9604.8)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.188151)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-2"
    unit.SetPosition(29.731124, 59.249680, 9168.8)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.188151)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-34'
    unit.unitName = "Fullback Bombers-1"
    unit.SetPosition(29.804978, 59.093320, 9444.8)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 36000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M54E Klub Alfa', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M54E Klub Alfa', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'PPI-50', 48)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'PRP-50', 48)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(10, 0)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 200, "MisOffRange": 0, "Alt+": 15000.0, "Sub": 0, "Speed+": 500, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 1, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 1, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {"R-77*": 0, "KAB-1500L": 0, "KAB-500Kr": 0, "KAB-500R": 0, "3M80 Moskit": 0, "Kh-59MK": 0, "R-73*": 0, "Kh-31P": 0, "PPI-50": 0, "R-27*": 0, "KAB-500L": 0, "3M54E Klub Alfa": 0, "KAB-1500Kr": 0, "PRP-50": 0, "Kh-59M": 0}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {"R-73E": [2, 2], "Kh-31P": [4, 4], "PPI-50": [48, 48], "3M80 Moskit": [1, 1], "PRP-50": [48, 48]}, "HasThrottle": 1}')
    UI.SetThrottle(0.188151)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'A-50'
    unit.unitName = "Guard"
    unit.SetPosition(30.908552, 57.259397, 9430.6)
    unit.heading = 90.00
    unit.speed = 300.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.538203, 1.010179, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.537844, 0.983243, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(1.000000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Escort Flanker-1"
    unit.SetPosition(28.190154, 59.123114, 9604.0)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.205642)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Escort Flanker-2"
    unit.SetPosition(28.415842, 59.270479, 9792.4)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.275955)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Escort Flanker-3"
    unit.SetPosition(28.415842, 59.013966, 9391.6)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.275955)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Escort Flanker-4"
    unit.SetPosition(28.662042, 59.106727, 9629.2)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.275955)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Escort Flanker-5"
    unit.SetPosition(27.487507, 55.806363, 9256.6)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.275955)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Escort Flanker-6"
    unit.SetPosition(27.241306, 55.713602, 9113.2)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.275955)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Escort Flanker-7"
    unit.SetPosition(27.241306, 55.970110, 8968.0)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.275955)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-27'
    unit.unitName = "Escort Flanker-8"
    unit.SetPosition(27.015620, 55.822748, 9059.8)
    unit.heading = 270.00
    unit.speed = 300.0
    unit.cost = 25000004.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'R-27R', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'R-27R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 30)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 30)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.275955)
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Ronneby AB"
    unit.SetPosition(15.259000, 56.266669, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Ronneby AB", 'Fuel', 1000000)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "MisOffRange": 0, "Alt+": 0, "Sub": 0, "Speed+": 0, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 1, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 1, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 0, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 1, "Snorkel-": 0, "Launchers": 0, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {}, "Air": 0, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 0, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 0, "Tasks": {}, "HasOptical": 1, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {}, "HasThrottle": 0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'AEW aircraft'
    unit.unitName = "Swedish AEW"
    unit.SetPosition(16.868394, 55.898050, 10000.0)
    unit.heading = 90.00
    unit.speed = 100.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.307442, 0.984721, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.308875, 0.976804, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.277508, 0.973766, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 100, "MisOffRange": 0, "Alt+": 10000.0, "Sub": 0, "Speed+": 200, "MisDefMisRange": 0, "TrackError": 0, "ROE5": 0, "HasFlightPort": 0, "PermAtkGnd": 0, "RadarMast+": 0, "RadarMast-": 0, "MisDefAirRange": 0, "HasMagazine": 0, "DieselSub": 0, "MisStkRange": 0, "PermAtkMis": 0, "HasAINav": 0, "UnitCount": 1, "HasECM": 0, "PermMisStk": 0, "PermMisOff": 0, "HasTarget": 0, "TargetDatum": 0, "PermMisDefMis": 0, "FixedLand": 0, "Snorkel-": 0, "Launchers": 0, "TargetTrack": 0, "ROE2": 0, "ROE3": 0, "ROE0": 0, "Snorkel+": 0, "HasBombs": 0, "FormModeSprint": 0, "Periscope-": 0, "CanStrafe": 0, "MagWeaponList": {}, "Air": 1, "PeriDeep": 0, "FormLeader": 0, "PermAtkAir": 0, "HasESM": 1, "PermMisUse": 0, "Periscope+": 0, "ROE4": 0, "HasAIWeap": 0, "PermMisDefAir": 0, "FixedWing": 1, "Tasks": {"Nav": 1}, "HasOptical": 0, "HasSonarA": 0, "Depth+": 0, "PermAtkSub": 0, "MobileLand": 0, "Depth-": 0, "HasRadar": 1, "HasSonarP": 0, "FormModePace": 0, "PermAtkShp": 0, "Ship": 0, "ROE1": 0, "TargetSet": 0, "FormMember": 0, "WeaponList": {}, "HasThrottle": 0}')
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Russian Fighter Wing-4')
    goal_temp.AddTarget('Russian Fighter Wing-21')
    goal_temp.AddTarget('Russian Fighter Wing-22')
    goal_temp.AddTarget('Russian Fighter Wing-23')
    goal_temp.AddTarget('Russian Fighter Wing-18')
    goal_temp.AddTarget('Russian Fighter Wing-17')
    goal_temp.AddTarget('Russian Fighter Wing-19')
    goal_temp.AddTarget('Russian Fighter Wing-20')
    goal_temp.AddTarget('Russian Fighter Wing-24')
    goal_temp.AddTarget('Russian Fighter Wing-12')
    goal_temp.AddTarget('Russian Fighter Wing-11')
    goal_temp.AddTarget('Russian Fighter Wing-10')
    goal_temp.AddTarget('Russian Fighter Wing-9')
    goal_temp.AddTarget('Russian Fighter Wing-3')
    goal_temp.AddTarget('Russian Fighter Wing-2')
    goal_temp.AddTarget('Russian Fighter Wing-1')
    goal_temp.SetQuantity(12)
    goal_0_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Siauliai AB')
    goal_temp.AddTarget('Amari AB')
    goal_temp.SetQuantity(2)
    goal_0_1 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(86400.0)
    goal_temp.SetFailTimeout(31556926.0)
    goal_0_2 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Baranawitschy AB')
    goal_temp.SetQuantity(1)
    goal_0_3 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Fullback Bombers-6')
    goal_temp.AddTarget('Fullback Bombers-5')
    goal_temp.AddTarget('Fullback Bombers-4')
    goal_temp.AddTarget('Fullback Bombers-3')
    goal_temp.AddTarget('Fullback Bombers-2')
    goal_temp.AddTarget('Fullback Bombers-1')
    goal_temp.SetQuantity(4)
    goal_0_4 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Fullback Bombers-7')
    goal_temp.AddTarget('Fullback Bombers-12')
    goal_temp.AddTarget('Fullback Bombers-11')
    goal_temp.AddTarget('Fullback Bombers-10')
    goal_temp.AddTarget('Fullback Bombers-9')
    goal_temp.AddTarget('Fullback Bombers-8')
    goal_temp.SetQuantity(4)
    goal_0_5 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Fencer Bomber-1')
    goal_temp.AddTarget('Fencer Bomber-6')
    goal_temp.AddTarget('Fencer Bomber-5')
    goal_temp.AddTarget('Fencer Bomber-4')
    goal_temp.AddTarget('Fencer Bomber-3')
    goal_temp.AddTarget('Fencer Bomber-2')
    goal_temp.SetQuantity(4)
    goal_0_6 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Fencer Bomber-12')
    goal_temp.AddTarget('Fencer Bomber-11')
    goal_temp.AddTarget('Fencer Bomber-10')
    goal_temp.AddTarget('Fencer Bomber-9')
    goal_temp.AddTarget('Fencer Bomber-8')
    goal_temp.AddTarget('Fencer Bomber-7')
    goal_temp.SetQuantity(4)
    goal_0_7 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_0_0)
    goal_temp.AddGoal(goal_0_1)
    goal_temp.AddGoal(goal_0_2)
    goal_temp.AddGoal(goal_0_3)
    goal_temp.AddGoal(goal_0_4)
    goal_temp.AddGoal(goal_0_5)
    goal_temp.AddGoal(goal_0_6)
    goal_temp.AddGoal(goal_0_7)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Siauliai AB')
    goal_temp.AddTarget('Amari AB')
    goal_temp.SetQuantity(1)
    goal_1_0 = goal_temp

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(86400.0)
    goal_temp.SetFailTimeout(31556926.0)
    goal_1_1 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_1_0)
    goal_temp.AddGoal(goal_1_1)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Alliance 3 goals
    ##############################

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
