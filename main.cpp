#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    // time the creation of a new movetree
    Board * board = new Board();
    board->setup();
    auto start = chrono::high_resolution_clock::now();
    MoveTree * tree = new MoveTree(board, 4, 0);
    auto middle = chrono::high_resolution_clock::now();
    cout << tree->getBestMove() << endl;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end - middle);
    cout << "Time taken: " << duration.count() * 1e-6 << " seconds" << endl;
    cout << "Time taken: " << duration2.count() * 1e-6 << " seconds" << endl;
    delete tree;
}
