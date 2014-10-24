#new home for the weaponry lists, they shouldn't be in the core file
#hopefully in 1.4 the entire purpose of this file dissolves and these lists go away.

def target_flags(flag, val):
    while flag > 0:
        if flag ==  val:
            return True
        elif flag < val:
            return False
        else:
            if flag >= 16:
                flag -= 16
            elif flag >= 8:
                flag -= 8
            elif flag >= 4:
                flag -= 4
            elif flag >= 2:
                flag -= 2
            elif flag >= 1:
                flag -= 1
    return False

def HasIronBombs(interface):
    #simple check to see if we have bombs, capable of functioning for both group and individual units.
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
            
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            nLaunchers = UI.GetLauncherCount()
            for n in range(0, nLaunchers):
                info = UI.GetLauncherInfo(n)
                # LaunchMode == 3 is gravity bomb
                if (info.LaunchMode == 3) and (info.Quantity > 0): 
                    return 1
        return 0
    else:
        UI = interface
        nLaunchers = UI.GetLauncherCount()
        for n in range(0, nLaunchers):
            info = UI.GetLauncherInfo(n)
            # LaunchMode == 3 is gravity bomb
            if (info.LaunchMode == 3) and (info.Quantity > 0): 
                return 1
        return 0
        
def HasRockets(interface):
    #simple check to see if we have bombs, capable of functioning for both group and individual units.
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
            
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            nLaunchers = UI.GetLauncherCount()
            for n in range(0, nLaunchers):
                if UI.QueryDatabase('ballistic',UI.GetLauncherWeaponName(n),'BallisticType').GetString(0) == '5':  #rocket
                    return 1
        return 0
    else:
        UI = interface
        nLaunchers = UI.GetLauncherCount()
        for n in range(0, nLaunchers):
            if UI.QueryDatabase('ballistic',UI.GetLauncherWeaponName(n),'BallisticType').GetString(0) == '5':  #rocket
                return 1
        return 0

def HasGBU(interface):
    #simple check to see if we have bombs, capable of functioning for both group and individual units.
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
            
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            nLaunchers = UI.GetLauncherCount()
            for n in range(0, nLaunchers):
                if UI.QueryDatabase('ballistic',UI.GetLauncherWeaponName(n),'BallisticType').GetString(0) == '3':  #guided bomb
                    return 1
        return 0
    else:
        UI = interface
        nLaunchers = UI.GetLauncherCount()
        for n in range(0, nLaunchers):
            if UI.QueryDatabase('ballistic',UI.GetLauncherWeaponName(n),'BallisticType').GetString(0) == '3':  #guided bomb
                return 1
        return 0        
        
def HasStrafeGuns(interface):
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
            
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            nLaunchers = UI.GetLauncherCount()
            for n in range(0, nLaunchers):
                weapon_name = UI.GetLauncherWeaponName(n)
                if (UI.QueryDatabase('ballistic',weapon_name,'BallisticType').GetString(0) in ['0','2'] and
                    (target_flags(int(UI.QueryDatabase('ballistic', weapon_name, 'targetFlags').GetString(0)),1) or
                    target_flags(int(UI.QueryDatabase('ballistic', weapon_name, 'targetFlags').GetString(0)),4))):
                    return 1
        return 0
    else:
        UI = interface
        nLaunchers = UI.GetLauncherCount()
        for n in range(0, nLaunchers):
            weapon_name = UI.GetLauncherWeaponName(n)
            if (UI.QueryDatabase('ballistic',weapon_name,'BallisticType').GetString(0) in ['0','2'] and
                (target_flags(int(UI.QueryDatabase('ballistic', weapon_name, 'targetFlags').GetString(0)),1) or
                target_flags(int(UI.QueryDatabase('ballistic', weapon_name, 'targetFlags').GetString(0)),4))):
                return 1
        return 0

def HasAAW(interface):
    try:
        #GetPlatformId ONLY works on UnitInfo, so if we throw an error, we got called by GroupInfo instead
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
            
    if group:
        for unit in xrange(interface.GetUnitCount()):
            if target_flags(int(UI.QueryDatabase('missile', UI.GetLauncherWeaponName(n), 'targetFlags').GetString(0)),2):
                return 1
        return 0
    else:
        UI = interface
        nLaunchers = UI.GetLauncherCount()
        for n in range(0, nLaunchers):
            weapon_name = UI.GetLauncherWeaponName(n)
            if target_flags(int(UI.QueryDatabase('missile', UI.GetLauncherWeaponName(n), 'targetFlags').GetString(0)),2):
                return 1
        return 0

def strafe_capable(UI):
    capable = False
    for n in range(0, UI.GetLauncherCount()):
        weaponName = UI.GetLauncherWeaponName(n)
        if (UI.QueryDatabase('ballistic',weapon_name,'BallisticType').GetString(0) in ['0','2','5'] and
            (target_flags(int(UI.QueryDatabase('ballistic', weapon_name, 'targetFlags').GetString(0)),1) or
            target_flags(int(UI.QueryDatabase('ballistic', weapon_name, 'targetFlags').GetString(0)),4))):
            capable = True
    return capable        

#

