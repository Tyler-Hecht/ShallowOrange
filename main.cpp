#include "Board.h"
#include <iostream>

using namespace std;

int main() {
    Board board;
    board.setup();
    board.makeMove(Move('P', "e2", "e4"));
    board.print();
    vector<Move> moves = board.getNBRMoves("b1", 'N');
    for (Move move : moves) {
        cout << move.toString() << endl;
    }
    return 0;
}
