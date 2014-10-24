def RefuelAllAircraft(TI):
    UI = TI.GetPlatformInterface()
    FP = UI.GetFlightPortInfo()
    if (not FP.IsValid()):
        UI.DisplayMessage('No flightport')
        TI.EndTask()

    TI.SetUpdateInterval(60)

    nUnits = FP.GetUnitCount()
    for n in range(0, nUnits):
        unitStatus = FP.GetUnitStatus(n)
        unitName = unitStatus.name
        unitLoc = unitStatus.current_loc
        UI_n = FP.GetUnitPlatformInterface(n)
        if (UI_n.GetFuel() < 1.0) and (not UI_n.IsRefueling()) and (not UI_n.MaintenanceHold()) and (UI_n.GetWeightMargin() > 10):
            #UI_n.DisplayMessage('Refueling %s' % unitName)
            #UI_n.LoadOther('Fuel')   -LoadOther was changed, now requires quantity to stock.  Determine fuel need before attempting to load.
            name = UI_n.GetPlatformClass()
            if UI_n.HasThrottle():
                fuel_capacity = UI.QueryDatabase('air',name,'FuelCapacity_kg')
            else:
                fuel_capacity = UI.QueryDatabase('simple_air',name,'FuelCapacity_kg')
            fuel_capacity = float(fuel_capacity.GetString(0))
            fuel_qty = int((1 - UI_n.GetFuel()) * fuel_capacity + 1)
            UI_n.LoadOther('Fuel', fuel_qty)
            return # only start one refueling at a time
            


def MaintainCAP(TI):
    UI = TI.GetPlatformInterface()
    FP = UI.GetFlightPortInfo()
    if (not FP.IsValid()):
        UI.DisplayMessage('No flightport')
        TI.EndTask()