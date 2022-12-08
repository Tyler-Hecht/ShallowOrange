#pragma once
#include <string>
#include <vector>
#include <map>
#include "Piece.h"
#include "Move.h"
#include "Eval.h"

/**
 * @brief A class representing a chess board
 * Contains information about the board, including:
 * - The squares on the board (including the pieces on them)
 * - Which color's turn it is
 * - What castling is possible
 * - What en passant is possible
 */
class Board {
    Piece squares[8][8];
    std::string enPassant;
    bool turn; // 1 for white, 0 for black
    bool canCastleKingsideWhite;
    bool canCastleQueensideWhite;
    bool canCastleKingsideBlack;
    bool canCastleQueensideBlack;
    std::string whiteKingSquare, blackKingSquare;
    int halfmoveClock;
    int fullmoveNumber;
    std::map<std::string, int> FENcounter;
    int result; // see updateResult() for details
    int phase; // 0 for opening, 1 for middle game, 2 for endgame
public:
    /**
     * @brief Default constructor for Board (empty board)
     */
    Board();
    /**
     * @brief Sets up the board to the standard starting position
     */
    void setup();
    /**
     * @brief Prints the board onscreen
     * 
     * @param withCoords Whether to print the coordinates on the side
     * @param pov The point of view to print the board from (true for white, false for black)
     */
    void print(bool withCoords = false, bool pov = true) const;
    /**
     * @brief Makes a move on the board, updating relevant member variables
     * 
     * @param move The move to make
     * @param update Whether to update the result of the game
     */
    void makeMove(Move & move, bool update = false);
    /**
     * @brief Get the Piece at a given square
     * 
     * @param square A string for the square, such as "e4"
     * @return Square* A pointer to the Square object
     */
    Piece getPiece(std::string square) const {
        int x = square[0] - 'a';
        int y = square[1] - '1';
        return squares[x][y];
    }

    /**
     * @brief Sets the Piece at a given square
     * 
     * @param square The square to set the piece at
     * @param piece The piece to set
     */
    void setPiece(std::string square, Piece piece) {
        int x = square[0] - 'a';
        int y = square[1] - '1';
        squares[x][y] = piece;
    }

    /**
     * @brief Gets the current turn
     * 
     * @return The current turn: 1 for white, 0 for black
     */
    bool getTurn() const {
        return turn;
    }
    /**
     * @brief Gets the halfmove clock
     * 
     * @return int The halfmove clock
     */
    int getHalfmoveClock() const {
        return halfmoveClock;
    }
    /**
     * @brief Gets the fullmove number
     * 
     * @return int The fullmove number
     */
    int getFullmoveNumber() const {
        return fullmoveNumber;
    }

    /**
     * @brief Finds all the squares that a knight can move to from a given square
     * 
     * @param square The starting square of the knight
     * @return std::vector<std::string> All possible squares the knight can move to
     */
    std::vector<std::string> knightSquares(std::string square) const;
    /**
     * @brief Finds all the squares that a rook or bishop can move to from a given square
     * 
     * @param square The starting square of the rook or bishop
     * @param rook true if rook, false if bishop
     * @return std::vector<std::string> All possible squares the rook or bishop can move to
     */
    std::vector<std::string> rbSquares(std::string square, bool rook) const;

    /**
     * @brief Finds the square of the king of a given color
     * If there are multiple kings of the same color, returns the first one found
     * 
     * @param color The color of the king to find
     * @return std::string The square the king is on
     */
    std::string findKing(bool color) const;
    /**
     * @brief Determines if a king would be in check if it were on a given square
     * 
     * @param color The color of the king
     * @param square The square the king would be on
     * @return bool Whether the king would be in check
     */
    bool inCheck(bool color, std::string kingSquare) const;
    /**
     * @brief Determines if a king is in checkmate
     * 
     * @param color The color of the king
     * @param allMoves All possible moves for the color
     * @return bool Whether the king is in checkmate
     */
    bool inCheckmate(bool color) const {
        return inCheck(color, findKing(color)) && getAllMoves().empty();
    }
    /**
     * @brief Determines if a given move is legal
     * A move is legal if it is not a move that would put the king in check
     * or tries to castle in or through check
     * 
     * @param move The move to check
     * @return bool Whether or not the move is legal
     */
    bool isLegal(Move & move) const;

    /**
     * @brief Gets all the possible pawn moves for a given square
     * 
     * @param square The square the pawn is on
     * @return std::vector<Move> All the possible moves for the pawn
     */
    std::vector<Move> getPawnMoves(std::string square) const;
    /**
     * @brief Gets all the possible knight, bishop, rook, or queen moves for a given square
     * 
     * @param square The square the piece is on
     * @param symbol The symbol of the piece: 'N', 'B', 'R', or 'Q'
     * @return std::vector<Move> All the possible moves for the piece
     */
    std::vector<Move> getNBRQMoves(std::string square, char symbol) const;
    /**
     * @brief Gets all the possible king moves for a given square
     * 
     * @param square The square the king is on
     * @return std::vector<Move> All the possible moves for the king
     */
    std::vector<Move> getKingMoves(std::string square) const;

    /**
     * @brief Gets all the possible legal moves for a given square
     * The piece on the square must be the same color as the turn
     * Disambiguation is not handled
     * 
     * @param square The square to get the moves for
     * @return std::vector<Move> All the possible moves for the square
     */
    std::vector<Move> getMoves(std::string square) const;

    /**
     * @brief Gets all possible legal moves in the current position
     * Disambiguation is handled
     * 
     * @return std::vector<Move> All the possible moves
     */
    std::vector<Move> getAllMoves() const;

    /**
     * @brief Determines if there are no legal moves for a the current turn
     * This is faster than getAllMoves().empty() because it return false once it finds a legal move
     * 
     * @return bool Whether or not there are no legal moves
     */
    bool noMoves() const;

    /**
     * @brief Reads in a move from a string (algabraic notation)
     * Since en passant is always a brilliant move, it must end with "!!"
     * 
     * @param str The string to read the move from (algebraic notation)
     * @param Move The move to read the string into
     * @return bool Whether the move exists in the current position
     */
    bool readMove(std::string str, Move & move) const;
    /**
     * @brief Reads in a position from an Forsyth-Edwards Notation (FEN) string
     * 
     * @param fen The FEN
     */
    void readFEN(std::string fen);
    /**
     * @brief Gets the Forsyth-Edwards Notation (FEN) of the current position
     * 
     * @param full Whether to include the halfmove clock and fullmove number
     * @return std::string The FEN
     */
    std::string writeFEN(bool full = true) const;

    /**
     * @brief Determines if there is insufficient material for checkmate
     * 
     * @return Whether there is insufficient material
     */
    bool insufficientMaterial() const;

    /**
     * @brief Determines if a position has been repeated a certain number of times or more
     * 
     * @param amount The number of times the position was repeated
     * @return bool Whether the position has been repeated the given number of times
     */
    bool repetition(int amount) const {
        for (auto it = FENcounter.begin(); it != FENcounter.end(); it++) {
            if (it->second >= amount) {
                return true;
            }
        }
        return false;
    }
    /**
     * @brief Updates the result of the position
     * 0 = in progress, 1 = white wins, 2 = black wins, 3 = draw by stalemate,
     * 4 = draw by insufficient material, 5 = draw by 50 move rule,
     * 6 = draw by threefold repetition
     * 
     * @return int The result of the position
     */
    int updateResult();

    /**
     * @brief Gets the result of the position
     * 
     * @return int The result of the position
     */
    int getResult() const {
        return result;
    }

    /**
     * @brief Updates the phase of the game
     * 
     * @return int The phase of the game
     */
    int updatePhase();
    
    /**
     * @brief Gets the phase of the game
     * 
     * @return int The phase of the game
     */
    int getPhase() const {
        return phase;
    }

    /**
     * @brief Evaluates the position (no depth)
     * 
     * @return Eval The evaluation of the position
     */
    Eval evaluate() const;
};

/**
 * @brief Gets the name of a square from its coordinates
 * 
 * @param rank The rank of the square as an integer, 0-7
 * @param file The file of the square as an integer, 0-7
 * @return string The name of the square
 */
std::string asString(int rank, int file);
