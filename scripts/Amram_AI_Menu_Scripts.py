#new home for all my menu stuffs, they occupied too much room in the core file to remain.
#at 300 lines and growing, I thought it was about time they got their own file.
import Amram_AI_Scripts as AI

def Amram_AI_Core_Menu(UnitMenu, UnitInfo):
    UnitMenu.AddItem('AI Start/Stop','')
    UnitMenu.BeginSubMenu()
    UnitMenu.SetStayOpen(1)
    
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        if not(UnitInfo.TaskExists('AI_Weaponry')) and not(UnitInfo.TaskExists('AI_Navigation')):
            UnitMenu.AddItemWithTextParam('Start Full AI Control', 'BBOptionHandler','AI_Weaponry;AI_Navigation|Task|Start')
        elif UnitInfo.TaskExists('AI_Weaponry') and UnitInfo.TaskExists('AI_Navigation'):
            UnitMenu.AddItemWithTextParam('Stop All AI Control', 'BBOptionHandler','AI_Weaponry;AI_Navigation|Task|End')
        if UnitInfo.TaskExists('AI_Weaponry'):
            UnitMenu.AddItemWithTextParam('Stop AI_Weaponry', 'BBOptionHandler','AI_Weaponry|Task|End')
        else:
            UnitMenu.AddItemWithTextParam('Start AI_Weaponry', 'BBOptionHandler','AI_Weaponry|Task|Start')
        if UnitInfo.TaskExists('AI_Navigation'):
            UnitMenu.AddItemWithTextParam('Stop AI_Navigation', 'BBOptionHandler','AI_Navigation|Task|End')
        else:
            UnitMenu.AddItemWithTextParam('Start AI_Navigation', 'BBOptionHandler','AI_Navigation|Task|Start')
        UnitMenu.EndSubMenu()

    if (UnitInfo.TaskExists('AI_Navigation') or UnitInfo.TaskExists('AI_Weaponry')):
        UnitMenu.AddItem('* == N/A','')
        UnitMenu.AddItem('~ == WIP','')

    if UnitInfo.TaskExists('AI_Weaponry'):
        UnitMenu.AddItem('Combat Settings','')
        Amram_Weapon_Officer_FlagFree_Menu(UnitMenu, UnitInfo)

        UnitMenu.AddItem('Rules of Engagement','')
        Amram_Weapon_Officer_ROE_Menu(UnitMenu, UnitInfo)

    if UnitInfo.TaskExists('AI_Navigation'):
        UnitMenu.AddItem('AI_Navigation','')
        Amram_Helm_Officer_Patrol_Settings_Menu(UnitMenu, UnitInfo)


        UnitMenu.AddItem('Status','')
        Amram_Helm_Officer_Nav_Status_Menu(UnitMenu, UnitInfo)
        UnitMenu.EndSubMenu()
        
    if (UnitInfo.TaskExists('AI_Navigation') or UnitInfo.TaskExists('AI_Weaponry')):
        UnitMenu.AddItem('','')  #just to isolate my menu options from the game's menu options
        
def Amram_Weapon_Officer_FlagFree_Menu(UnitMenu, UnitInfo):
    BB = UnitInfo.GetBlackboardInterface()
    UnitMenu.BeginSubMenu()
    UnitMenu.SetStayOpen(1)
    UnitMenu.AddItemWithTextParam('May attack Surface      : %s'% (BB.ReadMessage('Flagfree1')  == '1'), 'BBOptionHandler', 'Flagfree1|Toggle|1')
    UnitMenu.AddItemWithTextParam('May attack Aircraft       : %s'% (BB.ReadMessage('Flagfree2')  == '1'), 'BBOptionHandler', 'Flagfree2|Toggle|1')
    UnitMenu.AddItemWithTextParam('May attack Ground       : %s'% (BB.ReadMessage('Flagfree4')  == '1'), 'BBOptionHandler', 'Flagfree4|Toggle|1')
    UnitMenu.AddItemWithTextParam('May attack Missile        : %s'% (BB.ReadMessage('Flagfree8')  == '1'), 'BBOptionHandler', 'Flagfree8|Toggle|1')
    UnitMenu.AddItemWithTextParam('May attack Submarine : %s'% (BB.ReadMessage('Flagfree16')  == '1'), 'BBOptionHandler', 'Flagfree16|Toggle|1')
    UnitMenu.AddItemWithTextParam('Offensive Missile Use : %s'% (BB.ReadMessage('MissileStrikeAllow')  == '1'), 'BBOptionHandler', 'MissileStrikeAllow|Toggle|1')
    if BB.ReadMessage('MissileStrikeAllow') == '1':
        UnitMenu.AddItemWithTextParam('Max Missile Range:  %skm'% (BB.ReadMessage('MissileStrikeRange')), 'BBOptionHandler', 'MissileStrikeRange|Input|Maximum_Offensive_Missile_Range')
    UnitMenu.AddItemWithTextParam('Max Track Error            : %skm'% (BB.ReadMessage('error_km')), 'BBOptionHandler', 'error_km|Input|Maximum_Track_Error')
    UnitMenu.EndSubMenu()

def Amram_Weapon_Officer_ROE_Menu(UnitMenu, UnitInfo):
    BB = UnitInfo.GetBlackboardInterface()
    UnitMenu.BeginSubMenu()
    UnitMenu.SetStayOpen(1)
    UnitMenu.AddItemWithTextParam('Only Valid               : %s'% (BB.ReadMessage('ROE') == '100'), 'BBOptionHandler', 'ROE|Set|100')
    UnitMenu.AddItemWithTextParam('Only None Friendly : %s'% (BB.ReadMessage('ROE') == '4'), 'BBOptionHandler', 'ROE|Set|4')
    UnitMenu.AddItemWithTextParam('Only Hostile             : %s'% (BB.ReadMessage('ROE') == '3'), 'BBOptionHandler', 'ROE|Set|3')
    UnitMenu.AddItemWithTextParam('Only Neutral            : %s'% (BB.ReadMessage('ROE') == '2'), 'BBOptionHandler', 'ROE|Set|2')
    UnitMenu.AddItemWithTextParam('Only Friendly           : %s'% (BB.ReadMessage('ROE') == '1'), 'BBOptionHandler', 'ROE|Set|1')
    UnitMenu.AddItemWithTextParam('Only Unknown         : %s'% (BB.ReadMessage('ROE') == '0'), 'BBOptionHandler', 'ROE|Set|0')
    UnitMenu.EndSubMenu()

def Amram_Helm_Officer_Patrol_Settings_Menu(UnitMenu, UnitInfo):
    BB = UnitInfo.GetBlackboardInterface()
    Patrol_Transit_Pace = AI.Try_Read_Message(BB, 'Patrol_Transit_Pace',2)  #pace of transit to patrol point
    Patrol_Transit_Rules = AI.Try_Read_Message(BB, 'Patrol_Transit_Rules',0)#transit sprint-drift/zig-zag/straight
    Patrol_Stance = AI.Try_Read_Message(BB, 'Patrol_Stance',0)       #aggressiveness of patrol
    Patrol_Patrol_Pace = AI.Try_Read_Message(BB, 'Patrol_Patrol_Pace',2)    #pace during patrol
    Patrol_Patrol_Rules = AI.Try_Read_Message(BB, 'Patrol_Patrol_Rules',0)  #patrol sprint-drift/zig-zag/straight
    Patrol_Focus = AI.Try_Read_Message(BB, 'Patrol_Focus',0)         #patrol purpose
    Patrol_EMCON = AI.Try_Read_Message(BB, 'Patrol_EMCON',0)                #EMCON ruleset
    Patrol_Direction = AI.Try_Read_Message(BB, 'Patrol_Direction',0)   #direction of progress
    Patrol_Type = AI.Try_Read_Message(BB, 'Patrol_Type',0)  #pace of transit to patrol point
    
    UnitMenu.BeginSubMenu()
    UnitMenu.SetStayOpen(1)

    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        UnitMenu.AddItem('Patrol Settings','')
        patrol_settings_submenu(UnitMenu, UnitInfo, Patrol_Transit_Pace, Patrol_Transit_Rules, Patrol_Stance, Patrol_Patrol_Pace, Patrol_Patrol_Rules, Patrol_Focus, Patrol_EMCON, Patrol_Direction, Patrol_Type)

        if 1==1:  #used simply to allow for nesting of the text for the nested menus
            if ((Patrol_Transit_Pace != '') and (Patrol_Transit_Rules != '') and (Patrol_Stance != '') and (Patrol_Patrol_Pace != '') and (Patrol_Focus != '') and (Patrol_EMCON != '') and (Patrol_Direction != '')):
                if Patrol_Type == '':
                    if 1==1:  #used simply to allow for nesting of the text for the nested menus
                        UnitMenu.AddItem('Set Patrol Type:  %s' % Patrol_Type, '')
                        UnitMenu.BeginSubMenu()
                        UnitMenu.SetStayOpen(1)
                        UnitMenu.AddItemWithTextParam('*_Box Spiral', 'BBOptionHandler', 'Patrol_Type|Set|Box Spiral')
                        UnitMenu.AddItemWithTextParam('*_Box Ladder', 'BBOptionHandler', 'Patrol_Type|Set|Box Ladder')
                        UnitMenu.AddItemWithTextParam('*_Box Random', 'BBOptionHandler', 'Patrol_Type|Set|Box Random')
                        UnitMenu.AddItemWithTextParam('Spiral', 'BBOptionHandler', 'Patrol_Type|Set|Spiral')
                        UnitMenu.AddItemWithTextParam('*_Spiral Inverted', 'BBOptionHandler', 'Patrol_Type|Set|Spiral Inverted')
                        UnitMenu.AddItemWithTextParam('*_Radius Random', 'BBOptionHandler', 'Patrol_Type|Set|Radius Random')
                        UnitMenu.AddItemWithTextParam('*_Waypoint', 'BBOptionHandler', 'Patrol_Type|Set|Waypoint')
                        UnitMenu.AddItemWithTextParam('*_Waypoint Loop', 'BBOptionHandler', 'Patrol_Type|Set|Waypoint Loop')
                        UnitMenu.AddItemWithTextParam('*_Waypoint Inverted Loop', 'BBOptionHandler', 'Patrol_Type|Set|Waypoint Inverted Loop')
                        UnitMenu.EndSubMenu()
                else:
                    if 1==1:  #used simply to allow for nesting of the text for the nested menus
                        UnitMenu.AddItem('Start/Stop %s Patrol' % Patrol_Type, '')
                        UnitMenu.BeginSubMenu()
                        UnitMenu.SetStayOpen(1)
                        UnitMenu.AddItemUI('Begin Current Patrol', 'Begin_Patrol_Type', 'Datum')
                        UnitMenu.AddItemWithTextParam('End Current Patrol', 'BBOptionHandler', 'Patrol_Type|Erase|None')
                        UnitMenu.EndSubMenu()
                if 1==1:  #used simply to allow for nesting of the text for the nested menus
                    UnitMenu.AddItem('*_Sprint-Drift Settings', '')
                    UnitMenu.BeginSubMenu()
                    UnitMenu.SetStayOpen(1)
                    if 1==1:  #used simply to allow for nesting of the text for the nested menus
                        UnitMenu.AddItem('*_Rate of Advance', '')
                        SprintDrift_Rate_of_Advance_Menu(UnitMenu, UnitInfo)
                    UnitMenu.EndSubMenu()
                if 1==1:  #used simply to allow for nesting of the text for the nested menus
                    UnitMenu.AddItem('*_Zig-Zag Settings', '')
                    UnitMenu.BeginSubMenu()
                    UnitMenu.SetStayOpen(1)
                    UnitMenu.EndSubMenu()
        UnitMenu.EndSubMenu()
                    
def Transit_Rate_of_Advance_Menu(UnitMenu, UnitInfo):
    BB = UnitInfo.GetBlackboardInterface()
    Patrol_Transit_Pace = AI.Try_Read_Message(BB, 'Patrol_Transit_Pace',2)  #pace of transit to patrol point

    UnitMenu.AddItem('Transit Speed:  %skts' % Patrol_Transit_Pace, '')
#    UnitMenu.AddItemWithTextParam('Ahead Flank'
#    UnitMenu.AddItemWithTextParam('Ahead Standard'
#    UnitMenu.AddItemWithTextParam('Ahead Flank'
#    UnitMenu.AddItemWithTextParam('Ahead Flank'
#    UnitMenu.AddItemWithTextParam('Ahead Flank'

    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        UnitMenu.BeginSubMenu()
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItemUI('Specify Transit Speed','BBoptionHandler', 'Patrol_Transit_Pace|Input|Enter Transit Speed in Knots')
        if UnitInfo.GetMaxSpeed() >= 1000:
            if Patrol_Transit_Pace + 500 <= UnitInfo.GetMaxSpeed():
                UnitMenu.AddItemWithTextParam('Transit Speed +500kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Plus|500')
        if UnitInfo.GetMaxSpeed() >= 500:
            if Patrol_Transit_Pace + 250 <= UnitInfo.GetMaxSpeed():
                UnitMenu.AddItemWithTextParam('Transit Speed +200kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Plus|200')
        if UnitInfo.GetMaxSpeed() >= 200:
            if Patrol_Transit_Pace + 100 <= UnitInfo.GetMaxSpeed():
                UnitMenu.AddItemWithTextParam('Transit Speed +100kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Plus|100')
        if UnitInfo.GetMaxSpeed() >= 100:
            if Patrol_Transit_Pace + 50 <= UnitInfo.GetMaxSpeed():
                UnitMenu.AddItemWithTextParam('Transit Speed +50kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Plus|50')
        if UnitInfo.GetMaxSpeed() >= 20:
            if Patrol_Transit_Pace + 10 <= UnitInfo.GetMaxSpeed():
                UnitMenu.AddItemWithTextParam('Transit Speed +10kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Plus|10')
        if Patrol_Transit_Pace + 5 <= UnitInfo.GetMaxSpeed():
            UnitMenu.AddItemWithTextParam('Transit Speed +5kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Plus|5')
        if Patrol_Transit_Pace + 1 <= UnitInfo.GetMaxSpeed():
            UnitMenu.AddItemWithTextParam('Transit Speed +1kts', 'BBOptionHandler', 'Patrol_Transit_Pace|Plus|1')
        if Patrol_Transit_Pace >= 1:
            UnitMenu.AddItemWithTextParam('Transit Speed -1kts', 'BBOptionHandler', 'Patrol_Transit_Pace|Minus|1')
        if Patrol_Transit_Pace >= 5:
            UnitMenu.AddItemWithTextParam('Transit Speed -5kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Minus|5')
        if UnitInfo.GetMaxSpeed() >= 20:
            if Patrol_Transit_Pace >= 10:
                UnitMenu.AddItemWithTextParam('Transit Speed -10kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Minus|10')
        if UnitInfo.GetMaxSpeed() >= 100:
            if Patrol_Transit_Pace >= 50:
                UnitMenu.AddItemWithTextParam('Transit Speed -50kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Minus|50')
        if UnitInfo.GetMaxSpeed() >= 200:
            if Patrol_Transit_Pace >= 100:
                UnitMenu.AddItemWithTextParam('Transit Speed -100kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Minus|100')
        if UnitInfo.GetMaxSpeed() >= 500:
            if Patrol_Transit_Pace >= 250:
                UnitMenu.AddItemWithTextParam('Transit Speed -200kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Minus|200')
        if UnitInfo.GetMaxSpeed() >= 1000:
            if Patrol_Transit_Pace >= 500:
                UnitMenu.AddItemWithTextParam('Transit Speed -500kts',  'BBOptionHandler', 'Patrol_Transit_Pace|Minus|500')
        UnitMenu.EndSubMenu()

def Patrol_Rate_of_Advance_Menu(UnitMenu, UnitInfo):
    BB = UnitInfo.GetBlackboardInterface()
    Patrol_Patrol_Pace = AI.Try_Read_Message(BB, 'Patrol_Patrol_Pace',2)    #pace during patrol
    
    UnitMenu.AddItem('Patrol Speed:  %skts' % Patrol_Patrol_Pace, '')
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        UnitMenu.BeginSubMenu()
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItemUI('Specify Patrol Speed','BBOptionHandler', 'Patrol_Patrol_Pace|Input|Enter Patrol Speed in Knots')
        if UnitInfo.GetMaxSpeed() >= 1000:
            if Patrol_Patrol_Pace + 500 <= UnitInfo.GetMaxSpeed():
                UnitMenu.AddItemWithTextParam('Patrol Speed +500kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Plus|500')
        if UnitInfo.GetMaxSpeed() >= 500:
            if Patrol_Patrol_Pace + 250 <= UnitInfo.GetMaxSpeed():
                UnitMenu.AddItemWithTextParam('Patrol Speed +200kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Plus|200')
        if UnitInfo.GetMaxSpeed() >= 200:
            if Patrol_Patrol_Pace + 100 <= UnitInfo.GetMaxSpeed():
                UnitMenu.AddItemWithTextParam('Patrol Speed +100kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Plus|100')
        if UnitInfo.GetMaxSpeed() >= 100:
            if Patrol_Patrol_Pace + 50 <= UnitInfo.GetMaxSpeed():
                UnitMenu.AddItemWithTextParam('Patrol Speed +50kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Plus|50')
        if UnitInfo.GetMaxSpeed() >= 20:
            if Patrol_Patrol_Pace + 10 <= UnitInfo.GetMaxSpeed():
                UnitMenu.AddItemWithTextParam('Patrol Speed +10kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Plus|10')
        if Patrol_Patrol_Pace + 5 <= UnitInfo.GetMaxSpeed():
            UnitMenu.AddItemWithTextParam('Patrol Speed +5kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Plus|5')
        if Patrol_Patrol_Pace + 1 <= UnitInfo.GetMaxSpeed():
            UnitMenu.AddItemWithTextParam('Patrol Speed +1kts', 'BBOptionHandler', 'Patrol_Patrol_Pace|Plus|1')
        if Patrol_Patrol_Pace >= 1:
            UnitMenu.AddItemWithTextParam('Patrol Speed -1kts', 'BBOptionHandler', 'Patrol_Patrol_Pace|Minus|1')
        if Patrol_Patrol_Pace >= 5:
            UnitMenu.AddItemWithTextParam('Patrol Speed -5kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Minus|5')
        if UnitInfo.GetMaxSpeed() >= 20:
            if Patrol_Patrol_Pace >= 10:
                UnitMenu.AddItemWithTextParam('Patrol Speed -10kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Minus|10')
        if UnitInfo.GetMaxSpeed() >= 100:
            if Patrol_Patrol_Pace >= 50:
                UnitMenu.AddItemWithTextParam('Patrol Speed -50kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Minus|50')
        if UnitInfo.GetMaxSpeed() >= 200:
            if Patrol_Patrol_Pace >= 100:
                UnitMenu.AddItemWithTextParam('Patrol Speed -100kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Minus|100')
        if UnitInfo.GetMaxSpeed() >= 500:
            if Patrol_Patrol_Pace >= 250:
                UnitMenu.AddItemWithTextParam('Patrol Speed -200kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Minus|200')
        if UnitInfo.GetMaxSpeed() >= 1000:
            if Patrol_Patrol_Pace >= 500:
                UnitMenu.AddItemWithTextParam('Patrol Speed -500kts',  'BBOptionHandler', 'Patrol_Patrol_Pace|Minus|500')
        UnitMenu.EndSubMenu()
       
def ZigZag_Menu(UnitMenu, UnitInfo):
    BB = UnitInfo.GetBlackboardInterface()
    ZigZag_Offset = AI.Try_Read_Message(BB, 'Transit_Sprint_Drift',1)
    Patrol_Sprint_Advance = AI.Try_Read_Message(BB, 'Patrol_Sprint_Advance',1)
    Patrol_Sprint_Drift = AI.Try_Read_Message(BB, 'Patrol_Sprint_Drift',1)

    #drift time
    UnitMenu.BeginSubMenu()
    UnitMenu.SetStayOpen(1)
    Transit_Sprint_Advance = AI.Try_Read_Message(BB, 'Transit_Sprint_Advance',1)
    UnitMenu.AddItem('*Transit Drift Duration:  %ss' % Transit_Sprint_Drift, '')
    UnitMenu.EndSubMenu()
    
def SprintDrift_Rate_of_Advance_Menu(UnitMenu, UnitInfo):
    BB = UnitInfo.GetBlackboardInterface()
    Transit_Sprint_Drift = AI.Try_Read_Message(BB, 'Transit_Sprint_Drift',1)
    Patrol_Sprint_Drift = AI.Try_Read_Message(BB, 'Patrol_Sprint_Drift',1)

    #drift time
    Transit_Sprint_Advance = AI.Try_Read_Message(BB, 'Transit_Sprint_Advance',1)
    UnitMenu.BeginSubMenu()
    UnitMenu.SetStayOpen(1)
    UnitMenu.AddItem('*Transit Drift Duration:  %ss' % Transit_Sprint_Drift, '')
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        UnitMenu.BeginSubMenu()
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItemWithTextParam('*Transit Drift Time +60s', 'BBoptionHandler', 'TransitDriftTime|Plus|60')
        UnitMenu.AddItemWithTextParam('*Transit Drift Time +15s', 'BBoptionHandler', 'TransitDriftTime|Plus|15')
        UnitMenu.AddItemWithTextParam('*Transit Drift Time +5s',  'BBoptionHandler', 'TransitDriftTime|Plus|5')
        UnitMenu.AddItemWithTextParam('*Transit Drift Time -5s',  'BBoptionHandler', 'TransitDriftTime|Minus|-5')
        UnitMenu.AddItemWithTextParam('*Transit Drift Time -15s', 'BBoptionHandler', 'TransitDriftTime|Minus|-15')
        UnitMenu.AddItemWithTextParam('*Transit Drift Time -60s', 'BBoptionHandler', 'TransitDriftTime|Minus|-60')
        UnitMenu.EndSubMenu()
    UnitMenu.AddItem('*Patrol Drift Duration:  %ss' % Transit_Sprint_Drift, '')
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        UnitMenu.BeginSubMenu()
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItemWithTextParam('*Patrol Drift Time +60s', 'BBoptionHandler', 'PatrolDriftTime|Plus|60')
        UnitMenu.AddItemWithTextParam('*Patrol Drift Time +15s', 'BBoptionHandler', 'PatrolDriftTime|Plus|15')
        UnitMenu.AddItemWithTextParam('*Patrol Drift Time +5s',  'BBoptionHandler', 'PatrolDriftTime|Plus|5')
        UnitMenu.AddItemWithTextParam('*Patrol Drift Time -5s',  'BBoptionHandler', 'PatrolDriftTime|Minus|-5')
        UnitMenu.AddItemWithTextParam('*Patrol Drift Time -15s', 'BBoptionHandler', 'PatrolDriftTime|Minus|-15')
        UnitMenu.AddItemWithTextParam('*Patrol Drift Time -60s', 'BBoptionHandler', 'PatrolDriftTime|Minus|-60')
        UnitMenu.EndSubMenu()
    UnitMenu.EndSubMenu()

def SetTransitDriftTime(UI, setvar):
    BB = UI.GetBlackboardInterface()
    Transit_Sprint_Drift = Try_Read_Message(BB, 'Transit_Sprint_Drift',1)
    Transit_Sprint_Drift += setvar
    BB.WriteGlobal('Transit_Sprint_Drift', Transit_Sprint_Drift)
    
def SetPatrolDriftTime(UI, setvar):
    BB = UI.GetBlackboardInterface()
    Patrol_Sprint_Drift = Try_Read_Message(BB, 'Patrol_Sprint_Drift',1)
    Patrol_Sprint_Drift += setvar
    BB.WriteGlobal('Patrol_Sprint_Drift', Patrol_Sprint_Drift)
    
def Amram_Helm_Officer_Nav_Status_Menu(UnitMenu, UnitInfo):
    BB = UnitInfo.GetBlackboardInterface()
    Patrol_Type = AI.Try_Read_Message(BB, 'Patrol_Type',0)  #pace of transit to patrol point
    Patrol_State = AI.Try_Read_Message(BB, 'Patrol_State',0)         #have we begun our patrol or not
    Patrol_Pace = AI.Try_Read_Message(BB, 'Patrol_Patrol_Pace',2)    #pace during patrol
    Transit_Pace = AI.Try_Read_Message(BB, 'Patrol_Transit_Pace',2)  #pace of transit to patrol point

    UnitMenu.BeginSubMenu()
    UnitMenu.SetStayOpen(1)

    UnitMenu.AddItem('Active Patrol:  %s' % Patrol_Type, '')
    UnitMenu.AddItem('Patrol State       : %s' % Patrol_State, '')
    UnitMenu.AddItem('Transit State       : %0.1fkts' % Transit_Pace, '')
    UnitMenu.AddItem('Patrol Speed       : %0.1fKts' % Patrol_Pace, '')
    #range to next destination, co-ordinates
    #current speed, heading
    #ETA : time at est. speed kts.
    #Current fuel, Current range, best range
    #percentage of current patrol completed, if applicable.
    #current helm priority
    UnitMenu.EndSubMenu()
        
def patrol_settings_submenu(UnitMenu, UnitInfo, Patrol_Transit_Pace, Patrol_Transit_Rules, Patrol_Stance, Patrol_Patrol_Pace, Patrol_Patrol_Rules, Patrol_Focus, Patrol_EMCON, Patrol_Direction, Patrol_Type):
    BB = UnitInfo.GetBlackboardInterface()
    UnitMenu.BeginSubMenu()
    UnitMenu.SetStayOpen(1)
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        Transit_Rate_of_Advance_Menu(UnitMenu, UnitInfo)
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        UnitMenu.AddItem('*_Transit Method  : %s' % Patrol_Transit_Rules, '')
        UnitMenu.BeginSubMenu()
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItemWithTextParam('Standard', 'BBOptionHandler', 'Patrol_Transit_Rules|Set|Standard')
        UnitMenu.AddItemWithTextParam('*_Sprint-Drift', 'BBOptionHandler', 'Patrol_Transit_Rules|Set|Sprint-Drift')
        UnitMenu.AddItemWithTextParam('*_Zig-Zag', 'BBOptionHandler', 'Patrol_Transit_Rules|Set|Zig-Zag')
        UnitMenu.EndSubMenu()
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        UnitMenu.AddItem('*_Patrol Stance    : %s' % Patrol_Stance, '')
        UnitMenu.BeginSubMenu()
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItemWithTextParam('*_Passive', 'BBOptionHandler', 'Patrol_Stance|Set|Passive')
        UnitMenu.AddItemWithTextParam('*_Standard', 'BBOptionHandler', 'Patrol_Stance|Set|Standard')
        UnitMenu.AddItemWithTextParam('*_Agressive', 'BBOptionHandler', 'Patrol_Stance|Set|Agressive')
        UnitMenu.EndSubMenu()
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        Patrol_Rate_of_Advance_Menu(UnitMenu, UnitInfo)
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        UnitMenu.AddItem('*_Patrol Method   : %s' % Patrol_Patrol_Rules, '')
        UnitMenu.BeginSubMenu()
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItemWithTextParam('Standard', 'BBOptionHandler', 'Patrol_Patrol_Rules|Set|Standard')
        UnitMenu.AddItemWithTextParam('*_Sprint-Drift', 'BBOptionHandler', 'Patrol_Patrol_Rules|Set|Sprint-Drift')
        UnitMenu.AddItemWithTextParam('*_Zig-Zag', 'BBOptionHandler', 'Patrol_Patrol_Rules|Set|Zig-Zag')
        UnitMenu.EndSubMenu()
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        UnitMenu.AddItem('Patrol Focus      : %s' % Patrol_Focus, '')
        UnitMenu.BeginSubMenu()
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItemWithTextParam('ASW', 'BBOptionHandler', 'Patrol_Focus|Set|ASW')
        UnitMenu.AddItemWithTextParam('ASuW', 'BBOptionHandler', 'Patrol_Focus|Set|ASuW')
        UnitMenu.EndSubMenu()
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        UnitMenu.AddItem('*_Patrol EMCON   : %s' % Patrol_EMCON, '')
        UnitMenu.BeginSubMenu()
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItemWithTextParam('*_All Off', 'BBOptionHandler', 'Patrol_EMCON|Set|All_Off')
        UnitMenu.AddItemWithTextParam('*_Intermittent', 'BBOptionHandler', 'Patrol_EMCON|Set|Intermittent')
        UnitMenu.AddItemWithTextParam('*_Free', 'BBOptionHandler', 'Patrol_EMCON|Set|Free')
        UnitMenu.AddItemWithTextParam('*_All On', 'BBOptionHandler', 'Patrol_EMCON|Set|All_On')
        UnitMenu.EndSubMenu()
    if 1==1:  #used simply to allow for nesting of the text for the nested menus
        UnitMenu.AddItem('~_Patrol Direction : %s' % Patrol_Direction, '')
        UnitMenu.BeginSubMenu()
        UnitMenu.SetStayOpen(1)
        UnitMenu.AddItemWithTextParam('*_North', 'BBOptionHandler', 'Patrol_Direction|Set|North')
        UnitMenu.AddItemWithTextParam('*_East', 'BBOptionHandler', 'Patrol_Direction|Set|East')
        UnitMenu.AddItemWithTextParam('*_South', 'BBOptionHandler', 'Patrol_Direction|Set|South')
        UnitMenu.AddItemWithTextParam('*_West', 'BBOptionHandler', 'Patrol_Direction|Set|West')
        UnitMenu.AddItemWithTextParam('Clockwise', 'BBOptionHandler', 'Patrol_Direction|Set|Clockwise')
        UnitMenu.AddItemWithTextParam('Counter-Clockwise', 'BBOptionHandler', 'Patrol_Direction|Set|Counter-Clockwise')
        UnitMenu.EndSubMenu()
    UnitMenu.EndSubMenu()

def Begin_Patrol_Type(UI, arg1, arg2):
    BB = UI.GetBlackboardInterface()
    patrol_type = AI.Try_Read_Message(BB, 'Patrol_Type', 0)
    UI.AddTask('%s' % patrol_type, 0, 0)
    position = [arg1,arg2]
    AI.Write_Message_List(BB, position, 'Patrol_datum_start')
    AI.Write_Message_List(BB, position, 'Patrol_datum_a')    

def Set_Patrol_Transit_Pace(UI, setvar):
    BB = UI.GetBlackboardInterface()
    Patrol_Transit_Pace = AI.Try_Read_Message(BB, 'Patrol_Transit_Pace',2)  #pace of transit to patrol point
    Patrol_Transit_Pace += float(setvar)
    if Patrol_Transit_Pace > UI.GetMaxSpeed():
        Patrol_Transit_Pace = UI.GetMaxSpeed()
    elif Patrol_Transit_Pace < 0:
        Patrol_Transit_Pace = 0
    BB.WriteGlobal('Patrol_Transit_Pace', str(Patrol_Transit_Pace))

def Set_Patrol_Patrol_Pace(UI, setvar):
    BB = UI.GetBlackboardInterface()
    Patrol_Patrol_Pace = AI.Try_Read_Message(BB, 'Patrol_Patrol_Pace',2)  #pace of transit to patrol point
    Patrol_Patrol_Pace += float(setvar)
    if Patrol_Patrol_Pace > UI.GetMaxSpeed():
        Patrol_Patrol_Pace = UI.GetMaxSpeed()
    elif Patrol_Patrol_Pace < 0:
        Patrol_Patrol_Pace = 0
    BB.WriteGlobal('Patrol_Patrol_Pace', str(Patrol_Patrol_Pace))
      
def Task_Counter(GI, unit_count, task_name):
    counter = 0
    for n in range(0, unit_count):
        UI = GI.GetPlatformInterface(n)
        if UI.TaskExists(task_name):
            counter += 1
    
    return counter

def free_Counter(GI, unit_count):
    freelist = [0,0,0,0,0]
    for n in range(0, unit_count):
        UI = GI.GetPlatformInterface(n)
        BB = UI.GetBlackboardInterface()
        if BB.ReadMessage('Flagfree1') == '1':
            freelist[0] += 1
        if BB.ReadMessage('Flagfree2') == '1':
            freelist[1] += 1
        if BB.ReadMessage('Flagfree4') == '1':
            freelist[2] += 1
        if BB.ReadMessage('Flagfree8') == '1':
            freelist[3] += 1
        if BB.ReadMessage('Flagfree16') == '1':
            freelist[4] += 1
    return freelist
    
def ROE_Counter(GI, unit_count):
    roelist = [0,0,0,0,0,0]
    for n in range(0, unit_count):
        UI = GI.GetPlatformInterface(n)
        BB = UI.GetBlackboardInterface()
        if BB.ReadMessage('ROE') == '100':
            roelist[0] += 1
        if BB.ReadMessage('ROE') == '4':
            roelist[1] += 1
        if BB.ReadMessage('ROE') == '3':
            roelist[2] += 1
        if BB.ReadMessage('ROE') == '2':
            roelist[3] += 1
        if BB.ReadMessage('ROE') == '1':
            roelist[4] += 1
        if BB.ReadMessage('ROE') == '0':
            roelist[5] += 1
    return roelist

def BBOptionHandler(interface, params):
    params = [x.split(';') for x in params.split('|')]
    if len(params[0])>1:
        params = params[0], params[1][0], params[2][0]
    else:
        params = params[0][0], params[1][0], params[2][0]
    #can accept multiple 'variable' parameters, if it finds more than one, it leaves them in a tuple

    try:
        #determine if we are called from GroupInfo or UnitInfo by calling something explicitly UnitInfo.  Success means UnitInfo called us, failure means GroupInfo did.
        test = interface.GetPlatformId()
        group = False
    except:
        group = True
            
    if group:
        for unit in xrange(interface.GetUnitCount()):
            UI = interface.GetPlatformInterface(unit)
            SetBBOption(UI, params)
    else:
        UI = interface
        SetBBOption(UI, params)
        
def SetBBOption(UI, params):
    BB = UI.GetBlackboardInterface()
    if type(params) == type(''):
        #then we got passed back to ourself, so we used getinput last pass.
        params = BB.ReadMessage('temp'), 'Set', params
        BB.Erase('temp')
    variable, method, value = params
    #method might be set, toggle, input, or delete.
    if method == 'Toggle':
        if BB.ReadMessage(variable) == '1':
            BB.WriteGlobal(variable, '0')
        else:
            BB.WriteGlobal(variable, '1')
    elif method == 'Erase':
        BB.Erase(variable)
    elif method == 'Set':
        BB.WriteGlobal(variable, value)
    elif method == 'Input':
        BB.WriteGlobal('temp', variable)
        #try to loop within ourselves by calling ourself when using GetuserInput.
        UI.GetUserInput('SetBBOption', 'Text %s' % value)
    elif method == 'Task' and value == 'Start':
        if type(variable) is list:
            for task in xrange(len(variable)):
                UI.AddTask(variable[task], 0.0, 0)
        else:
            UI.AddTask(variable, 0.0, 0)
    elif method == 'Task' and value == 'Start Hidden':
        if type(variable) is list:
            for task in xrange(len(variable)):
                UI.AddTask(variable[task], -1, 0)
        else:
            UI.AddTask(variable, -1, 0)
    elif method == 'Task' and value == 'End':
        if type(variable) is list:
            for task in xrange(len(variable)):
                if UI.TaskExists(variable[task]):
                    UI.DeleteTask(variable[task])
                if UI.TaskExists(variable[task]):
                    AI.DeleteHiddenTask(UI, variable[task])
        else:
            if UI.TaskExists(variable):
                UI.DeleteTask(variable)
            if UI.TaskExists(variable):
                AI.DeleteHiddenTask(UI, variable)
    elif method == 'Plus':
        var = AI.Try_Read_Message(BB, variable,2)
        value = str(var + float(value))
        BB.WriteGlobal(variable, value)
    elif method == 'Minus':
        var = AI.Try_Read_Message(BB, variable,2)
        value = str(var - float(value))
        BB.WriteGlobal(variable, value)
        