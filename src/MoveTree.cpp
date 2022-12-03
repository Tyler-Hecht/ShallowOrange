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

pair<Eval, Move> MoveTree::getBestEval(MoveNode * subroot) const {
    if (subroot->isLeaf) {
        Eval eval = subroot->eval;
        eval.incrementMate();
        return pair(eval, subroot->move);
    }
    Eval bestEval;
    Move bestMove;
    if (subroot->board.getTurn()) {
        bestEval = Eval(0, false);
    } else {
        bestEval = Eval(0, true);
    }
    for (int i = 0; i < subroot->lines.size(); i++) {
        Eval eval = getBestEval(subroot->lines[i]).first;
        Move move = subroot->lines[i]->move;
        if (subroot->board.getTurn()) {
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
    }
    // increase moves to mate
    bestEval.incrementMate();
    return pair(bestEval, bestMove);
}

Move MoveTree::getBestMove() const {
    return getBestEval(root).second;
}
