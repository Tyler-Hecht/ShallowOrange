#include <catch2/catch_test_macros.hpp>

#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

TEST_CASE("Generate depth 3") {
    MoveTree mt;
    Board board;
    board.setup();
    Game game(0);
    game.generateDeepGame(3, true);
    cout << game.getPGN() << endl;
}
