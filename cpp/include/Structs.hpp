#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <stdlib.h>     
#include <time.h> 

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

inline unsigned short Coeffs[64] = {1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 5, 10, 10, 5, 1, 1, 1, 5, 10, 17, 17, 10, 5, 1, 2, 10, 17, 39, 39, 17, 10, 2, 2, 10, 17, 39, 39, 17, 10, 2, 1, 5, 10, 17, 17, 10, 5, 1, 1, 1, 5, 10, 10, 5, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1};

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
        vector<Piece> CurrentPieces;
        int points;
    
    public:
        void addPoints(int P) { points += P; }

        int getPoints() const; // { return points; }

        ULL getBoard() const { return BitMaskBoard; }

        bool getBit(int index) const { return BitMaskBoard & (1ULL << index); }

        vector<Piece> getPieces() const { return CurrentPieces; }

        void setPieces(vector<Piece> pieces) { this->CurrentPieces = pieces; }

        void addPiece(Piece piece) { CurrentPieces.push_back(piece); }

        void removePiece(int index) { CurrentPieces.erase(CurrentPieces.begin() + index); }

        void removePiece(Piece p) {
            for (size_t i = 0; i < CurrentPieces.size(); i++) {
                if (CurrentPieces[i].BitMask.Bits == p.BitMask.Bits) {
                    CurrentPieces.erase(CurrentPieces.begin() + i);
                    return;
                }
            }
        }

        void clearPieces() { CurrentPieces.clear(); }

        void clear() { BitMaskBoard = 0; CurrentPieces.clear(); }
        
        void setBoard(ULL Board) { BitMaskBoard = Board; }

        void setBit(int index) { BitMaskBoard |= 1ULL << index; }

        void setBits(ULL index) { BitMaskBoard |= index; }

        void clearBit(int index) { BitMaskBoard &= ~(1ULL << index); }

        int countBits() const { return __builtin_popcountll(BitMaskBoard); };

        void clearBoard() { BitMaskBoard = 0; }

        void checkLines();

        vector<Board> AllPossibilities() const;

        vector<Move> AllMoveForPiece(Piece p) const;

        void MakeMove();

        Board() {
            BitMaskBoard = 0;
            points = 0;
            for (int i=0; i<64; i++) {
                BitMaskBoard |= ((ULL)((rand() % 3)&2)>>1) << i;
            }
            CurrentPieces = {};
            for (int i=0; i<3; i++) {
                CurrentPieces.push_back(pieces[rand() % 41]);
            }
        }

        Board(ULL Board) : BitMaskBoard{Board}, CurrentPieces{{}}, points{0} {}

        Board operator=(const Board& board) { BitMaskBoard = board.getBoard(); CurrentPieces = board.getPieces(); return *this; }
};

ostream& operator<<(ostream& os, const Board& board);

ostream& operator<<(ostream& os, const Move& move);

Board operator+(const Board& board, const Move& m);

#endif