#include <bits/stdc++.h>
using namespace std;

bool isVertical(vector<string>& board, int r, int c) {      // TODO: Check from end of word too, not just beginning
    if (board[r + 1][c] == '-' && board[r][c + 1] != '-') {
        return true;
    }
    else if (board[r][c + 1] == '-') {
        return false;
    }
}

bool isIntersect(vector<string>& board, int r, int c, bool vertical) {  // TODO: Can intersect with end of word too, this one only has beginning covered
    if (!vertical && ((r > 0 && isalpha(board[r - 1][c])) || (r < 9 && isalpha(board[r + 1][c])))) { // Horizontal me vertical intersection??
        return true;
    }
    else if (vertical && ((c > 0 && isalpha(board[r][c - 1])) || (c < 9 && isalpha(board[r][c + 1])))) {
        return true;
    }
    return false;
}

int findTotalLength(vector<string>& board, int r, int c, bool vertical) {
    int n = 1; // Assuming (r, c) is a dash
    if (vertical) {
        if (isIntersect(board, r, c, vertical)) {  // Let this block stay to find total len of word required
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

int findLength(vector<string>& board, int r, int c, bool vertical) {
    int n = 1; // Assuming (r, c) is a dash
    if (vertical) {
        while (board[r + 1][c] == '-') {
            n++;
            r++;
        }
    }
    else {
        while (board[r][c + 1] == '-') {
            n++;
            c++;
        }
    }
    return n;
}

void fillBlanks(vector<string>& board, int r, int c, bool vertical, string word) {
    bool intersect = isIntersect(board, r, c, vertical);
    int len = word.size();
    if (vertical && intersect) {        // TODO: Refactor
        r--;
    }
    else if (!vertical && intersect) {  // Do these blocks even matter? Overwriting
        // len--;
        c--;
    }

    if (vertical) {
        for (int x = 0; x < len; x++) { // TODO: Refactor
            board[r + x][c] = word[x];
        }
    }
    else {
        for (int x = 0; x < len; x++) {
            board[r][c + x] = word[x];
        }
    }
}

void unfillBlanks(vector<string>& board, int r, int c, int len, bool vertical) {
    if (vertical) {
        for (int x = 0; x < len; x++) { // TODO: Refactor
            board[r + x][c] = '-';
        }
    }
    else {
        for (int x = 0; x < len; x++) {
            board[r][c + x] = '-';
        }
    }
}

bool solveCrossword(vector<string>& board, vector<string>& words) {
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            if (board[r][c] == '-') {
                bool vertical = isVertical(board, r, c);
                int totalLen = findTotalLength(board, r, c, vertical);
                int length = findLength(board, r, c, vertical);
                for (int i = 0; i < words.size(); i++) {
                    if (words[i].size() == totalLen) {
                        string temp = words[i];
                        fillBlanks(board, r, c, vertical, words[i]);
                        words[i] = "";
                        if (solveCrossword(board, words) == true) {
                            return true;
                        }
                        else {
                            unfillBlanks(board, r, c, length, vertical);
                            words[i] = temp;
                            // return false;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true; // Implicit base case when we run out of the loop
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
        // cout << isVertical(board, 8, 9) << endl; // Checking (8, 9) before filling
        // int len = findTotalLength(board, row, col, type);
        // cout << len << endl;
        // fillBlanks(board, row, col, type, words[0]);

        // fillBlanks overwrites during intersections
        // row = 5, col = 9;
        // bool type2 = isVertical(board, row, col);
        // cout << type2 << endl;
        // cout << isIntersect(board, row, col, type2) << endl;
        // fillBlanks(board, row, col, type2, words[2]);

        // Output:-
        solveCrossword(board, words);

        for (int r = 0; r < 10; r++) {
            cout << board[r] << endl;
        }
    }
    return 0;
}
