#include "Board.h"
#include <map>

using namespace std;

double Board::evaluate() const {
    double whiteMaterial = 0;
    double blackMaterial = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j]->getPiece() != nullptr) {
                Piece * piece = squares[i][j]->getPiece();
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
    Piece * piece = getSquare(square)->getPiece();
    if (piece == nullptr) {
        return 0;
    }
    return piece->locationAdjustment(square);
}
