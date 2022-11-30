#pragma once
#include "Board.h"
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <limits>

/**
 * @brief A class representing a tree of possible moves from a root position
 */
class MoveTree {
private:
    struct MoveNode {
        Move move;
        Board board;
        std::vector<MoveNode*> lines;
        Eval eval;
        bool isLeaf;
        MoveNode(Move move, Board board) {
            this->move = move;
            this->board = board;
            this->isLeaf = true;
        }
        ~MoveNode() {
            for (int i = 0; i < lines.size(); i++) {
                delete lines[i];
            }
        }
    };
    MoveNode * root;
    int depth;
    double randomness;
    
    /**
     * @brief Generates a tree of possible moves from a given position
     * 
     * @param subroot The root of the subtree to generate
     * @param depth The depth of the subtree to generate
     */
    void generateTree(MoveNode * subroot, int depth);
    /**
     * @brief Deletes a tree of moves
     * 
     * @param subroot The root of the subtree to delete
     */
    void deleteTree(MoveNode * subroot);

    /**
     * @brief Gets the best eval from a subtree using minimax
     * 
     * @param subroot The root of the subtree to search
     * @return double The best eval from the subtree
     */
    Eval getBestEval(MoveNode * subroot) const;
public:
    MoveTree() {
        root = nullptr;
        depth = 0;
        randomness = 0;
    }
    MoveTree(Board board, int depth, double randomness = 0) {
        srand(time(NULL));
        Board board_ = Board(board);
        root = new MoveNode(Move(), board_);
        this->depth = depth;
        this->randomness = randomness;
        generateTree(root, depth);
    }
    ~MoveTree() {
        deleteTree(root);
    }
    /**
     * @brief Gets the best move at the depth of the tree
     * Uses a minimax algorithm
     * 
     * @return Move The best move
     */
    Move getBestMove() const;
};