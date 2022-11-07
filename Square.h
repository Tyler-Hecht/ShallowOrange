#pragma once
#include "Piece.h"

class Square {
    Piece * piece;
    bool lit;
public:
    Square() {
        lit = false;
        piece = NULL;
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
    }
};
