#include "Board.h"
#include <iostream>
using namespace std;

Board::Board() {
    turn = 1;
    enPassant = "";
    halfmoveClock = 0;
    fullmoveNumber = 1;
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
        getSquare(file + "2")->setPiece(new Piece('P', 1));
        getSquare(file + "7")->setPiece(new Piece('P', 0));
    }
    getSquare("a1")->setPiece(new Piece('R', 1));
    getSquare("b1")->setPiece(new Piece('N', 1));
    getSquare("c1")->setPiece(new Piece('B', 1));
    getSquare("d1")->setPiece(new Piece('Q', 1));
    getSquare("e1")->setPiece(new Piece('K', 1));
    getSquare("f1")->setPiece(new Piece('B', 1));
    getSquare("g1")->setPiece(new Piece('N', 1));
    getSquare("h1")->setPiece(new Piece('R', 1));
    getSquare("a8")->setPiece(new Piece('R', 0));
    getSquare("b8")->setPiece(new Piece('N', 0));
    getSquare("c8")->setPiece(new Piece('B', 0));
    getSquare("d8")->setPiece(new Piece('Q', 0));
    getSquare("e8")->setPiece(new Piece('K', 0));
    getSquare("f8")->setPiece(new Piece('B', 0));
    getSquare("g8")->setPiece(new Piece('N', 0));
    getSquare("h8")->setPiece(new Piece('R', 0));
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

void Board::makeMove(Move move) {
    // the piece that is moving
    Piece * piece = getSquare(move.getFrom())->getPiece();
    // handles promotion
    if (move.isPromotion()) {
        piece->promote(move.getPromotionType());
    }
    // removes the piece from its square
    getSquare(move.getFrom())->setPiece(NULL);
    // moves the piece to its new square
    getSquare(move.getTo())->setPiece(piece);
    // handles castling
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
    // handles en passant
    if (move.isEnPassant()) {
        string captureSquare = move.enPassantSquare();
        getSquare(captureSquare)->setPiece(NULL);
    }
    // determines new en passant square
    if (move.getPiece() == 'P') {
        if (move.getFrom()[1] == '2' && move.getTo()[1] == '4') {
            enPassant = move.getFrom()[0] + "3";
        }
        else if (move.getFrom()[1] == '7' && move.getTo()[1] == '5') {
            enPassant = move.getFrom()[0] + "6";
        }
        else {
            enPassant = "";
        }
    } else {
        enPassant = "";
    }
    turn = !turn;
    if (move.getPiece() == 'P' || move.isCapture()) {
        halfmoveClock = 0;
    } else {
        halfmoveClock++;
    }
    if (!turn) {
        fullmoveNumber++;
    }
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
                return asString(i, j);
            }
        }
    }
    return "";
}

bool Board::inCheck(bool color, std::string kingSquare) const {
    //detect check by knight, bishop, rook, queen
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
    if (color) {
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
    if (tmp->inCheck(!tmp->turn, tmp->findKing(!tmp->turn))) {
        delete tmp;
        return false;
    }
    delete tmp;
    return true;
}

string asString(int file, int rank) {
    string to_return = "";
    to_return += (char)('a' + file);
    to_return += (char)('1' + rank);
    return to_return;
}

vector<Move> Board::getPawnMoves(string square) const {
    vector<Move> moves;
    int file = square[0] - 'a';
    int rank = square[1] - '1';
    bool color = getSquare(square)->getPiece()->getColor();
    int colorMultiplier = color ? 1 : -1;
    // move forward
    if (getSquare(asString(file, rank + colorMultiplier))->getPiece() == NULL) {
        // promotion
        if (color && rank == 6 || !color && rank == 1) {
            moves.push_back(Move('P', square, asString(file, rank + colorMultiplier), false, true, 'Q'));
            moves.push_back(Move('P', square, asString(file, rank + colorMultiplier), false, true, 'R'));
            moves.push_back(Move('P', square, asString(file, rank + colorMultiplier), false, true, 'B'));
            moves.push_back(Move('P', square, asString(file, rank + colorMultiplier), false, true, 'N'));
        } else {
            moves.push_back(Move('P', square, asString(file, rank + colorMultiplier)));
        }
        // move two squares
        if (rank == (color ? 1 : 6) && getSquare(asString(file, rank + 2 * colorMultiplier))->getPiece() == NULL) {
            moves.push_back(Move('P', square, asString(file, rank + 2 * colorMultiplier)));
        }
    }
    // capture left
    if (file > 0 && getSquare(asString(file-1,rank+colorMultiplier))->getPiece() != NULL && getSquare(asString(file-1,rank+colorMultiplier))->getPiece()->getColor() != color) {
        // promotion
        if (color && rank == 6 || !color && rank == 1) {
            moves.push_back(Move('P', square, asString(file - 1, rank + colorMultiplier), true, true, 'Q'));
            moves.push_back(Move('P', square, asString(file - 1, rank + colorMultiplier), true, true, 'R'));
            moves.push_back(Move('P', square, asString(file - 1, rank + colorMultiplier), true, true, 'B'));
            moves.push_back(Move('P', square, asString(file - 1, rank + colorMultiplier), true, true, 'N'));
        } else {
            moves.push_back(Move('P', square, asString(file - 1, rank + colorMultiplier), true));
        }
    }
    // capture right
    if (file < 7 && getSquare(asString(file+1,rank+colorMultiplier))->getPiece() != NULL && getSquare(asString(file+1, rank+colorMultiplier))->getPiece()->getColor() != color) {
        // promotion
        if (color && rank == 6 || !color && rank == 1) {
            moves.push_back(Move('P', square, asString(file + 1, rank + colorMultiplier), true, true, 'Q'));
            moves.push_back(Move('P', square, asString(file + 1, rank + colorMultiplier), true, true, 'R'));
            moves.push_back(Move('P', square, asString(file + 1, rank + colorMultiplier), true, true, 'B'));
            moves.push_back(Move('P', square, asString(file + 1, rank + colorMultiplier), true, true, 'N'));
        } else {
            moves.push_back(Move('P', square, asString(file + 1, rank + colorMultiplier), true));
        }
    }
    // en passant
    if (enPassant != "") {
        if (enPassant == asString(file - 1, rank + colorMultiplier)) {
            moves.push_back(Move('P', square, asString(file - 1, rank + colorMultiplier), true, false, ' ', false, true));
        }
        if (enPassant == asString(file + 1, rank + colorMultiplier)) {
            moves.push_back(Move('P', square, asString(file + 1, rank + colorMultiplier), true, false, ' ', false, true));
        }
    }
    return moves;
}

vector<Move> Board::getNBRQMoves(string square, char symbol) const {
    vector<Move> moves;
    bool color = getSquare(square)->getPiece()->getColor();
    vector<string> squares;
    if (symbol == 'N') {
        squares = knightSquares(square);
    } else if (symbol == 'B') {
        squares = rbSquares(square, false);
    } else if (symbol == 'R') {
        squares = rbSquares(square, true);
    } else if (symbol == 'Q') {
        squares = rbSquares(square, true);
        vector<string> tmp = rbSquares(square, false);
        squares.insert(squares.end(), tmp.begin(), tmp.end());
    }
    for (int i = 0; i < squares.size(); i++) {
        if (getSquare(squares[i])->getPiece() == NULL) {
            moves.push_back(Move(symbol, square, squares[i]));
        } else if (getSquare(squares[i])->getPiece()->getColor() != color) {
            moves.push_back(Move(symbol, square, squares[i], true));
        }
    }
    return moves;
}

vector<Move> Board::getKingMoves(string square) const {
    vector<Move> moves;
    bool color = getSquare(square)->getPiece()->getColor();
    vector<pair<int, int>> offsets = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < offsets.size(); i++) {
        int file = square[0] - 'a' + offsets[i].first;
        int rank = square[1] - '1' + offsets[i].second;
        if (file >= 0 && file <= 7 && rank >= 0 && rank <= 7) {
            if (getSquare(asString(file, rank))->getPiece() == NULL) {
                moves.push_back(Move('K', square, asString(file, rank)));
            } else if (getSquare(asString(file, rank))->getPiece()->getColor() != color) {
                moves.push_back(Move('K', square, asString(file, rank), true));
            }
        }
    }
    // castling
    if (color && canCastleKingsideWhite) {
        if (getSquare("f1")->getPiece() == NULL && getSquare("g1")->getPiece() == NULL) {
            moves.push_back(Move('K', square, "g1", false, false, ' ', true));
        }
    }
    if (color && canCastleQueensideWhite) {
        if (getSquare("d1")->getPiece() == NULL && getSquare("c1")->getPiece() == NULL && getSquare("b1")->getPiece() == NULL) {
            moves.push_back(Move('K', square, "c1", false, false, ' ', true));
        }
    }
    if (!color && canCastleKingsideBlack) {
        if (getSquare("f8")->getPiece() == NULL && getSquare("g8")->getPiece() == NULL) {
            moves.push_back(Move('K', square, "g8", false, false, ' ', true));
        }
    }
    if (!color && canCastleQueensideBlack) {
        if (getSquare("d8")->getPiece() == NULL && getSquare("c8")->getPiece() == NULL && getSquare("b8")->getPiece() == NULL) {
            moves.push_back(Move('K', square, "c8", false, false, ' ', true));
        }
    }
    return moves;
}

vector<Move> Board::getMoves(string square) const {
    // no piece on square
    if (getSquare(square)->getPiece() == NULL) {
        return vector<Move>();
    }
    // piece is not the right color
    if (getSquare(square)->getPiece()->getColor() != turn) {
        return vector<Move>();
    }
    vector<Move> moves;
    switch (getSquare(square)->getPiece()->getSymbol()) {
        case 'P':
            moves = getPawnMoves(square);
            break;
        case 'N':
            moves = getNBRQMoves(square, 'N');
            break;
        case 'B':
            moves = getNBRQMoves(square, 'B');
            break;
        case 'R':
            moves = getNBRQMoves(square, 'R');
            break;
        case 'Q':
            moves = getNBRQMoves(square, 'Q');
            break;
        case 'K':
            moves = getKingMoves(square);
            break;
    }
    // check if moves are legal
    vector<Move> legalMoves;
    for (Move move : moves) {
        if (isLegal(move)) {
            legalMoves.push_back(move);
        }
    }
    // add check to moves
    for (int i = 0; i < legalMoves.size(); i++) {
        Board * tmp = new Board(*this);
        tmp->makeMove(legalMoves[i]);
        if (tmp->inCheck(tmp->turn, tmp->findKing(tmp->turn))) {
            legalMoves[i].makeCheck(tmp->inCheckmate(!turn, tmp->findKing(!turn)));
        }
        delete tmp;
    }
    return legalMoves;
}

vector<Move> Board::getAllMoves() const {
    vector<Move> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            vector<Move> tmp = getMoves(asString(i, j));
            moves.insert(moves.end(), tmp.begin(), tmp.end());
        }
    }
    // handle disambiguation
    for (int i = 0; i < moves.size(); i++) {
        vector<Move> disamb = {moves[i]};
        for (int j = i + 1; j < moves.size(); j++) {
            if (moves[i].getTo() == moves[j].getTo() && moves[i].getPiece() == moves[j].getPiece()) {
                disamb.push_back(moves[j]);
            }
        }
        if (disamb.size() > 1) {
            bool differentFiles = true;
            bool differentRanks = true;
            for (int j = 0; j < disamb.size(); j++) {
                for (int k = j + 1; k < disamb.size(); k++) {
                    if (disamb[j].getFrom()[0] == disamb[k].getFrom()[0]) {
                        differentFiles = false;
                    }
                    if (disamb[j].getFrom()[1] == disamb[k].getFrom()[1]) {
                        differentRanks = false;
                    }
                }
            }
            for (int j = 0; j < disamb.size(); j++) {
                if (differentFiles && !differentRanks) {
                    disamb[j].setDisambiguation(to_string(disamb[j].getFrom()[0]));
                }
                if (!differentFiles && differentRanks) {
                    disamb[j].setDisambiguation(to_string(disamb[j].getFrom()[1]));
                }
                if (differentFiles && differentRanks) {
                    disamb[j].setDisambiguation(disamb[j].getFrom());
                }
            }
        }
    }
    return moves;
}

Move Board::readMove(string str) const {
    Move move;
    return move;
}

void Board::readFEN(string fen) {
    int rank = 7;
    int file = 0;
    int i = 0;
    char c = fen[i];
    while (c != ' ') {
        if (c == '/') {
            rank--;
            file = 0;
        } else if (c >= '1' && c <= '8') {
            file += c - '0';
        } else {
            bool color = isupper(c) ? true : false;
            squares[file][rank]->setPiece(new Piece(toupper(c), color));
            file++;
        }
        i++;
        c = fen[i];
    }
    i++;
    turn = (fen[i] == 'w') ? true : false;
    i += 2;
    string castle = "";
    while (fen[i] != ' ') {
        castle += fen[i];
        i++;
    }
    for (char c : castle) {
        if (c == 'K') {
            canCastleKingsideWhite = true;
        }
        if (c == 'Q') {
            canCastleQueensideWhite = true;
        }
        if (c == 'k') {
            canCastleKingsideBlack = true;
        }
        if (c == 'q') {
            canCastleQueensideBlack = true;
        }
    }
    i++;
    if (fen[i] != '-') {
        enPassant = fen[i] + fen[i + 1];
        i += 2;
    } else {
        enPassant = "";
        i++;
    }
    i++;
    string halfmove = "";
    while (fen[i] != ' ') {
        halfmove += fen[i];
        i++;
    }
    halfmoveClock = stoi(halfmove);
    i++;
    string fullmove = "";
    while (i < fen.length()) {
        fullmove += fen[i];
        i++;
    }
    fullmoveNumber = stoi(fullmove);
}

string Board::writeFEN() const {
    string fen = "";
    for (int rank = 7; rank >= 0; rank--) {
        int empty = 0;
        for (int file = 0; file < 8; file++) {
            if (squares[file][rank]->getPiece() == NULL) {
                empty++;
            } else {
                if (empty > 0) {
                    fen += to_string(empty);
                    empty = 0;
                }
                fen += squares[file][rank]->getPiece()->getSymbol();
            }
        }
        if (rank != 0) {
            fen += '/';
        }
    }
    fen += ' ';
    fen += (turn) ? 'w' : 'b';
    fen += ' ';
    if (canCastleKingsideWhite) {
        fen += 'K';
    }
    if (canCastleQueensideWhite) {
        fen += 'Q';
    }
    if (canCastleKingsideBlack) {
        fen += 'k';
    }
    if (canCastleQueensideBlack) {
        fen += 'q';
    }
    if (fen[fen.size() - 1] == ' ') {
        fen += '-';
    }
    fen += ' ';
    fen += (enPassant == "") ? "-" : enPassant;
    fen += ' ';
    fen += to_string(halfmoveClock);
    fen += ' ';
    fen += to_string(fullmoveNumber);
    return fen;
}
