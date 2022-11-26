#include "MoveTree.h"
#include <iostream>

using namespace std;

void MoveTree::generateTree(MoveNode * subroot, int depth) {
    if (depth == 0) {
        return;
    }
    std::vector<Move> moves;
    if (allMovesMap->find(subroot->board->writeFEN()) != allMovesMap->end()) {
        moves = (*allMovesMap)[subroot->board->writeFEN()];
    } else {
        moves = subroot->board->getAllMoves();
        (*allMovesMap)[subroot->board->writeFEN()] = moves;
    }
    for (int i = 0; i < moves.size(); i++) {
        Board * tmp = new Board(*subroot->board);
        tmp->makeMove(moves[i]);
        MoveNode * node = new MoveNode(moves[i], tmp);
        string fen = tmp->writeFEN();
        if (evals->find(fen) == evals->end()) {
            (*evals)[fen] = tmp->evaluate();
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
        delete subroot->board;
    } else {
        for (int i = 0; i < subroot->lines.size(); i++) {
            deleteTree(subroot->lines[i]);
        }
    }
}

pair<Move, double> MoveTree::getBestMove(MoveNode * subroot, int depth) {
    return pair<Move, double>();
}
