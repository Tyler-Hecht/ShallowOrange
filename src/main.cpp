#include "Game.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    string colorResponse;
    cout << "Would you like to play as white or black? (w/b): ";
    cin >> colorResponse;
    while (colorResponse != "w" && colorResponse != "b") {
        cout << "Invalid response. Please enter w or b: ";
        cin >> colorResponse;
    }
    bool playAsWhite = colorResponse == "w";
    double difficulty;
    cout << "What would you like the difficulty of the engine to be?" << endl;
    cout << "Enter a number between 0 and 1, where 0 is the easiest and 1 is the hardest: ";
    cin >> difficulty;
    while (difficulty < 0 || difficulty > 1) {
        cout << "Invalid response. Please enter a number between 0 and 1: ";
        cin >> difficulty;
    }
    double randomness = pow((1 - difficulty), 2) * 5;
    int depth = 3;
    Game game(randomness);
    game.playGame(depth, playAsWhite);
    cout << game.getPGN() << endl;
}
