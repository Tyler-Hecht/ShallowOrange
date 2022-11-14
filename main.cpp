#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    Game game;
    game.playRandomGame(0, false);
    cout << game.getPGN() << endl;
    return 0;
}
