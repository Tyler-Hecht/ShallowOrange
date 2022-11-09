#pragma once
#include <string>
#include <vector>
#include "Square.h"
#include "Move.h"

/**
 * @brief A class representing a chess board
 * Contains information about the board, including:
 * - The squares on the board (including the pieces on them)
 * - Which color's turn it is
 * - What castling is possible
 * - What en passant is possible
 */
class Board {
    Square * squares[8][8];
    std::string enPassant;
    bool turn; // 0 for white, 1 for black
    bool canCastleKingsideWhite;
    bool canCastleQueensideWhite;
    bool canCastleKingsideBlack;
    bool canCastleQueensideBlack;
public:
    Board();
    Board(const Board & board);
    void setup();
    void print(bool withCoords = false) const;
    void light(std::string square, bool lit = true) {
        getSquare(square)->setLit(true);
    }
    /**
     * @brief Makes a move on the board, updating relevant member variables
     * 
     * @param move The move to make
     */
    void makeMove(Move move);
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
     * @brief Determines if a king would be in check if it were on a given square
     * 
     * @param color The color of the king
     * @param square The square the king would be on
     * @return bool Whether the king would be in check
     */
    bool inCheck(bool color, std::string kingSquare) const;
    /**
     * @brief Determines if a given move is legal
     * A move is legal if it is not a move that would put the king in check
     * or tries to castle in or through check
     * 
     * @param move The move to check
     * @return bool Whether or not the move is legal
     */
    bool isLegal(Move move) const;

    /**
     * @brief Gets all the possible legal moves for a given square
     * The piece on the square must be the same color as the turn
     * 
     * @param square The square to get the moves for
     * @return std::vector<Move> All the possible moves for the square
     */
    std::vector<Move> getMoves(std::string square) const;
};
