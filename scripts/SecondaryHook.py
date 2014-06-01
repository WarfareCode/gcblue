from UnitCommands import *

# used for targeting with right mouse click
def ProcessSecondaryHook(UnitInfo, id):
    UnitInfo.PlaySound('LowBeep')
    UnitInfo.SetTarget(id)
    track_info = UnitInfo.GetTargetTrackInfo()
    if (track_info.Affiliation == 1):
        UnitInfo.DisplayMessage('WARNING: targeting friendly platform')
    
