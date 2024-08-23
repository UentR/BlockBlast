#include "Structs.hpp"

int main() {
    srand(time(NULL));
    loadPieces();

    Board board;

    while (true) {
        cout << board << endl;
        board.MakeMove();
    }
    return 0;
}