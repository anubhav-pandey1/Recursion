#include <bits/stdc++.h>
using namespace std;

bool checkInsertion(vector<vector<char>>& board, int rowCheck, int colCheck, char test) {
    int topLine = 3 * (rowCheck / 3);                                      // Top-line of a subgrid for a given value of rowCheck
    int leftLine = 3 * (colCheck / 3);                                     // Left-line of a subgrid for a given value of colCheck
    for (int x = 0; x < 9; x++) {
        if (board[rowCheck][x] == test) {
            return false;
        }
        if (board[x][colCheck] == test) {
            return false;
        }

        if (board[topLine + (x / 3)][leftLine + (x % 3)] == test) {
            return false;
        }
    }
    return true;
}

bool solveSudoku(vector<vector<char>>& board) {  // Can track row and col for more efficient implementation
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == '.') {
                for (char n = '1'; n <= '9'; n++) {
                    if (checkInsertion(board, r, c, n)) {
                        board[r][c] = n;
                        // bool flag = sudokuSolver(board);
                        if (solveSudoku(board) == true) {    // Recursion inside the if (cI()) only, else segfault
                            return true;
                        }
                        else {
                            board[r][c] = '.';
                        }
                    }
                }
                return false;               // necessary
            }
        }
    }
    return true;  // Base case
}

// void solveSudoku(vector<vector<char>>& board) {
//     sudokuSolver(board);
// }

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

        solveSudoku(board);
        for (auto& vec : board) {
            for (char& ch : vec) {
                cout << ch << " ";
            }
            cout << endl;
        }

        cout << "_________________" << endl;
    }
    return 0;
}

// My correct, but less efficient and inconcise implementation with bloated logic:

// bool checkInsertion(vector<vector<char>>& board, int rowCheck, int colCheck, int test) {
//     char num = '0' + test;                                                 // Test needs to be input since we check before changing board
//     if (board[rowCheck][colCheck] != '.') {                                // Safety condition: Don't fill if not empty
//         return false;
//     }

//     if (test > 9 || test < 1) {                                            // Safety condition: Don't fill if input incorrect
//         return false;
//     }

//     for (int x = 0; x < 9; x++) {                                          // Check entire colCheck (all rows) and rowCheck (all cols) for test
//         if (x != rowCheck) {                                               // x is a row, check all rows except the one cell where we will input
//             if (board[x][colCheck] == num) {                               // Check if any cell (using rows) in the col colCheck is equal to test
//                 return false;
//             }
//         }

//         if (x != colCheck) {                                               // x is a col, check all cols except the one cell where we will input
//             if (board[rowCheck][x] == num) {                               // Check if any cell (using cols) in the row rowCheck is equal to test
//                 return false;
//             }
//         }
//     }

//     int topLine = 3 * (rowCheck / 3);                                      // Top-line of a subgrid for a given value of rowCheck
//     int leftLine = 3 * (colCheck / 3);                                     // Left-line of a subgrid for a given value of colCheck
//     for (int r = topLine; r <= topLine + 2; r++) {                         // Total 9 iterations in subgrid, from topline to topline + 2 (3 rows)..
//         for (int c = leftLine; c <= leftLine + 2; c++) {                   // and leftline to leftine + 2 (3 cols per row). Can we merge with x-loop?
//             if (r != rowCheck && c != colCheck) {
//                 if (board[r][c] == num) {
//                     return false;
//                 }
//             }
//         }
//     }

//     return true;                                                            // If not in row, col or subgrid, return true
// }

// void sudokuSolver(vector<vector<char>>& board, int r, int c, bool& flag) {  // Flag by-ref to notify when base case is hit to avoid further backtracking
//     if (r > 8) {                                                            // Base case: Only when all rows have been covered, next call to r = 9 made
//         // cout << "Base case: (" << r << ", " << c << ")" << endl;         // Other base cases based on c = 9 are incorrect since we explicitly avoid c > 8
//         flag = true;                                                        // Modify flag to notify base case is hit (Can we do this better?)
//         return;
//     }

//     while (board[r][c] != '.') {                                            // Loop to take our pointer to next empty cell (Separate from induction steps?)
//         if (r == 8 && c == 8) {                                             // Necessary to terminate at the last cell of the board, else base case gets hit early
//             // cout << "breaking at (8, 8)" << endl;
//             break;
//         }
//         if (c < 8) {                                                        // Increase c while possible, else reset it to 0 and increase r
//             c++;                                                            // Can this be done better? Notice the cyclicity in c and use modulus %
//         }
//         else {
//             c = 0;
//             r++;
//         }
//     }

//     for (int n = 1; n <= 9; n++) {                                          // This loop reflects our choices ie. inserting 1 to 9 in the cells
//         if (checkInsertion(board, r, c, n)) {                               // If safe to insert n at (r,c)..
//             board[r][c] = ('0' + n);                                        // Do it, then call the next insertion recursively
//             // cout << "(" << r << ", " << c << ") = " << n << endl;
//             if (c == 8) {                                                   // If at the last col in a row, begin checking from the next row, 0th col
//                 sudokuSolver(board, r + 1, 0, flag);
//             }
//             else {                                                          // Else, begin checking from the next col in the current row
//                 sudokuSolver(board, r, c + 1, flag);
//             }
//         }
//         if (flag == false) {                                                // Backtracking step: Only valid while base case is not hit, otherwise result will be reversed
//             board[r][c] = '.';                                              // Will help restore the original board if we get out of checkInsertion() when it did not work out
//             // cout << "(" << r << ", " << c << ") = ." << endl;            // If it did work out, we will keep calling recursively till the base case gets hit
//         }                                                                   // We will only come out of checkInsertion() wit flag = false if it did not work out down the line
//     }                                                                       // In which case, we must reverse this particular insertion and go back to previous call to find a new route
// }

// vector<vector<char>> solveSudoku(vector<vector<char>>& board) {
//     bool flag = false;
//     sudokuSolver(board, 0, 0, flag);
//     return board;
// }
