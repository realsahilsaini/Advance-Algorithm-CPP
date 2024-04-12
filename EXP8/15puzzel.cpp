#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <cstring>   // For memcpy
#include <climits>   // For INT_MAX

using namespace std;

const int N = 4;
int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

struct Node {
    int puzzle[N][N];
    int x, y; // Blank tile coordinates
    int cost; // Number of moves so far
    int level; // Distance from the root node (depth of the node)
    Node* parent; // Pointer to parent node

    Node(int p[N][N], int x, int y, int newX, int newY, int lev, Node* par) {
        parent = par;
        memcpy(puzzle, p, sizeof(puzzle));
        swap(puzzle[x][y], puzzle[newX][newY]);
        this->cost = INT_MAX;
        this->level = lev;
        this->x = newX;
        this->y = newY;
    }
};

// Function to calculate the number of misplaced tiles
int calculateCost(int initial[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (initial[i][j] && initial[i][j] != goal[i][j]) {
                count++;
            }
        }
    }
    return count;
}

// Function to check if (x, y) is a valid matrix coordinate
bool isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Print path from root node to destination node
void printPath(Node* root) {
    if (root == nullptr) return;
    printPath(root->parent);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << root->puzzle[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};

// Directions arrays for moving the empty tile
const int row[] = {1, 0, -1, 0};
const int col[] = {0, -1, 0, 1};

void solve(int initial[N][N], int x, int y) {
    priority_queue<Node*, vector<Node*>, comp> pq;
    Node* root = new Node(initial, x, y, x, y, 0, nullptr);
    root->cost = calculateCost(initial);
    pq.push(root);

    while (!pq.empty()) {
        Node* min = pq.top();
        pq.pop();

        // If min is an answer node
        if (min->cost == 0) {
            printPath(min);
            return;
        }

        // Generate all possible children
        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];
            if (isSafe(newX, newY)) {
                Node* child = new Node(min->puzzle, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateCost(child->puzzle);
                pq.push(child);
            }
        }
    }
}

int main() {
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 11},
        {13, 14, 15, 12}
    };

    int x = 1, y = 2; // Position of the blank space

    solve(initial, x, y);
    return 0;
}
