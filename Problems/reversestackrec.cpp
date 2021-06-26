#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

int deleteBottom(stack<int>& s, int K = -1) {  // Delete bottom based implementation instead of insert-bottom
    int sz = s.size();
    if (K == -1) {                             // Default-value checker for implementing optional parameters
        K = sz - 1;                            // K is the 0-index of the bottom measured from the top
    }

    if (K == 0) {                              // If bottom has the index = 0, it must be the top and only element
        int bottom = s.top();                  // Store the value of the bottom to return as function value
        s.pop();                               // Pop the top/bottom, ending the stack into an empty stack
        return bottom;                         // Return the bottom value
    }

    int top = s.top();                         // Store the top in a temp variable, remove it to create smaller inputs
    s.pop();                                   // The bottom will remain the same for smaller inputs, K will decrease
    int bottom = deleteBottom(s, K - 1);       // deleteBottom for smaller inputs and keep storing the bottom value
    s.push(top);                               // Once the bottom is deleted and stored, push the top back to recreate
    return bottom;                             // Return the final bottom value as the functional return to end it
}                                              // Bottom must be stored for every call on smaller input to finally return

void reverseStack(stack<int>& s) {             // Delete and store bottom based implementation of reverseStack()
    if (s.empty()) {                           // Base condition: If the stack has no elements left on reducing I/P
        return;                                // Return if the stack is empty
    }

    int bottom = deleteBottom(s);              // Store the bottom-value and delete the bottom to create smaller I/P
    reverseStack(s);                           // Reverse the stack on the smaller I/P without original bottom
    s.push(bottom);                            // Push the original bottom to the top of the reversed stack
}

// -------------------------------------------------------------------------------------------------------------------------------

void insert_Bottom(stack<int>& s, int n) {     // Simpler, insertBottom() based implementation
    if (s.empty()) {                           // Base condition: Just push N if stack is empty
        s.push(n);
        return;                                // Return back to previous call after pushing N
    }

    int top = s.top();                         // If not empty, store the top in a temp variable
    s.pop();                                   // Remove the top to create a smaller I/P stack
    insert_Bottom(s, n);                       // Insert N at the bottom of the smaller I/P stack
    s.push(top);                               // Push the top back to the top after inserting N
}

void reverse_Stack(stack<int>& s) {            // Simpler, insertBottom() based reverseStack()
    if (s.empty()) {                           // Base case: If stack is empty, there is nothing
        return;                                // Simply return to previous/higher function call
    }

    int top = s.top();                         // If not empty, store the top in a temp variable
    s.pop();                                   // Create a smaller I/P stack by removing the top
    reverse_Stack(s);                          // Reverse the smaller stack
    insert_Bottom(s, top);                     // Insert the previous top to the bottom of new stack
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

        reverse_Stack(st);
        stack<int> temp;
        for (int i = 0; i < size; i++) {
            temp.push(st.top());
            st.pop();
        }

        for (int i = 0; i < size; i++) {
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

// 5
// 1 5
// 0 1 5
// 2 0 1 5
// 3 2 0 1 5
