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
    Board board;
    double randomness; // alters the evaluation function by up to this amount in either direction randomly
    std::vector<std::string> moves;
public:
    Game() {
        board = Board();
        board.setup();
        randomness = 0;
    }
    Game(double randomness) {
        std::srand(time(NULL));
        board = Board();
        board.setup();
        this->randomness = randomness;
    }
    
    /**
     * @brief Makes a move on the board and updates the result
     * 
     * @param move The move to make
     */
    void makeMove(Move & move);
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
     */
    
    void generateRandomGame(bool print = false);

    /**
     * @brief Plays a game where each side tries to get the best position after one move (depth 1)
     * 
     * @param print Whether to print the board and move after each move
     */
    void generateGreedyGame(bool print = false);

    /**
     * @brief Plays a game where each side tries to get the best position at a given depth
     * Uses alpha-beta pruning to determine the best move
     * 
     * @param print Whether to print the board and move after each move
     * @param depth The depth to search to
     */
    void generateDeepGame(int depth = 3, bool print = false);

    /**
     * @brief A game of chess where you play against the engine
     * 
     * @param depth The depth of the engine
     * @param print Whether to print the board after each move
     * @param yourColor Whether you are white (true) or black (false)
     * @param pov What perspective to print the board from (true = white, false = black)
     * @param coords Whether to print the coordinates when printing the board
     */
    void playGame(int depth = 3, bool print = true, bool yourColor = true, bool pov = true, bool coords = false);
};
