#include <bits/stdc++.h>
using namespace std;

void insertStack(stack<int>& s, int n) {
    if (s.empty() || n >= s.top()) {       // Order of these conditions matters, this is correct
        s.push(n);
        return;
    }

    int top = s.top();
    s.pop();
    insertStack(s, n);
    s.push(top);
}

void sortStack(stack<int>& s) {
    if (s.empty()) {
        return;
    }

    int top = s.top();
    s.pop();
    sortStack(s);
    insertStack(s, top);
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

        sortStack(st);
        for (int i = 0; i < size; i++) {
            cout << st.top() << " ";
            st.pop();
        }
        cout << endl;

    }

    return 0;
}

// Test cases:

// Input:

// 1
// 4
// 5 1 0 2

// Output:

// 5 2 1 0
