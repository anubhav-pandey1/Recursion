#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int wpartition(int n, int k) { // Wrong relation, doesn't hold for (9,4) and (9,5)
    if (n == 1 || k == 1)      // Once again you did not check for larger values of n
        return 1;
    else if (k == 2) {
        return (n / 2) + 1;
    }
    else if (k >= n)
        return wpartition(n, n - 1) + 1;
    else {
        return wpartition(n, k - 1) + (n - k);
    }
}

int partition(int n, int k) {
    if (n == 1 || k == 1 || n == 0)
        return 1;
    else if (k == 0 or n < 0) {
        return 0;
    }
    else {
        return partition(n, k - 1) + partition(n - k, k);
    }
}

int main() {
    long count = 0;
    for (int n = 1; n < 10; n++) {
        for (int k = 1; k < 10; k++) {
            if (wpartition(n, k) != partition(n, k)) {
                cout << n << ", " << k << endl;
                count++;
            }
        }
    }

    cout << "Total count: " << count << endl;

    // cout << partition(9,4) << endl;
    // cout << partition(9,5) << endl;
    return 0;
}
