#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    Board board;
    board.readFEN("1rnk1br1/1Q6/2nB2pp/p7/2PQp2K/1R2PP1N/6PP/N4BR1 w - - 4 53");
    board.print();
    vector<Move> moves = board.getAllMoves();
    for (Move move : moves) {
        cout << move << ", ";
    }
    cout << moves.size() << endl;
    /*
    Game game;
    game.playRandomGame();
    cout << game.getPGN() << endl;
    */
    return 0;
}
