#include <bits/stdc++.h>
using namespace std;

bool isVertical(vector<string>& board, int r, int c) {
    if (board[r + 1][c] == '-' && board[r][c + 1] != '-') {
        return true;
    }
    else if (board[r][c + 1] == '-') {
        return false;
    }
}

bool isIntersect(vector<string>& board, int r, int c, bool vertical) {
    if (vertical && (r > 0 && isalpha(board[r - 1][c]))) {
        return true;
    }
    else if (!vertical && (c > 0 && isalpha(board[r][c - 1]))) {
        return true;
    }
    return false;
}

int findLength(vector<string>& board, int r, int c, bool vertical) {
    int n = 1;
    if (vertical) {
        if (isIntersect(board, r, c, vertical)) {
            n++;
        }

        while (board[r + 1][c] == '-') {
            n++;
            r++;
        }
    }
    else {
        if (isIntersect(board, r, c, vertical)) {
            n++;
        }

        while (board[r][c + 1] == '-') {
            n++;
            c++;
        }
    }
    return n;
}

// void fillBlanks(vector<string>& board, int r, int c)

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
        vector<string> board;
        for (int r = 0; r < 10; r++) {
            string line;
            cin >> line;
            board.push_back(line);
        }

        int numWords;
        cin >> numWords;
        vector<string> words;
        while (numWords--) {
            string word;
            cin >> word;
            words.push_back(word);
        }

        // Tests for helper functions:-
        // int row = 0, col = 9;
        // bool type = isVertical(board, row, col);
        // int len = findLength(board, row, col, type);
        // cout << len << endl;
    }
    return 0;
}
