#include <bits/stdc++.h>
using namespace std;

// Reference - https://www.geeksforgeeks.org/toggle-case-string-using-bitwise-operators/
// 32 is the same as 1 << 5 (ie shifting 1 bit by 5 places to the left)
// Taking XOR of a char with 32 inverts its case from upper to lower or vice-versa

vector<string> letterCasePermutation(string s, string aux = "") {       // Pass-by-ref causes nasty bug due to s.pop_back()
    if (s == "") {                                                      // Base case: When input gets reduced to ""
        return {aux};                                                   // Aux will have the entire output when s == ""
    }                                                                   // Modified recursion tree approach with empty branches
    int len = s.size();                                                 // Calculate once, use multiple times to save time
    string last(1, s[len - 1]);                                         // Convert the last character to string using constructor
    string lastInvert = "";                                             // Placeholder for inverted last char, to be used for checks
    if (isalpha(s[s.size() - 1])) {                                     // If the last char is in the alphabet ..
        lastInvert = string(1, s[len - 1] ^ 32);                        // Take XOR of last char with 32 to invert the case
    }                                                                   // lastInvert == "" if last char is numeric, used for checks
    s.pop_back();                                                       // Pop the last char to reduce input size for next call
    vector<string> auxVec1 = letterCasePermutation(s, last + aux);      // Left subtree: last char + aux = new aux for next call
    vector<string> auxVec2 = {};                                        // Placeholder for right subtree output, empty if numeric
    if (lastInvert != "") {                                             // If the last char is not numeric, then ..
        auxVec2 = letterCasePermutation(s, lastInvert + aux);           // Right subtree: inverted last char + aux = new aux
        auxVec1.insert(auxVec1.end(), auxVec2.begin(), auxVec2.end());  // Append right subtree output to left subtree output
    }                                                                   // ^can be done outside the if condition scope as well
    return auxVec1;                                                     // Return the combined output vector
}                                                                       // A dry run is must to clearly understand this

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
        int size;
        cin >> size;
        string s;
        cin >> s;

        vector<string> result = letterCasePermutation(s);
        for (string& str : result) {
            cout << str << endl;
        }
        cout << ".............." << endl;
    }
    return 0;
}

// Test cases:

// Inputs:

// 7
// 3
// a1
// 2
// 2P
// 1
// r
// 4
// a1B2
// 4
// a123
// 4
// 1234
// 4
// aB1c

// Outputs:

// a1
// A1
// ..............
// 2P
// 2p
// ..............
// r
// R
// ..............
// a1B2
// A1B2
// a1b2
// A1b2
// ..............
// a123
// A123
// ..............
// 1234
// ..............
// aB1c
// AB1c
// ab1c
// Ab1c
// aB1C
// AB1C
// ab1C
// Ab1C
// ..............
