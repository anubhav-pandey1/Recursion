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

void helperNQueens(int n, int& result, vector<int>& prevCols, int r) {
    if (prevCols.size() == n) {
        result++;
        prevCols.pop_back();
        return;
    }

    for (int i = 0; i < n; i++) {
        if (checkQueen(prevCols, i)) {
            prevCols.push_back(i);
            helperNQueens(n, result, prevCols, r + 1);
        }
    }
    prevCols.pop_back();
}

int totalNQueens(int numPieces) {
    int result = 0;
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

        int result = totalNQueens(numPieces);
        cout << result << endl;
    }
    return 0;
}
