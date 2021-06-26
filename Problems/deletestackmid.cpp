#include <bits/stdc++.h>
using namespace std;

void deleteStackMid(stack<int>& s, int n = -1) { // Index 0 is the bottom of the stack, sz - 1 is top of the stack
    int sz = s.size();                           // Mid is (sz/2 + 1)th element so its index = sz / 2
    if (n == -1) {                               // If n has no value passed, it will be -1 so we can update it
        n = (sz / 2);                            // Update n since it represents the index of the original mid
    }                                            // Index of original mid will remain n even on popping the top

    if (sz == n + 1) {                           // Base condition (BC): If the original mid is at the top
        s.pop();                                 // since we are passing mid as a parameter in recursive calls
        return;                                  // Pop the top element (original mid) and return
    }

    int top = s.top();                           // Store the top if the original mid is not at the top (BC not hit)
    s.pop();                                     // Remove the top element to create a smaller stack for recursion
    deleteStackMid(s, n);                        // Remove the nth element from the new stack (it is actual mid)
    s.push(top);                                 // Now add the top back to the stack afte removing from smaller stack
}

void delete_Mid(stack<int>& s, int K = -1) {     // Index 0 is at the top of the stack, sz - 1 is the top
    int sz = s.size();
    if (K == -1) {                               // Default value catcher - enables optional parameters
        K = (sz - 1) / 2;                        // In an 1-indexed system, K = sz/2 + 1 from top
    }                                            // In a 0-indexed system, K = (sz - 1)/2 from top

    if (K == 0) {                                // Base condition: If the mid is at the top (K = 0)
        s.pop();                                 // Pop the top element and return
        return;
    }                                            // Otherwise if mid is not at the top (K != 0)

    int top = s.top();                           // Store and pop the top to create a smaller stack
    s.pop();                                     // Original mid is now at index K - 1 in smaller stack
    delete_Mid(s, K - 1);                        // Delete the (K - 1)th element in the smaller stack
    s.push(top);                                 // Push the top back again to recreate the stack
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
        stack<int> st;
        for (int i = 0; i < size; i++) {
            int ele;
            cin >> ele;
            st.push(ele);
        }

        delete_Mid(st);
        stack<int> temp;
        for (int i = 0; i < size - 1; i++) {
            temp.push(st.top());
            st.pop();
        }

        for (int i = 0; i < size - 1; i++) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;

    }

    return 0;
}

// Test cases:

// Input:

// 5
// 1
// 5
// 2
// 5 1
// 3
// 5 1 0
// 4
// 5 1 0 2
// 5
// 5 1 0 2 3

// Output:

//
// 5
// 5 0
// 5 1 2
// 5 1 2 3
