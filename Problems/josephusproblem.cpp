#include <bits/stdc++.h>
using namespace std;

int josephusRecurrence(int n, int K) {                   // O(n) implementation using a recurrence relation
    if (n == 1) {                                        // Necessary base case: This case will need explicit termination
        return 1;                                        // When n == 1, only 1 man is standing and hence is the survivor
    }                                                    // This also forms the end condition for the recurrence relation
    if (K == 1) {                                        // Extra base case: This is not really required
        return n;                                        // Basically, for K = 1, every man except the last man dies
    }                                                    // f(n,K) = (f(n-1, K) + K) % n (0-index) ie. circular sum of K and f(n-1,K)
    return 1 + ((K - 1) + josephusRecurrence(n - 1, K)) % n;
}

int josephus_Helper(int n, int K, vector<int>& v, int delPos) {
    if (n == 1) {                                        // Base case: When only one soldier is left standing
        return v[0];                                     // Return the value of vector (ie. original position)
    }                                                    // v[start] is valid too, but not start + 1 (iterator gets invalidated)
    delPos = (delPos + K) % n;                           // New delPos is K steps ahead of the previous pos, mod N (for circular)
    v.erase(v.begin() + delPos);                         // Delete the soldier at delPos, reducing size of array by 1
    // int newStart = (delPos + (n - 1)) % (n - 1);      // No need to calculate this, the next recursive call handles it above
    int result = josephus_Helper(n - 1, K, v, delPos);   // Next recursive call on reduced vector (by ref) with N - 1
    return result;                                       // Return the result to the solver function once calculated
}

int josephusRecursive(int n, int K) {                    // Solver function, using a recursive helper to calculate
    int startPos = 0;                                    // Give 0 and let the helper figure out the deletion position
    vector<int> v;                                       // Arrays have O(n) deletion, can use a better ADT (Maps?)
    for (int i = startPos; i < n; i++) {                 // Array of soldiers get constructed from start to n
        v.push_back(i + 1);                              // i + 1 as arrays are 0-index but input is 1-index
    }                                                    // Assigning v[i] = i+1 in a vector leads to a dirty segfault
    K--;                                                 // For K = 3, 2 soldiers get skipped and third one is killed
    int result = josephus_Helper(n, K, v, startPos);     // The helper carries out the recursive deletion (murder?)
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
        int n, k;
        cin >> n >> k;

        int result1 = josephusRecurrence(n, k);
        int result2 = josephusRecursive(n, k);
        cout << result1 << ", " << result2 << endl;
    }

    return 0;
}

// Test cases:

// Inputs:

// 5
// 1 2
// 3 1
// 4 3
// 3 2
// 5 7

// Outputs: Approach 1, Approach 2

// 1, 1
// 3, 3
// 1, 1
// 3, 3
// 4, 4
