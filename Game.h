#pragma once
#include "Board.h"

/**
 * @brief A class representing a chess game
 */
class Game {
private:
    Board * board;
public:
    Game() {
        board = new Board();
        board->setup();
    }
    ~Game() {
        delete board;
    }
    Game(const Game & other) {
        board = new Board(*other.board);
    }
    Game & operator=(const Game & other) {
        delete board;
        board = new Board(*other.board);
        return *this;
    }
};
