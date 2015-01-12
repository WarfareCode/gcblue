# Created on 01/09/15 07:27:48
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Operation Odyssey Dawn\n\nMarch, 2011.\n\nUS led Coalition Forces start their attacks on Libyan bases. \n\nThis scenario models the first multi-axis attacks.\n\nAre you up to the challenge to coordinate your multinational forces?\n\nYou command venerable B-2 bombers as well as modern fighter bombers \nlike the Rafale, Tomahawk surface and sub-surface shooters.\n\nGood Luck, Commander! \n\n\n\n\n""")
    SM.SetScenarioName("""Operation Odyssey Dawn""")
    SM.CreateAlliance(1, 'USA')
    SM.SetAllianceDefaultCountry(1, 'USA')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'Libya')
    SM.SetAllianceDefaultCountry(2, 'Libya')
    SM.SetAlliancePlayable(2, 0)
    SM.CreateAlliance(3, 'Neutrals')
    SM.SetAllianceDefaultCountry(3, 'Neutrals')
    SM.SetAlliancePlayable(3, 0)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(1)

    SM.SetDateTime(2011,3,20,4,0,0)
    SM.SetStartTheater(9.616665, 35.883335) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(2)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """TASKING ORDERS\n\nYour job is to support the Libyan Revolution by neutralizing the Libyan \nAir Force, destroying the Libyan Navy and decapitating the Libyan air \ndefense.\n\n\nINTELLIGENCE\n\nThe Libyans expect your attacks. They will throw everything they have \nagainst you. All Libyan SAM sites are on red alert, as well as the Libyan \nNavy and Air Force are. \n\nWe do not know for sure if their subs are really out of action and if those \nsix to eight modern Russian fighter bombers ordered in 2010 have not \nyet been delivered. \n\n\nMISSION\n\nYou need to destroy the following primary targets:\n\n1. The Comm Center near Tripolis\n\n2. The Chemical Plant located at approx 32 N 12 East \n\n3. The two SA-10 Sites guarding that plant \n\n4. All eight Libyan SA-5 Sites\n\n5. Derna Army HQ\n\n6. Brega Army HQ\n\nYou may not lose a single sub or ship. \n\nEXECUTION\n\nBe careful. Act coordinated and do not forget that any loss of a ship or \nsubmarine imposes grave political problems.\n\nYou have 12 hours to achieve Your goals.\n\nCOMMAND AND SIGNAL\n\nUSS Mount Whitney\n\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """TASKING ORDERS:\n\n\nNO ADDITIONAL INTELLIGENCE AVAILABLE.\n""")

    ####################
    SM.SetSimpleBriefing(3, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Akrotiri AB"
    unit.SetPosition(32.975042, 34.593624, 10.0)
    unit.heading = 287.73
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Akrotiri AB", 'Fuel', 9000000)
    SM.AddToUnitMagazine("Akrotiri AB", '20mm PGU', 1603)
    SM.AddToUnitMagazine("Akrotiri AB", '600 gallon tank', 40)
    SM.AddToUnitMagazine("Akrotiri AB", 'AGM-65D', 55)
    SM.AddToUnitMagazine("Akrotiri AB", 'AGM-84F Harpoon', 41)
    SM.AddToUnitMagazine("Akrotiri AB", 'AGM-84H SLAM-ER', 41)
    SM.AddToUnitMagazine("Akrotiri AB", 'AGM-88C', 55)
    SM.AddToUnitMagazine("Akrotiri AB", 'AIM-120C5', 184)
    SM.AddToUnitMagazine("Akrotiri AB", 'AIM-120C7', 653)
    SM.AddToUnitMagazine("Akrotiri AB", 'AIM-120D', 559)
    SM.AddToUnitMagazine("Akrotiri AB", 'AIM-9P4', 69)
    SM.AddToUnitMagazine("Akrotiri AB", 'AIM-9X', 67)
    SM.AddToUnitMagazine("Akrotiri AB", 'Chaff-1', 2091)
    SM.AddToUnitMagazine("Akrotiri AB", 'Flare-1', 2091)
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
    
    SM.AddUnitToFlightDeck('Akrotiri AB', 'F-22', 'Raptor-1', 2)
    SM.SetFlightDeckUnitLoadout('Akrotiri AB', 'Raptor-1', '2 AIM-120D;2 AIM-120D;2 AIM-9X;2 AIM-120D;4 AIM-120D;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Akrotiri AB', 'F-22', 'Raptor-2', 2)
    SM.SetFlightDeckUnitLoadout('Akrotiri AB', 'Raptor-2', '2 AIM-120D;2 AIM-120D;2 AIM-9X;2 AIM-120D;4 AIM-120D;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Akrotiri AB', 'F-22', 'Raptor-3', 2)
    SM.SetFlightDeckUnitLoadout('Akrotiri AB', 'Raptor-3', '2 AIM-120D;2 AIM-120D;2 AIM-9X;2 AIM-120D;4 AIM-120D;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Akrotiri AB', 'F-22', 'Raptor-4', 2)
    SM.SetFlightDeckUnitLoadout('Akrotiri AB', 'Raptor-4', '2 AIM-120D;2 AIM-120D;2 AIM-9X;2 AIM-120D;4 AIM-120D;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Akrotiri AB', 'F-22', 'Raptor-5', 2)
    SM.SetFlightDeckUnitLoadout('Akrotiri AB', 'Raptor-5', '2 AIM-120D;2 AIM-120D;2 AIM-9X;2 AIM-120D;4 AIM-120D;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Akrotiri AB', 'F-22', 'Raptor-6', 2)
    SM.SetFlightDeckUnitLoadout('Akrotiri AB', 'Raptor-6', '2 AIM-120D;2 AIM-120D;2 AIM-9X;2 AIM-120D;4 AIM-120D;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Akrotiri AB', 'F-22', 'Raptor-7', 2)
    SM.SetFlightDeckUnitLoadout('Akrotiri AB', 'Raptor-7', '2 AIM-120D;2 AIM-120D;2 AIM-9X;2 AIM-120D;4 AIM-120D;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Akrotiri AB', 'F-22', 'Raptor-8', 2)
    SM.SetFlightDeckUnitLoadout('Akrotiri AB', 'Raptor-8', '2 AIM-120D;2 AIM-120D;2 AIM-9X;2 AIM-120D;4 AIM-120D;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Akrotiri AB', 'F-22', 'Raptor-9', 1)
    SM.SetFlightDeckUnitLoadout('Akrotiri AB', 'Raptor-9', '2 AIM-120D;2 AIM-120D;2 AIM-9X;2 AIM-120D;4 AIM-120D;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Akrotiri AB', 'F-22', 'Raptor-10', 1)
    SM.SetFlightDeckUnitLoadout('Akrotiri AB', 'Raptor-10', '2 AIM-120D;2 AIM-120D;2 AIM-9X;2 AIM-120D;4 AIM-120D;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Konya AB"
    unit.SetPosition(32.554911, 37.966761, 10.0)
    unit.heading = 196.67
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Konya AB", 'Fuel', 8000000)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Konya AB', 'E-737 AEW&C', 'AEW (US)-1', 2)
    SM.SetFlightDeckUnitLoadout('Konya AB', 'AEW (US)-1', '30 Chaff-1;30 Chaff-1;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Konya AB', 'E-737 AEW&C', 'AEW (US)-2', 2)
    SM.SetFlightDeckUnitLoadout('Konya AB', 'AEW (US)-2', '30 Chaff-1;30 Chaff-1;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Konya AB', 'KC-767A', 'Refuel (US)-1', 2)
    SM.SetFlightDeckUnitLoadout('Konya AB', 'Refuel (US)-1', '')
    
    SM.AddUnitToFlightDeck('Konya AB', 'KC-767A', 'Refuel (US)-2', 2)
    SM.SetFlightDeckUnitLoadout('Konya AB', 'Refuel (US)-2', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Aktio AB"
    unit.SetPosition(20.766360, 38.925966, 10.0)
    unit.heading = 248.07
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Aktio AB", 'Fuel', 7000000)
    SM.AddToUnitMagazine("Aktio AB", '1400 liter tank', 6)
    SM.AddToUnitMagazine("Aktio AB", '20mm PGU', 544)
    SM.AddToUnitMagazine("Aktio AB", '20mm PGU-28/B', 544)
    SM.AddToUnitMagazine("Aktio AB", 'AGM-88C', 29)
    SM.AddToUnitMagazine("Aktio AB", 'AIM-120C5', 19)
    SM.AddToUnitMagazine("Aktio AB", 'AIM-120C7', 67)
    SM.AddToUnitMagazine("Aktio AB", 'AIM-120D', 58)
    SM.AddToUnitMagazine("Aktio AB", 'AIM-9P4', 44)
    SM.AddToUnitMagazine("Aktio AB", 'AIM-9X', 43)
    SM.AddToUnitMagazine("Aktio AB", 'Chaff-1', 887)
    SM.AddToUnitMagazine("Aktio AB", 'FPU-6', 18)
    SM.AddToUnitMagazine("Aktio AB", 'FPU-8', 18)
    SM.AddToUnitMagazine("Aktio AB", 'Flare-1', 887)
    SM.AddToUnitMagazine("Aktio AB", 'GBU-10/B', 8)
    SM.AddToUnitMagazine("Aktio AB", 'GBU-12/B', 22)
    SM.AddToUnitMagazine("Aktio AB", 'GBU-16/B', 17)
    SM.AddToUnitMagazine("Aktio AB", 'GBU-24/B', 8)
    SM.AddToUnitMagazine("Aktio AB", 'GBU-24B/B', 8)
    SM.AddToUnitMagazine("Aktio AB", 'GBU-27', 8)
    SM.AddToUnitMagazine("Aktio AB", 'GBU-28B/B', 14)
    SM.AddToUnitMagazine("Aktio AB", 'GBU-31A(v)2', 4)
    SM.AddToUnitMagazine("Aktio AB", 'GBU-31C(v)4', 4)
    SM.AddToUnitMagazine("Aktio AB", 'GBU-32A(v)2', 6)
    SM.AddToUnitMagazine("Aktio AB", 'GBU-32C(v)4', 6)
    SM.AddToUnitMagazine("Aktio AB", 'Mk-81', 79)
    SM.AddToUnitMagazine("Aktio AB", 'Mk-82', 85)
    SM.AddToUnitMagazine("Aktio AB", 'Mk-83', 44)
    SM.AddToUnitMagazine("Aktio AB", 'Mk-84', 19)
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
    
    SM.AddUnitToFlightDeck('Aktio AB', 'CF-18 p.I', 'Hornet (Canada)-1', 2)
    SM.SetFlightDeckUnitLoadout('Aktio AB', 'Hornet (Canada)-1', '1 1400 liter tank;2 AIM-120C7;2 AIM-120C7;2 AIM-120C7;2 AIM-9X;46 20mm PGU;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Aktio AB', 'CF-18 p.I', 'Hornet (Canada)-2', 2)
    SM.SetFlightDeckUnitLoadout('Aktio AB', 'Hornet (Canada)-2', '1 1400 liter tank;2 AIM-120C7;2 AIM-120C7;2 AIM-120C7;2 AIM-9X;46 20mm PGU;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Aktio AB', 'CF-18 p.I', 'Hornet (Canada)-3', 2)
    SM.SetFlightDeckUnitLoadout('Aktio AB', 'Hornet (Canada)-3', '1 1400 liter tank;2 AIM-120C7;2 AIM-120C7;2 AIM-120C7;2 AIM-9X;46 20mm PGU;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Aktio AB', 'CF-18 p.I', 'Hornet (Canada)-4', 2)
    SM.SetFlightDeckUnitLoadout('Aktio AB', 'Hornet (Canada)-4', '1 1400 liter tank;2 AIM-120C7;2 AIM-120C7;2 AIM-120C7;2 AIM-9X;46 20mm PGU;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Aktio AB', 'CF-18 p.I', 'Hornet (Canada)-5', 2)
    SM.SetFlightDeckUnitLoadout('Aktio AB', 'Hornet (Canada)-5', '1 1400 liter tank;2 AIM-120C7;2 AIM-120C7;2 AIM-120C7;2 AIM-9X;46 20mm PGU;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Aktio AB', 'CF-18 p.I', 'Hornet (Canada)-6', 2)
    SM.SetFlightDeckUnitLoadout('Aktio AB', 'Hornet (Canada)-6', '1 1400 liter tank;2 AIM-120C7;2 AIM-120C7;2 AIM-120C7;2 AIM-9X;46 20mm PGU;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Aktio AB', 'KC-130F', 'Transport (Canada)-1', 2)
    SM.SetFlightDeckUnitLoadout('Aktio AB', 'Transport (Canada)-1', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Souda AB"
    unit.SetPosition(24.166058, 35.526452, 10.0)
    unit.heading = 111.67
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Souda AB", 'Fuel', 6000000)
    SM.AddToUnitMagazine("Souda AB", '20mm PGU', 453)
    SM.AddToUnitMagazine("Souda AB", '300 gallon wing tank', 6)
    SM.AddToUnitMagazine("Souda AB", '370 gallon wing tank', 12)
    SM.AddToUnitMagazine("Souda AB", 'AGM-65J', 23)
    SM.AddToUnitMagazine("Souda AB", 'AGM-65K', 23)
    SM.AddToUnitMagazine("Souda AB", 'AGM-84F Harpoon', 4)
    SM.AddToUnitMagazine("Souda AB", 'AGM-84H SLAM-ER', 4)
    SM.AddToUnitMagazine("Souda AB", 'AGM-88C', 19)
    SM.AddToUnitMagazine("Souda AB", 'AIM-120C5', 15)
    SM.AddToUnitMagazine("Souda AB", 'AIM-120C7', 56)
    SM.AddToUnitMagazine("Souda AB", 'AIM-120D', 48)
    SM.AddToUnitMagazine("Souda AB", 'AIM-9P4', 37)
    SM.AddToUnitMagazine("Souda AB", 'AIM-9X', 35)
    SM.AddToUnitMagazine("Souda AB", 'Chaff-1', 740)
    SM.AddToUnitMagazine("Souda AB", 'Flare-1', 740)
    SM.AddToUnitMagazine("Souda AB", 'GBU-10/B', 9)
    SM.AddToUnitMagazine("Souda AB", 'GBU-12/B', 37)
    SM.AddToUnitMagazine("Souda AB", 'GBU-15/B', 17)
    SM.AddToUnitMagazine("Souda AB", 'GBU-24/B', 9)
    SM.AddToUnitMagazine("Souda AB", 'GBU-24B/B', 9)
    SM.AddToUnitMagazine("Souda AB", 'GBU-31A(v)2', 4)
    SM.AddToUnitMagazine("Souda AB", 'GBU-31C(v)4', 4)
    SM.AddToUnitMagazine("Souda AB", 'GBU-32A(v)2', 7)
    SM.AddToUnitMagazine("Souda AB", 'GBU-32C(v)4', 7)
    SM.AddToUnitMagazine("Souda AB", 'GBU-39 SDB', 20)
    SM.AddToUnitMagazine("Souda AB", 'Mk 16 Zuni FFAR', 157)
    SM.AddToUnitMagazine("Souda AB", 'Mk 71 Zuni WAFAR', 157)
    SM.AddToUnitMagazine("Souda AB", 'Mk-82', 93)
    SM.AddToUnitMagazine("Souda AB", 'Mk-83', 33)
    SM.AddToUnitMagazine("Souda AB", 'Mk-84', 12)
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
    
    SM.AddUnitToFlightDeck('Souda AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Greece)-1', 2)
    SM.SetFlightDeckUnitLoadout('Souda AB', 'Falcon (Greece)-1', '2 AIM-9X;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Souda AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Greece)-2', 2)
    SM.SetFlightDeckUnitLoadout('Souda AB', 'Falcon (Greece)-2', '2 AIM-9X;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Souda AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Greece)-3', 2)
    SM.SetFlightDeckUnitLoadout('Souda AB', 'Falcon (Greece)-3', '2 AIM-9X;2 AIM-120C7;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Souda AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Greece)-4', 2)
    SM.SetFlightDeckUnitLoadout('Souda AB', 'Falcon (Greece)-4', '2 AIM-9X;2 AIM-120C7;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Souda AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Greece)-5', 2)
    SM.SetFlightDeckUnitLoadout('Souda AB', 'Falcon (Greece)-5', '2 AIM-120C7;2 AGM-88C;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Souda AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Greece)-6', 2)
    SM.SetFlightDeckUnitLoadout('Souda AB', 'Falcon (Greece)-6', '2 AIM-120C7;2 AGM-88C;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Sevilla-Moron AB"
    unit.SetPosition(-5.610558, 37.187602, 10.0)
    unit.heading = 19.67
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'Fuel', 5000000)
    SM.AddToUnitMagazine("Sevilla-Moron AB", '1400 liter tank', 8)
    SM.AddToUnitMagazine("Sevilla-Moron AB", '20mm PGU', 744)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'AGM-65J', 48)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'AGM-65K', 48)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'AGM-84F Harpoon', 12)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'AGM-88C', 40)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'AIM-120C5', 26)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'AIM-120C7', 92)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'AIM-120D', 78)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'AIM-9P4', 60)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'AIM-9X', 58)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'Chaff-1', 1212)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'FPU-6', 24)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'FPU-8', 24)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'Flare-1', 1212)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'GBU-10/B', 12)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'GBU-12/B', 30)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'GBU-16/B', 24)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'GBU-24/B', 12)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'GBU-24B/B', 12)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'GBU-27', 12)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'GBU-28B/B', 20)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'GBU-31A(v)2', 6)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'GBU-31C(v)4', 6)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'GBU-32A(v)2', 14)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'GBU-32C(v)4', 14)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'Mk-81', 108)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'Mk-82', 116)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'Mk-83', 60)
    SM.AddToUnitMagazine("Sevilla-Moron AB", 'Mk-84', 26)
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
    
    SM.AddUnitToFlightDeck('Sevilla-Moron AB', 'F/A-18C', 'Hornet (Spain)-1', 2)
    SM.SetFlightDeckUnitLoadout('Sevilla-Moron AB', 'Hornet (Spain)-1', '1 1400 liter tank;2 AIM-120C7;4 AGM-65J;4 AGM-65J;2 AIM-9X;6 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Sevilla-Moron AB', 'F/A-18C', 'Hornet (Spain)-2', 2)
    SM.SetFlightDeckUnitLoadout('Sevilla-Moron AB', 'Hornet (Spain)-2', '1 1400 liter tank;2 AIM-120C7;4 AGM-65J;4 AGM-65J;2 AIM-9X;6 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Sevilla-Moron AB', 'F/A-18C', 'Hornet (Spain)-3', 2)
    SM.SetFlightDeckUnitLoadout('Sevilla-Moron AB', 'Hornet (Spain)-3', '1 1400 liter tank;2 AIM-120C7;4 AGM-65J;4 AGM-65J;2 AIM-9X;6 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Sevilla-Moron AB', 'F/A-18C', 'Hornet (Spain)-4', 2)
    SM.SetFlightDeckUnitLoadout('Sevilla-Moron AB', 'Hornet (Spain)-4', '1 1400 liter tank;2 AIM-120C7;4 AGM-65J;4 AGM-65J;2 AIM-9X;6 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Sevilla-Moron AB', 'KC-767A', 'Refuel (Spain)-1', 2)
    SM.SetFlightDeckUnitLoadout('Sevilla-Moron AB', 'Refuel (Spain)-1', '')
    
    SM.AddUnitToFlightDeck('Sevilla-Moron AB', 'E-3D/F', 'Recce (Spain)-1', 2)
    SM.SetFlightDeckUnitLoadout('Sevilla-Moron AB', 'Recce (Spain)-1', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'CVN-65 (Enterprise) USS Enterprise'
    unit.unitName = "USS Enterprise"
    unit.SetPosition(35.181895, 26.373076, 0.0)
    unit.heading = -42.51
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-116B RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-116B RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-162D', 16)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-162D', 16)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm mark 244-0 ELC', 97)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Enterprise", 'Fuel', 4000000)
    SM.AddToUnitMagazine("USS Enterprise", '120 gallon tank', 19)
    SM.AddToUnitMagazine("USS Enterprise", '1400 liter tank', 52)
    SM.AddToUnitMagazine("USS Enterprise", '20mm PGU', 2578)
    SM.AddToUnitMagazine("USS Enterprise", '20mm PGU-28/B', 2578)
    SM.AddToUnitMagazine("USS Enterprise", '20mm mark 244-0 ELC', 1227)
    SM.AddToUnitMagazine("USS Enterprise", '300 gallon tank', 33)
    SM.AddToUnitMagazine("USS Enterprise", 'AGM-65B', 201)
    SM.AddToUnitMagazine("USS Enterprise", 'AGM-65D', 201)
    SM.AddToUnitMagazine("USS Enterprise", 'AGM-65J', 201)
    SM.AddToUnitMagazine("USS Enterprise", 'AGM-65K', 201)
    SM.AddToUnitMagazine("USS Enterprise", 'AGM-84F Harpoon', 56)
    SM.AddToUnitMagazine("USS Enterprise", 'AGM-84H SLAM-ER', 56)
    SM.AddToUnitMagazine("USS Enterprise", 'AGM-88C', 210)
    SM.AddToUnitMagazine("USS Enterprise", 'AIM-120C5', 105)
    SM.AddToUnitMagazine("USS Enterprise", 'AIM-120C7', 375)
    SM.AddToUnitMagazine("USS Enterprise", 'AIM-120D', 321)
    SM.AddToUnitMagazine("USS Enterprise", 'AIM-132 ASRAAM', 139)
    SM.AddToUnitMagazine("USS Enterprise", 'AIM-9X', 238)
    SM.AddToUnitMagazine("USS Enterprise", 'Chaff-1', 4520)
    SM.AddToUnitMagazine("USS Enterprise", 'DICASS (100) Sonobuoy', 43)
    SM.AddToUnitMagazine("USS Enterprise", 'DICASS (105) Sonobuoy', 156)
    SM.AddToUnitMagazine("USS Enterprise", 'DIFAR (100) Sonobuoy', 86)
    SM.AddToUnitMagazine("USS Enterprise", 'DIFAR (105) Sonobuoy', 312)
    SM.AddToUnitMagazine("USS Enterprise", 'FPU-6', 158)
    SM.AddToUnitMagazine("USS Enterprise", 'FPU-8', 158)
    SM.AddToUnitMagazine("USS Enterprise", 'Flare-1', 4520)
    SM.AddToUnitMagazine("USS Enterprise", 'GBU-10/B', 56)
    SM.AddToUnitMagazine("USS Enterprise", 'GBU-12/B', 126)
    SM.AddToUnitMagazine("USS Enterprise", 'GBU-16/B', 100)
    SM.AddToUnitMagazine("USS Enterprise", 'GBU-24/B', 56)
    SM.AddToUnitMagazine("USS Enterprise", 'GBU-24B/B', 56)
    SM.AddToUnitMagazine("USS Enterprise", 'GBU-27', 56)
    SM.AddToUnitMagazine("USS Enterprise", 'GBU-28B/B', 84)
    SM.AddToUnitMagazine("USS Enterprise", 'GBU-31A(v)2', 28)
    SM.AddToUnitMagazine("USS Enterprise", 'GBU-31C(v)4', 28)
    SM.AddToUnitMagazine("USS Enterprise", 'GBU-32A(v)2', 62)
    SM.AddToUnitMagazine("USS Enterprise", 'GBU-32C(v)4', 62)
    SM.AddToUnitMagazine("USS Enterprise", 'Mk-46 Mod5', 25)
    SM.AddToUnitMagazine("USS Enterprise", 'Mk-50', 26)
    SM.AddToUnitMagazine("USS Enterprise", 'Mk-54', 26)
    SM.AddToUnitMagazine("USS Enterprise", 'Mk-81', 441)
    SM.AddToUnitMagazine("USS Enterprise", 'Mk-82', 479)
    SM.AddToUnitMagazine("USS Enterprise", 'Mk-83', 252)
    SM.AddToUnitMagazine("USS Enterprise", 'Mk-84', 109)
    SM.AddToUnitMagazine("USS Enterprise", 'RIM-116B RAM', 159)
    SM.AddToUnitMagazine("USS Enterprise", 'RIM-162D', 121)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.599534, 0.479442, 0.000000, 0.000000)
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
    BB.Write('InvMulti', '1')
    BB.Write('MagGenAllowNukes', '1')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"RIM-116A RAM": 0, "RIM-7F": 0, "RIM-7P(v1)": 0, "RIM-7E": 0, "20mm mark 244-0 ELC": 2454, "RIM-116B RAM": 318, "RIM-7H": 0, "ASPIDE-1A": 0, "RIM-7M(v1)": 0, "RIM-162D": 242}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 1}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"RIM-116B RAM": [42, 42], "RIM-162D": [32, 32], "20mm mark 244-0 ELC": [194, 194]}}')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 1', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;4 AGM-65J;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 2', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;4 AGM-65J;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 3', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;4 AGM-65J;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 4', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;4 AGM-65J;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 5', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;4 AGM-65J;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 6', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;4 AGM-65J;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 7', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;4 AGM-65J;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 8', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;4 AGM-65J;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 9', '1 1400 liter tank;2 AIM-120D;2 GBU-32C(v)4;2 GBU-32C(v)4;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 10', '1 1400 liter tank;2 AIM-120D;2 GBU-32C(v)4;2 GBU-32C(v)4;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 11', '1 1400 liter tank;2 AIM-120D;2 GBU-32C(v)4;2 GBU-32C(v)4;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18E', 'Dog 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dog 12', '1 1400 liter tank;2 AIM-120D;2 GBU-32C(v)4;2 GBU-32C(v)4;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 1', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;2 GBU-31C(v)4;0 Empty;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 2', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;2 GBU-31C(v)4;0 Empty;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 3', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;2 GBU-31C(v)4;0 Empty;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 4', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;2 GBU-31C(v)4;0 Empty;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 5', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;2 GBU-31C(v)4;0 Empty;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 6', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;2 GBU-31C(v)4;0 Empty;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 7', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;2 GBU-31C(v)4;0 Empty;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 8', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;2 GBU-31C(v)4;0 Empty;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 9', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;2 GBU-31C(v)4;0 Empty;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 10', '1 1400 liter tank;2 AIM-120D;2 AGM-88C;2 GBU-31C(v)4;0 Empty;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 11', '1 1400 liter tank;2 AIM-120D;2 GBU-32A(v)2;2 GBU-32A(v)2;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18F', 'Victory 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Victory 12', '1 1400 liter tank;2 AIM-120D;2 GBU-32A(v)2;2 GBU-32A(v)2;4 AGM-65J;2 AIM-9X;46 20mm PGU;25 Chaff-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 1', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 2', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 3', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 4', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 5', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 6', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 7', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 8', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 9', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 10', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 11', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Ram 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Ram 12', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 1', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 2', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 3', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 4', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 5', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 6', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 7', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 8', '1 1400 liter tank;2 AIM-120D;2 AIM-120D;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 9', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 10', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 11', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'F/A-18C', 'Cat 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Cat 12', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AIM-120D;2 AIM-9X;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'EA-6B', 'Patriot 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Patriot 1', '2 AGM-88C;2 AGM-88C;1 Mk-84;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'EA-6B', 'Patriot 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Patriot 2', '2 AGM-88C;2 AGM-88C;1 Mk-84;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'EA-6B', 'Patriot 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Patriot 3', '2 AGM-88C;2 AGM-88C;1 Mk-84;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'EA-6B', 'Patriot 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Patriot 4', '2 AGM-88C;2 AGM-88C;1 Mk-84;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'EA-6B', 'Patriot 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Patriot 5', '2 AGM-88C;2 AGM-88C;1 Mk-84;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'EA-6B', 'Patriot 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Patriot 6', '2 AGM-88C;2 AGM-88C;1 Mk-84;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'E-2C 2000 NP', 'Bluetails 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Bluetails 1', '')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'E-2C 2000 NP', 'Bluetails 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Bluetails 2', '')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'E-2C 2000 NP', 'Bluetails 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Bluetails 3', '')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'E-2C 2000 NP', 'Bluetails 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Bluetails 4', '')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'SH-60F', 'Dipper 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dipper 1', '1 Mk-54;1 Mk-54;1 Mk-54;30 Flare-1;30 Chaff-1;5 DICASS (105) Sonobuoy;10 DICASS (105) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'SH-60F', 'Dipper 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dipper 2', '1 Mk-54;1 Mk-54;1 Mk-54;30 Flare-1;30 Chaff-1;5 DICASS (105) Sonobuoy;10 DICASS (105) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'SH-60F', 'Dipper 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dipper 3', '1 Mk-54;1 Mk-54;1 Mk-54;30 Flare-1;30 Chaff-1;5 DICASS (105) Sonobuoy;10 DICASS (105) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'SH-60F', 'Dipper 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dipper 4', '1 Mk-54;1 Mk-54;1 Mk-54;30 Flare-1;30 Chaff-1;5 DICASS (105) Sonobuoy;10 DICASS (105) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'SH-60F', 'Dipper 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dipper 5', '1 Mk-54;1 120 gallon tank;1 Mk-54;30 Flare-1;30 Chaff-1;5 DICASS (105) Sonobuoy;10 DICASS (105) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'SH-60F', 'Dipper 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Dipper 6', '1 Mk-54;1 120 gallon tank;1 Mk-54;30 Flare-1;30 Chaff-1;5 DICASS (105) Sonobuoy;10 DICASS (105) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'C-2A', 'Rawhide 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Rawhide 1', '')
    
    SM.AddUnitToFlightDeck('USS Enterprise', 'C-2A', 'Rawhide 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Enterprise', 'Rawhide 2', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Trapani-Birgi AB"
    unit.SetPosition(12.498060, 37.905370, 10.0)
    unit.heading = 127.43
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'Fuel', 6000000)
    SM.AddToUnitMagazine("Trapani-Birgi AB", '20mm PGU', 908)
    SM.AddToUnitMagazine("Trapani-Birgi AB", '300 gallon wing tank', 10)
    SM.AddToUnitMagazine("Trapani-Birgi AB", '370 gallon wing tank', 20)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'AGM-65J', 47)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'AGM-65K', 47)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'AGM-88C', 39)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'AIM-120C5', 31)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'AIM-120C7', 113)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'AIM-120D', 97)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'AIM-9P4', 74)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'AIM-9X', 71)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'Chaff-1', 1480)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'Flare-1', 1480)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'GBU-10/B', 19)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'GBU-12/B', 74)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'GBU-15/B', 35)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'GBU-24/B', 19)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'GBU-24B/B', 19)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'GBU-31A(v)2', 9)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'GBU-31C(v)4', 9)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'GBU-32A(v)2', 14)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'GBU-32C(v)4', 14)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'GBU-39 SDB', 41)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'Mk 16 Zuni FFAR', 315)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'Mk 71 Zuni WAFAR', 315)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'Mk-82', 186)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'Mk-83', 66)
    SM.AddToUnitMagazine("Trapani-Birgi AB", 'Mk-84', 25)
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
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Denmark)-1', 2)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Falcon (Denmark)-1', '2 AIM-9X;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Denmark)-2', 2)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Falcon (Denmark)-2', '2 AIM-9X;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Denmark)-3', 2)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Falcon (Denmark)-3', '2 AIM-9X;2 AIM-120C7;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Denmark)-4', 2)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Falcon (Denmark)-4', '2 AIM-9X;2 AIM-120C7;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Norway)-1', 2)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Falcon (Norway)-1', '2 AIM-9X;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Norway)-2', 2)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Falcon (Norway)-2', '2 AIM-9X;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Norway)-3', 2)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Falcon (Norway)-3', '2 AIM-9X;2 AIM-120C7;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Norway)-4', 2)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Falcon (Norway)-4', '2 AIM-9X;2 AIM-120C7;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Norway)-5', 1)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Falcon (Norway)-5', '2 AIM-120C7;2 AGM-88C;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Norway)-6', 1)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Falcon (Norway)-6', '2 AIM-120C7;2 AGM-88C;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'KC-130F', 'Transport (Norway)-1', 1)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Transport (Norway)-1', '')
    
    SM.AddUnitToFlightDeck('Trapani-Birgi AB', 'KC-130F', 'Transport (Denmark)-1', 1)
    SM.SetFlightDeckUnitLoadout('Trapani-Birgi AB', 'Transport (Denmark)-1', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Catania-Sigonella AB"
    unit.SetPosition(14.934217, 37.400209, 10.0)
    unit.heading = 98.36
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'Fuel', 5000000)
    SM.AddToUnitMagazine("Catania-Sigonella AB", '1150 Liter Tank', 10)
    SM.AddToUnitMagazine("Catania-Sigonella AB", '20mm PGU', 915)
    SM.AddToUnitMagazine("Catania-Sigonella AB", '20mm PGU-28/B', 915)
    SM.AddToUnitMagazine("Catania-Sigonella AB", '27mm BK27 27x145mm', 695)
    SM.AddToUnitMagazine("Catania-Sigonella AB", '300 gallon wing tank', 6)
    SM.AddToUnitMagazine("Catania-Sigonella AB", '370 gallon wing tank', 12)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AGM-65B', 47)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AGM-65D', 47)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AGM-65J', 47)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AGM-65K', 47)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AGM-84F Harpoon', 9)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AGM-84H SLAM-ER', 9)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AGM-88C', 139)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AIM-120C5', 32)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AIM-120C7', 114)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AIM-120D', 97)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AIM-9P4', 74)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'AIM-9X', 193)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'Chaff-1', 3982)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'Flare-1', 3982)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'GBU-10/B', 19)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'GBU-12/B', 174)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'GBU-15/B', 35)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'GBU-24/B', 19)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'GBU-24B/B', 19)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'GBU-30', 79)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'GBU-31A(v)2', 9)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'GBU-31C(v)4', 9)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'GBU-32A(v)2', 14)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'GBU-32C(v)4', 14)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'GBU-39 SDB', 41)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'MBDA Meteor', 217)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'Mk 16 Zuni FFAR', 318)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'Mk 71 Zuni WAFAR', 318)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'Mk-82', 188)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'Mk-83', 67)
    SM.AddToUnitMagazine("Catania-Sigonella AB", 'Mk-84', 25)
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
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Belgium)-1', 2)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Falcon (Belgium)-1', '2 AIM-9X;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Belgium)-2', 2)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Falcon (Belgium)-2', '2 AIM-9X;2 AIM-120C7;2 AIM-120C7;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Belgium)-3', 2)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Falcon (Belgium)-3', '2 AIM-9X;2 AIM-120C7;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Belgium)-4', 2)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Falcon (Belgium)-4', '2 AIM-9X;2 AIM-120C7;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Belgium)-5', 2)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Falcon (Belgium)-5', '2 AIM-120C7;2 AGM-88C;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'F-16AM/BM Blk 15 MLU', 'Falcon (Belgium)-6', 2)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Falcon (Belgium)-6', '2 AIM-120C7;2 AGM-88C;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'Typhoon', 'Eurofighter (Italy)-1', 2)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Eurofighter (Italy)-1', '2 ASRAAM;2 MBDA Meteor;2 MBDA Meteor;4 MBDA Meteor;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'Typhoon', 'Eurofighter (Italy)-2', 2)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Eurofighter (Italy)-2', '2 ASRAAM;2 MBDA Meteor;2 MBDA Meteor;4 MBDA Meteor;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'Typhoon', 'Eurofighter (Italy)-3', 1)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Eurofighter (Italy)-3', '2 ASRAAM;2 MBDA Meteor;2 MBDA Meteor;4 MBDA Meteor;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'Typhoon', 'Eurofighter (Italy)-4', 1)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Eurofighter (Italy)-4', '2 ASRAAM;2 MBDA Meteor;2 MBDA Meteor;4 MBDA Meteor;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'Typhoon', 'Eurofighter (Italy)-5', 1)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Eurofighter (Italy)-5', '2 ASRAAM;2 MBDA Meteor;2 MBDA Meteor;4 MBDA Meteor;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'Typhoon', 'Eurofighter (Italy)-6', 1)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Eurofighter (Italy)-6', '2 ASRAAM;2 MBDA Meteor;2 MBDA Meteor;4 MBDA Meteor;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'Typhoon', 'Eurofighter (Italy)-7', 1)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Eurofighter (Italy)-7', '2 ASRAAM;4 GBU-30;4 GBU-30;4 MBDA Meteor;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'Typhoon', 'Eurofighter (Italy)-8', 1)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Eurofighter (Italy)-8', '2 ASRAAM;4 GBU-30;4 GBU-30;4 MBDA Meteor;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'Typhoon', 'Eurofighter (Italy)-9', 1)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Eurofighter (Italy)-9', '2 ASRAAM;4 GBU-30;4 GBU-30;4 MBDA Meteor;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Catania-Sigonella AB', 'Typhoon', 'Eurofighter (Italy)-10', 1)
    SM.SetFlightDeckUnitLoadout('Catania-Sigonella AB', 'Eurofighter (Italy)-10', '2 ASRAAM;4 GBU-30;4 GBU-30;4 MBDA Meteor;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Chaff-1;30 Flare-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Solenzara AB"
    unit.SetPosition(9.392000, 41.921000, -0.0)
    unit.heading = 179.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Solenzara AB", 'Fuel', 5000000)
    SM.AddToUnitMagazine("Solenzara AB", '1250 liter tank', 30)
    SM.AddToUnitMagazine("Solenzara AB", '2000 liter tank', 18)
    SM.AddToUnitMagazine("Solenzara AB", '3000 liter tank', 6)
    SM.AddToUnitMagazine("Solenzara AB", '30x150mm GIAT', 82)
    SM.AddToUnitMagazine("Solenzara AB", 'ALARM', 41)
    SM.AddToUnitMagazine("Solenzara AB", 'AM-39 Exocet', 12)
    SM.AddToUnitMagazine("Solenzara AB", 'AS-30L', 19)
    SM.AddToUnitMagazine("Solenzara AB", 'Chaff-1', 1244)
    SM.AddToUnitMagazine("Solenzara AB", 'Durandal', 149)
    SM.AddToUnitMagazine("Solenzara AB", 'Flare-1', 1244)
    SM.AddToUnitMagazine("Solenzara AB", 'GBU-10/B', 12)
    SM.AddToUnitMagazine("Solenzara AB", 'GBU-12/B', 31)
    SM.AddToUnitMagazine("Solenzara AB", 'MBDA Meteor', 87)
    SM.AddToUnitMagazine("Solenzara AB", 'MICA IR', 149)
    SM.AddToUnitMagazine("Solenzara AB", 'MICA RF', 141)
    SM.AddToUnitMagazine("Solenzara AB", 'Mk-82', 149)
    SM.AddToUnitMagazine("Solenzara AB", 'Mk-83', 62)
    SM.AddToUnitMagazine("Solenzara AB", 'SCALP EG', 16)
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
    
    SM.AddUnitToFlightDeck('Solenzara AB', 'Rafale M', 'Rafale (Land Based)-1', 2)
    SM.SetFlightDeckUnitLoadout('Solenzara AB', 'Rafale (Land Based)-1', '2 MICA IR;2 MICA RF;2 MBDA Meteor;2 MBDA Meteor;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Solenzara AB', 'Rafale M', 'Rafale (Land Based)-2', 2)
    SM.SetFlightDeckUnitLoadout('Solenzara AB', 'Rafale (Land Based)-2', '2 MICA IR;2 MICA RF;2 MBDA Meteor;2 MBDA Meteor;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Solenzara AB', 'Rafale M', 'Rafale (Land Based)-3', 2)
    SM.SetFlightDeckUnitLoadout('Solenzara AB', 'Rafale (Land Based)-3', '2 MICA IR;2 MICA RF;2 ALARM;2 ALARM;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Solenzara AB', 'Rafale M', 'Rafale (Land Based)-4', 2)
    SM.SetFlightDeckUnitLoadout('Solenzara AB', 'Rafale (Land Based)-4', '2 MICA IR;2 MICA RF;2 ALARM;2 ALARM;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Solenzara AB', 'Rafale M', 'Rafale (Land Based)-5', 2)
    SM.SetFlightDeckUnitLoadout('Solenzara AB', 'Rafale (Land Based)-5', '2 MICA IR;2 MICA RF;2 AM-39 Exocet;2 AM-39 Exocet;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Solenzara AB', 'Rafale M', 'Rafale (Land Based)-6', 2)
    SM.SetFlightDeckUnitLoadout('Solenzara AB', 'Rafale (Land Based)-6', '2 MICA IR;2 MICA RF;2 AM-39 Exocet;2 AM-39 Exocet;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Solenzara AB', 'E-3D/F', 'AEW (France)-1', 2)
    SM.SetFlightDeckUnitLoadout('Solenzara AB', 'AEW (France)-1', '')
    
    SM.AddUnitToFlightDeck('Solenzara AB', 'E-3D/F', 'AEW (France)-2', 2)
    SM.SetFlightDeckUnitLoadout('Solenzara AB', 'AEW (France)-2', '')
    
    SM.AddUnitToFlightDeck('Solenzara AB', 'KC-767A', 'Refuel (France)-1', 1)
    SM.SetFlightDeckUnitLoadout('Solenzara AB', 'Refuel (France)-1', '')
    
    SM.AddUnitToFlightDeck('Solenzara AB', 'KC-767A', 'Refuel (France)-2', 1)
    SM.SetFlightDeckUnitLoadout('Solenzara AB', 'Refuel (France)-2', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Decimomannu AB"
    unit.SetPosition(8.977359, 39.342191, 10.0)
    unit.heading = 166.93
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Decimomannu AB", 'AM-39 Exocet', 39)
    SM.AddToUnitMagazine("Decimomannu AB", 'GB-200', 131)
    SM.AddToUnitMagazine("Decimomannu AB", 'GB-500', 26)
    SM.AddToUnitMagazine("Decimomannu AB", 'MICA IR', 623)
    SM.AddToUnitMagazine("Decimomannu AB", 'MICA RF', 623)
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
    
    SM.AddUnitToFlightDeck('Decimomannu AB', 'Mirage-2000', 'Mirage (France)-1', 2)
    SM.SetFlightDeckUnitLoadout('Decimomannu AB', 'Mirage (France)-1', '2 AM-39 Exocet;2 MICA IR;2 MICA RF;')
    
    SM.AddUnitToFlightDeck('Decimomannu AB', 'Mirage-2000', 'Mirage (France)-2', 2)
    SM.SetFlightDeckUnitLoadout('Decimomannu AB', 'Mirage (France)-2', '2 AM-39 Exocet;2 MICA IR;2 MICA RF;')
    
    SM.AddUnitToFlightDeck('Decimomannu AB', 'Mirage-2000', 'Mirage (France)-3', 2)
    SM.SetFlightDeckUnitLoadout('Decimomannu AB', 'Mirage (France)-3', '2 AM-39 Exocet;2 MICA IR;2 MICA RF;')
    
    SM.AddUnitToFlightDeck('Decimomannu AB', 'Mirage-2000', 'Mirage (France)-4', 2)
    SM.SetFlightDeckUnitLoadout('Decimomannu AB', 'Mirage (France)-4', '2 AM-39 Exocet;2 MICA IR;2 MICA RF;')
    
    SM.AddUnitToFlightDeck('Decimomannu AB', 'Mirage-2000', 'Mirage (France)-5', 2)
    SM.SetFlightDeckUnitLoadout('Decimomannu AB', 'Mirage (France)-5', '2 AM-39 Exocet;2 MICA IR;2 MICA RF;')
    
    SM.AddUnitToFlightDeck('Decimomannu AB', 'Mirage-2000', 'Mirage (France)-6', 2)
    SM.SetFlightDeckUnitLoadout('Decimomannu AB', 'Mirage (France)-6', '2 AM-39 Exocet;2 MICA IR;2 MICA RF;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Gioia del Colle AB"
    unit.SetPosition(16.942562, 40.755809, 10.0)
    unit.heading = 140.89
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'Fuel', 3000000)
    SM.AddToUnitMagazine("Gioia del Colle AB", '27mm BK27 27x145mm', 686)
    SM.AddToUnitMagazine("Gioia del Colle AB", '330 gallon wing tank', 40)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'AGM-65D', 1)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'AIM-132 ASRAAM', 8)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'ALARM', 37)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'BAe Sea Eagle', 22)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'Brimstone', 132)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'Chaff-1', 2361)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'Flare-1', 2361)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'GB-200', 144)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'GB-500', 68)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'GBU-10/B', 17)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'GBU-15/B', 27)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'GBU-16/B', 27)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'GBU-24/B', 17)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'GBU-24B/B', 17)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'Mk-81', 154)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'Mk-82', 144)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'Mk-83', 68)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'Mk-84', 29)
    SM.AddToUnitMagazine("Gioia del Colle AB", 'Storm Shadow', 22)
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
    
    SM.AddUnitToFlightDeck('Gioia del Colle AB', 'Tornado GR.Mk.4', 'Tornado (UK)-1', 2)
    SM.SetFlightDeckUnitLoadout('Gioia del Colle AB', 'Tornado (UK)-1', '50 Chaff-1;50 Flare-1;1 AIM-132 ASRAAM;1 AIM-132 ASRAAM;1 ALARM;1 ALARM;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gioia del Colle AB', 'Tornado GR.Mk.4', 'Tornado (UK)-2', 2)
    SM.SetFlightDeckUnitLoadout('Gioia del Colle AB', 'Tornado (UK)-2', '50 Chaff-1;50 Flare-1;1 AIM-132 ASRAAM;1 AIM-132 ASRAAM;1 ALARM;1 ALARM;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gioia del Colle AB', 'Tornado GR.Mk.4', 'Tornado (UK)-3', 2)
    SM.SetFlightDeckUnitLoadout('Gioia del Colle AB', 'Tornado (UK)-3', '50 Chaff-1;50 Flare-1;1 AIM-132 ASRAAM;1 AIM-132 ASRAAM;1 ALARM;1 ALARM;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gioia del Colle AB', 'Tornado GR.Mk.4', 'Tornado (UK)-4', 2)
    SM.SetFlightDeckUnitLoadout('Gioia del Colle AB', 'Tornado (UK)-4', '50 Chaff-1;50 Flare-1;1 AIM-132 ASRAAM;1 AIM-132 ASRAAM;1 ALARM;1 ALARM;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gioia del Colle AB', 'Tornado GR.Mk.4', 'Tornado (UK)-5', 2)
    SM.SetFlightDeckUnitLoadout('Gioia del Colle AB', 'Tornado (UK)-5', '50 Chaff-1;50 Flare-1;1 AIM-132 ASRAAM;1 AIM-132 ASRAAM;1 ALARM;1 ALARM;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gioia del Colle AB', 'Tornado GR.Mk.4', 'Tornado (UK)-6', 2)
    SM.SetFlightDeckUnitLoadout('Gioia del Colle AB', 'Tornado (UK)-6', '50 Chaff-1;50 Flare-1;1 AIM-132 ASRAAM;1 AIM-132 ASRAAM;1 ALARM;1 ALARM;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gioia del Colle AB', 'Tornado GR.Mk.4', 'Tornado (UK)-7', 2)
    SM.SetFlightDeckUnitLoadout('Gioia del Colle AB', 'Tornado (UK)-7', '50 Chaff-1;50 Flare-1;1 AIM-132 ASRAAM;1 AIM-132 ASRAAM;1 ALARM;1 ALARM;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gioia del Colle AB', 'Tornado GR.Mk.4', 'Tornado (UK)-8', 2)
    SM.SetFlightDeckUnitLoadout('Gioia del Colle AB', 'Tornado (UK)-8', '50 Chaff-1;50 Flare-1;1 AIM-132 ASRAAM;1 AIM-132 ASRAAM;1 ALARM;1 ALARM;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gioia del Colle AB', 'Tornado GR.Mk.4', 'Tornado (UK)-9', 1)
    SM.SetFlightDeckUnitLoadout('Gioia del Colle AB', 'Tornado (UK)-9', '50 Chaff-1;50 Flare-1;1 AIM-132 ASRAAM;1 AIM-132 ASRAAM;1 ALARM;1 ALARM;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gioia del Colle AB', 'Tornado GR.Mk.4', 'Tornado (UK)-10', 1)
    SM.SetFlightDeckUnitLoadout('Gioia del Colle AB', 'Tornado (UK)-10', '50 Chaff-1;50 Flare-1;1 AIM-132 ASRAAM;1 AIM-132 ASRAAM;1 ALARM;1 ALARM;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Amendola AB"
    unit.SetPosition(15.728344, 41.534737, 10.0)
    unit.heading = 113.79
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Amendola AB", 'Fuel', 2000000)
    SM.AddToUnitMagazine("Amendola AB", 'AM-39 Exocet', 33)
    SM.AddToUnitMagazine("Amendola AB", 'GB-200', 107)
    SM.AddToUnitMagazine("Amendola AB", 'GB-500', 22)
    SM.AddToUnitMagazine("Amendola AB", 'MICA IR', 522)
    SM.AddToUnitMagazine("Amendola AB", 'MICA RF', 522)
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
    
    SM.AddUnitToFlightDeck('Amendola AB', 'Mirage-2000', 'Mirage (Quatar)-1', 2)
    SM.SetFlightDeckUnitLoadout('Amendola AB', 'Mirage (Quatar)-1', '2 AM-39 Exocet;2 MICA IR;2 MICA RF;')
    
    SM.AddUnitToFlightDeck('Amendola AB', 'Mirage-2000', 'Mirage (Quatar)-2', 2)
    SM.SetFlightDeckUnitLoadout('Amendola AB', 'Mirage (Quatar)-2', '2 AM-39 Exocet;2 MICA IR;2 MICA RF;')
    
    SM.AddUnitToFlightDeck('Amendola AB', 'Mirage-2000', 'Mirage (Quatar)-3', 2)
    SM.SetFlightDeckUnitLoadout('Amendola AB', 'Mirage (Quatar)-3', '2 AM-39 Exocet;2 MICA IR;2 MICA RF;')
    
    SM.AddUnitToFlightDeck('Amendola AB', 'Mirage-2000', 'Mirage (Quatar)-4', 2)
    SM.SetFlightDeckUnitLoadout('Amendola AB', 'Mirage (Quatar)-4', '2 AM-39 Exocet;2 MICA IR;2 MICA RF;')
    
    SM.AddUnitToFlightDeck('Amendola AB', 'KC-130F', 'Transport (Quatar)-1', 2)
    SM.SetFlightDeckUnitLoadout('Amendola AB', 'Transport (Quatar)-1', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Aviano AB"
    unit.SetPosition(12.607460, 46.038024, 10.0)
    unit.heading = 47.65
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Aviano AB", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Aviano AB", 'AGM-130', 12)
    SM.AddToUnitMagazine("Aviano AB", 'AGM-158A JASSM', 27)
    SM.AddToUnitMagazine("Aviano AB", 'Chaff-1', 207)
    SM.AddToUnitMagazine("Aviano AB", 'Flare-1', 207)
    SM.AddToUnitMagazine("Aviano AB", 'GBU-31A(v)2', 12)
    SM.AddToUnitMagazine("Aviano AB", 'GBU-31C(v)4', 12)
    SM.AddToUnitMagazine("Aviano AB", 'GBU-32A(v)2', 27)
    SM.AddToUnitMagazine("Aviano AB", 'GBU-32C(v)4', 54)
    SM.AddToUnitMagazine("Aviano AB", 'GBU-39 SDB', 36)
    SM.AddToUnitMagazine("Aviano AB", 'M117', 180)
    SM.AddToUnitMagazine("Aviano AB", 'M118', 39)
    SM.AddToUnitMagazine("Aviano AB", 'Mk-81', 207)
    SM.AddToUnitMagazine("Aviano AB", 'Mk-82', 276)
    SM.AddToUnitMagazine("Aviano AB", 'Mk-83', 123)
    SM.AddToUnitMagazine("Aviano AB", 'Mk-84', 39)
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
    
    SM.AddUnitToFlightDeck('Aviano AB', 'E-3D/F', 'Sharpeye-1', 2)
    SM.SetFlightDeckUnitLoadout('Aviano AB', 'Sharpeye-1', '')
    
    SM.AddUnitToFlightDeck('Aviano AB', 'E-3D/F', 'Sharpeye-2', 3)
    SM.SetFlightDeckUnitLoadout('Aviano AB', 'Sharpeye-2', '')
    
    SM.AddUnitToFlightDeck('Aviano AB', 'B-2A', 'Spirit-1', 3)
    SM.SetFlightDeckUnitLoadout('Aviano AB', 'Spirit-1', '40 GBU-39 SDB;40 GBU-39 SDB;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Aviano AB', 'B-2A', 'Spirit-2', 3)
    SM.SetFlightDeckUnitLoadout('Aviano AB', 'Spirit-2', '40 GBU-39 SDB;40 GBU-39 SDB;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Aviano AB', 'B-2A', 'Spirit-3', 3)
    SM.SetFlightDeckUnitLoadout('Aviano AB', 'Spirit-3', '40 GBU-39 SDB;40 GBU-39 SDB;30 Flare-1;30 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'CV R91 Charles de Gaulle'
    unit.unitName = "Charles de Gaulle"
    unit.SetPosition(6.910560, 38.805057, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'ASTER 15', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mistral 2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mistral 2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 8, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 9, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 10, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 11, 'Sagaie Flare', 6)
    SM.SetUnitLauncherItem(unit.unitName, 12, 'Chaff-Round-1', 6)
    SM.SetUnitLauncherItem(unit.unitName, 13, 'Sagaie Flare', 6)
    SM.SetUnitLauncherItem(unit.unitName, 14, 'Chaff-Round-1', 6)
    SM.SetUnitLauncherItem(unit.unitName, 15, 'Decoy-1', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Charles de Gaulle", 'Fuel', 2409000)
    SM.AddToUnitMagazine("Charles de Gaulle", '1100 Liter Tank', 66)
    SM.AddToUnitMagazine("Charles de Gaulle", '1250 liter tank', 66)
    SM.AddToUnitMagazine("Charles de Gaulle", '2000 liter tank', 39)
    SM.AddToUnitMagazine("Charles de Gaulle", '20mm F2', 6823)
    SM.AddToUnitMagazine("Charles de Gaulle", '20x102 mm burst', 375)
    SM.AddToUnitMagazine("Charles de Gaulle", '3000 liter tank', 13)
    SM.AddToUnitMagazine("Charles de Gaulle", '30mm DEFA', 750)
    SM.AddToUnitMagazine("Charles de Gaulle", '30x150mm GIAT', 450)
    SM.AddToUnitMagazine("Charles de Gaulle", '625 liter tank', 66)
    SM.AddToUnitMagazine("Charles de Gaulle", '750 litre tank', 4)
    SM.AddToUnitMagazine("Charles de Gaulle", 'AM-39 Exocet', 540)
    SM.AddToUnitMagazine("Charles de Gaulle", 'AS-30L', 228)
    SM.AddToUnitMagazine("Charles de Gaulle", 'Chaff-1', 11259)
    SM.AddToUnitMagazine("Charles de Gaulle", 'DICASS (100) Sonobuoy', 23)
    SM.AddToUnitMagazine("Charles de Gaulle", 'DICASS (105) Sonobuoy', 83)
    SM.AddToUnitMagazine("Charles de Gaulle", 'DIFAR (100) Sonobuoy', 69)
    SM.AddToUnitMagazine("Charles de Gaulle", 'DIFAR (105) Sonobuoy', 250)
    SM.AddToUnitMagazine("Charles de Gaulle", 'Durandal', 1261)
    SM.AddToUnitMagazine("Charles de Gaulle", 'Flare-1', 11259)
    SM.AddToUnitMagazine("Charles de Gaulle", 'LOFAR (100) Sonobuoy', 23)
    SM.AddToUnitMagazine("Charles de Gaulle", 'LOFAR (105) Sonobuoy', 83)
    SM.AddToUnitMagazine("Charles de Gaulle", 'MICA IR', 810)
    SM.AddToUnitMagazine("Charles de Gaulle", 'MICA RF', 810)
    SM.AddToUnitMagazine("Charles de Gaulle", 'SCALP EG', 67)
    SM.AddToUnitMagazine("Charles de Gaulle", 'Mistral 2', 46)
    SM.AddToUnitMagazine("Charles de Gaulle", 'ASTER 15', 32)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
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
    BB.Write('InvMulti', '1')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"Sagaie Flare": 0, "Decoy-1": 0, "Mistral": 0, "Mistral 2": 92, "Chaff-Round-1": 0, "20mm F2": 54584, "ASTER 15": 32}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"Sagaie Flare": [12, 12], "Decoy-1": [6, 6], "Mistral 2": [12, 12], "Chaff-Round-1": [12, 12], "20mm F2": [800, 800], "ASTER 15": [1, 1]}}')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 1', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 1', '2 ASRAAM;2 ASRAAM;2 MICA IR;2 MICA RF;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 2', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 2', '2 ASRAAM;2 ASRAAM;2 MICA IR;2 MICA RF;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 3', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 3', '2 ASRAAM;2 ASRAAM;2 MICA IR;2 MICA RF;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 4', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 4', '2 ASRAAM;2 ASRAAM;2 MICA IR;2 MICA RF;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 5', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 5', '2 ASRAAM;2 ASRAAM;2 MICA IR;2 MICA RF;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 6', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 6', '2 ASRAAM;2 ASRAAM;2 MICA IR;2 MICA RF;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 7', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 7', '2 ASRAAM;2 ASRAAM;2 MICA IR;2 MICA RF;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 8', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 8', '2 ASRAAM;2 ASRAAM;2 MICA IR;2 MICA RF;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 9', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 9', '2 ASRAAM;2 MICA IR;2 GBU-12/B;2 GBU-10/B;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 10', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 10', '2 ASRAAM;2 MICA IR;2 GBU-12/B;2 GBU-10/B;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 11', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 11', '2 ASRAAM;2 MICA IR;2 GBU-12/B;2 GBU-10/B;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Rafale M', 'Vent 12', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Vent 12', '2 ASRAAM;2 MICA IR;2 GBU-12/B;2 GBU-10/B;0 Empty;2 MBDA Meteor;1 3000 liter tank;5 30x150mm GIAT;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 1', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 1', '2 R.550 Magic;1 AS-30L;1 AS-30L;1 AS-30L;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 2', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 2', '2 R.550 Magic;1 AS-30L;1 AS-30L;1 AS-30L;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 3', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 3', '2 R.550 Magic;1 AS-30L;1 AS-30L;1 AS-30L;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 4', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 4', '2 R.550 Magic;1 AS-30L;1 AS-30L;1 AS-30L;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 5', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 5', '2 R.550 Magic;1 AS-30L;1 AS-30L;1 AS-30L;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 6', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 6', '2 R.550 Magic;1 AS-30L;1 AS-30L;1 AS-30L;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 7', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 7', '2 R.550 Magic;1 AS-30L;1 AS-30L;1 AS-30L;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 8', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 8', '2 R.550 Magic;1 AS-30L;1 AS-30L;1 AS-30L;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 9', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 9', '2 GBU-12/B;2 Durandal;2 Durandal;2 Durandal;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 10', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 10', '2 GBU-12/B;2 Durandal;2 Durandal;2 Durandal;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 11', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 11', '2 GBU-12/B;2 Durandal;2 Durandal;2 Durandal;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 12', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 12', '2 GBU-12/B;2 Durandal;2 Durandal;2 Durandal;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 13', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 13', '2 GBU-12/B;2 Durandal;2 Durandal;2 Durandal;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 14', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 14', '2 GBU-12/B;2 Durandal;2 Durandal;2 Durandal;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 15', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 15', '2 GBU-12/B;2 Durandal;2 Durandal;2 Durandal;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 16', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 16', '2 GBU-12/B;2 Durandal;2 Durandal;2 Durandal;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 17', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 17', '2 R.550 Magic;1 AM-39 Exocet;1 AM-39 Exocet;1 AM-39 Exocet;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 18', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 18', '2 R.550 Magic;1 AM-39 Exocet;1 AM-39 Exocet;1 AM-39 Exocet;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 19', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 19', '2 R.550 Magic;1 AM-39 Exocet;1 AM-39 Exocet;1 AM-39 Exocet;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'Super Etendard M', 'Norme 20', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Norme 20', '2 R.550 Magic;1 AM-39 Exocet;1 AM-39 Exocet;1 AM-39 Exocet;10 30mm DEFA;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'E-2C 2000 NP', 'Garde 1', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Garde 1', '')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'E-2C 2000 NP', 'Garde 2', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Garde 2', '')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'AS 565MB Panther', 'CdG Helo 1', 2)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'CdG Helo 1', '1 MU-90;1 MU-90;8 DICASS (105) Sonobuoy;8 LOFAR (105) Sonobuoy;8 DIFAR (105) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'AS 565MB Panther', 'CdG Helo 2', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'CdG Helo 2', '1 MU-90;1 MU-90;8 DICASS (105) Sonobuoy;8 LOFAR (105) Sonobuoy;8 DIFAR (105) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'SA-365', 'Aide 1', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Aide 1', '')
    
    SM.AddUnitToFlightDeck('Charles de Gaulle', 'SA-365', 'Aide 2', 1)
    SM.SetFlightDeckUnitLoadout('Charles de Gaulle', 'Aide 2', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSN 688 Los Angeles Improved'
    unit.unitName = "USS Scranton"
    unit.SetPosition(11.770730, 35.645538, -28.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'UGM-84C Harpoon', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'UGM-109C', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'UGM-109C', 6)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Scranton", 'Mk-48 Mod6', 12)
    SM.AddToUnitMagazine("USS Scranton", 'UGM-84C Harpoon', 4)
    SM.AddToUnitMagazine("USS Scranton", 'UGM-109A', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSN 688 Los Angeles (1985)'
    unit.unitName = "USS Providence"
    unit.SetPosition(16.106760, 35.797372, -28.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'UGM-84C Harpoon', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'UGM-109C', 6)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'UGM-109C', 6)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Providence", 'Mk-48 Mod6', 12)
    SM.AddToUnitMagazine("USS Providence", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSGN 726 Ohio (2008)'
    unit.unitName = "USS Florida"
    unit.SetPosition(17.793032, 35.060032, -28.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Mk-48 Mod6', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'BGM-109 TLAM', 154)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Decoy-1', 10)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Decoy-1', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Florida", 'Mk-48 Mod6', 28)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(6, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Blue Ridge AGFH'
    unit.unitName = "USS Mount Whitney"
    unit.SetPosition(17.434420, 38.099745, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 2, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 3, '25mm APDS', 400)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Mount Whitney", 'Fuel', 50000)
    SM.AddToUnitMagazine("USS Mount Whitney", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Mount Whitney", '25mm APDS', 8000)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Austin LPD'
    unit.unitName = "USS Ponce"
    unit.SetPosition(15.767226, 36.328045, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 1, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 2, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 3, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 4, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 5, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 9, '25mm APDS', 400)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Ponce", '.50 cal bullet', 36000)
    SM.AddToUnitMagazine("USS Ponce", '25mm APDS', 8000)
    SM.AddToUnitMagazine("USS Ponce", '20mm mark 244-0 ELC', 1046)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Wasp LHDM'
    unit.unitName = "USS Keersarge"
    unit.SetPosition(20.242371, 36.556083, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-116B RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-116B RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 4, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 5, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 9, '25mm APDS', 400)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Keersarge", 'Fuel', 1200000)
    SM.AddToUnitMagazine("USS Keersarge", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Keersarge", 'RIM-7P(v1)', 48)
    SM.AddToUnitMagazine("USS Keersarge", 'RIM-116B RAM', 84)
    SM.AddToUnitMagazine("USS Keersarge", '.50 cal bullet', 12000)
    SM.AddToUnitMagazine("USS Keersarge", '25mm APDS', 8000)
    SM.AddToUnitMagazine("USS Keersarge", '120 gallon tank', 8)
    SM.AddToUnitMagazine("USS Keersarge", '190 gallon wing tank', 40)
    SM.AddToUnitMagazine("USS Keersarge", '300 gallon wing tank', 40)
    SM.AddToUnitMagazine("USS Keersarge", 'AGM-114 Hellfire', 1675)
    SM.AddToUnitMagazine("USS Keersarge", 'AGM-119B', 8)
    SM.AddToUnitMagazine("USS Keersarge", 'AGM-65D', 399)
    SM.AddToUnitMagazine("USS Keersarge", 'AGM-88C', 152)
    SM.AddToUnitMagazine("USS Keersarge", 'AIM-120C7', 76)
    SM.AddToUnitMagazine("USS Keersarge", 'AIM-120D', 191)
    SM.AddToUnitMagazine("USS Keersarge", 'AIM-9X', 100)
    SM.AddToUnitMagazine("USS Keersarge", 'BGM-71E TOW 2', 1675)
    SM.AddToUnitMagazine("USS Keersarge", 'Chaff-1', 14362)
    SM.AddToUnitMagazine("USS Keersarge", 'DICASS (105) Sonobuoy', 526)
    SM.AddToUnitMagazine("USS Keersarge", 'DIFAR (105) Sonobuoy', 1576)
    SM.AddToUnitMagazine("USS Keersarge", 'Flare-1', 12562)
    SM.AddToUnitMagazine("USS Keersarge", 'GBU-31A(v)2', 479)
    SM.AddToUnitMagazine("USS Keersarge", 'GBU-31C(v)4', 479)
    SM.AddToUnitMagazine("USS Keersarge", 'GBU-32A(v)2', 479)
    SM.AddToUnitMagazine("USS Keersarge", 'GBU-32C(v)4', 479)
    SM.AddToUnitMagazine("USS Keersarge", 'GBU-39 SDB', 1412)
    SM.AddToUnitMagazine("USS Keersarge", 'Hydra-70 rocket', 47671)
    SM.AddToUnitMagazine("USS Keersarge", 'LOFAR (105) Sonobuoy', 526)
    SM.AddToUnitMagazine("USS Keersarge", 'Mk 71 Zuni WAFAR', 2333)
    SM.AddToUnitMagazine("USS Keersarge", 'Mk-46 Mod5', 8)
    SM.AddToUnitMagazine("USS Keersarge", 'Mk-50', 4)
    SM.AddToUnitMagazine("USS Keersarge", 'Mk-54', 54)
    SM.AddToUnitMagazine("USS Keersarge", 'Mk-81', 1117)
    SM.AddToUnitMagazine("USS Keersarge", 'Mk-82', 1115)
    SM.AddToUnitMagazine("USS Keersarge", 'Mk-83', 279)
    SM.AddToUnitMagazine("USS Keersarge", 'Mk-84', 417)
    SM.AddToUnitMagazine("USS Keersarge", 'M117', 6)
    SM.AddToUnitMagazine("USS Keersarge", '100 gallon wing tank', 24)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
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
    BB.Write('InvMulti', '1')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"RIM-7F": 0, "RIM-116A RAM": 0, "RIM-7P(v1)": 96, "RIM-7E": 0, "20mm mark 244-0 ELC": 2092, "25mm APDS": 16000, "RIM-116B RAM": 168, "25mm FAPDS-T": 0, "25mm SAPHEI-T": 0, "RIM-7H": 0, "ASPIDE-1A": 0, "RIM-7M(v1)": 0, ".50 cal bullet": 24000, "RIM-162D": 0, "25mm APDS-T": 0, "25mm HEI": 0, "25mm SAPHEI": 0, "25mm HEI-T": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"RIM-7P(v1)": [16, 16], "RIM-116B RAM": [42, 42], ".50 cal bullet": [1200, 1200], "25mm APDS": [800, 800], "20mm mark 244-0 ELC": [194, 194]}}')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AV-8B Harrier II+', 'Striker 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Striker 1', '4 AIM-9X;2 AIM-120C7;2 AIM-9X;2 AIM-120C7;0 Empty;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AV-8B Harrier II+', 'Striker 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Striker 2', '4 AIM-9X;2 AIM-120C7;2 AIM-9X;2 AIM-120C7;0 Empty;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AV-8B Harrier II+', 'Striker 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Striker 3', '6 GBU-39 SDB;2 AIM-120D;2 AIM-9X;6 GBU-39 SDB;1 Mk-82;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AV-8B Harrier II+', 'Striker 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Striker 4', '6 GBU-39 SDB;2 AIM-120D;2 AIM-9X;6 GBU-39 SDB;1 Mk-82;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AV-8B Harrier II+', 'Striker 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Striker 5', '38 Hydra-70 rocket;2 AGM-88C;2 AIM-9X;2 AGM-88C;1 Mk-84;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AV-8B Harrier II+', 'Striker 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Striker 6', '38 Hydra-70 rocket;2 AGM-88C;2 AIM-9X;2 AGM-88C;1 Mk-84;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 1', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 2', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 3', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 4', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 5', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 6', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 7', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 8', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 9', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 10', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 11', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'CH-53E', 'Stallion 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Stallion 12', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'UH-1N', 'Huey  1', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Huey  1', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'UH-1N', 'Huey  2', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Huey  2', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'UH-1N', 'Huey  3', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Huey  3', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'UH-1N', 'Huey  4', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Huey  4', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'UH-1N', 'Huey  5', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Huey  5', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'UH-1N', 'Huey  6', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Huey  6', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'UH-1N', 'Huey  7', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Huey  7', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'UH-1N', 'Huey  8', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Huey  8', '')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  1', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  1', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  2', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  2', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  3', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  3', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  4', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  4', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  5', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  5', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  6', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  6', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  7', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  7', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  8', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  8', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  9', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  9', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  10', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  10', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  11', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  11', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'AH-1Z Viper', 'Snake  12', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'Snake  12', '230 20mm M53 API;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;4 AGM-114 Hellfire;2 AIM-9X;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'SH-60B', 'SeaHawk  1', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'SeaHawk  1', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;15 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Keersarge', 'SH-60B', 'SeaHawk  2', 1)
    SM.SetFlightDeckUnitLoadout('USS Keersarge', 'SeaHawk  2', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (100) Sonobuoy;5 LOFAR (100) Sonobuoy;15 DIFAR (100) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Lewis and Clark'
    unit.unitName = "USNS Robert E Peary"
    unit.SetPosition(26.604148, 34.240646, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USNS Robert E Peary", 'Fuel', 1000000)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USNS Robert E Peary', 'SA-330J', 'Puma1', 1)
    SM.SetFlightDeckUnitLoadout('USNS Robert E Peary', 'Puma1', '')
    
    SM.AddUnitToFlightDeck('USNS Robert E Peary', 'SA-330J', 'Puma2', 1)
    SM.SetFlightDeckUnitLoadout('USNS Robert E Peary', 'Puma2', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Henry J Kaiser'
    unit.unitName = "USNS Kanawha"
    unit.SetPosition(27.561274, 33.667802, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USNS Kanawha", 'Fuel', 15000000)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Halifax FFH'
    unit.unitName = "HMCS Charlottetown"
    unit.SetPosition(12.665918, 34.677469, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-162B', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-162B', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RGM-84A Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'RGM-84A Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '57mm HCER', 120)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Chaff-Round-1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Chaff-Round-1', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMCS Charlottetown", 'DICASS (90) Sonobuoy', 200)
    SM.AddToUnitMagazine("HMCS Charlottetown", 'DIFAR (90) Sonobuoy', 200)
    SM.AddToUnitMagazine("HMCS Charlottetown", 'Fuel', 100000)
    SM.AddToUnitMagazine("HMCS Charlottetown", 'LOFAR (90) Sonobuoy', 200)
    SM.AddToUnitMagazine("HMCS Charlottetown", 'Mk-46 Mod5', 30)
    SM.AddToUnitMagazine("HMCS Charlottetown", 'RIM-162B', 16)
    SM.AddToUnitMagazine("HMCS Charlottetown", '20mm mark 244-0 ELC', 970)
    SM.AddToUnitMagazine("HMCS Charlottetown", '57mm HCER', 600)
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
    BB.Write('InvMulti', '1')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"RGM-84G Harpoon": 0, "Mk-44": 0, "20mm mark 244-0 ELC": 970, "57mm PFHE": 0, "MU-90": 0, "RGM-84D Harpoon": 0, "57mm HE": 0, "Chaff-Round-1": 0, "RGM-84F Harpoon": 0, "Mk-46 Mod5": 60, "57mm HCER": 600, "RIM-162B": 32, "Mk-54": 0, "Mk-186 TORCH Flare": 0, "RGM-84A Harpoon": 0, "Stingray": 0, "Mk-15 Mod0": 0, "RGM-84C Harpoon": 0, "Mk-50": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"20mm mark 244-0 ELC": [97, 97], "RGM-84A Harpoon": [8, 8], "57mm HCER": [120, 120], "Mk-46 Mod5": [6, 6], "RIM-162B": [16, 16], "Chaff-Round-1": [2, 2]}}')
    
    SM.AddUnitToFlightDeck('HMCS Charlottetown', 'CH-124B2', 'King1', 2)
    SM.SetFlightDeckUnitLoadout('HMCS Charlottetown', 'King1', '2 Mk-46 Mod5;10 DICASS (100) Sonobuoy;10 LOFAR (100) Sonobuoy;30 DIFAR (100) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Arleigh Burke DDGHM'
    unit.unitName = "USS Stout"
    unit.SetPosition(15.649424, 34.659134, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-162A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-156', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, '127mm mk 127 HE-CVT mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Mk-54', 3)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-54', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Stout", 'Fuel', 28058)
    SM.AddToUnitMagazine("USS Stout", 'Mk-54', 12)
    SM.AddToUnitMagazine("USS Stout", 'RIM-156', 24)
    SM.AddToUnitMagazine("USS Stout", 'RIM-162A', 79)
    SM.AddToUnitMagazine("USS Stout", 'RIM-66M', 44)
    SM.AddToUnitMagazine("USS Stout", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Stout", '127mm mk 127 HE-CVT mk 67', 680)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Arleigh Burke DDGHM'
    unit.unitName = "USS Barry"
    unit.SetPosition(16.641043, 34.893531, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-162A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-156', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, '127mm mk 127 HE-CVT mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Mk-54', 3)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-54', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Barry", 'Fuel', 28058)
    SM.AddToUnitMagazine("USS Barry", 'Mk-54', 29)
    SM.AddToUnitMagazine("USS Barry", '120 gallon tank', 3)
    SM.AddToUnitMagazine("USS Barry", 'RIM-156', 24)
    SM.AddToUnitMagazine("USS Barry", 'RIM-162A', 79)
    SM.AddToUnitMagazine("USS Barry", 'RIM-66M', 44)
    SM.AddToUnitMagazine("USS Barry", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Barry", '127mm mk 127 HE-CVT mk 67', 680)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Etna (A5326)'
    unit.unitName = "Etna"
    unit.SetPosition(16.487490, 34.075233, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 1, '20mm HE-T', 50)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Etna", '20mm HE-T', 200)
    SM.AddToUnitMagazine("Etna", '76mm HE-MOM', 800)
    SM.AddToUnitMagazine("Etna", 'Mk-46 Mod5', 10)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Etna', 'SH-3D', 'King101', 2)
    SM.SetFlightDeckUnitLoadout('Etna', 'King101', '2 Mk-46 Mod5;10 DICASS (105) Sonobuoy;10 LOFAR (105) Sonobuoy;30 DIFAR (105) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Cassard(92)'
    unit.unitName = "Jean Bart"
    unit.SetPosition(17.057869, 33.865931, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 500000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-66A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Mistral 2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Mistral 2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'MM-40 B3 Exocet', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'MM-40 B3 Exocet', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, '100mm OEA F1 HE', 35)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'L5 Mod4', 2)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'L5 Mod4', 2)
    SM.SetUnitLauncherItem(unit.unitName, 10, '12.7mm B-30 AP', 34)
    SM.SetUnitLauncherItem(unit.unitName, 11, 'Chaff-Round-1', 6)
    SM.SetUnitLauncherItem(unit.unitName, 12, 'Sagaie Flare', 6)
    SM.SetUnitLauncherItem(unit.unitName, 13, 'Chaff-Round-1', 6)
    SM.SetUnitLauncherItem(unit.unitName, 14, 'Sagaie Flare', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Jean Bart", 'Fuel', 27290)
    SM.AddToUnitMagazine("Jean Bart", 'MU-90', 9)
    SM.AddToUnitMagazine("Jean Bart", 'AS-30L', 4)
    SM.AddToUnitMagazine("Jean Bart", '750 litre tank', 4)
    SM.AddToUnitMagazine("Jean Bart", 'DICASS (105) Sonobuoy', 108)
    SM.AddToUnitMagazine("Jean Bart", 'LOFAR (105) Sonobuoy', 108)
    SM.AddToUnitMagazine("Jean Bart", 'DIFAR (105) Sonobuoy', 324)
    SM.AddToUnitMagazine("Jean Bart", 'RIM-66A', 40)
    SM.AddToUnitMagazine("Jean Bart", '100mm OEA F1 HE', 600)
    SM.AddToUnitMagazine("Jean Bart", 'Mistral 2', 48)
    SM.AddToUnitMagazine("Jean Bart", 'L5 Mod4', 12)
    SM.AddToUnitMagazine("Jean Bart", '20mm F2', 700)
    SM.AddToUnitMagazine("Jean Bart", '12.7mm B-30 AP', 300)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Jean Bart', 'AS 565MB Panther', 'Coup 1', 1)
    SM.SetFlightDeckUnitLoadout('Jean Bart', 'Coup 1', '1 MU-90;0 Empty;24 DIFAR (105) Sonobuoy;8 DICASS (105) Sonobuoy;8 LOFAR (105) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 23 FF'
    unit.unitName = "HMS Westminster"
    unit.SetPosition(18.001129, 34.284591, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Sea Wolf', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '114mm N4A1 HE', 16)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm/75 GCM-AO3-2 APDS', 83)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm/75 GCM-AO3-2 APDS', 83)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Stingray', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Westminster", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Westminster", 'Stingray', 29)
    SM.AddToUnitMagazine("HMS Westminster", 'Sea Skua', 16)
    SM.AddToUnitMagazine("HMS Westminster", 'LOFAR (105) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Westminster", 'DICASS (105) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Westminster", 'DIFAR (105) Sonobuoy', 609)
    SM.AddToUnitMagazine("HMS Westminster", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Westminster", 'Sea Wolf', 20)
    SM.AddToUnitMagazine("HMS Westminster", '30mm/75 GCM-AO3-2 APDS', 1660)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('HMS Westminster', 'Lynx HAS.Mk.2', 'Type 23 Lynx 1', 2)
    SM.SetFlightDeckUnitLoadout('HMS Westminster', 'Type 23 Lynx 1', '1 Stingray;1 Stingray;')
    
    SM.AddUnitToFlightDeck('HMS Westminster', 'Lynx HAS.Mk.2', 'Type 23 Lynx 2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Westminster', 'Type 23 Lynx 2', '1 Stingray;1 Stingray;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Maestrale'
    unit.unitName = "ITS Euro"
    unit.SetPosition(19.063164, 34.361998, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '127mm mk 127 HE-CVT EX-175', 20)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Aspide 2000', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Otomat Mk-2', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '40 mm L70 HE x5', 24)
    SM.SetUnitLauncherItem(unit.unitName, 4, '40 mm L70 HE x5', 24)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'A-244S Mod1', 3)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'A-244S Mod1', 3)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'A-184', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'A-184', 1)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Chaff-Round-1', 6)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'Ship Flare-2', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("ITS Euro", 'Fuel', 100000)
    SM.AddToUnitMagazine("ITS Euro", 'A-244S Mod1', 32)
    SM.AddToUnitMagazine("ITS Euro", 'Aspide 2000', 16)
    SM.AddToUnitMagazine("ITS Euro", '40 mm L70 HE x5', 240)
    SM.AddToUnitMagazine("ITS Euro", 'A-184', 8)
    SM.AddToUnitMagazine("ITS Euro", 'Chaff-Round-1', 12)
    SM.AddToUnitMagazine("ITS Euro", 'Ship Flare-2', 12)
    SM.AddToUnitMagazine("ITS Euro", '127mm mk 127 HE-CVT EX-175', 200)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('ITS Euro', 'AB212ASW', 'Bell1', 2)
    SM.SetFlightDeckUnitLoadout('ITS Euro', 'Bell1', '1 A-244S Mod1;1 A-244S Mod1;')
    
    SM.AddUnitToFlightDeck('ITS Euro', 'AB212ASW', 'Bell2', 1)
    SM.SetFlightDeckUnitLoadout('ITS Euro', 'Bell2', '1 A-244S Mod1;1 A-244S Mod1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Andrea Doria'
    unit.unitName = "Andrea Doria"
    unit.SetPosition(18.865723, 34.861904, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Otomat Mk-2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'ASTER 30', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'ASTER 30', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'ASTER 15', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76x900mm HE', 85)
    SM.SetUnitLauncherItem(unit.unitName, 5, '76x900mm HE', 85)
    SM.SetUnitLauncherItem(unit.unitName, 6, '76x900mm HE', 85)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 8, '20mm F2', 100)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'MU-90', 2)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'MU-90', 2)
    SM.SetUnitLauncherItem(unit.unitName, 11, 'Decoy-1', 6)
    SM.SetUnitLauncherItem(unit.unitName, 12, 'Chaff-Round-1', 6)
    SM.SetUnitLauncherItem(unit.unitName, 13, 'Ship Flare-2', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Andrea Doria", 'Fuel', 100000)
    SM.AddToUnitMagazine("Andrea Doria", 'Marte Mk2/S', 10)
    SM.AddToUnitMagazine("Andrea Doria", 'Otomat Mk-2', 8)
    SM.AddToUnitMagazine("Andrea Doria", '76x900mm HE', 1275)
    SM.AddToUnitMagazine("Andrea Doria", '20mm F2', 1000)
    SM.AddToUnitMagazine("Andrea Doria", 'MU-90', 12)
    SM.AddToUnitMagazine("Andrea Doria", 'Decoy-1', 12)
    SM.AddToUnitMagazine("Andrea Doria", 'Chaff-Round-1', 12)
    SM.AddToUnitMagazine("Andrea Doria", 'Ship Flare-2', 12)
    SM.AddToUnitMagazine("Andrea Doria", 'ASTER 30', 30)
    SM.AddToUnitMagazine("Andrea Doria", 'ASTER 15', 15)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(5, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Andrea Doria', 'AW101 Series 110', 'HeloBravo1', 2)
    SM.SetFlightDeckUnitLoadout('Andrea Doria', 'HeloBravo1', '2 MU-90;2 MU-90;30 Flare-1;30 Chaff-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Lewis and Clark'
    unit.unitName = "USNS Lewis and Clark"
    unit.SetPosition(18.690227, 35.250713, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USNS Lewis and Clark", 'Fuel', 1000000)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USNS Lewis and Clark', 'SA-330J', 'Puma101', 1)
    SM.SetFlightDeckUnitLoadout('USNS Lewis and Clark', 'Puma101', '')
    
    SM.AddUnitToFlightDeck('USNS Lewis and Clark', 'SA-330J', 'Puma102', 1)
    SM.SetFlightDeckUnitLoadout('USNS Lewis and Clark', 'Puma102', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'E-3D/F'
    unit.unitName = "Eye-1"
    unit.SetPosition(18.346945, 36.696801, 10000.0)
    unit.heading = 90.00
    unit.speed = 100.0
    unit.cost = 270000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.266725, 0.635457, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.341385, 0.628998, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Arleigh Burke IIA DDGHM'
    unit.unitName = "USS Gridley"
    UI = SM.GetUnitInterface('USS Enterprise')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0020
    lat_deg = 57.296*leader_track.Lat + 0.0053
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -38.79
    unit.speed = 3.0
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-156', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-162B', 16)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'RIM-162B', 16)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, '127mm mk 127 HE-CVT mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'Mk-54', 3)
    SM.SetUnitLauncherItem(unit.unitName, 11, 'Mk-54', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Gridley", '120 gallon tank', 6)
    SM.AddToUnitMagazine("USS Gridley", 'AGM-114 Hellfire', 20)
    SM.AddToUnitMagazine("USS Gridley", 'AGM-119B', 4)
    SM.AddToUnitMagazine("USS Gridley", 'Chaff-1', 125)
    SM.AddToUnitMagazine("USS Gridley", 'DICASS (105) Sonobuoy', 193)
    SM.AddToUnitMagazine("USS Gridley", 'DIFAR (105) Sonobuoy', 578)
    SM.AddToUnitMagazine("USS Gridley", 'Flare-1', 125)
    SM.AddToUnitMagazine("USS Gridley", 'Fuel', 56117)
    SM.AddToUnitMagazine("USS Gridley", 'LOFAR (105) Sonobuoy', 193)
    SM.AddToUnitMagazine("USS Gridley", 'Mk-46 Mod5', 2)
    SM.AddToUnitMagazine("USS Gridley", 'Mk-50', 2)
    SM.AddToUnitMagazine("USS Gridley", 'Mk-54', 29)
    SM.AddToUnitMagazine("USS Gridley", 'BGM-109 TLAM', 36)
    SM.AddToUnitMagazine("USS Gridley", 'RIM-156', 10)
    SM.AddToUnitMagazine("USS Gridley", 'RIM-66M', 38)
    SM.AddToUnitMagazine("USS Gridley", 'RUM-139 Mod4 ASROC', 12)
    SM.AddToUnitMagazine("USS Gridley", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Gridley", '127mm mk 127 HE-CVT mk 67', 680)
    UI.SetSensorState(5, 0)
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
    BB.Write('InvMulti', '1')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"127mm mk 80 HE-PD EX-175": 0, "RIM-162B": 0, "Mk-54": 58, "RIM-162A": 0, "RIM-66M": 114, "Stingray": 0, "127mm mk 80 HE-PD mk 67": 0, "RIM-66C": 0, "127mm mk 127 HE-CVT EX-175": 0, "BGM-109 TASM": 0, "BGM-109G TLAM-N": 0, "MU-90": 0, "RUM-139 Mod4 ASROC": 36, "RIM-7P(v2)": 0, "RGM-84C Harpoon": 0, "Mk-50": 4, "RIM-156": 30, "127mm mk 127 HE-CVT mk 67": 680, "RGM-84G Harpoon": 0, "RIM-66H": 0, "20mm mark 244-0 ELC": 2092, "BGM-109 TLAM": 108, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "Mk-46 Mod5": 4, "Mk-15 Mod0": 0, "RGM-84A Harpoon": 0, "Mk-44": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 1, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 1, "WeaponList": {"20mm mark 244-0 ELC": [194, 194], "RIM-156": [1, 1], "RGM-84F Harpoon": [8, 8], "RIM-162B": [32, 32], "RIM-66M": [2, 2], "Mk-54": [6, 6], "127mm mk 127 HE-CVT mk 67": [20, 20]}}')
    leader_id = UI.LookupFriendlyId('USS Enterprise')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(0.590, 0.292, 1.006, 0.769)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('USS Gridley', 'SH-60B', 'Burke Seahawk 1', 2)
    SM.SetFlightDeckUnitLoadout('USS Gridley', 'Burke Seahawk 1', '1 Mk-54;1 120 gallon tank;1 Mk-54;25 Chaff-1;25 Flare-1;5 DICASS (105) Sonobuoy;5 LOFAR (105) Sonobuoy;15 DIFAR (105) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Gridley', 'SH-60B', 'Burke Seahawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Gridley', 'Burke Seahawk 2', '4 AGM-114 Hellfire;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (105) Sonobuoy;5 LOFAR (105) Sonobuoy;15 DIFAR (105) Sonobuoy;')
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 205ER Tsunami(Libya)'
    unit.unitName = "Al Ruha"
    unit.SetPosition(22.868407, 33.288562, 0.0)
    unit.heading = 90.00
    unit.speed = 42.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.457467, 0.598012, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.476417, 0.583999, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.441335, 0.580118, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Combattante II G (Libya)'
    unit.unitName = "Shouala"
    unit.SetPosition(13.742565, 33.269769, 0.0)
    unit.heading = 90.00
    unit.speed = 39.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Otomat Mk-1', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Otomat Mk-1', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 3, '40 mm L70 HE x5', 24)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Shouala", '76mm HE-MOM', 240)
    SM.AddToUnitMagazine("Shouala", '40 mm L70 HE x5', 240)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.226172, 0.601036, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.276362, 0.601474, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.296592, 0.586808, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.255108, 0.581555, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Combattante II G (Libya)'
    unit.unitName = "Wahg"
    unit.SetPosition(16.067914, 32.555920, 0.0)
    unit.heading = 90.00
    unit.speed = 39.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Otomat Mk-1', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Otomat Mk-1', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 3, '40 mm L70 HE x5', 24)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Wahg", '76mm HE-MOM', 240)
    SM.AddToUnitMagazine("Wahg", '40 mm L70 HE x5', 240)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.276618, 0.592718, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.301969, 0.583525, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 205ER Tsunami(Libya)'
    unit.unitName = "Al Bitar"
    unit.SetPosition(19.402356, 32.198968, 0.0)
    unit.heading = 90.00
    unit.speed = 42.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.312018, 0.590897, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.332759, 0.595856, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-1"
    unit.SetPosition(19.393074, 30.178661, 31.3)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-2"
    unit.SetPosition(19.381959, 30.179750, 31.3)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-3"
    unit.SetPosition(19.370844, 30.180208, 31.3)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-4"
    unit.SetPosition(19.360702, 30.180208, 31.3)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-5"
    unit.SetPosition(19.393189, 30.184219, 31.3)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-6"
    unit.SetPosition(19.382303, 30.185537, 31.3)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-7"
    unit.SetPosition(19.370443, 30.186339, 31.3)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-8"
    unit.SetPosition(19.360072, 30.187198, 31.3)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-9"
    unit.SetPosition(19.392673, 30.194475, 31.3)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-10"
    unit.SetPosition(19.380813, 30.194876, 31.3)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-11"
    unit.SetPosition(19.368953, 30.195735, 16.2)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-72 MBT'
    unit.unitName = "T-72 MBT (group 2)-12"
    unit.SetPosition(19.359614, 30.196194, 0.0)
    unit.heading = 281.10
    unit.speed = 25.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4 Shilka'
    unit.unitName = "ZSU-23-4 Shilka (8)"
    unit.SetPosition(19.385282, 30.214528, 53.9)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4 Shilka'
    unit.unitName = "ZSU-23-4 Shilka (7)"
    unit.SetPosition(19.365000, 30.214987, -0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-90 MBT'
    unit.unitName = "T-90 MBT (group 1)-1"
    unit.SetPosition(22.348849, 32.455710, 1885.2)
    unit.heading = 269.70
    unit.speed = 20.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-90 MBT'
    unit.unitName = "T-90 MBT (group 1)-2"
    unit.SetPosition(22.347932, 32.455825, 1885.2)
    unit.heading = 269.70
    unit.speed = 20.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-90 MBT'
    unit.unitName = "T-90 MBT (group 1)-3"
    unit.SetPosition(22.348849, 32.456627, 1885.2)
    unit.heading = 269.70
    unit.speed = 20.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-90 MBT'
    unit.unitName = "T-90 MBT (group 1)-4"
    unit.SetPosition(22.347875, 32.456684, 1507.5)
    unit.heading = 269.70
    unit.speed = 20.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-90 MBT'
    unit.unitName = "T-90 MBT (group 1)-5"
    unit.SetPosition(22.348792, 32.457314, 1132.6)
    unit.heading = 269.70
    unit.speed = 20.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-90 MBT'
    unit.unitName = "T-90 MBT (group 1)-6"
    unit.SetPosition(22.347818, 32.457429, 754.3)
    unit.heading = 269.70
    unit.speed = 20.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-90 MBT'
    unit.unitName = "T-90 MBT (group 1)-7"
    unit.SetPosition(22.348792, 32.457945, 379.1)
    unit.heading = 269.70
    unit.speed = 20.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'T-90 MBT'
    unit.unitName = "T-90 MBT (group 1)-8"
    unit.SetPosition(22.347703, 32.458117, 0.0)
    unit.heading = 269.70
    unit.speed = 20.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Gen105AT', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, '125mm 3VBM19 APFSDS', 39)
    SM.SetUnitLauncherItem(unit.unitName, 2, '12.7x108mm', 50)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (17)"
    unit.SetPosition(10.114767, 25.168260, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "Sa-8 Site (16)"
    unit.SetPosition(10.176590, 25.165624, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (15)"
    unit.SetPosition(14.537371, 27.026820, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (14)"
    unit.SetPosition(14.387830, 27.026820, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (13)"
    unit.SetPosition(23.888845, 31.897820, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (12)"
    unit.SetPosition(23.934568, 31.877825, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (11)"
    unit.SetPosition(22.318883, 32.448146, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (10)"
    unit.SetPosition(22.383684, 32.463159, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (9)"
    unit.SetPosition(22.338994, 32.484301, 163.7)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (8)"
    unit.SetPosition(23.241116, 32.178227, 70.2)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "Sa-8 Site (7)"
    unit.SetPosition(23.895033, 31.861839, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (6)"
    unit.SetPosition(19.400351, 30.235671, 51.8)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (5)"
    unit.SetPosition(19.341967, 30.232405, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33 OSA'
    unit.unitName = "SA-8 Site (4)"
    unit.SetPosition(16.609473, 31.073222, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4 Shilka'
    unit.unitName = "ZSU-23-4 Shilka (6)"
    unit.SetPosition(16.589305, 31.069381, 59.3)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4 Shilka'
    unit.unitName = "ZSU-23-4 Shilka (5)"
    unit.SetPosition(16.600191, 31.068980, -0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4 Shilka'
    unit.unitName = "ZSU-23-4 Shilka (4)"
    unit.SetPosition(15.066843, 32.337910, -0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4 Shilka'
    unit.unitName = "ZSU-23-4 Shilka (3)"
    unit.SetPosition(13.198828, 32.647823, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4 Shilka'
    unit.unitName = "ZSU-23-4 Shilka (2)"
    unit.SetPosition(12.515804, 32.263198, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4 Shilka'
    unit.unitName = "ZSU-23-4 Shilka (1)"
    unit.SetPosition(12.528352, 32.287261, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33M2 OSA-AK'
    unit.unitName = "SA-8 Site (3)"
    unit.SetPosition(12.573330, 32.283880, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M2', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33M2 OSA-AK'
    unit.unitName = "SA-8 Site (2)"
    unit.SetPosition(12.506122, 32.278723, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M2', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K33M2 OSA-AK'
    unit.unitName = "Sa-8 Site (1)"
    unit.SetPosition(13.172414, 32.685983, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M33M2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M2', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200A Angara'
    unit.unitName = "SA-5 Site (8)"
    unit.SetPosition(9.872808, 30.429217, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-860', 1)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5 Site (8)", 'V-860', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200A Angara'
    unit.unitName = "SA-5 Site (7)"
    unit.SetPosition(23.234699, 32.150381, 900.4)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-860', 1)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5 Site (7)", 'V-860', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200A Angara'
    unit.unitName = "SA-5 Site (6)"
    unit.SetPosition(22.041343, 32.443105, 349.8)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-860', 1)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5 Site (6)", 'V-860', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200A Angara'
    unit.unitName = "SA-5 Site (5)"
    unit.SetPosition(19.779592, 30.305571, 337.7)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-860', 1)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5 Site (5)", 'V-860', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200A Angara'
    unit.unitName = "SA-5 Site (4)"
    unit.SetPosition(18.060948, 30.696157, 237.5)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-860', 1)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5 Site (4)", 'V-860', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200A Angara'
    unit.unitName = "SA-5 Site (3)"
    unit.SetPosition(16.608213, 31.029331, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-860', 1)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5 Site (3)", 'V-860', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200A Angara'
    unit.unitName = "SA-5 Site (2)"
    unit.SetPosition(15.011380, 32.254087, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-860', 1)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5 Site (2)", 'V-860', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200A Angara'
    unit.unitName = "SA-5 Site (1)"
    unit.SetPosition(13.208224, 32.676472, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-860', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-860', 1)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5 Site (1)", 'V-860', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Tripolis AB"
    unit.SetPosition(13.159171, 32.663576, 10.0)
    unit.heading = 357.02
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Tripolis AB", 'Fuel', 1000456)
    SM.AddToUnitMagazine("Tripolis AB", 'Chaff-1', 10200)
    SM.AddToUnitMagazine("Tripolis AB", 'Flare-1', 10200)
    SM.AddToUnitMagazine("Tripolis AB", 'R-60', 300)
    SM.AddToUnitMagazine("Tripolis AB", 'R-24R', 328)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-1', 2)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-1', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-2', 2)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-2', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-3', 2)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-3', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-4', 2)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-4', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-5', 2)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-5', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-6', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-6', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-7', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-7', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-8', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-8', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-9', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-10', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-11', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-11', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-12', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-12', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-13', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-13', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-14', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-14', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-15', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-15', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-16', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-16', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-17', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-17', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-18', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-18', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-19', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-19', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-20', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-20', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-21', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-21', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-22', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-22', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-23', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-23', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-24', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-24', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-25', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-25', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-26', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-26', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-27', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-27', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-28', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-28', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-29', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-29', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-30', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-30', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-31', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-31', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-32', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-32', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-33', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-33', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-34', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-34', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-35', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-35', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-23', 'Tripolis AAW-36', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis AAW-36', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-1', 2)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-1', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-2', 2)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-2', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-3', 2)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-3', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-4', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-4', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-5', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-5', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-6', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-6', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-7', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-7', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-8', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-8', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-9', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-10', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-11', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-11', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-12', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-12', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-13', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-13', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-14', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-14', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-15', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-15', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-16', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-16', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-17', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-17', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tripolis AB', 'MiG-21F', 'Tripolis Fishbed AAW-18', 1)
    SM.SetFlightDeckUnitLoadout('Tripolis AB', 'Tripolis Fishbed AAW-18', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-6')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-7')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-8')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-9')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-10')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-11')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-12')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-13')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-14')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-15')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-16')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-17')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-18')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-19')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-20')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-21')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-22')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-23')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 6)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2613234,0.5813683,0.2441376,0.5790710,0.2108253,0.5845349,0.2184507,0.5914581,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2297540, 0.5684860, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2280270, 0.5811290, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-24')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-25')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-26')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-27')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-28')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-29')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-30')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-31')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-32')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-33')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-34')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-35')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-36')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2526461,0.5629061,0.2574126,0.5660283,0.2424426,0.5806178,0.2310980,0.5773821,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2297540, 0.5684860, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2392970, 0.5701700, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-4')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-5')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-6')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-7')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-8')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-9')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-10')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-11')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-12')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-13')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-14')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-15')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2245957,0.5717443,0.2365398,0.5718927,0.2357919,0.5702232,0.2240458,0.5703159,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2297540, 0.5684860, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2294870, 0.5700590, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-1')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-2')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-3')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-16')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-17')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-18')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 6)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2302689,0.5699557,0.2283858,0.5694391,0.2274308,0.5681477,0.2302508,0.5692948,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2297540, 0.5684860, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2282250, 0.5681080, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-4')
    FP.AddAircraftToMission(mission_id, 'Tripolis AAW-5')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-1')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-2')
    FP.AddAircraftToMission(mission_id, 'Tripolis Fishbed AAW-3')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2300886,0.5686231,0.2310887,0.5674229,0.2334059,0.5671024,0.2307592,0.5697376,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2297540, 0.5684860, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2306740, 0.5678250, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Ghadames AB"
    unit.SetPosition(9.703041, 30.146158, 10.0)
    unit.heading = 62.50
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Ghadames AB", 'Fuel', 1000456)
    SM.AddToUnitMagazine("Ghadames AB", 'Chaff-1', 10000)
    SM.AddToUnitMagazine("Ghadames AB", 'Flare-1', 10000)
    SM.AddToUnitMagazine("Ghadames AB", 'AM-39 Exocet', 100)
    SM.AddToUnitMagazine("Ghadames AB", 'R.550 Magic', 300)
    SM.AddToUnitMagazine("Ghadames AB", 'AIM-9M', 300)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    SM.AddUnitToFlightDeck('Ghadames AB', 'Mirage-F1', 'Ghadames AAW-1', 2)
    SM.SetFlightDeckUnitLoadout('Ghadames AB', 'Ghadames AAW-1', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Ghadames AB', 'Mirage-F1', 'Ghadames AAW-2', 2)
    SM.SetFlightDeckUnitLoadout('Ghadames AB', 'Ghadames AAW-2', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Ghadames AB', 'Mirage-F1', 'Ghadames AAW-3', 2)
    SM.SetFlightDeckUnitLoadout('Ghadames AB', 'Ghadames AAW-3', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Ghadames AB', 'Mirage-F1', 'Ghadames AAW-4', 2)
    SM.SetFlightDeckUnitLoadout('Ghadames AB', 'Ghadames AAW-4', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Ghadames AB', 'Mirage-F1', 'Ghadames AAW-5', 2)
    SM.SetFlightDeckUnitLoadout('Ghadames AB', 'Ghadames AAW-5', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Ghadames AB', 'Mirage-F1', 'Ghadames AAW-6', 2)
    SM.SetFlightDeckUnitLoadout('Ghadames AB', 'Ghadames AAW-6', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Ghadames AB', 'Mirage-F1', 'Ghadames AAW-7', 2)
    SM.SetFlightDeckUnitLoadout('Ghadames AB', 'Ghadames AAW-7', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Ghadames AB', 'Mirage-F1', 'Ghadames AAW-8', 2)
    SM.SetFlightDeckUnitLoadout('Ghadames AB', 'Ghadames AAW-8', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Ghadames AB', 'Mirage-F1', 'Ghadames AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Ghadames AB', 'Ghadames AAW-9', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Ghadames AB', 'Mirage-F1', 'Ghadames AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Ghadames AB', 'Ghadames AAW-10', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Ghadames AAW-1')
    FP.AddAircraftToMission(mission_id, 'Ghadames AAW-2')
    FP.AddAircraftToMission(mission_id, 'Ghadames AAW-3')
    FP.AddAircraftToMission(mission_id, 'Ghadames AAW-4')
    FP.AddAircraftToMission(mission_id, 'Ghadames AAW-5')
    FP.AddAircraftToMission(mission_id, 'Ghadames AAW-6')
    FP.AddAircraftToMission(mission_id, 'Ghadames AAW-7')
    FP.AddAircraftToMission(mission_id, 'Ghadames AAW-8')
    FP.AddAircraftToMission(mission_id, 'Ghadames AAW-9')
    FP.AddAircraftToMission(mission_id, 'Ghadames AAW-10')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 3)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.1866800,0.5922979,0.1861513,0.5896087,0.1968498,0.5844849,0.2281063,0.5850150,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1640230, 0.5395190, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1890810, 0.5868280, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Sabha AB"
    unit.SetPosition(14.463092, 26.994839, 10.0)
    unit.heading = 132.79
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Sabha AB", 'Fuel', 1003128)
    SM.AddToUnitMagazine("Sabha AB", 'Chaff-1', 862)
    SM.AddToUnitMagazine("Sabha AB", 'Flare-1', 862)
    SM.AddToUnitMagazine("Sabha AB", 'Kh-29T', 27)
    SM.AddToUnitMagazine("Sabha AB", 'Kh-31P', 40)
    SM.AddToUnitMagazine("Sabha AB", 'R-27R', 114)
    SM.AddToUnitMagazine("Sabha AB", 'R-73M', 71)
    SM.AddToUnitMagazine("Sabha AB", 'R-77', 68)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('InvMulti', '1')
    BB.Write('MagTonnage', '35')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    SM.AddUnitToFlightDeck('Sabha AB', 'Su-30MKK', 'Sabha AAW-1', 2)
    SM.SetFlightDeckUnitLoadout('Sabha AB', 'Sabha AAW-1', '4 R-27R;2 R-77;4 R-77;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Sabha AB', 'Su-30MKK', 'Sabha AAW-2', 2)
    SM.SetFlightDeckUnitLoadout('Sabha AB', 'Sabha AAW-2', '4 R-27R;2 R-77;4 R-77;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Sabha AB', 'Su-30MKK', 'Sabha AAW-3', 2)
    SM.SetFlightDeckUnitLoadout('Sabha AB', 'Sabha AAW-3', '4 R-27R;2 R-77;4 R-77;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Sabha AB', 'Su-30MKK', 'Sabha AAW-4', 2)
    SM.SetFlightDeckUnitLoadout('Sabha AB', 'Sabha AAW-4', '4 R-27R;2 R-77;4 R-77;30 Flare-1;30 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Sabha AAW-1')
    FP.AddAircraftToMission(mission_id, 'Sabha AAW-2')
    FP.AddAircraftToMission(mission_id, 'Sabha AAW-3')
    FP.AddAircraftToMission(mission_id, 'Sabha AAW-4')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2336258,0.5510382,0.2595021,0.5607598,0.2309598,0.5632245,0.2111997,0.5578845,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2497370, 0.4760240, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2341110, 0.5491490, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Ghat AB"
    unit.SetPosition(10.144362, 25.136645, 10.0)
    unit.heading = 351.52
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Ghat AB", 'Fuel', 1000456)
    SM.AddToUnitMagazine("Ghat AB", '30mm OP-84 FRAG Tracer AK-306', 143)
    SM.AddToUnitMagazine("Ghat AB", 'Chaff-1', 3439)
    SM.AddToUnitMagazine("Ghat AB", 'Flare-1', 1719)
    SM.AddToUnitMagazine("Ghat AB", 'Kh-29T', 68)
    SM.AddToUnitMagazine("Ghat AB", 'Kh-31P', 100)
    SM.AddToUnitMagazine("Ghat AB", 'R-27R', 286)
    SM.AddToUnitMagazine("Ghat AB", 'R-73M', 179)
    SM.AddToUnitMagazine("Ghat AB", 'R-77', 171)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('InvMulti', '1')
    BB.Write('MagTonnage', '35')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    SM.AddUnitToFlightDeck('Ghat AB', 'Su-35BM', 'Ghat AAW-1', 2)
    SM.SetFlightDeckUnitLoadout('Ghat AB', 'Ghat AAW-1', '5 30mm OP-84 FRAG Tracer AK-306;4 R-27R;2 R-77;4 R-77;24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Ghat AB', 'Su-35BM', 'Ghat AAW-2', 2)
    SM.SetFlightDeckUnitLoadout('Ghat AB', 'Ghat AAW-2', '5 30mm OP-84 FRAG Tracer AK-306;4 R-27R;2 R-77;4 R-77;24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Ghat AB', 'Su-35BM', 'Ghat AAW-3', 2)
    SM.SetFlightDeckUnitLoadout('Ghat AB', 'Ghat AAW-3', '5 30mm OP-84 FRAG Tracer AK-306;4 R-27R;2 R-77;4 R-77;24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Ghat AB', 'Su-35BM', 'Ghat AAW-4', 2)
    SM.SetFlightDeckUnitLoadout('Ghat AB', 'Ghat AAW-4', '5 30mm OP-84 FRAG Tracer AK-306;4 R-27R;2 R-77;4 R-77;24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Ghat AB', 'Su-35BM', 'Ghat AAW-5', 2)
    SM.SetFlightDeckUnitLoadout('Ghat AB', 'Ghat AAW-5', '5 30mm OP-84 FRAG Tracer AK-306;4 R-27R;2 R-77;4 R-77;24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Ghat AB', 'Su-35BM', 'Ghat AAW-6', 2)
    SM.SetFlightDeckUnitLoadout('Ghat AB', 'Ghat AAW-6', '5 30mm OP-84 FRAG Tracer AK-306;4 R-27R;2 R-77;4 R-77;24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Ghat AB', 'Su-35BM', 'Ghat AAW-7', 2)
    SM.SetFlightDeckUnitLoadout('Ghat AB', 'Ghat AAW-7', '5 30mm OP-84 FRAG Tracer AK-306;4 R-27R;2 R-77;4 R-77;24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Ghat AB', 'Su-35BM', 'Ghat AAW-8', 2)
    SM.SetFlightDeckUnitLoadout('Ghat AB', 'Ghat AAW-8', '5 30mm OP-84 FRAG Tracer AK-306;4 R-27R;2 R-77;4 R-77;24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Ghat AB', 'Su-35BM', 'Ghat AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Ghat AB', 'Ghat AAW-9', '5 30mm OP-84 FRAG Tracer AK-306;4 R-27R;2 R-77;4 R-77;24 Flare-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Ghat AB', 'Su-35BM', 'Ghat AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Ghat AB', 'Ghat AAW-10', '5 30mm OP-84 FRAG Tracer AK-306;4 R-27R;2 R-77;4 R-77;24 Flare-1;48 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Ghat AAW-1')
    FP.AddAircraftToMission(mission_id, 'Ghat AAW-2')
    FP.AddAircraftToMission(mission_id, 'Ghat AAW-3')
    FP.AddAircraftToMission(mission_id, 'Ghat AAW-4')
    FP.AddAircraftToMission(mission_id, 'Ghat AAW-5')
    FP.AddAircraftToMission(mission_id, 'Ghat AAW-6')
    FP.AddAircraftToMission(mission_id, 'Ghat AAW-7')
    FP.AddAircraftToMission(mission_id, 'Ghat AAW-8')
    FP.AddAircraftToMission(mission_id, 'Ghat AAW-9')
    FP.AddAircraftToMission(mission_id, 'Ghat AAW-10')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 3)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2837271,0.4802096,0.2462053,0.4836736,0.1857110,0.5408301,0.1703960,0.5609214,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1793830, 0.4303910, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2059570, 0.5174200, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Sirte AB"
    unit.SetPosition(16.597038, 31.061795, 10.0)
    unit.heading = 314.54
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Sirte AB", 'Fuel', 1000456)
    SM.AddToUnitMagazine("Sirte AB", 'Chaff-1', 10200)
    SM.AddToUnitMagazine("Sirte AB", 'Flare-1', 10200)
    SM.AddToUnitMagazine("Sirte AB", 'R-60', 200)
    SM.AddToUnitMagazine("Sirte AB", 'Kh-59MK', 196)
    SM.AddToUnitMagazine("Sirte AB", 'Kh-29T', 184)
    SM.AddToUnitMagazine("Sirte AB", 'KAB-500L', 188)
    SM.AddToUnitMagazine("Sirte AB", 'FAB-500', 224)
    SM.AddToUnitMagazine("Sirte AB", '3000 liter tank', 208)
    SM.AddToUnitMagazine("Sirte AB", '23mm AM-23', 200)
    SM.AddToUnitMagazine("Sirte AB", 'AM-39 Exocet', 200)
    SM.AddToUnitMagazine("Sirte AB", 'R.550 Magic', 200)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Su-24M', 'Sirte ASuW -1', 2)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte ASuW -1', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Su-24M', 'Sirte ASuW -2', 2)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte ASuW -2', '2 KAB-500L;2 KAB-500L;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Su-24M', 'Sirte ASuW -3', 2)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte ASuW -3', '2 KAB-500L;2 Kh-59MK;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Su-24M', 'Sirte ASuW -4', 2)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte ASuW -4', '2 KAB-500L;2 KAB-500L;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Mirage-F1', 'Sirte AAW-1', 2)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AAW-1', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Mirage-F1', 'Sirte AAW-2', 2)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AAW-2', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Mirage-F1', 'Sirte AAW-3', 2)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AAW-3', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Mirage-F1', 'Sirte AAW-4', 2)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AAW-4', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Mirage-F1', 'Sirte AAW-5', 1)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AAW-5', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Mirage-F1', 'Sirte AAW-6', 1)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AAW-6', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Mirage-F1', 'Sirte AAW-7', 1)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AAW-7', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Mirage-F1', 'Sirte AAW-8', 1)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AAW-8', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Mirage-F1', 'Sirte AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AAW-9', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'Mirage-F1', 'Sirte AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AAW-10', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'A-50', 'Sirte AEW-1', 1)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AEW-1', '')
    
    SM.AddUnitToFlightDeck('Sirte AB', 'A-50', 'Sirte AEW-2', 1)
    SM.SetFlightDeckUnitLoadout('Sirte AB', 'Sirte AEW-2', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Sirte ASuW -1')
    FP.AddAircraftToMission(mission_id, 'Sirte ASuW -2')
    FP.AddAircraftToMission(mission_id, 'Sirte ASuW -3')
    FP.AddAircraftToMission(mission_id, 'Sirte ASuW -4')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.2977150, 0.5910720)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2926388, 0.5390733, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAllAir,RadarRandom')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2971840, 0.5863844, 6000.0, 500.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3011786, 0.5897090, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Sirte AAW-1')
    FP.AddAircraftToMission(mission_id, 'Sirte AAW-2')
    FP.AddAircraftToMission(mission_id, 'Sirte AAW-3')
    FP.AddAircraftToMission(mission_id, 'Sirte AAW-4')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.2877600, 0.5947250)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2926388, 0.5390733, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAllAir,RadarRandom')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2882473, 0.5900342, 6000.0, 500.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2922516, 0.5933589, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Sirte AAW-5')
    FP.AddAircraftToMission(mission_id, 'Sirte AAW-6')
    FP.AddAircraftToMission(mission_id, 'Sirte AAW-7')
    FP.AddAircraftToMission(mission_id, 'Sirte AAW-8')
    FP.AddAircraftToMission(mission_id, 'Sirte AAW-9')
    FP.AddAircraftToMission(mission_id, 'Sirte AAW-10')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.3141780, 0.5983790)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 6)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2926388, 0.5390733, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAllAir,RadarRandom')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3121827, 0.5938813, 6000.0, 500.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3161974, 0.5972059, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Sirte AEW-1')
    FP.AddAircraftToMission(mission_id, 'Sirte AEW-2')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2782769,0.5358245,0.2965841,0.5305998,0.2978046,0.5343794,0.2796901,0.5398263,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2897540, 0.5433980, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2881690, 0.5379920, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Misurata AB"
    unit.SetPosition(15.060694, 32.323504, 10.0)
    unit.heading = 325.83
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Misurata AB", 'Fuel', 1000456)
    SM.AddToUnitMagazine("Misurata AB", 'Chaff-1', 10000)
    SM.AddToUnitMagazine("Misurata AB", 'Flare-1', 10000)
    SM.AddToUnitMagazine("Misurata AB", 'R-23T', 100)
    SM.AddToUnitMagazine("Misurata AB", 'R-24R', 260)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-1', 2)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-1', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-2', 2)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-2', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-3', 2)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-3', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-4', 2)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-4', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-5', 2)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-5', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-6', 2)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-6', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-7', 2)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-7', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-8', 2)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-8', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-9', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-10', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-11', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-11', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-12', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-12', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-13', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-13', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-14', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-14', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-15', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-15', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-16', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-16', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-17', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-17', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-18', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-18', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-19', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-19', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Misurata AB', 'MiG-23', 'Misurata AAW-20', 1)
    SM.SetFlightDeckUnitLoadout('Misurata AB', 'Misurata AAW-20', '2 R-24R;0 Empty;0 Empty;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-1')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-2')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-3')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-4')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-5')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-6')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-7')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-8')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 3)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2704933,0.5702934,0.2904321,0.5677669,0.2904321,0.5659373,0.2661253,0.5673313,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2664760, 0.5624360, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2765320, 0.5661200, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-9')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-10')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-11')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-12')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-13')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-14')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-15')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-16')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-17')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-18')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-19')
    FP.AddAircraftToMission(mission_id, 'Misurata AAW-20')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2965715,0.5829448,0.2649554,0.5845400,0.2584314,0.5726290,0.3076120,0.5708210,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2664760, 0.5624360, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2747250, 0.5690160, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ'
    unit.unitName = "Derna Army HQ"
    unit.SetPosition(22.354120, 32.450439, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 0.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ'
    unit.unitName = "Brega Army HQ"
    unit.SetPosition(19.375026, 30.214127, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 0.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Metiga AB"
    unit.SetPosition(13.275302, 32.894653, 10.0)
    unit.heading = 105.28
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Metiga AB", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Metiga AB", 'Chaff-1', 10000)
    SM.AddToUnitMagazine("Metiga AB", 'Flare-1', 10000)
    SM.AddToUnitMagazine("Metiga AB", 'R-24R', 180)
    UI.SetSensorState(0, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    SM.AddUnitToFlightDeck('Metiga AB', 'MiG-23', 'Metiga AAW-1', 1)
    SM.SetFlightDeckUnitLoadout('Metiga AB', 'Metiga AAW-1', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Metiga AB', 'MiG-23', 'Metiga AAW-2', 1)
    SM.SetFlightDeckUnitLoadout('Metiga AB', 'Metiga AAW-2', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Metiga AB', 'MiG-23', 'Metiga AAW-3', 1)
    SM.SetFlightDeckUnitLoadout('Metiga AB', 'Metiga AAW-3', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Metiga AB', 'MiG-23', 'Metiga AAW-4', 1)
    SM.SetFlightDeckUnitLoadout('Metiga AB', 'Metiga AAW-4', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Metiga AB', 'MiG-23', 'Metiga AAW-5', 1)
    SM.SetFlightDeckUnitLoadout('Metiga AB', 'Metiga AAW-5', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Metiga AB', 'MiG-23', 'Metiga AAW-6', 1)
    SM.SetFlightDeckUnitLoadout('Metiga AB', 'Metiga AAW-6', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Metiga AB', 'MiG-23', 'Metiga AAW-7', 1)
    SM.SetFlightDeckUnitLoadout('Metiga AB', 'Metiga AAW-7', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Metiga AB', 'MiG-23', 'Metiga AAW-8', 1)
    SM.SetFlightDeckUnitLoadout('Metiga AB', 'Metiga AAW-8', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Metiga AB', 'MiG-23', 'Metiga AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Metiga AB', 'Metiga AAW-9', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Metiga AB', 'MiG-23', 'Metiga AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Metiga AB', 'Metiga AAW-10', '2 R-24R;0 Empty;0 Empty;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Metiga AAW-1')
    FP.AddAircraftToMission(mission_id, 'Metiga AAW-2')
    FP.AddAircraftToMission(mission_id, 'Metiga AAW-3')
    FP.AddAircraftToMission(mission_id, 'Metiga AAW-4')
    FP.AddAircraftToMission(mission_id, 'Metiga AAW-5')
    FP.AddAircraftToMission(mission_id, 'Metiga AAW-6')
    FP.AddAircraftToMission(mission_id, 'Metiga AAW-7')
    FP.AddAircraftToMission(mission_id, 'Metiga AAW-8')
    FP.AddAircraftToMission(mission_id, 'Metiga AAW-9')
    FP.AddAircraftToMission(mission_id, 'Metiga AAW-10')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2576051,0.6081638,0.2339181,0.6036431,0.2416465,0.6018850,0.2892212,0.5971968,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2311680, 0.5687430, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2568320, 0.6001070, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Tobruk AB"
    unit.SetPosition(23.914303, 31.858113, 10.0)
    unit.heading = 329.22
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Tobruk AB", 'Fuel', 2000000)
    SM.AddToUnitMagazine("Tobruk AB", '30mm NR-30 HEI x2', 18793)
    SM.AddToUnitMagazine("Tobruk AB", 'AM-39 Exocet', 97)
    SM.AddToUnitMagazine("Tobruk AB", 'FAB-100', 469)
    SM.AddToUnitMagazine("Tobruk AB", 'FAB-250', 626)
    SM.AddToUnitMagazine("Tobruk AB", 'FAB-500', 469)
    SM.AddToUnitMagazine("Tobruk AB", 'PTB-400', 12)
    SM.AddToUnitMagazine("Tobruk AB", 'S-24B 240mm', 939)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('InvMulti', '1')
    BB.Write('MagTonnage', '35')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'Mirage-F1', 'Tobruk AAW-1', 2)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW-1', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'Mirage-F1', 'Tobruk AAW-2', 2)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW-2', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'Mirage-F1', 'Tobruk AAW-3', 2)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW-3', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'Mirage-F1', 'Tobruk AAW-4', 2)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW-4', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'Mirage-F1', 'Tobruk AAW-5', 2)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW-5', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'Mirage-F1', 'Tobruk AAW-6', 2)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW-6', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'Mirage-F1', 'Tobruk AAW-7', 2)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW-7', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'Mirage-F1', 'Tobruk AAW-8', 2)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW-8', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'Mirage-F1', 'Tobruk AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW-9', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'Mirage-F1', 'Tobruk AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW-10', '1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AIM-9M;1 AM-39 Exocet;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-1', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-1', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-2', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-2', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-3', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-3', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-4', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-4', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-5', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-5', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-6', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-6', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-7', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-7', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-8', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-8', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-9', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-9', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-10', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-10', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-11', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-11', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    
    SM.AddUnitToFlightDeck('Tobruk AB', 'MiG-21F', 'Tobruk AAW Fishbed-12', 1)
    SM.SetFlightDeckUnitLoadout('Tobruk AB', 'Tobruk AAW Fishbed-12', '0 Empty;1 PTB-400;60 30mm NR-30 HEI x2;1 FAB-100;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW-1')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW-2')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW-3')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW-4')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW-5')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW-6')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW-7')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW-8')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW-9')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW-10')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 3)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.4997907,0.5974599,0.4373056,0.6054708,0.4553532,0.5906996,0.4912145,0.5850557,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4028570, 0.5676720, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4611730, 0.5883740, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-1')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-2')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-3')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-4')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-5')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-6')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-7')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-8')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-9')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-10')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-11')
    FP.AddAircraftToMission(mission_id, 'Tobruk AAW Fishbed-12')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0376101,0.0255664,-0.0085547,0.0332203,0.0292993,0.0467959,-0.0151859,0.0494180,')
    FP.SetMissionPatrolAnchor(mission_id, 'Tobruk AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.4028570, 0.5676720, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4033060, 0.5930670, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PMU'
    unit.unitName = "SA-10 Site (1)"
    unit.SetPosition(12.539410, 32.339802, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55RUD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10 Site (1)", '5V55RUD', 72)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PMU'
    unit.unitName = "SA-10 Site (2)"
    unit.SetPosition(12.510992, 32.210828, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55RUD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10 Site (2)", '5V55RUD', 72)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gas Processing Plant'
    unit.unitName = "Chemical Plant"
    unit.SetPosition(12.503142, 32.266978, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 0.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Combattante II G (Libya)'
    unit.unitName = "Shehab"
    unit.SetPosition(15.570758, 32.464133, 0.0)
    unit.heading = 90.00
    unit.speed = 39.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Otomat Mk-1', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Otomat Mk-1', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 3, '40 mm L70 HE x5', 24)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Shehab", '76mm HE-MOM', 240)
    SM.AddToUnitMagazine("Shehab", '40 mm L70 HE x5', 240)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.278411, 0.599066, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.305042, 0.606289, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.322199, 0.598847, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.307091, 0.585057, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Combattante II G (Libya)'
    unit.unitName = "Shouaae"
    unit.SetPosition(15.669021, 32.166023, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Otomat Mk-1', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Otomat Mk-1', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 3, '40 mm L70 HE x5', 24)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Shouaae", '76mm HE-MOM', 240)
    SM.AddToUnitMagazine("Shouaae", '40 mm L70 HE x5', 240)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.261254, 0.601693, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.325528, 0.595783, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.293007, 0.577615, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 205ER Tsunami(Libya)'
    unit.unitName = "Al Fikah"
    unit.SetPosition(23.180325, 32.941177, 0.0)
    unit.heading = 90.00
    unit.speed = 42.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.456955, 0.596072, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.471551, 0.583352, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.452090, 0.583999, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 205ER Tsunami(Libya)'
    unit.unitName = "Al Sadad"
    unit.SetPosition(22.815294, 32.953095, 0.0)
    unit.heading = 90.00
    unit.speed = 42.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.453626, 0.595856, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.475136, 0.585723, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.454650, 0.578824, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 205ER Tsunami(Libya)'
    unit.unitName = "Al Zuara"
    unit.SetPosition(19.670386, 31.808268, 0.0)
    unit.heading = 90.00
    unit.speed = 42.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.294349, 0.588742, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.305872, 0.600815, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.326358, 0.594562, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 205ER Tsunami(Libya)'
    unit.unitName = "Al Mathur"
    unit.SetPosition(19.824798, 32.130270, 0.0)
    unit.heading = 90.00
    unit.speed = 42.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.328150, 0.607498, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.343771, 0.596072, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.319700, 0.590035, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.318163, 0.603186, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1159TR Koni(Libya)'
    unit.unitName = "Al Hani"
    unit.SetPosition(13.506907, 33.048492, 0.0)
    unit.heading = 90.00
    unit.speed = 7.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M', 16)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm Br-83 AP', 250)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm Br-83 AP', 250)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'SAET-40', 2)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'SAET-40', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Al Hani", '76.2mm OS-62 FRAG', 1200)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.227196, 0.581117, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.257157, 0.574550, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1159TR Koni(Libya)'
    unit.unitName = "Al Ghadabia"
    unit.SetPosition(18.168148, 30.961608, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20K', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M', 16)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm Br-83 AP', 250)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm Br-83 AP', 250)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'SAET-40', 2)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'SAET-40', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Al Ghadabia", '76.2mm OS-62 FRAG', 1200)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.303311, 0.547779, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.329943, 0.537647, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641 SSK(Libya)'
    unit.unitName = "Al Hunain"
    unit.SetPosition(12.907880, 34.169312, -70.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Al Hunain", '53-65M', 4)
    SM.AddToUnitMagazine("Al Hunain", 'SAET-60M', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.220026, 0.603663, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.263558, 0.578490, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641 SSK(Libya)'
    unit.unitName = "Al Kiber"
    unit.SetPosition(17.246144, 33.201243, -70.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'SAET-60M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Al Kiber", '53-65M', 8)
    SM.AddToUnitMagazine("Al Kiber", 'SAET-60M', 16)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.300689, 0.593156, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.283788, 0.595564, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.306835, 0.609791, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.329625, 0.601693, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.313749, 0.583963, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Communications Station'
    unit.unitName = "Com Center Tripolis"
    unit.SetPosition(13.166799, 32.627138, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 0.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"115.0": 0.0, "117.0": 0.0, "127.0": 0.0, "126.0": 0.0, "128.0": 0.0, "118.0": 0.0, "131.0": 0.0, "123.0": 0.0, "120.0": 0.0, "125.0": 0.0, "130.0": 0.0, "124.0": 0.0, "129.0": 0.0, "122.0": 0.0, "121.0": 0.0, "116.0": 0.0, "132.0": 0.0}')
    BB.Write('MissionTarget', '["Target", 121]')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 81, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 12, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"DART Test": 0, "TEST-71ME": 0, "V-860": 576, "SAET-60M": 240, "P-20K": 0, "23mm OFZ": 0, "53-56": 0, "SET-65M": 0, "SET-72": 0, "USET-80": 0, "76mm HE-SAPOM": 0, "76mm HE-SAPOMER": 0, "TEST-71MKE": 0, "125mm 3VBM19 APFSDS": 0, "9M33": 0, "V-860P": 0, "53-56V": 0, "Shkval": 0, "30mm OF-83 HE-FRAG": 0, "53-65KE": 0, "SET-65": 0, "TEST-71": 0, "Otomat Mk-2": 0, "Otomat Mk-1": 0, "3M10 Granat(n)": 0, "5V55RUD": 576, "5V55PM": 0, "12.7x108mm": 0, "76.2mm OS-62 FRAG": 4800, "9M33M": 0, "30mm F-33 HE": 0, "UMGT-1M": 0, "9M33M2": 0, "Gen105AT": 0, "40 mm L70 HE x5": 960, "76.2mm ZS-63 AA": 0, "76mm HE-MOM": 960, "5V55U": 0, "5V55V": 0, "SAET-40": 0, "30mm Br-83 AP": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "3M54E Klub Alfa": 0, "53-65M": 120, "RPK-6 Vodopod": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 250.0, "MobileLand": 55, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 2, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"MissileWarning": 16, "Nav": 14, "EngageAll": 50}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 12, "TargetSet": 1, "FormModePace": 0, "WeaponList": {"5V55RUD": [32, 32], "9M33M2": [72, 72], "Gen105AT": [800, 800], "40 mm L70 HE x5": [96, 96], "Otomat Mk-1": [16, 16], "76mm HE-MOM": [320, 320], "V-860": [48, 48], "SAET-40": [8, 8], "125mm 3VBM19 APFSDS": [780, 780], "P-20K": [32, 32], "23mm OFZ": [200, 200], "12.7x108mm": [1000, 1000], "76.2mm OS-62 FRAG": [1000, 1000], "9M33M": [32, 32], "9M33": [336, 336], "SAET-60M": [12, 12], "30mm OF-83 HE-FRAG": [3000, 3000], "53-65M": [8, 8], "30mm Br-83 AP": [1000, 1000]}}')
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Ferry'
    unit.unitName = "Ferry "
    boxes = [[23.1563, 23.1963, 34.1265, 34.1665]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 16.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.388279, 0.577887, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.427332, 0.611366, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Generic submarine'
    unit.unitName = "Neutral Sub (2)"
    unit.SetPosition(17.596050, 34.223056, -100.0)
    unit.heading = 90.00
    unit.speed = 7.2
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MK-T1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'UGM-84C Harpoon', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Neutral Sub (2)", 'MK-T1', 15)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.264993, 0.606010, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.335442, 0.604336, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.303281, 0.615384, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.309407, 0.575878, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Generic submarine'
    unit.unitName = "Neutral Sub (1)"
    unit.SetPosition(26.809669, 33.705159, -100.0)
    unit.heading = 90.00
    unit.speed = 4.9
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MK-T1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'UGM-84C Harpoon', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Neutral Sub (1)", 'MK-T1', 15)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.457580, 0.597975, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.475192, 0.585253, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.325870, 0.603331, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Cruiser'
    unit.unitName = "Neutral Cruiser"
    unit.SetPosition(11.958202, 34.625902, 0.0)
    unit.heading = 90.00
    unit.speed = 16.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SAM-I', 10)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SAM-I', 10)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SSM-I', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.222877, 0.589605, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.256953, 0.579896, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.295623, 0.588601, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Civilian Airport (1)"
    unit.SetPosition(14.210213, 37.289411, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Civilian Airport (1)", 'Fuel', 1000228)
    UI.SetSensorState(0, 1)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Civilian Airport (1)', 'Boeing 767', 'Civilian Airliner (Group 2)-1', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (1)', 'Civilian Airliner (Group 2)-1', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (1)', 'Boeing 767', 'Civilian Airliner (Group 2)-2', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (1)', 'Civilian Airliner (Group 2)-2', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (1)', 'Boeing 767', 'Civilian Airliner (Group 2)-3', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (1)', 'Civilian Airliner (Group 2)-3', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (1)', 'Boeing 767', 'Civilian Airliner (Group 2)-4', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (1)', 'Civilian Airliner (Group 2)-4', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 2)-1')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (3)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2539271, 0.6508230, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.1802242, 0.6164976, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 2)-2')
    FP.SetMissionLaunchTime(mission_id, '06:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (2)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2539271, 0.6508230, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.4504136, 0.5458856, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 2)-3')
    FP.SetMissionLaunchTime(mission_id, '07:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (4)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2539271, 0.6508230, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3803121, 0.6527846, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 2)-4')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (4)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2539271, 0.6508230, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3803121, 0.6527846, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Civilian Airport (2)"
    unit.SetPosition(26.122120, 31.276964, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Civilian Airport (2)", 'Fuel', 1000228)
    UI.SetSensorState(0, 1)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Civilian Airport (2)', 'Airbus A330', 'Civilian Airliner (Group 3)-1', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (2)', 'Civilian Airliner (Group 3)-1', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (2)', 'Airbus A330', 'Civilian Airliner (Group 3)-2', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (2)', 'Civilian Airliner (Group 3)-2', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (2)', 'Airbus A330', 'Civilian Airliner (Group 3)-3', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (2)', 'Civilian Airliner (Group 3)-3', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (2)', 'Airbus A330', 'Civilian Airliner (Group 3)-4', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (2)', 'Civilian Airliner (Group 3)-4', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 3)-1')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (1)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4614204, 0.5458860, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.2421029, 0.6508226, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 3)-2')
    FP.SetMissionLaunchTime(mission_id, '04:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (3)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4614204, 0.5458860, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.1802242, 0.6164976, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 3)-3')
    FP.SetMissionLaunchTime(mission_id, '04:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (4)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4614204, 0.5458860, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3803121, 0.6527846, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 3)-4')
    FP.SetMissionLaunchTime(mission_id, '08:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (3)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4614204, 0.5458860, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.1802242, 0.6164976, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Civilian Airport (3)"
    unit.SetPosition(10.656385, 35.322734, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Civilian Airport (3)", 'Fuel', 1000228)
    UI.SetSensorState(0, 1)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Civilian Airport (3)', 'Airbus A330', 'Civilian Airliner Group 1-1', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (3)', 'Civilian Airliner Group 1-1', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (3)', 'Airbus A330', 'Civilian Airliner Group 1-2', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (3)', 'Civilian Airliner Group 1-2', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (3)', 'Airbus A330', 'Civilian Airliner Group 1-3', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (3)', 'Civilian Airliner Group 1-3', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (3)', 'Airbus A330', 'Civilian Airliner Group 1-4', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (3)', 'Civilian Airliner Group 1-4', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner Group 1-1')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (4)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1917538, 0.6164980, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3803121, 0.6527846, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner Group 1-2')
    FP.SetMissionLaunchTime(mission_id, '06:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (1)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1917538, 0.6164980, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.2421029, 0.6508226, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner Group 1-3')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (2)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1917538, 0.6164980, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.4504136, 0.5458856, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner Group 1-4')
    FP.SetMissionLaunchTime(mission_id, '08:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (4)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.1917538, 0.6164980, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3803121, 0.6527846, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Civilian Airport (4)"
    unit.SetPosition(22.129521, 37.401826, 109.4)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Civilian Airport (4)", 'Fuel', 2000456)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "Alt+": 0, "Speed+": 0, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 1, "Launchers": 0, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 0, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {}}')
    
    SM.AddUnitToFlightDeck('Civilian Airport (4)', 'Airbus A330', 'Civilian Airliner (Group 4)-1', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (4)', 'Civilian Airliner (Group 4)-1', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (4)', 'Airbus A330', 'Civilian Airliner (Group 4)-2', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (4)', 'Civilian Airliner (Group 4)-2', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (4)', 'Airbus A330', 'Civilian Airliner (Group 4)-3', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (4)', 'Civilian Airliner (Group 4)-3', '')
    
    SM.AddUnitToFlightDeck('Civilian Airport (4)', 'Airbus A330', 'Civilian Airliner (Group 4)-4', 2)
    SM.SetFlightDeckUnitLoadout('Civilian Airport (4)', 'Civilian Airliner (Group 4)-4', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 4)-1')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (3)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3921539, 0.6527850, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.1802242, 0.6164976, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 4)-2')
    FP.SetMissionLaunchTime(mission_id, '06:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (1)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3921539, 0.6527850, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.2421029, 0.6508226, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 4)-3')
    FP.SetMissionLaunchTime(mission_id, '08:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (2)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3921539, 0.6527850, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.4504136, 0.5458856, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Civilian Airliner (Group 4)-4')
    FP.SetMissionLaunchTime(mission_id, '09:00:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, 'Civilian Airport (3)')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3921539, 0.6527850, 9000.0, 500.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.1802242, 0.6164976, 0.0, 0.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'Land')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'AAW cruiser'
    unit.unitName = "Neutral AAW Cruiser"
    unit.SetPosition(15.738922, 32.844748, 0.0)
    unit.heading = 90.00
    unit.speed = 16.5
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SA-SAM', 10)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SA-SAM', 10)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SSM-I', 10)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.247129, 0.584705, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.302263, 0.553610, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.332128, 0.560811, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 206A'
    unit.unitName = "U 24"
    unit.SetPosition(16.413637, 35.408219, -100.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DM2A1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DM2A1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DM2A1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'DM2A1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'DM2A1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'DM2A1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'DM2A1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'DM2A1', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(2, 0)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.274220, 0.624425, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.279581, 0.597078, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.345818, 0.604799, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.307531, 0.617347, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Container Ship'
    unit.unitName = "Morning Star"
    unit.SetPosition(25.736978, 34.412819, 0.0)
    unit.heading = 90.00
    unit.speed = 10.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.404781, 0.586139, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.309828, 0.583243, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.219469, 0.611234, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.201474, 0.637616, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.196879, 0.668502, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.124133, 0.670755, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877EKM Paltus(Iran)'
    unit.unitName = "Yunes"
    unit.SetPosition(35.369430, 26.773229, -100.0)
    unit.heading = 90.00
    unit.speed = 2.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M32M Strela 3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65KE', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-65KE', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-65KE', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65KE', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65KE', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '53-65KE', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.620108, 0.447452, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.607856, 0.464969, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.624703, 0.453057, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 971 Shchuka-B'
    unit.unitName = "K-322 kashalot"
    unit.SetPosition(7.086514, 38.347378, -100.0)
    unit.heading = 90.00
    unit.speed = 8.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Igla-M SAM', 18)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-322 kashalot", 'SET-65M', 8)
    SM.AddToUnitMagazine("K-322 kashalot", '65-76 Kit', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(7, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.115260, 0.673433, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.134786, 0.676622, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.168862, 0.665462, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.212127, 0.649838, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.246969, 0.636128, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.269941, 0.581924, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.327373, 0.566938, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.369106, 0.583837, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.416966, 0.592127, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.460230, 0.577460, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.398970, 0.608388, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.287554, 0.624012, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.235100, 0.628157, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.196812, 0.656853, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.091904, 0.675984, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 5, "Alt+": 0, "Speed+": 50, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"SET-65": 0, "TEST-71": 0, "Shkval": 0, "53-56V": 0, "TEST-71MKE": 0, "3M10 Granat(n)": 0, "TEST-71ME": 0, "USET-80": 0, "RPK-7 Veter": 0, "RPK-6 Vodopod": 0, "SAET-60M": 0, "Igla-M SAM": 0, "53-65KE": 0, "3M80M Moskit-M": 0, "3M10 Granat": 0, "SET-65M": 32, "53-56": 0, "3M54E Klub Alfa": 0, "53-65M": 0, "65-76 Kit": 32}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 375.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 0, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 1}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"SET-65M": [4, 4], "Igla-M SAM": [18, 18], "65-76 Kit": [4, 4]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877E Paltus'
    unit.unitName = "Neutral Sub (3)"
    unit.SetPosition(17.462780, 37.653182, -100.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 250000000.0
    SM.AddUnitToAlliance(unit, 3)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65KE', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65KE', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Igla-M SAM', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Neutral Sub (3)", 'TEST-71ME', 12)
    SM.AddToUnitMagazine("Neutral Sub (3)", '53-65KE', 6)
    SM.AddToUnitMagazine("Neutral Sub (3)", 'Igla-M SAM', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.346134, 0.636766, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.300571, 0.623374, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.279130, 0.639316, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Dolphin'
    unit.unitName = "Dolphin"
    unit.SetPosition(15.195528, 35.116412, -17.6)
    unit.heading = 90.00
    unit.speed = 12.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.286722, 0.602552, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.304903, 0.606863, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.303623, 0.620010, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.263163, 0.618932, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Boat'
    unit.unitName = "NEU Boat"
    unit.SetPosition(17.689728, 31.189531, 0.0)
    unit.heading = 90.00
    unit.speed = 25.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.290819, 0.549748, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.279040, 0.558584, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.249335, 0.576473, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'CASA C-212-400'
    unit.unitName = "Temp 729"
    unit.SetPosition(12.158394, 35.844985, 4000.0)
    unit.heading = 90.00
    unit.speed = 100.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Land', 3.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('LandTarget', 'Civilian Airport (1)')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Boeing 747'
    unit.unitName = "Temp 0690"
    unit.SetPosition(17.454987, 36.289543, 10000.0)
    unit.heading = 90.00
    unit.speed = 464.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Land', 3.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('LandTarget', 'Civilian Airport (2)')
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(599940.0)
    goal_temp.SetFailTimeout(43200.0)
    goal_0_0 = goal_temp

    goal_temp = SM.ProtectGoal('')
    goal_temp.AddTarget('Charles de Gaulle')
    goal_temp.AddTarget('USS Enterprise')
    goal_temp.AddTarget('USS Scranton')
    goal_temp.AddTarget('USS Providence')
    goal_temp.AddTarget('USS Florida')
    goal_temp.AddTarget('USS Mount Whitney')
    goal_temp.AddTarget('USS Ponce')
    goal_temp.AddTarget('USS Keersarge')
    goal_temp.AddTarget('USNS Robert E Peary')
    goal_temp.AddTarget('USNS Kanawha')
    goal_temp.AddTarget('HMCS Charlottetown')
    goal_temp.AddTarget('USS Stout')
    goal_temp.AddTarget('USS Barry')
    goal_temp.AddTarget('Etna')
    goal_temp.AddTarget('Jean Bart')
    goal_temp.AddTarget('HMS Westminster')
    goal_temp.AddTarget('ITS Euro')
    goal_temp.AddTarget('Andrea Doria')
    goal_temp.AddTarget('USNS Lewis and Clark')
    goal_temp.SetQuantity(19)
    goal_0_1 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('SA-5 Site (2)')
    goal_temp.AddTarget('Com Center Tripolis')
    goal_temp.AddTarget('Chemical Plant')
    goal_temp.AddTarget('SA-10 Site (2)')
    goal_temp.AddTarget('SA-10 Site (1)')
    goal_temp.AddTarget('SA-5 Site (1)')
    goal_temp.AddTarget('SA-5 Site (3)')
    goal_temp.AddTarget('SA-5 Site (4)')
    goal_temp.AddTarget('SA-5 Site (5)')
    goal_temp.AddTarget('SA-5 Site (6)')
    goal_temp.AddTarget('SA-5 Site (7)')
    goal_temp.AddTarget('SA-5 Site (8)')
    goal_temp.AddTarget('Brega Army HQ')
    goal_temp.AddTarget('Derna Army HQ')
    goal_temp.SetQuantity(14)
    goal_0_2 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_0_0)
    goal_temp.AddGoal(goal_0_1)
    goal_temp.AddGoal(goal_0_2)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 0, 0, 0)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(43200.0)
    goal_temp.SetFailTimeout(599940.0)
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
    SM.SetIncludeProbability('Ferry ', 1.000000)
    SM.AddRandomBox('Ferry ', 23.1563, 23.1963, 34.1265, 34.1665)
    SM.SetIncludeProbability('Temp 0728', 0.500000)
