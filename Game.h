#pragma once
#include "Board.h"
#include "MoveTree.h"
#include <map>
#include <vector>
#include <string>

/**
 * @brief A class representing a chess game
 */
class Game {
private:
    Board * board;
    double randomness; // alters the evaluation function by up to this amount in either direction randomly
    std::vector<std::string> moves;
    std::map<std::string, double> * evals; // stores evals so they can be determined faster later
public:
    Game() {
        board = new Board();
        board->setup();
        randomness = 0;
        evals = new std::map<std::string, double>();
    }
    Game(double randomness) {
        std::srand(time(NULL));
        board = new Board();
        board->setup();
        this->randomness = randomness;
        evals = new std::map<std::string, double>();
    }
    ~Game() {
        delete board;
    }
    Game(const Game & other) {
        board = new Board(*other.board);
        moves = other.moves;
        evals = new std::map<std::string, double>(*other.evals);
    }
    Game & operator=(const Game & other) {
        delete board;
        board = new Board(*other.board);
        moves = other.moves;
        randomness = other.randomness;
        evals = new std::map<std::string, double>(*other.evals);
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
     * Also updates the evals map
     * 
     * @return Move The best move
     */
    Move getBestMove();

    /**
     * @brief Gets the best move for the current position at a given depth
     * 
     * @param depth The depth to search to
     * @return Move The best move
     */
    Move getBestMove(int depth);
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
