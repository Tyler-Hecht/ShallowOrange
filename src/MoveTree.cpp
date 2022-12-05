#include "MoveTree.h"
#include <iostream>

using namespace std;

void MoveTree::generateTree(MoveNode * subroot, int depth) {
    if (depth == 0) {
        return;
    }
    std::vector<Move> moves = subroot->board.getAllMoves();
    for (int i = 0; i < moves.size(); i++) {
        Board tmp = Board(subroot->board);
        tmp.makeMove(moves[i], true);
        MoveNode * node = new MoveNode(moves[i], tmp);
        string fen = tmp.writeFEN();
        double adjustment = (rand() % 2) - 1;
        node->eval = tmp.evaluate() + adjustment * randomness;
        node->board = tmp;
        node->move = moves[i];
        subroot->lines.push_back(node);
        subroot->isLeaf = false;
        generateTree(node, depth - 1);
    }
}

void MoveTree::deleteTree(MoveNode * subroot) {
    if (subroot->lines.size() == 0) {
        return;
    } else {
        for (int i = 0; i < subroot->lines.size(); i++) {
            deleteTree(subroot->lines[i]);
        }
    }
}

pair<Eval, Move> MoveTree::getBestEval(MoveNode * subroot, int currDepth, Eval alpha, Eval beta) const {
    if (subroot->isLeaf || currDepth == depth) {
        Eval eval = subroot->eval;
        eval.incrementMate();
        return pair(eval, subroot->move);
    }
    Eval bestEval;
    Move bestMove;
    if (subroot->board.getTurn()) {
        bestEval = Eval(0, false);
         for (int i = 0; i < subroot->lines.size(); i++) {
            Eval eval = getBestEval(subroot->lines[i], currDepth + 1, alpha, beta).first;
            Move move = subroot->lines[i]->move;
            if (eval > bestEval) {
                bestEval = eval;
                bestMove = move;
            }
            if (eval > alpha) {
                alpha = eval;
            }
            if (beta <= alpha) {
                break;
            }
        }
    } else {
        bestEval = Eval(0, true);
        for (int i = 0; i < subroot->lines.size(); i++) {
            Eval eval = getBestEval(subroot->lines[i], currDepth + 1, alpha, beta).first;
            Move move = subroot->lines[i]->move;
            if (eval < bestEval) {
                bestEval = eval;
                bestMove = move;
            }
            if (eval < beta) {
                beta = eval;
            }
            if (beta <= alpha) {
                break;
            }
        }
    }

    // increase moves to mate
    bestEval.incrementMate();
    return pair(bestEval, bestMove);
}

Move MoveTree::getBestMove() const {
    return getBestEval(root, 0, Eval(0, false), Eval(0, true)).second;
}
