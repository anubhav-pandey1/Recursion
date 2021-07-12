#include <bits/stdc++.h>
using namespace std;

bool checkInsertion(vector<vector<char>>& board, int row, int col, char test) {
    int topRow = 3 * (row / 3);                                                 // Top-row of a subgrid for a given value of rowCheck
    int leftCol = 3 * (col / 3);                                                // Left-col of a subgrid for a given value of colCheck
    for (int x = 0; x < 9; x++) {                                               // 9 comparisions required for the cell's row/col/subgrid
        if (board[row][x] == test) {                                            // Check for test in the row of the cell, keeping row fixed
            return false;
        }
        if (board[x][col] == test) {                                            // Look for test in the col of the cell, keeping col fixed
            return false;
        }
        if (board[topRow + (x / 3)][leftCol + (x % 3)] == test) {               // Toprow + (0, 1, 2, .., 8) / 3 gives all the 3 row values in the subgrid
            return false;                                                       // It remains 0 for {0, 1, 2}, becomes 1 for {3, 4, 5} and 2 for {6, 7, 8}
        }                                                                       // Leftcol + (0, 1, 2, .., 8) % 3 gives all the 3 col values in the subgrid
    }                                                                           // It is 0 for {0, 3, 6}, becomes 1 for {1, 4, 7} and 2 for {2, 5, 8}
    return true;
}

bool solveSudoku(vector<vector<char>>& board) {                                 // Can track row and col for more efficient implementation
    for (int r = 0; r < 9; r++) {                                               // Looping a 2-D matrix to find the next empty cell to fill
        for (int c = 0; c < 9; c++) {                                           // Base case will hit after both the loops have ended ie. no more cells
            if (board[r][c] == '.') {                                           // Check if the cell is empty, otherwise move to next value of c
                for (char n = '1'; n <= '9'; n++) {                             // These chars represent our choices to fill the board, '1' + 1 == '2'
                    if (checkInsertion(board, r, c, n)) {                       // Check if the char n can be inserted in the board at (r, c)
                        board[r][c] = n;                                        // If true, insert n in the board at (r, c) and prepare for recursive step
                        // bool flag = sudokuSolver(board);                     // A flag based implementation can also be used inside the if (flag == true)
                        if (solveSudoku(board) == true) {                       // Recursive call inside the checkInsertion{}, else it will fill the next eligible n
                            return true;                                        // If recursive call returns true, you return true back to the upper call
                        }                                                       // Can get overflow if recursion not inside cI{} as base case will not get hit
                        else {                                                  // If true not returned from lower levels -> base case not hit -> wrong route taken
                            board[r][c] = '.';                                  // Backtracking step: Revert the insertion of n if false and move to the next n value
                        }                                                       // This must be inside the cI{} as well, complementing the boolean recursive call
                    }                                                           // Check the next value of n, unless the recursion has already fallen to base case
                }                                                               // If none of the n values can be filled, return false so that it can backtrack further
                return false;                                                   // This false value is not returned if recursion falls to the base case, starts returning trues
            }                                                                   // Once it starts returning trues for all preceeding calls, the main call will return true and end
        }                                                                       // A dry-run is must to understand this recursive pattern without a clear base case
    }                                                                           // Also, instead of precalculating the index of empty cell, recursion is in the loops
    return true;                                                                // Base case:- After r == 8 and c == 8, it skips return false and jumps to this value
}                                                                               // If there are no more empty cells left, it also jumps straight to the base case

// Slightly more efficient implementation, tracking row and col, but not worth it
// Instead of starting search at r = 0 and c = 0, start it at row and col
// (8 + row) % row == row except when row == 8, it wraps back to 0
// (8 + col) % col == col except when col == 8, it wraps back to 0
// This means for the last row, it starts search from (0, c) and then goes to the next still empty spot
// Also, when c == 8, it starts the search from (r, 0) and then goes to the next still empty spot
// (8, c) and (r, 8) will get missed in this implementation if search is not start from (0, c) and (r, 0)
// r + (c/8) == r, unless c == 8, in which case it becomes r + 1
// (c + 1) % 9 == c + 1, unless c == 8, in which case it becomes 0
// solveSudoku(board, r + (c / 8), (c + 1) % 9) is basically solveSudoku(board, r, c) unless c == 8

bool solveSudoku(vector<vector<char>>& board, int row = 0, int col = 0) {
    for (int r = (8 + row) % 8; r < 9; r++) {
        for (int c = (8 + col) % 8; c < 9; c++) {
            if (board[r][c] == '.') {
                for (char n = '1'; n <= '9'; n++) {
                    if (checkInsertion(board, r, c, n)) {
                        board[r][c] = n;
                        if (solveSudoku(board, r + (c / 8), (c + 1) % 9) == true) {
                            return true;
                        }
                        else {
                            board[r][c] = '.';
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
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
        //         cout << checkInsertion(board, r, c, '4') << " ";
        //     }
        //     cout << endl;
        // }
        // cout << "_________________" << endl;

        solveSudoku(board, 0, 0);
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

//     int topRow = 3 * (rowCheck / 3);                                       // Top-line of a subgrid for a given value of rowCheck
//     int leftCol = 3 * (colCheck / 3);                                      // Left-line of a subgrid for a given value of colCheck
//     for (int r = topRow; r <= topRow + 2; r++) {                           // Total 9 iterations in subgrid, from topline to topline + 2 (3 rows)..
//         for (int c = leftCol; c <= leftCol + 2; c++) {                     // and leftline to leftine + 2 (3 cols per row). Can we merge with x-loop?
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


// Test cases:

// Inputs:

// 3
// ..9748...
// 7........
// .2.1.9...
// ..7...24.
// .64.1.59.
// .98...3..
// ...8.3.2.
// ........6
// ...2759..

// 53..7....
// 6..195...
// .98....6.
// 8...6...3
// 4..8.3..1
// 7...2...6
// .6....28.
// ...419..5
// ....8..79

// ...2...63
// 3....54.1
// ..1..398.
// .......9.
// ...538...
// .3.......
// .263..5..
// 5.37....8
// 47...1...

// Outputs:

// 5 1 9 7 4 8 6 3 2
// 7 8 3 6 5 2 4 1 9
// 4 2 6 1 3 9 8 7 5
// 3 5 7 9 8 6 2 4 1
// 2 6 4 3 1 7 5 9 8
// 1 9 8 5 2 4 3 6 7
// 9 7 5 8 6 3 1 2 4
// 8 3 2 4 9 1 7 5 6
// 6 4 1 2 7 5 9 8 3
// _________________
// 5 3 4 6 7 8 9 1 2
// 6 7 2 1 9 5 3 4 8
// 1 9 8 3 4 2 5 6 7
// 8 5 9 7 6 1 4 2 3
// 4 2 6 8 5 3 7 9 1
// 7 1 3 9 2 4 8 5 6
// 9 6 1 5 3 7 2 8 4
// 2 8 7 4 1 9 6 3 5
// 3 4 5 2 8 6 1 7 9
// _________________
// 8 5 4 2 1 9 7 6 3
// 3 9 7 8 6 5 4 2 1
// 2 6 1 4 7 3 9 8 5
// 7 8 5 1 2 6 3 9 4
// 6 4 9 5 3 8 1 7 2
// 1 3 2 9 4 7 8 5 6
// 9 2 6 3 8 4 5 1 7
// 5 1 3 7 9 2 6 4 8
// 4 7 8 6 5 1 2 3 9
// _________________
