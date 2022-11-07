#pragma once
#include <string>
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
        int x = square[0] - 'a';
        int y = 8 - (square[1] - '0');
        squares[x][y]->setLit(lit);
    }
    bool move(Move move);
    bool isLegal(Move move) const {return true;}
    Square * getSquare(std::string square) const {
        int x = square[0] - 'a';
        int y = 8 - (square[1] - '0');
        return squares[x][y];
    }
    Square * findKing(bool color) const;
    bool inCheck(bool color) const {return false;}
};
