#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    // time the creation of a new movetree
    Game * game = new Game(0);
    auto start = chrono::high_resolution_clock::now();
    game->playGreedyGame(false);
    cout << "Done playing a greedy game." << endl;
    auto end = chrono::high_resolution_clock::now();
    cout << game->getPGN() << endl;
    cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() * 0.001 << " seconds" << endl;
    delete game;
}
