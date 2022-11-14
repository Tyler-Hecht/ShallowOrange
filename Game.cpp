#include "Game.h"
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

void Game::makeMove(Move move) {
    board->makeMove(move);
    moves.push_back(move.toString());
    string FEN = board->writeFEN();
    // get rid of the halfmove clock and fullmove number
    FEN = FEN.substr(0, FEN.find_last_of(' '));
    FEN = FEN.substr(0, FEN.find_last_of(' '));
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

void Game::playRandomGame(bool print, int delay) {
    while (true) {
        vector<Move> moves = board->getAllMoves();
        if (result != 0) {
            cout << getResult() << endl;
            break;
        }
        srand(time(NULL));
        Move move = moves[rand() % moves.size()];
        makeMove(move);
        if (print) {
            board->print();
            cout << move << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

void Game::playGreedyGame(bool print, int delay) {
    while (true) {
        if (result != 0) {
            cout << getResult() << endl;
            break;
        }
        Move move = board->getBestMove();
        makeMove(move);
        if (print) {
            board->print();
            cout << move << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}
