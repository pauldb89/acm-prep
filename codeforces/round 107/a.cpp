#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

long long n;
vector<long long> prime_factors;

int main() {
#ifndef ONLINE_JUDGE
  ifstream cin("a.in");
#endif

  cin >> n;

  for (long long i = 2; i*i <= n; ++i) {
    while (n % i == 0) {
      prime_factors.push_back(i);
      n /= i;
    }
  }
  if (n > 1) {
    prime_factors.push_back(n);
  }

  if (prime_factors.size() <= 1) {
    cout << 1 << endl;
    cout << 0 << endl;
  } else if (prime_factors.size() == 2) {
    cout << 2 << endl;
  } else {
    cout << 1 << endl;
    cout << prime_factors[0] * prime_factors[1] << endl;
  }

  return 0;
}
