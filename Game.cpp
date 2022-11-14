#include "Game.h"
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

void Game::makeMove(Move move) {
    board->makeMove(move);
    string FEN = board->writeFEN();
    moves.push_back(move.toString());
    if (FENcounter.find(FEN) == FENcounter.end()) {
        FENcounter[FEN] = 1;
    } else {
        FENcounter[FEN]++;
    }
    if (FENcounter[FEN] == 3) {
        result = 6;
        return;
    }
    if (board->getHalfmoveClock() == 100) {
        result = 5;
        return;
    }
    if (board->insufficientMaterial()) {
        result = 4;
        return;
    }
    if (board->getAllMoves().size() == 0) {
        if (board->inCheckmate(board->getTurn(), board->findKing(board->getTurn()))) {
            result = board->getTurn() ? 2 : 1;
        } else {
            result = 3;
        }
    }
}

string Game::getResult() const {
    switch (result) {
        case 0:
            return "Game in progress";
        case 1:
            return "White wins";
        case 2:
            return "Black wins";
        case 3:
            return "Draw by stalemate";
        case 4:
            return "Draw by insufficient material";
        case 5:
            return "Draw by 50 move rule";
        case 6:
            return "Draw by threefold repetition";
    }
    return "";
}

string Game::getPGN() const {
    string PGN = "";
    for (int i = 0; i < moves.size(); i++) {
        if (i % 2 == 0) {
            PGN += to_string(i / 2 + 1) + ". ";
        }
        PGN += moves[i] + " ";
    }
    if (result == 1) {
        PGN += "1-0";
    } else if (result == 2) {
        PGN += "0-1";
    } else if (result == 3 || result == 4 || result == 5 || result == 6) {
        PGN += "1/2-1/2";
    }
    return PGN;
}

void Game::playRandomGame(int delay, bool print) {
    while (true) {
        vector<Move> moves = board->getAllMoves();
        if (result != 0) {
            cout << getResult() << endl;
            break;
        }
        srand(time(NULL));
        Move move = moves[rand() % moves.size()];
        makeMove(move);
        board->print();
        cout << move << endl;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}
