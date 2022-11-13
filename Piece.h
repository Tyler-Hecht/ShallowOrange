#pragma once
#include <string>
#include <iostream>

/**
 * @brief A class representing a chess piece
 */
class Piece {
    char symbol; // The symbol of the piece, 'P' for pawn
    bool color; //0 for black, 1 for white
public:
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

