#include <math.h>
#include <vector>
#include <iostream>
using namespace std;


long long hanoi(int n) {
  return (1LL << n) - 1LL;
}

long long ohanoi(int n, int start, int end) { // This can be used to print moves as well using the helper function
                                              //pm(int start, int end) := print(int start, "->", int end)
  if (n == 1) {
    //pm(start, end);
    return 1;
  }
  else {
    int other = 6 - (start + end);
    //ohanoi(n-1, start, other); // Moves to take n-1 disks from the start to the midpoint/other point
    //pm(start, end); // Move to take the largest disk left from start to the end
    //ohanoi(n-1, other, end); // Moves to take the n-1 disk from the midpoint/other point to the end
    return ohanoi(n-1, start, other) + 1 + ohanoi(n-1, other, start);
  }
}

void towerOfHanoi (int n, char start, char dest, char helper) {
    if (n == 1) {
        cout << start << " -> " << dest << " using " << helper << endl;
    }
    towerOfHanoi(n-1, start, helper, dest);
    cout << start << " -> " << dest << " using " << helper << endl;
    towerOfHanoi(n-1, helper, dest, start);
}

int main() {
  long count = 0;
  for (int n = 1; n < 10; n++) {
      if (hanoi(n) != ohanoi(n, 3, 1)) {
        cout << n << endl;
        count++;
      }
  }

  cout << "Total count: " << count << endl;
    return 0;
}
