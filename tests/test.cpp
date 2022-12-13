#include <catch2/catch_test_macros.hpp>

#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

TEST_CASE("position") {
    Board board;
    board.readFEN("1r4nr/ppnk1p2/2p3pb/3ppP1p/3P2b1/4B1PN/PP1QP2P/RN2KBR1 w Q e6 0 20");
    vector<Move> moves = board.getAllMoves();
    for (Move move : moves) {
        cout << move << endl;
    }
}

TEST_CASE("random") {
    Game game;
    game.generateRandomGame();
    cout << game.getPGN() << endl;
}

TEST_CASE("deep") {
    Game game(0);
    game.generateDeepGame(3, true);
    cout << game.getPGN() << endl;
}
