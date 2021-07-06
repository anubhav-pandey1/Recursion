#include <bits/stdc++.h>
using namespace std;

bool checkQueen(vector<int>& prevCols, int r, int c) { // 02, 1,3
    for (int rp = 0; rp < prevCols.size(); rp++) {
        int cp = prevCols[rp];
        if (rp == r || cp == c) {
            return false;
        }
        else if (abs(rp - r) == abs(cp - c)) {
            return false;
        }
        else {
            continue;
        }
    }
    return true;
}

vector<string> createBoard (vector<int>& prevCols, int n) {
    vector<string> board;
    for (int i = 0; i < n; i++) {
        string line(n, '.');
        int queenIdx = prevCols[i];
        line[queenIdx] = 'Q';
        board.push_back(line);
    }
    return board;
}

void helperNQueens(int n, vector<vector<string>>& result, vector<int>& prevCols, int r = 0) {
    if (prevCols.size() == n) {
        vector<string> board = createBoard(prevCols, n);
        prevCols.clear();
        r = 0;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (checkQueen(prevCols, r, i)) {
            prevCols.push_back(i);
            r++;
            helperNQueens(n, result, prevCols, r);
        }
        continue;
    }
    r--;
    prevCols.pop_back();
    return;
}

vector<vector<string>> solveNQueens(int numPieces) {
    vector<vector<string>> result;
    vector<int> prevCols = {};
    helperNQueens(numPieces, result, prevCols);
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
        vector<int> pc = {0, 2};
        cout << checkQueen(pc, 1, 3) << endl;
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

// Alt implementation:

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
