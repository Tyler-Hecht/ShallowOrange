#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

/**
 * @brief A class representing the evaluation of a position
 * This allows for mate in x to be represented
 */
class Eval {
private:
    double eval; // the evaluation of the position if not a forced mate
    bool forcedMate; // whether the position is a forced mate
    int plyToMate; // positive for white mate, negative for black mate
    bool winner; // true for white, false for black
public:
    Eval() : eval(0), forcedMate(false), plyToMate(0), winner(false) {}
    Eval(double eval_) : eval(eval_), forcedMate(false), plyToMate(0), winner(false) {}
    Eval(int plyToMate_, bool winner_) : eval(0), forcedMate(true), plyToMate(plyToMate_), winner(winner_) {}
    /**
     * @brief Converts the evaluation to a string
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

    // overloading assignment operator
    Eval & operator=(const Eval & other) {
        eval = other.eval;
        forcedMate = other.forcedMate;
        plyToMate = other.plyToMate;
        winner = other.winner;
        return *this;
    }

    // increase mate in x by 1
    void incrementMate() {
        if (forcedMate) {
            plyToMate++;
        }
    }

};

std::ostream & operator<<(std::ostream & out, const Eval & eval);
