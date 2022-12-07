#include "Game.h"
#include "readconfig.h"
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    bool config;
    bool playAsWhite, showBoard, showCoords, povWhite;
    double randomness;
    int depth;
    string configResponse;
    cout << "Would you like to use the settings from the config file? (y/n)" << endl;
    cin >> configResponse;
    while (configResponse != "y" && configResponse != "n") {
        cout << "Invalid response. Try again: ";
        cin >> configResponse;
    }
    config = configResponse == "y";
    if (config) {
        vector<char> settings = readConfig("../entry/config.yaml");
        playAsWhite = settings[0] == 'W';
        depth = settings[1] - '0';
        randomness = stod(string(1, settings[2]));
        showBoard = settings[3] == 'Y';
        showCoords = settings[4] == 'Y';
        povWhite = settings[5] == 'W';
    } else {
        string colorResponse;
        cout << "Would you like to play as white or black? (w/b): ";
        cin >> colorResponse;
        while (colorResponse != "w" && colorResponse != "b") {
            cout << "Invalid response. Please enter w or b: ";
            cin >> colorResponse;
        }
        playAsWhite = colorResponse == "w";
        double difficulty;
        cout << "What would you like the difficulty of the engine to be?" << endl;
        cout << "Enter a number between 0 and 1, where 0 is the easiest and 1 is the hardest: ";
        cin >> difficulty;
        while (difficulty < 0 || difficulty > 1) {
            cout << "Invalid response. Please enter a number between 0 and 1: ";
            cin >> difficulty;
        }
        randomness = pow((1 - difficulty), 2) * 5;
        depth = 3;
        showBoard = true;
        showCoords = false;
        povWhite = playAsWhite;
    }
    Game game(randomness);
    game.playGame(depth, showBoard, playAsWhite, povWhite, showCoords);
    cout << game.getPGN() << endl;
}
