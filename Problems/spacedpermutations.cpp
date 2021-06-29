#include <bits/stdc++.h>
using namespace std;

vector<string> spacedPermutations(string s, string aux = "") {          // Using auxilary string
    if (s.size() == 1) {                                                // Base condition: If only one char in string
        return {s + aux};                                               // Vector containing concatenated s + aux
    }                                                                   // Returns first char (like 'A') + aux in the end

    string last(1, s[s.size() - 1]);                                    // Converting last char to a string of size 1
    s.pop_back();                                                       // Popping last char for next recursive calls
    vector<string> auxVec1 = spacedPermutations(s, last + aux);         // Left subtree - without adding __ to aux
    vector<string> auxVec2 = spacedPermutations(s, "_" + last + aux);   // Right subtree - adding __ right before aux
    auxVec1.insert(auxVec1.end(), auxVec2.begin(), auxVec2.end());      // Insert vector 2 to the end of vector 1
    return auxVec1;                                                     // Return vector 1
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

        vector<string> result = spacedPermutations(s);
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
// ABC
// 2
// PQ
// 1
// R
// 4
// AAAA
// 4
// ABAB
// 4
// AABB
// 4
// ABBA

// Outputs:

// ABC
// A_BC
// AB_C
// A_B_C
// ..............
// PQ
// P_Q
// ..............
// R
// ..............
// AAAA
// A_AAA
// AA_AA
// A_A_AA
// AAA_A
// A_AA_A
// AA_A_A
// A_A_A_A
// ..............
// ABAB
// A_BAB
// AB_AB
// A_B_AB
// ABA_B
// A_BA_B
// AB_A_B
// A_B_A_B
// ..............
// AABB
// A_ABB
// AA_BB
// A_A_BB
// AAB_B
// A_AB_B
// AA_B_B
// A_A_B_B
// ..............
// ABBA
// A_BBA
// AB_BA
// A_B_BA
// ABB_A
// A_BB_A
// AB_B_A
// A_B_B_A
// ..............
