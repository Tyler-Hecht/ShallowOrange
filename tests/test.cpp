#include <catch2/catch_test_macros.hpp>

#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

TEST_CASE("Generate depth 3") {
    Board board;
    board.setup();
    Game game(0);
    auto start = chrono::high_resolution_clock::now();
    game.generateDeepGame(3, true);
    cout << game.getPGN() << endl;
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time taken: " << duration.count() * 0.001 << " seconds" << endl;
}
