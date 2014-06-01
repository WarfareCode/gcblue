import math

deg_to_rad = 0.01745329252

def GetMessageParam(BB, messageName):
    msg = BB.ReadMessage(messageName)
    if (msg == ''):
        return 0
    else:
        return float(msg)
 

# abs() of difference between two radian headings
def RadianHeadingDiff(h1, h2):
    delta = h1 - h2
    if (delta < -3.14159):
        delta = delta + 6.28318
    elif (delta > 3.14159):
        delta = delta - 6.28318
    if (delta < 0):
        delta = -delta
    return delta




