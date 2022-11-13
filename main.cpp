#include "Board.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    Board board;
    board.readFEN("5r2/4n2k/Brp5/pP2p1pN/P3P3/K4P1P/2PB3Q/3r2R1 w - - 0 1");
    board.print();
    while (true) {
        vector<Move> moves = board.getAllMoves();
        cout << "Possible moves: " << moves.size() << endl;
        if (moves.size() == 0) {
            cout << "No moves" << endl;
            break;
        }
        board.makeMove(moves[rand() % moves.size()]);
        board.print();
    }
    return 0;
}
