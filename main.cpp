#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    Board * board = new Board();
    board->setup();
    auto start = chrono::high_resolution_clock::now();
    MoveTree tree(board, 3);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << duration.count() * 1e-6 << endl;
}
