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
    for (string file : {"a", "b", "c", "d", "e", "f", "g", "h"}) {
        getSquare(file + "2")->setPiece(new Piece('P', 0));
        getSquare(file + "7")->setPiece(new Piece('P', 1));
    }
    getSquare("a1")->setPiece(new Piece('R', 0));
    getSquare("b1")->setPiece(new Piece('N', 0));
    getSquare("c1")->setPiece(new Piece('B', 0));
    getSquare("d1")->setPiece(new Piece('Q', 0));
    getSquare("e1")->setPiece(new Piece('K', 0));
    getSquare("f1")->setPiece(new Piece('B', 0));
    getSquare("g1")->setPiece(new Piece('N', 0));
    getSquare("h1")->setPiece(new Piece('R', 0));
    getSquare("a8")->setPiece(new Piece('R', 1));
    getSquare("b8")->setPiece(new Piece('N', 1));
    getSquare("c8")->setPiece(new Piece('B', 1));
    getSquare("d8")->setPiece(new Piece('Q', 1));
    getSquare("e8")->setPiece(new Piece('K', 1));
    getSquare("f8")->setPiece(new Piece('B', 1));
    getSquare("g8")->setPiece(new Piece('N', 1));
    getSquare("h8")->setPiece(new Piece('R', 1));
}

void Board::print(bool withCoords) const {
    if (withCoords) {
        cout << "  a b c d e f g h" << endl;
    }
    for (string rank : {"8", "7", "6", "5", "4", "3", "2", "1"}) {
        if (withCoords) {
            cout << rank << " ";
        }
        for (string file : {"a", "b", "c", "d", "e", "f", "g", "h"}) {
            Square * square = getSquare(file + rank);
            if (square->getPiece() != NULL) {
                cout << *square->getPiece();
            }
            else {
                if (square->isLit()) {
                    cout << "#";
                }
                else {
                    cout << " ";
                }
            }
            cout << " ";
        }
        if (withCoords) {
            cout << " " << rank;
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
