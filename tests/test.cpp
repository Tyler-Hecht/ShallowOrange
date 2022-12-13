#include <catch2/catch_test_macros.hpp>

#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

TEST_CASE("position") {
    Board board;
    board.readFEN("2r3k1/2p2p2/p4Qbp/2p3p1/1q4P1/1P3P1P/2P5/R6K w - - 4 33");
    board.print();
    MoveTree mt(board, 3);
    cout << mt.getBestMove() << endl;
}

TEST_CASE("deep") {
    Board board;
    board.setup();
    Game game(0);
    game.generateDeepGame(3, true);
    cout << game.getPGN() << endl;
}
