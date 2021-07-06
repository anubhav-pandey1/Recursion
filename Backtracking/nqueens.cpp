#include <bits/stdc++.h>
using namespace std;

bool checkQueen(vector<int>& prevCols, int c) {
    int r = prevCols.size();
    for (int rp = 0; rp < prevCols.size(); rp++) {
        int cp = prevCols[rp];
        if (cp == c || (abs(rp - r) == abs(cp - c))) {
            return false;
        }
    }
    return true;
}

vector<string> createBoard (vector<int>& prevCols) {
    int n = prevCols.size();
    vector<string> board;
    for (int i = 0; i < n; i++) {
        string line(n, '.');
        int queenIdx = prevCols[i];
        line[queenIdx] = 'Q';
        board.push_back(line);
    }
    return board;
}

void helperNQueens(int n, vector<vector<string>>& result, vector<int>& prevCols, int r) {
    if (prevCols.size() == n) {
        vector<string> board = createBoard(prevCols);
        prevCols.pop_back();
        result.push_back(board);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (checkQueen(prevCols, i)) {
            prevCols.push_back(i);
            helperNQueens(n, result, prevCols, r + 1);
        }
    }
    r--;
    prevCols.pop_back();
}

vector<vector<string>> solveNQueens(int numPieces) {
    vector<vector<string>> result;
    vector<int> prevCols;
    helperNQueens(numPieces, result, prevCols, 0);
    return result;
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


// Alt implementation (Incorrect):

// int numPieces;
// map<int, string> mp;
// string s(numPieces, '.');
// for (int i = 0; i < numPieces; i++) {
//     s[i] = 'Q';
//     mp[i] = s;
//     s[i] = '.';
// }

// bool checkLastRow(vector<string>& board, int c) {
//     int r = board.size() - 1;
//     int N = board[0].size();
//     for (int x = 1; x < N; x++) {
//         if ((r + x) < N && (c + x) < N && board[r + x][c + x] == 'Q') {
//             return false;
//         }
//         if ((r + x) < N && (c - x) >= 0 && board[r + x][c - x] == 'Q') {
//             return false;
//         }
//         if ((r - x) >= 0 && (c - x) >= 0 && board[r - x][c - x] == 'Q') {
//             return false;
//         }
//         if ((r - x) >= 0 && (c + x) < N && board[r - x][c + x] == 'Q') {
//             return false;
//         }
//         if ((r - x) >= 0 && board[r - x][c] == 'Q') {
//             return false;
//         }
//         if ((r + x) < N && board[r + x][c] == 'Q') {
//             return false;
//         }
//     }
//     return true;
// }

// void helperNQueens(int n, vector<string> board, vector<vector<string>>& result) {
//     if (board.size() == n) {
//         result.push_back(board);
//         return;
//     }
//     for (int i = 0; i < n; i++) {
//         board.push_back(mp[i]);
//         if (checkLastRow(board, i)) {
//             helperNQueens(n, board, result);
//         }
//     }
//     return;
// }

// vector<vector<string>> solveNQueens(int n) {
//     vector<vector<string>> result = {};
//     vector<string> board = {};
//     helperNQueens(n, board, result);
//     return result;
// }
