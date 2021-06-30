#include <bits/stdc++.h>
using namespace std;

// Target is to print all N-bit binary numbers having 1’s more than/equal to 0’s for any prefix

void generateBinaryStrings(int n1, int n0, int total, string s, vector<string>& result) {
    if (n1 + n0 == total) {                                   // Base case: When num zeroes + ones = string length
        result.push_back(s);                                  // Add the current string to results vector
        return;                                               // Terminate the recursion and return to prev. call
    }                                                         // Left subtree -> Add 1, Right subtree -> Add 0

    s += '1';                                                 // 1 can always be added so no if required for adding 1
    generateBinaryStrings(n1 + 1, n0, total, s, result);      // Recursive call on n1 + 1 with new, concated string
    s.pop_back();                                             // Popping newly added 1 to preserve s for right subtree:

    if (n1 >= n0 + 1) {                                       // Right subtree: Only when n1 >= updated n0 ie n0 + 1
        s += '0';                                             // Adding 0 to s if condition is met, n0 -> n0 + 1
        generateBinaryStrings(n1, n0 + 1, total, s, result);  // Recursive call on new s and n0 + 1 for right subtree
    }                                                         // No need to revert s as all processing is complete

    return;
}

vector<string> specialBinaryStrings(int n) {                  // Preprocessor function using solver generateBinaryStrings()
    int n1 = 0;                                               // Initially, num of 1s = 0
    int n0 = 0;                                               // Initially, num of 0s = 0
    int total = n;                                            // Total must remain constant in all recursive calls
    string s = "";                                            // Initially, the I/P string is empty, will be filled
    vector<string> result = {};                               // Initially, the results vector is empty, will be filled
    generateBinaryStrings(n1, n0, total, s, result);          // Call solver function and pass results by reference
    return result;                                            // Return results once it is generated
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
        int n;
        cin >> n;

        vector<string> result = specialBinaryStrings(n);
        for (string& str : result) {
            cout << str << endl;
        }
        cout << ".............." << endl;
    }
    return 0;
}

// Test cases:

// Inputs:

// 5
// 1
// 2
// 3
// 4
// 5

// Outputs:

// 1
// ..............
// 11
// 10
// ..............
// 111
// 110
// 101
// ..............
// 1111
// 1110
// 1101
// 1100
// 1011
// 1010
// ..............
// 11111
// 11110
// 11101
// 11100
// 11011
// 11010
// 11001
// 10111
// 10110
// 10101
// ..............
