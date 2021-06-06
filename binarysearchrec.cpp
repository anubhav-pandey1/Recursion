#include <iostream>
#include <vector>
using namespace std;

bool binarySearchRec(vector<int>& v, int n, int start, int end) {
    if (start > end) {                               // Base case 1: When start goes up higher than end, or end goes down lower than start
        return false;                                // Return false if base case 1 is hit ie. none of the nodes of the recursion tree find n
    }                                                // We can also return -1 or index of the found element instead of a boolean

    int mid = start + (end - start)/2;               // If base case 1 is not hit, find mid to kick start binary search
    if (v[mid] == n) {                               // Base case 2: If mid element is equal to n, then this is base case 2
        return true;                                 // Return true if base case 2 is hit ie. this is the main searching step
    }
    else if (n < v[mid]) {                           // Else if n is less than the middle element, then conduct new binary search
        return binarySearchRec(v, n, start, end-1);  // New binary search in the range start -> )end - 1)
    }
    else if (n > v[mid]) {                           // Otherwise if n is greater than the middle element, conduct new binary search
        return binarySearchRec(v, n, mid+1, end);    // New binary search in the range (mid + 1) -> start
    }
    return false;                                    // If nothing returns anything, return false to avoid -Wreturn type warning as..
}                                                    // if nothing returns anything, n has not been found in the vector

int main() {
    vector<int> v = {4, 9, 17, 21, 25, 29, 32, 35};

    bool result = binarySearchRec(v, 10, 0, 7);     // Test case 1 - for recursive binary search
    cout << ((result) ? "true" : "false") << endl;

    return 0;
}
