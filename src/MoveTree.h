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
    /**
     * @brief A struct representing a node (position) in the tree
     */
    struct MoveNode {
        Move move; // The move that got to this position
        Board board; // The board
        std::vector<MoveNode*> lines; // The possible lines from this position
        Eval eval; // The board's evaluation
        MoveNode(Move move, Board board) {
            this->move = move;
            this->board = board;
        }
        /**
         * @brief Generates the lines from the node's position (also calculates evals)
         * 
         * @param randomness The amount of randomness to add to the evals
         */
        void calculateLines(double randomness);
    };
    MoveNode * root; // The root of the tree
    int depth; // The maximum depth of the tree
    double randomness; // The amount of randomness to add to the evals (see Game class)

    /**
     * @brief Deletes a tree of moves
     * 
     * @param subroot The root of the subtree to delete
     */
    void deleteTree(MoveNode * subroot);

    /**
     * @brief Gets the best eval from a subtree using minimax with alpha-beta pruning
     * 
     * @param subroot The root of the subtree to search
     * @param depth The current depth of the search
     * @param alpha The alpha value for alpha-beta pruning
     * @param beta The beta value for alpha-beta pruning
     * @return pair<Eval, Move> The best eval and most from the subtree
     */
    std::pair<Eval, Move> getBestEval(MoveNode * subroot, int currDepth, Eval alpha, Eval beta) const;
public:
    /**
     * @brief Default constructor for MoveTree (idk why you would use this)
     */
    MoveTree() : root(nullptr), depth(0), randomness(0) {}
    /**
     * @brief MoveTree constructor
     * 
     * @param board The board from which to generate the tree
     * @param depth The depth to search (must be at least 1)
     * @param randomness The amount of randomness to add to the evals (see Game class)
     */
    MoveTree(Board board, int depth, double randomness = 0) {
        srand(time(NULL));
        root = new MoveNode(Move(), Board(board));
        root->eval = board.evaluate();
        this->depth = depth;
        this->randomness = randomness;
        //generateTree(root, depth);
    }
    ~MoveTree() {
        deleteTree(root);
    }
    /**
     * @brief Gets the best move at the depth of the tree
     * Uses a minimax algorithm with alpha-beta pruing
     * 
     * @return Move The best move
     */
    Move getBestMove() const;
};
