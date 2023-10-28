import numpy as np

class Board:
    def __init__(self, Nbr):
        self.State = np.uint(Nbr)

    def __repr__(self) -> str:
        N = 3
        Base = 8
        nb = str(np.binary_repr(self.State))
        nb = "0" * (Base*Base - len(nb)) + nb
        msg = "-"*(1+(N+1)*Base) + "\n"
        for Power in range(Base*Base):
            msg += "|" 
            msg += "█"*N if nb[Power] == "1" else " "*N
            if not (Power+1)%Base:
                msg += "|\n" + "-"*(1+(N+1)*Base) + "\n"
        return msg

Data = [30306304, 25952256, 16777216, 17318416, 17318400, 17317888, 17301504, 32505856, 31457280, 29360128, 25165824, 25690112, 25427968, 9175040, 17563648, 17330176, 29900800, 29495296, 4354048, 17580032, 29622272, 9183232, 9306112, 25706496, 29491200, 8675328, 17694720, 25436160, 5111808, 17326080, 29884416, 25976832, 30277632, 9191424, 25559040, 17571840, 13369344, 4472832, 17043456, 8912896, 17039360]

T = Board(-9205357638345293824)
print(T)