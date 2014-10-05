from UnitCommands import *
from GroupCommands import *
from MissionEditCommands import *
from GameMenuCommands import *
from HotKey import *
from FlightPort import *
from SecondaryHook import *
from Landing import *
from DevMode import *
from GroupMenu import *
from EditMenu import *
from Amram_Menu import *

###### Track menu scripts #####
def BuildTrackMenu(TrackMenu, HookedTrackInfo):
    TrackMenu.Clear()
    TrackMenu.AddItem('Declare affiliation','')
    TrackMenu.BeginSubMenu()
    TrackMenu.AddItem('Declare friendly','DeclareFriendly')
    TrackMenu.AddItem('Declare neutral','DeclareNeutral') 
    TrackMenu.AddItem('Declare hostile','DeclareHostile')
    TrackMenu.EndSubMenu()
    TrackMenu.AddItem('Drop track','DropTrack')
    TrackMenu.AddItem('Update ambiguity list','UpdateAmbiguityList')

def DeclareFriendly(TrackInfo):
    TrackInfo.DeclareFriendly()

def DeclareNeutral(TrackInfo):
    TrackInfo.DeclareNeutral()

def DeclareHostile(TrackInfo):
    TrackInfo.DeclareHostile()

def DropTrack(TrackInfo):
    TrackInfo.DropTrack()

def UpdateAmbiguityList(TrackInfo):
    TrackInfo.UpdateAmbiguityList()


###### Unit menu scripts #####
def BuildUnitMenu(UnitMenu, UnitInfo):
    UnitMenu.Clear()

    BuildAmramMenu(UnitMenu, UnitInfo)
    return
    UnitMenu.AddItem('Stock Menu','');UnitMenu.BeginSubMenu()
    UnitMenu.SetStayOpen(0)
    
    if (not UnitInfo.IsValid()):
        return

    # Multiplayer options
    if (UnitInfo.IsMultiplayerActive()):
        if (not UnitInfo.IsPlayerControlled()):
            if (UnitInfo.IsAvailable()):
                UnitMenu.AddItem('Take control', 'TakeControl')
                return
            else:
                controller = UnitInfo.GetController()
                UnitMenu.AddItem('Unavailable unit (%s)' % controller, '')
                return


    if (not UnitInfo.IsFixed()):
        UnitMenu.AddItem('Navigate','')
        UnitMenu.BeginSubMenu()
        BuildNavMenu(UnitMenu, UnitInfo)
        UnitMenu.EndSubMenu()
    
    # Target submenu
    BuildTargetMenu(UnitMenu, UnitInfo)

    # Launcher
    BuildLaunchMenu(UnitMenu, UnitInfo)

    # Orders test
    UnitMenu.AddItem('Tasks','')
    UnitMenu.BeginSubMenu()
    
    UnitMenu.AddItemUI('EngageAll [e]', 'AddEngageAllOrder','Null')
    if (not UnitInfo.IsFixed()):
        UnitMenu.AddItemUI('Patrol station','AddPatrolStation', 'Datum')
        UnitMenu.AddItemUI('Set patrol area', 'SetPatrolArea', 'Box')
        UnitMenu.AddItem('Clear patrol area', 'ClearPatrolArea')
        #UnitMenu.AddItemUI('Missile alert', 'AddMissileWarnTask','Null')
    UnitMenu.AddItemUI('Clear tasks [C]','ClearTasks','Null')
    UnitMenu.AddItemUI('Add by name','AddTaskByName','Text Enter new task name')
    UnitMenu.EndSubMenu() 
    
    if (UnitInfo.IsAir()):
        BuildRefuelMenu(UnitMenu, UnitInfo)
        BuildLandMenu(UnitMenu, UnitInfo)
        

    # Submarine menu
    if (UnitInfo.IsSub()):
        BuildSubmarineMenu(UnitMenu, UnitInfo)

    UnitMenu.AddItem('Platform panel [s]', 'ShowPlatformPanel')

    # Flight port panel if available
    if (UnitInfo.HasFlightPort()):
        UnitMenu.AddItem('Flight deck [f]', 'ShowFlightPanel')
        BuildMissionMenu(UnitMenu, UnitInfo)
        

    if (UnitInfo.IsMultiplayerActive() and UnitInfo.IsPlayerControlled()):
        UnitMenu.AddItem('Release control', 'ReleaseControl')

    # Formation
    BuildFormationMenu(UnitMenu, UnitInfo)
    
    # developer tool menu for dev mode
    BuildDeveloperMenu(UnitMenu, UnitInfo)

# menu for adding and editing aircraft missions    
def BuildMissionMenu(UnitMenu, UnitInfo):
    FP = UnitInfo.GetFlightPortInfo()
    if (not FP.IsValid()):
        return
        
    hasCAP = FP.HasAircraftForMission('cap')
    hasStrike = FP.HasAircraftForMission('strike')
    hasASW = FP.HasAircraftForMission('asw')
    hasAEW = FP.HasAircraftForMission('aew') 
    
    if (hasCAP or hasAEW or hasStrike or hasASW):
        UnitMenu.AddItem('Quick Mission', '')
        UnitMenu.BeginSubMenu()
        
        UnitMenu.AddItem('Add', '')
        UnitMenu.BeginSubMenu()
        if (hasCAP):
            UnitMenu.AddItemUI('CAP', 'AddCAPMission', 'Datum')
        if (hasStrike):
            UnitMenu.AddItemUI('Land/Surf Attack', 'AddAttackMission', 'Target')
        if (hasASW):
            UnitMenu.AddItemUI('ASW Patrol', 'AddASWMission', 'Datum')
        if (hasAEW):
            UnitMenu.AddItemUI('AEW Patrol', 'AddAEWMission', 'Datum')
        UnitMenu.EndSubMenu()
        
        UnitMenu.EndSubMenu()

    
def BuildNavMenu(UnitMenu, UnitInfo):
    if (UnitInfo.IsInFormation() and ~UnitInfo.IsFormationLeader()):
        UnitMenu.AddItem('Break formation','BreakAirFormation')
        return
        
    UnitMenu.AddItemUI('Set heading [h]','SetHeading','Heading')
    # Speed submenu
    UnitMenu.AddItem('Set speed','')
    UnitMenu.BeginSubMenu()
    if (UnitInfo.HasThrottle()):
        UnitMenu.AddItem('Cruise [0]', 'SpeedCruise')
    UnitMenu.AddItem('30% [1]','Speed30')
    UnitMenu.AddItem('50% [2]','Speed50')
    UnitMenu.AddItem('80% [3]','Speed80')
    UnitMenu.AddItem('100% [4]','Speed100')
    UnitMenu.AddItem('Max [5]','SpeedAB')
    UnitMenu.EndSubMenu()
    
    if (UnitInfo.IsAir()):
        # Altitude submenu
        UnitMenu.AddItem('Set altitude','')
        UnitMenu.BeginSubMenu()
        UnitMenu.AddItem('High [H]','AltitudeHigh')
        UnitMenu.AddItem('Medium [M]','AltitudeMedium')
    	UnitMenu.AddItem('Low [L]','AltitudeLow')
        UnitMenu.AddItem('Very low','AltitudeVeryLow') 
        UnitMenu.EndSubMenu()
        UnitMenu.AddItemUI('Join air formation','AddAirFormationTaskId','Target')
        
    UnitMenu.AddItem('Waypoints','')
    UnitMenu.BeginSubMenu()
    UnitMenu.SetStayOpen(1)
    UnitMenu.AddItemUI('Add [w]', 'AddWaypointOrder', 'Datum')
    UnitMenu.AddItem('Clear all', 'ClearWaypoints')
    if (UnitInfo.GetNavLoopState()):
        UnitMenu.AddItemWithParam('Set loop off', 'SetNavLoopState', 0)
    else:
        UnitMenu.AddItemWithParam('Set loop on', 'SetNavLoopState', 1)
    UnitMenu.SetStayOpen(0)
    UnitMenu.EndSubMenu()
    
def BuildRefuelMenu(UnitMenu, UnitInfo):
    UnitMenu.AddItem('Refuel','')
    UnitMenu.BeginSubMenu()
    if (UnitInfo.TaskExists('Refuel')):
        UnitMenu.AddItem('Cancel refuel', 'CancelRefuel')
    else:
        tanker_info = GetNearbyTankers(UnitInfo)
        UnitMenu.AddItemUI('Refuel from selected','AddRefuelOrder','Target')

        # nearby tankers  menu
        if (len(tanker_info) > 0):
            UnitMenu.AddItem('Refuel from','')
            UnitMenu.BeginSubMenu()
            for n in range(0, len(tanker_info)):
                UnitMenu.AddItemWithTextParam('%s [%.0f km]' % (tanker_info[n].name, tanker_info[n].range_km), 'RefuelFromNamed', tanker_info[n].name)
            UnitMenu.EndSubMenu()
        
    UnitMenu.EndSubMenu()
    
    
def BuildLandMenu(UnitMenu, UnitInfo):
    # Land submenu
    if (UnitInfo.TaskExists('Land')):
        UnitMenu.AddItem('Cancel landing', 'CancelLanding')
    else:
        base_info = GetNearbyAirfields(UnitInfo)
        
        UnitMenu.AddItem('Land','')
        UnitMenu.BeginSubMenu()
        home_base = GetHomeBase(UnitInfo)
        if (home_base != ''):
            UnitMenu.AddItemWithTextParam('Return to base (%s)' % home_base, 'LandAtNamed', home_base)
        UnitMenu.AddItemUI('Land at selected','AddLandingOrder', 'Target')

        # nearby airbase menu
        if (len(base_info) > 0):
            UnitMenu.AddItem('Land at','')
            UnitMenu.BeginSubMenu()
            for n in range(0, len(base_info)):
                UnitMenu.AddItemWithTextParam('%s [%.0f km]' % (base_info[n].name, base_info[n].range_km), 'LandAtNamed', base_info[n].name)
            UnitMenu.EndSubMenu()
        
        UnitMenu.EndSubMenu()
    
def BuildSubmarineMenu(UnitMenu, UnitInfo):
    UnitMenu.AddItem('Set depth','')
    UnitMenu.BeginSubMenu()
    UnitMenu.AddItem('Surface','DepthSurface')
    UnitMenu.AddItem('Periscope','DepthPeriscope')
    UnitMenu.AddItem('Medium','DepthMedium')
    UnitMenu.AddItem('Deep','DepthDeep') 
    UnitMenu.EndSubMenu()

    SubMenu = UnitInfo.GetSubInterface()
    if (SubMenu.IsAtPeriscopeDepth()):
        UnitMenu.AddItem('Scope-Mast','')
        UnitMenu.BeginSubMenu()
        if (SubMenu.IsPeriscopeRaised()):
            UnitMenu.AddItemWithParam('Lower scope', 'SetPeriscope', 0)
        else:
            UnitMenu.AddItemWithParam('Raise scope', 'SetPeriscope', 1)
            
        if (SubMenu.IsRadarMastRaised()):
            UnitMenu.AddItemWithParam('Lower mast', 'SetRadarMast', 0)
        else:
            UnitMenu.AddItemWithParam('Raise mast', 'SetRadarMast', 1)
            
        if (SubMenu.IsDieselElectric()):
            if (UnitInfo.GetAlt() < 0):
                term_str = 'snorkeling'
            else:
                term_str = 'diesels'
                
            if (SubMenu.IsSnorkeling()):
                UnitMenu.AddItemWithParam('Stop %s' % term_str, 'SetSnorkel', 0)
            else:
                UnitMenu.AddItemWithParam('Start %s' % term_str, 'SetSnorkel', 1)

        UnitMenu.EndSubMenu()
        
    UnitMenu.AddItem('Mounts','')
    UnitMenu.BeginSubMenu()
    nCount = UnitInfo.GetLauncherCount()
    for n in range(0, nCount):
        launcher_info = UnitInfo.GetLauncherInfo(n)
        weap_name = UnitInfo.GetLauncherWeaponName(n)
        weap_qty = launcher_info.Quantity
        isLoadingUnloading = launcher_info.IsLoading
        if (weap_qty == 0):
            if (not isLoadingUnloading):
                nTypes = UnitInfo.GetLauncherTypesCount(n)
                for k in range(0, nTypes):
                    type_name = UnitInfo.GetLauncherTypeName(n, k)
                    reload_qty = UnitInfo.GetMagazineQuantity(type_name)
                    #UnitInfo.DisplayMessage('%s %d' % (type_name, reload_qty))
                    if (reload_qty > 0):
                        UnitMenu.AddItemWithTextParam('Load %s [%d]' % (type_name, reload_qty), 'Reload%d' % n, type_name)
            else:
                UnitMenu.AddItemWithParam('Cancel load %s' % weap_name, 'Unload', n)
        else:
            if (not isLoadingUnloading):
                if (UnitInfo.CanMagazineAcceptItem(weap_name)):
                    UnitMenu.AddItemWithParam('Unload %s' % weap_name, 'Unload', n)
            else:
                UnitMenu.AddItemWithTextParam('Cancel unload %s' % weap_name, 'Reload%d' % n, weap_name)
    UnitMenu.EndSubMenu()


def BuildLaunchMenu(UnitMenu, UnitInfo):
    nCount = UnitInfo.GetLauncherCount()
    if (nCount == 0):
        return
    
    ## Engage Datum with submenu
    launcherText = []
    launcherIdx = []    
    for n in range(0, nCount):
        if (UnitInfo.IsDatumLaunch(n)): 
            weap_name = UnitInfo.GetLauncherWeaponName(n)
            weap_qty = UnitInfo.GetLauncherQuantity(n)
            if (weap_qty > 0):
                launcherText.append('%s [%d]' % (weap_name, weap_qty))
                launcherIdx.append(n)
                #UnitMenu.AddItemUIWithParam('%s [%d]' % (weap_name, weap_qty), 'LaunchDatum', 'Datum', n)
    
    nDatumLaunch = len(launcherText)
    if (nDatumLaunch > 0):
        UnitMenu.AddItem('Engage datum with','')
        UnitMenu.BeginSubMenu()
        for n in range(0, nDatumLaunch):
            UnitMenu.AddItemUIWithParam(launcherText[n], 'LaunchDatum', 'Datum', launcherIdx[n])
        UnitMenu.EndSubMenu()    
    

    hasGravityBombs = HasGravityBombs(UnitInfo)
    if (hasGravityBombs):
        UnitMenu.AddItemUI('Bomb datum', 'AddBombDatumTask', 'Datum')
        UnitMenu.AddItemUI('Bomb datum', 'AddBombDatumTask', 'Datum')
        UnitMenu.AddItemUI('Bomb datum', 'AddBombDatumTask', 'Datum')

    # "Engage target with" menu lists launchers that are effective vs. selected target
    target_id = UnitInfo.GetTarget()
    if (target_id != -1):
        if (hasGravityBombs):
            UnitMenu.AddItem('Bomb target', 'AddBombTargetTask')

        launcherText = []
        launcherIdx = []
        for n in range(0, nCount):
            if (UnitInfo.IsLauncherEffective(n)):
                weap_name = UnitInfo.GetLauncherWeaponName(n)
                weap_qty = UnitInfo.GetLauncherQuantity(n)
                launcherText.append('%s [%d]' % (weap_name, weap_qty))
                launcherIdx.append(n)
                # UnitMenu.AddItemWithParam('%s [%d]' % (weap_name, weap_qty), 'LaunchTarget', n)
        nEngageTarget = len(launcherText)
        if (nEngageTarget > 0):
            UnitMenu.AddItem('Engage target with','')
            UnitMenu.BeginSubMenu()
            for n in range(0, nEngageTarget):
                UnitMenu.AddItemWithParam(launcherText[n], 'LaunchTarget', launcherIdx[n])
            UnitMenu.EndSubMenu()


    # "Quick engage with" allows user to click on target and then automatically launch
    launcherText = []
    launcherIdx = []
    for n in range(0, nCount):
        weap_name = UnitInfo.GetLauncherWeaponName(n)
        weap_qty = UnitInfo.GetLauncherQuantity(n)
        if (weap_qty > 0):
            launcherText.append('%s [%d]' % (weap_name, weap_qty))
            launcherIdx.append(n)
            # UnitMenu.AddItemUIWithParam('%s [%d]' % (weap_name, weap_qty), 'TargetAndEngageWith', 'Target', n)
    nQuickEngage = len(launcherText)
    if (nQuickEngage > 0):
        UnitMenu.AddItem('Quick engage with','')
        UnitMenu.BeginSubMenu()
        for n in range(0, nQuickEngage):
            UnitMenu.AddItemUIWithParam(launcherText[n], 'TargetAndEngageWith', 'Target', launcherIdx[n])
        UnitMenu.EndSubMenu()  



def BuildTargetMenu(UnitMenu, UnitInfo):
    UnitMenu.AddItem('Target','')
    UnitMenu.BeginSubMenu()
    if (UnitInfo.GetTarget() == -1):
        UnitMenu.AddItemUI('Select target','SelectTarget','Target')
    else:
        UnitMenu.AddItem('Clear','ClearTarget')
        UnitMenu.AddItemUI('Change','SelectTarget','Target')
        UnitMenu.AddItem('Attack', 'AttackTarget')
        if (UnitInfo.IsAir()):
            UnitMenu.AddItem('Intercept','AddInterceptTask')
    UnitMenu.EndSubMenu()
    



def BuildFormationMenu(UnitMenu, UnitInfo):
    if (not UnitInfo.IsSurface()):
        return
    
    UnitMenu.AddItem('Formation', '')
    UnitMenu.BeginSubMenu()
	
    formEditId = UnitInfo.GetFormationEditId()
    myId = UnitInfo.GetPlatformId()
	
    if (~UnitInfo.IsFormationLeader()):
        if (UnitInfo.IsInFormation()):
            leaderId = UnitInfo.GetFormationLeader()
            UnitMenu.AddItemWithParam('Leave formation', 'SetFormationLeader', -2)
            UnitMenu.AddItemUI('Change formation leader', 'SetFormationLeader', 'Target')
            UnitMenu.AddItem('Formation mode','')
            current_mode = UnitInfo.GetFormationMode()
            UnitMenu.BeginSubMenu()
            if (current_mode == 1): # FOLLOW mode
                UnitMenu.AddItemWithParam('Follow [x]', 'SetFormationMode', 1)
                UnitMenu.AddItemWithParam('Sprint-drift', 'SetFormationMode', 2)
            else: # SPRINT & DRIFT mode
                UnitMenu.AddItemWithParam('Follow', 'SetFormationMode', 1)
                UnitMenu.AddItemWithParam('Sprint-drift [x]', 'SetFormationMode', 2)
            UnitMenu.EndSubMenu()
            if (formEditId == leaderId):
                UnitMenu.AddItem('Clear formation edit', 'DisableFormationEdit')
            else:
                UnitMenu.AddItem('Enable formation edit', 'EnableFormationEdit')
        else:
            UnitMenu.AddItemUI('Set formation leader', 'SetFormationLeader', 'Target')
    if (UnitInfo.IsFormationLeader()):
        if (formEditId == myId):
            UnitMenu.AddItem('Clear formation edit', 'DisableFormationEdit')
        else:
            UnitMenu.AddItem('Enable formation edit', 'EnableFormationEdit')
        
    UnitMenu.EndSubMenu()

def BuildDeveloperMenu(UnitMenu, UnitInfo):
    if (UnitInfo.IsDeveloperMode() == 0):
        return
    UnitMenu.AddItem('Dev tools', '')
    UnitMenu.BeginSubMenu()
    UnitMenu.AddItemUI('Move unit', 'MovePlatformDev', 'Datum')
    if (UnitInfo.HasThrottle()):
        UnitMenu.AddItem('Speed vs alt', '*ShowAirInfo')
    BuildDamageMenu(UnitMenu, UnitInfo)
    UnitMenu.AddItem('TestCollision', '*TestCollision')
    UnitMenu.AddItem('TestCrossSection', '*TestCrossSection')
    UnitMenu.AddItem('ShowPlatformDebug', '*ShowPlatformDebug')
    UnitMenu.AddItem('Show Sonar Panel', '*ShowSonarPanel')
    UnitMenu.AddItem('Make invulnerable', 'MakePlatformInvulnerable')
    UnitMenu.AddItem('Show best launcher', 'ReportBestLauncherForTarget')
    BuildLoadLauncherMenuAll(UnitMenu, UnitInfo)
    BuildSetFuelMenu(UnitMenu, UnitInfo)
    BuildLaunchAtMeMenu(UnitMenu, UnitInfo)
    UnitMenu.EndSubMenu()
    
    
def BuildWeaponMenu(UnitMenu, WeaponInfo):
    UnitMenu.Clear()
    if (not WeaponInfo.IsValid()):
        return
    
    weapon_type = WeaponInfo.GetWeaponType()
    UnitMenu.AddItem('Weapon Type: %s' % weapon_type, '')
    if (WeaponInfo.IsLinkActive()):
        UnitMenu.AddItem('LINK IS ACTIVE', '')
        UnitMenu.AddItemUI('Update target datum', 'UpdateWeaponTargetDatum', 'Datum')
