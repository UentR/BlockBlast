import numpy as np
from multiprocessing import Process, Manager

BASE = 8

COLUMNS = print(np.array([sum(2**(BASE*j+c) for j in range(BASE)) for c in range(BASE)]))
ROWS = np.array([np.uint(sum(2**(BASE*c+j) for j in range(BASE))) for c in range(BASE)])

def NewState(State):
    # doesn't work if row and column
    New = State
    for c in COLUMNS:
        if State&c == c:
            New = New&(~c)
    for r in ROWS:
        if State&r == r:
            New = New&(~r)
    return New

def TestAll(ToTest, WillTest, Data, Done, NextDone):
    while not Done.get() or ToTest.qsize():
        State, Pieces, Path = ToTest.get(block=True)
        for Idx, CurrentPiece in enumerate(Pieces):
            for AllPos in Data[str(CurrentPiece)]:
                if not (State&AllPos):
                    WillTest.put((NewState(State|AllPos), np.delete(Pieces, Idx), Path+[AllPos]))
    NextDone.set(True)

manager = Manager()

First = manager.Queue()
Second = manager.Queue()
Third = manager.Queue()
Final = manager.Queue()
FirstDone = manager.Value(bool, False)
SecondDone = manager.Value(bool, False)
ThirdDone = manager.Value(bool, False)
Scoring = manager.Value(bool, False)

Pieces = [30306304, 25952256, 16777216, 17318416, 17318400, 17317888, 17301504, 32505856, 31457280, 29360128, 25165824, 25690112, 25427968, 9175040, 17563648, 17330176, 29900800, 29495296, 4354048, 17580032, 29622272, 9183232, 9306112, 25706496, 29491200, 8675328, 17694720, 25436160, 5111808, 17326080, 29884416, 25976832, 30277632, 9191424, 25559040, 17571840, 13369344, 4472832, 17043456, 8912896, 17039360]
Pieces = np.array(list(map(np.uint, Pieces)))

import json
data = json.load(open("PiecesPlaces.json"))
data = {key: np.array(list(map(np.uint, value))) for key, value in data.items()}



from game import Board

# state = np.uint(Board.Create(input()).State)
state = np.uint(0)
pieces = np.array([Pieces[2], Pieces[2], Pieces[2]])


One = Process(target=TestAll, args=(First,Second,data,FirstDone,SecondDone))
Two = Process(target=TestAll, args=(Second,Third,data,SecondDone,ThirdDone))
Three = Process(target=TestAll, args=(Third,Final,data,ThirdDone,Scoring))

One.start()
Two.start()
Three.start()
input()

FirstDone.set(True)

First.put((state, pieces, list()))

Min = np.ubyte(65)
Path = list()
State = np.uint()
while not Scoring.get() or Final.qsize():
    # print(First.qsize(), Second.qsize(), Third.qsize(), Final.qsize())
    DState, _, DPath = Final.get(block=True)
    # print(DState)
    if not DState: continue
    Score = 0
    for i in str(np.binary_repr(State)):
        Score += int(i)
    if Score < Min:
        Min = Score
        Path = DPath[::]
        State = DState

print(Board(State))
[print(Board(O)) for O in Path]
print(Score)




# from time import sleep

# while Three.is_alive():
#     print(First.qsize(), Second.qsize(), Third.qsize(), Final.qsize())
#     sleep(1)

# Fin = np.ndarray(shape=(Final.qsize()), dtype=np.uint)

# t = 0
# while Final.qsize():
#     Fin[t] = Final.get()[0]
#     t += 1

# print(Fin)
# print(Fin, file=open('Temp.txt', "w"))
# print(len(Fin))