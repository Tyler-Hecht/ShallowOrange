#include "Board.h"
#include <iostream>
using namespace std;

Board::Board() {
    turn = 0;
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

Board::Board(const Board & board) {
    turn = board.turn;
    enPassant = board.enPassant;
    canCastleKingsideWhite = board.canCastleKingsideWhite;
    canCastleQueensideWhite = board.canCastleQueensideWhite;
    canCastleKingsideBlack = board.canCastleKingsideBlack;
    canCastleQueensideBlack = board.canCastleQueensideBlack;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares[i][j] = new Square(*board.squares[i][j]);
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

bool Board::makeMove(Move move) {
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

vector<string> Board::knightSquares(string square) const {
    vector<vector<int>> directions = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    vector<string> squares;
    for (vector<int> direction : directions) {
        int file = square[0] - 'a' + direction[0];
        int rank = square[1] - '1' + direction[1];
        // if on the board
        if (file >= 0 && file < 8 && rank >= 0 && rank < 8) {
            squares.push_back(string(1, 'a' + file) + string(1, '1' + rank));
        }
    }
    return squares;
}

vector<string> Board::rbSquares(string square, bool rook) const {
    vector<vector<int>> directions;
    if (rook) {
        directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    } else {
        directions = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    }
    vector<string> squares;
    for (vector<int> direction : directions) {
        int file = square[0] - 'a';
        int rank = square[1] - '1';
        while (true) {
            // move further in a direction
            file += direction[0];
            rank += direction[1];
            // off the board
            if (file < 0 || file >= 8 || rank < 0 || rank >= 8) {
                break;
            }
            squares.push_back(string(1, 'a' + file) + string(1, '1' + rank));
            // ran into piece
            if (getSquare(squares.back())->getPiece() != NULL) {
                break;
            }
        }
    }
    return squares;
}

string Board::findKing(bool color) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j]->getPiece() != NULL && squares[i][j]->getPiece()->getSymbol() == 'K' && squares[i][j]->getPiece()->getColor() == color) {
                return string(1, i) + string(1, j);
            }
        }
    }
    return "";
}

bool Board::inCheck(bool color, std::string kingSquare) const {
    //detect check by knight
    vector<string> knightMoves = knightSquares(kingSquare);
    for (string square : knightMoves) {
        Piece * piece = getSquare(square)->getPiece();
        if (piece != NULL && piece->getSymbol() == 'N' && piece->getColor() != color) {
            return true;
        }
    }
    vector<string> bishopMoves = rbSquares(kingSquare, false);
    for (string square : bishopMoves) {
        Piece * piece = getSquare(square)->getPiece();
        if (piece != NULL && (piece->getSymbol() == 'B' || piece->getSymbol() == 'Q') && piece->getColor() != color) {
            return true;
        }
    }
    vector<string> rookMoves = rbSquares(kingSquare, true);
    for (string square : rookMoves) {
        Piece * piece = getSquare(square)->getPiece();
        if (piece != NULL && (piece->getSymbol() == 'R' || piece->getSymbol() == 'Q') && piece->getColor() != color) {
            return true;
        }
    }
    vector<string> pawnMoves;
    //work backwards to find possible pawn moves
    if (!color) {
        pawnMoves.push_back(to_string(kingSquare[0] - 'a' - 1) + to_string(kingSquare[1] - '1' - 1));
        pawnMoves.push_back(to_string(kingSquare[0] - 'a' + 1) + to_string(kingSquare[1] - '1' - 1));
    } else {
        pawnMoves.push_back(to_string(kingSquare[0] - 'a' - 1) + to_string(kingSquare[1] - '1' + 1));
        pawnMoves.push_back(to_string(kingSquare[0] - 'a' + 1) + to_string(kingSquare[1] - '1' + 1));
    }
    for (string square : pawnMoves) {
        if (square[0] >= 0 && square[0] < 8 && square[1] >= 0 && square[1] < 8) {
            Piece * piece = getSquare(square)->getPiece();
            if (piece != NULL && piece->getSymbol() == 'P' && piece->getColor() != color) {
                return true;
            }
        }
    }
    //no check
    return false;
}

bool Board::isLegal(Move move) const {
    // not legal if trying to castle in or through check
    if (move.isCastle()) {
        // white
        if (move.getFrom() == "e1") {
            // kingside
            if (move.getTo() == "g1") {
                if (inCheck(true, "e1") || inCheck(true, "f1") || inCheck(true, "g1")) {
                    return false;
                }
            // queenside
            } else if (move.getTo() == "c1") {
                if (inCheck(true, "e1") || inCheck(true, "d1") || inCheck(true, "c1")) {
                    return false;
                }
            }
        // black
        } else if (move.getFrom() == "e8") {
            // kingside
            if (move.getTo() == "g8") {
                if (inCheck(false, "e8") || inCheck(false, "f8") || inCheck(false, "g8")) {
                    return false;
                }
            // queenside
            } else if (move.getTo() == "c8") {
                if (inCheck(false, "e8") || inCheck(false, "d8") || inCheck(false, "c8")) {
                    return false;
                }
            }
        }
    }
    // not legal if trying to move into check
    Board * tmp = new Board(*this);
    tmp->makeMove(move);
    if (tmp->inCheck(turn, tmp->findKing(turn))) {
        delete tmp;
        return false;
    }
    delete tmp;
    return true;
}
