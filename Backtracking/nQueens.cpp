#include <bits/stdc++.h>
using namespace std;

bool checkQueen(vector<int>& prevCols, int c) {             // Bounding function to check if the Q can be added at column c
    int r = prevCols.size();                                // Rows corresponding to prevCols are their indices, so next row = size
    for (int rp = 0; rp < prevCols.size(); rp++) {          // rp -> prevRows and it goes from 0 to r - 1 (indices)
        int cp = prevCols[rp];                              // Prev. filled column values are stored at index rp in prevCols[]
        if (cp == c || (abs(rp - r) == abs(cp - c))) {      // If the current column is equal to any of the prevCols[] values or..
            return false;                                   // if current (r,c) is at a diagonal from any prev (rp, cp) (D-max metric)
        }                                                   // then Q can't be inserted at (r,c) so return false
    }                                                       // Check this for all values of (rp, cp) in prevCols[]
    return true;                                            // If not false for all values in prevCols[], then Q can be inserted
}                                                           // abs(rp - r) == abs(cp - c) checks if the two pts are diagonal or not

vector<string> createBoard (vector<int>& prevCols) {        // Helper function to create a chessboard for the base case
    int n = prevCols.size();                                // No. of rows = no. of elements in prevCols[] ie. no. of prev. cols
    vector<string> board;                                   // Board represented as vector of strings, where each row is a string
    for (int i = 0; i < n; i++) {                           // Iterating over each column value in prevCols[] to create a row with Q
        string line(n, '.');                                // Creating a string representing an empty row in the board "...."
        int queenIdx = prevCols[i];                         // Finding out the location for Q for the particular row using prevCols[]
        line[queenIdx] = 'Q';                               // Flipping the char at queenIdx from '.' to 'Q'
        board.push_back(line);                              // Adding this line to our initially created chessboard
    }                                                       // We can add all this code under the base case scope too but this is neat
    return board;                                           // The board gets constructed once all the iterations have been completed
}

void helperNQueens(int n, vector<vector<string>>& result, vector<int>& prevCols, int r) {
    if (prevCols.size() == n) {                             // Base case: Once all N columns are filled ie. prevCols[] is full
        vector<string> board = createBoard(prevCols);       // We can create a chessboard to return using the helper function
        prevCols.pop_back();                                // Backtracking for base case: since function returns from here directly
        result.push_back(board);                            // Push-back the creating chess board to the result[] storing boards
        return;                                             // Return back to prev call in the call stack ie. prevCols[] - 1 and r - 1
    }                                                       // We need to pop from prevCols[] otherwise incorrect results after first BC

    for (int i = 0; i < n; i++) {                           // N choices for column location c to place Q if base case is not hit
        if (checkQueen(prevCols, i)) {                      // Check if Q should be added for the ith choice using bounding function
            prevCols.push_back(i);                          // If yes, prevCols must add a new member column index i and check for next
            helperNQueens(n, result, prevCols, r + 1);      // Recursively, find location for next row r + 1 with new set of prevCols[]
        }                                                   // If no, increment i and check for the next choice for c = i + 1
    }                                                       // Once all the column choices for a particular row are checked, go backtrack..
    prevCols.pop_back();                                    // Pop the last col from prevCols[] to open space for other options to get filled
}                                                           // This is the backtracking step ie. us going back to find newer paths/options

vector<vector<string>> solveNQueens(int numPieces) {        // Solver function to take specific inputs depending on the problem statement
    vector<vector<string>> result;                          // Creating an array to store all possible chessboards (arrays of strings)
    vector<int> prevCols;                                   // An array to keep track of filled columns (and rows ie. indices of the cols)
    helperNQueens(numPieces, result, prevCols, 0);          // Call void-returning function, with result vector passed by reference
    return result;                                          // Once the helperNQueens() has identified and stored all boards, return the result
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
        int numPieces;
        cin >> numPieces;

        vector<vector<string>> result = solveNQueens(numPieces);
        for (auto& vec : result) {
            for (string& str : vec) {
                cout << str << endl;
            }
            cout << "---------" << endl;
        }

        cout << "................." << endl;
    }
    return 0;
}

// Test cases:

// Inputs:

// 2
// 4
// 1

// Outputs:

// .Q..
// ...Q
// Q...
// ..Q.
// ---------
// ..Q.
// Q...
// ...Q
// .Q..
// ---------
// .................
// Q
// ---------
// .................


// Alt implementation (Incorrect): boolCheck implemented for NxN but wasn't working correctly for 1xN, 2xN...
// Now it does after updating to include RN

// bool checkLastRow(vector<string>& board, int c) {
//     int RN = board.size();
//     int r = board.size() - 1;
//     int N = board[0].size();
//     for (int x = 1; x < N; x++) {
//         if ((r + x) < RN && (c + x) < N) {
//             if (board[r + x][c + x] == 'Q')
//                 return false;
//         }
//         if ((r + x) < RN && (c - x) >= 0) {
//             if (board[r + x][c - x] == 'Q')
//                 return false;
//         }
//         if ((r - x) >= 0 && (c - x) >= 0) {
//             if (board[r - x][c - x] == 'Q')
//                 return false;
//         }
//         if ((r - x) >= 0 && (c + x) < N) {
//             if (board[r - x][c + x] == 'Q')
//                 return false;
//         }
//         if ((r - x) >= 0) {
//             if (board[r - x][c] == 'Q')
//                 return false;
//         }
//         if ((r + x) < RN) {
//             if (board[r + x][c] == 'Q')
//                 return false;
//         }
//     }
//     return true;
// }

// void helperNQueens(int n, vector<string>& board, const map<int, string>& mp, vector<vector<string>>& result) {
//     if (board.size() == n) {
//         result.push_back(board);
//         board.pop_back();
//         return;
//     }
//     for (int i = 0; i < n; i++) {
//         string s = mp.at(i);
//         board.push_back(s);
//         if (checkLastRow(board, i)) {
//             helperNQueens(n, board, mp, result);
//         }
//         else {
//             board.pop_back();
//         }
//     }
//     // board.pop_back();
//     // return;
// }

// vector<vector<string>> solveNQueens(int n) {
//     vector<vector<string>> result;
//     map<int, string> mp;
//     string s(n, '.');
//     for (int i = 0; i < n; i++) {
//         s[i] = 'Q';
//         mp[i] = s;
//         s[i] = '.';
//     }
//     vector<string> board;
//     helperNQueens(n, board, mp, result);
//     return result;
// }
