#pragma once
#include <string>
#include "Move.h"

/**
 * @brief A class representing a chess move
 */
class Move {
    char piece; // The piece that is moving
    std::string from; // The square the piece is moving from
    std::string to; // The square the piece is moving to
    bool capture; // Whether the move is a capture
    bool promotion; // Whether the move is a promotion
    int promotionType; // If a promotion, the type of piece to promote to
    bool castle; // Whether the move is a castle
    bool enPassant; // Whether the move is en passant!!
    bool check; // Whether the move is a check
    bool checkmate; // Whether the move is a checkmate
    char disambiguation; // The file and/or rank of the piece being moved, if needed for disambiguation
public:
    /**
     * @brief If you can't figure out what these functions do why are you looking at this
     */
    Move(char piece_, std::string from_, std::string to_, bool capture_ = false, bool promotion_ = false, int promotionType_ = 0, bool castle_ = false, bool enPassant_ = false, bool check_ = false, bool checkmate_ = false, char disambiguation_ = '\0') {
        piece = piece_;
        from = from_;
        to = to_;
        capture = capture_;
        promotion = promotion_;
        promotionType = promotionType_;
        castle = castle_;
        enPassant = enPassant_;
        check = check_;
        checkmate = checkmate_;
        disambiguation = disambiguation_;
    }
    char getPiece() const {
        return piece;
    }
    std::string getFrom() const {
        return from;
    }
    std::string getTo() const {
        return to;
    }
    bool isCapture() const {
        return capture;
    }
    bool isPromotion() const {
        return promotion;
    }
    int getPromotionType() const {
        return promotionType;
    }
    bool isCastle() const {
        return castle;
    }
    bool isEnPassant() const {
        return enPassant;
    }
    bool isCheck() const {
        return check;
    }
    bool isCheckmate() const {
        return checkmate;
    }
    std::string enPassantSquare() const {
        char x = to[0];
        char y = to[1];
        return std::string(1, x) + std::string(1, y);
    }
    char getDisambiguation() const {
        return disambiguation;
    }

    /**
     * @brief Converts the move to a string
     * 
     * @return std::string The move as a string
     */
    std::string toString() const;
};
