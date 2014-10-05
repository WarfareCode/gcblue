# Created on 05/22/11 21:09:20
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Samurai\n\na scenario for GCB2 by Ralf Koelbach\nVersion 2.0\nJuly, 5th, 2010\n\nJapan finds itself attacked by far superior forces. Fight with the heart \nand spirit of a real Samurai. The scenario is a \nheavily modified variation of the tutorial scen "Defend Japan".\n\nComments and critiques welcome!\n\nrkoelbach@yahoo.com \n\n\n\n\n\n\n\n\n\n\n""")
    SM.SetScenarioName("""Samurai""")
    SM.CreateAlliance(1, 'Japan')
    SM.SetAllianceDefaultCountry(1, 'Japan')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'China')
    SM.SetAllianceDefaultCountry(2, 'China')
    SM.SetAlliancePlayable(2, 1)
    SM.SetUserAlliance(1)

    SM.SetDateTime(2010,9,1,4,0,0)
    SM.SetStartTheater(133.116669, 38.450001) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """ORDERS FOR CMDR JAPANESE OPERATIONS\n\nINTELLIGENCE\nVast numbers of Chinese aircraft are approaching. The Chinese \nKusnetzov class carrier has been detected, too. Leading an \namhibious assault group, it is closing to our home turf. \n\nThis is a direct threat to our motherland.\n\nThe US have given us all units that could be ferried right in time. They \nact under your command.\n\nMISSION\nDefend your airspace and bases against the Chinese aggression. You \nmust no lose even one base. Sink the carrier and the LSTs in order to \nstop the aggression. \n\nCounterstrike when you are ready to do so. You have all assets needed \nfor taht at your disposal. \n\nEXECUTION\nWeapons free. \n\nCOMMAND AND SIGNAL\nMisawa AB\n\nGood Luck, Samurai!\n\n\n\n\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """This scenario is meant to be played from Japanese side.\n""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Los Angeles (1988)'
    unit.unitName = "USS Annapolis "
    unit.SetPosition(135.308913, 39.180115, -400.0)
    unit.heading = 272.28
    unit.speed = 3.0
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
    SM.AddToUnitMagazine("USS Annapolis ", 'Mk-48 Mod6', 12)
    SM.AddToUnitMagazine("USS Annapolis ", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-2A'
    unit.unitName = "Spirit-8"
    unit.SetPosition(134.451111, 32.054209, 50.0)
    unit.heading = 47.61
    unit.speed = 262.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-2A'
    unit.unitName = "Spirit-7"
    unit.SetPosition(134.684075, 32.300639, 50.0)
    unit.heading = 312.33
    unit.speed = 262.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-2A'
    unit.unitName = "Spirit-6"
    unit.SetPosition(134.944482, 32.121419, 213.1)
    unit.heading = 47.61
    unit.speed = 262.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-2A'
    unit.unitName = "Spirit-5"
    unit.SetPosition(134.711518, 31.807838, 213.1)
    unit.heading = 47.61
    unit.speed = 262.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-1B'
    unit.unitName = "Bone-8"
    unit.SetPosition(144.846040, 45.639540, 50.0)
    unit.heading = 327.97
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(2, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.223388)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-1B'
    unit.unitName = "Bone-7"
    unit.SetPosition(145.167236, 46.003541, 50.0)
    unit.heading = 327.97
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(2, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.223388)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-1B'
    unit.unitName = "Bone-6"
    unit.SetPosition(145.218640, 45.309918, 50.0)
    unit.heading = 327.97
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(2, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.223388)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-1B'
    unit.unitName = "Bone-5"
    unit.SetPosition(145.643478, 45.617024, 50.0)
    unit.heading = 327.97
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(2, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.223388)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-2A'
    unit.unitName = "Spirit-1"
    unit.SetPosition(127.901948, 33.661614, 213.1)
    unit.heading = 47.61
    unit.speed = 262.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-2A'
    unit.unitName = "Spirit-2"
    unit.SetPosition(128.134912, 33.975195, 213.1)
    unit.heading = 47.61
    unit.speed = 262.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-2A'
    unit.unitName = "Spirit-3"
    unit.SetPosition(127.874505, 34.154416, 50.0)
    unit.heading = 47.61
    unit.speed = 262.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-2A'
    unit.unitName = "Spirit-4"
    unit.SetPosition(127.641541, 33.907986, 50.0)
    unit.heading = 47.61
    unit.speed = 262.5
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-1B'
    unit.unitName = "Bone-1"
    unit.SetPosition(145.867551, 40.472879, 50.0)
    unit.heading = 276.23
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(2, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.223388)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-1B'
    unit.unitName = "Bone-2"
    unit.SetPosition(145.442703, 40.165774, 50.0)
    unit.heading = 276.23
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(2, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.223388)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-1B'
    unit.unitName = "Bone-3"
    unit.SetPosition(145.391309, 40.859397, 50.0)
    unit.heading = 276.23
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(2, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.223388)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'B-1B'
    unit.unitName = "Bone-4"
    unit.SetPosition(145.070109, 40.495397, 50.0)
    unit.heading = 276.23
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'GBU-31A(v)2', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(2, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    UI.SetThrottle(0.224446)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Los Angeles (1988)'
    unit.unitName = "USS Hampton "
    unit.SetPosition(135.392451, 38.796921, -400.0)
    unit.heading = 272.28
    unit.speed = 3.0
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
    SM.AddToUnitMagazine("USS Hampton ", 'Mk-48 Mod6', 12)
    SM.AddToUnitMagazine("USS Hampton ", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'E-2C 2000 NP'
    unit.unitName = "Eye-1"
    unit.SetPosition(139.153192, 39.081795, 10000.0)
    unit.heading = 90.00
    unit.speed = 100.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(1, 1)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.440396, 0.704444, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.465028, 0.740556, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.692330')
    BB.Write('StationLongitude', '2.419167')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Hyakuri"
    unit.SetPosition(140.430545, 36.220960, -0.0)
    unit.heading = 298.58
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Hyakuri", 'Fuel', 9000000)
    SM.AddToUnitMagazine("Hyakuri", '1400 liter tank', 200)
    SM.AddToUnitMagazine("Hyakuri", '20mm PGU', 500)
    SM.AddToUnitMagazine("Hyakuri", 'AGM-65G', 150)
    SM.AddToUnitMagazine("Hyakuri", 'AGM-65F', 150)
    SM.AddToUnitMagazine("Hyakuri", 'AGM-88C', 150)
    SM.AddToUnitMagazine("Hyakuri", 'AIM-120D', 584)
    SM.AddToUnitMagazine("Hyakuri", 'AIM-9X', 216)
    SM.AddToUnitMagazine("Hyakuri", 'Chaff-1', 600)
    SM.AddToUnitMagazine("Hyakuri", 'Flare-1', 600)
    SM.AddToUnitMagazine("Hyakuri", 'Mk-82', 224)
    SM.AddToUnitMagazine("Hyakuri", 'Mk-84', 200)
    SM.AddToUnitMagazine("Hyakuri", 'Mk-83', 100)
    SM.AddToUnitMagazine("Hyakuri", 'B-83', 100)
    SM.AddToUnitMagazine("Hyakuri", 'FPU-8', 100)
    SM.AddToUnitMagazine("Hyakuri", 'GBU-31A(v)2', 100)
    SM.AddToUnitMagazine("Hyakuri", 'GBU-31C(v)4', 100)
    SM.AddToUnitMagazine("Hyakuri", 'AGM-84F Harpoon', 388)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Hyakuri', 'KC-767A', 'Bar-1', 2)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Bar-1', '')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'KC-767A', 'Bar-2', 2)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Bar-2', '')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'KC-767A', 'Bar-3', 2)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Bar-3', '')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'KC-767A', 'Bar-4', 2)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Bar-4', '')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-16C/D Blk 52+', 'Terminator-1', 3)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Terminator-1', '2 AIM-9X;2 AIM-120D;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-16C/D Blk 52+', 'Terminator-2', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Terminator-2', '2 AIM-9X;2 AIM-120D;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-16C/D Blk 52+', 'Terminator-3', 3)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Terminator-3', '2 AIM-9X;2 AIM-120D;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-16C/D Blk 52+', 'Terminator-4', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Terminator-4', '2 AIM-9X;2 AIM-120D;4 AGM-65G;2 AGM-65G;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'A-6E', 'Sea Eagle-1', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Sea Eagle-1', '1 AGM-84F Harpoon;1 300 gallon wing tank;1 AGM-84F Harpoon;1 300 gallon wing tank;1 AGM-84F Harpoon;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'A-6E', 'Sea Eagle-2', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Sea Eagle-2', '1 AGM-84F Harpoon;1 300 gallon wing tank;1 AGM-84F Harpoon;1 300 gallon wing tank;1 AGM-84F Harpoon;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'A-6E', 'Sea Eagle-3', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Sea Eagle-3', '1 AGM-84F Harpoon;1 300 gallon wing tank;1 AGM-84F Harpoon;1 300 gallon wing tank;1 AGM-84F Harpoon;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'A-6E', 'Sea Eagle-4', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Sea Eagle-4', '1 AGM-84F Harpoon;1 300 gallon wing tank;1 AGM-84F Harpoon;1 300 gallon wing tank;1 AGM-84F Harpoon;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F/A-18D', 'Hornet-1', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Hornet-1', '1 AGM-84F Harpoon;2 AIM-120C;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9M;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F/A-18D', 'Hornet-2', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Hornet-2', '1 AGM-84F Harpoon;2 AIM-120C;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9M;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F/A-18D', 'Hornet-3', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Hornet-3', '1 AGM-84F Harpoon;2 AIM-120C;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9M;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F/A-18D', 'Hornet-4', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Hornet-4', '1 AGM-84F Harpoon;2 AIM-120C;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9M;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-1', 2)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-1', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-2', 2)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-2', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-3', 2)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-3', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-4', 2)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-4', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-5', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-5', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-6', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-6', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-7', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-7', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-8', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-8', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-9', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-9', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-10', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-10', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-11', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-11', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-12', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-12', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-13', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-13', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-14', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-14', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-15', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-15', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-16', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-16', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-17', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-17', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-18', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-18', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-19', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-19', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'F-22', 'Goalkeeper-20', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Goalkeeper-20', '0 empty;0 empty;2 AIM-9X;2 AIM-120D;4 AIM-120D;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'E-3D/F', 'Big Eye-1', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Big Eye-1', '')
    
    SM.AddUnitToFlightDeck('Hyakuri', 'E-3D/F', 'Big Eye-2', 1)
    SM.SetFlightDeckUnitLoadout('Hyakuri', 'Big Eye-2', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Komatsu"
    unit.SetPosition(136.435195, 36.395253, 0.0)
    unit.heading = 319.09
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Komatsu", 'Fuel', 4016440)
    SM.AddToUnitMagazine("Komatsu", 'AIM-120D', 200)
    SM.AddToUnitMagazine("Komatsu", 'AAM-4b', 380)
    SM.AddToUnitMagazine("Komatsu", 'AIM-9M', 120)
    SM.AddToUnitMagazine("Komatsu", 'AAM-5', 120)
    SM.AddToUnitMagazine("Komatsu", 'Chaff-1', 400)
    SM.AddToUnitMagazine("Komatsu", 'Flare-1', 400)
    SM.AddToUnitMagazine("Komatsu", '20mm PGU', 460)
    SM.AddToUnitMagazine("Komatsu", 'AGM-84F Harpoon', 170)
    SM.AddToUnitMagazine("Komatsu", 'AGM-65J', 100)
    SM.AddToUnitMagazine("Komatsu", 'AGM-88C', 60)
    SM.AddToUnitMagazine("Komatsu", 'Mk-84', 100)
    SM.AddToUnitMagazine("Komatsu", 'Mk-83', 100)
    SM.AddToUnitMagazine("Komatsu", 'Mk-82', 100)
    SM.AddToUnitMagazine("Komatsu", 'GBU-31A(v)2', 100)
    SM.AddToUnitMagazine("Komatsu", '1400 liter tank', 10)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Komatsu', 'F-15J', 'Warrior-1', 3)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Warrior-1', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F-15J', 'Warrior-2', 3)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Warrior-2', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F-15J', 'Warrior-3', 2)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Warrior-3', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F-15J', 'Warrior-4', 2)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Warrior-4', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F-15J', 'Warrior-5', 2)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Warrior-5', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F-15J', 'Warrior-6', 2)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Warrior-6', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F-15J', 'Warrior-7', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Warrior-7', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F-15J', 'Warrior-8', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Warrior-8', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F-15J', 'Warrior-9', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Warrior-9', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F-15J', 'Warrior-10', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Warrior-10', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F/A-18D', 'Dove-1', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Dove-1', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9X;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F/A-18D', 'Dove-2', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Dove-2', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9X;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F/A-18D', 'Dove-3', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Dove-3', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9X;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F/A-18D', 'Dove-4', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Dove-4', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9X;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F/A-18D', 'Dove-5', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Dove-5', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9X;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F/A-18D', 'Dove-6', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Dove-6', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9X;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F/A-18D', 'Dove-7', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Dove-7', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9X;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F/A-18D', 'Dove-8', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Dove-8', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9X;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F/A-18D', 'Dove-9', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Dove-9', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9X;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Komatsu', 'F/A-18D', 'Dove-10', 1)
    SM.SetFlightDeckUnitLoadout('Komatsu', 'Dove-10', '1 AGM-84F Harpoon;2 AIM-120D;2 AGM-84F Harpoon;2 AGM-88C;2 AIM-9X;6 20mm PGU;25 Flare-1;25 Chaff-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Chitose"
    unit.SetPosition(141.731331, 42.771357, -0.0)
    unit.heading = 270.79
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Chitose", 'Fuel', 2516440)
    SM.AddToUnitMagazine("Chitose", 'AAM-14b', 640)
    SM.AddToUnitMagazine("Chitose", 'AAM-5', 340)
    SM.AddToUnitMagazine("Chitose", 'AGM-88C', 60)
    SM.AddToUnitMagazine("Chitose", 'FPU-8', 32)
    SM.AddToUnitMagazine("Chitose", '600 gallon tank', 60)
    SM.AddToUnitMagazine("Chitose", 'Chaff-1', 400)
    SM.AddToUnitMagazine("Chitose", 'Flare-1', 400)
    SM.AddToUnitMagazine("Chitose", '20mm PGU', 660)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Chitose', 'F-15J', 'Dragon-1', 3)
    SM.SetFlightDeckUnitLoadout('Chitose', 'Dragon-1', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Chitose', 'F-15J', 'Dragon-2', 3)
    SM.SetFlightDeckUnitLoadout('Chitose', 'Dragon-2', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Chitose', 'F-15J', 'Dragon-3', 2)
    SM.SetFlightDeckUnitLoadout('Chitose', 'Dragon-3', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Chitose', 'F-15J', 'Dragon-4', 2)
    SM.SetFlightDeckUnitLoadout('Chitose', 'Dragon-4', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Chitose', 'F-15J', 'Dragon-5', 2)
    SM.SetFlightDeckUnitLoadout('Chitose', 'Dragon-5', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Chitose', 'F-15J', 'Dragon-6', 2)
    SM.SetFlightDeckUnitLoadout('Chitose', 'Dragon-6', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Chitose', 'F-15J', 'Dragon-7', 1)
    SM.SetFlightDeckUnitLoadout('Chitose', 'Dragon-7', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Chitose', 'F-15J', 'Dragon-8', 1)
    SM.SetFlightDeckUnitLoadout('Chitose', 'Dragon-8', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Chitose', 'F-15J', 'Dragon-9', 1)
    SM.SetFlightDeckUnitLoadout('Chitose', 'Dragon-9', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Chitose', 'F-15J', 'Dragon-10', 1)
    SM.SetFlightDeckUnitLoadout('Chitose', 'Dragon-10', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Chitose', 'EA-6B', 'White Noise-1', 2)
    SM.SetFlightDeckUnitLoadout('Chitose', 'White Noise-1', '2 FPU-8;2 AGM-88C;')
    
    SM.AddUnitToFlightDeck('Chitose', 'EA-6B', 'White Noise-2', 2)
    SM.SetFlightDeckUnitLoadout('Chitose', 'White Noise-2', '2 FPU-8;2 AGM-88C;')
    
    SM.AddUnitToFlightDeck('Chitose', 'EA-6B', 'White Noise-3', 2)
    SM.SetFlightDeckUnitLoadout('Chitose', 'White Noise-3', '2 FPU-8;2 AGM-88C;')
    
    SM.AddUnitToFlightDeck('Chitose', 'EA-6B', 'White Noise-4', 2)
    SM.SetFlightDeckUnitLoadout('Chitose', 'White Noise-4', '2 FPU-8;2 AGM-88C;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Misawa"
    unit.SetPosition(141.297716, 40.728992, 0.0)
    unit.heading = 269.87
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Misawa", 'Fuel', 6032880)
    SM.AddToUnitMagazine("Misawa", 'AAM-4b', 546)
    SM.AddToUnitMagazine("Misawa", 'AAM-5', 580)
    SM.AddToUnitMagazine("Misawa", 'Mk-82', 300)
    SM.AddToUnitMagazine("Misawa", 'Mk-83', 312)
    SM.AddToUnitMagazine("Misawa", 'Mk-84', 212)
    SM.AddToUnitMagazine("Misawa", '600 gallon tank', 60)
    SM.AddToUnitMagazine("Misawa", 'Flare-1', 700)
    SM.AddToUnitMagazine("Misawa", 'Chaff-1', 800)
    SM.AddToUnitMagazine("Misawa", '20mm PGU', 920)
    SM.AddToUnitMagazine("Misawa", 'GBU-31A(v)2', 200)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Misawa', 'E-2C 2000 NP', 'AEW-2', 3)
    SM.SetFlightDeckUnitLoadout('Misawa', 'AEW-2', '')
    
    SM.AddUnitToFlightDeck('Misawa', 'E-2C 2000 NP', 'AEW-4', 2)
    SM.SetFlightDeckUnitLoadout('Misawa', 'AEW-4', '')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-1', 2)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-1', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-2', 2)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-2', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-3', 3)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-3', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-4', 2)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-4', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-5', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-5', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-6', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-6', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-7', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-7', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-8', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-8', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-9', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-9', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-10', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-10', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-11', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-11', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-12', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-12', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-13', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-13', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-14', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-14', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-15', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-15', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-16', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-16', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-17', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-17', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-18', 1)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-18', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-19', 2)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-19', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Misawa', 'F-15J', 'Storm-20', 2)
    SM.SetFlightDeckUnitLoadout('Misawa', 'Storm-20', '4 AAM-4b;2 AAM-5;2 AAM-5;3 600 gallon tank;25 Chaff-1;25 Flare-1;46 20mm PGU;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MIM-23 I-Hawk'
    unit.unitName = "SAM I-Hawk (1)"
    unit.SetPosition(141.494110, 42.750673, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'MIM-23B', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SAM I-Hawk (1)", 'MIM-23B', 36)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MIM-23 I-Hawk'
    unit.unitName = "SAM I-Hawk (2)"
    unit.SetPosition(141.195427, 40.725210, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'MIM-23B', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SAM I-Hawk (2)", 'MIM-23B', 36)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MIM-104 Patriot PAC-1'
    unit.unitName = "SAM Patriot"
    unit.SetPosition(140.372545, 36.217522, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MIM-104A', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MIM-104A', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MIM-104A', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MIM-104A', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'MIM-104A', 8)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'MIM-104A', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SAM Patriot", 'MIM-104A', 48)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MIM-23 I-Hawk'
    unit.unitName = "SAM I-Hawk (3)"
    unit.SetPosition(136.415298, 36.396399, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'MIM-23B', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'MIM-23B', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SAM I-Hawk (3)", 'MIM-23B', 36)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 945 Barrakuda'
    unit.unitName = "K-276 Krab"
    unit.SetPosition(134.808721, 39.647763, -700.0)
    unit.heading = 90.00
    unit.speed = 7.7
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '65-76 Kit', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'RPK-7 Veter', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RPK-7 Veter', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("K-276 Krab", '53-65M', 30)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(5, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.355764, 0.681644, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.367551, 0.664614, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.388369, 0.675927, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.379491, 0.698675, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.339385, 0.658654, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.358979, 0.645151, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.380409, 0.681036, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.362193, 0.705608, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.337854, 0.693931, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.357907, 0.661695, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 18"
    unit.SetPosition(128.891678, 38.879941, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.188156, 0.676841, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.243766, 0.670438, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.676840')
    BB.Write('StationLongitude', '2.425579')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 10"
    unit.SetPosition(128.883987, 38.716765, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.189352, 0.677790, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.241972, 0.667830, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.650164')
    BB.Write('StationLongitude', '2.390291')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 9"
    unit.SetPosition(130.562696, 36.043229, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.230980, 0.627321, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.280311, 0.608021, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.650164')
    BB.Write('StationLongitude', '2.390291')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 17"
    unit.SetPosition(130.570387, 36.206406, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.229784, 0.626588, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.289280, 0.606311, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.676840')
    BB.Write('StationLongitude', '2.425579')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 8"
    unit.SetPosition(136.129955, 38.044857, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.650164')
    BB.Write('StationLongitude', '2.390291')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 16"
    unit.SetPosition(136.137646, 38.208034, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.676840')
    BB.Write('StationLongitude', '2.425579')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 7"
    unit.SetPosition(130.428280, 46.544113, 9058.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.436236, 0.691473, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.427865, 0.669620, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.650164')
    BB.Write('StationLongitude', '2.390291')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 15"
    unit.SetPosition(130.435971, 46.707290, 9537.1)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.436236, 0.691473, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.427865, 0.669620, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.676840')
    BB.Write('StationLongitude', '2.425579')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 6"
    unit.SetPosition(140.723415, 44.280471, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.436236, 0.691473, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.427865, 0.669620, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.650164')
    BB.Write('StationLongitude', '2.390291')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 14"
    unit.SetPosition(140.731106, 44.443648, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.436236, 0.691473, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.427865, 0.669620, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.676840')
    BB.Write('StationLongitude', '2.425579')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 5"
    unit.SetPosition(128.292236, 41.585163, 6874.9)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.154022, 0.734250, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.231457, 0.712678, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.650164')
    BB.Write('StationLongitude', '2.390291')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 13"
    unit.SetPosition(128.299927, 41.748340, 6165.1)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.150136, 0.730879, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.228766, 0.706386, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.676840')
    BB.Write('StationLongitude', '2.425579')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 4"
    unit.SetPosition(136.737348, 38.981700, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.436236, 0.691473, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.427865, 0.669620, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.650164')
    BB.Write('StationLongitude', '2.390291')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 12"
    unit.SetPosition(136.745039, 39.144877, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.436236, 0.691473, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.427865, 0.669620, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.676840')
    BB.Write('StationLongitude', '2.425579')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200D Dubna'
    unit.unitName = "SA-5C (5)"
    unit.SetPosition(124.273968, 45.890826, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-880M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5C (5)", 'V-880M', 12)
    UI.SetSensorState(2, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200D Dubna'
    unit.unitName = "SA-5C (4)"
    unit.SetPosition(132.202043, 45.635804, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-880M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5C (4)", 'V-880M', 12)
    UI.SetSensorState(2, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200D Dubna'
    unit.unitName = "SA-5C (3)"
    unit.SetPosition(125.787210, 42.420021, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-880M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5C (3)", 'V-880M', 12)
    UI.SetSensorState(2, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Communications Station'
    unit.unitName = "Com Center"
    unit.SetPosition(126.478142, 44.997756, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PMU-2'
    unit.unitName = "SA-20B (3)"
    unit.SetPosition(126.728411, 44.932267, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55RUD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-20B (3)", '5V55RUD', 72)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PMU-2'
    unit.unitName = "SA-20B (2)"
    unit.SetPosition(126.175507, 45.141110, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55RUD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-20B (2)", '5V55RUD', 72)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10C (3)"
    unit.SetPosition(125.959154, 45.038838, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10C (3)", '5V55R', 72)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fuel Tanks'
    unit.unitName = "Fuel Tanks"
    unit.SetPosition(126.087442, 44.956274, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammunition Bunker"
    unit.SetPosition(126.216587, 45.060037, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10C (2)"
    unit.SetPosition(126.554118, 45.149648, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10C (2)", '5V55R', 72)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10C (1)"
    unit.SetPosition(125.926097, 44.696094, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10C (1)", '5V55R', 72)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200D Dubna'
    unit.unitName = "SA-5C (2)"
    unit.SetPosition(126.109445, 44.463473, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-880M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5C (2)", 'V-880M', 12)
    UI.SetSensorState(2, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-200D Dubna'
    unit.unitName = "SA-5C (1)"
    unit.SetPosition(126.947394, 45.003658, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-880M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'V-880M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-5C (1)", 'V-880M', 12)
    UI.SetSensorState(2, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PMU-2'
    unit.unitName = "SA-20B (1)"
    unit.SetPosition(126.469150, 44.828561, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55RUD', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55RUD', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-20B (1)", '5V55RUD', 72)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-41"
    unit.SetPosition(134.979010, 45.002915, 818.3)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.392331, 0.776063, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.479153, 0.767381, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.473891, 0.747005, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746501')
    BB.Write('DatumLongitude', '2.473678')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.634949')
    BB.Write('StationLongitude', '2.381544')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-42"
    unit.SetPosition(134.773490, 44.754194, 1240.5)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.433980, 0.662333, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.380882, 0.634300, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635217')
    BB.Write('DatumLongitude', '2.381243')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-43"
    unit.SetPosition(135.304509, 44.853658, 10.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.501136, 0.721022, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.451014, 0.631599, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.631269')
    BB.Write('DatumLongitude', '2.442995')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-5"
    unit.SetPosition(134.465120, 45.015978, 1793.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.386914, 0.672498, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.463152, 0.654156, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.450819, 0.631003, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.632175')
    BB.Write('DatumLongitude', '2.450975')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-6"
    unit.SetPosition(134.722099, 43.742178, 1653.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635217')
    BB.Write('DatumLongitude', '2.381243')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-7"
    unit.SetPosition(134.588651, 43.548173, 473.5)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.299171, 0.682666, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.322132, 0.642526, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.380970, 0.635058, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635217')
    BB.Write('DatumLongitude', '2.381243')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-8"
    unit.SetPosition(134.263206, 43.792598, 10.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.362577, 0.736345, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.463107, 0.690177, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.451209, 0.631865, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.631269')
    BB.Write('DatumLongitude', '2.442995')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-10"
    unit.SetPosition(135.085465, 43.573899, 1799.7)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710110')
    BB.Write('DatumLongitude', '2.459795')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-11"
    unit.SetPosition(133.064125, 41.747138, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.367088, 0.732772, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.469457, 0.745899, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746978')
    BB.Write('DatumLongitude', '2.466304')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-12"
    unit.SetPosition(133.595145, 41.952945, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.367805, 0.734960, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.473762, 0.746264, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746501')
    BB.Write('DatumLongitude', '2.473678')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-13"
    unit.SetPosition(133.817850, 41.592724, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.370675, 0.718186, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.464673, 0.710528, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710110')
    BB.Write('DatumLongitude', '2.459795')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-14"
    unit.SetPosition(133.081255, 42.030123, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.376982, 0.656315, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.408075, 0.642268, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.381526, 0.634378, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635647')
    BB.Write('DatumLongitude', '2.380679')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-15"
    unit.SetPosition(132.601858, 40.213559, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635217')
    BB.Write('DatumLongitude', '2.381243')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-16"
    unit.SetPosition(132.934584, 40.616636, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746501')
    BB.Write('DatumLongitude', '2.473678')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-17"
    unit.SetPosition(132.390669, 40.653761, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635217')
    BB.Write('DatumLongitude', '2.381243')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-18"
    unit.SetPosition(133.311242, 40.390375, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.631269')
    BB.Write('DatumLongitude', '2.442995')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-19"
    unit.SetPosition(131.582398, 36.825659, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.381757, 0.635113, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746978')
    BB.Write('DatumLongitude', '2.466304')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-20"
    unit.SetPosition(131.739560, 37.370028, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.381757, 0.635113, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.631269')
    BB.Write('DatumLongitude', '2.442995')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-21"
    unit.SetPosition(131.564065, 37.109446, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.381757, 0.635113, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746501')
    BB.Write('DatumLongitude', '2.473678')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-22"
    unit.SetPosition(132.035498, 37.056792, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.381757, 0.635113, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635217')
    BB.Write('DatumLongitude', '2.381243')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-23"
    unit.SetPosition(130.908832, 38.950418, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.316018, 0.664218, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.449660, 0.632364, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.631269')
    BB.Write('DatumLongitude', '2.442995')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-24"
    unit.SetPosition(130.841445, 39.494784, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.310039, 0.675714, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.450258, 0.631885, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.632175')
    BB.Write('DatumLongitude', '2.450975')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-25"
    unit.SetPosition(130.482205, 39.196274, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.307647, 0.689605, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.406309, 0.645776, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.448763, 0.671403, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.465805, 0.709244, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710855')
    BB.Write('DatumLongitude', '2.466110')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-26"
    unit.SetPosition(131.245615, 39.319173, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.373721, 0.685294, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.465805, 0.709962, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710110')
    BB.Write('DatumLongitude', '2.459795')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-27"
    unit.SetPosition(131.127070, 40.515737, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.329681, 0.715976, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.396890, 0.729449, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.470080, 0.745541, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746978')
    BB.Write('DatumLongitude', '2.466304')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-28"
    unit.SetPosition(131.194443, 40.986306, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.426549, 0.694832, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.470319, 0.746290, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746501')
    BB.Write('DatumLongitude', '2.473678')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-29"
    unit.SetPosition(130.835202, 40.750992, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.306480, 0.690528, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.380626, 0.635140, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635217')
    BB.Write('DatumLongitude', '2.381243')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-30"
    unit.SetPosition(131.621016, 40.769099, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.340444, 0.705685, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.412676, 0.702504, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.465774, 0.710550, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710110')
    BB.Write('DatumLongitude', '2.459795')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-31"
    unit.SetPosition(137.907795, 43.701269, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.412107, 0.709406, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.443873, 0.638986, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.631269')
    BB.Write('DatumLongitude', '2.442995')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-32"
    unit.SetPosition(138.185456, 44.018401, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.412107, 0.709406, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.443873, 0.638986, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.631269')
    BB.Write('DatumLongitude', '2.442995')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-33"
    unit.SetPosition(137.713968, 44.052661, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.412107, 0.709406, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.443873, 0.638986, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.632175')
    BB.Write('DatumLongitude', '2.450975')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-34"
    unit.SetPosition(138.095612, 44.344013, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.412107, 0.709406, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.443873, 0.638986, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710110')
    BB.Write('DatumLongitude', '2.459795')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-35"
    unit.SetPosition(136.726008, 42.270419, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.414354, 0.735497, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.468122, 0.743669, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746501')
    BB.Write('DatumLongitude', '2.473678')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-36"
    unit.SetPosition(137.827976, 42.839080, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635217')
    BB.Write('DatumLongitude', '2.381243')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-37"
    unit.SetPosition(137.466222, 42.896549, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.631269')
    BB.Write('DatumLongitude', '2.442995')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-38"
    unit.SetPosition(137.601666, 43.007301, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.632175')
    BB.Write('DatumLongitude', '2.450975')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-39"
    unit.SetPosition(135.558497, 40.728074, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.391988, 0.709684, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.462247, 0.707635, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710110')
    BB.Write('DatumLongitude', '2.459795')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-40"
    unit.SetPosition(135.221714, 40.916577, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.396472, 0.717196, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.465535, 0.745422, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746978')
    BB.Write('DatumLongitude', '2.466304')
    BB.Write('Home', 'Harbin')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Bomb 7"
    unit.SetPosition(133.838655, 36.656294, 10000.0)
    unit.heading = 90.00
    unit.speed = 400.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.349357, 0.638475, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.381725, 0.635067, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.637218')
    BB.Write('DatumLongitude', '2.384624')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Bomb 8"
    unit.SetPosition(134.074187, 36.344946, 10000.0)
    unit.heading = 90.00
    unit.speed = 400.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.351473, 0.634120, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.381255, 0.635067, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635217')
    BB.Write('DatumLongitude', '2.381243')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Bomb 1"
    unit.SetPosition(141.913123, 44.773672, 8882.4)
    unit.heading = 90.00
    unit.speed = 100.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.471109, 0.752500, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746978')
    BB.Write('DatumLongitude', '2.466304')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Bomb 2"
    unit.SetPosition(142.679283, 44.667389, 7868.3)
    unit.heading = 90.00
    unit.speed = 100.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.475294, 0.751184, 0.000000, 0.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746501')
    BB.Write('DatumLongitude', '2.473678')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 19"
    unit.SetPosition(134.288300, 37.071402, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.356410, 0.642767, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.379688, 0.635508, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.634821')
    BB.Write('StationLongitude', '2.387165')
    UI.SetThrottle(0.800000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Blinder 1"
    unit.SetPosition(134.288300, 35.964389, 6720.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.368245, 0.630396, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.379844, 0.636266, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.633942')
    BB.Write('StationLongitude', '2.379796')
    UI.SetThrottle(0.800000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Souhtern Axis-9"
    unit.SetPosition(133.577605, 38.589394, 4000.0)
    unit.heading = 90.04
    unit.speed = 394.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.443311, 0.634640, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.635898')
    BB.Write('StationLongitude', '2.375555')
    UI.SetThrottle(0.499869)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Souhtern Axis-8"
    unit.SetPosition(133.500889, 38.528261, 4000.0)
    unit.heading = 90.04
    unit.speed = 394.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.443311, 0.634640, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.637824')
    BB.Write('StationLongitude', '2.374890')
    UI.SetThrottle(0.499869)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Northern Axis-9"
    unit.SetPosition(133.347974, 39.529447, 4000.0)
    unit.heading = 90.04
    unit.speed = 446.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.451614, 0.741779, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.631696')
    BB.Write('StationLongitude', '2.439543')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Northern Axis-8"
    unit.SetPosition(133.721367, 39.052918, 4000.0)
    unit.heading = 90.04
    unit.speed = 446.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.451614, 0.741779, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.639224')
    BB.Write('StationLongitude', '2.379540')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'A-50'
    unit.unitName = "Sky Watcher 2"
    unit.SetPosition(136.861815, 43.086025, 10000.0)
    unit.heading = 90.00
    unit.speed = 100.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.374955, 0.744338, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.395332, 0.768266, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.741906')
    BB.Write('StationLongitude', '2.384797')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'A-50'
    unit.unitName = "Sky Watcher 1"
    unit.SetPosition(133.206635, 38.132404, 10000.0)
    unit.heading = 90.00
    unit.speed = 100.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.319755, 0.702293, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.317842, 0.655404, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.657779')
    BB.Write('StationLongitude', '2.322299')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 1"
    unit.SetPosition(134.548329, 37.913649, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.363226, 0.649264, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.383677, 0.640513, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.383677, 0.638252, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.641302')
    BB.Write('StationLongitude', '2.379880')
    UI.SetThrottle(0.176108)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 2"
    unit.SetPosition(134.325334, 37.504213, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.372166, 0.636973, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.375962, 0.634122, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.381228, 0.632549, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.639601')
    BB.Write('StationLongitude', '2.374691')
    UI.SetThrottle(0.176108)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Harbin"
    unit.SetPosition(126.247927, 44.971171, 0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Harbin", 'Fuel', 9000000)
    SM.AddToUnitMagazine("Harbin", 'GB-200', 600)
    SM.AddToUnitMagazine("Harbin", 'GB-500', 500)
    SM.AddToUnitMagazine("Harbin", 'YJ-6', 300)
    SM.AddToUnitMagazine("Harbin", 'PL-12', 300)
    SM.AddToUnitMagazine("Harbin", 'R-73M', 400)
    SM.AddToUnitMagazine("Harbin", 'PL-11 AMR', 220)
    SM.AddToUnitMagazine("Harbin", 'Kh-31P', 200)
    SM.AddToUnitMagazine("Harbin", 'Kh-29T', 280)
    SM.AddToUnitMagazine("Harbin", 'Flare-1', 300)
    SM.AddToUnitMagazine("Harbin", 'Chaff-1', 200)
    UI.SetSensorState(0, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-1', 2)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-1', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-2', 2)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-2', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-3', 2)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-3', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-4', 2)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-4', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-5', 2)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-5', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-6', 2)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-6', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-7', 2)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-7', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-8', 2)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-8', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-9', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-10', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-11', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-11', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-12', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-12', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-13', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-13', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-14', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-14', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-15', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-15', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-16', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-16', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-17', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-17', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-18', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-18', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-19', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-19', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'Su-30MKK', 'Harbin AAW-20', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AAW-20', '4 PL-11 AMR;2 PL-12;4 PL-12;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Harbin', 'A-50', 'Harbin AEW-1', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AEW-1', '')
    
    SM.AddUnitToFlightDeck('Harbin', 'A-50', 'Harbin AEW-2', 1)
    SM.SetFlightDeckUnitLoadout('Harbin', 'Harbin AEW-2', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Harbin AEW-1')
    FP.AddAircraftToMission(mission_id, 'Harbin AEW-2')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R3.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '2.2135174,0.7808772,2.2179961,0.7848542,2.2227862,0.7855109,2.2131917,0.7786785,')
    FP.AddMissionWaypointAdvanced(mission_id, 2.2044420, 0.7858950, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 2.2140980, 0.7818620, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-9')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-10')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-11')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-12')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-13')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-14')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-15')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-16')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-17')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-18')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-19')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-20')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R2.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '2.2473824,0.7856532,2.2358458,0.7906231,2.2043707,0.7686390,2.2171614,0.7630870,')
    FP.AddMissionWaypointAdvanced(mission_id, 2.2044420, 0.7858950, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 2.2194009, 0.7749020, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-1')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-2')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-3')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-4')
    FP.SetMissionLaunchTime(mission_id, '06:00:00+15m+R1.5')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '2.1986978,0.7782572,2.1998262,0.7719955,2.1798475,0.7852825,2.1905034,0.7846330,')
    FP.AddMissionWaypointAdvanced(mission_id, 2.2044420, 0.7858950, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 2.1932271, 0.7827680, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-5')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-6')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-7')
    FP.AddAircraftToMission(mission_id, 'Harbin AAW-8')
    FP.SetMissionLaunchTime(mission_id, '04:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '2.2097123,0.7947997,2.2247381,0.7819746,2.2189853,0.7831606,2.2090845,0.7912142,')
    FP.AddMissionWaypointAdvanced(mission_id, 2.2044420, 0.7858950, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 2.2131600, 0.7874620, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 4"
    unit.SetPosition(136.676120, 40.246160, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.436236, 0.691473, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.427865, 0.669620, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.676840')
    BB.Write('StationLongitude', '2.425579')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 3"
    unit.SetPosition(136.668429, 40.082983, 10000.0)
    unit.heading = 90.00
    unit.speed = 522.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.436236, 0.691473, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.427865, 0.669620, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.650164')
    BB.Write('StationLongitude', '2.390291')
    UI.SetThrottle(0.554667)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 10"
    unit.SetPosition(139.411535, 44.176479, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.776742')
    BB.Write('StationLongitude', '2.449795')
    UI.SetThrottle(0.176108)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 9"
    unit.SetPosition(139.352062, 43.786581, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.751698')
    BB.Write('StationLongitude', '2.441839')
    UI.SetThrottle(0.176108)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 6"
    unit.SetPosition(138.896160, 41.571870, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.451710, 0.714842, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.710322')
    BB.Write('StationLongitude', '2.447374')
    UI.SetThrottle(0.176108)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 5"
    unit.SetPosition(138.539379, 41.244367, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-12', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.451710, 0.714842, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.688545')
    BB.Write('StationLongitude', '2.436649')
    UI.SetThrottle(0.176108)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 8"
    unit.SetPosition(138.578970, 43.100349, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.749521')
    BB.Write('StationLongitude', '2.444952')
    UI.SetThrottle(0.176108)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 7"
    unit.SetPosition(138.479906, 42.679225, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'PL-11 AMR', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.738360')
    BB.Write('StationLongitude', '2.444260')
    UI.SetThrottle(0.176108)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 11435 Brezhnev'
    unit.unitName = "CVN Varyag"
    boxes = [[133.1340, 133.1794, 39.0271, 39.0946]]
    box = boxes[int(1*random())]
    lon_deg = random()*(box[1]-box[0]) + box[0]
    lat_deg = random()*(box[3]-box[2]) + box[2]
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 9.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M330 Kinzhal', 24)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 6, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 7, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 8, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 9, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 10, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 11, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 12, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 13, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 14, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 15, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 16, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 17, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 18, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 19, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 20, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 21, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 22, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 23, '3M45 Granit', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("CVN Varyag", 'Fuel', 900000)
    SM.AddToUnitMagazine("CVN Varyag", 'Chaff-1', 600)
    SM.AddToUnitMagazine("CVN Varyag", 'Flare-1', 600)
    SM.AddToUnitMagazine("CVN Varyag", 'Kh-29T', 300)
    SM.AddToUnitMagazine("CVN Varyag", 'Kh-31P', 326)
    SM.AddToUnitMagazine("CVN Varyag", 'R-73M', 460)
    SM.AddToUnitMagazine("CVN Varyag", 'PL-12', 400)
    SM.AddToUnitMagazine("CVN Varyag", 'PL-11 AMR', 396)
    SM.AddToUnitMagazine("CVN Varyag", 'AT-1', 350)
    SM.AddToUnitMagazine("CVN Varyag", 'DICASS (100) Sonobuoy', 360)
    SM.AddToUnitMagazine("CVN Varyag", 'LOFAR (100) Sonobuoy', 120)
    SM.AddToUnitMagazine("CVN Varyag", 'DIFAR (100) Sonobuoy', 120)
    SM.AddToUnitMagazine("CVN Varyag", '30mm OF-84 HE-FRAG AK-630M', 600)
    SM.AddToUnitMagazine("CVN Varyag", '9M311 Kashtan', 400)
    SM.AddToUnitMagazine("CVN Varyag", '9M330 Kinzhal', 100)
    UI.SetSensorState(1, 1)
    UI.SetSensorState(3, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.331722, 0.659508, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.370373, 0.635422, 0.000000, 0.000000)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.677395')
    BB.Write('StationLongitude', '2.400312')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-34', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-34', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-33', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-33', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-3', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-3', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-4', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-4', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-5', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-5', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-6', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-6', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-7', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-7', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-8', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-8', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-9', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-9', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-10', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-10', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-11', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-11', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-12', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-12', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-13', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-13', '4 PL-11 AMR;2 PL-12;4 PL-11 AMR;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-14', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-14', '4 R-73M;2 PL-12;4 R-73M;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-15', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-15', '4 R-73M;2 PL-12;4 R-73M;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-16', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-16', '4 R-73M;2 PL-12;4 R-73M;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-17', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-17', '4 R-73M;2 PL-12;4 R-73M;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Su-33', 'Sky Dragon-18', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Sky Dragon-18', '4 R-73M;2 PL-12;4 R-73M;25 Flare-1;25 Chaff-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Ka-27A', 'Varyag ASW-1', 2)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Varyag ASW-1', '5 DIFAR (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Ka-27A', 'Varyag ASW-2', 2)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Varyag ASW-2', '5 DIFAR (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Ka-27A', 'Varyag ASW-3', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Varyag ASW-3', '5 DIFAR (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 AT-1;')
    
    SM.AddUnitToFlightDeck('CVN Varyag', 'Ka-27A', 'Varyag ASW-4', 1)
    SM.SetFlightDeckUnitLoadout('CVN Varyag', 'Varyag ASW-4', '5 DIFAR (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 AT-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-7')
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-8')
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-9')
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-10')
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-11')
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-12')
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-13')
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-14')
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-15')
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-16')
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-17')
    FP.AddAircraftToMission(mission_id, 'Sky Dragon-18')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0084184,0.0039524,-0.0056797,0.0151658,-0.0011495,0.0224467,0.0136515,0.0119341,')
    FP.SetMissionPatrolAnchor(mission_id, 'CVN Varyag', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 2.3255954, 0.6826936, 2000.0, 200.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 2.3346119, 0.6789090, 3000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Varyag ASW-1')
    FP.AddAircraftToMission(mission_id, 'Varyag ASW-2')
    FP.AddAircraftToMission(mission_id, 'Varyag ASW-3')
    FP.AddAircraftToMission(mission_id, 'Varyag ASW-4')
    FP.SetMissionLaunchTime(mission_id, '05:00:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'ASW-Helo')
    FP.SetMissionPatrolArea(mission_id, '0.0038363,0.0024639,0.0053199,0.0042908,-0.0002564,0.0081899,-0.0010648,0.0058628,')
    FP.SetMissionPatrolAnchor(mission_id, 'CVN Varyag', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 2.3255954, 0.6826936, 500.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 2.3297350, 0.6801870, 300.0, 100.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'ASWPatrolArea,EngageAll')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-1"
    unit.SetPosition(131.763972, 41.687780, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.321549, 0.722151, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.421526, 0.652729, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.465296, 0.683230, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.464339, 0.710924, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710110')
    BB.Write('DatumLongitude', '2.459795')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.709616')
    BB.Write('StationLongitude', '2.459729')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-2"
    unit.SetPosition(131.876274, 42.133310, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635217')
    BB.Write('DatumLongitude', '2.381243')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.636065')
    BB.Write('StationLongitude', '2.383775')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-3"
    unit.SetPosition(131.292484, 41.979129, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.361253, 0.735437, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.429992, 0.771607, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.466347, 0.767595, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.474001, 0.745899, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746501')
    BB.Write('DatumLongitude', '2.473678')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.747334')
    BB.Write('StationLongitude', '2.465397')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-4"
    unit.SetPosition(131.494562, 42.321871, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.352642, 0.725894, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.465535, 0.709801, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710110')
    BB.Write('DatumLongitude', '2.459795')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.631350')
    BB.Write('StationLongitude', '2.442724')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-54"
    unit.SetPosition(131.045477, 42.184762, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.331355, 0.710924, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.398804, 0.665267, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.381105, 0.634766, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.637218')
    BB.Write('DatumLongitude', '2.384624')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.745920')
    BB.Write('StationLongitude', '2.472199')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-53"
    unit.SetPosition(138.926395, 45.183737, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.468418, 0.751623, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.631269')
    BB.Write('DatumLongitude', '2.442995')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.637008')
    BB.Write('StationLongitude', '2.384909')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-52"
    unit.SetPosition(139.285649, 45.389374, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.468418, 0.751623, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.637218')
    BB.Write('DatumLongitude', '2.384624')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.631350')
    BB.Write('StationLongitude', '2.451226')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-50"
    unit.SetPosition(138.814107, 45.612140, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.370729, 0.730168, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.381940, 0.640381, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.637218')
    BB.Write('DatumLongitude', '2.384624')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.746392')
    BB.Write('StationLongitude', '2.466531')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-49"
    unit.SetPosition(138.432449, 45.440768, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.435382, 0.762687, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.423797, 0.680095, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.445098, 0.635777, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.631269')
    BB.Write('DatumLongitude', '2.442995')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.637480')
    BB.Write('StationLongitude', '2.383775')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-48"
    unit.SetPosition(141.396191, 45.235134, 3664.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.454665, 0.754255, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.462438, 0.714543, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710110')
    BB.Write('DatumLongitude', '2.459795')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.709145')
    BB.Write('StationLongitude', '2.464830')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-51"
    unit.SetPosition(128.687982, 43.093016, 1007.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.313169, 0.631808, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.364294, 0.604810, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.380737, 0.634675, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.635217')
    BB.Write('DatumLongitude', '2.381243')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.637480')
    BB.Write('StationLongitude', '2.383775')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-44"
    unit.SetPosition(129.181941, 43.452892, 509.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.388168, 0.680596, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.413820, 0.646527, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.381291, 0.635059, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.637218')
    BB.Write('DatumLongitude', '2.384624')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.630879')
    BB.Write('StationLongitude', '2.443291')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-45"
    unit.SetPosition(129.675887, 43.744241, 614.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.348154, 0.742248, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.464635, 0.710721, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710110')
    BB.Write('DatumLongitude', '2.459795')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.709616')
    BB.Write('StationLongitude', '2.461429')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-46"
    unit.SetPosition(130.057585, 44.001268, 118.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.341696, 0.755145, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.442391, 0.742248, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.474202, 0.746010, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.746501')
    BB.Write('DatumLongitude', '2.473678')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.745449')
    BB.Write('StationLongitude', '2.475033')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'H-6D'
    unit.unitName = "Hammer-47"
    unit.SetPosition(128.575694, 42.613165, 10.0)
    unit.heading = 90.00
    unit.speed = 500.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'GB-200', 40)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'YJ-6', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('BombDatum', 3.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.339147, 0.742842, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.465090, 0.710241, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('DatumLatitude', '0.710110')
    BB.Write('DatumLongitude', '2.459795')
    BB.Write('Home', 'Harbin')
    BB.Write('StationLatitude', '0.631822')
    BB.Write('StationLongitude', '2.451226')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor12"
    unit.SetPosition(136.482047, 41.537550, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.714175')
    BB.Write('StationLongitude', '2.451159')
    UI.SetThrottle(0.176108)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-30MKK'
    unit.unitName = "Raptor 11"
    unit.SetPosition(136.478963, 41.711786, 10000.0)
    unit.heading = 90.00
    unit.speed = 200.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-29T', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-11 AMR', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Chaff-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Flare-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('StationLatitude', '0.704665')
    BB.Write('StationLongitude', '2.450592')
    UI.SetThrottle(0.176108)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Northern Axis-7"
    unit.SetPosition(133.496709, 39.111935, 4000.0)
    unit.heading = 90.04
    unit.speed = 446.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.451614, 0.741779, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.666716')
    BB.Write('StationLongitude', '2.380204')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Northern Axis-6"
    unit.SetPosition(133.511434, 39.071882, 4000.0)
    unit.heading = 90.04
    unit.speed = 446.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.451614, 0.741779, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.657263')
    BB.Write('StationLongitude', '2.368912')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Northern Axis-5"
    unit.SetPosition(133.496709, 39.187794, 4000.0)
    unit.heading = 90.04
    unit.speed = 446.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.451614, 0.741779, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.650044')
    BB.Write('StationLongitude', '2.353192')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Souhtern Axis-7"
    unit.SetPosition(133.559218, 39.005992, 4000.0)
    unit.heading = 90.04
    unit.speed = 394.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.443311, 0.634640, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.672904')
    BB.Write('StationLongitude', '2.404781')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Souhtern Axis-6"
    unit.SetPosition(133.568439, 38.938728, 4000.0)
    unit.heading = 90.04
    unit.speed = 394.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.443311, 0.634640, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.673248')
    BB.Write('StationLongitude', '2.424486')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Souhtern Axis-5"
    unit.SetPosition(133.570270, 38.871464, 4000.0)
    unit.heading = 90.04
    unit.speed = 394.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.443311, 0.634640, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.682186')
    BB.Write('StationLongitude', '2.421387')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Northern Axis-4"
    unit.SetPosition(133.515095, 39.270873, 4000.0)
    unit.heading = 90.04
    unit.speed = 446.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.451614, 0.741779, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.691296')
    BB.Write('StationLongitude', '2.434229')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Northern Axis-3"
    unit.SetPosition(133.474592, 39.359621, 4000.0)
    unit.heading = 90.04
    unit.speed = 446.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.451614, 0.741779, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.639387')
    BB.Write('StationLongitude', '2.375776')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Souhtern Axis-4"
    unit.SetPosition(133.572114, 38.814166, 4000.0)
    unit.heading = 90.04
    unit.speed = 394.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.443311, 0.634640, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.693530')
    BB.Write('StationLongitude', '2.432457')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Souhtern Axis-3"
    unit.SetPosition(133.577605, 38.749767, 4000.0)
    unit.heading = 90.04
    unit.speed = 394.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.443311, 0.634640, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.690952')
    BB.Write('StationLongitude', '2.428693')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Northern Axis-2"
    unit.SetPosition(133.458091, 39.425454, 4000.0)
    unit.heading = 90.04
    unit.speed = 446.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.451614, 0.741779, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.682530')
    BB.Write('StationLongitude', '2.424929')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Northern Axis-1"
    unit.SetPosition(133.474592, 39.507044, 4000.0)
    unit.heading = 90.04
    unit.speed = 446.4
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.451614, 0.741779, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.691468')
    BB.Write('StationLongitude', '2.440207')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Souhtern Axis-2"
    unit.SetPosition(133.584996, 38.691038, 4000.0)
    unit.heading = 90.04
    unit.speed = 394.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.443311, 0.634640, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.704187')
    BB.Write('StationLongitude', '2.458141')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Su-33'
    unit.unitName = "Souhtern Axis-1"
    unit.SetPosition(133.581335, 38.639528, 4000.0)
    unit.heading = 90.04
    unit.speed = 394.5
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Kh-31P', 3)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'PL-12', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Kh-31P', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Flare-1', 25)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Chaff-1', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('JetTakeoff', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.443311, 0.634640, 0.000000, 0.000000)
    UI.AddTask('PatrolCircle', 1.000000, 0)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'CVN Kusnetzov')
    BB.Write('StationLatitude', '0.744579')
    BB.Write('StationLongitude', '2.436886')
    UI.SetThrottle(0.640000)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 945 Barrakuda'
    unit.unitName = "K-239 Karp"
    unit.SetPosition(134.282350, 38.584239, -700.0)
    unit.heading = 90.00
    unit.speed = 7.7
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
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(2.352272, 0.686037, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.353012, 0.668921, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.366079, 0.659784, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.353480, 0.649286, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(2.377975, 0.675055, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1155 Fregat'
    unit.unitName = "Admiral Vinogradov"
    UI = SM.GetUnitInterface('CVN Varyag')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.3291
    lat_deg = 57.296*leader_track.Lat + 0.0773
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M330 Kinzhal', 64)
    SM.SetUnitLauncherItem(unit.unitName, 1, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 2, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Empty', 8)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Admiral Vinogradov", 'Fuel', 45900)
    SM.AddToUnitMagazine("Admiral Vinogradov", 'AT-1', 22)
    SM.AddToUnitMagazine("Admiral Vinogradov", 'DICASS (100) Sonobuoy', 378)
    SM.AddToUnitMagazine("Admiral Vinogradov", 'LOFAR (100) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Vinogradov", 'DIFAR (100) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Vinogradov", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Admiral Vinogradov", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Admiral Vinogradov", '53-65M', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('CVN Varyag')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(14.369, 2.542, -2.847, 0.235)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Admiral Vinogradov', 'Ka-27A', 'Fregat Ka-27 201', 1)
    SM.SetFlightDeckUnitLoadout('Admiral Vinogradov', 'Fregat Ka-27 201', '5 DIFAR (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135M Burevestnik-M'
    unit.unitName = "Krivak II FFM"
    UI = SM.GetUnitInterface('CVN Varyag')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2263
    lat_deg = 57.296*leader_track.Lat + -0.1915
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 1, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RPK-3 Metel', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Krivak II FFM", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Krivak II FFM", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('CVN Varyag')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(19.770, 7.785, 2.326, 0.320)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1164 Atlant'
    unit.unitName = "Slava CGHM"
    UI = SM.GetUnitInterface('CVN Varyag')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.2385
    lat_deg = 57.296*leader_track.Lat + -0.0430
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 9.6
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
    SM.AddToUnitMagazine("Slava CGHM", 'Fuel', 68850)
    SM.AddToUnitMagazine("Slava CGHM", 'AT-1', 26)
    SM.AddToUnitMagazine("Slava CGHM", 'DICASS (100) Sonobuoy', 490)
    SM.AddToUnitMagazine("Slava CGHM", 'LOFAR (100) Sonobuoy', 175)
    SM.AddToUnitMagazine("Slava CGHM", 'DIFAR (100) Sonobuoy', 175)
    SM.AddToUnitMagazine("Slava CGHM", '30mm OF-84 HE-FRAG AK-630M', 1416)
    SM.AddToUnitMagazine("Slava CGHM", '130mm F-44 HE', 500)
    SM.AddToUnitMagazine("Slava CGHM", '53-65M', 30)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('CVN Varyag')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(9.383, 2.613, 0.226, 0.401)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Slava CGHM', 'Ka-27A', 'Atlant Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Slava CGHM', 'Atlant Ka-27 1', '5 DIFAR (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1155 Fregat'
    unit.unitName = "Admiral Kharlamov"
    UI = SM.GetUnitInterface('CVN Varyag')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0840
    lat_deg = 57.296*leader_track.Lat + -0.1997
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M330 Kinzhal', 64)
    SM.SetUnitLauncherItem(unit.unitName, 1, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 2, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Empty', 8)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Admiral Kharlamov", 'Fuel', 45900)
    SM.AddToUnitMagazine("Admiral Kharlamov", 'AT-1', 22)
    SM.AddToUnitMagazine("Admiral Kharlamov", 'DICASS (100) Sonobuoy', 378)
    SM.AddToUnitMagazine("Admiral Kharlamov", 'LOFAR (100) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Kharlamov", 'DIFAR (100) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Kharlamov", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Admiral Kharlamov", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Admiral Kharlamov", '53-65M', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('CVN Varyag')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(10.946, 3.169, 1.273, 0.554)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Admiral Kharlamov', 'Ka-27A', 'Fregat Ka-27 101', 1)
    SM.SetFlightDeckUnitLoadout('Admiral Kharlamov', 'Fregat Ka-27 101', '5 DIFAR (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Fleet Oiler"
    UI = SM.GetUnitInterface('CVN Varyag')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0633
    lat_deg = 57.296*leader_track.Lat + -0.0346
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('CVN Varyag')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(3.599, 1.405, 2.489, 0.440)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1155 Fregat'
    unit.unitName = "Admiral Levchenko"
    UI = SM.GetUnitInterface('CVN Varyag')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0254
    lat_deg = 57.296*leader_track.Lat + 0.1887
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M330 Kinzhal', 64)
    SM.SetUnitLauncherItem(unit.unitName, 1, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 2, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Empty', 8)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Admiral Levchenko", 'Fuel', 45900)
    SM.AddToUnitMagazine("Admiral Levchenko", 'AT-1', 22)
    SM.AddToUnitMagazine("Admiral Levchenko", 'DICASS (100) Sonobuoy', 378)
    SM.AddToUnitMagazine("Admiral Levchenko", 'LOFAR (100) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Levchenko", 'DIFAR (100) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Levchenko", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Admiral Levchenko", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Admiral Levchenko", '53-65M', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 0.000000, 0)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('CVN Varyag')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(12.553, 5.358, -1.465, 0.356)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Admiral Levchenko', 'Ka-27A', 'Fregat Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Admiral Levchenko', 'Fregat Ka-27 1', '5 DIFAR (100) Sonobuoy;5 LOFAR (100) Sonobuoy;14 DICASS (100) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "LST 2"
    UI = SM.GetUnitInterface('CVN Varyag')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0304
    lat_deg = 57.296*leader_track.Lat + 0.0233
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 75.75
    unit.speed = 9.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("LST 2", '9M32 Strela 2', 24)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('CVN Varyag')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(2.667, 1.060, -2.370, 0.310)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 775  Ropucha'
    unit.unitName = "LST 1"
    UI = SM.GetUnitInterface('CVN Varyag')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0557
    lat_deg = 57.296*leader_track.Lat + -0.0105
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 74.71
    unit.speed = 8.8
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 2, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 3, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M32 Strela 2', 32)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("LST 1", '57mm Tracer-FRAG', 2800)
    SM.AddToUnitMagazine("LST 1", '30mm OF-84 HE-FRAG AK-630M', 472)
    SM.AddToUnitMagazine("LST 1", '9M32 Strela 2', 64)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('CVN Varyag')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(2.614, 1.290, 2.898, 0.818)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('CVN Varyag')
    goal_2_0 = goal_temp

    goal_temp = SM.ProtectGoal('Chitose')
    goal_2_1 = goal_temp

    goal_temp = SM.ProtectGoal('Misawa')
    goal_2_2 = goal_temp

    goal_temp = SM.ProtectGoal('Hyakuri')
    goal_2_3 = goal_temp

    goal_temp = SM.ProtectGoal('Komatsu')
    goal_2_4 = goal_temp

    goal_temp = SM.DestroyGoal('LST 2')
    goal_2_5 = goal_temp

    goal_temp = SM.DestroyGoal('LST 1')
    goal_2_6 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_2_0)
    goal_temp.AddGoal(goal_2_1)
    goal_temp.AddGoal(goal_2_2)
    goal_temp.AddGoal(goal_2_3)
    goal_temp.AddGoal(goal_2_4)
    goal_temp.AddGoal(goal_2_5)
    goal_temp.AddGoal(goal_2_6)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 1, 1, 1, 1)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.DestroyGoal('Chitose')
    goal_3_0 = goal_temp

    goal_temp = SM.DestroyGoal('Komatsu')
    goal_3_1 = goal_temp

    goal_temp = SM.DestroyGoal('Hyakuri')
    goal_3_2 = goal_temp

    goal_temp = SM.DestroyGoal('Misawa')
    goal_3_3 = goal_temp

    goal_temp = SM.CompoundGoal(1)
    goal_temp.AddGoal(goal_3_0)
    goal_temp.AddGoal(goal_3_1)
    goal_temp.AddGoal(goal_3_2)
    goal_temp.AddGoal(goal_3_3)
    
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    ##############################
    ### Randomization Info
    ##############################
    SM.SetIncludeProbability('CVN Varyag', 1.000000)
    SM.AddRandomBox('CVN Varyag', 133.1340, 133.1794, 39.0271, 39.0946)
