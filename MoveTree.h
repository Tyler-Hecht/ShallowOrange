#pragma once
#include "Board.h"
#include <map>
#include <vector>
#include <string>

/**
 * @brief A class representing a tree of possible moves from a root position
 */
class MoveTree {
private:
    struct MoveNode {
        Move move;
        Board * board;
        std::vector<MoveNode*> lines;
        bool isLeaf;
        double eval;
        MoveNode(Move move, Board * board) {
            this->move = move;
            this->board = board;
            isLeaf = true;
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

    /**
     * @brief Generates a tree of moves
     * 
     * @param subroot The root of the subtree to generate
     * @param depth How deep to go
     */
    void generateTree(MoveNode * subroot, int depth);
    /**
     * @brief Deletes a tree of moves
     * 
     * @param subroot The root of the subtree to delete
     */
    void deleteTree(MoveNode * subroot);
public:
    MoveTree(Board * board, int depth, double randomness, std::map<std::string, double> *& evals) {
        srand(time(NULL));
        Board * board_ = new Board(*board);
        root = new MoveNode(Move(), board_);
        this->depth = depth;
        this->randomness = randomness;
        this->evals = evals;
        generateTree(root, depth);
    }
    ~MoveTree() {
        delete root;
    }
};
