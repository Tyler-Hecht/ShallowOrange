#include "Board.h"
#include <iostream>
using namespace std;

Board::Board() {
    turn = 1;
    enPassant = "";
    halfmoveClock = 0;
    fullmoveNumber = 1;
    canCastleKingsideWhite = false;
    canCastleQueensideWhite = false;
    canCastleKingsideBlack = false;
    canCastleQueensideBlack = false;
    whiteKingSquare = "";
    blackKingSquare = "";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares[i][j] = Piece();
        }
    }
    result = 0;
    phase = 0;
}

void Board::setup() {
    readFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void Board::print(bool withCoords, bool pov) const {
    if (pov) {
        if (withCoords) {
            cout << "  a b c d e f g h" << endl;
        }
        for (string rank : {"8", "7", "6", "5", "4", "3", "2", "1"}) {
            if (withCoords) {
                cout << rank << " ";
            }
            for (string file : {"a", "b", "c", "d", "e", "f", "g", "h"}) {
                Piece piece = getPiece(file + rank);
                if (piece != Piece()) {
                    cout << piece;
                }
                else {
                    cout << " ";
                }
                cout << " ";
            }
            if (withCoords) {
                cout << rank;
            }
            cout << endl;
        }
        if (withCoords) {
            cout << "  a b c d e f g h" << endl;
        }
    } else {
        if (withCoords) {
            cout << "  h g f e d c b a" << endl;
        }
        for (string rank : {"1", "2", "3", "4", "5", "6", "7", "8"}) {
            if (withCoords) {
                cout << rank << " ";
            }
            for (string file : {"h", "g", "f", "e", "d", "c", "b", "a"}) {
                Piece piece = getPiece(file + rank);
                if (piece != Piece()) {
                    cout << piece;
                }
                else {
                    cout << " ";
                }
                cout << " ";
            }
            if (withCoords) {
                cout << rank;
            }
            cout << endl;
        }
        if (withCoords) {
            cout << "  h g f e d c b a" << endl;
        }
    }
}

void Board::makeMove(const Move & move, bool update) {
    // the piece that is moving
    Piece piece = getPiece(move.getFrom());
    // update king square
    if (piece.getSymbol() == 'K') {
        if (piece.getColor()) {
            whiteKingSquare = move.getTo();
        } else {
            blackKingSquare = move.getTo();
        }
    }
    // handles promotion
    if (move.isPromotion()) {
        piece.promote(move.getPromotionType());
    }
    // removes the piece from its square
    setPiece(move.getFrom(), Piece());
    // moves the piece to its new square
    setPiece(move.getTo(), piece);
    // handles castling
    if (move.isCastle()) {
        Piece rook;
        if (move.getTo() == "g1") {
            rook = getPiece("h1");
            setPiece("h1", Piece());
            setPiece("f1", rook);
            canCastleKingsideWhite = false;
            canCastleQueensideWhite = false;
        }
        else if (move.getTo() == "c1") {
            rook = getPiece("a1");
            setPiece("a1", Piece());
            setPiece("d1", rook);
            canCastleKingsideWhite = false;
            canCastleQueensideWhite = false;
        }
        else if (move.getTo() == "g8") {
            rook = getPiece("h8");
            setPiece("h8", Piece());
            setPiece("f8", rook);
            canCastleKingsideBlack = false;
            canCastleQueensideBlack = false;
        }
        else if (move.getTo() == "c8") {
            rook = getPiece("a8");
            setPiece("a8", Piece());
            setPiece("d8", rook);
            canCastleKingsideBlack = false;
            canCastleQueensideBlack = false;
        }
    }
    if (turn && move.getPiece() == 'K') {
        canCastleKingsideWhite = false;
        canCastleQueensideWhite = false;
    }
    else if (turn && move.getPiece() == 'R') {
        if (move.getFrom() == "a1") {
            canCastleQueensideWhite = false;
        }
        else if (move.getFrom() == "h1") {
            canCastleKingsideWhite = false;
        }
    }
    else if (!turn && move.getPiece() == 'K') {
        canCastleKingsideBlack = false;
        canCastleQueensideBlack = false;
    }
    else if (!turn && move.getPiece() == 'R') {
        if (move.getFrom() == "a8") {
            canCastleQueensideBlack = false;
        }
        else if (move.getFrom() == "h8") {
            canCastleKingsideBlack = false;
        }
    }
    // determines new en passant square
    if (move.getPiece() == 'P') {
        if (move.getFrom()[1] == '2' && move.getTo()[1] == '4') {
            enPassant = string(1, move.getFrom()[0]) + "3";
        }
        else if (move.getFrom()[1] == '7' && move.getTo()[1] == '5') {
            enPassant = string(1, move.getFrom()[0]) + "6";
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
    string FEN = writeFEN(false);
    if (FENcounter.find(FEN) != FENcounter.end()) {
        FENcounter[FEN]++;
    } else {
        FENcounter[FEN] = 1;
    }
    if (update) {
        updateResult();
    }
    updatePhase();
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
            if (getPiece(squares.back()) != Piece()) {
                break;
            }
        }
    }
    return squares;
}

string Board::findKing(bool color) const {
    return color ? whiteKingSquare : blackKingSquare;
}

bool Board::inCheck(bool color, std::string kingSquare) const {
    //detect check by knight, bishop, rook, queen
    vector<string> knightMoves = knightSquares(kingSquare);
    for (string square : knightMoves) {
        Piece piece = getPiece(square);
        if (piece != Piece() && piece.getSymbol() == 'N' && piece.getColor() != color) {
            return true;
        }
    }
    vector<string> bishopMoves = rbSquares(kingSquare, false);
    for (string square : bishopMoves) {
        Piece piece = getPiece(square);
        if (piece != Piece() && (piece.getSymbol() == 'B' || piece.getSymbol() == 'Q') && piece.getColor() != color) {
            return true;
        }
    }
    vector<string> rookMoves = rbSquares(kingSquare, true);
    for (string square : rookMoves) {
        Piece piece = getPiece(square);
        if (piece != Piece() && (piece.getSymbol() == 'R' || piece.getSymbol() == 'Q') && piece.getColor() != color) {
            return true;
        }
    }
    vector<string> pawnMoves;
    // work backwards to find possible pawn moves
    // black
    if (!color) {
        pawnMoves.push_back(asString(kingSquare[0] - 'a' - 1, kingSquare[1] - '1' - 1));
        pawnMoves.push_back(asString(kingSquare[0] - 'a' + 1, kingSquare[1] - '1' - 1));
    // white
    } else {
        pawnMoves.push_back(asString(kingSquare[0] - 'a' - 1, kingSquare[1] - '1' + 1));
        pawnMoves.push_back(asString(kingSquare[0] - 'a' + 1, kingSquare[1] - '1' + 1));
    }
    for (string square : pawnMoves) {
        if (square[0] >= 'a' && square[0] <= 'h' && square[1] >= '1' && square[1] <= '8') {
            Piece piece = getPiece(square);
            if (piece != Piece() && piece.getSymbol() == 'P' && piece.getColor() != color) {
                return true;
            }
        }
    }
    // detect "check" by king
    vector<pair<int, int>> kingMoves = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (pair<int, int> move : kingMoves) {
        int file = kingSquare[0] - 'a' + move.first;
        int rank = kingSquare[1] - '1' + move.second;
        if (file >= 0 && file < 8 && rank >= 0 && rank < 8) {
            Piece piece = getPiece(asString(file, rank));
            if (piece != Piece() && piece.getSymbol() == 'K' && piece.getColor() != color) {
                return true;
            }
        }
    }
    //no check
    return false;
}

bool Board::isLegal(const Move & move) const {
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
    Board tmp = Board(*this);
    tmp.makeMove(move);
    if (tmp.inCheck(!tmp.turn, tmp.findKing(!tmp.turn))) {
        return false;
    }
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
    bool color = getPiece(square).getColor();
    int colorMultiplier = color ? 1 : -1;
    // move forward
    if (squareEmpty(asString(file, rank + colorMultiplier))) {
        // promotion
        if ((color && rank == 6 ) || (!color && rank == 1)) {
            moves.push_back(Move('P', square, asString(file, rank + colorMultiplier), false, true, 'Q'));
            moves.push_back(Move('P', square, asString(file, rank + colorMultiplier), false, true, 'R'));
            moves.push_back(Move('P', square, asString(file, rank + colorMultiplier), false, true, 'B'));
            moves.push_back(Move('P', square, asString(file, rank + colorMultiplier), false, true, 'N'));
        } else {
            moves.push_back(Move('P', square, asString(file, rank + colorMultiplier)));
        }
        // move two squares
        if (rank == (color ? 1 : 6) && squareEmpty(asString(file, rank + 2 * colorMultiplier))) {
            moves.push_back(Move('P', square, asString(file, rank + 2 * colorMultiplier)));
        }
    }
    // capture left
    if (file > 0 && getPiece(asString(file-1,rank+colorMultiplier)) != Piece() && getPiece(asString(file-1,rank+colorMultiplier)).getColor() != color) {
        // promotion
        if ((color && rank == 6) || (!color && rank == 1)) {
            moves.push_back(Move('P', square, asString(file - 1, rank + colorMultiplier), true, true, 'Q'));
            moves.push_back(Move('P', square, asString(file - 1, rank + colorMultiplier), true, true, 'R'));
            moves.push_back(Move('P', square, asString(file - 1, rank + colorMultiplier), true, true, 'B'));
            moves.push_back(Move('P', square, asString(file - 1, rank + colorMultiplier), true, true, 'N'));
        } else {
            moves.push_back(Move('P', square, asString(file - 1, rank + colorMultiplier), true));
        }
    }
    // capture right
    if (file < 7 && getPiece(asString(file+1,rank+colorMultiplier)) != Piece() && getPiece(asString(file+1, rank+colorMultiplier)).getColor() != color) {
        // promotion
        if ((color && rank == 6) || (!color && rank == 1)) {
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
    bool color = getPiece(square).getColor();
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
    for (size_t i = 0; i < squares.size(); i++) {
        if (squareEmpty(squares[i])) {
            moves.push_back(Move(symbol, square, squares[i]));
        } else if (getPiece(squares[i]).getColor() != color) {
            moves.push_back(Move(symbol, square, squares[i], true));
        }
    }
    return moves;
}

vector<Move> Board::getKingMoves(string square) const {
    vector<Move> moves;
    bool color = getPiece(square).getColor();
    vector<pair<int, int>> offsets = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (size_t i = 0; i < offsets.size(); i++) {
        int file = square[0] - 'a' + offsets[i].first;
        int rank = square[1] - '1' + offsets[i].second;
        if (file >= 0 && file <= 7 && rank >= 0 && rank <= 7) {
            if (squareEmpty(asString(file, rank))) {
                moves.push_back(Move('K', square, asString(file, rank)));
            } else if (getPiece(asString(file, rank)).getColor() != color) {
                moves.push_back(Move('K', square, asString(file, rank), true));
            }
        }
    }
    // castling
    if (color && canCastleKingsideWhite) {
        if (squareEmpty("f1") && squareEmpty("g1")) {
            moves.push_back(Move('K', square, "g1", false, false, ' ', true));
        }
    }
    if (color && canCastleQueensideWhite) {
        if (squareEmpty("d1") && squareEmpty("c1") && squareEmpty("b1")) {
            moves.push_back(Move('K', square, "c1", false, false, ' ', true));
        }
    }
    if (!color && canCastleKingsideBlack) {
        if (squareEmpty("f8") && squareEmpty("g8")) {
            moves.push_back(Move('K', square, "g8", false, false, ' ', true));
        }
    }
    if (!color && canCastleQueensideBlack) {
        if (squareEmpty("d8") && squareEmpty("c8") && squareEmpty("b8")) {
            moves.push_back(Move('K', square, "c8", false, false, ' ', true));
        }
    }
    return moves;
}

vector<Move> Board::getMoves(string square, bool check4checks) const {
    // no piece on square
    if (squareEmpty(square)) {
        return vector<Move>();
    }
    // piece is not the right color
    if (getPiece(square).getColor() != turn) {
        return vector<Move>();
    }
    vector<Move> moves;
    switch (getPiece(square).getSymbol()) {
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
    // add check/mate to moves
    if (check4checks) {
        for (size_t i = 0; i < legalMoves.size(); i++) {
            Board tmp = Board(*this);
            tmp.makeMove(legalMoves[i]);
            if (tmp.inCheck(tmp.turn, tmp.findKing(tmp.turn))) {
                legalMoves[i].setCheck(true);
                legalMoves[i].setCheckmate(tmp.noMoves());
            }
        }
    }
    return legalMoves;
}

vector<Move> Board::getAllMoves(bool check4checks) const {
    if (result != 0) {
        return vector<Move>();
    }
    vector<Move> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            vector<Move> tmp = getMoves(asString(i, j), check4checks);
            if (!tmp.empty()) {
                moves.insert(moves.end(), tmp.begin(), tmp.end());
            }
        }
    }
    // handle disambiguation
    for (size_t i = 0; i < moves.size(); i++) {
        // this will hold the indices in moves that need disambiguation
        vector<int> disamb = {(int) i};
        // find all moves with the same destination
        for (size_t j = i + 1; j < moves.size(); j++) {
            if (moves[i].getTo() == moves[j].getTo() && moves[i].getPiece() == moves[j].getPiece()) {
                disamb.push_back(j);
            }
        }
        if (disamb.size() > 1) {
            bool differentFiles = true;
            bool differentRanks = true;
            // check if any moves have the same file or rank
            for (size_t j = 0; j < disamb.size(); j++) {
                for (size_t k = j + 1; k < disamb.size(); k++) {
                    if (moves[disamb[j]].getFrom()[0] == moves[disamb[k]].getFrom()[0]) {
                        differentFiles = false;
                    }
                    if (moves[disamb[j]].getFrom()[1] == moves[disamb[k]].getFrom()[1]) {
                        differentRanks = false;
                    }
                }
            }
            // disambiguate
            for (size_t j = 0; j < disamb.size(); j++) {
                if ((differentFiles && !differentRanks) || (differentFiles && differentRanks)) {
                    moves[disamb[j]].setDisambiguation(string(1, moves[disamb[j]].getFrom()[0]));
                }
                else if (!differentFiles && differentRanks) {
                    moves[disamb[j]].setDisambiguation(string(1, moves[disamb[j]].getFrom()[1]));
                } else {
                    moves[disamb[j]].setDisambiguation(moves[disamb[j]].getFrom());
                }
            }
        }

    }
    
    // force en passant
    vector<Move> trueMoves;
    for (Move move : moves) {
        if (move.isEnPassant()) {
            trueMoves.push_back(move);
        }
    }
    if (!trueMoves.empty()) {
        return trueMoves;
    }
    return moves;
}

bool Board::noMoves() const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (getPiece(asString(i, j)) != Piece() && getPiece(asString(i, j)).getColor() == turn) {
                if (getMoves(asString(i, j), false).size() > 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Board::readMove(string str, Move & move) const {
    vector<Move> moves = getAllMoves();
    for (Move move_ : moves) {
        if (move_.toString() == str) {
            move = move_;
            return true;
        }
    }
    return false;
}

void Board::readFEN(string fen) {
    // clear board
    Board tmp = Board();
    *this = tmp;
    // read FEN
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
            squares[file][rank] = Piece(toupper(c), color);
            if (c == 'k') {
                blackKingSquare = asString(file, rank);
            } else if (c == 'K') {
                whiteKingSquare = asString(file, rank);
            }
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
        enPassant = string(1, fen[i]) + string(1, fen[i+1]);
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
    while (i < (int) fen.length()) {
        fullmove += fen[i];
        i++;
    }
    fullmoveNumber = stoi(fullmove);
    FENcounter[fen] = 1;
}

string Board::writeFEN(bool full) const {
    string fen = "";
    for (int rank = 7; rank >= 0; rank--) {
        int empty = 0;
        for (int file = 0; file < 8; file++) {
            if (squareEmpty(asString(file, rank))) {
                empty++;
            } else {
                if (empty > 0) {
                    fen += to_string(empty);
                    empty = 0;
                }
                Piece piece = squares[file][rank];
                fen += piece.getColor() ? piece.getSymbol() : tolower(piece.getSymbol());
            }
        }
        if (rank != 0) {
            if (empty > 0) {
                fen += to_string(empty);
            }
            fen += '/';
        }
        if (rank == 0 && empty > 0) {
            fen += to_string(empty);
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
    if (full) {
        fen += ' ';
        fen += to_string(halfmoveClock);
        fen += ' ';
        fen += to_string(fullmoveNumber);
    }
    return fen;
}

bool Board::insufficientMaterial() const {
    int numWhiteBishops = 0;
    int numBlackBishops = 0;
    int numWhiteKnights = 0;
    int numBlackKnights = 0;
    bool whiteBishopOnLight = false;
    bool whiteBishopOnDark = false;
    bool blackBishopOnLight = false;
    bool blackBishopOnDark = false;
    for (int file = 0; file < 8; file++) {
        for (int rank = 0; rank < 8; rank++) {
            if (squares[file][rank] != Piece()) {
                if (squares[file][rank].getSymbol() == 'P') {
                    return false;
                } else if (squares[file][rank].getSymbol() == 'R') {
                    return false;
                } else if (squares[file][rank].getSymbol() == 'Q') {
                    return false;
                } else if (squares[file][rank].getSymbol() == 'B') {
                    if (squares[file][rank].getColor()) {
                        numWhiteBishops++;
                        if ((file + rank) % 2 == 0) {
                            whiteBishopOnLight = true;
                        } else {
                            whiteBishopOnDark = true;
                        }
                    } else {
                        numBlackBishops++;
                        if ((file + rank) % 2 == 0) {
                            blackBishopOnLight = true;
                        } else {
                            blackBishopOnDark = true;
                        }
                    }
                } else if (squares[file][rank].getSymbol() == 'N') {
                    if (squares[file][rank].getColor()) {
                        numWhiteKnights++;
                    } else {
                        numBlackKnights++;
                    }
                }
            }
        }
    }
    // king vs king and one minor piece
    if (numWhiteBishops + numWhiteKnights + numBlackBishops + numBlackKnights <= 1) {
        return true;
    }
    // two bishops of the same color is insufficient material
    if (numWhiteBishops == 1 && numBlackBishops == 1) {
        if (whiteBishopOnLight && blackBishopOnLight) {
            return true;
        }
        if (whiteBishopOnDark && blackBishopOnDark) {
            return true;
        }
    }
    return false;
}

int Board::updateResult() {
    if (noMoves()) {
        if (inCheck(true, findKing(true))) {
            result = 2;
            return 2;
        } else if (inCheck(false, findKing(false))) {
            result = 1;
            return 1;
        } else {
            result = 3;
            return 3;
        }
    }
    if (insufficientMaterial()) {
        result = 4;
        return 4;
    } else if (halfmoveClock >= 100) {
        result = 5;
        return 5;
    } else if (repetition(3)) {
        result = 6;
        return 6;
    } else {
        result = 0;
        return 0;
    }
}

int Board::updatePhase() {
    if (fullmoveNumber < 6) {
        phase = 0;
        return 0;
    }
    if (!(canCastleKingsideBlack || canCastleQueensideBlack || canCastleKingsideWhite || canCastleQueensideWhite)) {
        if (fullmoveNumber <= 40) {
            phase = 1;
            return 1;
        } else {
            phase = 2;
            return 2;
        }
    } else {
        if (fullmoveNumber > 40) {
            phase = 2;
            return 2;
        } else if (fullmoveNumber > 15) {
            phase = 1;
            return 1;
        } else {
            phase = 0;
            return 0;
        }

    }
}
