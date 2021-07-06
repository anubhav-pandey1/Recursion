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
