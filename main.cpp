#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    Game game;
    game.playRandomGame();
    cout << game.getPGN() << endl;
    return 0;
}
