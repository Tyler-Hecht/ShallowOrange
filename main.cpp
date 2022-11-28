#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    Game game = Game(0);
    game.generateDeepGame(3, true);
    cout << game.getPGN() << endl;
}
