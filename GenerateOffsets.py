with open("PiecesValue.csv") as T:
    Lines = T.readlines()
    Data = "".join(Lines).split(',\n')


Conv = {}
for value in Data:
    Nb = bin(int(value))[2:]
    Nbr = "0"*(25-len(Nb)) + Nb
    Offsets = []
    for Idx, i in enumerate(Nbr):
        if i == "1":
            y, x = divmod(Idx, 5)
            Offsets.append([7-x, 7-y])
    Conv[value] = Offsets

print(Conv, file=open("PiecesOffsets.json", "w"))