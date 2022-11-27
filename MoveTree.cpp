#include "MoveTree.h"
#include <iostream>

using namespace std;

void MoveTree::generateTree(MoveNode * subroot, int depth) {
    if (depth == 0) {
        return;
    }
    std::vector<Move> moves;
    if (allMovesMap->find(subroot->board.writeFEN()) != allMovesMap->end()) {
        moves = (*allMovesMap)[subroot->board.writeFEN()];
    } else {
        moves = subroot->board.getAllMoves();
        (*allMovesMap)[subroot->board.writeFEN()] = moves;
    }
    for (int i = 0; i < moves.size(); i++) {
        Board tmp = Board(subroot->board);
        tmp.makeMove(moves[i], true);
        MoveNode * node = new MoveNode(moves[i], tmp);
        string fen = tmp.writeFEN();
        if (evals->find(fen) == evals->end()) {
            (*evals)[fen] = tmp.evaluate();
        }
        double adjustment = (rand() % 2) - 1;
        node->eval = (*evals)[fen] + adjustment * randomness;
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

double MoveTree::getBestEval(MoveNode * subroot) {
    if (subroot->isLeaf) {
        return subroot->eval;
    }
    double bestEval;
    if (subroot->board.getTurn()) {
        bestEval = -std::numeric_limits<double>::infinity();
    } else {
        bestEval = std::numeric_limits<double>::infinity();
    }
    for (int i = 0; i < subroot->lines.size(); i++) {
        double eval = getBestEval(subroot->lines[i]);
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
    return bestEval;
}
