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
    char promotionType; // If a promotion, the type of piece to promote to
    bool castle; // Whether the move is a castle
    bool enPassant; // Whether the move is en passant!!
    std::string disambiguation; // The file and/or rank of the piece being moved, if needed for disambiguation
    bool check; // Whether the move is a check
    bool checkmate; // Whether the move is a checkmate
public:
    /**
     * @brief If you can't figure out what these functions do why are you looking at this
     */
    Move() : piece('\0'), from(""), to(""), capture(false), promotion(false), promotionType('\0'), castle(false), enPassant(false), disambiguation(""), check(false), checkmate(false) {}
    Move(char piece_, std::string from_, std::string to_, bool capture_ = false, bool promotion_ = false, char promotionType_ = '\0', bool castle_ = false, bool enPassant_ = false) {
        piece = piece_;
        from = from_;
        to = to_;
        capture = capture_;
        promotion = promotion_;
        promotionType = promotionType_;
        castle = castle_;
        enPassant = enPassant_;
        check = false;
        checkmate = false;
        disambiguation = "";
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
    char getPromotionType() const {
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
    std::string getDisambiguation() const {
        return disambiguation;
    }

    void setPiece(char piece_) {
        piece = piece_;
    }
    void setFrom(std::string from_) {
        from = from_;
    }
    void setTo(std::string to_) {
        to = to_;
    }
    void setCapture(bool capture_) {
        capture = capture_;
    }
    void setPromotion(bool promotion_) {
        promotion = promotion_;
    }
    void setPromotionType(char promotionType_) {
        promotionType = promotionType_;
    }
    void setCastle(bool castle_) {
        castle = castle_;
    }
    void setEnPassant(bool enPassant_) {
        enPassant = enPassant_;
    }
    void setCheck(bool check_) {
        check = check_;
    }
    void setCheckmate(bool checkmate_) {
        checkmate = checkmate_;
    }
    void setDisambiguation(std::string disambiguation_) {
        disambiguation = disambiguation_;
    }
    
    /**
     * @brief Converts the move to a string (algebraic notation)
     * 
     * @return std::string The move as a string
     */
    std::string toString() const;
};

std::ostream &operator<<(std::ostream &os, const Move &move);
