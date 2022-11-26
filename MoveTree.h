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
        Board * board;
        std::vector<MoveNode*> lines;
        double eval;
        bool isLeaf;
        MoveNode(Move move, Board * board) {
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
    std::map<std::string, double> * evals; // stores evals so they can be determined faster later
    std::map<std::string, std::vector<Move>> * allMovesMap; // stores all possible moves from a position so they can be determined faster later
    
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
     * @brief Gets the best move from a subtree using alpha-beta pruning
     * 
     * @param subroot 
     * @param depth 
     * @return std::pair<Move, double> 
     */
    std::pair<Move, double> getBestMove(MoveNode * subroot, int depth);
public:
    MoveTree(Board * board, int depth, double randomness, std::map<std::string, double> * evals = new std::map<std::string, double>(), std::map<std::string, std::vector<Move>> * allMoves = new std::map<std::string, std::vector<Move>>()) {
        srand(time(NULL));
        Board * board_ = new Board(*board);
        root = new MoveNode(Move(), board_);
        this->depth = depth;
        this->randomness = randomness;
        this->evals = evals;
        this->allMovesMap = allMoves;
        generateTree(root, depth);
    }
    ~MoveTree() {
        deleteTree(root);
    }
    /**
     * @brief Gets the best move at the depth of the tree
     * Uses a minimax algorithm with alpha-beta pruning
     * 
     * @return Move The best move
     */
    Move getBestMove() {
        return getBestMove(root, 0).first;
    }
};
