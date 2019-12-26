#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <cstdlib>
#include <algorithm>
using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::getline;
using std::istringstream;
using std::pair;
using std::abs;
using std::sort;

enum State { kEmpty, kObstacle, kClosed, kPath, kStart, kFinish };
typedef vector< vector<State> > Board;
typedef pair<int, int> Coordinate;


class Node {
    public:
    Node(int x, int y, int g, int h):
    x(x), 
    y(y), 
    g(g), 
    h(h) {}

    int x;
    int y;
    int g;
    int h;
};

string cellString(State state) {
    string cell = "0 ";
    switch (state)
    {
    case kObstacle:
    cell = "⛰️ ";
    break;
    case kStart:
    cell = "🚦 ";
    break;
    case kFinish:
    cell = "🏁 ";
    break;
    case kPath:
    cell = "🚗 ";
    break;
    default:
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

vector<State> parseLine(string line) {
    int mark;
    istringstream ss(line);
    vector<State> grids;
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
    while (getline(fin, line)) {
        board.push_back(parseLine(line));
    }
    return board;
}

bool compare(const Node& one, const Node& two) {
    return one.g + one.h > two.g + two.h;
}

void cellSort(vector<Node>& openNodes) {
    sort(openNodes.begin(), openNodes.end(), compare);
}

bool checkValidCell(int x, int y, const Board& board) {
    bool isOnBoard = (0 <= x && x < board.size()) && (0 <= y && y < board[0].size());
    if (isOnBoard) {
        return board[x][y] == kEmpty;
    }
    return false;
}

int heuristic(const Coordinate& p1, const Coordinate& p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

void addToOpen(const Node& node, vector<Node>& openNodes, Board& board) {
    openNodes.push_back(node);
    board[node.x][node.y] = kClosed;
}

void expandNeighbors(const Node& current, vector<Node>& openNodes, Board& board, const Coordinate& goal) {
    // directional deltas
    const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    for (int i = 0; i < 4; i++) {
        int x2 = current.x + delta[i][0];
        int y2 = current.y + delta[i][1];
        if (checkValidCell(x2, y2, board)) {
            int g = current.g + 1;
            int h = heuristic(pair{x2, y2}, goal);
            addToOpen(Node(x2, y2, g, h), openNodes, board);
        }
    } 
}

Board search(Board& board, const Coordinate& start, const Coordinate& goal) {

    vector<Node> openNodes;
    Node node(start.first, start.second, 0, heuristic(start, goal));
    addToOpen(node, openNodes, board);
    while (!openNodes.empty()) {
        cellSort(openNodes);
        const Node current = openNodes.back();
        openNodes.pop_back();
        board[current.x][current.y] = kPath;
        if (current.x == goal.first && current.y == goal.second) {
            board[start.first][start.second] = kStart;
            board[goal.first][goal.second] = kFinish;
            return board;
        }
        expandNeighbors(current, openNodes, board, goal);
    }
    cout << "No path found!" << endl;
    return Board{};
}

int main() {
    auto board = readBoardFile("1.board");
    printBoard(board);
    auto solution = search(board, {0, 0}, {4, 5});
    cout << "solution: " << endl;
    printBoard(solution);
    return 0;
}

