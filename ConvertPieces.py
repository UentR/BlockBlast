with open("Pieces.csv") as T:
    Lines = T.readlines()
    Data = "".join(Lines).split(',\n')

Line = 4

Conv = []

for Value in Data:
    Line = 4
    Temp = 0
    Idx = 4
    for i in Value:
        if i == "#":
            Temp += 2**(Line*5+Idx)
            Idx -= 1
        elif i == "|":
            Line -= 1
            Idx = 4
        elif i == "~":
            Idx -= 1
    Conv.append(Temp)

print(Conv)