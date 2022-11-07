#pragma once
#include <string>
#include "Move.h"

class Move {
    std::string from;
    std::string to;
    bool capture;
    bool promotion;
    int promotionType;
    bool castle;
    bool enPassant;
    bool check;
    bool checkmate;
    char disambiguation;
public:
    Move(std::string from_, std::string to_, bool capture_ = false, bool promotion_ = false, int promotionType_ = 0, bool castle_ = false, bool enPassant_ = false, bool check_ = false, bool checkmate_ = false, char disambiguation_ = '\0') {
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
};
