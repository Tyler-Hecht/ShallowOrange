#include "Board.h"
#include <iostream>

using namespace std;

int main() {
    Board board;
    board.setup();
    board.move(Move("e2", "e4"));
    board.print();
    vector<string> squares = board.knightSquares("e4");
    for (string square : squares) {
        cout << square << endl;
    }
    return 0;
}
