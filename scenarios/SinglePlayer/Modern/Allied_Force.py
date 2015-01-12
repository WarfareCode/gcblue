# Created on 01/09/15 06:59:15
from math import *
from random import *
from UnitCommands import *

def CreateScenario(SM):

    SM.SetScenarioDescription("""Serbian forces have utilized Heroin drug trade profits to modernize their \nmilitary. Recent satellite photos show the Serbian airforce has been fully \nmobilized. Advanced SAM S300(Nato sig SA-10) installations are \nthroughtout Serbia. Long range deadly Mobile Silkwarm (Nato sig. SSC-\n1b) ASM sites have also been active in the theater. Reports of a possible \nKilo Class sub operating in the area have not been comfirmed. There are \nreports from Italy that organizations sympathetic to the Milosovich \nregime are using Italian ships to smuggle arms and oil from Russia and \nPLA to Serbia via Bosnia. These ships are to be identified and neutralized \nimmediately. Targets are concentrated in 5 primary areas and a few \nscattered regions: industrial and military targets in Novi Sod which \nprovide equipment to the Serbian armed forces; both military and \nindustrial targets in Belgrade; merchant, military, and industrial in \nthe ports of Budva and Herceg Novi; isolated command centers in central \nSerbia; military targets\n""")
    SM.SetScenarioName("""Operation Allied Force""")
    SM.CreateAlliance(1, 'NATO')
    SM.SetAllianceDefaultCountry(1, 'NATO')
    SM.SetAlliancePlayable(1, 1)
    SM.CreateAlliance(2, 'Red')
    SM.SetAllianceDefaultCountry(2, 'Red')
    SM.SetAlliancePlayable(2, 0)
    SM.CreateAlliance(3, 'Neutral')
    SM.SetAllianceDefaultCountry(3, 'Neutral')
    SM.SetAlliancePlayable(3, 0)
    SM.SetAllianceRelationship(1, 3, 'Neutral')
    SM.SetAllianceRelationship(2, 3, 'Neutral')
    SM.SetUserAlliance(1)

    SM.SetDateTime(1999,3,24,0,0,0)
    SM.SetStartTheater(13.529165, 44.970833) # (lon, lat) in degrees, negative is West or South
    SM.SetScenarioLoaded(1)

    SM.SetSeaState(2)

    SM.SetSVP('0.000000,1515.000000,200.000000,1500.000000,300.000000,1510.000000,500.000000,1520.000000,5000.000000,1600.000000')

    ####################
    SM.SetSimpleBriefing(1, """FROM: STRATEGIC COMMAND, NATO JOINT OPERATIONS\n\nTO: CAPTAIN, JOINT NATO FORCE, ADRIATIC SEA\n\nRE: OPERATION ALLIED FORCES\n\nTASKING (1)RECON : 0200 PREFORM RECON ID OF SERBIAN MILITARY \nAND ECONOMIC INFRASTRUCTURAL TARGETS.  TARGETS INCLUDE \nMILITARY UNITS AND FACILITIES, SHIPPING PORTS, FACTORIES, \nWAREHOUSES, POWER STATIONS AND OTHER SUCH ASSETS.\n\nTASKING (2) TLAM: WHEN DIRECTED CONDUCT TLAM STRIKES ON \nSERBIAN SAM/RADAR/AA/AIRBASE INSTALLATIONS. \n\nTASKING (3) AIR CAMPAIGN: CONDUCT AIR STRIKES AGAINST C-1, C-\n2, C-3, C-4 TARGETS IN PREPARATION OF AMPHIBIOUS ASSAULT. \n\nTASKING (4) COLLATERAL DAMAGE: AVOID ALL FORMS OF COLLATERAL \nDAMAGE TO ANY EMBASSIES, SCHOOLS, HOSPITALS OR OTHER \nRESIDENTIAL/CIVILIAN TARGETS. INTEL REPORTS POSSIBLE SERBIAN \nCOMMAND STRUCTURES INSIDE RED CROSS CAMPS. \n\nTASKING (3) MARITINE: LOCATE AND SINK ALL COMMERCIAL VESSELS \nTHAT ARE KNOWN TO BE CARRYING MUNITIONS AND OIL TO BOSNIA \nFOR DISTRIBUTION TO SERBIAN FORCES.  SOME OF THE \nREGISTRATION NUMBERS OF THESE SHIPS ARE BEING GATHERED BY \nTHE ITALIAN MILITARY AND WILL BE FORWARDED TO NATO COMMAND \nFOR DISTRIBUTION.  THESE SHIPS MAY BE TRAVELLING IN A BUSY \nCOMMERICAL SHIPPING LANE - YOU MUST NOT ATTACK ANY \nCOMMERCIAL VESSEL NOT TARGETED TO BE NEUTRALIZED.\n\nTASKING (4) AIRBOURNE ASSAULT: THE NATO  COALITION NEEDS TO \nSECURE THE PORT AT BUDVA AT 42-15/19-02. WHERE YOU WILL \nEXECUTE A AIRBOURNE ASSAULT ONT HE PORT. ASSAULT MISSION \nWILL BE COMPLETE WHEN YOU HAVE DROPPED PARA TROOPERS \nWITHIN 1 NM OF BUDVA PORT USING THE FOLLOWING \nAIRCRAFT 15...C-130H TRN CARRYING US 82ND AIRBORNE/ FRENCH \n4TH AIR SPECIAL OPS 15...C-130J TRN CARRYING US 7th ARMY \nARMORED MECH DIVIVSION/45TH ROYAL MARINES. EXPECT STRONG \nRESISTANCE. CLEAR ALL SILKWARM BATTERIES BEFORE ENTERING \nADRIATIC SEA.\n\n\n\n\n""")

    ####################
    SM.SetSimpleBriefing(2, """No briefing found""")

    ####################
    SM.SetSimpleBriefing(3, """No briefing found""")

    ##############################
    ### Alliance 1 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'SSN 688 Los Angeles Improved'
    unit.unitName = "USS Tucson"
    unit.SetPosition(17.728231, 41.219501, -110.0)
    unit.heading = 351.03
    unit.speed = 3.7
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
    SM.AddToUnitMagazine("USS Tucson", 'Mk-48 Mod6', 12)
    SM.AddToUnitMagazine("USS Tucson", 'UGM-84C Harpoon', 4)
    UI.SetSensorState(5, 0)
    UI.SetSensorState(6, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.300854, 0.737123, 0.000000, 0.000000)
    UI.AddTask('SubBattery', 4.000000, 3)
    UI.AddTask('SubEvade', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'CVN-73 (Nimitz) USS George Washington'
    unit.unitName = "USS George Washington"
    unit.SetPosition(25.147793, 38.940258, 0.0)
    unit.heading = -35.70
    unit.speed = 5.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS George Washington", 'Fuel', 8205300)
    SM.AddToUnitMagazine("USS George Washington", 'AIM-9M', 754)
    SM.AddToUnitMagazine("USS George Washington", 'AIM-7P', 311)
    SM.AddToUnitMagazine("USS George Washington", 'AIM-120B', 305)
    SM.AddToUnitMagazine("USS George Washington", 'AIM-120C', 410)
    SM.AddToUnitMagazine("USS George Washington", 'AIM-54C', 100)
    SM.AddToUnitMagazine("USS George Washington", 'AGM-88B', 207)
    SM.AddToUnitMagazine("USS George Washington", 'AGM-88C', 239)
    SM.AddToUnitMagazine("USS George Washington", 'AGM-84D Harpoon', 154)
    SM.AddToUnitMagazine("USS George Washington", 'AGM-84F Harpoon', 231)
    SM.AddToUnitMagazine("USS George Washington", 'AGM-65F', 1224)
    SM.AddToUnitMagazine("USS George Washington", 'Mk-46 Mod5', 217)
    SM.AddToUnitMagazine("USS George Washington", 'Mk-50', 25)
    SM.AddToUnitMagazine("USS George Washington", 'Mk-82', 813)
    SM.AddToUnitMagazine("USS George Washington", 'Mk-83', 849)
    SM.AddToUnitMagazine("USS George Washington", 'Mk-84', 430)
    SM.AddToUnitMagazine("USS George Washington", 'GBU-31C(v)4', 141)
    SM.AddToUnitMagazine("USS George Washington", 'GBU-32A(v)2', 424)
    SM.AddToUnitMagazine("USS George Washington", 'GBU-32C(v)4', 424)
    SM.AddToUnitMagazine("USS George Washington", '1400 liter tank', 28)
    SM.AddToUnitMagazine("USS George Washington", 'FPU-6', 66)
    SM.AddToUnitMagazine("USS George Washington", '120 gallon tank', 9)
    SM.AddToUnitMagazine("USS George Washington", '20mm PGU', 3773)
    SM.AddToUnitMagazine("USS George Washington", 'Chaff-1', 5660)
    SM.AddToUnitMagazine("USS George Washington", 'Flare-1', 5540)
    SM.AddToUnitMagazine("USS George Washington", 'LOFAR (95) Sonobuoy', 440)
    SM.AddToUnitMagazine("USS George Washington", 'DICASS (95) Sonobuoy', 605)
    SM.AddToUnitMagazine("USS George Washington", 'DIFAR (95) Sonobuoy', 1650)
    SM.AddToUnitMagazine("USS George Washington", 'RIM-7P(v1)', 94)
    SM.AddToUnitMagazine("USS George Washington", 'FPU-8', 24)
    SM.AddToUnitMagazine("USS George Washington", '20mm mark 244-0 ELC', 2092)
    UI.SetSensorState(4, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.422333, 0.697451, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 1', 3)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 1', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 2', 3)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 2', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 3', 2)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 3', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 4', 2)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 4', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 5', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 5', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 6', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 6', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 7', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 7', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 8', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 8', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 9', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 9', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 10', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 10', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 11', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 11', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F-14B', 'Diamond 12', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Diamond 12', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 1', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 1', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 2', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 2', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 3', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 3', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 4', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 4', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 5', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 5', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 6', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 6', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 7', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 7', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 8', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 8', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 9', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 9', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 10', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 10', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 11', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 11', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'T-Bolt 12', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'T-Bolt 12', '1 1400 liter tank;2 AIM-120C;2 AGM-88C;2 AGM-88C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 1', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 1', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 2', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 2', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 3', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 3', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 4', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 4', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 5', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 5', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 6', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 6', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 7', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 7', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 8', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 8', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 9', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 9', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 10', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 10', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 11', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 11', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Claw 12', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Claw 12', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 1', 2)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 1', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 2', 2)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 2', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 3', 2)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 3', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 4', 2)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 4', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 5', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 5', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 6', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 6', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 7', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 7', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 8', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 8', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 9', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 9', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 10', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 10', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 11', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 11', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'F/A-18C', 'Winder 12', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Winder 12', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'E-2C Group 2', 'Screwtops 1', 3)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Screwtops 1', '')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'E-2C Group 2', 'Screwtops 2', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Screwtops 2', '')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'E-2C Group 2', 'Screwtops 3', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Screwtops 3', '')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'E-2C Group 2', 'Screwtops 4', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Screwtops 4', '')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'SH-60F', 'Dragonslayers 1', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Dragonslayers 1', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (100) Sonobuoy;10 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'SH-60F', 'Dragonslayers 2', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Dragonslayers 2', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (100) Sonobuoy;10 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'SH-60F', 'Dragonslayers 3', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Dragonslayers 3', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (100) Sonobuoy;10 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'SH-60F', 'Dragonslayers 4', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Dragonslayers 4', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (100) Sonobuoy;10 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'SH-60F', 'Dragonslayers 5', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Dragonslayers 5', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (100) Sonobuoy;10 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'SH-60F', 'Dragonslayers 6', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Dragonslayers 6', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (100) Sonobuoy;10 DIFAR (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'EA-6B', 'Rooks 1', 2)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Rooks 1', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'EA-6B', 'Rooks 2', 2)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Rooks 2', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'EA-6B', 'Rooks 3', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Rooks 3', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'EA-6B', 'Rooks 4', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Rooks 4', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'EA-6B', 'Rooks 5', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Rooks 5', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'EA-6B', 'Rooks 6', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Rooks 6', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'S-3B', 'Maulers 1', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Maulers 1', '12 DICASS (100) Sonobuoy;12 LOFAR (100) Sonobuoy;36 DIFAR (100) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;3 AGM-65F;3 AGM-65F;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'S-3B', 'Maulers 2', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Maulers 2', '12 DICASS (100) Sonobuoy;12 LOFAR (100) Sonobuoy;36 DIFAR (100) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;3 AGM-65F;3 AGM-65F;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'S-3B', 'Maulers 3', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Maulers 3', '12 DICASS (100) Sonobuoy;12 LOFAR (100) Sonobuoy;36 DIFAR (100) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;3 AGM-65F;3 AGM-65F;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'S-3B', 'Maulers 4', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Maulers 4', '12 DICASS (100) Sonobuoy;12 LOFAR (100) Sonobuoy;36 DIFAR (100) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;3 AGM-65F;3 AGM-65F;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'ES-3A', 'Black Ravens 1', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Black Ravens 1', '6 LOFAR (100) Sonobuoy;27 DIFAR (100) Sonobuoy;27 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'ES-3A', 'Black Ravens 2', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Black Ravens 2', '6 LOFAR (100) Sonobuoy;27 DIFAR (100) Sonobuoy;27 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'C-2A', 'Rawhide 1', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Rawhide 1', '')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'C-2A', 'Rawhide 2', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Rawhide 2', '')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'KA-6D', 'Texaco-1', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Texaco-1', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'KA-6D', 'Texaco-2', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Texaco-2', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'KA-6D', 'Texaco-3', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Texaco-3', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS George Washington', 'KA-6D', 'Texaco-4', 1)
    SM.SetFlightDeckUnitLoadout('USS George Washington', 'Texaco-4', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'CVN-72 (Nimitz) USS Abraham Lincoln'
    unit.unitName = "USS Abraham Lincoln"
    unit.SetPosition(10.489407, 41.295946, 0.0)
    unit.heading = 118.90
    unit.speed = 5.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'Fuel', 8205300)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'AIM-9M', 754)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'AIM-7P', 311)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'AIM-120B', 305)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'AIM-120C', 410)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'AIM-54C', 100)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'AGM-88B', 207)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'AGM-88C', 287)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'AGM-84D Harpoon', 154)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'AGM-84F Harpoon', 231)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'AGM-65F', 1304)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'Mk-46 Mod5', 217)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'Mk-50', 25)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'Mk-82', 813)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'Mk-83', 849)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'Mk-84', 430)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'GBU-31C(v)4', 141)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'GBU-32A(v)2', 376)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'GBU-32C(v)4', 424)
    SM.AddToUnitMagazine("USS Abraham Lincoln", '1400 liter tank', 28)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'FPU-6', 66)
    SM.AddToUnitMagazine("USS Abraham Lincoln", '120 gallon tank', 9)
    SM.AddToUnitMagazine("USS Abraham Lincoln", '20mm PGU', 3773)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'Chaff-1', 5660)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'Flare-1', 5540)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'LOFAR (95) Sonobuoy', 440)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'DICASS (95) Sonobuoy', 605)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'DIFAR (95) Sonobuoy', 1650)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'RIM-7P(v1)', 94)
    SM.AddToUnitMagazine("USS Abraham Lincoln", 'FPU-8', 24)
    SM.AddToUnitMagazine("USS Abraham Lincoln", '20mm mark 244-0 ELC', 2092)
    UI.SetSensorState(4, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.262991, 0.687127, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 1', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 2', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 3', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 4', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 5', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 6', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 7', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 8', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 9', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 10', '32 20mm PGU;4 AIM-7P;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 11', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F-14D', 'Lion 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Lion 12', '32 20mm PGU;4 AIM-54C;2 AIM-9M;2 AIM-54C;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 1', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-132 ASRAAM;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 2', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 3', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 4', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 5', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 6', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 7', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 8', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 9', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 10', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 11', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Talon 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Talon 12', '1 1400 liter tank;2 AIM-120C;2 AIM-120C;2 AIM-120C;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 1', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 2', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 3', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 4', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 5', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 6', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 7', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 8', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 9', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 10', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 11', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Sting 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sting 12', '1 1400 liter tank;2 AIM-120C;2 GBU-32A(v)2;2 GBU-32A(v)2;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 1', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 2', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 3', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 4', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 5', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 6', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 7', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 8', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 9', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 9', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 10', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 10', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 11', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 11', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'F/A-18C', 'Fist 12', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Fist 12', '1 1400 liter tank;2 AIM-120C;4 AGM-65F;4 AGM-65F;2 AIM-9M;46 20mm PGU;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'EA-6B', 'Cougar 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Cougar 1', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'EA-6B', 'Cougar 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Cougar 2', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'EA-6B', 'Cougar 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Cougar 3', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'EA-6B', 'Cougar 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Cougar 4', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'EA-6B', 'Cougar 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Cougar 5', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'EA-6B', 'Cougar 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Cougar 6', '2 AGM-88C;2 AGM-88C;6 Mk-82;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'S-3B', 'Blue Wolves 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Blue Wolves 1', '12 DICASS (95) Sonobuoy;12 LOFAR (95) Sonobuoy;36 DIFAR (95) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;3 AGM-65F;3 AGM-65F;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'S-3B', 'Blue Wolves 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Blue Wolves 2', '12 DICASS (95) Sonobuoy;12 LOFAR (95) Sonobuoy;36 DIFAR (95) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;3 AGM-65F;3 AGM-65F;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'S-3B', 'Blue Wolves 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Blue Wolves 3', '12 DICASS (95) Sonobuoy;12 LOFAR (95) Sonobuoy;36 DIFAR (95) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;3 AGM-65F;3 AGM-65F;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'S-3B', 'Blue Wolves 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Blue Wolves 4', '12 DICASS (95) Sonobuoy;12 LOFAR (95) Sonobuoy;36 DIFAR (95) Sonobuoy;2 Mk-46 Mod5;2 Mk-46 Mod5;3 AGM-65F;3 AGM-65F;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'E-2C Group 2', 'Black Eagles 1', 3)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Black Eagles 1', '')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'E-2C Group 2', 'Black Eagles 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Black Eagles 2', '')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'E-2C Group 2', 'Black Eagles 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Black Eagles 3', '')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'E-2C Group 2', 'Black Eagles 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Black Eagles 4', '')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'SH-60F', 'Knight 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Knight 1', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (95) Sonobuoy;10 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'SH-60F', 'Knight 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Knight 2', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (95) Sonobuoy;10 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'SH-60F', 'Knight 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Knight 3', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (95) Sonobuoy;10 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'SH-60F', 'Knight 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Knight 4', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (95) Sonobuoy;10 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'SH-60F', 'Knight 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Knight 5', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (95) Sonobuoy;10 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'SH-60F', 'Knight 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Knight 6', '1 120 gallon tank;1 120 gallon tank;1 120 gallon tank;30 Flare-1;30 Chaff-1;5 DICASS (95) Sonobuoy;10 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'C-2A', 'Provider 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Provider 1', '')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'C-2A', 'Provider 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Provider 2', '')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'ES-3A', 'Sea Shadow 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sea Shadow 1', '6 LOFAR (100) Sonobuoy;27 DIFAR (100) Sonobuoy;27 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'ES-3A', 'Sea Shadow 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sea Shadow 2', '6 LOFAR (100) Sonobuoy;27 DIFAR (100) Sonobuoy;27 DICASS (100) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'KA-6D', 'Sunoco-1', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sunoco-1', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'KA-6D', 'Sunoco-2', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sunoco-2', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'KA-6D', 'Sunoco-3', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sunoco-3', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Abraham Lincoln', 'KA-6D', 'Sunoco-4', 1)
    SM.SetFlightDeckUnitLoadout('USS Abraham Lincoln', 'Sunoco-4', '1 300 gallon wing tank;1 300 gallon wing tank;1 300 gallon wing tank;30 Flare-1;30 Chaff-1;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Milano AB"
    unit.SetPosition(11.101630, 44.778144, 0.0)
    unit.heading = 54.46
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Milano AB", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Milano AB", '1150 Liter Tank', 12)
    SM.AddToUnitMagazine("Milano AB", '20mm PGU', 10254)
    SM.AddToUnitMagazine("Milano AB", '20mm PGU-28/B', 10254)
    SM.AddToUnitMagazine("Milano AB", '27mm BK27 27x145mm', 3918)
    SM.AddToUnitMagazine("Milano AB", '330 gallon wing tank', 24)
    SM.AddToUnitMagazine("Milano AB", '600 gallon tank', 60)
    SM.AddToUnitMagazine("Milano AB", 'AGM-130', 40)
    SM.AddToUnitMagazine("Milano AB", 'AGM-65B', 260)
    SM.AddToUnitMagazine("Milano AB", 'AGM-65D', 260)
    SM.AddToUnitMagazine("Milano AB", 'AGM-65E', 69)
    SM.AddToUnitMagazine("Milano AB", 'AGM-65F', 260)
    SM.AddToUnitMagazine("Milano AB", 'AGM-65G', 259)
    SM.AddToUnitMagazine("Milano AB", 'AGM-88B', 586)
    SM.AddToUnitMagazine("Milano AB", 'AGM-88C', 446)
    SM.AddToUnitMagazine("Milano AB", 'AIM-120B', 410)
    SM.AddToUnitMagazine("Milano AB", 'AIM-120C', 2155)
    SM.AddToUnitMagazine("Milano AB", 'AIM-7P', 1188)
    SM.AddToUnitMagazine("Milano AB", 'AIM-9M', 1238)
    SM.AddToUnitMagazine("Milano AB", 'AIM-9P', 743)
    SM.AddToUnitMagazine("Milano AB", 'AIM-9P4', 743)
    SM.AddToUnitMagazine("Milano AB", 'Chaff-1', 35914)
    SM.AddToUnitMagazine("Milano AB", 'Flare-1', 35914)
    SM.AddToUnitMagazine("Milano AB", 'GBU-10/B', 206)
    SM.AddToUnitMagazine("Milano AB", 'GBU-12/B', 796)
    SM.AddToUnitMagazine("Milano AB", 'GBU-15/B', 59)
    SM.AddToUnitMagazine("Milano AB", 'GBU-16/B', 165)
    SM.AddToUnitMagazine("Milano AB", 'GBU-24/B', 99)
    SM.AddToUnitMagazine("Milano AB", 'GBU-24B/B', 99)
    SM.AddToUnitMagazine("Milano AB", 'GBU-27', 82)
    SM.AddToUnitMagazine("Milano AB", 'GBU-28B/B', 12)
    SM.AddToUnitMagazine("Milano AB", 'Mk-81', 1003)
    SM.AddToUnitMagazine("Milano AB", 'Mk-82', 1025)
    SM.AddToUnitMagazine("Milano AB", 'Mk-83', 371)
    SM.AddToUnitMagazine("Milano AB", 'Mk-84', 257)
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
    
    SM.AddUnitToFlightDeck('Milano AB', 'E-3D/F', 'Sentry-1', 3)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Sentry-1', '')
    
    SM.AddUnitToFlightDeck('Milano AB', 'E-3D/F', 'Sentry-2', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Sentry-2', '')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-1', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-1', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-2', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-2', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-3', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-3', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-4', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-4', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-5', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-5', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-6', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-6', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-7', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-7', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-8', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-8', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-9', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-9', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-10', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-10', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-11', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-11', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15E', 'Strike Eagle-12', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Strike Eagle-12', '2 AGM-130;2 AGM-65D;2 AGM-65D;4 GBU-12/B;4 AIM-120C;1 GBU-28B/B;120 Flare-1;120 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-1', 2)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-1', '2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-2', 2)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-2', '2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-3', 2)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-3', '2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-4', 2)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-4', '2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-5', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-5', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-6', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-6', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-7', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-7', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-8', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-8', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-9', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-9', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-10', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-10', '2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-11', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-11', '2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-12', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-12', '2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-13', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-13', '2 AGM-88B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-14', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-14', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-15', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-15', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-16', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-16', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-17', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-17', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-18', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-18', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-19', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-19', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-117', 'Goblin-20', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Goblin-20', '2 GBU-10/B;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Tornado ECR (Italy)', 'Weasel-1', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Weasel-1', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-88B;1 AGM-88B;1 AGM-88B;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Tornado ECR (Italy)', 'Weasel-2', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Weasel-2', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-88B;1 AGM-88B;1 AGM-88B;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Tornado ECR (Italy)', 'Weasel-3', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Weasel-3', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-88B;1 AGM-88B;1 AGM-88B;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Tornado ECR (Italy)', 'Weasel-4', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Weasel-4', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-88B;1 AGM-88B;1 AGM-88B;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Tornado ECR (Italy)', 'Weasel-5', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Weasel-5', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-88B;1 AGM-88B;1 AGM-88B;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Tornado ECR (Italy)', 'Weasel-6', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Weasel-6', '50 Chaff-1;50 Flare-1;1 AIM-9M;1 AIM-9M;1 330 gallon wing tank;1 330 gallon wing tank;1 AGM-88B;1 AGM-88B;1 AGM-88B;30 27mm BK27 27x145mm;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-1', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-1', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-2', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-2', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-3', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-3', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-4', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-4', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-5', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-5', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-6', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-6', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-7', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-7', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-8', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-8', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-9', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-9', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-10', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-10', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-11', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-11', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'Typhoon', 'Typhoon-12', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Typhoon-12', '2 AIM-9M;4 GBU-12/B;4 GBU-12/B;4 AIM-120C;1 1150 Liter Tank;30 27mm BK27 27x145mm;30 Flare-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-1', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-1', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-2', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-2', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-3', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-3', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-4', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-4', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-5', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-5', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-6', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-6', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-7', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-7', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-8', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-8', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-9', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-9', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-10', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-10', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-11', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-11', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'F-15C', 'Cobras-12', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Cobras-12', '4 AIM-120C;2 AIM-9M;2 AIM-120C;3 600 gallon tank;30 Flare-1;30 Chaff-1;46 20mm PGU;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'KC-767A', 'Refuel-1', 3)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Refuel-1', '')
    
    SM.AddUnitToFlightDeck('Milano AB', 'KC-767A', 'Refuel-2', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Refuel-2', '')
    
    SM.AddUnitToFlightDeck('Milano AB', 'KC-767A', 'Refuel-3', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Refuel-3', '')
    
    SM.AddUnitToFlightDeck('Milano AB', 'KC-767A', 'Refuel-4', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Refuel-4', '')
    
    SM.AddUnitToFlightDeck('Milano AB', 'KC-767A', 'Refuel-5', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Refuel-5', '')
    
    SM.AddUnitToFlightDeck('Milano AB', 'KC-767A', 'Refuel-6', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', 'Refuel-6', '')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-1', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-1', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-2', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-2', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-3', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-3', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-4', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-4', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-5', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-5', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-6', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-6', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-7', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-7', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-8', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-8', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-9', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-9', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-10', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-10', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-11', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-11', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-12', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-12', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-13', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-13', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-14', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-14', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130H', '82nd ABN-15', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '82nd ABN-15', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-1', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-1', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-2', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-2', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-3', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-3', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-4', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-4', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-5', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-5', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-6', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-6', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-7', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-7', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-8', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-8', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-9', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-9', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-10', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-10', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-11', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-11', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-12', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-12', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-13', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-13', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-14', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-14', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    
    SM.AddUnitToFlightDeck('Milano AB', 'C-130J', '7th INF-15', 1)
    SM.SetFlightDeckUnitLoadout('Milano AB', '7th INF-15', '4 AN/ALE-55 FOTD;4 AN/ALE-55 FOTD;100 AN/AAQ-24 Nemesis Laser Beam;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Wasp LHDM'
    unit.unitName = "USS Bonhomme Richard"
    unit.SetPosition(19.007093, 40.014066, 0.0)
    unit.heading = -10.89
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 4, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 5, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 9, '25mm APDS', 400)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'Fuel', 1200000)
    SM.AddToUnitMagazine("USS Bonhomme Richard", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'RIM-7P(v1)', 48)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'RIM-116A RAM', 84)
    SM.AddToUnitMagazine("USS Bonhomme Richard", '.50 cal bullet', 12000)
    SM.AddToUnitMagazine("USS Bonhomme Richard", '25mm APDS', 8000)
    SM.AddToUnitMagazine("USS Bonhomme Richard", '190 gallon wing tank', 36)
    SM.AddToUnitMagazine("USS Bonhomme Richard", '300 gallon wing tank', 36)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'AGM-114 Hellfire', 2287)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'AGM-65D', 363)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'AGM-88C', 145)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'AIM-120C', 187)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'AIM-9M', 115)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'BGM-71E TOW 2', 2287)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'Chaff-1', 21141)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'Flare-1', 19701)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'GBU-31A(v)2', 436)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'GBU-31C(v)4', 420)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'GBU-32A(v)2', 436)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'GBU-32C(v)4', 420)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'Hydra-70 rocket', 101395)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'Mk 71 Zuni WAFAR', 3540)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'Mk-81', 1016)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'Mk-82', 1016)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'Mk-83', 246)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'Mk-84', 405)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'AGM-119B', 8)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'Mk-46 Mod5', 58)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'Mk-50', 8)
    SM.AddToUnitMagazine("USS Bonhomme Richard", '120 gallon tank', 8)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'LOFAR (95) Sonobuoy', 526)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'DICASS (95) Sonobuoy', 526)
    SM.AddToUnitMagazine("USS Bonhomme Richard", 'DIFAR (95) Sonobuoy', 1576)
    SM.AddToUnitMagazine("USS Bonhomme Richard", '100 gallon wing tank', 32)
    UI.SetSensorState(4, 0)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.322950, 0.732851, 0.000000, 0.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AV-8B Harrier II+', 'Striker 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Striker 1', '2 GBU-32C(v)4;2 AIM-120C;2 AIM-9M;2 GBU-31C(v)4;1 Mk-83;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AV-8B Harrier II+', 'Striker 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Striker 2', '2 GBU-32C(v)4;2 AIM-120C;2 AIM-9M;2 GBU-31C(v)4;1 Mk-83;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AV-8B Harrier II+', 'Striker 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Striker 3', '2 GBU-32C(v)4;2 AIM-120C;2 AIM-9M;2 GBU-31C(v)4;1 Mk-83;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AV-8B Harrier II+', 'Striker 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Striker 4', '2 GBU-32C(v)4;2 AIM-120C;2 AIM-9M;2 GBU-31C(v)4;1 Mk-83;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AV-8B Harrier II+', 'Striker 5', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Striker 5', '2 GBU-32C(v)4;2 AIM-120C;2 AIM-9M;2 GBU-31C(v)4;1 Mk-83;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AV-8B Harrier II+', 'Striker 6', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Striker 6', '2 GBU-32C(v)4;2 AIM-120C;2 AIM-9M;2 GBU-31C(v)4;1 Mk-83;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AV-8B Harrier II+', 'Striker 7', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Striker 7', '2 GBU-32C(v)4;2 AIM-120C;2 AIM-9M;2 GBU-31C(v)4;1 Mk-83;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AV-8B Harrier II+', 'Striker 8', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Striker 8', '2 GBU-32C(v)4;2 AIM-120C;2 AIM-9M;2 GBU-31C(v)4;1 Mk-83;90 Flare-1;90 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'CH-53E', 'Stallion 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Stallion 1', '')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'CH-53E', 'Stallion 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Stallion 2', '')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'CH-53E', 'Stallion 3', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Stallion 3', '')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'CH-53E', 'Stallion 4', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Stallion 4', '')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'UH-1N', 'Huey  1', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Huey  1', '')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'UH-1N', 'Huey  2', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Huey  2', '')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  1', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  1', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  2', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  2', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  3', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  3', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  4', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  4', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  5', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  5', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  6', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  6', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  7', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  7', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  8', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  8', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  9', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  9', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  10', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  10', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  11', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  11', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  12', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  12', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  13', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  13', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  14', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  14', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  15', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  15', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  16', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  16', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  17', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  17', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  18', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  18', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  19', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  19', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  20', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  20', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  21', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  21', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  22', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  22', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  23', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  23', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'AH-1W Super Cobra', 'Snake  24', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'Snake  24', '230 20mm M53 API;4 AGM-114 Hellfire;1 AIM-9D;1 AIM-9D;4 AGM-114 Hellfire;30 Chaff-1;30 Chaff-1;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'SH-60B', 'SeaHawk  1', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'SeaHawk  1', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Bonhomme Richard', 'SH-60B', 'SeaHawk  2', 1)
    SM.SetFlightDeckUnitLoadout('USS Bonhomme Richard', 'SeaHawk  2', '4 AGM-114 Hellfire;1 120 gallon tank;1 120 gallon tank;25 Chaff-1;25 Chaff-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Sacramento AOEHM'
    unit.unitName = "USS Sacramento"
    UI = SM.GetUnitInterface('USS Bonhomme Richard')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0325
    lat_deg = 57.296*leader_track.Lat + 0.0155
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -10.89
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 1, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-7P(v1)', 8)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Sacramento", '20mm mark 244-0 ELC', 1046)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Bonhomme Richard')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(3.010, 0.500, 1.095, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Whidbey Island LSDHM'
    unit.unitName = "USS Comstock"
    UI = SM.GetUnitInterface('USS Bonhomme Richard')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0098
    lat_deg = 57.296*leader_track.Lat + -0.0179
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -10.89
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 2, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 3, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 4, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 5, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 9, '25mm APDS', 400)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Comstock", '.50 cal bullet', 24000)
    SM.AddToUnitMagazine("USS Comstock", '25mm APDS', 8000)
    SM.AddToUnitMagazine("USS Comstock", 'RIM-116A RAM', 84)
    SM.AddToUnitMagazine("USS Comstock", '20mm mark 244-0 ELC', 1046)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Bonhomme Richard')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(2.422, 0.500, 2.823, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Spruance DDG VLS 93'
    unit.unitName = "USS Nicholson"
    UI = SM.GetUnitInterface('USS George Washington')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0298
    lat_deg = 57.296*leader_track.Lat + -0.0218
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -50.56
    unit.speed = 4.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RUM-139 Mod4 ASROC', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'BGM-109 TASM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'BGM-109 TLAM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'RIM-116A RAM', 21)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Nicholson", '120 gallon tank', 6)
    SM.AddToUnitMagazine("USS Nicholson", 'AGM-114 Hellfire', 24)
    SM.AddToUnitMagazine("USS Nicholson", 'AGM-119B', 4)
    SM.AddToUnitMagazine("USS Nicholson", 'Chaff-1', 131)
    SM.AddToUnitMagazine("USS Nicholson", 'DICASS (95) Sonobuoy', 253)
    SM.AddToUnitMagazine("USS Nicholson", 'DIFAR (95) Sonobuoy', 758)
    SM.AddToUnitMagazine("USS Nicholson", 'Flare-1', 150)
    SM.AddToUnitMagazine("USS Nicholson", 'Fuel', 65095)
    SM.AddToUnitMagazine("USS Nicholson", 'LOFAR (95) Sonobuoy', 253)
    SM.AddToUnitMagazine("USS Nicholson", 'Mk-46 Mod5', 19)
    SM.AddToUnitMagazine("USS Nicholson", 'Mk-50', 2)
    SM.AddToUnitMagazine("USS Nicholson", 'BGM-109 TASM', 5)
    SM.AddToUnitMagazine("USS Nicholson", 'BGM-109 TLAM', 38)
    SM.AddToUnitMagazine("USS Nicholson", 'RUM-139 Mod4 ASROC', 15)
    SM.AddToUnitMagazine("USS Nicholson", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Nicholson", 'RIM-116A RAM', 42)
    SM.AddToUnitMagazine("USS Nicholson", '127mm mk 80 HE-PD mk 67', 1200)
    UI.SetSensorState(6, 0)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"RIM-7F": 0, "RIM-7E": 0, "RIM-116B RAM": 0, "RIM-7H": 0, "RIM-7M(v1)": 0, "RIM-162D": 0, "127mm mk 80 HE-PD mk 67": 2400, "127mm mk 127 HE-CVT EX-175": 0, "BGM-109 TASM": 15, "BGM-109G TLAM-N": 0, "127mm mk 80 HE-PD EX-175": 0, "RUM-139 Mod4 ASROC": 45, "RGM-84C Harpoon": 0, "RIM-116A RAM": 42, "RIM-7P(v1)": 0, "127mm mk 127 HE-CVT mk 67": 0, "RGM-84G Harpoon": 0, "20mm mark 244-0 ELC": 2092, "BGM-109 TLAM": 114, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "ASPIDE-1A": 0, "RGM-84A Harpoon": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 1, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 1, "WeaponList": {"RIM-116A RAM": [21, 21], "RIM-7P(v1)": [8, 8], "20mm mark 244-0 ELC": [194, 194], "BGM-109 TLAM": [1, 1], "RGM-84F Harpoon": [8, 8], "RUM-139 Mod4 ASROC": [1, 1], "127mm mk 80 HE-PD mk 67": [40, 40], "BGM-109 TASM": [1, 1]}}')
    leader_id = UI.LookupFriendlyId('USS George Washington')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(3.985, 0.500, -2.341, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Nicholson', 'SH-60B', 'Spruance VLS 93 DDG Seahawk 301', 1)
    SM.SetFlightDeckUnitLoadout('USS Nicholson', 'Spruance VLS 93 DDG Seahawk 301', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Nicholson', 'SH-60B', 'Spruance VLS 93 DDG Seahawk 302', 1)
    SM.SetFlightDeckUnitLoadout('USS Nicholson', 'Spruance VLS 93 DDG Seahawk 302', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Spruance DDG VLS 93'
    unit.unitName = "USS Cushing"
    UI = SM.GetUnitInterface('USS George Washington')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0507
    lat_deg = 57.296*leader_track.Lat + 0.0364
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 309.83
    unit.speed = 4.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RUM-139 Mod4 ASROC', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'BGM-109 TASM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'BGM-109 TLAM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'RIM-116A RAM', 21)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Cushing", '120 gallon tank', 6)
    SM.AddToUnitMagazine("USS Cushing", 'AGM-114 Hellfire', 24)
    SM.AddToUnitMagazine("USS Cushing", 'AGM-119B', 4)
    SM.AddToUnitMagazine("USS Cushing", 'Chaff-1', 150)
    SM.AddToUnitMagazine("USS Cushing", 'DICASS (95) Sonobuoy', 253)
    SM.AddToUnitMagazine("USS Cushing", 'DIFAR (95) Sonobuoy', 758)
    SM.AddToUnitMagazine("USS Cushing", 'Flare-1', 150)
    SM.AddToUnitMagazine("USS Cushing", 'Fuel', 65095)
    SM.AddToUnitMagazine("USS Cushing", 'LOFAR (95) Sonobuoy', 253)
    SM.AddToUnitMagazine("USS Cushing", 'Mk-46 Mod5', 19)
    SM.AddToUnitMagazine("USS Cushing", 'Mk-50', 2)
    SM.AddToUnitMagazine("USS Cushing", 'BGM-109 TASM', 5)
    SM.AddToUnitMagazine("USS Cushing", 'BGM-109 TLAM', 38)
    SM.AddToUnitMagazine("USS Cushing", 'RUM-139 Mod4 ASROC', 15)
    SM.AddToUnitMagazine("USS Cushing", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Cushing", 'RIM-116A RAM', 42)
    SM.AddToUnitMagazine("USS Cushing", '127mm mk 80 HE-PD mk 67', 1200)
    UI.SetSensorState(6, 0)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"RIM-7F": 0, "RIM-7E": 0, "RIM-116B RAM": 0, "RIM-7H": 0, "RIM-7M(v1)": 0, "RIM-162D": 0, "127mm mk 80 HE-PD mk 67": 2400, "127mm mk 127 HE-CVT EX-175": 0, "BGM-109 TASM": 15, "BGM-109G TLAM-N": 0, "127mm mk 80 HE-PD EX-175": 0, "RUM-139 Mod4 ASROC": 45, "RGM-84C Harpoon": 0, "RIM-116A RAM": 42, "RIM-7P(v1)": 0, "127mm mk 127 HE-CVT mk 67": 0, "RGM-84G Harpoon": 0, "20mm mark 244-0 ELC": 2092, "BGM-109 TLAM": 114, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "ASPIDE-1A": 0, "RGM-84A Harpoon": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 1, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 1, "WeaponList": {"RIM-116A RAM": [21, 21], "RIM-7P(v1)": [8, 8], "20mm mark 244-0 ELC": [194, 194], "BGM-109 TLAM": [1, 1], "RGM-84F Harpoon": [8, 8], "RUM-139 Mod4 ASROC": [1, 1], "127mm mk 80 HE-PD mk 67": [40, 40], "BGM-109 TASM": [1, 1]}}')
    leader_id = UI.LookupFriendlyId('USS George Washington')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(5.962, 0.666, -0.906, 0.119)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Cushing', 'SH-60B', 'Spruance VLS 93 DDG Seahawk 201', 1)
    SM.SetFlightDeckUnitLoadout('USS Cushing', 'Spruance VLS 93 DDG Seahawk 201', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Cushing', 'SH-60B', 'Spruance VLS 93 DDG Seahawk 202', 1)
    SM.SetFlightDeckUnitLoadout('USS Cushing', 'Spruance VLS 93 DDG Seahawk 202', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ticonderoga CG Baseline 4'
    unit.unitName = "USS Vicksburg"
    UI = SM.GetUnitInterface('USS George Washington')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0032
    lat_deg = 57.296*leader_track.Lat + 0.0215
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -49.65
    unit.speed = 4.9
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-156', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Vicksburg", '120 gallon tank', 6)
    SM.AddToUnitMagazine("USS Vicksburg", 'AGM-114 Hellfire', 24)
    SM.AddToUnitMagazine("USS Vicksburg", 'AGM-119B', 4)
    SM.AddToUnitMagazine("USS Vicksburg", 'Chaff-1', 125)
    SM.AddToUnitMagazine("USS Vicksburg", 'DICASS (95) Sonobuoy', 193)
    SM.AddToUnitMagazine("USS Vicksburg", 'DIFAR (95) Sonobuoy', 578)
    SM.AddToUnitMagazine("USS Vicksburg", 'Flare-1', 125)
    SM.AddToUnitMagazine("USS Vicksburg", 'Fuel', 56117)
    SM.AddToUnitMagazine("USS Vicksburg", 'LOFAR (95) Sonobuoy', 193)
    SM.AddToUnitMagazine("USS Vicksburg", 'Mk-46 Mod5', 29)
    SM.AddToUnitMagazine("USS Vicksburg", 'Mk-50', 3)
    SM.AddToUnitMagazine("USS Vicksburg", 'RIM-156', 24)
    SM.AddToUnitMagazine("USS Vicksburg", 'RIM-66M', 90)
    SM.AddToUnitMagazine("USS Vicksburg", 'RUM-139 Mod4 ASROC', 8)
    SM.AddToUnitMagazine("USS Vicksburg", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Vicksburg", '127mm mk 80 HE-PD mk 67', 1200)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 1, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"127mm mk 80 HE-PD EX-175": 0, "RIM-66H": 0, "Mk-54": 0, "RIM-162A": 0, "RIM-66M": 270, "Stingray": 0, "127mm mk 80 HE-PD mk 67": 2400, "RIM-66C": 0, "127mm mk 127 HE-CVT EX-175": 0, "BGM-109 TASM": 0, "BGM-109G TLAM-N": 0, "MU-90": 0, "RUM-139 Mod4 ASROC": 24, "RIM-7P(v2)": 0, "RGM-84C Harpoon": 0, "Mk-50": 6, "RIM-156": 72, "127mm mk 127 HE-CVT mk 67": 0, "RGM-84G Harpoon": 0, "20mm mark 244-0 ELC": 2092, "BGM-109 TLAM": 0, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "Mk-46 Mod5": 58, "Mk-15 Mod0": 0, "RGM-84A Harpoon": 0, "Mk-44": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 1, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 1, "WeaponList": {"20mm mark 244-0 ELC": [194, 194], "RIM-156": [1, 1], "RGM-84F Harpoon": [8, 8], "Mk-46 Mod5": [6, 6], "RIM-66M": [2, 2], "127mm mk 80 HE-PD mk 67": [40, 40]}}')
    leader_id = UI.LookupFriendlyId('USS George Washington')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(2.025, 0.500, -0.009, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Vicksburg', 'SH-60B', 'Tico Seahawk 201', 1)
    SM.SetFlightDeckUnitLoadout('USS Vicksburg', 'Tico Seahawk 201', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Vicksburg', 'SH-60B', 'Tico Seahawk 202', 1)
    SM.SetFlightDeckUnitLoadout('USS Vicksburg', 'Tico Seahawk 202', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Spruance DDG VLS 93'
    unit.unitName = "USS Moosbrugger"
    UI = SM.GetUnitInterface('USS Abraham Lincoln')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0506
    lat_deg = 57.296*leader_track.Lat + -0.0211
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 118.90
    unit.speed = 5.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RUM-139 Mod4 ASROC', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'BGM-109 TASM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'BGM-109 TLAM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'RIM-116A RAM', 21)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Moosbrugger", '120 gallon tank', 6)
    SM.AddToUnitMagazine("USS Moosbrugger", 'AGM-114 Hellfire', 24)
    SM.AddToUnitMagazine("USS Moosbrugger", 'AGM-119B', 4)
    SM.AddToUnitMagazine("USS Moosbrugger", 'Chaff-1', 150)
    SM.AddToUnitMagazine("USS Moosbrugger", 'DICASS (95) Sonobuoy', 253)
    SM.AddToUnitMagazine("USS Moosbrugger", 'DIFAR (95) Sonobuoy', 758)
    SM.AddToUnitMagazine("USS Moosbrugger", 'Flare-1', 150)
    SM.AddToUnitMagazine("USS Moosbrugger", 'Fuel', 65095)
    SM.AddToUnitMagazine("USS Moosbrugger", 'LOFAR (95) Sonobuoy', 253)
    SM.AddToUnitMagazine("USS Moosbrugger", 'Mk-46 Mod5', 19)
    SM.AddToUnitMagazine("USS Moosbrugger", 'Mk-50', 2)
    SM.AddToUnitMagazine("USS Moosbrugger", 'BGM-109 TASM', 5)
    SM.AddToUnitMagazine("USS Moosbrugger", 'BGM-109 TLAM', 38)
    SM.AddToUnitMagazine("USS Moosbrugger", 'RUM-139 Mod4 ASROC', 15)
    SM.AddToUnitMagazine("USS Moosbrugger", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Moosbrugger", 'RIM-116A RAM', 42)
    SM.AddToUnitMagazine("USS Moosbrugger", '127mm mk 80 HE-PD mk 67', 1200)
    UI.SetSensorState(6, 0)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 5, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"RIM-7F": 0, "RIM-7E": 0, "RIM-116B RAM": 0, "RIM-7H": 0, "RIM-7M(v1)": 0, "RIM-162D": 0, "127mm mk 80 HE-PD mk 67": 2400, "127mm mk 127 HE-CVT EX-175": 0, "BGM-109 TASM": 15, "BGM-109G TLAM-N": 0, "127mm mk 80 HE-PD EX-175": 0, "RUM-139 Mod4 ASROC": 45, "RGM-84C Harpoon": 0, "RIM-116A RAM": 42, "RIM-7P(v1)": 0, "127mm mk 127 HE-CVT mk 67": 0, "RGM-84G Harpoon": 0, "20mm mark 244-0 ELC": 2092, "BGM-109 TLAM": 114, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "ASPIDE-1A": 0, "RGM-84A Harpoon": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 1, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 1, "WeaponList": {"RIM-116A RAM": [21, 21], "RIM-7P(v1)": [8, 8], "20mm mark 244-0 ELC": [194, 194], "BGM-109 TLAM": [1, 1], "RGM-84F Harpoon": [8, 8], "RUM-139 Mod4 ASROC": [1, 1], "127mm mk 80 HE-PD mk 67": [40, 40], "BGM-109 TASM": [1, 1]}}')
    leader_id = UI.LookupFriendlyId('USS Abraham Lincoln')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(4.970, 0.755, 2.171, 0.161)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Moosbrugger', 'SH-60B', 'Spruance VLS 93 DDG Seahawk 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Moosbrugger', 'Spruance VLS 93 DDG Seahawk 101', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Moosbrugger', 'SH-60B', 'Spruance VLS 93 DDG Seahawk 102', 1)
    SM.SetFlightDeckUnitLoadout('USS Moosbrugger', 'Spruance VLS 93 DDG Seahawk 102', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Spruance DDG VLS 93'
    unit.unitName = "USS Fletcher"
    UI = SM.GetUnitInterface('USS Abraham Lincoln')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0563
    lat_deg = 57.296*leader_track.Lat + -0.0082
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 118.90
    unit.speed = 5.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RUM-139 Mod4 ASROC', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'BGM-109 TASM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'BGM-109 TLAM', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, 'RIM-7P(v1)', 8)
    SM.SetUnitLauncherItem(unit.unitName, 4, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 5, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'RIM-116A RAM', 21)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Fletcher", '120 gallon tank', 6)
    SM.AddToUnitMagazine("USS Fletcher", 'AGM-114 Hellfire', 24)
    SM.AddToUnitMagazine("USS Fletcher", 'AGM-119B', 4)
    SM.AddToUnitMagazine("USS Fletcher", 'Chaff-1', 150)
    SM.AddToUnitMagazine("USS Fletcher", 'DICASS (95) Sonobuoy', 253)
    SM.AddToUnitMagazine("USS Fletcher", 'DIFAR (95) Sonobuoy', 758)
    SM.AddToUnitMagazine("USS Fletcher", 'Flare-1', 150)
    SM.AddToUnitMagazine("USS Fletcher", 'Fuel', 65095)
    SM.AddToUnitMagazine("USS Fletcher", 'LOFAR (95) Sonobuoy', 253)
    SM.AddToUnitMagazine("USS Fletcher", 'Mk-46 Mod5', 23)
    SM.AddToUnitMagazine("USS Fletcher", 'Mk-50', 2)
    SM.AddToUnitMagazine("USS Fletcher", 'BGM-109 TASM', 5)
    SM.AddToUnitMagazine("USS Fletcher", 'BGM-109 TLAM', 38)
    SM.AddToUnitMagazine("USS Fletcher", 'RUM-139 Mod4 ASROC', 15)
    SM.AddToUnitMagazine("USS Fletcher", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Fletcher", 'RIM-116A RAM', 42)
    SM.AddToUnitMagazine("USS Fletcher", '127mm mk 80 HE-PD mk 67', 1200)
    UI.SetSensorState(6, 0)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 5, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"RIM-7F": 0, "RIM-7E": 0, "RIM-116B RAM": 0, "RIM-7H": 0, "RIM-7M(v1)": 0, "RIM-162D": 0, "127mm mk 80 HE-PD mk 67": 2400, "127mm mk 127 HE-CVT EX-175": 0, "BGM-109 TASM": 15, "BGM-109G TLAM-N": 0, "127mm mk 80 HE-PD EX-175": 0, "RUM-139 Mod4 ASROC": 45, "RGM-84C Harpoon": 0, "RIM-116A RAM": 42, "RIM-7P(v1)": 0, "127mm mk 127 HE-CVT mk 67": 0, "RGM-84G Harpoon": 0, "20mm mark 244-0 ELC": 2092, "BGM-109 TLAM": 114, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "ASPIDE-1A": 0, "RGM-84A Harpoon": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 1, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 1, "WeaponList": {"RIM-116A RAM": [21, 21], "RIM-7P(v1)": [8, 8], "20mm mark 244-0 ELC": [194, 194], "BGM-109 TLAM": [1, 1], "RGM-84F Harpoon": [8, 8], "RUM-139 Mod4 ASROC": [1, 1], "127mm mk 80 HE-PD mk 67": [40, 40], "BGM-109 TASM": [1, 1]}}')
    leader_id = UI.LookupFriendlyId('USS Abraham Lincoln')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(5.022, 0.844, -1.846, 0.179)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Fletcher', 'SH-60B', 'Spruance VLS 93 DDG Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Fletcher', 'Spruance VLS 93 DDG Seahawk 1', '0 Empty;1 120 gallon tank;0 Empty;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Fletcher', 'SH-60B', 'Spruance VLS 93 DDG Seahawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Fletcher', 'Spruance VLS 93 DDG Seahawk 2', '0 Empty;1 120 gallon tank;0 Empty;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Arleigh Burke DDGHM'
    unit.unitName = "USS Fitzgerald"
    UI = SM.GetUnitInterface('USS Abraham Lincoln')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0858
    lat_deg = 57.296*leader_track.Lat + 0.0680
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 118.90
    unit.speed = 5.1
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-156', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, '127mm mk 127 HE-CVT mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Fitzgerald", 'Fuel', 28058)
    SM.AddToUnitMagazine("USS Fitzgerald", 'Mk-46 Mod5', 12)
    SM.AddToUnitMagazine("USS Fitzgerald", 'BGM-109 TLAM', 30)
    SM.AddToUnitMagazine("USS Fitzgerald", 'RIM-156', 8)
    SM.AddToUnitMagazine("USS Fitzgerald", 'RIM-66M', 40)
    SM.AddToUnitMagazine("USS Fitzgerald", 'RUM-139 Mod4 ASROC', 12)
    SM.AddToUnitMagazine("USS Fitzgerald", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Fitzgerald", '127mm mk 127 HE-CVT mk 67', 680)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 5, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"127mm mk 80 HE-PD EX-175": 0, "RIM-66H": 0, "Mk-54": 0, "RIM-162A": 0, "RIM-66M": 120, "Stingray": 0, "127mm mk 80 HE-PD mk 67": 0, "RIM-66C": 0, "127mm mk 127 HE-CVT EX-175": 0, "BGM-109 TASM": 0, "BGM-109G TLAM-N": 0, "MU-90": 0, "RUM-139 Mod4 ASROC": 36, "RIM-7P(v2)": 0, "RGM-84C Harpoon": 0, "Mk-50": 0, "RIM-156": 24, "127mm mk 127 HE-CVT mk 67": 680, "RGM-84G Harpoon": 0, "20mm mark 244-0 ELC": 2092, "BGM-109 TLAM": 90, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "Mk-46 Mod5": 24, "Mk-15 Mod0": 0, "RGM-84A Harpoon": 0, "Mk-44": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 1, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 1, "WeaponList": {"20mm mark 244-0 ELC": [194, 194], "RIM-156": [1, 1], "RGM-84F Harpoon": [8, 8], "Mk-46 Mod5": [6, 6], "RIM-66M": [2, 2], "127mm mk 127 HE-CVT mk 67": [20, 20]}}')
    leader_id = UI.LookupFriendlyId('USS Abraham Lincoln')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(10.020, 0.625, 0.778, 0.087)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Arleigh Burke II DDGHM'
    unit.unitName = "USS Porter"
    UI = SM.GetUnitInterface('USS Bonhomme Richard')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0252
    lat_deg = 57.296*leader_track.Lat + 0.0942
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -10.89
    unit.speed = 15.4
    unit.cost = 1000000000.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-156', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, '127mm mk 127 HE-CVT mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Porter", 'Fuel', 28058)
    SM.AddToUnitMagazine("USS Porter", 'Mk-46 Mod5', 12)
    SM.AddToUnitMagazine("USS Porter", 'BGM-109 TLAM', 30)
    SM.AddToUnitMagazine("USS Porter", 'RIM-156', 8)
    SM.AddToUnitMagazine("USS Porter", 'RIM-66M', 40)
    SM.AddToUnitMagazine("USS Porter", 'RUM-139 Mod4 ASROC', 12)
    SM.AddToUnitMagazine("USS Porter", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Porter", '127mm mk 127 HE-CVT mk 67', 680)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"127mm mk 80 HE-PD EX-175": 0, "RIM-66H": 0, "Mk-54": 0, "RIM-162A": 0, "RIM-66M": 120, "Stingray": 0, "127mm mk 80 HE-PD mk 67": 0, "RIM-66C": 0, "127mm mk 127 HE-CVT EX-175": 0, "BGM-109 TASM": 0, "BGM-109G TLAM-N": 0, "MU-90": 0, "RUM-139 Mod4 ASROC": 36, "RIM-7P(v2)": 0, "RGM-84C Harpoon": 0, "Mk-50": 0, "RIM-156": 24, "127mm mk 127 HE-CVT mk 67": 680, "RGM-84G Harpoon": 0, "20mm mark 244-0 ELC": 2092, "BGM-109 TLAM": 90, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "Mk-46 Mod5": 24, "Mk-15 Mod0": 0, "RGM-84A Harpoon": 0, "Mk-44": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 1, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 1, "WeaponList": {"20mm mark 244-0 ELC": [194, 194], "RIM-156": [1, 1], "RGM-84F Harpoon": [8, 8], "Mk-46 Mod5": [6, 6], "RIM-66M": [2, 2], "127mm mk 127 HE-CVT mk 67": [20, 20]}}')
    leader_id = UI.LookupFriendlyId('USS Bonhomme Richard')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(10.016, 1.648, -0.258, 0.135)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ticonderoga CG Baseline 4'
    unit.unitName = "USS Chosin"
    UI = SM.GetUnitInterface('USS Abraham Lincoln')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0034
    lat_deg = 57.296*leader_track.Lat + 0.0258
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = 118.90
    unit.speed = 5.1
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-156', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Chosin", '120 gallon tank', 6)
    SM.AddToUnitMagazine("USS Chosin", 'AGM-114 Hellfire', 24)
    SM.AddToUnitMagazine("USS Chosin", 'AGM-119B', 4)
    SM.AddToUnitMagazine("USS Chosin", 'Chaff-1', 125)
    SM.AddToUnitMagazine("USS Chosin", 'DICASS (95) Sonobuoy', 193)
    SM.AddToUnitMagazine("USS Chosin", 'DIFAR (95) Sonobuoy', 578)
    SM.AddToUnitMagazine("USS Chosin", 'Flare-1', 125)
    SM.AddToUnitMagazine("USS Chosin", 'Fuel', 56117)
    SM.AddToUnitMagazine("USS Chosin", 'LOFAR (95) Sonobuoy', 203)
    SM.AddToUnitMagazine("USS Chosin", 'Mk-46 Mod5', 29)
    SM.AddToUnitMagazine("USS Chosin", 'Mk-50', 3)
    SM.AddToUnitMagazine("USS Chosin", 'RIM-156', 24)
    SM.AddToUnitMagazine("USS Chosin", 'RIM-66M', 90)
    SM.AddToUnitMagazine("USS Chosin", 'RUM-139 Mod4 ASROC', 8)
    SM.AddToUnitMagazine("USS Chosin", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Chosin", '127mm mk 80 HE-PD mk 67', 1200)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 5, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"127mm mk 80 HE-PD EX-175": 0, "RIM-66H": 0, "Mk-54": 0, "RIM-162A": 0, "RIM-66M": 270, "Stingray": 0, "127mm mk 80 HE-PD mk 67": 2400, "RIM-66C": 0, "127mm mk 127 HE-CVT EX-175": 0, "BGM-109 TASM": 0, "BGM-109G TLAM-N": 0, "MU-90": 0, "RUM-139 Mod4 ASROC": 24, "RIM-7P(v2)": 0, "RGM-84C Harpoon": 0, "Mk-50": 6, "RIM-156": 72, "127mm mk 127 HE-CVT mk 67": 0, "RGM-84G Harpoon": 0, "20mm mark 244-0 ELC": 2092, "BGM-109 TLAM": 0, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "Mk-46 Mod5": 58, "Mk-15 Mod0": 0, "RGM-84A Harpoon": 0, "Mk-44": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 1, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 1, "WeaponList": {"20mm mark 244-0 ELC": [194, 194], "RIM-156": [1, 1], "RGM-84F Harpoon": [8, 8], "Mk-46 Mod5": [6, 6], "RIM-66M": [2, 2], "127mm mk 80 HE-PD mk 67": [40, 40]}}')
    leader_id = UI.LookupFriendlyId('USS Abraham Lincoln')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(2.480, 0.500, 0.097, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Chosin', 'SH-60B', 'Tico Seahawk 101', 1)
    SM.SetFlightDeckUnitLoadout('USS Chosin', 'Tico Seahawk 101', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;0 Empty;15 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Chosin', 'SH-60B', 'Tico Seahawk 102', 1)
    SM.SetFlightDeckUnitLoadout('USS Chosin', 'Tico Seahawk 102', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;0 Empty;15 DIFAR (95) Sonobuoy;')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Lewis and Clark'
    unit.unitName = "USNS Sacagawea"
    UI = SM.GetUnitInterface('USS Bonhomme Richard')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0394
    lat_deg = 57.296*leader_track.Lat + -0.0090
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -10.89
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USNS Sacagawea", 'Fuel', 1000000)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Bonhomme Richard')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(3.536, 0.500, 1.989, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USNS Sacagawea', 'SA-330J', 'Puma101', 1)
    SM.SetFlightDeckUnitLoadout('USNS Sacagawea', 'Puma101', '')
    
    SM.AddUnitToFlightDeck('USNS Sacagawea', 'SA-330J', 'Puma102', 1)
    SM.SetFlightDeckUnitLoadout('USNS Sacagawea', 'Puma102', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Lewis and Clark'
    unit.unitName = "USNS Lewis and Clark"
    UI = SM.GetUnitInterface('USS Bonhomme Richard')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0181
    lat_deg = 57.296*leader_track.Lat + -0.0245
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -10.89
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USNS Lewis and Clark", 'Fuel', 1000000)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Bonhomme Richard')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(3.527, 0.500, -2.652, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USNS Lewis and Clark', 'SA-330J', 'Puma1', 1)
    SM.SetFlightDeckUnitLoadout('USNS Lewis and Clark', 'Puma1', '')
    
    SM.AddUnitToFlightDeck('USNS Lewis and Clark', 'SA-330J', 'Puma2', 1)
    SM.SetFlightDeckUnitLoadout('USNS Lewis and Clark', 'Puma2', '')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Converted Raleigh AGFH'
    unit.unitName = "La Salle"
    UI = SM.GetUnitInterface('USS Bonhomme Richard')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0282
    lat_deg = 57.296*leader_track.Lat + -0.0004
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -10.89
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 1, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 2, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 5, '25mm APDS', 400)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("La Salle", '.50 cal bullet', 12000)
    SM.AddToUnitMagazine("La Salle", '25mm APDS', 8000)
    SM.AddToUnitMagazine("La Salle", '20mm mark 244-0 ELC', 1046)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Bonhomme Richard')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(2.518, 0.500, -1.699, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Harpers Ferry LSD-CV'
    unit.unitName = "USS Oak Hill"
    UI = SM.GetUnitInterface('USS Bonhomme Richard')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0338
    lat_deg = 57.296*leader_track.Lat + 0.0264
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -10.89
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 2, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 3, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 4, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 5, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 9, '25mm APDS', 400)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Oak Hill", '.50 cal bullet', 24000)
    SM.AddToUnitMagazine("USS Oak Hill", '25mm APDS', 8000)
    SM.AddToUnitMagazine("USS Oak Hill", 'RIM-116A RAM', 42)
    SM.AddToUnitMagazine("USS Oak Hill", '20mm mark 244-0 ELC', 1046)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Bonhomme Richard')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(3.988, 0.500, -0.840, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Harpers Ferry LSD-CV'
    unit.unitName = "USS Harpers Ferry"
    UI = SM.GetUnitInterface('USS Bonhomme Richard')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + -0.0002
    lat_deg = 57.296*leader_track.Lat + 0.0334
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -10.89
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 2, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 3, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 4, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 5, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 9, '25mm APDS', 400)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Harpers Ferry", '.50 cal bullet', 24000)
    SM.AddToUnitMagazine("USS Harpers Ferry", '25mm APDS', 8000)
    SM.AddToUnitMagazine("USS Harpers Ferry", 'RIM-116A RAM', 42)
    SM.AddToUnitMagazine("USS Harpers Ferry", '20mm mark 244-0 ELC', 1046)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Bonhomme Richard')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(3.444, 0.500, -0.034, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Whidbey Island LSDHM'
    unit.unitName = "USS Fort McHenry"
    UI = SM.GetUnitInterface('USS Bonhomme Richard')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0233
    lat_deg = 57.296*leader_track.Lat + 0.0411
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -10.89
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-116A RAM', 21)
    SM.SetUnitLauncherItem(unit.unitName, 2, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 3, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 4, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 5, '.50 cal bullet', 600)
    SM.SetUnitLauncherItem(unit.unitName, 6, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 7, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 8, '25mm APDS', 400)
    SM.SetUnitLauncherItem(unit.unitName, 9, '25mm APDS', 400)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Fort McHenry", '.50 cal bullet', 24000)
    SM.AddToUnitMagazine("USS Fort McHenry", '25mm APDS', 8000)
    SM.AddToUnitMagazine("USS Fort McHenry", 'RIM-116A RAM', 84)
    SM.AddToUnitMagazine("USS Fort McHenry", '20mm mark 244-0 ELC', 1046)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    leader_id = UI.LookupFriendlyId('USS Bonhomme Richard')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(4.598, 0.500, 0.433, 0.200)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ticonderoga CG Baseline 3'
    unit.unitName = "USS Princeton"
    UI = SM.GetUnitInterface('USS Bonhomme Richard')
    leader_track = UI.GetTrackById(UI.GetPlatformId())
    lon_deg = 57.296*leader_track.Lon + 0.0611
    lat_deg = 57.296*leader_track.Lat + 0.0459
    unit.SetPosition(lon_deg, lat_deg, 0.0)
    unit.heading = -10.89
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 1)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'RIM-156', 1)
    SM.SetUnitLauncherItem(unit.unitName, 1, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 2, 'RIM-66M', 1)
    SM.SetUnitLauncherItem(unit.unitName, 3, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 4, '20mm mark 244-0 ELC', 97)
    SM.SetUnitLauncherItem(unit.unitName, 5, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 6, 'RGM-84F Harpoon', 4)
    SM.SetUnitLauncherItem(unit.unitName, 7, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 8, '127mm mk 80 HE-PD mk 67', 20)
    SM.SetUnitLauncherItem(unit.unitName, 9, 'Mk-46 Mod5', 3)
    SM.SetUnitLauncherItem(unit.unitName, 10, 'Mk-46 Mod5', 3)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("USS Princeton", '120 gallon tank', 6)
    SM.AddToUnitMagazine("USS Princeton", 'AGM-114 Hellfire', 24)
    SM.AddToUnitMagazine("USS Princeton", 'AGM-119B', 4)
    SM.AddToUnitMagazine("USS Princeton", 'DICASS (95) Sonobuoy', 193)
    SM.AddToUnitMagazine("USS Princeton", 'DIFAR (95) Sonobuoy', 578)
    SM.AddToUnitMagazine("USS Princeton", 'Fuel', 56117)
    SM.AddToUnitMagazine("USS Princeton", 'LOFAR (95) Sonobuoy', 193)
    SM.AddToUnitMagazine("USS Princeton", 'Mk-46 Mod5', 29)
    SM.AddToUnitMagazine("USS Princeton", 'Mk-50', 3)
    SM.AddToUnitMagazine("USS Princeton", 'Chaff-1', 100)
    SM.AddToUnitMagazine("USS Princeton", 'Flare-1', 100)
    SM.AddToUnitMagazine("USS Princeton", 'RIM-156', 24)
    SM.AddToUnitMagazine("USS Princeton", 'RIM-66M', 90)
    SM.AddToUnitMagazine("USS Princeton", 'RUM-139 Mod4 ASROC', 8)
    SM.AddToUnitMagazine("USS Princeton", '20mm mark 244-0 ELC', 1046)
    SM.AddToUnitMagazine("USS Princeton", '127mm mk 80 HE-PD mk 67', 1200)
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
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 1, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"127mm mk 80 HE-PD EX-175": 0, "RIM-66H": 0, "Mk-54": 0, "RIM-162A": 0, "RIM-66M": 270, "Stingray": 0, "127mm mk 80 HE-PD mk 67": 2400, "RIM-66C": 0, "127mm mk 127 HE-CVT EX-175": 0, "BGM-109 TASM": 0, "BGM-109G TLAM-N": 0, "MU-90": 0, "RUM-139 Mod4 ASROC": 24, "RIM-7P(v2)": 0, "RGM-84C Harpoon": 0, "Mk-50": 6, "RIM-156": 72, "127mm mk 127 HE-CVT mk 67": 0, "RGM-84G Harpoon": 0, "20mm mark 244-0 ELC": 2092, "BGM-109 TLAM": 0, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "Mk-46 Mod5": 58, "Mk-15 Mod0": 0, "RGM-84A Harpoon": 0, "Mk-44": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 0, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 1, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 1, "TargetSet": 0, "FormModePace": 1, "WeaponList": {"20mm mark 244-0 ELC": [194, 194], "RIM-156": [1, 1], "RGM-84F Harpoon": [8, 8], "Mk-46 Mod5": [6, 6], "RIM-66M": [2, 2], "127mm mk 80 HE-PD mk 67": [40, 40]}}')
    leader_id = UI.LookupFriendlyId('USS Bonhomme Richard')
    UI.SetFormationLeader(leader_id)
    UI.SetFormationMode(1)
    UI.SetFormationPosition(6.972, 0.571, 0.809, 0.116)
    UI.SetFormationAltitudeOffset(0.0)
    UI.SetFormationUseNorthBearing(1)
    
    SM.AddUnitToFlightDeck('USS Princeton', 'SH-60B', 'Tico Seahawk 1', 1)
    SM.SetFlightDeckUnitLoadout('USS Princeton', 'Tico Seahawk 1', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    SM.AddUnitToFlightDeck('USS Princeton', 'SH-60B', 'Tico Seahawk 2', 1)
    SM.SetFlightDeckUnitLoadout('USS Princeton', 'Tico Seahawk 2', '1 Mk-46 Mod5;1 120 gallon tank;1 Mk-46 Mod5;25 Chaff-1;25 Flare-1;5 DICASS (95) Sonobuoy;5 LOFAR (95) Sonobuoy;15 DIFAR (95) Sonobuoy;')
    
    ##############################
    ### Alliance 2 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Smuggler5"
    unit.SetPosition(17.090967, 41.277223, 0.0)
    unit.heading = -21.16
    unit.speed = 16.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.284475, 0.746943, 0.000000, 17.000000)
    UI.AddNavWaypointAdvanced(0.287746, 0.750843, 0.000000, 17.000000)
    UI.AddNavWaypointAdvanced(0.290631, 0.751367, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Smuggler4"
    unit.SetPosition(17.695146, 42.492320, 0.0)
    unit.heading = -78.09
    unit.speed = 11.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.291748, 0.744286, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.288483, 0.748840, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.288654, 0.750990, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.290500, 0.751356, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Smuggler3"
    unit.SetPosition(15.486768, 42.001271, 0.0)
    unit.heading = 38.17
    unit.speed = 14.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.289392, 0.750966, 0.000000, 14.000000)
    UI.AddNavWaypointAdvanced(0.290602, 0.751321, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "Smuggler2"
    unit.SetPosition(14.440921, 44.322334, 0.0)
    unit.heading = 135.04
    unit.speed = 10.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.267660, 0.762321, 0.000000, 11.000000)
    UI.AddNavWaypointAdvanced(0.284694, 0.752638, 0.000000, 11.000000)
    UI.AddNavWaypointAdvanced(0.290503, 0.751414, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'General Cargo'
    unit.unitName = "Smuggler1"
    unit.SetPosition(13.797553, 43.428732, 0.0)
    unit.heading = 97.23
    unit.speed = 13.7
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.279077, 0.754443, 0.000000, 14.000000)
    UI.AddNavWaypointAdvanced(0.286965, 0.751860, 0.000000, 14.000000)
    UI.AddNavWaypointAdvanced(0.290619, 0.751428, 0.000000, 0.000000)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-X(6) (Generic)'
    unit.unitName = "Silkworm-3"
    unit.SetPosition(18.517366, 42.461845, -0.0)
    unit.heading = 213.69
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'HY-1A', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Silkworm-3", 'HY-1A', 6)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-X(6) (Generic)'
    unit.unitName = "Silkworm-2"
    unit.SetPosition(18.859536, 42.282796, 0.0)
    unit.heading = 216.87
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'HY-1A', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Silkworm-2", 'HY-1A', 6)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'TPS-70 Radar Post'
    unit.unitName = "Radar-6"
    unit.SetPosition(18.753825, 43.239349, 5436.2)
    unit.heading = 197.10
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'TPS-70 Radar Post'
    unit.unitName = "Radar-5"
    unit.SetPosition(20.311640, 42.809057, 3519.9)
    unit.heading = 197.10
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'TPS-70 Radar Post'
    unit.unitName = "Radar-4"
    unit.SetPosition(19.880260, 45.151309, 3037.9)
    unit.heading = 197.10
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'TPS-70 Radar Post'
    unit.unitName = "Radar-3"
    unit.SetPosition(20.515613, 44.690307, 2622.3)
    unit.heading = 197.10
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'TPS-70 Radar Post'
    unit.unitName = "Radar-2"
    unit.SetPosition(19.175866, 42.114633, 1372.4)
    unit.heading = 197.10
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'TPS-70 Radar Post'
    unit.unitName = "Radar-1"
    unit.SetPosition(18.810491, 42.393434, 1.0)
    unit.heading = 211.61
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V1 Shilka'
    unit.unitName = "ZSU-23-9"
    unit.SetPosition(18.728860, 42.447606, -0.0)
    unit.heading = 200.22
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V1 Shilka'
    unit.unitName = "ZSU-23-8"
    unit.SetPosition(18.614784, 42.461357, -0.0)
    unit.heading = 200.22
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V1 Shilka'
    unit.unitName = "ZSU-23-7"
    unit.SetPosition(19.022621, 42.182212, 0.1)
    unit.heading = 200.22
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V1 Shilka'
    unit.unitName = "ZSU-23-6"
    unit.SetPosition(19.081979, 42.148923, 0.1)
    unit.heading = 200.22
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V1 Shilka'
    unit.unitName = "ZSU-23-5"
    unit.SetPosition(21.114600, 42.410249, 0.0)
    unit.heading = 200.22
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V1 Shilka'
    unit.unitName = "ZSU-23-4"
    unit.SetPosition(20.542578, 44.448604, -0.0)
    unit.heading = 200.22
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V1 Shilka'
    unit.unitName = "ZSU-23-3"
    unit.SetPosition(20.345994, 44.533574, -0.0)
    unit.heading = 200.22
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V1 Shilka'
    unit.unitName = "ZSU-23-2"
    unit.SetPosition(19.648406, 45.136784, 0.0)
    unit.heading = 200.22
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'ZSU-23-4V1 Shilka'
    unit.unitName = "ZSU-23-1"
    unit.SetPosition(19.525506, 45.127444, -0.0)
    unit.heading = 200.22
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '23mm OFZ', 25)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gas Processing Plant'
    unit.unitName = "Chemical Wpns Plant-9"
    unit.SetPosition(19.515630, 45.156523, 3816.9)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gas Processing Plant'
    unit.unitName = "Chemical Wpns Plant-8"
    unit.SetPosition(20.239963, 44.507648, 3732.6)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gas Processing Plant'
    unit.unitName = "Chemical Wpns Plant-7"
    unit.SetPosition(20.192866, 44.159003, 3396.6)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gas Processing Plant'
    unit.unitName = "Chemical Wpns Plant-6"
    unit.SetPosition(20.386812, 43.472886, 2567.7)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gas Processing Plant'
    unit.unitName = "Chemical Wpns Plant-5"
    unit.SetPosition(20.725316, 43.176954, 2120.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gas Processing Plant'
    unit.unitName = "Chemical Wpns Plant-4"
    unit.SetPosition(21.263724, 43.461599, 1903.5)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gas Processing Plant'
    unit.unitName = "Chemical Wpns Plant-3"
    unit.SetPosition(20.454765, 42.842117, 222.3)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gas Processing Plant'
    unit.unitName = "Chemical Wpns Plant-2"
    unit.SetPosition(19.079208, 42.195248, 95.9)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Gas Processing Plant'
    unit.unitName = "Chemical Wpns Plant-1"
    unit.SetPosition(18.699853, 42.476455, 1.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-21"
    unit.SetPosition(18.744372, 42.452907, 11888.7)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-20"
    unit.SetPosition(18.670976, 42.416524, 11869.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-19"
    unit.SetPosition(19.103215, 42.168892, 11251.2)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-18"
    unit.SetPosition(20.045215, 43.018817, 9881.9)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-17"
    unit.SetPosition(21.039010, 43.018817, 8560.1)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-16"
    unit.SetPosition(21.940559, 42.805849, 7357.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-15"
    unit.SetPosition(21.479042, 43.417825, 6665.9)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-14"
    unit.SetPosition(20.799056, 43.381958, 5712.4)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-13"
    unit.SetPosition(20.512863, 43.581405, 4701.8)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-12"
    unit.SetPosition(21.297701, 43.903751, 4436.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-11"
    unit.SetPosition(20.532401, 44.303389, 3895.8)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-10"
    unit.SetPosition(20.543459, 44.138262, 2950.7)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-9"
    unit.SetPosition(20.296113, 44.062517, 2413.5)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-8"
    unit.SetPosition(19.752605, 44.134882, 1255.4)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-7"
    unit.SetPosition(20.401652, 44.474130, 1083.1)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-6"
    unit.SetPosition(20.337080, 44.493382, 946.3)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-5"
    unit.SetPosition(20.277206, 44.512576, 860.7)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-4"
    unit.SetPosition(19.634347, 45.182764, 610.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-3"
    unit.SetPosition(19.574473, 45.168326, 349.9)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-2"
    unit.SetPosition(19.520959, 45.198406, 190.7)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Weapons Factory-1"
    unit.SetPosition(19.470538, 45.166091, 1.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-13"
    unit.SetPosition(20.476538, 44.422621, 3136.5)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-12"
    unit.SetPosition(19.477127, 45.212558, 3002.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-11"
    unit.SetPosition(19.436161, 45.163513, 2767.1)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-10"
    unit.SetPosition(19.563759, 45.141225, 2443.2)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-9"
    unit.SetPosition(20.300754, 44.453274, 2265.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-8"
    unit.SetPosition(20.432878, 44.497908, 2076.3)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-7"
    unit.SetPosition(20.311870, 44.560532, 1929.8)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-6"
    unit.SetPosition(21.251692, 43.914580, 1748.3)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-5"
    unit.SetPosition(21.018269, 42.415149, 1053.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-4"
    unit.SetPosition(19.098288, 42.109476, 997.8)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-3"
    unit.SetPosition(19.043169, 42.169006, 288.6)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-2"
    unit.SetPosition(18.595746, 42.452850, 24.2)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ammunition Bunker'
    unit.unitName = "Ammo Bunker-1"
    unit.SetPosition(18.666621, 42.451646, 1.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'POL Tank'
    unit.unitName = "POL Tank-6"
    unit.SetPosition(19.074682, 42.111768, 989.1)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'POL Tank'
    unit.unitName = "POL Tank-5"
    unit.SetPosition(19.082531, 42.135145, 371.9)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'POL Tank'
    unit.unitName = "POL Tank-4"
    unit.SetPosition(19.011656, 42.165511, 270.7)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'POL Tank'
    unit.unitName = "POL Tank-3"
    unit.SetPosition(18.555925, 42.441276, 1.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'POL Tank'
    unit.unitName = "POL Tank-2"
    unit.SetPosition(18.707588, 42.423629, 32.6)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'POL Tank'
    unit.unitName = "POL Tank-1"
    unit.SetPosition(18.693436, 42.401455, 1.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Command Center-8"
    unit.SetPosition(21.339011, 43.877509, 3261.8)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Command Center-7"
    unit.SetPosition(20.746687, 43.382703, 2641.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Command Center-6"
    unit.SetPosition(20.077473, 43.229207, 1573.8)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Command Center-5"
    unit.SetPosition(21.042047, 42.382147, 773.2)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Command Center-4"
    unit.SetPosition(19.037038, 42.204988, 334.9)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Command Center-3"
    unit.SetPosition(18.666392, 42.494332, 303.4)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Command Center-2"
    unit.SetPosition(20.310151, 44.513320, 177.9)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Army HQ Bunker'
    unit.unitName = "Command Center-1"
    unit.SetPosition(19.491566, 45.185744, 1.0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-22"
    unit.SetPosition(19.728541, 44.125485, 0.0)
    unit.heading = 210.26
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-22", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-21"
    unit.SetPosition(18.704551, 44.627626, 0.0)
    unit.heading = 210.26
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-21", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-20"
    unit.SetPosition(20.975297, 42.359515, 0.0)
    unit.heading = 210.26
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-20", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-19"
    unit.SetPosition(20.430071, 42.811235, -0.0)
    unit.heading = 210.26
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-19", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-18"
    unit.SetPosition(21.950472, 42.762992, -0.0)
    unit.heading = 146.31
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-18", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-17"
    unit.SetPosition(20.538245, 44.122277, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-17", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-16"
    unit.SetPosition(20.475392, 43.561122, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-16", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-15"
    unit.SetPosition(20.778143, 43.307875, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-15", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-14"
    unit.SetPosition(19.420920, 43.374567, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-14", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-13"
    unit.SetPosition(20.001728, 43.009765, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-13", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-12"
    unit.SetPosition(21.013456, 42.978710, 0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-12", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-11"
    unit.SetPosition(18.929666, 42.227276, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-11", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-10"
    unit.SetPosition(19.179705, 42.061348, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-10", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-9"
    unit.SetPosition(18.789807, 42.390283, -0.1)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-9", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 0, "Alt+": 0, "Speed+": 0, "RadarMast+": 0, "RadarMast-": 0, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 1, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 0, "Launchers": 1, "Periscope-": 0, "FixedWing": 0, "MagWeaponList": {"5V55R": 288, "5V55RUD": 0, "5V55RD": 0}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 0, "MobileLand": 1, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 0, "HasThrottle": 0, "PeriDeep": 0, "Sub": 0, "HasSonarA": 0, "HasFlightPort": 0, "HasMagazine": 1, "DieselSub": 0, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 0, "TargetTrack": 0, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 0, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"EngageAllAir": 1}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 0, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"5V55R": [16, 16]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-8"
    unit.SetPosition(18.533810, 42.560508, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-8", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-7"
    unit.SetPosition(20.529021, 44.289523, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-7", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-6"
    unit.SetPosition(20.399532, 44.432820, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-6", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-5"
    unit.SetPosition(20.216816, 44.473557, 0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-5", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-4"
    unit.SetPosition(19.716853, 45.240518, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-4", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-3"
    unit.SetPosition(19.644718, 45.047088, 0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-3", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-2"
    unit.SetPosition(19.314064, 45.104212, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-2", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'S-300PM'
    unit.unitName = "SA-10-1"
    unit.SetPosition(19.497582, 45.270771, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '5V55R', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '5V55R', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-10-1", '5V55R', 72)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K37M1 Buk-M1'
    unit.unitName = "SA-11-7"
    unit.SetPosition(21.453946, 43.389693, 0.0)
    unit.heading = 153.43
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M38M1', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-11-7", '9M39M1', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K37M1 Buk-M1'
    unit.unitName = "SA-11-6"
    unit.SetPosition(20.289582, 44.047162, 0.0)
    unit.heading = 200.56
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M38M1', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-11-6", '9M39M1', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K37M1 Buk-M1'
    unit.unitName = "SA-11-5"
    unit.SetPosition(21.294320, 43.848575, -0.0)
    unit.heading = 216.87
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M38M1', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-11-5", '9M39M1', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K37M1 Buk-M1'
    unit.unitName = "SA-11-4"
    unit.SetPosition(19.676173, 45.145350, 0.0)
    unit.heading = 228.01
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M38M1', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-11-4", '9M39M1', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K37M1 Buk-M1'
    unit.unitName = "SA-11-3"
    unit.SetPosition(20.564028, 44.460265, -0.0)
    unit.heading = 219.81
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M38M1', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-11-3", '9M39M1', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K37M1 Buk-M1'
    unit.unitName = "SA-11-2"
    unit.SetPosition(19.000541, 42.194446, -0.0)
    unit.heading = 204.44
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M38M1', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-11-2", '9M39M1', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '9K37M1 Buk-M1'
    unit.unitName = "SA-11-1"
    unit.SetPosition(18.571224, 42.500291, -0.0)
    unit.heading = 225.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 4, '9M38M1', 4)
    SM.SetUnitLauncherItem(unit.unitName, 5, '9M38M1', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-11-1", '9M39M1', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(1, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '2K12E Kvadrat'
    unit.unitName = "SA-6-8"
    unit.SetPosition(19.914464, 44.798683, 0.0)
    unit.heading = 214.99
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '3M9M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-6-8", '3M9M', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(5, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '2K12E Kvadrat'
    unit.unitName = "SA-6-7"
    unit.SetPosition(18.953865, 43.950598, -0.0)
    unit.heading = 236.31
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '3M9M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-6-7", '3M9M', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(5, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '2K12E Kvadrat'
    unit.unitName = "SA-6-6"
    unit.SetPosition(20.055299, 43.193163, 0.0)
    unit.heading = 180.00
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '3M9M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-6-6", '3M9M', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(5, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '2K12E Kvadrat'
    unit.unitName = "SA-6-5"
    unit.SetPosition(19.054481, 42.133952, -0.0)
    unit.heading = 209.05
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '3M9M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-6-5", '3M9M', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(5, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '2K12E Kvadrat'
    unit.unitName = "SA-6-4"
    unit.SetPosition(18.607174, 42.413083, 0.0)
    unit.heading = 216.03
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '3M9M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-6-4", '3M9M', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(5, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '2K12E Kvadrat'
    unit.unitName = "SA-6-3"
    unit.SetPosition(20.268761, 44.537789, -0.0)
    unit.heading = 209.74
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '3M9M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-6-3", '3M9M', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(5, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '2K12E Kvadrat'
    unit.unitName = "SA-6-2"
    unit.SetPosition(19.488838, 45.091924, -0.0)
    unit.heading = 221.63
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '3M9M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-6-2", '3M9M', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(5, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = '2K12E Kvadrat'
    unit.unitName = "SA-6-1"
    unit.SetPosition(19.419525, 45.200545, 0.0)
    unit.heading = 221.19
    unit.speed = 3.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 1, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 2, '3M9M', 4)
    SM.SetUnitLauncherItem(unit.unitName, 3, '3M9M', 4)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("SA-6-1", '3M9M', 48)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(5, 1)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Belgrade AB"
    unit.SetPosition(20.267180, 44.559902, 0.0)
    unit.heading = 270.00
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Belgrade AB", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Belgrade AB", '1150 Liter Tank', 16)
    SM.AddToUnitMagazine("Belgrade AB", '1520 Liter Tank', 8)
    SM.AddToUnitMagazine("Belgrade AB", '23mm GSh-23 HEI', 685)
    SM.AddToUnitMagazine("Belgrade AB", '30mm NR-30 HEI', 449)
    SM.AddToUnitMagazine("Belgrade AB", 'Chaff-1', 5713)
    SM.AddToUnitMagazine("Belgrade AB", 'FAB-100', 241)
    SM.AddToUnitMagazine("Belgrade AB", 'FAB-250', 205)
    SM.AddToUnitMagazine("Belgrade AB", 'FAB-500', 138)
    SM.AddToUnitMagazine("Belgrade AB", 'Flare-1', 5713)
    SM.AddToUnitMagazine("Belgrade AB", 'KAB-500KRU', 15)
    SM.AddToUnitMagazine("Belgrade AB", 'KAB-500Kr', 57)
    SM.AddToUnitMagazine("Belgrade AB", 'KAB-500R', 29)
    SM.AddToUnitMagazine("Belgrade AB", 'Kh-25ML', 36)
    SM.AddToUnitMagazine("Belgrade AB", 'Kh-25MP', 76)
    SM.AddToUnitMagazine("Belgrade AB", 'Kh-31P', 152)
    SM.AddToUnitMagazine("Belgrade AB", 'Kh-35U', 29)
    SM.AddToUnitMagazine("Belgrade AB", 'Kh-59', 36)
    SM.AddToUnitMagazine("Belgrade AB", 'Kh-59M', 35)
    SM.AddToUnitMagazine("Belgrade AB", 'PTB-400', 48)
    SM.AddToUnitMagazine("Belgrade AB", 'PTB-490', 36)
    SM.AddToUnitMagazine("Belgrade AB", 'R-27R', 259)
    SM.AddToUnitMagazine("Belgrade AB", 'R-27RE', 114)
    SM.AddToUnitMagazine("Belgrade AB", 'R-27T', 243)
    SM.AddToUnitMagazine("Belgrade AB", 'R-27TE', 98)
    SM.AddToUnitMagazine("Belgrade AB", 'R-33', 68)
    SM.AddToUnitMagazine("Belgrade AB", 'R-60M', 234)
    SM.AddToUnitMagazine("Belgrade AB", 'R-60MK', 152)
    SM.AddToUnitMagazine("Belgrade AB", 'R-73', 226)
    SM.AddToUnitMagazine("Belgrade AB", 'R-73M', 132)
    SM.AddToUnitMagazine("Belgrade AB", 'R-77', 363)
    SM.AddToUnitMagazine("Belgrade AB", 'R-77T', 239)
    SM.AddToUnitMagazine("Belgrade AB", 'S-24B 240mm', 182)
    SM.AddToUnitMagazine("Belgrade AB", 'S-5K 57mm', 5850)
    SM.AddToUnitMagazine("Belgrade AB", 'S-5K Rocket', 5850)
    SM.AddToUnitMagazine("Belgrade AB", 'S-5M Rocket', 5850)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('InvMulti', '1')
    BB.Write('MagTonnage', '35')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-1', 3)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-1', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-2', 3)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-2', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-3', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-3', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-4', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-4', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-5', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-5', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-6', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-6', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-7', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-7', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-8', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-8', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-9', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-9', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-10', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-10', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-11', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-11', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-21-93', 'Bel Figher-12', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Figher-12', '1 R-73;1 R-77;15 23mm GSh-23 HEI;1 PTB-800;1 R-77;1 R-73;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-29ME', 'Bel AAW-1', 3)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel AAW-1', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-29ME', 'Bel AAW-2', 3)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel AAW-2', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-29ME', 'Bel AAW-3', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel AAW-3', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-29ME', 'Bel AAW-4', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel AAW-4', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-29ME', 'Bel AAW-5', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel AAW-5', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-29ME', 'Bel AAW-6', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel AAW-6', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-29ME', 'Bel AAW-7', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel AAW-7', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-29ME', 'Bel AAW-8', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel AAW-8', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-23', 'Bel Fighter1-1', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Fighter1-1', '2 R-24R;4 R-60M;2 PTB-800;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-23', 'Bel Fighter1-2', 2)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Fighter1-2', '2 R-24R;4 R-60M;2 PTB-800;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-23', 'Bel Fighter1-3', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Fighter1-3', '2 R-24R;4 R-60M;2 PTB-800;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-23', 'Bel Fighter1-4', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Fighter1-4', '2 R-24R;4 R-60M;2 PTB-800;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-23', 'Bel Fighter1-5', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Fighter1-5', '2 R-24R;4 R-60M;2 PTB-800;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-23', 'Bel Fighter1-6', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Fighter1-6', '2 R-24R;4 R-60M;2 PTB-800;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-23', 'Bel Fighter1-7', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Fighter1-7', '2 R-24R;4 R-60M;2 PTB-800;')
    
    SM.AddUnitToFlightDeck('Belgrade AB', 'MiG-23', 'Bel Fighter1-8', 1)
    SM.SetFlightDeckUnitLoadout('Belgrade AB', 'Bel Fighter1-8', '2 R-24R;4 R-60M;2 PTB-800;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Bel Figher-1')
    FP.AddAircraftToMission(mission_id, 'Bel Figher-2')
    FP.AddAircraftToMission(mission_id, 'Bel Figher-3')
    FP.AddAircraftToMission(mission_id, 'Bel Figher-4')
    FP.AddAircraftToMission(mission_id, 'Bel Figher-5')
    FP.AddAircraftToMission(mission_id, 'Bel Figher-6')
    FP.SetMissionLaunchTime(mission_id, '00:00:30+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 3)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0137547,-0.0021495,-0.0460634,-0.0088049,-0.0402781,-0.0345438,-0.0100690,-0.0249293,')
    FP.SetMissionPatrolAnchor(mission_id, 'Belgrade AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3505210, 0.7776460, 10000.0, 336.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3612830, 0.7714470, 10000.0, 336.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAllAir,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Bel Figher-7')
    FP.AddAircraftToMission(mission_id, 'Bel Figher-8')
    FP.AddAircraftToMission(mission_id, 'Bel Figher-9')
    FP.AddAircraftToMission(mission_id, 'Bel Figher-10')
    FP.AddAircraftToMission(mission_id, 'Bel Figher-11')
    FP.AddAircraftToMission(mission_id, 'Bel Figher-12')
    FP.SetMissionLaunchTime(mission_id, '01:30:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 3)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0137547,-0.0021495,-0.0460634,-0.0088049,-0.0402781,-0.0345438,-0.0100690,-0.0249293,')
    FP.SetMissionPatrolAnchor(mission_id, 'Belgrade AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3505210, 0.7776460, 10000.0, 336.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3612830, 0.7714470, 10000.0, 336.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAllAir,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Bel AAW-1')
    FP.AddAircraftToMission(mission_id, 'Bel AAW-2')
    FP.AddAircraftToMission(mission_id, 'Bel AAW-3')
    FP.AddAircraftToMission(mission_id, 'Bel AAW-4')
    FP.SetMissionLaunchTime(mission_id, '00:01:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Default')
    FP.SetMissionPatrolArea(mission_id, '-0.0141842,0.0270513,-0.0437761,-0.0053780,-0.0342888,-0.0237033,-0.0102646,-0.0138010,')
    FP.SetMissionPatrolAnchor(mission_id, 'Belgrade AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3506300, 0.7777170, 12000.0, 388.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3535060, 0.7643060, 12000.0, 388.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,RadarOn,EngageAllAir')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Bel AAW-5')
    FP.AddAircraftToMission(mission_id, 'Bel AAW-6')
    FP.AddAircraftToMission(mission_id, 'Bel AAW-7')
    FP.AddAircraftToMission(mission_id, 'Bel AAW-8')
    FP.SetMissionLaunchTime(mission_id, '01:31:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, 'Default')
    FP.SetMissionPatrolArea(mission_id, '-0.0141842,0.0270513,-0.0437761,-0.0053780,-0.0342888,-0.0237033,-0.0102646,-0.0138010,')
    FP.SetMissionPatrolAnchor(mission_id, 'Belgrade AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3506300, 0.7777170, 12000.0, 388.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3535060, 0.7643060, 12000.0, 388.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,RadarOn,EngageAllAir')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Bel Fighter1-1')
    FP.AddAircraftToMission(mission_id, 'Bel Fighter1-2')
    FP.AddAircraftToMission(mission_id, 'Bel Fighter1-3')
    FP.AddAircraftToMission(mission_id, 'Bel Fighter1-4')
    FP.SetMissionLaunchTime(mission_id, '00:05:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0222380,0.0211633,-0.0329703,0.0329769,-0.0483224,0.0172000,-0.0372300,0.0060044,')
    FP.SetMissionPatrolAnchor(mission_id, 'Belgrade AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3506290, 0.7773220, 10000.0, 334.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3509290, 0.7743140, 10000.0, 334.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAllAir,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Bel Fighter1-5')
    FP.AddAircraftToMission(mission_id, 'Bel Fighter1-6')
    FP.AddAircraftToMission(mission_id, 'Bel Fighter1-7')
    FP.AddAircraftToMission(mission_id, 'Bel Fighter1-8')
    FP.SetMissionLaunchTime(mission_id, '01:35:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0222380,0.0211633,-0.0329703,0.0329769,-0.0483224,0.0172000,-0.0372300,0.0060044,')
    FP.SetMissionPatrolAnchor(mission_id, 'Belgrade AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3506290, 0.7773220, 10000.0, 334.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAllAir,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3509290, 0.7743140, 10000.0, 334.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAllAir,RadarOn')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Novi Sod AB"
    unit.SetPosition(19.440401, 45.217715, 0.0)
    unit.heading = 300.96
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitAlwaysVisibleState(unit.unitName, 1)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Novi Sod AB", 'Fuel', 1000000)
    SM.AddToUnitMagazine("Novi Sod AB", '1150 Liter Tank', 20)
    SM.AddToUnitMagazine("Novi Sod AB", '1520 Liter Tank', 10)
    SM.AddToUnitMagazine("Novi Sod AB", '23mm GSh-23 HEI', 1071)
    SM.AddToUnitMagazine("Novi Sod AB", '30mm NR-30 HEI', 395)
    SM.AddToUnitMagazine("Novi Sod AB", 'Chaff-1', 7592)
    SM.AddToUnitMagazine("Novi Sod AB", 'FAB-100', 313)
    SM.AddToUnitMagazine("Novi Sod AB", 'FAB-250', 241)
    SM.AddToUnitMagazine("Novi Sod AB", 'FAB-500', 170)
    SM.AddToUnitMagazine("Novi Sod AB", 'Flare-1', 7592)
    SM.AddToUnitMagazine("Novi Sod AB", 'KAB-500KRU', 14)
    SM.AddToUnitMagazine("Novi Sod AB", 'KAB-500Kr', 75)
    SM.AddToUnitMagazine("Novi Sod AB", 'KAB-500R', 29)
    SM.AddToUnitMagazine("Novi Sod AB", 'Kh-25ML', 35)
    SM.AddToUnitMagazine("Novi Sod AB", 'Kh-25MP', 101)
    SM.AddToUnitMagazine("Novi Sod AB", 'Kh-31P', 202)
    SM.AddToUnitMagazine("Novi Sod AB", 'Kh-35U', 28)
    SM.AddToUnitMagazine("Novi Sod AB", 'Kh-59', 35)
    SM.AddToUnitMagazine("Novi Sod AB", 'Kh-59M', 35)
    SM.AddToUnitMagazine("Novi Sod AB", 'PTB-400', 96)
    SM.AddToUnitMagazine("Novi Sod AB", 'PTB-490', 72)
    SM.AddToUnitMagazine("Novi Sod AB", 'R-27R', 258)
    SM.AddToUnitMagazine("Novi Sod AB", 'R-27RE', 151)
    SM.AddToUnitMagazine("Novi Sod AB", 'R-27T', 238)
    SM.AddToUnitMagazine("Novi Sod AB", 'R-27TE', 131)
    SM.AddToUnitMagazine("Novi Sod AB", 'R-33', 107)
    SM.AddToUnitMagazine("Novi Sod AB", 'R-60M', 327)
    SM.AddToUnitMagazine("Novi Sod AB", 'R-60MK', 148)
    SM.AddToUnitMagazine("Novi Sod AB", 'R-73', 259)
    SM.AddToUnitMagazine("Novi Sod AB", 'R-73M', 138)
    SM.AddToUnitMagazine("Novi Sod AB", 'R-77', 427)
    SM.AddToUnitMagazine("Novi Sod AB", 'R-77T', 234)
    SM.AddToUnitMagazine("Novi Sod AB", 'S-24B 240mm', 285)
    SM.AddToUnitMagazine("Novi Sod AB", 'S-5K 57mm', 9146)
    SM.AddToUnitMagazine("Novi Sod AB", 'S-5K Rocket', 9146)
    SM.AddToUnitMagazine("Novi Sod AB", 'S-5M Rocket', 9146)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('InvMulti', '1')
    BB.Write('MagTonnage', '35')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-1', 3)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-1', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-2', 3)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-2', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-3', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-3', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-4', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-4', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-5', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-5', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-6', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-6', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-7', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-7', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-8', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-8', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-9', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-9', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-10', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-10', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-11', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-11', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-12', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-12', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-13', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-13', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-14', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-14', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-15', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-15', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-16', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-16', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-17', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-17', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-18', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-18', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-19', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-19', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-20', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-20', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-21', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-21', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-22', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-22', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-23', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-23', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-21-93', 'Novi Fighters-24', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi Fighters-24', '1 R-77;1 R-73;15 23mm GSh-23 HEI;1 PTB-800;1 R-73;1 R-77;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-29ME', 'Novi -1', 3)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi -1', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-29ME', 'Novi -2', 3)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi -2', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-29ME', 'Novi -3', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi -3', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-29ME', 'Novi -4', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi -4', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-29ME', 'Novi -5', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi -5', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-29ME', 'Novi -6', 2)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi -6', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-29ME', 'Novi -7', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi -7', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-29ME', 'Novi -8', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi -8', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-29ME', 'Novi -9', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi -9', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    
    SM.AddUnitToFlightDeck('Novi Sod AB', 'MiG-29ME', 'Novi -10', 1)
    SM.SetFlightDeckUnitLoadout('Novi Sod AB', 'Novi -10', '1 1520 Liter Tank;2 R-27TE;2 R-77;2 R-77;2 R-73;20 30mm NR-30 HEI;30 Chaff-1;30 Flare-1;')
    FP = UI.GetFlightPortInfo()
    base_track = UI.GetTrackById(UI.GetPlatformId())
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-1')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-2')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-3')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-4')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-5')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-6')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-7')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-8')
    FP.SetMissionLaunchTime(mission_id, '00:00:30+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0393872,0.0341236,-0.0526701,0.0004423,-0.0312061,-0.0119545,-0.0217620,0.0153919,')
    FP.SetMissionPatrolAnchor(mission_id, 'Novi Sod AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3363100, 0.7897470, 10000.0, 334.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'RadarOn,EngageAllAir')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3325860, 0.7902050, 10000.0, 334.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAllAir,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-9')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-10')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-11')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-12')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-13')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-14')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-15')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-16')
    FP.SetMissionLaunchTime(mission_id, '01:30:30+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0393872,0.0341236,-0.0526701,0.0004423,-0.0312061,-0.0119545,-0.0217620,0.0153919,')
    FP.SetMissionPatrolAnchor(mission_id, 'Novi Sod AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3363100, 0.7897470, 10000.0, 334.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'RadarOn,EngageAllAir')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3325860, 0.7902050, 10000.0, 334.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAllAir,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-17')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-18')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-19')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-20')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-21')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-22')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-23')
    FP.AddAircraftToMission(mission_id, 'Novi Fighters-24')
    FP.SetMissionLaunchTime(mission_id, '02:00:30+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 4)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '-0.0393872,0.0341236,-0.0526701,0.0004423,-0.0312061,-0.0119545,-0.0217620,0.0153919,')
    FP.SetMissionPatrolAnchor(mission_id, 'Novi Sod AB', 2)
    FP.AddMissionWaypointAdvanced(mission_id, 0.3363100, 0.7897470, 10000.0, 334.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'RadarOn,EngageAllAir')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3325860, 0.7902050, 10000.0, 334.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAllAir,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Novi -1')
    FP.AddAircraftToMission(mission_id, 'Novi -2')
    FP.AddAircraftToMission(mission_id, 'Novi -3')
    FP.AddAircraftToMission(mission_id, 'Novi -4')
    FP.AddAircraftToMission(mission_id, 'Novi -5')
    FP.SetMissionLaunchTime(mission_id, '00:01:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.3028927,0.7871861,0.3574671,0.7565247,0.3692669,0.7666665,0.3184620,0.7954410,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3374320, 0.7902430, 12000.0, 388.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3349500, 0.7904130, 12000.0, 388.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RadarOn')
    
    mission_id = FP.AddGenericMission()
    FP.AddAircraftToMission(mission_id, 'Novi -6')
    FP.AddAircraftToMission(mission_id, 'Novi -7')
    FP.AddAircraftToMission(mission_id, 'Novi -8')
    FP.AddAircraftToMission(mission_id, 'Novi -9')
    FP.AddAircraftToMission(mission_id, 'Novi -10')
    FP.SetMissionLaunchTime(mission_id, '01:01:00+0m+R0.1')
    FP.SetMissionDatum(mission_id, 0.0000000, 0.0000000)
    FP.SetMissionLandingTarget(mission_id, '')
    FP.SetMissionWaveQuantity(mission_id, 2)
    FP.SetMissionType(mission_id, '')
    FP.SetMissionPatrolArea(mission_id, '0.3028927,0.7871861,0.3574671,0.7565247,0.3692669,0.7666665,0.3184620,0.7954410,')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3374320, 0.7902430, 12000.0, 388.0)
    FP.SetMissionWaypointTasks(mission_id, 0, 'EngageAll,RadarOn')
    FP.AddMissionWaypointAdvanced(mission_id, 0.3349500, 0.7904130, 12000.0, 388.0)
    FP.SetMissionWaypointTasks(mission_id, 1, 'AirPatrolArea,EngageAll,RadarOn')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'SSC-X(6) (Generic)'
    unit.unitName = "Silkworm-1"
    unit.SetPosition(19.169163, 41.959246, -0.0)
    unit.heading = 197.10
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 2)
    SM.SetUnitLauncherItem(unit.unitName, 0, 'HY-1A', 6)
    UI = SM.GetUnitInterface(unit.unitName)
    SM.AddToUnitMagazine("Silkworm-1", 'HY-1A', 6)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('EngageAllAir', 2.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Pr 877M Paltus'
    unit.unitName = "B-464"
    unit.SetPosition(18.732517, 41.787995, -100.0)
    unit.heading = 270.00
    unit.speed = 2.1
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
    SM.AddToUnitMagazine("B-464", 'SET-65M', 8)
    SM.AddToUnitMagazine("B-464", '53-65M', 4)
    SM.AddToUnitMagazine("B-464", '9M32M Strela 3', 6)
    UI.SetSensorState(0, 0)
    UI.SetSensorState(4, 0)
    UI.AddTask('AvoidCav', 3.000000, 3)
    UI.AddTask('EngageAll', 2.000000, 0)
    UI.AddTask('PatrolCircle', 1.000000, 0)
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
    BB.Write('ID_EngageLimit', '{"146.0": 0.0, "154.0": 0.0, "155.0": 0.0, "174.0": 0.0, "164.0": 0.0, "147.0": 0.0, "176.0": 0.0, "159.0": 0.0, "175.0": 0.0, "163.0": 0.0, "162.0": 0.0, "158.0": 0.0, "161.0": 0.0, "160.0": 0.0, "153.0": 0.0, "168.0": 0.0, "152.0": 0.0, "151.0": 0.0, "143.0": 0.0, "177.0": 0.0, "150.0": 0.0, "156.0": 0.0, "157.0": 0.0, "170.0": 0.0, "171.0": 0.0, "165.0": 0.0, "149.0": 0.0, "173.0": 0.0, "148.0": 0.0, "144.0": 0.0, "145.0": 0.0}')
    BB.Write('Selected', '{"RotaryWing": 0, "Speed-": 10, "Alt+": 0, "Speed+": 10, "RadarMast+": 0, "RadarMast-": 1, "34_EngageLimit": "1", "257_EngageLimit": "24", "17_EngageLimit": "6", "UnitCount": 120, "HasECM": 0, "HasTarget": 0, "TargetDatum": 0, "Alliance0_EngageLimit": -1, "FixedLand": 65, "Launchers": 1, "Periscope-": 1, "FixedWing": 0, "MagWeaponList": {"YJ-12": 0, "SAET-60M": 0, "P-20K": 0, "Noor": 0, "YJ-62K": 0, "MM-40 B2 Exocet": 0, "HY-2A": 0, "HY-2B": 0, "YJ-61": 0, "YJ-63": 0, "Kh-35": 0, "C-201": 0, "P-21R": 0, "C-803": 0, "C-802": 0, "RBS-15M Mk2": 0, "RBS-15M Mk3": 0, "RGM-84G Harpoon": 0, "P-20 Rubezh": 0, "P-15U Termit": 0, "JJ-10": 0, "RGM-84A Harpoon": 0, "3M10 Granat": 0, "YJ-6": 0, "YJ-7": 0, "USET-80": 0, "YJ-1": 0, "3M9M": 1536, "C-803K": 0, "FL-10": 0, "TEST-71ME": 0, "C-602": 0, "C-601": 0, "SET-65M": 48, "FL-2": 0, "FL-9": 0, "FL-8": 0, "C-802A": 0, "YJ-83K": 0, "P-120 Malakhit": 0, "TEST-71MKE": 0, "RBS-15F Mk2": 0, "YJ-82K": 0, "3M54 Klub Alfa": 0, "C-101": 0, "5V55RUD": 0, "Otomat Mk-2": 0, "TL-6": 0, "3M80 Moskit": 0, "Otomat Mk-1": 0, "C-611": 0, "Hsiung Feng-II": 0, "C-802K": 0, "P-20M Rubezh": 0, "AS.37 Martel": 0, "5V55RD": 0, "P-27": 0, "P-15M Termit": 0, "P-15 Termit": 0, "5V55R": 6336, "YJ-82A": 0, "3M54 Warhead Section": 0, "HY-1J": 0, "3M54E Klub Alfa": 0, "C-201W": 0, "C-602K": 0, "9M38M1": 0, "9M32M Strela 3": 6, "23mm OFZ": 0, "HY-2AII": 0, "3M24E Uran-E": 0, "P-15T Termit": 0, "MM-38 Exocet": 0, "3M45 Granit": 0, "P-500 Bazalt": 0, "MM-40 Exocet": 0, "RGM-84C Harpoon": 0, "SET-65": 0, "JJ-6": 0, "53-56V": 0, "3M80M Moskit-M": 0, "YJ-82": 0, "53-65KE": 0, "P-800 Yakhont": 0, "SY-2": 0, "SY-1": 0, "RPK-6 Vodopod": 0, "53-56": 0, "9M39M1": 2016, "RGM-84D Harpoon": 0, "RGM-84F Harpoon": 0, "RBS-15F": 0, "HY-1A": 18, "HY-1JA": 0, "P-70 Ametist": 0, "RBS-15M": 0, "HY-4": 0, "SY-2A": 0, "HY-2": 0, "RBS-15K": 0, "YJ-62": 0, "C-401": 0, "BGM-109 TASM": 0, "NSM": 0, "HY-2BII": 0, "RBS-15K Mk2": 0, "RBS-15K Mk3": 0, "P-21 Termit": 0, "TEST-71": 0, "SY-1A": 0, "3M10 Granat(n)": 0, "C-704": 0, "C-705": 0, "C-703": 0, "C-701": 0, "YJ-83": 0, "MM-40 B3 Exocet": 0, "TL-10": 0, "Shkval": 0, "53-65M": 24}, "Air": 0, "64_EngageLimit": "1", "HasAIWeap": 0, "18_EngageLimit": "12", "256_EngageLimit": "2", "Depth+": 200.0, "MobileLand": 49, "CanStrafe": 0, "Depth-": 0, "HasSonarP": 1, "HasThrottle": 0, "PeriDeep": 0, "Sub": 1, "HasSonarA": 1, "HasFlightPort": 1, "HasMagazine": 1, "DieselSub": 1, "HasGBU": 0, "HasAINav": 0, "FormMember": 0, "Alliance1_EngageLimit": -1, "HasBombs": 0, "Snorkel-": 1, "TargetTrack": 1, "Snorkel+": 0, "16_EngageLimit": "4", "Alliance2_EngageLimit": -1, "258_EngageLimit": "2", "FormLeader": 0, "129_EngageLimit": "1", "HasESM": 1, "Periscope+": 0, "22_EngageLimit": "24", "FormModeSprint": 0, "32_EngageLimit": "1", "Tasks": {"Nav": 5, "PatrolCircle": 1, "EngageAllAir": 47, "EngageAll": 4}, "HasOptical": 1, "33_EngageLimit": "1", "HasRadar": 1, "Ship": 5, "TargetSet": 0, "FormModePace": 0, "WeaponList": {"9M38M1": [168, 168], "9M32M Strela 3": [1, 1], "3M9M": [128, 128], "5V55R": [352, 352], "23mm OFZ": [225, 225], "HY-1A": [18, 18], "SET-65M": [4, 4], "53-65M": [2, 2]}}')
    BB.Write('StationLatitude', '0.729358')
    BB.Write('StationLongitude', '0.326006')
    
    ##############################
    ### Alliance 3 units
    ##############################

    unit = SM.GetDefaultUnit()
    unit.className = 'LNG Carrier'
    unit.unitName = "LNG Tanker"
    unit.SetPosition(18.755484, 40.509198, 0.0)
    unit.heading = -44.01
    unit.speed = 11.6
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.217206, 0.790546, 0.000000, 12.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Freighter 5"
    unit.SetPosition(15.101580, 43.049960, 0.0)
    unit.heading = 137.31
    unit.speed = 11.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.312562, 0.711846, 0.000000, 11.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Freighter 4"
    unit.SetPosition(14.711306, 42.511708, 0.0)
    unit.heading = 97.04
    unit.speed = 11.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.329937, 0.735284, 0.000000, 11.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Freighter 3"
    unit.SetPosition(14.580133, 43.507034, 0.0)
    unit.heading = 130.00
    unit.speed = 11.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.334338, 0.709609, 0.000000, 11.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Freighter 2"
    unit.SetPosition(16.199080, 42.039012, 0.0)
    unit.heading = -31.19
    unit.speed = 11.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.244814, 0.779261, 0.000000, 11.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Freighter1"
    unit.SetPosition(15.128428, 43.785675, 0.0)
    unit.heading = -37.67
    unit.speed = 11.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.252943, 0.774531, 0.000000, 11.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Oil Tanker'
    unit.unitName = "BP Adventurer"
    unit.SetPosition(17.811112, 41.800612, 0.0)
    unit.heading = 153.84
    unit.speed = 12.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.332524, 0.696203, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.357903, 0.672688, 0.000000, 12.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Chemical Tanker'
    unit.unitName = "Hannes Z"
    unit.SetPosition(13.471224, 43.736298, 0.0)
    unit.heading = 100.99
    unit.speed = 18.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.SetSensorState(5, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.242547, 0.762299, 0.000000, 18.000000)
    UI.AddNavWaypointAdvanced(0.281671, 0.736997, 0.000000, 18.000000)
    UI.AddNavWaypointAdvanced(0.330039, 0.705374, 0.000000, 18.000000)
    UI.AddNavWaypointAdvanced(0.330167, 0.667273, 0.000000, 18.000000)
    UI.AddNavWaypointAdvanced(0.279567, 0.628148, 0.000000, 18.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ferry'
    unit.unitName = "Balkan Enterprise"
    unit.SetPosition(16.570901, 43.046364, 0.0)
    unit.heading = -124.44
    unit.speed = 16.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.258642, 0.735870, 0.000000, 16.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Ella B"
    unit.SetPosition(19.302896, 41.285410, 0.0)
    unit.heading = 0.27
    unit.speed = 4.3
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.336952, 0.728946, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'LNG Carrier'
    unit.unitName = "Exxon Traveler"
    unit.SetPosition(14.134009, 44.799463, 0.0)
    unit.heading = -165.79
    unit.speed = 11.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.244635, 0.776136, 0.000000, 11.000000)
    UI.AddNavWaypointAdvanced(0.268504, 0.747383, 0.000000, 11.000000)
    UI.AddNavWaypointAdvanced(0.340036, 0.727825, 0.000000, 11.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'General Cargo'
    unit.unitName = "Ralph T"
    unit.SetPosition(19.273221, 40.598478, 0.0)
    unit.heading = -50.67
    unit.speed = 12.2
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.273880, 0.746821, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.216276, 0.790572, 0.000000, 12.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Ferry'
    unit.unitName = "Palermo Maiden"
    unit.SetPosition(16.276618, 41.523787, 0.0)
    unit.heading = 112.72
    unit.speed = 12.5
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.336630, 0.708129, 0.000000, 12.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Boeing 747'
    unit.unitName = "IA 231"
    unit.SetPosition(30.042833, 40.790504, 8839.5)
    unit.heading = -81.38
    unit.speed = 426.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.110482, 0.758450, 10000.000000, 426.000000)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airbus A330'
    unit.unitName = "GA 1502"
    unit.SetPosition(15.884093, 45.249873, 5146.1)
    unit.heading = 144.91
    unit.speed = 464.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('AirEvade', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.438682, 0.614311, 10000.000000, 464.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('RTB', 2.000000, 3)
    BB = UI.GetBlackboardInterface()
    BB.Write('Home', 'Novi Sod Airport')
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Fishing Boat'
    unit.unitName = "Warrior"
    unit.SetPosition(15.242650, 43.572306, 0.0)
    unit.heading = 118.79
    unit.speed = 3.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.281539, 0.754290, 0.000000, 0.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'VLCC'
    unit.unitName = "Avia Carrier"
    unit.SetPosition(13.337463, 44.490713, 0.0)
    unit.heading = 137.24
    unit.speed = 11.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.273392, 0.744698, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.328359, 0.707636, 0.000000, 12.000000)
    UI.AddNavWaypointAdvanced(0.332384, 0.628781, 0.000000, 12.000000)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Container Ship'
    unit.unitName = "Maersk Challanger"
    unit.SetPosition(19.362521, 37.992150, 0.0)
    unit.heading = -8.94
    unit.speed = 15.8
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.328709, 0.708481, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.284562, 0.735670, 0.000000, 16.000000)
    UI.AddNavWaypointAdvanced(0.272066, 0.733662, 0.000000, 16.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Bulk Freighter'
    unit.unitName = "Wilma Jane"
    unit.SetPosition(17.008235, 40.404733, 0.0)
    unit.heading = 130.76
    unit.speed = 15.4
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(4, 1)
    UI.AddTask('MissileWarning', 3.000000, 3)
    UI.AddTask('Nav', 1.000000, 0)
    UI.AddNavWaypointAdvanced(0.317350, 0.691665, 0.000000, 15.000000)
    UI.AddNavWaypointAdvanced(0.327524, 0.695501, 0.000000, 15.000000)
    UI.AddNavWaypointAdvanced(0.331751, 0.734826, 0.000000, 15.000000)
    UI.SetNavLoopState(1)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Hospital1"
    unit.SetPosition(18.626457, 42.431536, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "School1"
    unit.SetPosition(18.641698, 42.444943, 36.2)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Hospital2"
    unit.SetPosition(19.060186, 42.126665, 62.7)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "School 2"
    unit.SetPosition(18.993608, 42.175595, 62.7)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "School 3"
    unit.SetPosition(21.121287, 42.446318, 238.4)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "School 4"
    unit.SetPosition(20.351690, 44.471380, 776.1)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "School 5"
    unit.SetPosition(19.457761, 45.129938, 907.6)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Hospital 3"
    unit.SetPosition(21.114755, 42.374412, 145.9)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Hospital 4"
    unit.SetPosition(20.383661, 44.499398, 733.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Hospital 5"
    unit.SetPosition(19.430202, 45.129078, 926.3)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Embassy1"
    unit.SetPosition(20.288722, 44.481579, 1.0)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Embassy 2"
    unit.SetPosition(20.274284, 44.481980, 91.5)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Embassy 3"
    unit.SetPosition(20.261220, 44.481521, 177.8)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Embassy 4"
    unit.SetPosition(20.261335, 44.485532, 262.4)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Embassy 5"
    unit.SetPosition(20.274398, 44.485360, 347.6)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Building'
    unit.unitName = "Embassy 6"
    unit.SetPosition(20.288951, 44.484844, 433.4)
    unit.heading = 90.00
    unit.speed = 0.0
    unit.cost = 0.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.AddTask('PointDefense', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    unit = SM.GetDefaultUnit()
    unit.className = 'Airstrip'
    unit.unitName = "Novi Sod Airport"
    unit.SetPosition(19.479992, 45.110514, -0.0)
    unit.heading = 228.01
    unit.speed = 0.0
    unit.cost = 20000000.0
    SM.AddUnitToAlliance(unit, 3)
    UI = SM.GetUnitInterface(unit.unitName)
    UI.SetSensorState(0, 1)
    UI.AddTask('RefuelAllAircraft', 3.000000, 3)
    BB = UI.GetBlackboardInterface()
    
    ##############################
    ### Alliance 1 goals
    ##############################

    goal_temp = SM.AreaGoal()
    goal_temp.SetTargetList('82nd ABN-1, 82nd ABN-2, 82nd ABN-3, 82nd ABN-4, 82nd ABN-5, 82nd ABN-6, 82nd ABN-7, 82nd ABN-8, 82nd ABN-9, 82nd ABN-10, 82nd ABN-11, 82nd ABN-12, 82nd ABN-13, 82nd ABN-14, 82nd ABN-15, 7th INF-1, 7th INF-2, 7th INF-3, 7th INF-4, 7th INF-5, 7th INF-6, 7th INF-7, 7th INF-8, 7th INF-9, 7th INF-10, 7th INF-11, 7th INF-12, 7th INF-13, 7th INF-14, 7th INF-15')
    goal_temp.SetTimeObjective(0.000000)
    goal_temp.SetLogicAny(0)
    goal_temp.SetQuantity(30)
    goal_temp.AddPointDeg(19.02832, 42.15691)
    goal_temp.AddPointDeg(19.02818, 42.14316)
    goal_temp.AddPointDeg(19.01073, 42.14316)
    goal_temp.AddPointDeg(19.01073, 42.15691)
    goal_2_0 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('SA-10-8')
    goal_temp.AddTarget('SA-6-4')
    goal_temp.AddTarget('SA-11-1')
    goal_temp.AddTarget('SA-10-9')
    goal_temp.AddTarget('Command Center-3')
    goal_temp.AddTarget('POL Tank-1')
    goal_temp.AddTarget('POL Tank-2')
    goal_temp.AddTarget('POL Tank-3')
    goal_temp.AddTarget('Ammo Bunker-1')
    goal_temp.AddTarget('Ammo Bunker-2')
    goal_temp.AddTarget('Weapons Factory-20')
    goal_temp.AddTarget('Weapons Factory-21')
    goal_temp.AddTarget('Chemical Wpns Plant-1')
    goal_temp.AddTarget('ZSU-23-8')
    goal_temp.AddTarget('ZSU-23-9')
    goal_temp.AddTarget('Radar-1')
    goal_temp.AddTarget('Silkworm-3')
    goal_temp.SetQuantity(17)
    goal_2_1 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Silkworm-1')
    goal_temp.AddTarget('SA-6-5')
    goal_temp.AddTarget('SA-11-2')
    goal_temp.AddTarget('SA-10-10')
    goal_temp.AddTarget('SA-10-11')
    goal_temp.AddTarget('Command Center-4')
    goal_temp.AddTarget('POL Tank-4')
    goal_temp.AddTarget('POL Tank-5')
    goal_temp.AddTarget('POL Tank-6')
    goal_temp.AddTarget('Ammo Bunker-3')
    goal_temp.AddTarget('Ammo Bunker-4')
    goal_temp.AddTarget('Weapons Factory-19')
    goal_temp.AddTarget('Chemical Wpns Plant-2')
    goal_temp.AddTarget('ZSU-23-6')
    goal_temp.AddTarget('ZSU-23-7')
    goal_temp.AddTarget('Radar-2')
    goal_temp.AddTarget('Silkworm-2')
    goal_temp.SetQuantity(17)
    goal_2_2 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('SA-10-20')
    goal_temp.AddTarget('Command Center-5')
    goal_temp.AddTarget('Ammo Bunker-5')
    goal_temp.AddTarget('ZSU-23-5')
    goal_temp.SetQuantity(4)
    goal_2_3 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('SA-10-1')
    goal_temp.AddTarget('Novi Sod AB')
    goal_temp.AddTarget('SA-6-1')
    goal_temp.AddTarget('SA-6-2')
    goal_temp.AddTarget('SA-11-4')
    goal_temp.AddTarget('SA-10-2')
    goal_temp.AddTarget('SA-10-3')
    goal_temp.AddTarget('SA-10-4')
    goal_temp.AddTarget('Command Center-1')
    goal_temp.AddTarget('Ammo Bunker-10')
    goal_temp.AddTarget('Ammo Bunker-11')
    goal_temp.AddTarget('Ammo Bunker-12')
    goal_temp.AddTarget('Weapons Factory-1')
    goal_temp.AddTarget('Weapons Factory-2')
    goal_temp.AddTarget('Weapons Factory-3')
    goal_temp.AddTarget('Weapons Factory-4')
    goal_temp.AddTarget('Chemical Wpns Plant-9')
    goal_temp.AddTarget('ZSU-23-1')
    goal_temp.AddTarget('ZSU-23-2')
    goal_temp.AddTarget('Radar-4')
    goal_temp.SetQuantity(20)
    goal_2_4 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('SA-10-21')
    goal_temp.AddTarget('Belgrade AB')
    goal_temp.AddTarget('SA-6-3')
    goal_temp.AddTarget('SA-6-8')
    goal_temp.AddTarget('SA-11-3')
    goal_temp.AddTarget('SA-11-6')
    goal_temp.AddTarget('SA-10-5')
    goal_temp.AddTarget('SA-10-6')
    goal_temp.AddTarget('SA-10-7')
    goal_temp.AddTarget('SA-10-17')
    goal_temp.AddTarget('SA-10-22')
    goal_temp.AddTarget('Command Center-2')
    goal_temp.AddTarget('Ammo Bunker-7')
    goal_temp.AddTarget('Ammo Bunker-8')
    goal_temp.AddTarget('Ammo Bunker-9')
    goal_temp.AddTarget('Ammo Bunker-13')
    goal_temp.AddTarget('Weapons Factory-5')
    goal_temp.AddTarget('Weapons Factory-6')
    goal_temp.AddTarget('Weapons Factory-7')
    goal_temp.AddTarget('Weapons Factory-8')
    goal_temp.AddTarget('Weapons Factory-9')
    goal_temp.AddTarget('Weapons Factory-10')
    goal_temp.AddTarget('Weapons Factory-11')
    goal_temp.AddTarget('Chemical Wpns Plant-7')
    goal_temp.AddTarget('Chemical Wpns Plant-8')
    goal_temp.AddTarget('ZSU-23-3')
    goal_temp.AddTarget('ZSU-23-4')
    goal_temp.AddTarget('Radar-3')
    goal_temp.SetQuantity(28)
    goal_2_5 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('SA-6-7')
    goal_temp.AddTarget('SA-6-6')
    goal_temp.AddTarget('SA-11-5')
    goal_temp.AddTarget('SA-11-7')
    goal_temp.AddTarget('SA-10-12')
    goal_temp.AddTarget('SA-10-13')
    goal_temp.AddTarget('SA-10-14')
    goal_temp.AddTarget('SA-10-15')
    goal_temp.AddTarget('SA-10-16')
    goal_temp.AddTarget('SA-10-18')
    goal_temp.AddTarget('SA-10-19')
    goal_temp.AddTarget('Command Center-6')
    goal_temp.AddTarget('Command Center-7')
    goal_temp.AddTarget('Command Center-8')
    goal_temp.AddTarget('Ammo Bunker-6')
    goal_temp.AddTarget('Weapons Factory-12')
    goal_temp.AddTarget('Weapons Factory-13')
    goal_temp.AddTarget('Weapons Factory-14')
    goal_temp.AddTarget('Weapons Factory-15')
    goal_temp.AddTarget('Weapons Factory-16')
    goal_temp.AddTarget('Weapons Factory-17')
    goal_temp.AddTarget('Weapons Factory-18')
    goal_temp.AddTarget('Chemical Wpns Plant-3')
    goal_temp.AddTarget('Chemical Wpns Plant-4')
    goal_temp.AddTarget('Chemical Wpns Plant-5')
    goal_temp.AddTarget('Chemical Wpns Plant-6')
    goal_temp.AddTarget('Radar-5')
    goal_temp.AddTarget('Radar-6')
    goal_temp.SetQuantity(28)
    goal_2_6 = goal_temp

    goal_temp = SM.DestroyGoal('')
    goal_temp.AddTarget('Smuggler2')
    goal_temp.AddTarget('Smuggler1')
    goal_temp.AddTarget('Smuggler3')
    goal_temp.AddTarget('Smuggler4')
    goal_temp.AddTarget('Smuggler5')
    goal_temp.SetQuantity(5)
    goal_2_7 = goal_temp

    goal_temp = SM.CompoundGoal(0)
    goal_temp.AddGoal(goal_2_0)
    goal_temp.AddGoal(goal_2_1)
    goal_temp.AddGoal(goal_2_2)
    goal_temp.AddGoal(goal_2_3)
    goal_temp.AddGoal(goal_2_4)
    goal_temp.AddGoal(goal_2_5)
    goal_temp.AddGoal(goal_2_6)
    goal_temp.AddGoal(goal_2_7)
    
    SM.SetAllianceGoal(1, goal_temp)

    SM.SetAllianceROEByType(1, 2, 2, 2, 2)

    ##############################
    ### Alliance 2 goals
    ##############################

    goal_temp = SM.TimeGoal()
    goal_temp.SetPassTimeout(36000.0)
    goal_temp.SetFailTimeout(59940.0)
    SM.SetAllianceGoal(2, goal_temp)

    SM.SetAllianceROEByType(2, 2, 2, 2, 2)

    ##############################
    ### Alliance 3 goals
    ##############################

    SM.SetAllianceGoal(3, goal_temp)

    SM.SetAllianceROEByType(3, 0, 0, 0, 0)

    ##############################
    ### Overlay Graphics
    ##############################
    SM.OverlayText('Novi Sod', 19.4550, 45.1534, '0x000000FF')
    SM.OverlayText('Prishtina', 21.1280, 42.4177, '0x000000FF')
    SM.OverlayText('Zagreb', 15.5848, 45.4828, '0x000000FF')
    SM.OverlayText('Belgrade', 20.2835, 44.4977, '0x000000FF')
    SM.OverlayText('Budva', 19.0177, 42.1442, '0x000000FF')
    SM.OverlayText('Hercog Novi', 18.6231, 42.4416, '0x000000FF')
    SM.OverlayText('Banja Luka', 17.1083, 44.4486, '0x000000FF')
    SM.OverlayText('Neum', 17.4467, 43.0369, '0x000000FF')
    ##############################
    ### Randomization Info
    ##############################
    SM.SetIncludeProbability('Ferry ', 1.000000)
    SM.AddRandomBox('Ferry ', 23.1563, 23.1963, 34.1265, 34.1665)
    SM.SetIncludeProbability('Temp 0728', 0.500000)
