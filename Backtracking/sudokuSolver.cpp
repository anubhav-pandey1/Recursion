#include <bits/stdc++.h>
using namespace std;

bool checkInsertion(vector<vector<char>>& board, int rowCheck, int colCheck, int test) {
    char num = '0' + test;
    if (board[rowCheck][colCheck] != '.') {
        return false;
    }

    if (test > 9 || test < 1) {
        return false;
    }

    for (int x = 0; x < 9; x++) {
        if (x != rowCheck) {                  // x is a row
            if (board[x][colCheck] == num) {
                return false;
            }
        }

        if (x != colCheck) {                  // x is a col
            if (board[rowCheck][x] == num) {
                return false;
            }
        }
    }

    int topLine = 3 * (rowCheck / 3);
    int leftLine = 3 * (colCheck / 3);
    for (int r = topLine; r <= topLine + 2; r++) {
        for (int c = leftLine; c <= leftLine + 2; c++) {
            if (r != rowCheck && c != colCheck) {
                if (board[r][c] == num) {
                    return false;
                }
            }
        }
    }

    return true;
}

void sudokuSolver(vector<vector<char>>& board, int r, int c, bool& flag) {
    if (r > 8) {
        // cout << "Base case: (" << r << ", " << c << ")" << endl;
        flag = true;
        return;
    }

    while (board[r][c] != '.') {
        if (r == 8 && c == 8) {
            // cout << "breaking at (8, 8)" << endl;
            break;
        }
        if (c < 8) {
            c++;
        }
        else {
            c = 0;
            r++;
        }
    }

    for (int n = 1; n <= 9; n++) {
        if (checkInsertion(board, r, c, n)) {
            board[r][c] = ('0' + n);
            // cout << "(" << r << ", " << c << ") = " << n << endl;
            if (c == 8) {
                sudokuSolver(board, r + 1, 0, flag);
            }
            else {
                sudokuSolver(board, r, c + 1, flag);
            }
        }
        if (flag == false) {
            board[r][c] = '.';
            // cout << "(" << r << ", " << c << ") = ." << endl;
        }
    }
}

vector<vector<char>> solveSudoku(vector<vector<char>>& board) {
    bool flag = false;
    sudokuSolver(board, 0, 0, flag);
    return board;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int testNum;
    cin >> testNum;
    while (testNum--) {
        vector<vector<char>> board;
        for (int r = 0; r < 9; r++) {
            vector<char> line;
            for (int c = 0; c < 9; c++) {
                char num;
                cin >> num;
                line.push_back(num);
            }
            board.push_back(line);
        }

        // for (int r = 0; r < 9; r++) {
        //     for (int c = 0; c < 9; c++) {
        //         cout << checkInsertion(board, r, c, 1) << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "_________________" << endl;

        vector<vector<char>> result = solveSudoku(board);
        for (auto& vec : result) {
            for (char& ch : vec) {
                cout << ch << " ";
            }
            cout << endl;
        }

        cout << "_________________" << endl;
    }
    return 0;
}

// Test cases:

// Inputs:
