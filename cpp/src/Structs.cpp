#include "Structs.hpp"

// Overload the << operator for the Mask struct
ostream& operator<<(ostream& os, const Mask& mask) {
    int X, Y, Power;
    for (int i=15; i>=0; i--) {
        X = i % 4;
        Y = i / 4;
        Power = Y*8 + X;
        if (mask.Bits & (1 << Power)) {
            os << "⬛";
        } else {
            os << "⬜";
        }
        if (i % 4 == 0 && i != 0) {
            os << "\n";
        }
    }
    return os;
}

ostream& operator<<(ostream& os, const Piece& piece) {
    os << "Xrange: " << piece.Xrange << "\n";
    os << "Yrange: " << piece.Yrange << "\n";
    os << "BitMask: \n" << piece.BitMask;
    return os;
}

void loadPieces() {
    // Read PiecesOffsets.txt
    FILE *file = fopen("Py/PiecesOffsets.txt", "r");
    if (file == NULL) {
        cout << "Error: File not found" << endl;
        return;
    }

    int Xrange, Yrange, BitMask;
    for (int i = 0; i < 41; i++) {
        if (!fscanf(file, "%d %d %d", &BitMask, &Xrange, &Yrange)) {
            cout << "Error: File not formatted correctly" << endl;
            fclose(file);
            return;
        }
        pieces[i] = {Xrange, Yrange, BitMask};
    }
    fclose(file);
}

void ShowPieces() {
    for (int i = 0; i < 41; i++) {
        cout << pieces[i] << endl;
    }
}

ostream& operator<<(ostream& os, const Board& board) {
    ULL power = pow(2, 63);
    for (int i=63; i>=0; i--) {
        if (board.getBoard() & power) {
            os << "⬛";
        } else {
            os << "⬜";
        }
        if (i % 8 == 0 && i != 0) {
            os << "\n";
        }
        power >>= 1;
    }
    return os;
}

ostream& operator<<(ostream& os, const Move& move) {
    ULL power = pow(2, 63);
    ULL PieceBitMask = (ULL)move.p.BitMask.Bits << (move.Y*8 + move.X);
    for (int i=63; i>=0; i--) {
        if (PieceBitMask & power) {
            os << "⬛";
        } else {
            os << "⬜";
        }
        if (i % 8 == 0 && i != 0) {
            os << "\n";
        }
        power >>= 1;
    }
    return os;
}

void Board::checkLines() {
    ULL row = 0b11111111;
    ULL column = 0b100000001000000010000000100000001000000010000000100000001;
    ULL mask;
    ULL TotalMask = 0;
    mask = row;
    for (int i=0; i<8; i++) {
        if ((BitMaskBoard & mask) == mask) {
            TotalMask |= mask;
        }
        mask <<= 8;
    }
    mask = column;
    for (int i=0; i<8; i++) {
        if ((BitMaskBoard & mask) == mask) {
            TotalMask |= mask;
        }
        mask <<= 1;
    }

    BitMaskBoard &= ~TotalMask;
}

Board operator+(const Board& board, const Move& m) {
    Board NewBoard = board;
    ULL NewMask = (ULL)m.p.BitMask.Bits << (m.Y*8 + m.X); 
    NewBoard.setBits(NewMask);
    NewBoard.checkLines();
    return NewBoard;
}

vector<Move> Board::AllMoveForPiece(Piece p) const {
    vector<Move> NewBoards = {};
    ULL PieceMaskBits = p.BitMask.Bits;
    for (int x=0; x<=p.Xrange; x++) {
        for (int y=0; y<=p.Yrange; y++) {
            if (!(BitMaskBoard & (PieceMaskBits << (y*8 + x)))) { // If Board and Piece (moved to x, y) don't overlap
                NewBoards.push_back(Move{p, x, y});
            }
        }
    }
    return NewBoards;
}

vector<Board> Board::AllPossibilities() const {
    if (pieces.size() == 0) return {*this};

    vector<Board> NewBoards;
    for (Piece P : pieces) {                        // Loop through pieces available
        for (Move M : AllMoveForPiece(P)) {         // Loop through all possibilities with said piece (I)
            Board B = *this + M;                    // Create a new board with said piece
            B.removePiece(P);                       // Remove said piece
            for (Board b : B.AllPossibilities()) {  // Loop through all possibilities of I with remaining pieces
                NewBoards.push_back(b);
            }
        }
    }
    return NewBoards;
}