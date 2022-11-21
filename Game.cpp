#include "Game.h"
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

void Game::makeMove(Move move) {
    board->makeMove(move);
    moves.push_back(move.toString());
}

string Game::getResult() const {
    switch (board->getResult()) {
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
    int result = board->getResult();
    if (result == 1) {
        PGN += "1-0";
    } else if (result == 2) {
        PGN += "0-1";
    } else if (result == 3 || result == 4 || result == 5 || result == 6) {
        PGN += "1/2-1/2";
    }
    return PGN;
}

Move Game::getBestMove() {
    vector<Move> moves = board->getAllMoves();
    if (moves.size() == 0) {
        return Move();
    }
    Board * tmp;
    Move bestMove;
    double bestEval = board->getTurn() ? -10000 : 10000;
    for (int i = 0; i < moves.size(); i++) {
        // evaluate the move
        Move move = moves[i];
        tmp = new Board(*board);
        tmp->makeMove(move);
        double eval;
        string fen = tmp->writeFEN();
        if (evals.find(fen) != evals.end()) {
            eval = evals[fen];
        } else {
            // if checkmate set eval to 10000 or -10000
            int result = tmp->getResult();
            if (result == 1) {
                eval = 10000;
            } else if (result == 2) {
                eval = -10000;
            }
            // if draw set eval to 0
            else if (result == 3 || result == 4 || result == 5 || result == 6) {
                eval = 0;
            } else {
                eval = tmp->evaluate();
            }
            evals[fen] = eval;
        }
        double adjustment = (rand() % 2) - 1;
        eval += adjustment * randomness;
        if (board->getTurn()) {
            if (eval > bestEval) {
                bestEval = eval;
                bestMove = move;
            }
        } else {
            if (eval < bestEval) {
                bestEval = eval;
                bestMove = move;
            }
        }
        delete tmp;
    }
    return bestMove;
}

void Game::playRandomGame(bool print, int delay) {
    while (true) {
        vector<Move> moves = board->getAllMoves();
        if (board->getResult() != 0) {
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
        if (board->getResult() != 0) {
            cout << getResult() << endl;
            break;
        }
        Move move = getBestMove();
        makeMove(move);
        if (print) {
            board->print();
            cout << move << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}
