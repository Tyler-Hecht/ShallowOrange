#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    Board * board = new Board();
    board->setup();
    MoveTree * tree = new MoveTree(board, 2, 0);
    cout << tree->getBestMove() << endl;
}
