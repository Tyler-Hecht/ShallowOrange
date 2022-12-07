#include "Game.h"
#include <chrono>
#include <thread>
#include <ctime>

using namespace std;

void Game::makeMove(Move & move) {
    board.makeMove(move, true);
    moves.push_back(move.toString());
}

string Game::getResult() const {
    switch (board.getResult()) {
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
    for (size_t i = 0; i < moves.size(); i++) {
        if (i % 2 == 0) {
            PGN += to_string(i / 2 + 1) + ". ";
        }
        PGN += moves[i] + " ";
    }
    int result = board.getResult();
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
    string fen = board.writeFEN();
    vector<Move> moves = board.getAllMoves();
    if (moves.empty()) {
        return Move();
    }
    Board tmp;
    Move bestMove;
    Eval bestEval = board.getTurn() ? Eval(0, false) : Eval(0, true);
    for (size_t i = 0; i < moves.size(); i++) {
        // evaluate the move
        Move move = moves[i];
        tmp = Board(board);
        tmp.makeMove(move, true);
        Eval eval = tmp.evaluate();
        double adjustment = (rand() % 2) - 1;
        eval += adjustment * randomness;
        if (board.getTurn()) {
            if (eval > bestEval) {
                bestEval = eval;
                cout << bestEval << endl;
                bestMove = move;
            }
        } else {
            if (eval < bestEval) {
                bestEval = eval;
                bestMove = move;
            }
        }
    }
    return bestMove;
}

void Game::generateRandomGame(bool print) {
    if (print) {
        board.print();
    }
    while (true) {
        vector<Move> moves = board.getAllMoves();
        if (board.getResult() != 0) {
            cout << getResult() << endl;
            break;
        }
        srand(time(NULL));
        Move move = moves[rand() % moves.size()];
        makeMove(move);
        if (print) {
            board.print();
            cout << move << endl;
        }
    }
}

void Game::generateGreedyGame(bool print) {
    if (print) {
        board.print();
    }
    while (true) {
        if (board.getResult() != 0) {
            cout << getResult() << endl;
            break;
        }
        Move move = getBestMove();
        makeMove(move);
        if (print) {
            board.print();
            cout << move << endl;
        }
    }
}

void Game::generateDeepGame(int depth, bool print) {
    if (print) {
        board.print();
    }
    while (true) {
        MoveTree tree = MoveTree(board, depth, randomness);
        if (board.getResult() != 0) {
            cout << getResult() << endl;
            break;
        }
        Move move = tree.getBestMove();
        makeMove(move);
        if (print) {
            board.print();
            cout << move << endl;
        }
    }
}

void Game::playGame(int depth, bool print, bool yourColor, bool pov, bool coords) {
    if (print) {
        board.print(coords, pov);
    }
    while (true) {
        if (board.getResult() != 0) {
            cout << getResult() << endl;
            break;
        }
        if (board.getTurn() == yourColor) {
            string moveString;
            cout << "Enter move: ";
            cin >> moveString;
            Move move;
            while (!board.readMove(moveString, move)) {
                cout << "Invalid move. Try again: ";
                cin >> moveString;
            }
            makeMove(move);
            if (print) {
                board.print(coords, pov);
            }
        } else {
            cout << "Thinking..." << endl;
            MoveTree tree = MoveTree(board, depth, randomness);
            Move move = tree.getBestMove();
            makeMove(move);
            if (print) {
                board.print(coords, pov);
            }
            cout << move << endl;
        }
    }
}
