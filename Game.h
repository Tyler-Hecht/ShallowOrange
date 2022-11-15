#pragma once
#include "Board.h"
#include <map>
#include <vector>
#include <string>

/**
 * @brief A class representing a chess game
 */
class Game {
private:
    Board * board;
    std::map<std::string, int> FENcounter;
    int result; // 0 = in progress, 1 = white wins, 2 = black wins, 3 = draw by stalemate, 4 = draw by insufficient material, 5 = draw by 50 move rule, 6 = draw by threefold repetition
    std::vector<std::string> moves;
public:
    Game() : result(0) {
        board = new Board();
        board->setup();
    }
    ~Game() {
        delete board;
    }
    Game(const Game & other) {
        board = new Board(*other.board);
        result = other.result;
    }
    Game & operator=(const Game & other) {
        delete board;
        board = new Board(*other.board);
        result = other.result;
        return *this;
    }
    
    /**
     * @brief Makes a move on the board and updates the result
     * 
     * @param move The move to make
     */
    void makeMove(Move move);
    /**
     * @brief Gets the result of the game
     * 
     * @return std::string The result of the game
     */
    std::string getResult() const;
    /**
     * @brief Gets the portable game notation (PGN) of the game
     * 
     * @return std::string The PGN of the game
     */
    std::string getPGN() const;

    /**
     * @brief Gets the best move for the current position
     * Only uses a depth of 1
     * 
     * @return Move The best move
     */
    Move getBestMove() const;
    /**
     * @brief Plays random moves until the game is over
     * 
     * @param print Whether to print the board and move after each move
     * @param delay The delay between moves in milliseconds
     */
    
    void playRandomGame(bool print = true, int delay = 0);

    /**
     * @brief Plays a game where each side tries to get the best position after one move (depth 1)
     * 
     * @param print Whether to print the board and move after each move
     * @param delay The delay between moves in milliseconds
     */
    void playGreedyGame(bool print = true, int delay = 0);
};
