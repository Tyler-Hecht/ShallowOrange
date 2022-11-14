#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    Game game;
    game.playGreedyGame();
    cout << game.getPGN() << endl;
}
