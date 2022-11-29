#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    Board board;
    board.readFEN("3Q2R1/1pp2p2/4k2p/p7/4Pb2/8/PP1NP1PP/3QKB1R w K - 1 22");
    MoveTree tree = MoveTree(board, 3, 0);
    cout << tree.getBestMove();
}
