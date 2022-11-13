#include "Board.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    Board board;
    board.readFEN("8/5P2/8/1n6/2k3K1/8/8/8 w - - 0 1");
    board.print();
    /*
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
    */
    return 0;
}
