def GetMessageParam(BB, messageName):
    msg = BB.ReadMessage(messageName)
    if (msg == ''):
        return 0
    else:
        return float(msg)