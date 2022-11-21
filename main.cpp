#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    Game game(0.3);
    game.playGreedyGame(false);
    cout << game.getPGN() << endl;
}
