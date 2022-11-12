#include "Piece.h"

using namespace std;

ostream& operator<<(ostream& os, const Piece& piece) {
    if (piece.getColor()) {
            os << piece.getSymbol();
    } else {
            os << (char)tolower(piece.getSymbol());
    }
    return os;
}
