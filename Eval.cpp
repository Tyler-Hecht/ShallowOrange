#include "Board.h"

using namespace std;

Move Board::getBestMove() const {
    vector<Move> moves = getAllMoves();
    if (moves.size() == 0) {
        return Move();
    }
    Board * tmp;
    Move bestMove;
    double bestEval = turn ? -10000 : 10000;
    for (int i = 0; i < moves.size(); i++) {
        tmp = new Board(*this);
        tmp->makeMove(moves[i]);
        double eval = tmp->evaluate();
        if (turn) {
            if (eval > bestEval) {
                bestEval = eval;
                bestMove = moves[i];
            }
        } else {
            if (eval < bestEval) {
                bestEval = eval;
                bestMove = moves[i];
            }
        }
    }
    return bestMove;
}

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
