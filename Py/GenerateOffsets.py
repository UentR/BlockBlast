with open("PiecesValue.csv") as T:
    Lines = T.readlines()
    Data = "".join(Lines).split(',\n')


Conv = {}
for value in Data:
    YOff = 0
    XOff = 0
    value = int(value)
    for X in range(1, 8):
        TestValue = value << X
        if TestValue & 9259542123273814144:
            XOff = X
            break
    for Y in range(1, 8):
        TestValue = value << Y*8
        if TestValue & 18374686479671623680:
            YOff = Y
            break
    Conv[value] = (XOff, YOff)


import json

with open("PiecesOffsets.txt", "w") as T:
    t = False
    for key, value in Conv.items():
        if t:
            T.write("\n")
        elif not t:
            t = True
        T.write(f"{key} {value[0]} {value[1]}")