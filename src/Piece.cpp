#include "Piece.h"
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, const Piece& piece) {
    if (piece.getColor()) {
            os << piece.getSymbol();
    } else {
            os << (char)tolower(piece.getSymbol());
    }
    return os;
}

int Piece::pointValue() const {
    switch (symbol) {
        case 'P':
            return 1;
        case 'N':
            return 3;
        case 'B':
            return 3;
        case 'R':
            return 5;
        case 'Q':
            return 9;
        default:
            return 0;
    }
}

double Piece::locationAdjustment(string square, int phase) const {
    vector<vector<double>> pieceTable = getPieceTable(phase);
    int row = square[1] - '1';
    int col = square[0] - 'a';
    if (color) {
        return pieceTable[7-row][col];
    } else {
        return pieceTable[row][col];
    }
}

vector<vector<double>> Piece::getPieceTable(int phase) const {
    switch (symbol) {
        case 'P':
            if (phase == 0) {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0.3, 0.5, 0.5, 0, 0, 0},
                    {-0.2, -0.2, 0.3, 0.5, 0.5, 0.1, -0.3, -0.3},
                    {0.1, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.1},
                    {0, 0, 0, -0.2, -0.2, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0}
                };
            } else if (phase == 1) {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0.1},
                    {0, 0, 0.3, 0.4, 0.4, 0, 0, 0},
                    {0, 0, 0.3, 0.4, 0.4, 0.1, 0, 0},
                    {0.1, 0.1, 0, 0, 0, 0, 0.1, 0.1},
                    {0, 0.1, -0.2, -0.4, -0.4, 0, 0.1, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0}
                };
            } else {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8, 0.8},
                    {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5},
                    {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3},
                    {0.1, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.1},
                    {-0.1, 0, 0, 0, 0, 0, 0, 0},
                    {-0.3, 0, -0.4, -0.4, -0.4, 0, 0, -0.2},
                    {0, 0, 0, 0, 0, 0, 0, 0}
                };
            }
            break;
        case 'N':
            if (phase == 0) {
                return {
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0.2, 0.3, 0.3, 0.2, 0, 0},
                        {0, 0, 0.1, 0.3, 0.3, 0.1, 0, 0},
                        {-0.2, 0.1, 0.3, 0, 0, 0.3, 0.1, -0.2},
                        {0, 0, 0, 0.2, 0.2, 0, 0, 0},
                        {-1, -0.3, 0, 0, 0, 0, -0.3, -1}
                    };
            } else if (phase == 1) {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0.2, 0.2, 0.3, 0.3, 0.2, 0,2, 0},
                    {0, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0},
                    {0, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0},
                    {-0.3, 0.1, 0.2, 0.1, 0.1, 0.2, 0.1, -0.3},
                    {-0.4, -0.2, 0, 0.1, 0.1, 0, -0.2, -0.4},
                    {-1, -0.5, -0.1, -0.1, -0.1, -0.1, -0.5, -1}
                };
            } else {
                return {
                    {-0.5, 0, 0, 0, 0, 0, 0, -0.5},
                    {0, 0, 0, 0.1, 0.1, 0, 0, 0},
                    {0, 0.1, 0.2, 0.2, 0.2, 0.2, 0.1, 0},
                    {0, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0},
                    {0, 0.1, 0.2, 0.3, 0.3, 0.2, 0.1, 0},
                    {-0.3, 0, 0.2, 0.2, 0.2, 0.2, 0, -0.3},
                    {-0.5, -0.3, 0, 0, 0, 0, 0, -0.5},
                    {-1, -0.5, -0.3, -0.3, -0.3, -0.3, -0.5, -1}
                };
            }
            break;
        case 'B':
            if (phase == 0) {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0.3, 0, 0, 0, 0, 0.3, 0},
                    {0, 0, 0.3, 0.2, 0.2, 0.3, 0, 0},
                    {0, 0, 0, 0, 0.2, 0.2, 0, 0},
                    {-0.3, 0.3, 0, 0.2, 0.2, 0, 0.3, -0.3},
                    {-1, -0.5, -0.3, 0, 0, -0.3, -0.5, -1}
                };
            } else if (phase == 1) {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0.3, 0.1, 0.1, 0.1, 0.1, 0.3, 0},
                    {0, 0.2, 0.3, 0.2, 0.2, 0.3, 0.2, 0},
                    {0, 0, 0, 0.1, 0.1, 0.1, 0.1, 0},
                    {-0.3, 0.3, -0.1, 0.1, 0.1, -0.1, 0.3, -0.3},
                    {-1, -0.4, -0.3, 0, 0, -0.3, -0.4, -1}
                };
            } else {
                return {
                    {-0.5, 0, 0, 0, 0, 0, 0, -0.5},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0},
                    {0, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0},
                    {0, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0},
                    {0, 0, 0.2, 0.2, 0.2, 0.2, 0, 0},
                    {0, 0.1, 0, 0, 0, 0, 0.1, 0},
                    {-1, -0.5, 0, 0, 0, 0, -0.5, -1}
                };
            }
            break;
        case 'R':
            if (phase == 0) {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {-0.2, -0.2, 0, 0.1, 0.1, 0, -0.2, -0.2},
                    {-0.1, -0.2, 0.3, 0.3, 0.3, 0.2, -0.2, -0.1}
                };
            } else if (phase == 1) {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0.05, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.05},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
                    {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
                    {0, 0, 0, 0.1, 0.1, 0, 0, 0},
                    {0, -0.2, 0.2, 0.2, 0.2, 0, -0.1, -0.1}
                };
            } else {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0.15, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.15},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0.05, 0.05, 0.05, 0.05, 0, 0},
                    {0, 0, 0.1, 0.1, 0.1, 0.1, 0, 0},
                    {0, 0, 0.1, 0.1, 0.1, 0.1, 0, 0},
                    {0, 0, 0.1, 0.1, 0.1, 0.1, 0, 0}
                };
            }
            break;
        case 'Q':
            if (phase == 0) {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0.15, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0.15, 0.05, 0.05, 0, 0, 0},
                    {-0.3, -0.1, 0.05, 0.1, 0.05, 0, -0.4, -0.4}
                };
            } else if (phase == 1) {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0.15, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0.15, 0.05, 0.05, 0, 0, 0},
                    {-0.3, -0.1, 0.05, 0.1, 0.05, 0, -0.4, -0.4}
                };
            } else {
                return {
                    {-0.05, 0, 0, 0, 0, 0, 0, -0.05},
                    {0, 0.05, 0, 0, 0, 0, 0.05, 0},
                    {0, 0, 0.1, 0.1, 0.1, 0.1, 0, 0},
                    {0, 0, 0.1, 0.1, 0.1, 0.1, 0, 0},
                    {0, 0, 0.1, 0.1, 0.1, 0.1, 0, 0},
                    {0, 0, 0.1, 0.1, 0.1, 0.1, 0, 0},
                    {0, 0.05, 0, 0, 0, 0, 0.05, 0},
                    {-0.1, 0, 0, 0, 0, 0, 0, -0.1}
                };
            }
            break;
        case 'K':
            if (phase == 0) {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {-0.4, -0.4, -0.4, -0.4, -0.4, -0.4, -0.4, -0.4},
                    {0.1, 0.3, 0.2, -0.3, -0.1, 0.1, 0.4, 0.2}
                };
            } else if (phase == 1) {
                return {
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {-0.4, -0.4, -0.4, -0.4, -0.4, -0.4, -0.4, -0.4},
                    {0.1, 0.2, 0.2, -0.2, -0.1, 0.1, 0.2, 0.2}
                };
            } else {
                return {
                    {-0.4, -0.3, -0.2, -0.2, -0.2, -0.2, -0.3, -0.2},
                    {-0.3, 0, 0, 0, 0, 0, 0, -0.3},
                    {-0.3, 0, 0.1, 0.1, 0.1, 0.1, 0, -0.3},
                    {-0.2, 0, 0.1, 0.2, 0.2, 0.1, 0, -0.2},
                    {-0.2, 0, 0.1, 0.2, 0.2, 0.1, 0, -0.2},
                    {-0.3, 0, 0.1, 0.1, 0.1, 0.1, 0, -0.3},
                    {-0.4, 0, 0, 0, 0, 0, 0, -0.4},
                    {-0.5, -0.3, -0.2, -0.2, -0.2, -0.2, -0.3, -0.5}
                };
            }
            break;
    }
    return {
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0}
            };;
}