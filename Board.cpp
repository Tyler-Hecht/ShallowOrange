#include "Board.h"
#include <iostream>
using namespace std;

Board::Board(bool original_) {
    turn = 0;
    original = original_;
    enPassant = "";
    canCastleKingsideWhite = true;
    canCastleQueensideWhite = true;
    canCastleKingsideBlack = true;
    canCastleQueensideBlack = true;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares[i][j] = new Square();
        }
    }
}

void Board::setup() {
    for (int i = 0; i < 8; i++) {
        squares[i][1]->setPiece(new Piece('P', 0));
        squares[i][6]->setPiece(new Piece('P', 1));
    }
    squares[0][0]->setPiece(new Piece('R', 0));
    squares[1][0]->setPiece(new Piece('N', 0));
    squares[2][0]->setPiece(new Piece('B', 0));
    squares[3][0]->setPiece(new Piece('Q', 0));
    squares[4][0]->setPiece(new Piece('K', 0));
    squares[5][0]->setPiece(new Piece('B', 0));
    squares[6][0]->setPiece(new Piece('N', 0));
    squares[7][0]->setPiece(new Piece('R', 0));
    squares[0][7]->setPiece(new Piece('R', 1));
    squares[1][7]->setPiece(new Piece('N', 1));
    squares[2][7]->setPiece(new Piece('B', 1));
    squares[3][7]->setPiece(new Piece('Q', 1));
    squares[4][7]->setPiece(new Piece('K', 1));
    squares[5][7]->setPiece(new Piece('B', 1));
    squares[6][7]->setPiece(new Piece('N', 1));
    squares[7][7]->setPiece(new Piece('R', 1));
}

void Board::print(bool withCoords) const {
    if (withCoords) {
        cout << "  a b c d e f g h" << endl;
    }
    for (int i = 0; i < 8; i++) {
        if (withCoords) {
            cout << 8 - i << " ";
        }
        for (int j = 0; j < 8; j++) {
            if (squares[j][i]->getPiece() == NULL) {
                if (squares[j][i]->isLit()) {
                    cout << "#";
                }
                else {
                    cout << " ";
                }
            }
            else {
                cout << *squares[j][i]->getPiece();
            }
            cout << " ";
        }
        if (withCoords) {
            cout << 8 - i;
        }
        cout << endl;
    }
    if (withCoords) {
        cout << "  a b c d e f g h" << endl;
    }
}

bool Board::move(Move move) {
    if (!isLegal(move)) {
        return false;
    }
    Piece * piece = getSquare(move.getFrom())->getPiece();
    if (move.isPromotion()) {
        piece->promote(move.getPromotionType());
    }
    getSquare(move.getFrom())->setPiece(NULL);
    getSquare(move.getTo())->setPiece(piece);
    if (move.isCastle()) {
        Piece * rook;
        if (move.getTo() == "g1") {
            rook = getSquare("h1")->getPiece();
            getSquare("h1")->setPiece(NULL);
            getSquare("f1")->setPiece(rook);
            canCastleKingsideWhite = false;
            canCastleQueensideWhite = false;
        }
        else if (move.getTo() == "c1") {
            rook = getSquare("a1")->getPiece();
            getSquare("a1")->setPiece(NULL);
            getSquare("d1")->setPiece(rook);
            canCastleKingsideWhite = false;
            canCastleQueensideWhite = false;
        }
        else if (move.getTo() == "g8") {
            rook = getSquare("h8")->getPiece();
            getSquare("h8")->setPiece(NULL);
            getSquare("f8")->setPiece(rook);
            canCastleKingsideBlack = false;
            canCastleQueensideBlack = false;
        }
        else if (move.getTo() == "c8") {
            rook = getSquare("a8")->getPiece();
            getSquare("a8")->setPiece(NULL);
            getSquare("d8")->setPiece(rook);
            canCastleKingsideBlack = false;
            canCastleQueensideBlack = false;
        }
    }
    if (move.isEnPassant()) {
        string captureSquare = move.enPassantSquare();
        getSquare(captureSquare)->setPiece(NULL);
    }
    return true;
}

Square * Board::findKing(bool color) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j]->getPiece() != NULL && squares[i][j]->getPiece()->getSymbol() == 'K' && squares[i][j]->getPiece()->getColor() == color) {
                return squares[i][j];
            }
        }
    }
    return NULL;
}
