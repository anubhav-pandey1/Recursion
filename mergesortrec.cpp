#include <iostream>
#include <vector>
using namespace std;

vector<int> merge(vector<int>& v1, vector<int>& v2){// Merges two sorted array and returns the merged array
    int l1 = v1.size(), l2 = v2.size();             // Vector class destructor destroys it after it goes out of scope
    vector<int> r((l1 + l2), -1);                   // Merge v1 and v2 into array R of size l1 + l2
    int i = 0, j = 0, k = 0;                        // i keeps track of elements in v1, j for v2 and k for merged array R

    while (i < l1 && j < l2) {                      // Can't use || here as it will remain true even if one evaluates to false
        if (v1[i] >= v2[j]) {                       // This operation is either O(l1) or O(l2).
            r[k] = v2[j];                           // The corresponding while loop below would be O(l2) or O(l1) respectively
            j++;                                    // Merge operation = O(l1 + l2) = O(N) for the merge sort array of size N (N = l1 + l2)
        }
        else {                                      // Add the smaller element of the two arrays to the merged array R
            r[k] = v1[i];                           // Keep adding while one of the arrays does not get exhausted
            i++;                                    // If one of the arrays gets exhausted, move on to using only the other one (while loops below)
        }
        k++;
    }

    while (j < l2) {                                // Can't use i == l1 here as its a while loop where i is not incremented -> infinite loop
        r[k] = v2[j];                               // This is O(l2)
        j++;                                        // Executed when v1 gets exhausted and elements from v2 are left
        k++;                                        // Keep incrementing j and k to move to next elements in v2 and R
    }

    while (i < l1) {                                // This is O(l1)
        r[k] = v1[i];                               // Executed when v2 gets exhausted and elements from v1 are left
        i++;                                        // Keep incrementing i and k to move to next elements in v1 and R
        k++;
    }

    return r;
}

vector<int> mergeSort(vector<int> v) {              // Merge sort uses the merge function as a subroutine and operates in T(n)
    int len = v.size();
    if (len == 1) {                                 // Base case for the recursion - return vector as it is, if size == 1
        return v;
    }
    else {                                          // Otherwise divide main vector into two separate subarrays v1 and v2
        vector<int> v1(len/2);
        vector<int> v2(len - (len/2));              // Len of v2 is whatever is left after giving len/2 space to v1

        for (int i = 0; i < len; i++) {             // Assigning elements to the two subarrays in O(n)
            if (i < len/2)                          // If element falls in first half, assign it to v1 subarray
                v1[i] = v[i];
            else                                    // Otherwise, assign it to the v2 subarray
                v2[i - (len/2)] = v[i];
        }

        vector<int> ar1 = mergeSort(v1);            // Recursively sort first half subarray v1 in time T(n/2)
        vector<int> ar2 = mergeSort(v2);            // Recursively sort second half subarray v2 in time T(n/2)
        vector<int> r = merge(ar1, ar2);            // Merge sorted v1 and v2 in O(n) time = C*n
        return r;                                   // T(n) = 2T(n/2) + C*n => Merge sort is O(N*logN)
    }
}

int main() {
    vector<int> x = {1, 1, 1, 1, 2, 2, 2, 2};
    vector<int> v = {17, 21, 29, 38, 4, 9, 25, 32};

    vector<int> merged = mergeSort(x);

    for (int i = 0; i < merged.size(); i++) {
        cout << merged[i] << " ";
    }
    cout << endl;

    return 0;
}
