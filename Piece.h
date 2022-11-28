#pragma once
#include <string>
#include <iostream>
#include <vector>

/**
 * @brief A class representing a chess piece
 */
class Piece {
    char symbol; // The symbol of the piece, 'P' for pawn
    bool color; //0 for black, 1 for white
public:
    Piece() : symbol('\0'), color(false) {}
    Piece(char symbol_, bool color_) : symbol(symbol_), color(color_) {}
    char getSymbol() const {
        return symbol;
    }
    bool getColor() const { return color; }
    void promote(char symbol_) {
        if (symbol == 'P') {
            symbol = symbol_;
        }
    }
    /**
     * @brief Gets the point value of the piece
     * Pawn = 1, Knight = 3, Bishop = 3, Rook = 5, Queen = 9, King = 0
     * 
     * @return int The point value of the piece
     */
    int pointValue() const;
    /**
     * @brief Gets the adjustment to the point value of the piece based on its location
     * 
     * @param square The square the piece is on
     * @param phase The phase of the game (0 for opening, 1 for middle game, 2 for endgame)
     * @return double The adjustment to be made
     */
    double locationAdjustment(std::string square, int phase) const;
    /**
     * @brief Gets a table of the piece's adjusted value based on its location
     * 
     * @param phase The phase of the game (0 for opening, 1 for middle game, 2 for endgame)
     * @return std::vector<std::vector<double>> The table
     */
    std::vector<std::vector<double>> getPieceTable(int phase) const;
};

/**
 * @brief Overloads the << operator for Piece
 * Spits out the symbol of the piece, with pawns being P or p
 * Uppercase for white, lowercase for black
 * 
 * @param os The ostream to output to
 * @param piece The piece to output
 * @return std::ostream& The ostream
 */
std::ostream& operator<<(std::ostream& os, const Piece& piece);

