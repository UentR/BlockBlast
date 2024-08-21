with open("Pieces.csv") as T:
    Lines = T.readlines()
    Data = "".join(Lines).split(',\n')

Line = 4

Conv = []

for Values in Data:
    Value = 0
    Y = 0
    X = 0
    for i in Values:
        match i:
            case "|":
                Y += 1
                X = 0
            case "#":
                Value += 2**(Y*8+X)
                X += 1
            case "~":
                X += 1
            case _:
                pass
    Conv.append(Value)
    # print(Value)
    # print(5/0)
    
    
    # Line = 4
    # Temp = 0
    # Idx = 4
    # for i in Value:
    #     if i == "#":
    #         Temp += 2**(Line*5+Idx)
    #         Idx -= 1
    #     elif i == "|":
    #         Line -= 1
    #         Idx = 4
    #     elif i == "~":
    #         Idx -= 1
    # Conv.append(Temp)

print(Conv)