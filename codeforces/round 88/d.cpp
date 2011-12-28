#include <fstream>
#include <iostream>
#include <cassert>

using namespace std;

long long n;
int num_queries, mod;

pair <int, long long> Query(long long n, long long x, long long upper) {
  if (x == 0 || upper == 0) {
    return make_pair(0, 0);
  }
  if (n == 1) {
    return make_pair(1, 1);
  }

  long long middle = (n+1)/2;
  if (x < middle) {
    pair <int, long long> res = Query(middle, x, (upper+1)/2);
    int sum = (2*res.first-res.second) % mod;
    if (sum < 0) {
      sum += mod;
    }
    return make_pair(sum, res.second);
  } else {
    pair <int, long long> res = Query(n-middle, x-middle, upper/2);
    int alpha = ((min(n, upper)+1)/2) % mod;
    int sum = ((long long) alpha*alpha + 2*res.first) % mod;
    return make_pair(sum, alpha+res.second);
  }
}

int main() {
#ifndef ONLINE_JUDGE
  ifstream cin("d.in");
#endif

  cin >> n >> num_queries >> mod;

  for (int i = 1; i <= num_queries; ++i) {
    long long x, y, lower, upper;
    cin >> x >> y >> lower >> upper;
    int result = (Query(n, y, upper).first-Query(n, x-1, upper).first-
                  Query(n, y, lower-1).first+Query(n, x-1, lower-1).first) % mod;
    if (result < 0) {
      result += mod;
    }
    cout << result << '\n';
  }

  return 0;
}
