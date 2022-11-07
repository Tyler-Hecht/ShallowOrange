#include "Piece.h"

using namespace std;

ostream& operator<<(ostream& os, const Piece& piece) {
    if (piece.getSymbol() == '\0') {
        if (!piece.getColor()) {
            os << "P";
        }
        else {
            os << 'p';
        }
    }
    else {
        if (!piece.getColor()) {
            os << piece.getSymbol();
        }
        else {
            os << (char)tolower(piece.getSymbol());
        }
    }
    return os;
}
