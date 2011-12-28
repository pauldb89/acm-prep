#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

const long long MAX_N = 1000000000000000000LL;
const int MAX_TERM = 100;

long long n;
int all_terms, terms;
long long fib[MAX_TERM];
int indexes[MAX_TERM];
long long dp[MAX_TERM][2];

int main() {
#ifndef ONLINE_JUDGE
  ifstream cin("d.in");
#endif

  fib[1] = 1;
  fib[2] = 2;
  all_terms = 2;
  while (fib[all_terms-1]+fib[all_terms] <= MAX_N) {
    ++all_terms;
    fib[all_terms] = fib[all_terms-1]+fib[all_terms-2];
  }

  int tests;
  cin >> tests;
  for (int t = 1; t <= tests; ++t) {
    cin >> n;
    terms = 0;
    for (int i = all_terms; i > 0; --i) {
      if (fib[i] <= n) {
        n -= fib[i];
        indexes[++terms] = i;
      }
    }

    reverse(indexes+1, indexes+terms+1);
    dp[0][1] = 1;
    dp[0][0] = 0;
    for (int i = 1; i <= terms; ++i) {
      int diff = indexes[i] - indexes[i-1] - 1;
      dp[i][1] = dp[i-1][0]+dp[i-1][1];
      dp[i][0] = (diff/2)*(dp[i-1][0]+dp[i-1][1]);
      if (diff%2 == 1) {
        dp[i][0] += dp[i-1][0];
      }
    }

    cout << dp[terms][0]+dp[terms][1] << '\n';
  }

  return 0;
}
