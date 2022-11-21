#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    // time the creation of a new movetree
    Board * board = new Board();
    board->setup();
    std::map<std::string, double> * evals = new std::map<std::string, double>();
    auto start = chrono::high_resolution_clock::now();
    MoveTree * tree = new MoveTree(board, 2, 0.5, evals);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time taken to create a new movetree: " << duration.count() * 1e-6 << " seconds" << endl;
    delete tree;
}
