#include "Board.h"
#include <map>

using namespace std;

Eval Board::evaluate() const {
    if (result == 1) {
        return Eval(0, true);
    } else if (result == 2) {
        return Eval(0, false);
    } else if (result == 3 || result == 4 || result == 5 || result == 6) {
        return Eval(0);
    }
    double whiteMaterial = 0;
    double blackMaterial = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j] != Piece()) {
                Piece piece = squares[i][j];
                if (piece.getColor()) {
                    whiteMaterial += piece.pointValue();
                    whiteMaterial += piece.locationAdjustment(asString(i, j), phase);
                } else {
                    blackMaterial += piece.pointValue();
                    blackMaterial += piece.locationAdjustment(asString(i, j), phase);
                }
            }
        }
    }
    return Eval(whiteMaterial - blackMaterial);
}
