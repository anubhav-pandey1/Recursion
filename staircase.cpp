#include <math.h>
#include <vector>
#include <deque>
#include <numeric>
#include <iostream>
using namespace std;

vector<vector<long>> dp(50, vector<long> (15, -1));

long count_ways(long n, long k) { // My solutions works, yay
  if (k == 1) {
    dp[n - 1][k - 1] = 1;
    return k;
  }
  else if (n <= k) {
    dp[n - 1][k - 1] = (1 << (n - 1));
    return dp[n - 1][k - 1];
  }
  else if (dp[n - 1][k - 1] != -1) {
    return dp[n - 1][k - 1];
  }
  else {
    long sum = 0;
    for (long i = 0; i < k; ++i) {
      sum += count_ways(n - i - 1, k);
    }
    dp[n - 1][k - 1] = sum;
    return sum;
  }
}


long counter_ways(long n, long k) { // Sliding window
  if (k == 1)
    return k;
  else if (n <= k)
    return (1LL << (n - 1));
  else {
    deque<long> dq;
    for (long i = 0; i < k; i++)
      dq.push_back((1LL << i));

    for (long j = k; j < n; j++) {
      dq.push_back(accumulate(dq.begin(), dq.end(), 0L));
      dq.pop_front();
    }
    return dq.back();
  }
}

int main() {
  long count = 0;
  for (int n = 1; n < 51; n++) {
    for (int k = 1; k < 16; k++) {
      if (counter_ways(n, k) != count_ways(n, k)) {
        cout << n << ", " << k << endl;
        count++;
      }
    }
  }

  cout << "Total count: " << count << endl;
  return 0;
}
