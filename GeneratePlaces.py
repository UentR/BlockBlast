import json
with open("PiecesOffsets.json") as T:
    data = json.load(T)

import numpy as np

Final = {key:[] for key in data.keys()}

for key, value in data.items():
    for y in range(8):
        for x in range(8):
            Offset = np.array([x, y])
            Dt = np.array(value)
            Offseted = (Dt-Offset)
            if all(0 <= Offseted.flatten()) and all(8 >= Offseted.flatten()):
                Temp = 0
                for X, Y in Offseted:
                    Temp += 2**((Y*8)+X)
                Final[key].append(np.uint(Temp))

print(Final.values(), file=open('Temp.txt', "w"))


# print(sum(len(T) for T in Final.values()))