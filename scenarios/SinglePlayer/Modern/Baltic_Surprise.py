# Created on 01/08/15 17:09:10
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""SOURCE SHAPE\n\nThe Russian amphibious group is escorted by a massive escort group. \nMost of the Baltic Fleet naval forces are assigned to its protection.\n\nThe Polish Army and Air Force were virtually destroyed during the \nfighting last spring but the Polish Navy was untouched.  Most of the \nPolish Navy is supporting the Russian offensive.\n\nTwo possibly three airfields are providing support for the attack.\n\nUnconfirmed reports say that Russian tactical nuclear units are on alert \nand deployed in the field, we'll try to confirm or deny.\n\n\n""")
    SM.SetScenarioName("""Baltic Surprise""")
    SM.CreateAlliance(1, 'NATO')
    SM.SetAllianceDefaultCountry(1, 'NATO')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'USSR')
    SM.SetAllianceDefaultCountry(2, 'USSR')
    SM.SetAlliancePlayable(2, 0)
    SM.CreateAlliance(3, 'Neutral')
    SM.SetAllianceDefaultCountry(3, 'Neutral')
    SM.SetAlliancePlayable(3, 0)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(1)

    SM.SetDateTime(1992,6,1,8,0,0)
    SM.SetStartTheater(15.616664, 52.883335) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(3)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """Source COBRA\n\nWar rages across Europe once more.  After the Russian Army coup in \nFebruary the Baltic states of Estonia, Latvia and Lithuania were \nreoccupied without a shot being fired. Last April 15 Russian Army \ndivisions crossed the border into Poland from assembly areas in Belarus \nand Ukraine, whose governments are actively supporting the operation. \n\nOn 16 April, the NATO governments invoked Article 5 and declared war \non Russia.  Poland was declared secure by the Russian\n\nYou are ordered to attack the Russian naval units and stop any attempt \nto land Russian troops on the island of Bornholm.\n\nBritish, Dutch and German naval and air assets are at your disposal. \nMost US units are still committed in Southwest Asia but some USAF units \nare expected on NATO airfields shortly.\n\nThe Swedish Navy and Airforce has pledged its support to NATO and \nsome of its units are now under your control.\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """No briefing found""")

    ####################
    SM.SetSimpleBriefing(3, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland 4"
    unit.SetPosition(14.981987, 55.200874, 179.7)
    unit.heading = 90.00
    unit.speed = 18.2
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.259856, 0.964083, 0.000000, 0.000000)
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland 5"
    unit.SetPosition(14.928931, 55.221157, 160.1)
    unit.heading = 90.00
    unit.speed = 18.2
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.262069, 0.962880, 0.000000, 0.000000)
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland 6"
    unit.SetPosition(14.697743, 55.244992, 120.5)
    unit.heading = 90.00
    unit.speed = 18.2
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.259341, 0.964170, 0.000000, 0.000000)
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland 7"
    unit.SetPosition(14.780077, 55.274327, 66.9)
    unit.heading = 90.00
    unit.speed = 18.2
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.256443, 0.963595, 0.000000, 0.000000)
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland 8"
    unit.SetPosition(14.810673, 55.069724, 66.9)
    unit.heading = 90.00
    unit.speed = 18.2
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.261010, 0.960447, 0.000000, 0.000000)
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland 9"
    unit.SetPosition(14.824194, 55.054254, 39.3)
    unit.heading = 90.00
    unit.speed = 18.2
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.256719, 0.961826, 0.000000, 0.000000)
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland 10"
    unit.SetPosition(15.099443, 55.115618, 115.1)
    unit.heading = 90.00
    unit.speed = 18.2
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.263958, 0.962017, 0.000000, 0.000000)
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland 11"
    unit.SetPosition(15.093313, 55.107769, 39.3)
    unit.heading = 90.00
    unit.speed = 18.2
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.263289, 0.961048, 0.000000, 0.000000)
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland 12"
    unit.SetPosition(15.010234, 55.050874, -0.0)
    unit.heading = 90.00
    unit.speed = 18.2
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.260845, 0.960342, 0.000000, 0.000000)
    UI.AddNavWaypointAdvanced(0.263640, 0.961006, 0.000000, 0.000000)
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland 3"
    unit.SetPosition(11.050007, 60.103273, 11.2)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland 2"
    unit.SetPosition(9.200614, 54.376331, 4.7)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Roland-2'
    unit.unitName = "Roland1"
    unit.SetPosition(7.531301, 53.312692, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Roland 2', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MIM-104 Patriot PAC-2'
    unit.unitName = "Patriot 3"
    unit.SetPosition(11.477949, 60.349186, 75.5)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'MIM-104C', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Patriot 3", 'MIM-104C', 48)
    UI.SetSensorState(5, 1)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MIM-104 Patriot PAC-2'
    unit.unitName = "Patriot 2"
    unit.SetPosition(9.651875, 54.428871, 5.2)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'MIM-104C', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Patriot 2", 'MIM-104C', 48)
    UI.SetSensorState(5, 1)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'MIM-104 Patriot PAC-2'
    unit.unitName = "Patriot1"
    unit.SetPosition(7.658956, 53.322147, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'MIM-104C', 8)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'MIM-104C', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Patriot1", 'MIM-104C', 48)
    UI.SetSensorState(5, 1)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Rapier-Mobile'
    unit.unitName = "Rapier 3"
    unit.SetPosition(11.600104, 60.034060, 10.5)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Rapier-SAM', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Rapier 3", 'Rapier-SAM', 8)
    UI.SetSensorState(0, 1)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Rapier-Mobile'
    unit.unitName = "Rapier 2"
    unit.SetPosition(9.290568, 54.370830, 3.2)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Rapier-SAM', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Rapier 2", 'Rapier-SAM', 8)
    UI.SetSensorState(0, 1)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Rapier-Mobile'
    unit.unitName = "Rapier1"
    unit.SetPosition(7.585560, 53.358929, 0.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Rapier-SAM', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Rapier1", 'Rapier-SAM', 8)
    UI.SetSensorState(0, 1)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gepard Type 143'
    unit.unitName = "Puma"
    unit.SetPosition(14.319820, 54.336625, 0.0)
    unit.heading = 90.00
    unit.speed = 10.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MM-40 B2 Exocet', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MM-40 B2 Exocet', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Puma", '76mm HE-MOM', 480)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.300576, 0.961181, 0.000000, 10.000000)
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Hauk PTGM'
    unit.unitName = "Orn"
    unit.SetPosition(13.378106, 55.246482, 0.0)
    unit.heading = 90.00
    unit.speed = 9.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Penguin Mk2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '40mm HE-T', 50)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm Rh202 HE-T', 50)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Orn", '40mm HE-T', 500)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.249238, 0.963908, 0.000000, 10.000000)
    UI.AddNavWaypointAdvanced(0.257830, 0.968563, 0.000000, 10.000000)
    UI.AddNavWaypointAdvanced(0.305471, 0.961989, 0.000000, 10.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 42 DDG Batch 2'
    unit.unitName = "HMS Southampton"
    unit.SetPosition(12.604098, 55.408514, 0.0)
    unit.heading = 143.75
    unit.speed = 5.3
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm Mark 149-4', 90)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Sea Dart Mod2', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 4, '114mm N4A1 HE', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Southampton", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Southampton", 'Stingray', 20)
    SM.AddToUnitMagazine("HMS Southampton", 'Sea Skua', 8)
    SM.AddToUnitMagazine("HMS Southampton", 'LOFAR (90) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Southampton", 'DICASS (90) Sonobuoy', 135)
    SM.AddToUnitMagazine("HMS Southampton", 'DIFAR (90) Sonobuoy', 405)
    SM.AddToUnitMagazine("HMS Southampton", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Southampton", '20mm Mark 149-4', 475)
    SM.AddToUnitMagazine("HMS Southampton", 'Sea Dart Mod2', 22)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.224234, 0.963181, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.247058, 0.962912, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.256053, 0.967406, 0.000000, 12.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('HMS Southampton', 'Lynx HAS.Mk.2', 'Type 42 B2 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Southampton', 'Type 42 B2 Lynx 1', '1 Stingray;1 Stingray;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Luetjens DDG'
    unit.unitName = "Luetjens"
    unit.SetPosition(12.295216, 54.555437, 0.0)
    unit.heading = 90.00
    unit.speed = 5.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-66A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '127mm mk 41 AAC', 40)
    SM.SetUnitLauncherItem(unit.unitName, 2, '127mm mk 41 AAC', 40)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RUR-5 ASROC', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Luetjens", '127mm mk 41 AAC', 360)
    SM.AddToUnitMagazine("Luetjens", '127mm mk 41 HC', 140)
    SM.AddToUnitMagazine("Luetjens", 'RIM-66A', 32)
    SM.AddToUnitMagazine("Luetjens", 'RGM-84C Harpoon', 8)
    SM.AddToUnitMagazine("Luetjens", 'Mk-46 Mod5', 12)
    SM.AddToUnitMagazine("Luetjens", 'RUR-5 ASROC', 16)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.219661, 0.953844, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.227394, 0.956325, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.261870, 0.956698, 0.000000, 12.000000)
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
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Jever AB"
    unit.SetPosition(7.530098, 53.320484, -0.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Jever AB", '20mm PGU', 1635)
    SM.AddToUnitMagazine("Jever AB", '20mm PGU-28/B', 1635)
    SM.AddToUnitMagazine("Jever AB", '300 gallon wing tank', 6)
    SM.AddToUnitMagazine("Jever AB", '330 gallon wing tank', 64)
    SM.AddToUnitMagazine("Jever AB", '370 gallon wing tank', 20)
    SM.AddToUnitMagazine("Jever AB", '594 gallon wing tank', 16)
    SM.AddToUnitMagazine("Jever AB", '600 gallon centerline tank', 4)
    SM.AddToUnitMagazine("Jever AB", '600 gallon tank', 16)
    SM.AddToUnitMagazine("Jever AB", 'AGM-65B', 73)
    SM.AddToUnitMagazine("Jever AB", 'AGM-65D', 106)
    SM.AddToUnitMagazine("Jever AB", 'AGM-65E', 71)
    SM.AddToUnitMagazine("Jever AB", 'AGM-65F', 62)
    SM.AddToUnitMagazine("Jever AB", 'AGM-65G', 50)
    SM.AddToUnitMagazine("Jever AB", 'AGM-88B', 48)
    SM.AddToUnitMagazine("Jever AB", 'AIM-120A', 177)
    SM.AddToUnitMagazine("Jever AB", 'AIM-7P', 518)
    SM.AddToUnitMagazine("Jever AB", 'AIM-9M', 359)
    SM.AddToUnitMagazine("Jever AB", 'AIM-9P', 107)
    SM.AddToUnitMagazine("Jever AB", 'AIM-9P4', 107)
    SM.AddToUnitMagazine("Jever AB", 'ALARM', 38)
    SM.AddToUnitMagazine("Jever AB", 'AS.34 Kormoran', 10)
    SM.AddToUnitMagazine("Jever AB", 'AS.34 Kormoran II', 5)
    SM.AddToUnitMagazine("Jever AB", 'ASPIDE-1A', 426)
    SM.AddToUnitMagazine("Jever AB", 'BAe Sea Eagle', 9)
    SM.AddToUnitMagazine("Jever AB", 'Chaff-1', 4952)
    SM.AddToUnitMagazine("Jever AB", 'Flare-1', 4952)
    SM.AddToUnitMagazine("Jever AB", 'GBU-1/B', 18)
    SM.AddToUnitMagazine("Jever AB", 'GBU-10/B', 76)
    SM.AddToUnitMagazine("Jever AB", 'GBU-11/B', 10)
    SM.AddToUnitMagazine("Jever AB", 'GBU-12/B', 232)
    SM.AddToUnitMagazine("Jever AB", 'GBU-15/B', 39)
    SM.AddToUnitMagazine("Jever AB", 'GBU-16/B', 48)
    SM.AddToUnitMagazine("Jever AB", 'GBU-24/B', 55)
    SM.AddToUnitMagazine("Jever AB", 'GBU-24B/B', 55)
    SM.AddToUnitMagazine("Jever AB", 'GBU-27', 19)
    SM.AddToUnitMagazine("Jever AB", 'GBU-28B/B', 35)
    SM.AddToUnitMagazine("Jever AB", 'M117', 41)
    SM.AddToUnitMagazine("Jever AB", 'Mk 16 Zuni FFAR', 243)
    SM.AddToUnitMagazine("Jever AB", 'Mk 71 Zuni WAFAR', 243)
    SM.AddToUnitMagazine("Jever AB", 'Mk-81', 320)
    SM.AddToUnitMagazine("Jever AB", 'Mk-82', 509)
    SM.AddToUnitMagazine("Jever AB", 'Mk-83', 215)
    SM.AddToUnitMagazine("Jever AB", 'Mk-84', 95)
    SM.AddToUnitMagazine("Jever AB", 'Skyflash', 507)
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
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-1', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-1', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-2', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-2', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-3', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-3', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-4', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-4', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-5', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-5', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-6', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-6', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-7', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-7', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-8', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-8', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-9', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-10', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-11', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-11', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado F.Mk.3', 'Jever AAW-12', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW-12', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-1', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-1', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-2', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-2', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-3', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-3', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-4', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-4', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-5', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-5', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-6', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-6', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-7', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-7', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-8', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-8', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-9', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-9', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-10', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-10', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-11', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-11', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado ADV', 'Jever AAW2-12', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AAW2-12', '4 AIM-9M;2 330 gallon wing tank;4 AIM-7P;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'E-3C', 'Jever AEW-1', 3)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AEW-1', '')
    
    SM.AddUnitToFlightDeck('Jever AB', 'E-3C', 'Jever AEW-2', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever AEW-2', '')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado GR.Mk.1B', 'Jever ASUW-1', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever ASUW-1', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 ALARM;1 ALARM;1 BAe Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado GR.Mk.1B', 'Jever ASUW-2', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever ASUW-2', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 ALARM;1 ALARM;1 BAe Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado GR.Mk.1B', 'Jever ASUW-3', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever ASUW-3', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 ALARM;1 ALARM;1 BAe Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado GR.Mk.1B', 'Jever ASUW-4', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever ASUW-4', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 ALARM;1 ALARM;1 BAe Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado GR.Mk.1B', 'Jever ASUW-5', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever ASUW-5', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 ALARM;1 ALARM;1 BAe Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado GR.Mk.1B', 'Jever ASUW-6', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever ASUW-6', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 ALARM;1 ALARM;1 BAe Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado GR.Mk.1B', 'Jever ASUW-7', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever ASUW-7', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 ALARM;1 ALARM;1 BAe Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'Tornado GR.Mk.1B', 'Jever ASUW-8', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever ASUW-8', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 ALARM;1 ALARM;1 BAe Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-15E', 'Jever STK-1', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK-1', '2 GBU-24/B;2 AIM-9M;2 AIM-120A;4 GBU-12/B;4 GBU-12/B;1 GBU-28B/B;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-15E', 'Jever STK-2', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK-2', '2 GBU-24/B;2 AIM-9M;2 AIM-120A;4 GBU-12/B;4 GBU-12/B;1 GBU-28B/B;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-15E', 'Jever STK-3', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK-3', '2 GBU-24/B;2 AIM-9M;2 AIM-120A;4 GBU-12/B;4 GBU-12/B;1 GBU-28B/B;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-15E', 'Jever STK-4', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK-4', '2 GBU-24/B;2 AIM-9M;2 AIM-120A;4 GBU-12/B;4 GBU-12/B;1 GBU-28B/B;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-15E', 'Jever STK-5', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK-5', '2 GBU-24/B;2 AIM-9M;2 AIM-120A;4 GBU-12/B;4 GBU-12/B;1 GBU-28B/B;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-15E', 'Jever STK-6', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK-6', '2 GBU-24/B;2 AIM-9M;2 AIM-120A;4 GBU-12/B;4 GBU-12/B;1 GBU-28B/B;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-15E', 'Jever STK-7', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK-7', '2 GBU-24/B;2 AIM-9M;2 AIM-120A;4 GBU-12/B;4 GBU-12/B;1 GBU-28B/B;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-15E', 'Jever STK-8', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK-8', '2 GBU-24/B;2 AIM-9M;2 AIM-120A;4 GBU-12/B;4 GBU-12/B;1 GBU-28B/B;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'KC-135R', 'Jever TNK-1', 2)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever TNK-1', '')
    
    SM.AddUnitToFlightDeck('Jever AB', 'KC-135R', 'Jever TNK-2', 2)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever TNK-2', '')
    
    SM.AddUnitToFlightDeck('Jever AB', 'KC-135R', 'Jever TNK-3', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever TNK-3', '')
    
    SM.AddUnitToFlightDeck('Jever AB', 'KC-135R', 'Jever TNK-4', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever TNK-4', '')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-16C/D Blk 50', 'Jever STK2-1', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK2-1', '2 AIM-9M;2 AIM-120A;4 GBU-15/B;2 GBU-15/B;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-16C/D Blk 50', 'Jever STK2-2', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK2-2', '2 AIM-9M;2 AIM-120A;4 GBU-15/B;2 GBU-15/B;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-16C/D Blk 50', 'Jever STK2-3', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK2-3', '2 AIM-9M;2 AIM-120A;4 GBU-15/B;2 GBU-15/B;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-16C/D Blk 50', 'Jever STK2-4', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK2-4', '2 AIM-9M;2 AIM-120A;4 GBU-15/B;2 GBU-15/B;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-16C/D Blk 50', 'Jever STK2-5', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK2-5', '2 AIM-9M;2 AIM-120A;4 GBU-15/B;2 GBU-15/B;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-16C/D Blk 50', 'Jever STK2-6', 1)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever STK2-6', '2 AIM-9M;2 AIM-120A;4 GBU-15/B;2 GBU-15/B;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-4G', 'Jever WW-1', 2)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever WW-1', '2 370 gallon wing tank;2 AGM-88B;2 AIM-7P;2 AIM-7P;1 600 gallon centerline tank;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-4G', 'Jever WW-2', 2)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever WW-2', '2 370 gallon wing tank;2 AGM-88B;2 AIM-7P;2 AIM-7P;1 600 gallon centerline tank;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-4G', 'Jever WW-3', 2)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever WW-3', '2 370 gallon wing tank;2 AGM-88B;2 AIM-7P;2 AIM-7P;1 600 gallon centerline tank;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Jever AB', 'F-4G', 'Jever WW-4', 2)
    SM.SetFlightDeckUnitLoadout('Jever AB', 'Jever WW-4', '2 370 gallon wing tank;2 AGM-88B;2 AIM-7P;2 AIM-7P;1 600 gallon centerline tank;30 Flare-1;30 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Eggebek AB"
    unit.SetPosition(9.199811, 54.369856, 2.6)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Eggebek AB", 'Fuel', 2014912)
    SM.AddToUnitMagazine("Eggebek AB", '20mm PGU', 1687)
    SM.AddToUnitMagazine("Eggebek AB", '20mm PGU-28/B', 1687)
    SM.AddToUnitMagazine("Eggebek AB", '300 gallon wing tank', 20)
    SM.AddToUnitMagazine("Eggebek AB", '330 gallon wing tank', 36)
    SM.AddToUnitMagazine("Eggebek AB", '370 gallon wing tank', 40)
    SM.AddToUnitMagazine("Eggebek AB", '594 gallon wing tank', 36)
    SM.AddToUnitMagazine("Eggebek AB", 'AGM-65B', 35)
    SM.AddToUnitMagazine("Eggebek AB", 'AGM-65D', 79)
    SM.AddToUnitMagazine("Eggebek AB", 'AGM-65E', 34)
    SM.AddToUnitMagazine("Eggebek AB", 'AGM-65F', 29)
    SM.AddToUnitMagazine("Eggebek AB", 'AGM-65G', 24)
    SM.AddToUnitMagazine("Eggebek AB", 'AGM-84A Harpoon', 28)
    SM.AddToUnitMagazine("Eggebek AB", 'AGM-84C Harpoon', 14)
    SM.AddToUnitMagazine("Eggebek AB", 'AGM-84D Harpoon', 30)
    SM.AddToUnitMagazine("Eggebek AB", 'AGM-84E SLAM', 31)
    SM.AddToUnitMagazine("Eggebek AB", 'AGM-84F Harpoon', 16)
    SM.AddToUnitMagazine("Eggebek AB", 'AGM-88B', 90)
    SM.AddToUnitMagazine("Eggebek AB", 'AIM-120A', 116)
    SM.AddToUnitMagazine("Eggebek AB", 'AIM-7P', 147)
    SM.AddToUnitMagazine("Eggebek AB", 'AIM-9M', 177)
    SM.AddToUnitMagazine("Eggebek AB", 'AIM-9P', 137)
    SM.AddToUnitMagazine("Eggebek AB", 'AIM-9P4', 137)
    SM.AddToUnitMagazine("Eggebek AB", 'ALARM', 62)
    SM.AddToUnitMagazine("Eggebek AB", 'AS.34 Kormoran', 11)
    SM.AddToUnitMagazine("Eggebek AB", 'AS.34 Kormoran II', 5)
    SM.AddToUnitMagazine("Eggebek AB", 'ASPIDE-1A', 99)
    SM.AddToUnitMagazine("Eggebek AB", 'BAe Sea Eagle', 10)
    SM.AddToUnitMagazine("Eggebek AB", 'Chaff-1', 2861)
    SM.AddToUnitMagazine("Eggebek AB", 'DICASS (85) Sonobuoy', 89)
    SM.AddToUnitMagazine("Eggebek AB", 'DICASS (90) Sonobuoy', 34)
    SM.AddToUnitMagazine("Eggebek AB", 'DIFAR (85) Sonobuoy', 263)
    SM.AddToUnitMagazine("Eggebek AB", 'DIFAR (90) Sonobuoy', 101)
    SM.AddToUnitMagazine("Eggebek AB", 'Flare-1', 2861)
    SM.AddToUnitMagazine("Eggebek AB", 'GBU-10/B', 33)
    SM.AddToUnitMagazine("Eggebek AB", 'GBU-12/B', 148)
    SM.AddToUnitMagazine("Eggebek AB", 'GBU-16/B', 79)
    SM.AddToUnitMagazine("Eggebek AB", 'GBU-24/B', 32)
    SM.AddToUnitMagazine("Eggebek AB", 'GBU-24B/B', 32)
    SM.AddToUnitMagazine("Eggebek AB", 'GBU-27', 31)
    SM.AddToUnitMagazine("Eggebek AB", 'GBU-28B/B', 52)
    SM.AddToUnitMagazine("Eggebek AB", 'LOFAR (85) Sonobuoy', 89)
    SM.AddToUnitMagazine("Eggebek AB", 'LOFAR (90) Sonobuoy', 34)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk 16 Zuni FFAR', 616)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk 71 Zuni WAFAR', 616)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk-36 DST', 3)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk-40 DST', 3)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk-41 DST', 2)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk-46 Mod5', 165)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk-50', 87)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk-56 Mine', 11)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk-81', 148)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk-82', 525)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk-83', 222)
    SM.AddToUnitMagazine("Eggebek AB", 'Mk-84', 90)
    SM.AddToUnitMagazine("Eggebek AB", 'Skyflash', 132)
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
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-1', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-1', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-2', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-2', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-3', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-3', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-4', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-4', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-5', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-5', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-6', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-6', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-7', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-7', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-8', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-8', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-9', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-10', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-11', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-11', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado IDS (Germany)', 'Egg AAW-12', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW-12', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AS.34 Kormoran II;1 AS.34 Kormoran II;1 AGM-88B;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 OCU', 'Egg AAW2-1', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW2-1', '2 AIM-9M;2 AIM-120A;2 AIM-120A;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 OCU', 'Egg AAW2-2', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW2-2', '2 AIM-9M;2 AIM-120A;2 AIM-120A;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 OCU', 'Egg AAW2-3', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW2-3', '2 AIM-9M;2 AIM-120A;2 AIM-120A;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 OCU', 'Egg AAW2-4', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW2-4', '2 AIM-9M;2 AIM-120A;2 AIM-120A;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 OCU', 'Egg AAW2-5', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW2-5', '2 AIM-9M;2 AIM-120A;2 AIM-120A;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 OCU', 'Egg AAW2-6', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW2-6', '2 AIM-9M;2 AIM-120A;2 AIM-120A;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 OCU', 'Egg AAW2-7', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW2-7', '2 AIM-9M;2 AIM-120A;2 AIM-120A;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 OCU', 'Egg AAW2-8', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AAW2-8', '2 AIM-9M;2 AIM-120A;2 AIM-120A;2 370 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-1', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-1', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-2', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-2', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-3', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-3', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-4', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-4', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-5', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-5', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-6', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-6', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-7', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-7', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-8', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-8', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-9', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-9', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-10', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-10', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-11', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-11', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'F-16A/B Blk 15 ADF', 'Egg STK-12', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK-12', '2 AIM-9M;2 AIM-9M;4 Mk-83;2 370 gallon wing tank;1 Mk-83;30 Flare-1;30 Chaff-1;33 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado GR.Mk.1', 'Egg STK2-1', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK2-1', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-65D;1 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado GR.Mk.1', 'Egg STK2-2', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK2-2', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-65D;1 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado GR.Mk.1', 'Egg STK2-3', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK2-3', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-65D;1 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado GR.Mk.1', 'Egg STK2-4', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK2-4', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-65D;1 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado GR.Mk.1', 'Egg STK2-5', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK2-5', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-65D;1 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Tornado GR.Mk.1', 'Egg STK2-6', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg STK2-6', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-65D;1 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'KC-135R', 'Egg TNK-1', 2)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg TNK-1', '')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'KC-135R', 'Egg TNK-2', 2)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg TNK-2', '')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'KC-135R', 'Egg TNK-3', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg TNK-3', '')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'KC-135R', 'Egg TNK-4', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg TNK-4', '')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Gannet AEW.3', 'Egg AEW-1', 3)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AEW-1', '')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'Gannet AEW.3', 'Egg AEW-2', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg AEW-2', '')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'P-3C III Orion', 'Egg ASW-1', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg ASW-1', '17 DICASS (90) Sonobuoy;17 LOFAR (90) Sonobuoy;50 DIFAR (90) Sonobuoy;0 Empty;2 AGM-84E SLAM;2 AGM-84E SLAM;2 Mk-46 Mod5;2 Mk-46 Mod5;6 Mk-46 Mod5;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'P-3C III Orion', 'Egg ASW-2', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg ASW-2', '17 DICASS (90) Sonobuoy;17 LOFAR (90) Sonobuoy;50 DIFAR (90) Sonobuoy;0 Empty;2 AGM-84E SLAM;2 AGM-84E SLAM;2 Mk-46 Mod5;2 Mk-46 Mod5;6 Mk-46 Mod5;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'P-3C III Orion', 'Egg ASW-3', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg ASW-3', '17 DICASS (90) Sonobuoy;17 LOFAR (90) Sonobuoy;50 DIFAR (90) Sonobuoy;0 Empty;2 AGM-84E SLAM;2 AGM-84E SLAM;2 Mk-46 Mod5;2 Mk-46 Mod5;6 Mk-46 Mod5;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Eggebek AB', 'P-3C III Orion', 'Egg ASW-4', 1)
    SM.SetFlightDeckUnitLoadout('Eggebek AB', 'Egg ASW-4', '17 DICASS (90) Sonobuoy;17 LOFAR (90) Sonobuoy;50 DIFAR (90) Sonobuoy;0 Empty;2 AGM-84E SLAM;2 AGM-84E SLAM;2 Mk-46 Mod5;2 Mk-46 Mod5;6 Mk-46 Mod5;30 Chaff-1;30 Flare-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Gardermoen AB"
    unit.SetPosition(11.050236, 60.109747, 8.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Gardermoen AB", 'Fuel', 3000000)
    SM.AddToUnitMagazine("Gardermoen AB", '330 gallon wing tank', 56)
    SM.AddToUnitMagazine("Gardermoen AB", '594 gallon wing tank', 32)
    SM.AddToUnitMagazine("Gardermoen AB", 'AGM-65D', 36)
    SM.AddToUnitMagazine("Gardermoen AB", 'AGM-88B', 59)
    SM.AddToUnitMagazine("Gardermoen AB", 'AIM-120A', 67)
    SM.AddToUnitMagazine("Gardermoen AB", 'AIM-7P', 227)
    SM.AddToUnitMagazine("Gardermoen AB", 'AIM-9M', 157)
    SM.AddToUnitMagazine("Gardermoen AB", 'ALARM', 59)
    SM.AddToUnitMagazine("Gardermoen AB", 'AS.34 Kormoran', 15)
    SM.AddToUnitMagazine("Gardermoen AB", 'AS.34 Kormoran II', 8)
    SM.AddToUnitMagazine("Gardermoen AB", 'ASPIDE-1A', 237)
    SM.AddToUnitMagazine("Gardermoen AB", 'BAe Sea Eagle', 15)
    SM.AddToUnitMagazine("Gardermoen AB", 'GBU-10/B', 31)
    SM.AddToUnitMagazine("Gardermoen AB", 'GBU-12/B', 142)
    SM.AddToUnitMagazine("Gardermoen AB", 'GBU-16/B', 75)
    SM.AddToUnitMagazine("Gardermoen AB", 'GBU-24/B', 31)
    SM.AddToUnitMagazine("Gardermoen AB", 'GBU-24B/B', 31)
    SM.AddToUnitMagazine("Gardermoen AB", 'GBU-27', 30)
    SM.AddToUnitMagazine("Gardermoen AB", 'GBU-28B/B', 50)
    SM.AddToUnitMagazine("Gardermoen AB", 'Mk-81', 142)
    SM.AddToUnitMagazine("Gardermoen AB", 'Mk-82', 170)
    SM.AddToUnitMagazine("Gardermoen AB", 'Mk-83', 94)
    SM.AddToUnitMagazine("Gardermoen AB", 'Mk-84', 41)
    SM.AddToUnitMagazine("Gardermoen AB", 'Skyflash', 292)
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
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-1', 2)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-1', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-2', 2)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-2', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-3', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-3', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-4', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-4', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-5', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-5', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-6', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-6', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-7', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-7', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-8', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-8', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-9', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-10', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-11', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-11', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado F.Mk.3', 'Gard AAW-12', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard AAW-12', '4 AIM-9M;2 330 gallon wing tank;4 Skyflash SuperTEMP;30 27mm BK27 27x145mm;45 Flare-1;45 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado GR.Mk.1B', 'Gard ASUW-1', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard ASUW-1', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 Bae Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado GR.Mk.1B', 'Gard ASUW-2', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard ASUW-2', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 Bae Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado GR.Mk.1B', 'Gard ASUW-3', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard ASUW-3', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 Bae Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado GR.Mk.1B', 'Gard ASUW-4', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard ASUW-4', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 Bae Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado GR.Mk.1B', 'Gard ASUW-5', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard ASUW-5', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 Bae Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado GR.Mk.1B', 'Gard ASUW-6', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard ASUW-6', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 Bae Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado GR.Mk.1B', 'Gard ASUW-7', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard ASUW-7', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 Bae Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado GR.Mk.1B', 'Gard ASUW-8', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard ASUW-8', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 Bae Sea Eagle;1 BAe Sea Eagle;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado IDS (Germany)', 'Gard STK-1', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard STK-1', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado IDS (Germany)', 'Gard STK-2', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard STK-2', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado IDS (Germany)', 'Gard STK-3', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard STK-3', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado IDS (Germany)', 'Gard STK-4', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard STK-4', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado IDS (Germany)', 'Gard STK-5', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard STK-5', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado IDS (Germany)', 'Gard STK-6', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard STK-6', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado IDS (Germany)', 'Gard STK-7', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard STK-7', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'Tornado IDS (Germany)', 'Gard STK-8', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard STK-8', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;2 AGM-65D;2 AGM-65D;1 ALARM;30 27mm BK27 27x145mm;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'KC-135R', 'Gard Refuel-1', 2)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard Refuel-1', '')
    
    SM.AddUnitToFlightDeck('Gardermoen AB', 'KC-135R', 'Gard Refuel-2', 1)
    SM.SetFlightDeckUnitLoadout('Gardermoen AB', 'Gard Refuel-2', '')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oberon SS'
    unit.unitName = "HMS Odin"
    unit.SetPosition(17.208272, 55.186378, -40.0)
    unit.heading = 90.00
    unit.speed = 3.9
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
    SM.AddToUnitMagazine("HMS Odin", 'mk-24 Tigerfish', 13)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(1, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.293956, 0.969194, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 206A'
    unit.unitName = "U 25"
    unit.SetPosition(18.241200, 55.180935, -35.0)
    unit.heading = 90.00
    unit.speed = 3.9
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'DM2A3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'DM2A3', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(3, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.333777, 0.963128, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 212A'
    unit.unitName = "U 31"
    unit.SetPosition(18.537820, 55.578339, -45.0)
    unit.heading = 90.00
    unit.speed = 4.8
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'DM2A4.1', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("U 31", 'DM2A4.1', 10)
    UI.SetSensorState(4, 0)
    UI.SetSensorState(5, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.336890, 0.990136, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 212A'
    unit.unitName = "U 33"
    unit.SetPosition(19.268112, 56.980080, -100.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'DM2A4.1', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("U 33", 'DM2A4.1', 10)
    UI.SetSensorState(4, 0)
    UI.SetSensorState(5, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.353408, 0.994469, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 212A'
    unit.unitName = "U 32"
    unit.SetPosition(20.661947, 57.374792, -45.0)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'DM2A4.1', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'DM2A4.1', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("U 32", 'DM2A4.1', 10)
    UI.SetSensorState(4, 0)
    UI.SetSensorState(5, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.343706, 1.001379, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Vastergotland'
    unit.unitName = "Halsginland"
    unit.SetPosition(20.461641, 58.609171, -55.0)
    unit.heading = 90.00
    unit.speed = 4.2
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Type-431 Torpedo', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Type-431 Torpedo', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Type-431 Torpedo', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Type-613 Torpedo', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Halsginland", 'Type-431 Torpedo', 8)
    SM.AddToUnitMagazine("Halsginland", 'Type-613 Torpedo', 6)
    UI.SetSensorState(4, 0)
    UI.SetSensorState(5, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.371428, 1.023084, 0.000000, 0.000000)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"Type-613 Torpedo": 24, "Type-431 Torpedo": 32}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 340.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 0, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 1}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"Type-613 Torpedo": [4, 4], "Type-431 Torpedo": [8, 8]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Vastergotland'
    unit.unitName = "Vastergotland"
    unit.SetPosition(20.471037, 57.710487, -100.0)
    unit.heading = 8.13
    unit.speed = 3.0
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Type-431 Torpedo', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Type-431 Torpedo', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Type-431 Torpedo', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Type-613 Torpedo', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Vastergotland", 'Type-431 Torpedo', 5)
    SM.AddToUnitMagazine("Vastergotland", 'Type-613 Torpedo', 6)
    UI.SetSensorState(4, 0)
    UI.SetSensorState(5, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.346648, 1.007444, 0.000000, 0.000000)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 50, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"Type-613 Torpedo": 36, "Type-431 Torpedo": 15}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 300.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 0, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 1}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"Type-613 Torpedo": [6, 6], "Type-431 Torpedo": [6, 6]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Vastergotland'
    unit.unitName = "Ostergotland"
    unit.SetPosition(20.039142, 58.147138, -100.0)
    unit.heading = 48.81
    unit.speed = 3.8
    unit.cost = 900000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Type-431 Torpedo', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Type-431 Torpedo', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Type-431 Torpedo', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Type-613 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Type-613 Torpedo', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Ostergotland", 'Type-431 Torpedo', 5)
    SM.AddToUnitMagazine("Ostergotland", 'Type-613 Torpedo', 6)
    UI.SetSensorState(4, 0)
    UI.SetSensorState(5, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 50, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"Type-613 Torpedo": 36, "Type-431 Torpedo": 15}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 300.0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 0, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"Type-613 Torpedo": [6, 6], "Type-431 Torpedo": [6, 6]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Communications Station'
    unit.unitName = "Comms Station"
    unit.SetPosition(14.787009, 55.190733, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Generic Mobile Artillery 155mm'
    unit.unitName = "Coastal Arty 1"
    unit.SetPosition(14.790104, 55.255189, 0.0)
    unit.heading = 63.43
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '12.7mm B-30 AP', 17)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Gen155ART', 40)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Generic Mobile Artillery 155mm'
    unit.unitName = "Coastal Arty 2"
    unit.SetPosition(15.118236, 55.128395, 86.0)
    unit.heading = 63.43
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '12.7mm B-30 AP', 17)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Gen155ART', 40)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'FPS-117 Installation'
    unit.unitName = "Radar Site"
    unit.SetPosition(14.875417, 55.116707, 1.0)
    unit.heading = 53.75
    unit.speed = 0.0
    unit.cost = 10000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Forward Observation Post'
    unit.unitName = "FO Post"
    unit.SetPosition(14.930994, 55.193483, 1.0)
    unit.heading = 55.49
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Small Airstrip'
    unit.unitName = "Bornholm Airport"
    unit.SetPosition(14.803740, 55.054254, -0.0)
    unit.heading = 280.62
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Govt Building"
    unit.SetPosition(14.786838, 55.073162, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Communications Station'
    unit.unitName = "Telephone Switch Center"
    unit.SetPosition(14.852957, 55.053338, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fuel Tanks'
    unit.unitName = "Fuel Center"
    unit.SetPosition(15.023927, 55.011741, 1.0)
    unit.heading = 180.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'POL Tank'
    unit.unitName = "Oil Center"
    unit.SetPosition(14.695107, 55.133437, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-X(6) (Generic)'
    unit.unitName = "Coastal SSM Battery1"
    unit.SetPosition(14.750054, 55.298277, 0.0)
    unit.heading = 54.46
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RBS-15M', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-X(6) (Generic)'
    unit.unitName = "Coastal SSM Battry2"
    unit.SetPosition(15.133935, 55.085996, 25.2)
    unit.heading = 64.65
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RBS-15M', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-X(6) (Generic)'
    unit.unitName = "Coastal SSM Battery3"
    unit.SetPosition(14.959527, 55.215255, 48.4)
    unit.heading = 64.65
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RBS-15M', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('EngageAllAir', 2.000000, 0)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gepard Type 143'
    unit.unitName = "Nerz"
    UI = SM.GetUnitInterface('Puma')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0449
    lat_deg = 57.296*leader_track.Lat + 0.0527
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 9.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MM-40 B2 Exocet', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MM-40 B2 Exocet', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Nerz", '76mm HE-MOM', 480)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    leader_id = UI.LookupFriendlyId('Puma')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(6.012, 0.720, 0.473, 0.162)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gepard Type 143'
    unit.unitName = "Wiesel"
    UI = SM.GetUnitInterface('Puma')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0939
    lat_deg = 57.296*leader_track.Lat + -0.0019
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 10.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MM-40 B2 Exocet', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MM-40 B2 Exocet', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Wiesel", '76mm HE-MOM', 480)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    leader_id = UI.LookupFriendlyId('Puma')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(5.978, 0.683, 1.697, 0.132)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gepard Type 143'
    unit.unitName = "Hermelin"
    UI = SM.GetUnitInterface('Puma')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1000
    lat_deg = 57.296*leader_track.Lat + 0.0311
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 10.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'MM-40 B2 Exocet', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'MM-40 B2 Exocet', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Hermelin", '76mm HE-MOM', 480)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    leader_id = UI.LookupFriendlyId('Puma')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(6.983, 0.696, 1.131, 0.112)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Hauk PTGM'
    unit.unitName = "Skarv"
    UI = SM.GetUnitInterface('Orn')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.2381
    lat_deg = 57.296*leader_track.Lat + -0.0030
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 9.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Penguin Mk2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '40mm HE-T', 50)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm Rh202 HE-T', 50)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Skarv", '40mm HE-T', 500)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Orn')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(15.000, 0.907, 1.629, 0.059)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Hauk PTGM'
    unit.unitName = "Stegg"
    UI = SM.GetUnitInterface('Orn')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.2292
    lat_deg = 57.296*leader_track.Lat + 0.0430
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 10.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Penguin Mk2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '40mm HE-T', 50)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm Rh202 HE-T', 50)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Stegg", '40mm HE-T', 500)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Orn')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(15.000, 1.042, 1.281, 0.078)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Hauk PTGM'
    unit.unitName = "Falk"
    UI = SM.GetUnitInterface('Orn')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1220
    lat_deg = 57.296*leader_track.Lat + -0.0197
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 10.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Penguin Mk2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '40mm HE-T', 50)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm Rh202 HE-T', 50)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Falk", '40mm HE-T', 500)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Orn')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(7.980, 0.910, 1.921, 0.108)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Hauk PTGM'
    unit.unitName = "Terne"
    UI = SM.GetUnitInterface('Orn')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1147
    lat_deg = 57.296*leader_track.Lat + 0.0369
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 10.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Penguin Mk2', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'Type-612 Torpedo', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '40mm HE-T', 50)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm Rh202 HE-T', 50)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Terne", '40mm HE-T', 500)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Orn')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(7.978, 0.989, 1.095, 0.136)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Avenger MCM'
    unit.unitName = "USS Ardent"
    UI = SM.GetUnitInterface('HMS Southampton')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1211
    lat_deg = 57.296*leader_track.Lat + -0.1716
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 139.76
    unit.speed = 4.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 1, '.50 cal bullet', 600)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Ardent", '.50 cal bullet', 12000)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Southampton')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(21.009, 0.837, 2.769, 0.051)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Kortenaer FFG (1984)'
    unit.unitName = "Banckert"
    UI = SM.GetUnitInterface('HMS Southampton')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0164
    lat_deg = 57.296*leader_track.Lat + -0.1213
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 142.43
    unit.speed = 4.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7M(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76mm HE-MOM', 80)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm PGU-13/B HE-I', 79)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Banckert", 'Fuel', 23700)
    SM.AddToUnitMagazine("Banckert", 'Mk-46 Mod5', 29)
    SM.AddToUnitMagazine("Banckert", 'Sea Skua', 16)
    SM.AddToUnitMagazine("Banckert", 'RIM-7M(v1)', 16)
    SM.AddToUnitMagazine("Banckert", '76mm HE-MOM', 480)
    SM.AddToUnitMagazine("Banckert", '30mm PGU-14/B API', 474)
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
    leader_id = UI.LookupFriendlyId('HMS Southampton')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(14.019, 0.850, -3.066, 0.072)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Banckert', 'SH-14D', 'Kort Lynx1', 2)
    SM.SetFlightDeckUnitLoadout('Banckert', 'Kort Lynx1', '1 Mk-46 Mod5;1 Mk-46 Mod5;')
    
    SM.AddUnitToFlightDeck('Banckert', 'SH-14D', 'Kort Lynx2', 1)
    SM.SetFlightDeckUnitLoadout('Banckert', 'Kort Lynx2', '1 Mk-46 Mod5;1 Mk-46 Mod5;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 22 FF Batch 3'
    unit.unitName = "HMS Campbeltown"
    UI = SM.GetUnitInterface('HMS Southampton')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0771
    lat_deg = 57.296*leader_track.Lat + -0.1132
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 140.71
    unit.speed = 5.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Sea Wolf', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'Sea Wolf', 6)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '114mm N4A1 HE', 16)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm PGU-14/B API', 79)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Stingray', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Campbeltown", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Campbeltown", 'Stingray', 29)
    SM.AddToUnitMagazine("HMS Campbeltown", 'Sea Skua', 16)
    SM.AddToUnitMagazine("HMS Campbeltown", 'LOFAR (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Campbeltown", 'DICASS (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Campbeltown", 'DIFAR (90) Sonobuoy', 609)
    SM.AddToUnitMagazine("HMS Campbeltown", '30mm PGU-14/B API', 474)
    SM.AddToUnitMagazine("HMS Campbeltown", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Campbeltown", 'Sea Wolf', 40)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Southampton')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(13.953, 0.991, 2.785, 0.066)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('HMS Campbeltown', 'Lynx HAS.Mk.2', 'Type 22 B3 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Campbeltown', 'Type 22 B3 Lynx 1', '1 Stingray;1 Stingray;')
    
    SM.AddUnitToFlightDeck('HMS Campbeltown', 'Lynx HAS.Mk.2', 'Type 22 B3 Lynx 2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Campbeltown', 'Type 22 B3 Lynx 2', '1 Stingray;1 Stingray;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 22 FF Batch 2'
    unit.unitName = "HMS Brave"
    UI = SM.GetUnitInterface('HMS Southampton')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1720
    lat_deg = 57.296*leader_track.Lat + -0.0886
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 141.84
    unit.speed = 5.1
    unit.cost = 0.0
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
    SM.AddToUnitMagazine("HMS Brave", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Brave", 'Stingray', 29)
    SM.AddToUnitMagazine("HMS Brave", 'Sea Skua', 16)
    SM.AddToUnitMagazine("HMS Brave", 'LOFAR (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Brave", 'DICASS (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Brave", 'DIFAR (90) Sonobuoy', 609)
    SM.AddToUnitMagazine("HMS Brave", 'Sea Wolf', 40)
    SM.AddToUnitMagazine("HMS Brave", '30mm/75 GCM-AO3-2 APDS', 1660)
    SM.AddToUnitMagazine("HMS Brave", '20mm/85  GAM-B01 HE-I', 500)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Southampton')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(15.023, 1.020, 2.333, 0.057)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('HMS Brave', 'Lynx HAS.Mk.2', 'Type 22 B2 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Brave', 'Type 22 B2 Lynx 1', '1 Stingray;1 Stingray;')
    
    SM.AddUnitToFlightDeck('HMS Brave', 'Lynx HAS.Mk.2', 'Type 22 B2 Lynx 2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Brave', 'Type 22 B2 Lynx 2', '1 Stingray;1 Stingray;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Type 23 FF'
    unit.unitName = "HMS Marlborough"
    UI = SM.GetUnitInterface('HMS Southampton')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0350
    lat_deg = 57.296*leader_track.Lat + -0.0456
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 147.09
    unit.speed = 5.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'Sea Wolf', 6)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84D Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '114mm N4A1 HE', 16)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm/75 GCM-AO3-2 APDS', 83)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm/75 GCM-AO3-2 APDS', 83)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Stingray', 3)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'Stingray', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("HMS Marlborough", 'Fuel', 23700)
    SM.AddToUnitMagazine("HMS Marlborough", 'Stingray', 29)
    SM.AddToUnitMagazine("HMS Marlborough", 'Sea Skua', 16)
    SM.AddToUnitMagazine("HMS Marlborough", 'LOFAR (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Marlborough", 'DICASS (90) Sonobuoy', 202)
    SM.AddToUnitMagazine("HMS Marlborough", 'DIFAR (90) Sonobuoy', 609)
    SM.AddToUnitMagazine("HMS Marlborough", '114mm N4A1 HE', 800)
    SM.AddToUnitMagazine("HMS Marlborough", 'Sea Wolf', 20)
    SM.AddToUnitMagazine("HMS Marlborough", '30mm/75 GCM-AO3-2 APDS', 1660)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Southampton')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(6.009, 0.426, 2.766, 0.070)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('HMS Marlborough', 'Lynx HAS.Mk.2', 'Type 23 Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('HMS Marlborough', 'Type 23 Lynx 1', '1 Stingray;1 Stingray;')
    
    SM.AddUnitToFlightDeck('HMS Marlborough', 'Lynx HAS.Mk.2', 'Type 23 Lynx 2', 1)
    SM.SetFlightDeckUnitLoadout('HMS Marlborough', 'Type 23 Lynx 2', '1 Stingray;1 Stingray;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Osprey MHC'
    unit.unitName = "USS Osprey"
    UI = SM.GetUnitInterface('Luetjens')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1871
    lat_deg = 57.296*leader_track.Lat + 0.0587
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 4.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 1, '.50 cal bullet', 600)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Luetjens')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(13.500, 1.143, 1.106, 0.085)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Luetjens DDG'
    unit.unitName = "Molders"
    UI = SM.GetUnitInterface('Luetjens')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0697
    lat_deg = 57.296*leader_track.Lat + 0.0253
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 5.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-66A', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, '127mm mk 41 AAC', 40)
    SM.SetUnitLauncherItem(unit.unitName, 2, '127mm mk 41 AAC', 40)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RUR-5 ASROC', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Molders", '127mm mk 41 AAC', 360)
    SM.AddToUnitMagazine("Molders", '127mm mk 41 HC', 140)
    SM.AddToUnitMagazine("Molders", 'RIM-66A', 32)
    SM.AddToUnitMagazine("Molders", 'RGM-84C Harpoon', 8)
    SM.AddToUnitMagazine("Molders", 'Mk-46 Mod5', 12)
    SM.AddToUnitMagazine("Molders", 'RUR-5 ASROC', 16)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Luetjens')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(5.035, 0.733, 1.095, 0.163)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bremen FFGHM (1982)'
    unit.unitName = "Niedersachsen"
    UI = SM.GetUnitInterface('Luetjens')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1519
    lat_deg = 57.296*leader_track.Lat + 0.0489
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 4.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7M(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '76mm HE-MOM', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Niedersachsen", 'Fuel', 11350)
    SM.AddToUnitMagazine("Niedersachsen", 'Mk-46 Mod5', 17)
    SM.AddToUnitMagazine("Niedersachsen", 'Sea Skua', 4)
    SM.AddToUnitMagazine("Niedersachsen", 'LOFAR (90) Sonobuoy', 105)
    SM.AddToUnitMagazine("Niedersachsen", 'DICASS (90) Sonobuoy', 105)
    SM.AddToUnitMagazine("Niedersachsen", 'DIFAR (90) Sonobuoy', 315)
    SM.AddToUnitMagazine("Niedersachsen", '76mm HE-MOM', 220)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Luetjens')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(11.026, 0.649, 1.092, 0.076)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Niedersachsen', 'Sea Lynx Mk 88', 'Bremen Sea Lynx 1', 1)
    SM.SetFlightDeckUnitLoadout('Niedersachsen', 'Bremen Sea Lynx 1', '1 Mk-46 Mod5;1 Mk-46 Mod5;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bremen FFGHM (1982)'
    unit.unitName = "Rheinlan-Pfalz"
    UI = SM.GetUnitInterface('Luetjens')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0981
    lat_deg = 57.296*leader_track.Lat + 0.0610
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 5.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7M(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '76mm HE-MOM', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Rheinlan-Pfalz", 'Fuel', 14173)
    SM.AddToUnitMagazine("Rheinlan-Pfalz", 'Mk-46 Mod5', 17)
    SM.AddToUnitMagazine("Rheinlan-Pfalz", 'Sea Skua', 4)
    SM.AddToUnitMagazine("Rheinlan-Pfalz", 'LOFAR (90) Sonobuoy', 105)
    SM.AddToUnitMagazine("Rheinlan-Pfalz", 'DICASS (90) Sonobuoy', 210)
    SM.AddToUnitMagazine("Rheinlan-Pfalz", 'DIFAR (90) Sonobuoy', 630)
    SM.AddToUnitMagazine("Rheinlan-Pfalz", '76mm HE-MOM', 240)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Luetjens')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(8.981, 0.587, 0.778, 0.069)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Rheinlan-Pfalz', 'Sea Lynx Mk 88', 'Bremen Sea Lynx 101', 1)
    SM.SetFlightDeckUnitLoadout('Rheinlan-Pfalz', 'Bremen Sea Lynx 101', '1 Mk-46 Mod5;1 Mk-46 Mod5;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bremen FFGHM (1982)'
    unit.unitName = "Koln"
    UI = SM.GetUnitInterface('Luetjens')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.1387
    lat_deg = 57.296*leader_track.Lat + 0.0150
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 4.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7M(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '76mm HE-MOM', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Koln", 'Fuel', 12075)
    SM.AddToUnitMagazine("Koln", 'Mk-46 Mod5', 17)
    SM.AddToUnitMagazine("Koln", 'Sea Skua', 4)
    SM.AddToUnitMagazine("Koln", 'LOFAR (90) Sonobuoy', 105)
    SM.AddToUnitMagazine("Koln", 'DICASS (90) Sonobuoy', 315)
    SM.AddToUnitMagazine("Koln", 'DIFAR (90) Sonobuoy', 945)
    SM.AddToUnitMagazine("Koln", '76mm HE-MOM', 240)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('Luetjens')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(9.025, 0.830, 1.430, 0.088)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Koln', 'Sea Lynx Mk 88', 'Bremen Sea Lynx 201', 1)
    SM.SetFlightDeckUnitLoadout('Koln', 'Bremen Sea Lynx 201', '1 Mk-46 Mod5;1 Mk-46 Mod5;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Jacob van Heemskerck FFG'
    unit.unitName = "Jacob van Heemskerck"
    UI = SM.GetUnitInterface('HMS Southampton')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0575
    lat_deg = 57.296*leader_track.Lat + -0.0808
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 144.46
    unit.speed = 4.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7M(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66E', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm PGU-13/B HE-I', 79)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Mk-46 Mod5', 2)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Mk-46 Mod5', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Jacob van Heemskerck", '30mm PGU-14/B API', 474)
    SM.AddToUnitMagazine("Jacob van Heemskerck", 'RIM-66E', 39)
    SM.AddToUnitMagazine("Jacob van Heemskerck", 'RIM-7M(v1)', 16)
    SM.AddToUnitMagazine("Jacob van Heemskerck", 'Mk-46 Mod5', 12)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('HMS Southampton')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(10.038, 0.563, 2.772, 0.057)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641B Som'
    unit.unitName = "B-225"
    unit.SetPosition(19.419316, 55.694764, -42.6)
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
    SM.AddToUnitMagazine("B-225", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-225", '53-65M', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.290381, 0.961997, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641 SSK'
    unit.unitName = "B-28"
    unit.SetPosition(17.864308, 55.435157, -37.6)
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
    SM.AddToUnitMagazine("B-28", '53-65M', 4)
    SM.AddToUnitMagazine("B-28", 'SAET-60M', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.277761, 0.963704, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 641B Som'
    unit.unitName = "B-474"
    unit.SetPosition(14.874557, 55.603893, -35.0)
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
    SM.AddToUnitMagazine("B-474", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-474", '53-65M', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.263089, 0.967108, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877E Paltus'
    unit.unitName = "Kilo"
    unit.SetPosition(14.148448, 54.719877, -17.5)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 250000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'TEST-71ME', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65KE', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65KE', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'Igla-M SAM', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Kilo", 'TEST-71ME', 12)
    SM.AddToUnitMagazine("Kilo", '53-65KE', 6)
    SM.AddToUnitMagazine("Kilo", 'Igla-M SAM', 8)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.239454, 0.959686, 0.000000, 3.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 675'
    unit.unitName = "K-172"
    unit.SetPosition(15.933212, 54.839510, -17.6)
    unit.heading = 270.00
    unit.speed = 3.0
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
    SM.AddToUnitMagazine("K-172", 'SET-65', 8)
    SM.AddToUnitMagazine("K-172", '53-65M', 4)
    SM.AddToUnitMagazine("K-172", 'UMGT-1M', 4)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 670 Skat'
    unit.unitName = "K-320"
    unit.SetPosition(15.362316, 54.678795, -17.6)
    unit.heading = 291.80
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
    SM.AddToUnitMagazine("K-320", 'SET-65', 8)
    SM.AddToUnitMagazine("K-320", '53-65M', 4)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1124ME Albatros'
    unit.unitName = "MPK-69"
    unit.SetPosition(19.036064, 54.722569, 0.0)
    unit.heading = 90.00
    unit.speed = 4.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M33M', 20)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("MPK-69", '30mm OF-84 HE-FRAG AK-630M', 236)
    SM.AddToUnitMagazine("MPK-69", '53-65M', 4)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.323028, 0.960576, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.296558, 0.959740, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.264777, 0.955022, 0.000000, 12.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 205 Tsunami (Poland)'
    unit.unitName = "Swinoujscie"
    unit.SetPosition(19.542445, 54.783131, 0.0)
    unit.heading = 90.00
    unit.speed = 4.7
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20 Rubezh', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.319747, 0.964235, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.266569, 0.970192, 0.000000, 12.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 61 Kashin'
    unit.unitName = "Reshitelny"
    unit.SetPosition(21.287159, 58.913756, 0.0)
    unit.heading = -131.63
    unit.speed = 15.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-600', 16)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'V-600', 16)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'Kh-35', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Reshitelny", '53-65M', 30)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.335648, 0.988509, 0.000000, 15.000000)
    UI.AddNavWaypointAdvanced(0.280273, 0.960856, 0.000000, 15.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1164 Atlant'
    unit.unitName = "Marshal Ustinov"
    unit.SetPosition(22.614071, 59.481671, 0.0)
    unit.heading = -129.81
    unit.speed = 15.3
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
    SM.AddToUnitMagazine("Marshal Ustinov", 'Fuel', 68850)
    SM.AddToUnitMagazine("Marshal Ustinov", 'AT-1', 26)
    SM.AddToUnitMagazine("Marshal Ustinov", 'DICASS (85) Sonobuoy', 175)
    SM.AddToUnitMagazine("Marshal Ustinov", 'LOFAR (85) Sonobuoy', 175)
    SM.AddToUnitMagazine("Marshal Ustinov", 'DIFAR (85) Sonobuoy', 490)
    SM.AddToUnitMagazine("Marshal Ustinov", '30mm OF-84 HE-FRAG AK-630M', 1416)
    SM.AddToUnitMagazine("Marshal Ustinov", '130mm F-44 HE', 500)
    SM.AddToUnitMagazine("Marshal Ustinov", '53-65M', 30)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.369385, 1.027288, 0.000000, 15.000000)
    UI.AddNavWaypointAdvanced(0.334180, 0.986380, 0.000000, 15.000000)
    UI.AddNavWaypointAdvanced(0.263194, 0.970168, 0.000000, 15.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    SM.AddUnitToFlightDeck('Marshal Ustinov', 'Ka-27A', 'Atlant Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Marshal Ustinov', 'Atlant Ka-27 1', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 775  Ropucha'
    unit.unitName = "BDK-101 Oslyabya"
    unit.SetPosition(23.273317, 59.613967, 0.0)
    unit.heading = -119.74
    unit.speed = 15.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 2, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 3, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M32 Strela 2', 32)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("BDK-101 Oslyabya", '57mm Tracer-FRAG', 2800)
    SM.AddToUnitMagazine("BDK-101 Oslyabya", '30mm OF-84 HE-FRAG AK-630M', 472)
    SM.AddToUnitMagazine("BDK-101 Oslyabya", '9M32 Strela 2', 64)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.374186, 1.030630, 0.000000, 15.000000)
    UI.AddNavWaypointAdvanced(0.334327, 0.984880, 0.000000, 15.000000)
    UI.AddNavWaypointAdvanced(0.265476, 0.964769, 0.000000, 15.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Trawler2"
    unit.SetPosition(14.811933, 54.948429, 0.0)
    unit.heading = -132.27
    unit.speed = 7.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.242323, 0.953018, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Trawler "
    unit.SetPosition(14.437734, 55.484144, 0.0)
    unit.heading = 90.00
    unit.speed = 7.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.256604, 0.966076, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Nivenskoye AB"
    unit.SetPosition(20.360342, 54.330437, -0.0)
    unit.heading = 273.81
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Nivenskoye AB", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Nivenskoye AB", '23mm AM-23', 207)
    SM.AddToUnitMagazine("Nivenskoye AB", '3000 liter tank', 12)
    SM.AddToUnitMagazine("Nivenskoye AB", '30mm Su-25', 172)
    SM.AddToUnitMagazine("Nivenskoye AB", '600 liter tank', 24)
    SM.AddToUnitMagazine("Nivenskoye AB", 'Chaff-1', 10127)
    SM.AddToUnitMagazine("Nivenskoye AB", 'FAB-250', 207)
    SM.AddToUnitMagazine("Nivenskoye AB", 'FAB-500', 276)
    SM.AddToUnitMagazine("Nivenskoye AB", 'Flare-1', 10127)
    SM.AddToUnitMagazine("Nivenskoye AB", 'KAB-500Kr', 34)
    SM.AddToUnitMagazine("Nivenskoye AB", 'KAB-500L', 92)
    SM.AddToUnitMagazine("Nivenskoye AB", 'Kh-29T', 294)
    SM.AddToUnitMagazine("Nivenskoye AB", 'Kh-31P', 320)
    SM.AddToUnitMagazine("Nivenskoye AB", 'PTB-800', 12)
    SM.AddToUnitMagazine("Nivenskoye AB", 'R-24R', 57)
    SM.AddToUnitMagazine("Nivenskoye AB", 'R-24T', 57)
    SM.AddToUnitMagazine("Nivenskoye AB", 'R-27R', 859)
    SM.AddToUnitMagazine("Nivenskoye AB", 'R-60M', 343)
    SM.AddToUnitMagazine("Nivenskoye AB", 'R-60MK', 343)
    SM.AddToUnitMagazine("Nivenskoye AB", 'R-73E', 75)
    SM.AddToUnitMagazine("Nivenskoye AB", 'R-77', 195)
    SM.AddToUnitMagazine("Nivenskoye AB", 'R-77T', 130)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    BB.Write('InvMulti', '1')
    BB.Write('MagTonnage', '35')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'MiG-23', 'Niv AAW-1', 3)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW-1', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'MiG-23', 'Niv AAW-2', 3)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW-2', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'MiG-23', 'Niv AAW-3', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW-3', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'MiG-23', 'Niv AAW-4', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW-4', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'MiG-23', 'Niv AAW-5', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW-5', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'MiG-23', 'Niv AAW-6', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW-6', '2 R-24R;0 Empty;0 Empty;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-27', 'Niv AAW2-1', 3)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW2-1', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-27', 'Niv AAW2-2', 3)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW2-2', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-27', 'Niv AAW2-3', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW2-3', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-27', 'Niv AAW2-4', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW2-4', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-27', 'Niv AAW2-5', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW2-5', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-27', 'Niv AAW2-6', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW2-6', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-27', 'Niv AAW2-7', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW2-7', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-27', 'Niv AAW2-8', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv AAW2-8', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-30MK2', 'Niv STK-1', 2)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv STK-1', '2 R-73E;0 Empty;0 Empty;0 Empty;2 R-77;48 PPI-50;48 PRP-50;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-30MK2', 'Niv STK-2', 2)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv STK-2', '2 R-73E;0 Empty;0 Empty;0 Empty;2 R-77;48 PPI-50;48 PRP-50;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-30MK2', 'Niv STK-3', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv STK-3', '2 R-73E;0 Empty;0 Empty;0 Empty;2 R-77;48 PPI-50;48 PRP-50;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-30MK2', 'Niv STK-4', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv STK-4', '2 R-73E;0 Empty;0 Empty;0 Empty;2 R-77;48 PPI-50;48 PRP-50;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-25', 'Nic STK2-1', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Nic STK2-1', '2 R-60;8 FAB-250;2 600 liter tank;2 600 liter tank;5 30mm Su-25;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-25', 'Nic STK2-2', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Nic STK2-2', '2 R-60;8 FAB-250;2 600 liter tank;2 600 liter tank;5 30mm Su-25;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-25', 'Nic STK2-3', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Nic STK2-3', '2 R-60;8 FAB-250;2 600 liter tank;2 600 liter tank;5 30mm Su-25;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-25', 'Nic STK2-4', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Nic STK2-4', '2 R-60;8 FAB-250;2 600 liter tank;2 600 liter tank;5 30mm Su-25;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-25', 'Nic STK2-5', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Nic STK2-5', '2 R-60;8 FAB-250;2 600 liter tank;2 600 liter tank;5 30mm Su-25;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-25', 'Nic STK2-6', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Nic STK2-6', '2 R-60;8 FAB-250;2 600 liter tank;2 600 liter tank;5 30mm Su-25;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-24M', 'Niv STK3-1', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv STK3-1', '2 FAB-500;2 FAB-500;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-24M', 'Niv STK3-2', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv STK3-2', '2 FAB-500;2 FAB-500;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-24M', 'Niv STK3-3', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv STK3-3', '2 FAB-500;2 FAB-500;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-24M', 'Niv STK3-4', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv STK3-4', '2 FAB-500;2 FAB-500;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-24M', 'Niv STK3-5', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv STK3-5', '2 FAB-500;2 FAB-500;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Nivenskoye AB', 'Su-24M', 'Niv STK3-6', 1)
    SM.SetFlightDeckUnitLoadout('Nivenskoye AB', 'Niv STK3-6', '2 FAB-500;2 FAB-500;2 Kh-29T;2 Kh-29T;6 23mm AM-23;30 Flare-1;30 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Niv STK-1')
    FP.SetMissionLaunchTime(mission_id, '08:01:00+0m')
    FP.SetMissionDatum(mission_id, 0.2614550, 0.9621370)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3517890, 0.9488290, 10000.0, 566.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2703380, 0.9607910, 10000.0, 566.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2819800, 0.9595180, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Niv STK-2')
    FP.SetMissionLaunchTime(mission_id, '08:01:00+0m')
    FP.SetMissionDatum(mission_id, 0.2592440, 0.9635880)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3516180, 0.9489890, 10000.0, 566.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2682170, 0.9621660, 10000.0, 566.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2830280, 0.9602780, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Niv AAW2-1')
    FP.AddAircraftToMission(mission_id, 'Niv AAW2-2')
    FP.AddAircraftToMission(mission_id, 'Niv AAW2-3')
    FP.AddAircraftToMission(mission_id, 'Niv AAW2-4')
    FP.AddAircraftToMission(mission_id, 'Niv AAW2-5')
    FP.AddAircraftToMission(mission_id, 'Niv AAW2-6')
    FP.AddAircraftToMission(mission_id, 'Niv AAW2-7')
    FP.AddAircraftToMission(mission_id, 'Niv AAW2-8')
    FP.SetMissionLaunchTime(mission_id, '08:00:10+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2552670,0.9599950,0.2552670,0.9664760,0.2683570,0.9664760,0.2683570,0.9599950,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3493840, 0.9494700, 10000.0, 566.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2683570, 0.9599950, 10000.0, 351.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Niv AAW-1')
    FP.AddAircraftToMission(mission_id, 'Niv AAW-2')
    FP.AddAircraftToMission(mission_id, 'Niv AAW-3')
    FP.AddAircraftToMission(mission_id, 'Niv AAW-4')
    FP.AddAircraftToMission(mission_id, 'Niv AAW-5')
    FP.AddAircraftToMission(mission_id, 'Niv AAW-6')
    FP.SetMissionLaunchTime(mission_id, '08:00:30+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0117318,-0.0239989,0.0057029,-0.0240555,0.0056943,-0.0171032,-0.0117318,-0.0170930,')
    FP.SetMissionPatrolAnchor(mission_id, 'Nivenskoye AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3509650, 0.9480670, 10001.0, 668.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3406880, 0.9478670, 10001.0, 501.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Niv STK-3')
    FP.AddAircraftToMission(mission_id, 'Niv STK-4')
    FP.SetMissionLaunchTime(mission_id, '08:15:00+0m+R1.0')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, 'Standby-ASuW')
    FP.SetMissionPatrolArea(mission_id, '0.2677323,0.9665088,0.2677706,0.9458069,0.2409194,0.9544443,0.2408355,0.9664786,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3491770, 0.9489290, 10000.0, 566.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3070310, 0.9538360, 10000.0, 566.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Niv STK3-1')
    FP.SetMissionLaunchTime(mission_id, '08:05:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2641370, 0.9614320)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3491090, 0.9490490, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2730110, 0.9599970, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2785780, 0.9595210, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Niv STK3-2')
    FP.SetMissionLaunchTime(mission_id, '08:05:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2610930, 0.9636880)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3491430, 0.9493900, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2713270, 0.9618660, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2805520, 0.9604490, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Niv STK3-3')
    FP.SetMissionLaunchTime(mission_id, '08:05:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2574370, 0.9651370)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3491770, 0.9489290, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2640580, 0.9640800, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2761310, 0.9621450, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Niv STK3-4')
    FP.SetMissionLaunchTime(mission_id, '08:05:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2596250, 0.9619680)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3491430, 0.9490490, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2758590, 0.9592820, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2874760, 0.9576910, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Niv STK3-5')
    FP.SetMissionLaunchTime(mission_id, '08:05:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2638630, 0.9621720)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3492460, 0.9490090, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2759970, 0.9601850, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2855500, 0.9586250, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Niv STK3-6')
    FP.SetMissionLaunchTime(mission_id, '08:05:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2581360, 0.9643850)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3492120, 0.9491090, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2692700, 0.9625240, 10000.0, 605.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2802260, 0.9607600, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Nic STK2-1')
    FP.SetMissionLaunchTime(mission_id, '08:10:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2605950, 0.9633080)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3491770, 0.9490890, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2663060, 0.9621560, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2793230, 0.9599760, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Nic STK2-2')
    FP.SetMissionLaunchTime(mission_id, '08:10:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2580820, 0.9632600)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3491330, 0.9488500, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2632230, 0.9623170, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2736700, 0.9607090, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Nic STK2-3')
    FP.SetMissionLaunchTime(mission_id, '08:10:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2622170, 0.9601360)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3490300, 0.9486900, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2655930, 0.9594710, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2777600, 0.9577630, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Nic STK2-4')
    FP.SetMissionLaunchTime(mission_id, '08:10:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2592330, 0.9608620)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3491670, 0.9488910, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2636230, 0.9600950, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2746210, 0.9587560, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Nic STK2-5')
    FP.SetMissionLaunchTime(mission_id, '08:10:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2580790, 0.9612080)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3490980, 0.9487700, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2637300, 0.9603680, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2756630, 0.9587940, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Nic STK2-6')
    FP.SetMissionLaunchTime(mission_id, '08:10:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2564780, 0.9622600)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3490640, 0.9487900, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2639500, 0.9610600, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2729680, 0.9596440, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Daugavpils AB"
    unit.SetPosition(26.389691, 55.560004, 0.0)
    unit.heading = 282.09
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Daugavpils AB", 'Fuel', 2296240)
    SM.AddToUnitMagazine("Daugavpils AB", 'AT-2M', 39)
    SM.AddToUnitMagazine("Daugavpils AB", 'Chaff-1', 983)
    SM.AddToUnitMagazine("Daugavpils AB", 'DICASS (85) Sonobuoy', 97)
    SM.AddToUnitMagazine("Daugavpils AB", 'DICASS (90) Sonobuoy', 37)
    SM.AddToUnitMagazine("Daugavpils AB", 'DIFAR (85) Sonobuoy', 235)
    SM.AddToUnitMagazine("Daugavpils AB", 'DIFAR (90) Sonobuoy', 90)
    SM.AddToUnitMagazine("Daugavpils AB", 'FAB-500', 224)
    SM.AddToUnitMagazine("Daugavpils AB", 'Flare-1', 791)
    SM.AddToUnitMagazine("Daugavpils AB", 'Kh-22M', 49)
    SM.AddToUnitMagazine("Daugavpils AB", 'Kh-22MP', 49)
    SM.AddToUnitMagazine("Daugavpils AB", 'LOFAR (85) Sonobuoy', 97)
    SM.AddToUnitMagazine("Daugavpils AB", 'LOFAR (90) Sonobuoy', 37)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    BB.Write('InvMulti', '1')
    BB.Write('MagTonnage', '35')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'A-50', 'Dau AEW-1', 3)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau AEW-1', '')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'A-50', 'Dau AEW-2', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau AEW-2', '')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'A-50', 'Dau AEW-3', 3)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau AEW-3', '')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'A-50', 'Dau AEW-4', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau AEW-4', '')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-95RT', 'Dau Recon-1', 3)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau Recon-1', '48 Chaff-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-95RT', 'Dau Recon-2', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau Recon-2', '48 Chaff-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-95RT', 'Dau Recon-3', 3)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau Recon-3', '48 Chaff-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-95RT', 'Dau Recon-4', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau Recon-4', '48 Chaff-1;48 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Il-38', 'Dau ASW-1', 2)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASW-1', '17 DICASS (90) Sonobuoy;17 LOFAR (90) Sonobuoy;41 DIFAR (90) Sonobuoy;4 AT-2M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Il-38', 'Dau ASW-2', 2)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASW-2', '17 DICASS (90) Sonobuoy;17 LOFAR (90) Sonobuoy;41 DIFAR (90) Sonobuoy;4 AT-2M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Il-38', 'Dau ASW-3', 2)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASW-3', '17 DICASS (90) Sonobuoy;17 LOFAR (90) Sonobuoy;41 DIFAR (90) Sonobuoy;4 AT-2M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Il-38', 'Dau ASW-4', 2)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASW-4', '17 DICASS (90) Sonobuoy;17 LOFAR (90) Sonobuoy;41 DIFAR (90) Sonobuoy;4 AT-2M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-22ME', 'Dau ASUW-1', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASUW-1', '1 Kh-22M;1 Kh-22MP;30 Flare-1;30 Chaff-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-22ME', 'Dau ASUW-2', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASUW-2', '1 Kh-22M;1 Kh-22MP;30 Flare-1;30 Chaff-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-22ME', 'Dau ASUW-3', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASUW-3', '1 Kh-22M;1 Kh-22MP;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-22ME', 'Dau ASUW-4', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASUW-4', '1 Kh-22M;1 Kh-22MP;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-22ME', 'Dau ASUW-5', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASUW-5', '1 Kh-22M;1 Kh-22MP;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-22ME', 'Dau ASUW-6', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASUW-6', '1 Kh-22M;1 Kh-22MP;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-22ME', 'Dau ASUW-7', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASUW-7', '1 Kh-22M;1 Kh-22MP;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-22ME', 'Dau ASUW-8', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASUW-8', '1 Kh-22M;1 Kh-22MP;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-22ME', 'Dau ASUW-9', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASUW-9', '1 Kh-22M;1 Kh-22MP;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    
    SM.AddUnitToFlightDeck('Daugavpils AB', 'Tu-22ME', 'Dau ASUW-10', 1)
    SM.SetFlightDeckUnitLoadout('Daugavpils AB', 'Dau ASUW-10', '1 Kh-22M;1 Kh-22MP;30 Chaff-1;30 Flare-1;2 Kh-22M;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Dau AEW-1')
    FP.AddAircraftToMission(mission_id, 'Dau AEW-2')
    FP.SetMissionLaunchTime(mission_id, '08:00:05+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0326974,0.0553712,-0.0277923,0.0564223,-0.0268520,0.0520326,-0.0317567,0.0509815,')
    FP.SetMissionPatrolAnchor(mission_id, 'Daugavpils AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.4540160, 0.9698050, 10000.0, 460.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3616780, 0.9541310, 10000.0, 138.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Dau AEW-3')
    FP.AddAircraftToMission(mission_id, 'Dau AEW-4')
    FP.SetMissionLaunchTime(mission_id, '08:00:10+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0254054,0.0513587,0.0214178,0.0505043,0.0223602,0.0462359,0.0263156,0.0471101,')
    FP.SetMissionPatrolAnchor(mission_id, 'Daugavpils AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.4491600, 0.9707260, 10000.0, 460.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3925560, 0.9992390, 10000.0, 138.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Dau Recon-1')
    FP.AddAircraftToMission(mission_id, 'Dau Recon-2')
    FP.SetMissionLaunchTime(mission_id, '08:00:30+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2937379,0.9715630,0.2937489,0.9619120,0.2512694,0.9618521,0.2512299,0.9715630,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4507640, 0.9694110, 10000.0, 482.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.2944830, 0.9665210, 10000.0, 222.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Dau Recon-3')
    FP.AddAircraftToMission(mission_id, 'Dau Recon-4')
    FP.SetMissionLaunchTime(mission_id, '08:00:40+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2558335,0.9584025,0.2558335,0.9504089,0.2965487,0.9504089,0.2965487,0.9584025,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4480950, 0.9686680, 10000.0, 482.0)
    FP.AddMissionWaypointAdvanced(mission_id, 0.2981160, 0.9542520, 10000.0, 222.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Dau ASW-1')
    FP.SetMissionLaunchTime(mission_id, '08:01:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, 'ASW-FW')
    FP.SetMissionPatrolArea(mission_id, '0.3757302,1.0234660,0.3757302,1.0120670,0.3419282,1.0120670,0.3419282,1.0234660,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4492080, 0.9746920, 4000.0, 390.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3762440, 1.0117810, 149.0, 117.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'EngageAll,ActiveSonarOn,ASWPatrolArea')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Dau ASW-2')
    FP.SetMissionLaunchTime(mission_id, '08:01:20+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, 'ASW-FW')
    FP.SetMissionPatrolArea(mission_id, '0.3724590,1.0121644,0.3724159,0.9973395,0.3278002,0.9973565,0.3405014,1.0121644,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4457380, 0.9738030, 4000.0, 390.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3779220, 0.9961070, 149.0, 117.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'EngageAll,ASWPatrolArea,ActiveSonarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Dau ASW-3')
    FP.SetMissionLaunchTime(mission_id, '08:02:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, 'ASW-FW')
    FP.SetMissionPatrolArea(mission_id, '0.3641123,0.9979750,0.3643172,0.9774359,0.3153562,0.9774359,0.3261020,0.9978667,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4492040, 0.9713060, 4000.0, 390.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3702860, 0.9824630, 149.0, 117.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'EngageAll,ASWPatrolArea,ActiveSonarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Dau ASW-4')
    FP.SetMissionLaunchTime(mission_id, '08:02:30+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 1)
    FP.SetMissionType(mission_id, 'ASW-FW')
    FP.SetMissionPatrolArea(mission_id, '0.3347343,0.9775593,0.3347343,0.9587603,0.2749163,0.9587603,0.2749163,0.9775593,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4522100, 0.9697390, 4000.0, 390.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3394740, 0.9684660, 149.0, 117.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'EngageAll,ASWPatrolArea,ActiveSonarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Dau ASUW-1')
    FP.AddAircraftToMission(mission_id, 'Dau ASUW-2')
    FP.AddAircraftToMission(mission_id, 'Dau ASUW-3')
    FP.AddAircraftToMission(mission_id, 'Dau ASUW-4')
    FP.AddAircraftToMission(mission_id, 'Dau ASUW-5')
    FP.AddAircraftToMission(mission_id, 'Dau ASUW-6')
    FP.AddAircraftToMission(mission_id, 'Dau ASUW-7')
    FP.AddAircraftToMission(mission_id, 'Dau ASUW-8')
    FP.AddAircraftToMission(mission_id, 'Dau ASUW-9')
    FP.AddAircraftToMission(mission_id, 'Dau ASUW-10')
    FP.SetMissionLaunchTime(mission_id, '08:20:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 10)
    FP.SetMissionType(mission_id, 'Standby-ASuW')
    FP.SetMissionPatrolArea(mission_id, '0.2547324,0.9666340,0.2547324,0.9515680,0.2160554,0.9515680,0.2160554,0.9666340,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4408860, 0.9697060, 10000.0, 545.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'WaitForGroup,EngageAll')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3236650, 0.9663830, 10000.0, 545.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RadarOn')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Krustpils AB"
    unit.SetPosition(25.530426, 56.319689, 188.6)
    unit.heading = 275.19
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Krustpils AB", 'Fuel', 3000000)
    SM.AddToUnitMagazine("Krustpils AB", '1150 Liter Tank', 48)
    SM.AddToUnitMagazine("Krustpils AB", '1520 Liter Tank', 24)
    SM.AddToUnitMagazine("Krustpils AB", '2000 liter tank', 24)
    SM.AddToUnitMagazine("Krustpils AB", '23mm AM-23', 650)
    SM.AddToUnitMagazine("Krustpils AB", '30mm NR-30 HEI', 3468)
    SM.AddToUnitMagazine("Krustpils AB", 'Chaff-1', 21677)
    SM.AddToUnitMagazine("Krustpils AB", 'FAB-100', 390)
    SM.AddToUnitMagazine("Krustpils AB", 'FAB-250', 390)
    SM.AddToUnitMagazine("Krustpils AB", 'FAB-500', 225)
    SM.AddToUnitMagazine("Krustpils AB", 'Flare-1', 21677)
    SM.AddToUnitMagazine("Krustpils AB", 'KAB-500KRU', 43)
    SM.AddToUnitMagazine("Krustpils AB", 'KAB-500Kr', 65)
    SM.AddToUnitMagazine("Krustpils AB", 'KAB-500R', 32)
    SM.AddToUnitMagazine("Krustpils AB", 'Kh-29T', 69)
    SM.AddToUnitMagazine("Krustpils AB", 'Kh-31P', 109)
    SM.AddToUnitMagazine("Krustpils AB", 'R-27R', 635)
    SM.AddToUnitMagazine("Krustpils AB", 'R-27RE', 125)
    SM.AddToUnitMagazine("Krustpils AB", 'R-27T', 346)
    SM.AddToUnitMagazine("Krustpils AB", 'R-27TE', 125)
    SM.AddToUnitMagazine("Krustpils AB", 'R-33', 423)
    SM.AddToUnitMagazine("Krustpils AB", 'R-60M', 646)
    SM.AddToUnitMagazine("Krustpils AB", 'R-60MK', 646)
    SM.AddToUnitMagazine("Krustpils AB", 'R-73', 650)
    SM.AddToUnitMagazine("Krustpils AB", 'R-77', 582)
    SM.AddToUnitMagazine("Krustpils AB", 'R-77T', 551)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    BB.Write('InvMulti', '1')
    BB.Write('MagTonnage', '35')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-1', 3)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-1', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-2', 3)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-2', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-3', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-3', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-4', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-4', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-5', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-5', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-6', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-6', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-7', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-7', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-8', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-8', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-9', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-9', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-10', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-10', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-11', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-11', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-31', 'Krust AAW-12', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW-12', '6 23mm AM-23;4 R-33;4 R-33;2 2000 liter tank;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-1', 3)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-1', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-2', 3)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-2', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-3', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-3', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-4', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-4', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-5', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-5', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-6', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-6', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-7', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-7', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-8', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-8', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-9', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-9', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-10', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-10', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-11', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-11', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust AAW2-12', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW2-12', '1 1520 Liter Tank;2 R-77;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'Su-27', 'Krust AAW3-1', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW3-1', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'Su-27', 'Krust AAW3-2', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW3-2', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'Su-27', 'Krust AAW3-3', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW3-3', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'Su-27', 'Krust AAW3-4', 1)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust AAW3-4', '4 R-27R;2 R-77;4 R-27R;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-1', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-1', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-2', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-2', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-3', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-3', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-4', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-4', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-5', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-5', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-6', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-6', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-7', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-7', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-8', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-8', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-9', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-9', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-10', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-10', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-11', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-11', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Krustpils AB', 'MiG-29SM', 'Krust STK-12', 2)
    SM.SetFlightDeckUnitLoadout('Krustpils AB', 'Krust STK-12', '1 1520 Liter Tank;6 FAB-250;2 R-77;2 R-77;0 Empty;30 Chaff-1;30 Chaff-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Krust STK-1')
    FP.AddAircraftToMission(mission_id, 'Krust STK-2')
    FP.AddAircraftToMission(mission_id, 'Krust STK-3')
    FP.AddAircraftToMission(mission_id, 'Krust STK-4')
    FP.AddAircraftToMission(mission_id, 'Krust STK-5')
    FP.AddAircraftToMission(mission_id, 'Krust STK-6')
    FP.AddAircraftToMission(mission_id, 'Krust STK-7')
    FP.AddAircraftToMission(mission_id, 'Krust STK-8')
    FP.AddAircraftToMission(mission_id, 'Krust STK-9')
    FP.AddAircraftToMission(mission_id, 'Krust STK-10')
    FP.AddAircraftToMission(mission_id, 'Krust STK-11')
    FP.AddAircraftToMission(mission_id, 'Krust STK-12')
    FP.SetMissionLaunchTime(mission_id, '08:05:00+0m+R1.5')
    FP.SetMissionDatum(mission_id, 0.2583740, 0.9608780)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 12)
    FP.SetMissionType(mission_id, '')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4277590, 0.9831390, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2617890, 0.9612360, 8000.0, 490.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'GroundStrike,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2697860, 0.9621550, 6000.0, 300.0)
    FP.SetMissionWaypointTasks(mission_id, 2, 'Land')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-1')
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-2')
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-3')
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-4')
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-5')
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-6')
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-7')
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-8')
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-9')
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-10')
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-11')
    FP.AddAircraftToMission(mission_id, 'Krust AAW2-12')
    FP.SetMissionLaunchTime(mission_id, '08:01:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.0185832,0.0553933,0.0543959,0.0587403,0.0551865,0.0508275,0.0192043,0.0476014,')
    FP.SetMissionPatrolAnchor(mission_id, 'Krustpils AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.4357470, 0.9845990, 10000.0, 673.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3719270, 1.0089190, 10000.0, 673.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Krust AAW-1')
    FP.AddAircraftToMission(mission_id, 'Krust AAW-2')
    FP.AddAircraftToMission(mission_id, 'Krust AAW-3')
    FP.AddAircraftToMission(mission_id, 'Krust AAW-4')
    FP.AddAircraftToMission(mission_id, 'Krust AAW-5')
    FP.AddAircraftToMission(mission_id, 'Krust AAW-6')
    FP.AddAircraftToMission(mission_id, 'Krust AAW-7')
    FP.AddAircraftToMission(mission_id, 'Krust AAW-8')
    FP.AddAircraftToMission(mission_id, 'Krust AAW-9')
    FP.AddAircraftToMission(mission_id, 'Krust AAW-10')
    FP.AddAircraftToMission(mission_id, 'Krust AAW-11')
    FP.AddAircraftToMission(mission_id, 'Krust AAW-12')
    FP.SetMissionLaunchTime(mission_id, '08:00:10+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0401427,0.0936976,-0.0142802,0.0960487,-0.0136055,0.0886271,-0.0394680,0.0862760,')
    FP.SetMissionPatrolAnchor(mission_id, 'Krustpils AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.4354210, 0.9825410, 10000.0, 638.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2989600, 0.9672190, 10000.0, 389.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Krust AAW3-1')
    FP.AddAircraftToMission(mission_id, 'Krust AAW3-2')
    FP.AddAircraftToMission(mission_id, 'Krust AAW3-3')
    FP.AddAircraftToMission(mission_id, 'Krust AAW3-4')
    FP.SetMissionLaunchTime(mission_id, '08:10:00+0m')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.2636428,0.9772360,0.2636428,0.9495110,0.2793268,0.9495110,0.2793268,0.9772360,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.4312040, 0.9832340, 10000.0, 566.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.2870090, 0.9642110, 10000.0, 494.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RadarOn')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Hq"
    unit.SetPosition(20.476538, 54.717069, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Small Building'
    unit.unitName = "Storage"
    unit.SetPosition(20.461698, 54.737466, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker 2"
    unit.SetPosition(20.500430, 54.737466, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Communications Station'
    unit.unitName = "Comm Station"
    unit.SetPosition(20.476996, 54.687504, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fuel Tanks'
    unit.unitName = "Fuel Tank"
    unit.SetPosition(20.453619, 54.767775, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker 3"
    unit.SetPosition(20.443134, 54.666075, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Barracks"
    unit.SetPosition(20.420560, 54.749154, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Barracks 2"
    unit.SetPosition(20.547183, 54.705266, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Barracks 1"
    unit.SetPosition(20.520598, 54.761244, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker 1"
    unit.SetPosition(20.547985, 54.760327, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877M Paltus'
    unit.unitName = "B-471"
    unit.SetPosition(19.987232, 57.644253, -72.6)
    unit.heading = 90.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M32M Strela 3', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 4, 'SET-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 5, '53-65M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 6, '53-65M', 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("B-471", 'SET-65M', 12)
    SM.AddToUnitMagazine("B-471", '53-65M', 6)
    SM.AddToUnitMagazine("B-471", '9M32M Strela 3', 8)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.338144, 0.985592, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1241.1 Molniya'
    unit.unitName = "R-69"
    unit.SetPosition(20.126460, 55.111092, 0.0)
    unit.heading = -95.71
    unit.speed = 15.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M32 Strela 2', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("R-69", '76.2mm OS-62 FRAG', 152)
    SM.AddToUnitMagazine("R-69", '9M32 Strela 2', 16)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.266633, 0.957733, 0.000000, 15.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12341 Ovod-1'
    unit.unitName = "Burun"
    UI = SM.GetUnitInterface('MPK-69')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0375
    lat_deg = 57.296*leader_track.Lat + 0.0443
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 4.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('MPK-69')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(4.987, 0.500, 0.465, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12341 Ovod-1'
    unit.unitName = "Veter"
    UI = SM.GetUnitInterface('MPK-69')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0373
    lat_deg = 57.296*leader_track.Lat + 0.0320
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 5.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('MPK-69')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(4.036, 0.500, -0.686, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12341 Ovod-1'
    unit.unitName = "Mirazh"
    UI = SM.GetUnitInterface('MPK-69')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1070
    lat_deg = 57.296*leader_track.Lat + 0.0685
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 5.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'P-120 Malakhit', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 4, '76.2mm OS-62 FRAG', 152)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('MPK-69')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(10.028, 0.722, -0.777, 0.082)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 205 Tsunami (Poland)'
    unit.unitName = "Dziwnow"
    UI = SM.GetUnitInterface('Swinoujscie')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1241
    lat_deg = 57.296*leader_track.Lat + 0.1705
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 5.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20 Rubezh', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Swinoujscie')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(20.176, 1.082, -0.410, 0.071)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 205 Tsunami (Poland)'
    unit.unitName = "Kolobrzeg"
    UI = SM.GetUnitInterface('Swinoujscie')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2142
    lat_deg = 57.296*leader_track.Lat + 0.0977
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 5.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20 Rubezh', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Swinoujscie')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(17.354, 1.004, -0.928, 0.071)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 205 Tsunami (Poland)'
    unit.unitName = "Gdynia"
    UI = SM.GetUnitInterface('Swinoujscie')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1602
    lat_deg = 57.296*leader_track.Lat + 0.0354
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 4.7
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20 Rubezh', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Swinoujscie')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(11.009, 1.010, -1.246, 0.103)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 205 Tsunami (Poland)'
    unit.unitName = "Wladyslawowo"
    UI = SM.GetUnitInterface('Swinoujscie')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0339
    lat_deg = 57.296*leader_track.Lat + 0.1012
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 90.00
    unit.speed = 4.7
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-20 Rubezh', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Swinoujscie')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(11.000, 1.014, -0.214, 0.129)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 266M Akvamarin-M'
    unit.unitName = "Svyazist"
    UI = SM.GetUnitInterface('Reshitelny')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1562
    lat_deg = 57.296*leader_track.Lat + -0.1577
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -139.40
    unit.speed = 14.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 1, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 6, '9M32 Strela 2', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Svyazist", '25mm APDS', 8000)
    SM.AddToUnitMagazine("Svyazist", '30mm OF-83 HE-FRAG', 4000)
    SM.AddToUnitMagazine("Svyazist", '30mm OF-84 HE-FRAG AK-630M', 472)
    SM.AddToUnitMagazine("Svyazist", '9M32 Strela 2', 32)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Reshitelny')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(20.235, 0.958, -2.672, 0.052)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 266M Akvamarin-M'
    unit.unitName = "Semen Roshal'"
    UI = SM.GetUnitInterface('Reshitelny')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2616
    lat_deg = 57.296*leader_track.Lat + -0.1185
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -135.00
    unit.speed = 14.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 1, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 6, '9M32 Strela 2', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Semen Roshal'", '25mm APDS', 8000)
    SM.AddToUnitMagazine("Semen Roshal'", '30mm OF-83 HE-FRAG', 4000)
    SM.AddToUnitMagazine("Semen Roshal'", '30mm OF-84 HE-FRAG AK-630M', 472)
    SM.AddToUnitMagazine("Semen Roshal'", '9M32 Strela 2', 32)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Reshitelny')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(20.426, 0.933, -2.304, 0.039)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 266M Akvamarin-M'
    unit.unitName = "Kontr-Admiral Khoroshin"
    UI = SM.GetUnitInterface('Reshitelny')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.3349
    lat_deg = 57.296*leader_track.Lat + -0.0794
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -135.00
    unit.speed = 14.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 1, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 6, '9M32 Strela 2', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Kontr-Admiral Khoroshin", '25mm APDS', 8000)
    SM.AddToUnitMagazine("Kontr-Admiral Khoroshin", '30mm OF-83 HE-FRAG', 4000)
    SM.AddToUnitMagazine("Kontr-Admiral Khoroshin", '30mm OF-84 HE-FRAG AK-630M', 472)
    SM.AddToUnitMagazine("Kontr-Admiral Khoroshin", '9M32 Strela 2', 32)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Reshitelny')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(21.489, 0.719, -2.017, 0.033)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 11351 Nerey'
    unit.unitName = "Pskov"
    UI = SM.GetUnitInterface('Reshitelny')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1392
    lat_deg = 57.296*leader_track.Lat + -0.1410
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -143.97
    unit.speed = 15.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M33M', 20)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Pskov", 'Fuel', 22950)
    SM.AddToUnitMagazine("Pskov", 'AT-1', 18)
    SM.AddToUnitMagazine("Pskov", 'DICASS (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("Pskov", 'LOFAR (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("Pskov", 'DIFAR (85) Sonobuoy', 294)
    SM.AddToUnitMagazine("Pskov", '30mm OF-83 HE-FRAG', 4000)
    SM.AddToUnitMagazine("Pskov", '53-65M', 8)
    SM.AddToUnitMagazine("Pskov", '100mm OF-58 FRAG', 350)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Reshitelny')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(18.120, 1.021, -2.677, 0.082)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Pskov', 'Ka-27A', 'Nerey Ka-27 201', 1)
    SM.SetFlightDeckUnitLoadout('Pskov', 'Nerey Ka-27 201', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 11351 Nerey'
    unit.unitName = "Pogranvoysk"
    UI = SM.GetUnitInterface('Reshitelny')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2435
    lat_deg = 57.296*leader_track.Lat + -0.1099
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -144.46
    unit.speed = 15.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M33M', 20)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Pogranvoysk", 'Fuel', 22950)
    SM.AddToUnitMagazine("Pogranvoysk", 'AT-1', 18)
    SM.AddToUnitMagazine("Pogranvoysk", 'DICASS (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("Pogranvoysk", 'LOFAR (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("Pogranvoysk", 'DIFAR (85) Sonobuoy', 294)
    SM.AddToUnitMagazine("Pogranvoysk", '30mm OF-83 HE-FRAG', 4000)
    SM.AddToUnitMagazine("Pogranvoysk", '53-65M', 8)
    SM.AddToUnitMagazine("Pogranvoysk", '100mm OF-58 FRAG', 350)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Reshitelny')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(19.013, 1.084, -2.301, 0.047)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Pogranvoysk', 'Ka-27A', 'Nerey Ka-27 101', 1)
    SM.SetFlightDeckUnitLoadout('Pogranvoysk', 'Nerey Ka-27 101', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 11351 Nerey'
    unit.unitName = "Orel"
    UI = SM.GetUnitInterface('Reshitelny')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.3149
    lat_deg = 57.296*leader_track.Lat + -0.0691
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -135.00
    unit.speed = 14.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 1, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 3, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 4, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M33M', 20)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Orel", 'Fuel', 22950)
    SM.AddToUnitMagazine("Orel", 'AT-1', 18)
    SM.AddToUnitMagazine("Orel", 'DICASS (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("Orel", 'LOFAR (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("Orel", 'DIFAR (85) Sonobuoy', 294)
    SM.AddToUnitMagazine("Orel", '30mm OF-83 HE-FRAG', 4000)
    SM.AddToUnitMagazine("Orel", '53-65M', 8)
    SM.AddToUnitMagazine("Orel", '100mm OF-58 FRAG', 350)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Reshitelny')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(19.968, 1.287, -1.992, 0.083)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Orel', 'Ka-27A', 'Nerey Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Orel', 'Nerey Ka-27 1', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 956 Sarych'
    unit.unitName = "Admiral Ushakov"
    UI = SM.GetUnitInterface('Reshitelny')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1310
    lat_deg = 57.296*leader_track.Lat + -0.0123
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -132.71
    unit.speed = 14.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 22)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 22)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '3M80 Moskit', 8)
    SM.SetUnitLauncherItem(unit.unitName, 7, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 8, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 10, '53-65M', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Admiral Ushakov", 'Fuel', 45900)
    SM.AddToUnitMagazine("Admiral Ushakov", 'AT-1', 22)
    SM.AddToUnitMagazine("Admiral Ushakov", 'DICASS (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Ushakov", 'LOFAR (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Ushakov", 'DIFAR (85) Sonobuoy', 378)
    SM.AddToUnitMagazine("Admiral Ushakov", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Admiral Ushakov", '130mm F-44 HE', 1000)
    SM.AddToUnitMagazine("Admiral Ushakov", '53-65M', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Reshitelny')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(7.913, 1.234, -1.811, 0.086)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Admiral Ushakov', 'Ka-27A', 'Sarych Ka-27 301', 1)
    SM.SetFlightDeckUnitLoadout('Admiral Ushakov', 'Sarych Ka-27 301', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1124ME Albatros'
    unit.unitName = "MPK-190"
    UI = SM.GetUnitInterface('Reshitelny')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1401
    lat_deg = 57.296*leader_track.Lat + -0.0739
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -127.87
    unit.speed = 15.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M33M', 20)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("MPK-190", '30mm OF-84 HE-FRAG AK-630M', 236)
    SM.AddToUnitMagazine("MPK-190", '53-65M', 4)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Reshitelny')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(11.976, 1.704, -2.387, 0.125)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1155 Fregat'
    unit.unitName = "Vice Admiral Kulakov"
    UI = SM.GetUnitInterface('Reshitelny')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0584
    lat_deg = 57.296*leader_track.Lat + -0.0692
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -130.24
    unit.speed = 14.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M330 Kinzhal', 64)
    SM.SetUnitLauncherItem(unit.unitName, 1, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 2, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'RPK-3 Metel', 8)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Vice Admiral Kulakov", 'Fuel', 45900)
    SM.AddToUnitMagazine("Vice Admiral Kulakov", 'AT-1', 22)
    SM.AddToUnitMagazine("Vice Admiral Kulakov", 'DICASS (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Vice Admiral Kulakov", 'LOFAR (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Vice Admiral Kulakov", 'DIFAR (85) Sonobuoy', 378)
    SM.AddToUnitMagazine("Vice Admiral Kulakov", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Vice Admiral Kulakov", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Vice Admiral Kulakov", '53-65M', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Reshitelny')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(8.860, 1.443, -2.744, 0.077)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Vice Admiral Kulakov', 'Ka-27A', 'Fregat Ka-27 101', 1)
    SM.SetFlightDeckUnitLoadout('Vice Admiral Kulakov', 'Fregat Ka-27 101', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 266M Akvamarin-M'
    unit.unitName = "Zaryad"
    UI = SM.GetUnitInterface('Marshal Ustinov')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2748
    lat_deg = 57.296*leader_track.Lat + -0.0738
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -135.00
    unit.speed = 14.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 1, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-83 HE-FRAG', 250)
    SM.SetUnitLauncherItem(unit.unitName, 6, '9M32 Strela 2', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Zaryad", '25mm APDS', 8000)
    SM.AddToUnitMagazine("Zaryad", '30mm OF-83 HE-FRAG', 4000)
    SM.AddToUnitMagazine("Zaryad", '30mm OF-84 HE-FRAG AK-630M', 472)
    SM.AddToUnitMagazine("Zaryad", '9M32 Strela 2', 32)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Marshal Ustinov')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(17.878, 0.911, -2.078, 0.067)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12660 Rubin'
    unit.unitName = "Zheleznyakov"
    UI = SM.GetUnitInterface('Marshal Ustinov')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1296
    lat_deg = 57.296*leader_track.Lat + -0.1276
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -131.63
    unit.speed = 14.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M32 Strela 2', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Zheleznyakov", '30mm OF-84 HE-FRAG AK-630M', 236)
    SM.AddToUnitMagazine("Zheleznyakov", '9M32 Strela 2', 32)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Marshal Ustinov')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(16.425, 0.885, -2.672, 0.054)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 12660 Rubin'
    unit.unitName = "Gumanenko"
    UI = SM.GetUnitInterface('Marshal Ustinov')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.3256
    lat_deg = 57.296*leader_track.Lat + -0.0175
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -125.54
    unit.speed = 14.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M32 Strela 2', 16)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Gumanenko", '30mm OF-84 HE-FRAG AK-630M', 236)
    SM.AddToUnitMagazine("Gumanenko", '9M32 Strela 2', 32)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Marshal Ustinov')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(18.694, 0.955, -1.699, 0.045)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1134B Berkut B'
    unit.unitName = "Petropavlovsk"
    UI = SM.GetUnitInterface('Marshal Ustinov')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2953
    lat_deg = 57.296*leader_track.Lat + -0.0153
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -135.00
    unit.speed = 14.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 8, '76.2mm OS-62 FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 9, '76.2mm OS-62 FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'RPK-3 Metel', 8)
    SM.SetUnitLauncherItem(unit.unitName, 11, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 12, '53-65M', 5)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Petropavlovsk", 'Fuel', 45900)
    SM.AddToUnitMagazine("Petropavlovsk", 'AT-1', 33)
    SM.AddToUnitMagazine("Petropavlovsk", 'DICASS (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("Petropavlovsk", 'LOFAR (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("Petropavlovsk", 'DIFAR (85) Sonobuoy', 567)
    SM.AddToUnitMagazine("Petropavlovsk", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Petropavlovsk", '53-65M', 20)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Marshal Ustinov')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(16.989, 0.865, -1.700, 0.047)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Petropavlovsk', 'Ka-27A', 'Berkut-B Ka-27 101', 1)
    SM.SetFlightDeckUnitLoadout('Petropavlovsk', 'Berkut-B Ka-27 101', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1155 Fregat'
    unit.unitName = "Admiral Levchenko"
    UI = SM.GetUnitInterface('Marshal Ustinov')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.2563
    lat_deg = 57.296*leader_track.Lat + -0.0644
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -135.00
    unit.speed = 15.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M330 Kinzhal', 64)
    SM.SetUnitLauncherItem(unit.unitName, 1, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 2, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'RPK-3 Metel', 8)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Admiral Levchenko", 'AT-1', 22)
    SM.AddToUnitMagazine("Admiral Levchenko", 'DICASS (85) Sonobuoy', 134)
    SM.AddToUnitMagazine("Admiral Levchenko", 'DIFAR (85) Sonobuoy', 383)
    SM.AddToUnitMagazine("Admiral Levchenko", 'Fuel', 45900)
    SM.AddToUnitMagazine("Admiral Levchenko", 'LOFAR (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Admiral Levchenko", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Admiral Levchenko", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Admiral Levchenko", '53-65M', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    BB.Write('InvMulti', '1')
    leader_id = UI.LookupFriendlyId('Marshal Ustinov')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(16.487, 1.060, -2.053, 0.069)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Admiral Levchenko', 'Ka-27A', 'Fregat Ka-27 201', 1)
    SM.SetFlightDeckUnitLoadout('Admiral Levchenko', 'Fregat Ka-27 201', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 APR-2E;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1134B Berkut B'
    unit.unitName = "Kerch"
    UI = SM.GetUnitInterface('Marshal Ustinov')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0573
    lat_deg = 57.296*leader_track.Lat + -0.0509
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -135.00
    unit.speed = 15.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M33M', 20)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'V-611', 36)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 8, '76.2mm OS-62 FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 9, '76.2mm OS-62 FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'RPK-3 Metel', 8)
    SM.SetUnitLauncherItem(unit.unitName, 11, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 12, '53-65M', 5)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Kerch", 'Fuel', 45900)
    SM.AddToUnitMagazine("Kerch", 'AT-1', 33)
    SM.AddToUnitMagazine("Kerch", 'DICASS (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("Kerch", 'LOFAR (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("Kerch", 'DIFAR (85) Sonobuoy', 567)
    SM.AddToUnitMagazine("Kerch", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Kerch", '53-65M', 20)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Marshal Ustinov')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(7.019, 0.631, -2.639, 0.112)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Kerch', 'Ka-27A', 'Berkut-B Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Kerch', 'Berkut-B Ka-27 1', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 956 Sarych'
    unit.unitName = "Sovremenny"
    UI = SM.GetUnitInterface('Marshal Ustinov')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1124
    lat_deg = 57.296*leader_track.Lat + -0.1174
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -135.00
    unit.speed = 14.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 22)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 22)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '3M80 Moskit', 8)
    SM.SetUnitLauncherItem(unit.unitName, 7, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 8, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 10, '53-65M', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Sovremenny", 'Fuel', 45900)
    SM.AddToUnitMagazine("Sovremenny", 'AT-1', 22)
    SM.AddToUnitMagazine("Sovremenny", 'DICASS (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Sovremenny", 'LOFAR (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Sovremenny", 'DIFAR (85) Sonobuoy', 378)
    SM.AddToUnitMagazine("Sovremenny", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Sovremenny", '130mm F-44 HE', 1000)
    SM.AddToUnitMagazine("Sovremenny", '53-65M', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Marshal Ustinov')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(14.992, 0.719, -2.695, 0.058)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Sovremenny', 'Ka-27A', 'Sarych Ka-27 201', 1)
    SM.SetFlightDeckUnitLoadout('Sovremenny', 'Sarych Ka-27 201', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 956 Sarych'
    unit.unitName = "Bespokoiny"
    UI = SM.GetUnitInterface('Marshal Ustinov')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1218
    lat_deg = 57.296*leader_track.Lat + -0.0279
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -140.19
    unit.speed = 15.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 22)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 22)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '3M80 Moskit', 8)
    SM.SetUnitLauncherItem(unit.unitName, 7, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 8, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 10, '53-65M', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Bespokoiny", 'Fuel', 45900)
    SM.AddToUnitMagazine("Bespokoiny", 'AT-1', 22)
    SM.AddToUnitMagazine("Bespokoiny", 'DICASS (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Bespokoiny", 'LOFAR (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Bespokoiny", 'DIFAR (85) Sonobuoy', 378)
    SM.AddToUnitMagazine("Bespokoiny", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Bespokoiny", '130mm F-44 HE', 1000)
    SM.AddToUnitMagazine("Bespokoiny", '53-65M', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Marshal Ustinov')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(7.936, 1.433, -2.042, 0.176)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Bespokoiny', 'Ka-27A', 'Sarych Ka-27 101', 1)
    SM.SetFlightDeckUnitLoadout('Bespokoiny', 'Sarych Ka-27 101', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1134A Berkut'
    unit.unitName = "Vladivostock"
    UI = SM.GetUnitInterface('Marshal Ustinov')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0814
    lat_deg = 57.296*leader_track.Lat + 0.0187
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -135.00
    unit.speed = 14.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'V-611', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'V-611', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RPK-3 Metel', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 8, '57mm Tracer-FRAG', 200)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 5)
    SM.SetUnitLauncherItem(unit.unitName, 10, '53-65M', 5)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Vladivostock", 'Fuel', 45900)
    SM.AddToUnitMagazine("Vladivostock", 'AT-1', 33)
    SM.AddToUnitMagazine("Vladivostock", 'DICASS (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("Vladivostock", 'LOFAR (85) Sonobuoy', 203)
    SM.AddToUnitMagazine("Vladivostock", 'DIFAR (85) Sonobuoy', 567)
    SM.AddToUnitMagazine("Vladivostock", '53-65M', 20)
    SM.AddToUnitMagazine("Vladivostock", '57mm Tracer-FRAG', 4000)
    SM.AddToUnitMagazine("Vladivostock", 'V-611', 44)
    SM.AddToUnitMagazine("Vladivostock", '30mm OF-84 HE-FRAG AK-630M', 944)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('Marshal Ustinov')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(5.031, 0.788, -1.243, 0.213)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('Vladivostock', 'Ka-27A', 'Berkut-A Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Vladivostock', 'Berkut-A Ka-27 1', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135M Burevestnik-M'
    unit.unitName = "Razitelnyy"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0850
    lat_deg = 57.296*leader_track.Lat + -0.0075
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -135.00
    unit.speed = 15.3
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
    SM.AddToUnitMagazine("Razitelnyy", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Razitelnyy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(4.975, 0.488, 0.305, 0.118)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 11540 Yastreb'
    unit.unitName = "Nepristupny"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0248
    lat_deg = 57.296*leader_track.Lat + -0.0008
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -140.19
    unit.speed = 15.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 3)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-65M', 3)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 6, '9M311 Kashtan', 8)
    SM.SetUnitLauncherItem(unit.unitName, 7, '9M330 Kinzhal', 32)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Nepristupny", 'Fuel', 22950)
    SM.AddToUnitMagazine("Nepristupny", 'AT-1', 18)
    SM.AddToUnitMagazine("Nepristupny", 'DICASS (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("Nepristupny", 'LOFAR (85) Sonobuoy', 105)
    SM.AddToUnitMagazine("Nepristupny", 'DIFAR (85) Sonobuoy', 294)
    SM.AddToUnitMagazine("Nepristupny", '30mm OF-84 HE-FRAG AK-630M', 472)
    SM.AddToUnitMagazine("Nepristupny", '9M311 Kashtan', 48)
    SM.AddToUnitMagazine("Nepristupny", '100mm OF-58 FRAG', 350)
    SM.AddToUnitMagazine("Nepristupny", '53-65M', 12)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(1.517, 0.241, 0.315, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Nepristupny', 'Ka-27A', 'Neustrashimiy Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Nepristupny', 'Neustrashimiy Ka-27 1', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1124ME Albatros'
    unit.unitName = "MPK-107 Irkutskiy komsomolets"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0726
    lat_deg = 57.296*leader_track.Lat + -0.0229
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -137.49
    unit.speed = 15.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 1, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 3, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M33M', 20)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("MPK-107 Irkutskiy komsomolets", '30mm OF-84 HE-FRAG AK-630M', 236)
    SM.AddToUnitMagazine("MPK-107 Irkutskiy komsomolets", '53-65M', 4)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(4.990, 0.439, -0.066, 0.092)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135 Burevestnik'
    unit.unitName = "Druzhnyy"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0411
    lat_deg = 57.296*leader_track.Lat + -0.0264
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -129.29
    unit.speed = 14.5
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
    SM.AddToUnitMagazine("Druzhnyy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(3.963, 0.371, -0.403, 0.115)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135 Burevestnik'
    unit.unitName = "Ladnyy"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0639
    lat_deg = 57.296*leader_track.Lat + -0.0135
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -132.88
    unit.speed = 15.0
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
    SM.AddToUnitMagazine("Ladnyy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(4.040, 0.438, 0.080, 0.117)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1135 Burevestnik'
    unit.unitName = "Bditelnyy"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0422
    lat_deg = 57.296*leader_track.Lat + -0.0374
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -140.71
    unit.speed = 14.5
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
    SM.AddToUnitMagazine("Bditelnyy", '53-65M', 8)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(5.018, 0.370, -0.541, 0.113)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 956 Sarych'
    unit.unitName = "Nastoychivy"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0048
    lat_deg = 57.296*leader_track.Lat + -0.0158
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -145.49
    unit.speed = 15.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 22)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 22)
    SM.SetUnitLauncherItem(unit.unitName, 2, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '3M80 Moskit', 8)
    SM.SetUnitLauncherItem(unit.unitName, 7, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 8, '130mm F-44 HE', 100)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 2)
    SM.SetUnitLauncherItem(unit.unitName, 10, '53-65M', 2)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Nastoychivy", 'Fuel', 45900)
    SM.AddToUnitMagazine("Nastoychivy", 'AT-1', 22)
    SM.AddToUnitMagazine("Nastoychivy", 'DICASS (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Nastoychivy", 'LOFAR (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Nastoychivy", 'DIFAR (85) Sonobuoy', 378)
    SM.AddToUnitMagazine("Nastoychivy", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Nastoychivy", '130mm F-44 HE', 1000)
    SM.AddToUnitMagazine("Nastoychivy", '53-65M', 12)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(2.003, 0.316, -0.880, 0.186)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Nastoychivy', 'Ka-27A', 'Sarych Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Nastoychivy', 'Sarych Ka-27 1', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1155 Fregat'
    unit.unitName = "Udaloy"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0325
    lat_deg = 57.296*leader_track.Lat + -0.0130
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -144.46
    unit.speed = 14.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M330 Kinzhal', 64)
    SM.SetUnitLauncherItem(unit.unitName, 1, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 2, '100mm OF-58 FRAG', 46)
    SM.SetUnitLauncherItem(unit.unitName, 3, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 6, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 7, 'RPK-3 Metel', 8)
    SM.SetUnitLauncherItem(unit.unitName, 8, '53-65M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, '53-65M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Udaloy", 'Fuel', 45900)
    SM.AddToUnitMagazine("Udaloy", 'AT-1', 22)
    SM.AddToUnitMagazine("Udaloy", 'DICASS (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Udaloy", 'LOFAR (85) Sonobuoy', 135)
    SM.AddToUnitMagazine("Udaloy", 'DIFAR (85) Sonobuoy', 378)
    SM.AddToUnitMagazine("Udaloy", '30mm OF-84 HE-FRAG AK-630M', 944)
    SM.AddToUnitMagazine("Udaloy", '100mm OF-58 FRAG', 700)
    SM.AddToUnitMagazine("Udaloy", '53-65M', 24)
    UI.AddTask('EngageAll', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(2.529, 0.323, -0.204, 0.131)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    SM.AddUnitToFlightDeck('Udaloy', 'Ka-27A', 'Fregat Ka-27 1', 1)
    SM.SetFlightDeckUnitLoadout('Udaloy', 'Fregat Ka-27 1', '5 DICASS (85) Sonobuoy;5 LOFAR (85) Sonobuoy;14 DIFAR (85) Sonobuoy;2 AT-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Freighter"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0095
    lat_deg = 57.296*leader_track.Lat + -0.0050
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -131.99
    unit.speed = 14.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(0.976, 0.316, -0.398, 0.315)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'General Cargo'
    unit.unitName = "Cargo"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0145
    lat_deg = 57.296*leader_track.Lat + 0.0051
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -131.19
    unit.speed = 14.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(0.992, 0.412, 0.913, 0.469)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "BDK-77"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0185
    lat_deg = 57.296*leader_track.Lat + 0.0052
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -140.71
    unit.speed = 14.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("BDK-77", '9M32 Strela 2', 24)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(2)
    UI.SetFormationPosition(1.048, 0.308, 3.319, 0.314)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "BDK-13"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0156
    lat_deg = 57.296*leader_track.Lat + -0.0035
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -141.34
    unit.speed = 15.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("BDK-13", '9M32 Strela 2', 24)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(1.006, 0.452, 4.309, 0.333)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1171 Tapir'
    unit.unitName = "BDK-10"
    UI = SM.GetUnitInterface('BDK-101 Oslyabya')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0001
    lat_deg = 57.296*leader_track.Lat + 0.0110
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -122.47
    unit.speed = 15.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M32 Strela 2', 12)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("BDK-10", '9M32 Strela 2', 24)
    UI.AddTask('MissileWarning', 3.000000, 3)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('BDK-101 Oslyabya')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(1.009, 0.293, 2.028, 0.401)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1241.1 Molniya'
    unit.unitName = "R255 Kirovskiy Komsomolets"
    UI = SM.GetUnitInterface('R-69')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.1222
    lat_deg = 57.296*leader_track.Lat + -0.0054
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -95.71
    unit.speed = 15.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M32 Strela 2', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("R255 Kirovskiy Komsomolets", '76.2mm OS-62 FRAG', 152)
    SM.AddToUnitMagazine("R255 Kirovskiy Komsomolets", '9M32 Strela 2', 16)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.266633, 0.957733, 0.000000, 15.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('R-69')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(7.979, 0.723, -0.024, 0.099)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1241.1 Molniya'
    unit.unitName = "R-71"
    UI = SM.GetUnitInterface('R-69')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0547
    lat_deg = 57.296*leader_track.Lat + 0.0190
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -95.71
    unit.speed = 15.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M32 Strela 2', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("R-71", '76.2mm OS-62 FRAG', 152)
    SM.AddToUnitMagazine("R-71", '9M32 Strela 2', 16)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.266633, 0.957733, 0.000000, 15.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('R-69')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(4.006, 0.500, 0.552, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1241.1 Molniya'
    unit.unitName = "R-54 Krasnodarskiy Komsomolets"
    UI = SM.GetUnitInterface('R-69')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0605
    lat_deg = 57.296*leader_track.Lat + -0.0009
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -95.71
    unit.speed = 15.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M32 Strela 2', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("R-54 Krasnodarskiy Komsomolets", '76.2mm OS-62 FRAG', 152)
    SM.AddToUnitMagazine("R-54 Krasnodarskiy Komsomolets", '9M32 Strela 2', 16)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.266633, 0.957733, 0.000000, 15.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('R-69')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(4.006, 0.500, -0.018, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 1241.1 Molniya'
    unit.unitName = "R-79"
    UI = SM.GetUnitInterface('R-69')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0488
    lat_deg = 57.296*leader_track.Lat + -0.0177
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -95.71
    unit.speed = 15.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'P-15M Termit', 2)
    SM.SetUnitLauncherItem(unit.unitName, 2, '76.2mm OS-62 FRAG', 152)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M32 Strela 2', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '30mm OF-84 HE-FRAG AK-630M', 59)
    SM.SetUnitLauncherItem(unit.unitName, 5, '30mm OF-84 HE-FRAG AK-630M', 59)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("R-79", '76.2mm OS-62 FRAG', 152)
    SM.AddToUnitMagazine("R-79", '9M32 Strela 2', 16)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.266633, 0.957733, 0.000000, 15.000000)
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
    BB.Write('ID_EngageLimit', '{"128.0": 0.0, "131.0": 0.0, "134.0": 0.0, "135.0": 0.0, "138.0": 0.0, "133.0": 0.0, "136.0": 0.0, "137.0": 0.0, "129.0": 0.0, "140.0": 0.0, "139.0": 0.0, "132.0": 0.0}')
    leader_id = UI.LookupFriendlyId('R-69')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(3.991, 0.500, -0.528, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(0)
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Airbus A330'
    unit.unitName = "BA 4187"
    unit.SetPosition(0.256800, 51.572676, 9363.1)
    unit.heading = 52.59
    unit.speed = 464.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.449873, 1.138943, 10000.000000, 464.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Boeing 767'
    unit.unitName = "NA 1587"
    unit.SetPosition(29.537636, 60.458048, 9347.7)
    unit.heading = 245.22
    unit.speed = 464.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.108537, 1.023246, 10000.000000, 464.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Herold"
    unit.SetPosition(17.940283, 54.958857, 0.0)
    unit.heading = -108.43
    unit.speed = 4.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.290435, 0.954734, 0.000000, 4.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'LNG Carrier'
    unit.unitName = "Gas Express"
    unit.SetPosition(22.099899, 57.796889, 0.0)
    unit.heading = -100.30
    unit.speed = 11.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.368917, 1.004858, 0.000000, 11.000000)
    UI.AddNavWaypointAdvanced(0.335851, 0.952605, 0.000000, 11.000000)
    UI.AddNavWaypointAdvanced(0.326117, 0.951438, 0.000000, 11.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Petros IV"
    unit.SetPosition(22.454503, 59.183103, 0.0)
    unit.heading = -135.00
    unit.speed = 4.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.383578, 1.030062, 0.000000, 4.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'General Cargo'
    unit.unitName = "Peg Leg"
    unit.SetPosition(17.250556, 56.116919, 0.0)
    unit.heading = 0.00
    unit.speed = 16.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.321437, 1.021663, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.340654, 1.034387, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.344420, 1.043152, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.333616, 1.050896, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.330553, 1.101401, 0.000000, 16.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Ellie P"
    unit.SetPosition(18.909727, 57.525307, 0.0)
    unit.heading = 21.25
    unit.speed = 4.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.335445, 1.009878, 0.000000, 4.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Peter F"
    unit.SetPosition(17.183291, 58.546604, 0.0)
    unit.heading = -165.96
    unit.speed = 4.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.297388, 1.012416, 0.000000, 4.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ferry'
    unit.unitName = "Latavia"
    unit.SetPosition(13.711396, 54.474364, 0.0)
    unit.heading = 67.62
    unit.speed = 16.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.241617, 0.954316, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.216234, 0.963575, 0.000000, 16.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Newton"
    unit.SetPosition(11.368915, 54.239967, 0.0)
    unit.heading = 69.78
    unit.speed = 10.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.226109, 0.956491, 0.000000, 10.000000)
    UI.AddNavWaypointAdvanced(0.253396, 0.966335, 0.000000, 10.000000)
    UI.AddNavWaypointAdvanced(0.300498, 0.980236, 0.000000, 10.000000)
    UI.AddNavWaypointAdvanced(0.309807, 1.012066, 0.000000, 10.000000)
    UI.AddNavWaypointAdvanced(0.300026, 1.022233, 0.000000, 10.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ferry'
    unit.unitName = "Lvov"
    unit.SetPosition(14.844534, 56.081167, 0.0)
    unit.heading = 132.51
    unit.speed = 16.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.291208, 0.953628, 0.000000, 16.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ferry'
    unit.unitName = "Freda"
    unit.SetPosition(21.261776, 57.063675, 0.0)
    unit.heading = -84.29
    unit.speed = 16.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.329461, 1.006734, 75217097760510450000000000000.000000, 16.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Container Ship'
    unit.unitName = "Bordeaux Maersk"
    unit.SetPosition(19.514656, 56.526756, 0.0)
    unit.heading = -122.74
    unit.speed = 16.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.267798, 0.957793, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.228793, 0.957223, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.209359, 0.949521, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.188717, 0.953986, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.189388, 0.957764, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.192175, 0.962727, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.187997, 0.973234, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.195633, 0.980075, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.206262, 0.989987, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.194228, 1.010026, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('BDK-10')
    goal_temp.AddTarget('BDK-77')
    goal_temp.AddTarget('BDK-13')
    goal_temp.AddTarget('BDK-101 Oslyabya')
    goal_temp.AddTarget('Cargo')
    goal_temp.AddTarget('Freighter')
    goal_temp.SetQuantity(6)
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.AreaGoal()
    goal_temp.SetTargetList('Freighter, BDK-13, BDK-101 Oslyabya, Cargo, BDK-10, BDK-77')
    goal_temp.SetTimeObjective(0.000000)
    goal_temp.SetLogicAny(0)
    goal_temp.SetQuantity(6)
    goal_temp.AddPointDeg(15.30360, 55.34752)
    goal_temp.AddPointDeg(15.30360, 55.18864)
    goal_temp.AddPointDeg(15.07992, 55.18829)
    goal_temp.AddPointDeg(15.08052, 55.34680)
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Alliance 3 goals
    ##############################

    SM.SetAllianceGoal(3, goal_temp)

    SM.SetAllianceROEByType(3, 2, 2, 2, 2)

    ##############################
    ### Overlay Graphics
    ##############################
    SM.OverlayText('Bornholm', 14.8043, 55.1542, '0x000000FF')
    ##############################
    ### Randomization Info
    ##############################
