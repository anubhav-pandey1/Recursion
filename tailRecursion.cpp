#include <bits/stdc++.h>
using namespace std;

int gofact(int n, int a) {       // Helper function for factorial
    if (n == 1)                  // Helper functions help in abstracting the factorial function so that it uses only one input -> N
        return a;                // Without helpers, we would have to define factorial as fact(int n, int a) for enabling tail recursion
    else {
        return gofact(n - 1, a * n);
    }
}

int fact(int n) {                // Factorial tail recursion using recursive helper gofact
    return gofact(n, 1);
}

int gofib(int n, int a, int b) { // Helper function for fibonacci
    if (n == 0)                  // Helper functions help in abstracting the fibonnaci function so that it uses only one input -> N
        return a;                // Without helpers, we would have to define fibonnaci as fib(int n, int a, int b) for enabling tail recursion
    else if (n == 1)
        return b;
    else {
        return gofib(n - 1, b, b + a);
    }
}

int fib(int n) {                 // Fibonnaci tail recursion using recursive helper gofib
    return gofib(n, 0, 1);
}

int main() {
    cout << fact(4) << endl;
    cout << fib(4) << endl;
    return 0;
}
