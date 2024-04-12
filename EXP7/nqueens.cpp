#include <iostream>
#include <vector>

using namespace std;

// Utility function to print the board
void printSolution(const vector<vector<int>>& board) {
    int n = board.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << (board[i][j] ? "Q " : ". ");
        cout << endl;
    }
    cout << endl;
}

// Function to check if a queen can be placed on board[row][col]
bool isSafe(const vector<vector<int>>& board, int row, int col) {
    int i, j;
    int n = board.size();

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < n; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

// Recursive utility function to solve N Queen problem
bool solveNQueenUtil(vector<vector<int>>& board, int col) {
    int n = board.size();

    // If all queens are placed
    if (col >= n)
        return true;

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < n; i++) {
        // Check if the queen can be placed on board[i][col]
        if (isSafe(board, i, col)) {
            // Place this queen in board[i][col]
            board[i][col] = 1;

            // Recur to place rest of the queens
            if (solveNQueenUtil(board, col + 1))
                return true;

            // If placing queen in board[i][col] doesn't lead to a solution, then
            // remove queen from board[i][col]
            board[i][col] = 0; // BACKTRACK
        }
    }

    // If the queen can not be placed in any row in this column col, return false
    return false;
}

// This function solves the N Queen problem using Backtracking
bool solveNQueen(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));

    if (!solveNQueenUtil(board, 0)) {
        cout << "Solution does not exist" << endl;
        return false;
    }

    printSolution(board);
    return true;
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;
    solveNQueen(n);
    return 0;
}
