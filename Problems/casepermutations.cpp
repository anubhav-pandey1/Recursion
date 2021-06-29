#include <bits/stdc++.h>
using namespace std;

vector<string> caseChangePermutations(string s, string aux = "") {        // Solved using recursive tree method
    if (s == "") {                                                        // Base condition: If input is empty in any call
        return {aux};                                                     // Return a vector containing the auxilary string
    }                                                                     // Correct output is in aux at leaves of the tree

    string last(1, s[s.size() - 1]);                                      // The last char as a string before popping it
    string lastUpper(1, s[s.size() - 1] + ('A' - 'a'));                   // The last char as an uppercase string
    s.pop_back();                                                         // Removing last char from input to reduce size
    vector<string> auxVec1 = caseChangePermutations(s, last + aux);       // Left subtree: perm(ab, c) --> perm(a, bc)
    vector<string> auxVec2 = caseChangePermutations(s, lastUpper + aux);  // Right subtree: perm(ab, C) --> perm(a, bC)
    auxVec1.insert(auxVec1.end(), auxVec2.begin(), auxVec2.end());        // Appending right output to left-side output
    sort(auxVec1.begin(), auxVec1.end(), greater<string>());              // Sorting the output in descending order
    return auxVec1;
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
        int size;
        cin >> size;
        string s;
        cin >> s;

        vector<string> result = caseChangePermutations(s);
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
// abc
// 2
// pq
// 1
// r
// 4
// aaaa
// 4
// abab
// 4
// aabb
// 4
// abba

// Outputs:

// abc
// abC
// aBc
// aBC
// Abc
// AbC
// ABc
// ABC
// ..............
// pq
// pQ
// Pq
// PQ
// ..............
// r
// R
// ..............
// aaaa
// aaaA
// aaAa
// aaAA
// aAaa
// aAaA
// aAAa
// aAAA
// Aaaa
// AaaA
// AaAa
// AaAA
// AAaa
// AAaA
// AAAa
// AAAA
// ..............
// abab
// abaB
// abAb
// abAB
// aBab
// aBaB
// aBAb
// aBAB
// Abab
// AbaB
// AbAb
// AbAB
// ABab
// ABaB
// ABAb
// ABAB
// ..............
// aabb
// aabB
// aaBb
// aaBB
// aAbb
// aAbB
// aABb
// aABB
// Aabb
// AabB
// AaBb
// AaBB
// AAbb
// AAbB
// AABb
// AABB
// ..............
// abba
// abbA
// abBa
// abBA
// aBba
// aBbA
// aBBa
// aBBA
// Abba
// AbbA
// AbBa
// AbBA
// ABba
// ABbA
// ABBa
// ABBA
// ..............
