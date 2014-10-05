#
# scripts for "developer mode" test features
# disallowed in non dev mode, since normally these would be cheats
#

deg_to_rad = 0.01745329252
rad_to_deg = 57.2957795131

def BuildLoadLauncherMenuAll(Menu, UnitInfo):
    nCount = UnitInfo.GetLauncherCount()
    Menu.AddItem('Load missile','')
    Menu.BeginSubMenu()
    for n in range(0, nCount):
        Menu.AddItem('L%d' % n, '')
        BuildPagedLoadLauncherMenu(Menu, UnitInfo, 'Missile', n)
    Menu.EndSubMenu()
    
    Menu.AddItem('Load ballistic','')
    Menu.BeginSubMenu()
    for n in range(0, nCount):
        Menu.AddItem('L%d' % n, '')
        BuildPagedLoadLauncherMenu(Menu, UnitInfo, 'Ballistic', n)        
    Menu.EndSubMenu()
    
    Menu.AddItem('Load torpedo','')
    Menu.BeginSubMenu()
    for n in range(0, nCount):
        Menu.AddItem('L%d' % n, '')
        BuildPagedLoadLauncherMenu(Menu, UnitInfo, 'Torpedo', n)        
    Menu.EndSubMenu()    
    
    Menu.AddItem('Load CM','')
    Menu.BeginSubMenu()
    for n in range(0, nCount):
        Menu.AddItem('L%d' % n, '')
        BuildPagedLoadLauncherMenu(Menu, UnitInfo, 'CM', n)        
    Menu.EndSubMenu()

def BuildDamageMenu(Menu, UnitInfo):
    Menu.AddItem('ApplyDamage','')
    Menu.BeginSubMenu()
    
    Menu.AddItem('Generic Damage','')
    Menu.BeginSubMenu()
    Menu.AddItemWithParam('10%', 'ApplyDamage', 10)
    Menu.AddItemWithParam('25%', 'ApplyDamage', 25)
    Menu.AddItemWithParam('50%', 'ApplyDamage', 50)
    Menu.EndSubMenu()
    
    Menu.AddItem('Blast Damage','')
    Menu.BeginSubMenu()
    Menu.AddItemWithParam('1 PSI', 'ApplyBlastDamage', 10)
    Menu.AddItemWithParam('2 PSI', 'ApplyBlastDamage', 20)
    Menu.AddItemWithParam('5 PSI', 'ApplyBlastDamage', 50)
    Menu.AddItemWithParam('10 PSI', 'ApplyBlastDamage', 100)
    Menu.EndSubMenu()
    
    Menu.AddItemWithParam('Repair Unit', 'ApplyDamage', -200)
    Menu.EndSubMenu()

# dev mode only
# @param damageFractionPercent integer percentage damage or negative for repair
def ApplyDamage(UnitInfo, damageFractionPercent):
    damageFraction = 0.01 * float(damageFractionPercent)
    UnitInfo.ApplyDamage(damageFraction)
    
# dev mode only
# @param blastPSI tenths of PSI to apply
def ApplyBlastDamage(UnitInfo, blastPSI):
    isPen = 0
    kinetic_J = 0
    explosive_kg = 0
    blast_psi = 0.1 * float(blastPSI)
    waterBlast_psi = 0
    thermal_J_cm2 = 0
    fragHits = 0
    fragEnergy_J = 0
    
    UnitInfo.ApplyAdvancedDamage(isPen, kinetic_J, explosive_kg, blast_psi, waterBlast_psi, thermal_J_cm2, fragHits, fragEnergy_J)
    
def BuildPagedLoadLauncherMenu(Menu, UnitInfo, equipType, launcher_idx):
    page_count = 16
    quantity = 20
    Menu.BeginSubMenu()
    
    weapons = UnitInfo.GetEquipmentListByClass(equipType)
    nWeapons = weapons.Size()
    if (nWeapons > page_count):
        nSubmenus = nWeapons/page_count + 1
        for sm in range(0, nSubmenus):
            Menu.AddItem('Page %d' % (sm+1),'')
            Menu.BeginSubMenu()
            nWeaponsPage = min(page_count, nWeapons - sm*page_count)
            for n in range(0, nWeaponsPage):
                className = weapons.GetString(n+sm*page_count)
                Menu.AddItemWithTextParam('%s' % className, 'LoadLauncherDev', ',%d,\'%s\',%d' % (launcher_idx, className, quantity))
            Menu.EndSubMenu()
    else:
        for n in range(0, nWeapons):
            className = weapons.GetString(n)
            Menu.AddItemWithTextParam('%s' % className, 'LoadLauncherDev', ',%d,\'%s\',%d' % (launcher_idx, className, quantity))
    Menu.EndSubMenu()

def LoadLauncherDev(UnitInfo, launcher_idx, childClass, quantity):
    UnitInfo.LoadLauncherTest(launcher_idx, childClass, quantity)
    
    
def MovePlatformDev(UnitInfo, lon_rad, lat_rad):
    UnitInfo.MovePlatform(lon_rad, lat_rad)
    
def MakePlatformInvulnerable(UnitInfo):
    UnitInfo.SetInvulnerable(1)

def BuildSetFuelMenu(Menu, UnitInfo):
    Menu.AddItem('Set fuel','')
    Menu.BeginSubMenu()
    
    Menu.AddItemWithParam('Empty', 'SetFuelTest', 0)
    Menu.AddItemWithParam('10%', 'SetFuelTest', 10)
    Menu.AddItemWithParam('20%', 'SetFuelTest', 20)
    Menu.AddItemWithParam('40%', 'SetFuelTest', 40)
    Menu.AddItemWithParam('60%', 'SetFuelTest', 60)
    Menu.AddItemWithParam('80%', 'SetFuelTest', 80)
    Menu.AddItemWithParam('Full', 'SetFuelTest', 100)
    
    Menu.EndSubMenu()
    
def SetFuelTest(UnitInfo, fuelFractionPercent):
    UnitInfo.SetFuelTest(0.01 * float(fuelFractionPercent))
    
def BuildLaunchAtMeMenu(Menu, UnitInfo):
    Menu.AddItem('Weapon test','')
    Menu.BeginSubMenu()

    Menu.AddItem('Set params','')
    Menu.BeginSubMenu()
    Menu.AddItemUI('SetLaunchRange', 'SetWeaponTestLaunchRangeDev', 'Text')
    Menu.AddItemUI('SetLaunchAltitude', 'SetWeaponTestLaunchAltitudeDev', 'Text')
    Menu.AddItemUI('SetLaunchQuantity', 'SetWeaponTestLaunchQuantityDev', 'Text')
    Menu.AddItemUI('SetLaunchInterval', 'SetWeaponTestLaunchIntervalDev', 'Text')
    Menu.EndSubMenu()

    Menu.AddItem('Start with','')
    Menu.BeginSubMenu()
    
    Menu.AddItem('Missile','')
    BuildPagedLaunchAtMeMenu(Menu, UnitInfo, 'Missile')

    Menu.AddItem('Ballistic','')
    BuildPagedLaunchAtMeMenu(Menu, UnitInfo, 'Ballistic')

    Menu.EndSubMenu()
    
    Menu.EndSubMenu()
    

def BuildPagedLaunchAtMeMenu(Menu, UnitInfo, equipType):
    page_count = 16
    quantity = 100
    Menu.BeginSubMenu()
    
    weapons = UnitInfo.GetEquipmentListByClass(equipType)
    nWeapons = weapons.Size()
    if (nWeapons > page_count):
        nSubmenus = nWeapons/page_count + 1
        for sm in range(0, nSubmenus):
            Menu.AddItem('Page %d' % (sm+1),'')
            Menu.BeginSubMenu()
            nWeaponsPage = min(page_count, nWeapons - sm*page_count)
            for n in range(0, nWeaponsPage):
                className = weapons.GetString(n+sm*page_count)
                Menu.AddItemWithTextParam('%s' % className, 'LaunchAtMeDev', ',\'%s\',%d' % (className, quantity))
            Menu.EndSubMenu()
    else:
        for n in range(0, nWeapons):
            className = weapons.GetString(n)
            Menu.AddItemWithTextParam('%s' % className, 'LaunchAtMeDev', ',\'%s\',%d' % (className, quantity))
    Menu.EndSubMenu()


def LaunchAtMeDev(UnitInfo, childClass, quantity):
    UnitInfo.LaunchAtMe(childClass, quantity)

def SetWeaponTestLaunchRangeDev(UnitInfo, range_km):
    UnitInfo.SetTestParameter('WeaponTesterLaunchRangeKm', float(range_km))

def SetWeaponTestLaunchAltitudeDev(UnitInfo, altitude_m):
    UnitInfo.SetTestParameter('WeaponTesterLaunchAltitude', float(altitude_m))
    
def SetWeaponTestLaunchQuantityDev(UnitInfo, quantity):
    UnitInfo.SetTestParameter('WeaponTesterLaunchQuantity', float(quantity))

def SetWeaponTestLaunchIntervalDev(UnitInfo, quantity):
    UnitInfo.SetTestParameter('WeaponTesterLaunchInterval', float(quantity))
    
