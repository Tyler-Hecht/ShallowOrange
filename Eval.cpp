#include "Board.h"
#include <map>

using namespace std;

double Board::evaluate() const {
    if (result == 1) {
        return 10000;
    } else if (result == 2) {
        return -10000;
    } else if (result == 3 || result == 4 || result == 5 || result == 6) {
        return 0;
    }
    double whiteMaterial = 0;
    double blackMaterial = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j] != nullptr) {
                Piece * piece = squares[i][j];
                if (piece->getColor()) {
                    whiteMaterial += piece->pointValue();
                    whiteMaterial += piece->locationAdjustment(asString(i, j));
                } else {
                    blackMaterial += piece->pointValue();
                    blackMaterial += piece->locationAdjustment(asString(i, j));
                }
            }
        }
    }
    return whiteMaterial - blackMaterial;
}

double Board::pieceLocationAdjustment(string square) const {
    Piece * piece = getPiece(square);
    if (piece == nullptr) {
        return 0;
    }
    return piece->locationAdjustment(square);
}
