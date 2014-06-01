from random import *

deg_to_rad = 0.01745329252
rad_to_deg = 57.2957795131

# workaround that passes UI object when nothing is hooked to
# do a command pass-through
def YellowBlueMap(UI):
    UI.SendCommand("YellowBlueMap")
    
def CopperMap(UI):
    UI.SendCommand("CopperMap")
    
def BlackBlueMap(UI):
    UI.SendCommand("BlackBlueMap")
    
def AddMapText(SI, lon, lat):
    SI.OverlayTextInteractive('', rad_to_deg*lon, rad_to_deg*lat)

