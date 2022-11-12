#pragma once
#include "Piece.h"

/**
 * @brief A class representing a chess square
 * Contains a pointer to a piece, or NULL if the square is empty
 * Has a lit property if needed
*/
class Square {
    Piece * piece;
    bool lit;
public:
    Square() {
        lit = false;
        piece = NULL;
    }
    Square(const Square & square) {
        lit = square.lit;
        if (square.piece != NULL) {
            piece = new Piece(*square.piece);
        }
        else {
            piece = NULL;
        }
    }
    void setPiece(Piece * piece_) {
        piece = piece_;
    }
    void setLit(bool lit_) {
        lit = lit_;
    }
    bool isLit() const {
        return lit;
    }
    Piece * getPiece() const {
        return piece;
    }/**
     * @brief Turns a rank and file into a square name
     * 
     * @param rank The rank of the square as an integer
     * @param file The file of the square as an integer
     * @return std::string 
     */
};
