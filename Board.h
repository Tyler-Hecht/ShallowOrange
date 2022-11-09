#pragma once
#include <string>
#include <vector>
#include "Square.h"
#include "Move.h"

class Board {
    Square * squares[8][8];
    std::string enPassant;
    bool original;
    bool turn; // 0 for white, 1 for black
    bool canCastleKingsideWhite;
    bool canCastleQueensideWhite;
    bool canCastleKingsideBlack;
    bool canCastleQueensideBlack;
public:
    Board(bool original_ = true);
    void setup();
    void print(bool withCoords = false) const;
    void light(std::string square, bool lit = true) {
        getSquare(square)->setLit(true);
    }
    bool move(Move move);
    /**
     * @brief Get the Square object at a given square
     * 
     * @param square A string for the square, such as "e4"
     * @return Square* A pointer to the Square object
     */
    Square * getSquare(std::string square) const {
        int x = square[0] - 'a';
        int y = square[1] - '1';
        return squares[x][y];
    }

    /**
     * @brief Finds all the squares that a knight can move to from a given square
     * 
     * @param square The starting square of the knight
     * @return std::vector<std::string> All possible squares the knight can move to
     */
    std::vector<std::string> knightSquares(std::string square) const;
    /**
     * @brief Finds all the squares that a rook or bishop can move to from a given square
     * 
     * @param square The starting square of the rook or bishop
     * @param rook true if rook, false if bishop
     * @return std::vector<std::string> All possible squares the rook or bishop can move to
     */
    std::vector<std::string> rbSquares(std::string square, bool rook) const;

    /**
     * @brief Finds the square of the king of a given color
     * If there are multiple kings of the same color, returns the first one found
     * 
     * @param color The color of the king to find
     * @return std::string The square the king is on
     */
    std::string findKing(bool color) const;
    /**
     * @brief Determines if a given color is in check
     * 
     * @param color The color of the king to check
     * @return bool Whether or not the king is in check
     */
    bool inCheck(bool color) const;
    /**
     * @brief Determines if a given move is legal
     * 
     * @param move The move to check
     * @return bool Whether or not the move is legal
     */
    bool isLegal(Move move) const;
};
