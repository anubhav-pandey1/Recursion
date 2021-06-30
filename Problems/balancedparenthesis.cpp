#include <bits/stdc++.h>
using namespace std;

vector<string> balancedParentheses(int nl, int nr = -1, string s = "") {  // Modified I/P O/P recursive tree -> multiple breaks in the tree
    if (nr == -1) {                                                       // To enable only single n input in the function call in main()
        nr = nl;                                                          // For the default call, nl = nr, which happens when no nr input
    }                                                                     // We have both integer and string inputs for the recursive calls
    string left(nl, '(');                                                 // Creating the strings of the left/right parentheses to be concated
    string right(nr, ')');                                                // String constructor and nl/nr values used to construct the strings
    if (nl == 0 || nr == 0) {                                             // Base case: If either of nl/nr becomes 0 during any recursive call..
        return {s + left + right};                                        // Add left/right to the existing string s, one of which will be empty
    }                                                                     // Return a vector with the concated string + left/right

    vector<string> auxVec1 = {};                                          // Empty auxilary vector, to be used to store left subtree output
    vector<string> auxVec2 = {};                                          // Empty auxilary vector, to be used to store right subtree output
    if (nl - 1 <= nr) {                                                   // Condition for left-subtree to exist -> nl <= nr (nl - 1 for left)
        s += '(';                                                         // Add a left bracket to fill one more spot in s, reduce nl by 1
        auxVec1 = balancedParentheses(nl - 1, nr, s);                     // Recursive call on modified s and nl to generate left side output
        s.pop_back();                                                     // Pop back added left bracket as the original s will be used further
    }                                                                     // If left subtree condition was not met, left subtree output is empty
    if (nl <= nr - 1) {                                                   // Condition for right-subtree to exist -> nl <= nr (nr - 1 for right)
        s += ')';                                                         // Add a right bracket to fill one more spot in s, reduce nr by 1
        auxVec2 = balancedParentheses(nl, nr - 1, s);                     // Recursive call on modified s and nr to generate right side output
    }                                                                     // If right subtree condition was not met, its subtree output is empty
    auxVec1.insert(auxVec1.end(), auxVec2.begin(), auxVec2.end());        // Concatenate both the subtree outputs together in a single array
    return auxVec1;                                                       // Return the vector with both the outputs (may be empty too)
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

        vector<string> result = balancedParentheses(n);
        for (string& str : result) {
            cout << str << endl;
        }
        cout << ".............." << endl;
    }
    return 0;
}

// Test cases:

// Inputs:

// 3
// 1
// 2
// 3

// Outputs:

// ()
// ..............
// (())
// ()()
// ..............
// ((()))
// (()())
// (())()
// ()(())
// ()()()
// ..............
