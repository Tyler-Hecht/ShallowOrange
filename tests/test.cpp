#include <catch2/catch_test_macros.hpp>

#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

TEST_CASE("random") {
    Game game;
    game.generateRandomGame();
    cout << game.getPGN() << endl;
}

TEST_CASE("greedy") {
    Game game(1);
    game.generateGreedyGame();
    cout << game.getPGN() << endl;
}

TEST_CASE("deep") {
    Game game(0);
    game.generateDeepGame(3, true);
    cout << game.getPGN() << endl;
}
