#include "Board.h"
#include <iostream>

using namespace std;

int main() {
    Board board;
    board.setup();
    board.makeMove(Move('P', "e2", "e4"));
    board.makeMove(Move('P', "e7", "e5"));
    board.print();
    vector<Move> moves = board.getAllMoves();
    for (Move move : moves) {
        cout << move.toString() << ", ";
    }
    return 0;
}
