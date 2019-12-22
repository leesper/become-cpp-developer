#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <cstdlib>
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::getline;
using std::istringstream;
using std::pair;
using std::abs;

enum State { kEmpty, kObstacle };
typedef vector< vector<State> > Board;
typedef pair<int, int> Coordinate;
typedef vector<State> Line;

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

void printBoard(Board& board) {
    for (auto line : board) {
        for (auto grid : line) {
            cout << cellString(grid);
        }
        cout << endl;
    }
}

Line parseLine(string line) {
    int mark;
    istringstream ss(line);
    Line grids;
    while (ss >> mark) {
        if (mark == 0) {
            grids.push_back(kEmpty);
        } else {
            grids.push_back(kObstacle);
        }
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }
    return grids;
}

Board readBoardFile(string fileName) {
    ifstream fin;
    string line;
    Board board;
    fin.open(fileName);
    while (fin) {
        getline(fin, line);
        board.push_back(parseLine(line));
    }
    return board;
}

Board search(Board board, Coordinate start, Coordinate goal) {
    cout << "No path found!" << endl;
    Board path;
    return path;
}

int heuristic(Coordinate p1, Coordinate p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int main() {
    auto board = readBoardFile("1.board");
    printBoard(board);
    auto solution = search(board, {0, 0}, {4, 5});
    printBoard(solution);
    return 0;
}

