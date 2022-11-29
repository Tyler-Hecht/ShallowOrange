#include "Eval.h"

using namespace std;

bool Eval::operator<(const Eval & other) const {
    // neither has a forced mate
    if (!forcedMate && !other.forcedMate) {
        return eval < other.eval;
    // both have a forced mate
    } else if (forcedMate && other.forcedMate) {
        // both mates are the same color
        if (winner == other.winner) {
            // the longer mate is less
            return plyToMate > other.plyToMate;
        } else {
            // the black mate is less
            return !winner;
        }
    // this has a forced mate
    } else if (forcedMate) {
        // the forced mate is less if it is black
        return !winner;
    // other has a forced mate
    } else {
        return other.winner;
    }
}

ostream & operator<<(ostream & out, const Eval & eval) {
    out << eval.toString();
    return out;
}
