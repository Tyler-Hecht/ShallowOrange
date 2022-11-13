#include "Move.h"
#include <iostream>

using namespace std;

string Move::toString() const {
    if (castle) {
        if (to[0] == 'g') {
            return "O-O";
        }
        else {
            return "O-O-O";
        }
    }
    string move = "";
    if (piece == 'P') {
        if (capture) {
            move += from[0];
        }
    }
    else {
        move += piece;
        if (disambiguation != "") {
            move += disambiguation;
        }
    }
    if (capture) {
        move += "x";
    }
    move += to;
    if (promotion) {
        move += "=";
        move.push_back(promotionType);
    }
    if (checkmate) {
        move += "#";
    } else {
        if (check) {
            move += "+";
        }
    }
    if (enPassant) {
        move += "!!";
    }
    return move;
}

ostream &operator<<(ostream &os, const Move &move) {
    os << move.toString();
    return os;
}
