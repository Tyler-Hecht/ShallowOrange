#include "MoveTree.h"
#include <iostream>

using namespace std;

void MoveTree::MoveNode::calculateLines(double randomness) {
    std::vector<Move> moves = board_.getAllMoves(isRoot_);
    for (size_t i = 0; i < moves.size(); i++) {
        Board tmp = Board(board_);
        tmp.makeMove(moves[i], true);
        MoveNode * node = new MoveNode(moves[i], tmp);
        double adjustment = (rand() % 2) - 1;
        node->eval_ = tmp.evaluate() + adjustment * randomness;
        node->board_ = tmp;
        node->move_ = moves[i];
        lines_.push_back(node);
    }
}

void MoveTree::deleteTree(MoveNode * subroot) {
    if (subroot == NULL) { return; }
    for (size_t i = 0; i < subroot->lines_.size(); i++) {
        deleteTree(subroot->lines_[i]);
    }
    delete subroot;
}

MoveTree::MoveNode * MoveTree::copyTree(MoveNode * subroot) {
    MoveNode * newSubroot = new MoveNode(*subroot);
    newSubroot->lines_ = vector<MoveNode*>();
    for (size_t i = 0; i < subroot->lines_.size(); i++) {
        newSubroot->lines_.push_back(copyTree(subroot->lines_[i]));
    }
    return newSubroot;
}

pair<Eval, Move> MoveTree::getBestEval(MoveNode * subroot, int currDepth, Eval alpha, Eval beta) const {
    //reached depth limit
    if (currDepth == depth_) {
        Eval eval = subroot->eval_;
        eval.incrementMate();
        return pair(eval, subroot->move_);
    }
    subroot->calculateLines(randomness_);
    Eval bestEval;
    //no moves
    if (subroot->lines_.size() == 0) {
        bestEval = subroot->eval_;
        bestEval.incrementMate();
        return pair(bestEval, subroot->move_);
    }
    Move bestMove = subroot->lines_[0]->move_;
    //minimax with alpha-beta pruning
    if (subroot->board_.getTurn()) {
        bestEval = Eval(0, false);
         for (size_t i = 0; i < subroot->lines_.size(); i++) {
            Eval eval = getBestEval(subroot->lines_[i], currDepth + 1, alpha, beta).first;
            Move move = subroot->lines_[i]->move_;
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
        for (size_t i = 0; i < subroot->lines_.size(); i++) {
            Eval eval = getBestEval(subroot->lines_[i], currDepth + 1, alpha, beta).first;
            Move move = subroot->lines_[i]->move_;
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

    // increase moves to mate if applicable
    bestEval.incrementMate();
    return pair(bestEval, bestMove);
}

Move MoveTree::getBestMove() const {
    return getBestEval(root_, 0, Eval(0, false), Eval(0, true)).second;
}
