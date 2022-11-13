#include "Board.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    Board board;
    board.readFEN("rnbqkbnr/pppp1p1p/6p1/4Q3/4P3/8/PPPP1PPP/RNB1KBNR b KQkq - 0 3");
    board.print();
    vector<Move> moves = board.getAllMoves();
    for (Move move : moves) {
        cout << move << ", ";
    }
    cout << board.writeFEN() << endl;
    cout << board.inCheck(0, "e8") << endl;
    return 0;
}
