#include "Board.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    Board board;
    board.readFEN("rnb1kbnr/pppp1ppp/8/4p3/4P2q/5N2/PPPPKPPP/RNBQ1B1R b kq - 3 3");
    board.print();
    vector<Move> moves = board.getAllMoves();
    for (Move move : moves) {
        cout << move << ", ";
    }
    cout << moves.size() << " possible moves" << endl;
    cout << board.writeFEN() << endl;
    return 0;
}
