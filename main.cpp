#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    Game game = Game(0.1);
    game.playGame(3, false);
    cout << game.getPGN() << endl;
}
