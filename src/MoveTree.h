#pragma once
#include "Board.h"
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
        Move move_; // The move that got to this position
        Board board_; // The board
        std::vector<MoveNode*> lines_; // The possible lines from this position
        Eval eval_; // The board's evaluation
        bool isRoot_; // Whether this node is the root
        /**
        * @brief MoveNode constructor
        *
        * @param move The move that got to this position
        * @param board The board for this node
        */
        MoveNode(Move move, Board board) : move_(move), board_(board), isRoot_(false) {
        }
        /**
         * @brief Generates the lines from the node's position (also calculates evals)
         * 
         * @param randomness The amount of randomness to add to the evals
         */
        void calculateLines(double randomness);
    };
    MoveNode * root_; // The root of the tree
    int depth_; // The maximum depth of the tree
    double randomness_; // The amount of randomness to add to the evals (see Game class)

    /**
     * @brief Deletes a tree of moves
     * 
     * @param subroot The root of the subtree to delete
     */
    void deleteTree(MoveNode * subroot);
    /**
    * @brief Copies a tree of moves
    *
    * @param subroot The root of the subtree to copy
    * @return MoveNode * The copied MoveNode
    */
    MoveNode * copyTree(MoveNode * subroot);

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
     * @brief Default constructor for MoveTree
     */
    MoveTree() : root_(nullptr), depth_(0), randomness_(0) {}
    /**
     * @brief MoveTree constructor
     * 
     * @param board The board from which to generate the tree
     * @param depth The depth to search (must be at least 1)
     * @param randomness The amount of randomness to add to the evals (see Game class)
     */
    MoveTree(Board board, int depth, double randomness = 0) {
        root_ = new MoveNode(Move(), Board(board));
        root_->isRoot_ = true;
        root_->eval_ = board.evaluate();
        this->depth_ = depth;
        this->randomness_ = randomness;
    }
    /**
    * @brief Destructor for MoveTree
    */
    ~MoveTree() {
        deleteTree(root_);
    }
    /**
    * @brief Copy constructor for MoveTree
    *
    * @param other The MoveTree to copy
    */
    MoveTree(const MoveTree & other) {
        depth_ = other.depth_;
        randomness_ = other.randomness_;
        root_ = copyTree(other.root_);
    }
    /**
    * @brief Assignment operator overload for MoveTree
    *
    * @param other The MoveTree to copy
    */
    MoveTree & operator=(const MoveTree & other) {
        depth_ = other.depth_;
        randomness_ = other.randomness_;
        copyTree(other.root_);
        deleteTree(root_);
        return *this;
    }
    /**
     * @brief Gets the best move at the depth of the tree
     * Uses a minimax algorithm with alpha-beta pruing
     * 
     * @return Move The best move
     */
    Move getBestMove() const;
};
