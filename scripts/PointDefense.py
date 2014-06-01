from UnitCommands import *
from GroupCommands import *
import math
import random


    
def GetPointDefenseLaunchers(UI):
    # build list of all launcher info
    launcher_list = []
    nLaunchers = UI.GetLauncherCount()
    for n in range(0, nLaunchers):
        launcher_info = UI.GetLauncherInfo(n)
        if ((launcher_info.Status == 0) and (launcher_info.TargetFlags & 0x0008) and (launcher_info.MinRange_km < 1.0)):
            launcher_list.append(launcher_info)
    return launcher_list
   
def GetPointDefenseTargets(UI):
    class_mask = 0x0060 # missiles and aircraft
    range_km = 8.0
    affiliation = 3 # hostile
    track_list = UI.GetTrackList(class_mask, range_km, affiliation)
    targets = []
    current_time = UI.GetTime()
    max_engaged_count = 10
    
    nTracks = track_list.Size()
    for n in range(0, nTracks):
        track_info = track_list.GetTrack(n)
        track_id = track_info.ID
        staleness = current_time - track_info.Time
        is_destroyed = track_info.IsDestroyed()
        bearing_only = track_info.IsBearingOnly()
        engaged_count = track_info.GetEngagedCount()
        is_air_target = track_info.IsAir() or track_info.IsMissile()
        if ((engaged_count < max_engaged_count) and (staleness < 15.0) and (not bearing_only) and (not is_destroyed) and is_air_target):
            targets.append(track_info)
            
    return targets
    
# script to augment EngageAll for better point defense reaction
def PointDefense(UI):
    target_list = GetPointDefenseTargets(UI)
    nTargets = len(target_list)
    if (nTargets == 0):
        return
    launcher_list = GetPointDefenseLaunchers(UI)
    
    for k in range(0, len(launcher_list)):
        launcher_info = launcher_list[k]
        launcher_idx = launcher_info.Launcher
        # engage first target in random target order
        target_order = random.sample(range(0, nTargets), nTargets)
        selected_target = -1
        for n in target_order:
            track_info = target_list[n]
            target_range = UI.GetRangeToTrack(track_info)
            launch_range = launcher_info.Range_km  # reference max range, use for launch decision
            
            #UI.DisplayMessage('Best launcher %d' % launcher_idx)
            if (launcher_idx != -1):
                target_range = UI.GetRangeToTarget()
                launch_range = launcher_info.Range_km  # reference max range, use for launch decision
                if ((selected_target == -1) and (target_range < launch_range)):
                    selected_target = track_info.ID
                    break
        if (selected_target != -1):
            UI.SendTargetToLauncher(selected_target, launcher_idx)
            UI.Launch(launcher_idx, 1)
                


    
    
        




