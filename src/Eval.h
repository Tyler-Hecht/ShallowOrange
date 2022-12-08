#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

/**
 * @brief A class representing the evaluation of a position
 * This allows for mate in x to be represented
 * Behaves mostly like a double otherwise
 */
class Eval {
private:
    double eval; // the evaluation of the position if not a forced mate
    bool forcedMate; // whether the position is a forced mate
    int plyToMate; // positive for white mate, negative for black mate
    bool winner; // true for white, false for black
public:
    /**
    * @brief Default constructor for Eval (eval = 0)
    */
    Eval() : eval(0), forcedMate(false), plyToMate(0), winner(false) {}
    /**
    * @brief Constructor for an Eval that isn't a forced mate
    *
    * @param eval_ The evaluation
    */
    Eval(double eval_) : eval(eval_), forcedMate(false), plyToMate(0), winner(false) {}
    /**
    * @brief Constructor for an Eval that is a forced mate
    *
    * @param plyToMate_ The number of ply until checkmate
    * @param winner_ The color doing the mating
    */
    Eval(int plyToMate_, bool winner_) : eval(0), forcedMate(true), plyToMate(plyToMate_), winner(winner_) {}
    /**
     * @brief Converts the evaluation to a string
     * Forced mate has a "-M"/"+M" (black/white) followed by the moves until mate
     * 
     * @param decimals The number of decimals to include
     * @return string The evaluation as a string
     */
    std::string toString(int decimals = 2) const {
        if (!forcedMate) {
            std::ostringstream out;
            out.precision(decimals);
            out << std::fixed << eval;
            return out.str();
        } else if (plyToMate != 0) {
            int movesToMate = (plyToMate + 2) / 2;
            if (winner) {
                return "+M" + std::to_string(movesToMate);
            } else {
                return "-M" + std::to_string(movesToMate);
            }
        } else {
            return "-";
        }
    }

    // overloading comparison operators
    // Forced mates are always better for the mating side than a non-forced mate eval
    bool operator==(const Eval & other) const {
        if (forcedMate != other.forcedMate) {
            return false;
        }
        if (forcedMate) {
            return plyToMate == other.plyToMate && winner == other.winner;
        } else {
            return eval == other.eval;
        }
    }

    bool operator!=(const Eval & other) const {
        return !(*this == other);
    }

    bool operator<(const Eval & other) const;
    bool operator<=(const Eval & other) const {
        return *this < other || *this == other;
    }
    bool operator>(const Eval & other) const {
        return !(*this <= other);
    }
    bool operator>=(const Eval & other) const {
        return !(*this < other);
    }

    // overloading arithmetic operators
    // If not a forced mate, the argument is added/subtracted from the Eval
    Eval operator+(double change) {
        if (!forcedMate) {
            return Eval(eval + change);
        }
        return *this;
    }
    Eval operator-(double change) {
        if (!forcedMate) {
            return Eval(eval - change);
        }
        return *this;
    }
    void operator+=(double change) {
        if (!forcedMate) {
            eval += change;
        }
    }
    void operator-=(double change) {
        if (!forcedMate) {
            eval -= change;
        }
    }

    /**
    * @brief Increases by one the ply until mate
    */
    void incrementMate() {
        if (forcedMate) {
            plyToMate++;
        }
    }

};

/**
* @brief Overloads the << operator for Eval
* Outputs the toString function's return
*
* @param out The ostream
* @param eval the Eval
* @return ostream The ostream
*/
std::ostream & operator<<(std::ostream & out, const Eval & eval);
