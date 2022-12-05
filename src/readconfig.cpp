#include "readconfig.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

vector<char> readConfig(string filename) {
    ifstream file(filename);
    string line;
    vector<char> config;
    while (getline(file, line)) {
        if (line[0] == '#') {
            continue;
        }
        istringstream iss(line);
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == ':') {
                config.push_back(line[i + 2]);
                break;
            }
        }
    }
    file.close();
    return config;
}

