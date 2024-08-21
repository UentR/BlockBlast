#include "Structs.hpp"

int main() {
    loadPieces();
    // ShowPieces();

    // cout << ((ULL)460551<<(5*8+5)) << endl; 

    Board board;
    board.setBits(72340172838076927); // first row and col 
    board.clearBit(0);
    board.clearBit(1);
    board.clearBit(2);
    board.setBit(10);
    board.addPiece(pieces[2]);
    board.addPiece(pieces[2]);
    board.addPiece(pieces[2]);


    int min = 70;
    vector<Board> BestPossibilities = {};
    for (Board b : board.AllPossibilities()) {
        if (b.countBits() < min) {
            min = b.countBits();
            BestPossibilities.clear();
        } else if (b.countBits() == min) {
            BestPossibilities.push_back(b);
        }
    }
    for (Board b : BestPossibilities) {
        cout << b << endl;
    }

    // Move move{pieces[0], 0, 1};

    // cout << board << endl;

    // board.checkLines();

    // cout << board << endl;
}