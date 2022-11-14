#include "Board.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    Board board;
    board.setup();
    board.print();
    while (true) {
        cout << "Enter a move: ";
        Move move;
        string str;
        cin >> str;
        while (!board.readMove(str, move)) {
            cout << "Invalid move. Try again: ";
            cin >> str;
        }
        cout << "making move" << endl;
        board.makeMove(move);
        board.print();
        if (board.getAllMoves().size() == 0) {
            cout << "Checkmate!" << endl;
            break;
        }
    }
    /*
    while (true) {
        vector<Move> moves = board.getAllMoves();
        cout << "Possible moves: " << moves.size() << endl;
        if (moves.size() == 0) {
            cout << "No moves" << endl;
            break;
        }
        board.makeMove(moves[rand() % moves.size()]);
        board.print();
    }
    */
    return 0;
}
