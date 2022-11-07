#pragma once
#include <string>
#include <iostream>

class Piece {
    int type; // 0 = pawn, 1 = knight, 2 = bishop, 3 = rook, 4 = queen, 5 = king
    bool color; //0 for white, 1 for black
public:
    Piece(char symbol, bool color_) {
        color = color_;
        switch (symbol) {
        case 'P':
            type = 0;
            break;
        case 'N':
            type = 1;
            break;
        case 'B':
            type = 2;
            break;
        case 'R':
            type = 3;
            break;
        case 'Q':
            type = 4;
            break;
        case 'K':
            type = 5;
            break;
        }
    }
    char getSymbol() const {
        switch (type) {
        case 0:
            return '\0';
        case 1:
            return 'N';
        case 2:
            return 'B';
        case 3:
            return 'R';
        case 4:
            return 'Q';
        case 5:
            return 'K';
        }
        return '\0';
    }
    bool getColor() const { return color; }
    void promote(int type_) {
        if (type == 0) {
            type = type_;
        }
    }
};

std::ostream& operator<<(std::ostream& os, const Piece& piece);

