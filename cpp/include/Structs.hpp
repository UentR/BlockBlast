#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#define ULL unsigned long long

using namespace std;

const string Vertical = "┃";
const string Top = "┏━━━━━━━━━━━━━━━━━┓";
const string Bottom = "┗━━━━━━━━━━━━━━━━━┛";



struct Mask {
    int Bits;
};

struct Piece {
    int Xrange, Yrange;
    Mask BitMask;
};

inline Piece pieces[41];

// inline const int BASE = 8;
// inline const unsigned long long COLUMNS[BASE] = {72340172838076673, 144680345676153346, 289360691352306692, 578721382704613384, 1157442765409226768, 2314885530818453536, 4629771061636907072, 9259542123273814144};
// inline const unsigned long long ROWS[BASE] = {255, 65280, 16711680, 4278190080, 1095216660480, 280375465082880, 71776119061217280, 18374686479671623680};

struct Move {
    Piece p;
    int X, Y;

    Move(Piece p, int X, int Y) {
        if (X<0 || X >p.Xrange || Y<0 || Y>p.Yrange) {
            cout << "Error: Move out of range" << endl;
            return;
        }
        this->p = p;
        this->X = X;
        this->Y = Y;
    }
};

// Overload the << operator for the Mask struct
ostream& operator<<(ostream& os, const Mask& mask);

ostream& operator<<(ostream& os, const Piece& piece);

void loadPieces();

void ShowPieces();


class Board {
    private:
        ULL BitMaskBoard;
        vector<Piece> pieces;
        int points;
    
    public:
        void addPoints(int P) { points += P; }

        int getPoints() const { return points; }

        ULL getBoard() const { return BitMaskBoard; }

        bool getBit(int index) const { return BitMaskBoard & (1ULL << index); }

        vector<Piece> getPieces() const { return pieces; }

        void setPieces(vector<Piece> pieces) { this->pieces = pieces; }

        void addPiece(Piece piece) { pieces.push_back(piece); }

        void removePiece(int index) { pieces.erase(pieces.begin() + index); }

        void removePiece(Piece p) {
            for (size_t i = 0; i < pieces.size(); i++) {
                if (pieces[i].BitMask.Bits == p.BitMask.Bits) {
                    pieces.erase(pieces.begin() + i);
                    return;
                }
            }
        }

        void clearPieces() { pieces.clear(); }

        void clear() { BitMaskBoard = 0; pieces.clear(); }
        
        void setBoard(ULL Board) { BitMaskBoard = Board; }

        void setBit(int index) { BitMaskBoard |= 1ULL << index; }

        void setBits(ULL index) { BitMaskBoard |= index; }

        void clearBit(int index) { BitMaskBoard &= ~(1ULL << index); }

        int countBits() const { return __builtin_popcountll(BitMaskBoard); };

        void clearBoard() { BitMaskBoard = 0; }

        void checkLines();

        vector<Board> AllPossibilities() const;

        vector<Move> AllMoveForPiece(Piece p) const;

        Board() : BitMaskBoard{0} {}

        Board(ULL Board) : BitMaskBoard{Board} {}

        Board operator=(const Board& board) { BitMaskBoard = board.getBoard(); return *this; }
};

ostream& operator<<(ostream& os, const Board& board);

ostream& operator<<(ostream& os, const Move& move);

Board operator+(const Board& board, const Move& m);

#endif