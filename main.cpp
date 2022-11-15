#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    Game game;
    game.playGreedyGame(false);
    cout << game.getPGN() << endl;
}
