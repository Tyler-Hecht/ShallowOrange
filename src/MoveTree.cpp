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

Eval MoveTree::getBestEval(MoveNode * subroot) const {
    if (subroot->isLeaf) {
        Eval eval = subroot->eval;
        eval.incrementMate();
        return eval;
    }
    Eval bestEval;
    if (subroot->board.getTurn()) {
        bestEval = Eval(0, false);
    } else {
        bestEval = Eval(0, true);
    }
    for (int i = 0; i < subroot->lines.size(); i++) {
        Eval eval = getBestEval(subroot->lines[i]);
        if (subroot->board.getTurn()) {
            if (eval > bestEval) {
                bestEval = eval;
            }
        } else {
            if (eval < bestEval) {
                bestEval = eval;
            }
        }
    }
    // increase moves to mate
    bestEval.incrementMate();
    return bestEval;
}

Move MoveTree::getBestMove() const {
    Move bestMove = root->lines[0]->move;
    Eval bestEval = getBestEval(root->lines[0]);
    for (int i = 1; i < root->lines.size(); i++) {
        Eval eval = getBestEval(root->lines[i]);
        if (root->board.getTurn()) {
            if (eval > bestEval) {
                bestEval = eval;
                bestMove = root->lines[i]->move;
            }
        } else {
            if (eval < bestEval) {
                bestEval = eval;
                bestMove = root->lines[i]->move;
            }
        }
    }
    return bestMove;
}
