#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::getline;
using std::istringstream;

enum State { kEmpty, kObstacle };

string cellString(State state) {
    string cell;
    switch (state)
    {
    case kObstacle:
        cell = "⛰️ ";
        break;
    case kEmpty:
        cell = "0 ";
        break;
    }
    return cell;
}

void printBoard(vector< vector<State> >& board) {
    for (auto line : board) {
        for (auto grid : line) {
            cout << cellString(grid);
        }
        cout << endl;
    }
}

vector<State> parseLine(string line) {
    int token;
    istringstream ss(line);
    vector<State> tokens;
    while (ss >> token) {
        if (token == 0) {
            tokens.push_back(kEmpty);
        } else {
            tokens.push_back(kObstacle);
        }
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }
    return tokens;
}

vector< vector<State> > readBoardFile(string fileName) {
    ifstream fin;
    string line;
    vector< vector<State> > board;
    fin.open(fileName);
    while (fin) {
        getline(fin, line);
        board.push_back(parseLine(line));
    }
    return board;
}

int main() {
    auto board = readBoardFile("1.board");
    printBoard(board);
    return 0;
}

