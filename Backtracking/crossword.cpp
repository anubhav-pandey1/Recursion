#include <bits/stdc++.h>
using namespace std;

void printBoard(vector<string>& board) {
    for (int r = 0; r < 10; r++) {
        cout << board[r] << endl;
    }
    cout << "___________" << endl;
}

bool canPlaceWordHorizontally(vector<string>& board, string word, int r, int c) {         // Trials and tribulations type bounding function
    if (c > 0 && board[r][c - 1] != '+') {                                                // If col index is 1 or greater, and the prev. cell is not a + (ie. word does not fit)
        return false;                                                                     // Then (r, c) is not a cell where the word can be placed horizontally
    }
    else if (c + word.size() < 10 && board[r][c + word.size()] != '+') {                  // If the cell just next to the end of the to-be-inserted word ie. dist of word.size is in bounds,
        return false;                                                                     // and if it is not a + (ie. word does not fit), then word cant be placed at (r, c)
    }

    for (int col = 0; col < word.size(); col++) {                                         // Loop over the next word.size cells to check them for the word-to-be-inserted
        if (c + col > 9) {                                                                // If at any moment, the index goes greater than 9, it goes out of bounds
            return false;
        }
        if (board[r][c + col] != '-' && board[r][c + col] != word[col]) {                 // If the cell is not blank and the cell does not have the same character as the word at the same index
            return false;                                                                 // Here && must be used and not || as we have != in the individual conditions (check Truth table)
        }                                                                                 // The same as:- !(board[r][c + col] == '-' || board[r][c + col] == word[col])
    }

    return true;                                                                          // Return true if it survives all trials and tribulations
}

bool canPlaceWordVertically(vector<string>& board, string word, int r, int c) {           // Similar to above
    if (r > 0 && board[r - 1][c] != '+') {
        return false;
    }
    else if (r + word.size() < 10 && board[r + word.size()][c] != '+') {
        return false;
    }

    for (int row = 0; row < word.size(); row++) {
        if (r + row > 9) {
            return false;
        }
        if (board[r + row][c] != '-' && board[r + row][c] != word[row]) {
            return false;
        }
    }

    return true;
}

vector<bool> horizontallyPlaceWord(vector<string>& board, string word, int r, int c) {    // Return a boolean array to store if we placed the letter at the index or not
    vector<bool> wePlaced;                                                                // Will be used while unplacing to only unplace the letters we placed
    for (int col = 0; col < word.size(); col++) {                                         // Iterate over word.size cells beginning at (r, c) to place chars one by one
        if (board[r][c + col] == '-') {
            board[r][c + col] = word[col];
            wePlaced.push_back(true);
        }
        else {
            wePlaced.push_back(false);
        }
    }
    return wePlaced;
}

vector<bool> verticallyPlaceWord(vector<string>& board, string word, int r, int c) {
    vector<bool> wePlaced; // All false initially
    for (int row = 0; row < word.size(); row++) {
        if (board[r + row][c] == '-') {
            board[r + row][c] = word[row];
            wePlaced.push_back(true);
        }
        else {
            wePlaced.push_back(false);
        }
    }
    return wePlaced;
}

void unplaceWordHorizontally(vector<string>& board, vector<bool> wePlaced, int r, int c) {
    for (int col = 0; col < wePlaced.size(); col++) {
        if (wePlaced[col]) {
            board[r][c + col] = '-';
        }
    }
}

void unplaceWordVertically(vector<string>& board, vector<bool> wePlaced, int r, int c) {
    for (int row = 0; row < wePlaced.size(); row++) {
        if (wePlaced[row]) {
            board[r + row][c] = '-';
        }
    }
}

void solveCrossword(vector<string>& board, vector<string>& words, int wordIdx) {
    if (wordIdx == words.size()) {
        printBoard(board);
        return;
    }

    string word = words[wordIdx];
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            if (board[r][c] == '-' || board[r][c] == word[0]) {
                if (canPlaceWordHorizontally(board, word, r, c)) {
                    vector<bool> wePlacedH = horizontallyPlaceWord(board, word, r, c);
                    solveCrossword(board, words, wordIdx + 1);
                    unplaceWordHorizontally(board, wePlacedH, r, c);
                }
                if (canPlaceWordVertically(board, word, r, c)) {
                    vector<bool> wePlacedV = verticallyPlaceWord(board, word, r, c);
                    solveCrossword(board, words, wordIdx + 1);
                    unplaceWordVertically(board, wePlacedV, r, c);
                }
            }
        }
    }
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

        // int row = 1, col = 0;
        // bool type = isVertical(board, row, col);
        // // cout << isVertical(board, 8, 9) << endl; // Checking (8, 9) before filling
        // int len = findTotalLength(board, row, col, type);
        // cout << len << endl;
        // fillBlanks(board, row, col, type, words[2]);

        // // fillBlanks overwrites during intersections
        // row = 2, col = 1;
        // bool type2 = isVertical(board, row, col);
        // cout << type2 << endl;                                   // Right - Must be 0 for (1,0) and (2,1)
        // cout << isIntersect(board, row, col, type2) << endl;     // Right - Must be 1 for (1,0) and (2,1)
        // cout << findLength(board, row, col, type2) << endl;      // Right - Must be 6 for (1,0) and (2,1)
        // cout << findTotalLength(board, row, col, type2) << endl; // Right - Must be 7 for (1,0) and (2,1)
        // fillBlanks(board, row, col, type2, words[1]);

        // Output:-
        solveCrossword(board, words, 0);
        // printBoard(board);
    }
    return 0;
}

// Only works for test cases where interesction is at the front and end due to boolean nature of helphers
// Use integer-based intersection locators to solve this issue, but this is getting too complex

// void printBoard(vector<string>& board) {
//     for (int r = 0; r < 10; r++) {
//         cout << board[r] << endl;
//     }
//     cout << "___________" << endl;
// }

// bool isVertical(vector<string>& board, int r, int c) {      // TODO: Check from end of word too, not just beginning
//     if (board[r + 1][c] == '-' && board[r][c + 1] != '-') {
//         return true;
//     }
//     else if (board[r][c + 1] == '-') {
//         return false;
//     }
// }

// int findLength(vector<string>& board, int r, int c, bool vertical) {
//     int n = 1; // Assuming (r, c) is a dash
//     if (vertical) {
//         while (board[r + 1][c] == '-') {
//             n++;
//             r++;
//         }
//     }
//     else {
//         while (board[r][c + 1] == '-') {
//             n++;
//             c++;
//         }
//     }
//     return n;
// }

// bool isIntersect(vector<string>& board, int r, int c, bool vertical) {  // TODO: Can intersect with end of word too, this one only has beginning covered
//     int len = findLength(board, r, c, vertical);
//     if (vertical && ((r > 0 && isalpha(board[r - 1][c])) || ((r + len) <= 9 && isalpha(board[r + len][c])))) { // Horizontal me vertical intersection??
//         return true;
//     }
//     else if (!vertical && ((c > 0 && isalpha(board[r][c - 1])) || ((c + len) <= 9 && isalpha(board[r][c + len])))) {
//         return true;
//     }
//     return false;                                                      // Fail, can intersect in the middle as well
// }

// bool intersectFront(vector<string>& board, int r, int c, bool vertical) {  // Only use if isIntersect is true
//     if (vertical && ((r > 0 && isalpha(board[r - 1][c])))) {
//         return true;
//     }
//     else if (!vertical && ((c > 0 && isalpha(board[r][c - 1])))) {         // Fail, can intersect in the middle as well
//         return true;
//     }
//     return false;
// }

// char findIntersect(vector<string>& board, int r, int c, bool vertical) {  // Only use if isIntersect is true
//     bool front = intersectFront(board, r, c, vertical);
//     int len = findLength(board, r, c, vertical);
//     if (front) {
//         if (vertical) {
//             return board[r - 1][c];
//         }
//         else {
//             return board[r][c - 1];
//         }
//     }
//     else {
//         if (vertical) {
//             return board[r + len][c];
//         }
//         else {
//             return board[r][c + len];
//         }
//     }
// }

// int findTotalLength(vector<string>& board, int r, int c, bool vertical) {
//     int n = 1; // Assuming (r, c) is a dash
//     if (vertical) {
//         if (isIntersect(board, r, c, vertical)) {  // Let this block stay to find total len of word required
//             n++;
//         }

//         while (board[r + 1][c] == '-') {
//             n++;
//             r++;
//         }
//     }
//     else {
//         if (isIntersect(board, r, c, vertical)) {
//             n++;
//         }

//         while (board[r][c + 1] == '-') {
//             n++;
//             c++;
//         }
//     }
//     return n;
// }

// void fillBlanks(vector<string>& board, int r, int c, bool vertical, string word) {
//     bool intersect = isIntersect(board, r, c, vertical);
//     bool front = intersectFront(board, r, c, vertical);
//     int len = word.size();
//     if (vertical && intersect) {        // TODO: Refactor, can't go r-- or c-- if intersects at back
//         if (front)                      // Put inside as can only be used if isIntersect is true
//             r--;
//         else                            // Reduce len if intersects at back to avoid last char
//             len--;
//     }
//     else if (!vertical && intersect) {  // Do these blocks even matter? Overwriting
//         // len--;
//         if (front)                      // Put inside as can only be used if isIntersect is true
//             c--;
//         else
//             len--;                      // If intersects at back, reduce length
//     }

//     if (vertical) {
//         for (int x = 0; x < len; x++) { // TODO: Refactor
//             board[r + x][c] = word[x];
//         }
//     }
//     else {
//         for (int x = 0; x < len; x++) {
//             board[r][c + x] = word[x];
//         }
//     }
// }

// void unfillBlanks(vector<string>& board, int r, int c, int len, bool vertical) {
//     if (vertical) {
//         for (int x = 0; x < len; x++) { // TODO: Refactor
//             board[r + x][c] = '-';
//         }
//     }
//     else {
//         for (int x = 0; x < len; x++) {
//             board[r][c + x] = '-';
//         }
//     }
// }

// bool solveCrossword(vector<string>& board, vector<string>& words) {
//     for (int r = 0; r < 10; r++) {
//         for (int c = 0; c < 10; c++) {
//             if (board[r][c] == '-') {
//                 bool vertical = isVertical(board, r, c);
//                 bool intersect = isIntersect(board, r, c, vertical);
//                 int totalLen = findTotalLength(board, r, c, vertical);
//                 int length = findLength(board, r, c, vertical);
//                 for (int i = 0; i < words.size(); i++) {
//                     if (words[i].size() == totalLen && !intersect) {
//                         string temp = words[i];
//                         fillBlanks(board, r, c, vertical, words[i]);
//                         // printBoard(board); // Visualize backtracking
//                         words[i] = "";
//                         if (solveCrossword(board, words) == true) {
//                             return true;
//                         }
//                         else {
//                             unfillBlanks(board, r, c, length, vertical);
//                             // printBoard(board); // Visualize backtracking
//                             words[i] = temp;
//                             // return false;
//                         }
//                     }
//                     else if (words[i].size() == totalLen && intersect) {
//                         string temp = words[i];
//                         char common = findIntersect(board, r, c, vertical);
//                         bool front = intersectFront(board, r, c, vertical);
//                         if (front && common == words[i][0]) {
//                             fillBlanks(board, r, c, vertical, words[i]);
//                             // printBoard(board); // Visualize backtracking
//                             words[i] = "";
//                             if (solveCrossword(board, words) == true) {
//                                 return true;
//                             }
//                             else {
//                                 unfillBlanks(board, r, c, length, vertical);
//                                 // printBoard(board); // Visualize backtracking
//                                 words[i] = temp;
//                                 // return false;
//                             }
//                         }
//                         else if (!front && common == words[i][words[i].size() - 1]) {
//                             string temp = words[i];
//                             fillBlanks(board, r, c, vertical, words[i]);
//                             // printBoard(board); // Visualize backtracking
//                             words[i] = "";
//                             if (solveCrossword(board, words) == true) {
//                                 return true;
//                             }
//                             else {
//                                 unfillBlanks(board, r, c, length, vertical);
//                                 // printBoard(board); // Visualize backtracking
//                                 words[i] = temp;
//                                 // return false;
//                             }
//                         }
//                     }
//                 }
//                 return false;
//             }
//         }
//     }
//     return true; // Implicit base case when we run out of the loop
// }

// Test cases:

// Inputs:

// 2
// +++++++++-
// -++++++++-
// -------++-
// -++++++++-
// -++++++++-
// -++++-----
// ------+++-
// -++++++++-
// +---------
// ++++++++++
// 6
// CHEMISTRY
// HISTORY
// PHYSICS
// MATHS
// GEOGRAPHY
// CIVICS
// +-++++++++
// +-++++++++
// +-++++-+++
// +-++++-+++
// +-++++-+++
// +-++++-+++
// +-++++-+++
// +-+------+
// +-++++++++
// +++-------
// 4
// PUNJAB
// JHARKHAND
// MIZORAM
// MUMBAI

// Outputs:

// +++++++++C
// P++++++++H
// HISTORY++E
// Y++++++++M
// S++++++++I
// I++++MATHS
// CIVICS+++T
// S++++++++R
// +GEOGRAPHY
// ++++++++++
// ___________
// +J++++++++
// +H++++++++
// +A++++P+++
// +R++++U+++
// +K++++N+++
// +H++++J+++
// +A++++A+++
// +N+MUMBAI+
// +D++++++++
// +++MIZORAM
// ___________
