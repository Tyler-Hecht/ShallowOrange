#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    // time the creation of a new movetree
    Game * game = new Game(0);
    auto start = chrono::high_resolution_clock::now();
    game->playDeepGame(true, 2);
    auto end = chrono::high_resolution_clock::now();
    //game->playGreedyGame(false);
    cout << game->getPGN() << endl;
    cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
    delete game;
}
