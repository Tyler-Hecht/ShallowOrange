#include "Board.h"
#include <iostream>

using namespace std;

int main() {
    Board board;
    board.setup();
    board.move(Move("e2", "e4"));
    board.print();
    return 0;
}
