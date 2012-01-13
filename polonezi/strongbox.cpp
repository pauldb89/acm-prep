#include <cstdio>
#include <map>

using namespace std;

const int MAX_M = 250010;
const int MAX_P = 20;

int m, p;
long long n;
long long values[MAX_M];
map<long long, int> divisors;
long long prime_divisors[MAX_P];

long long GCD(long long a, long long b) {
  while (b) {
    long long r = a % b;
    a = b;
    b = r;
  }
  return a;
}

void FindDivisors(long long x) {
  long long tmp = x;
  for (long long i = 1; i*i <= x; ++i) {
    if (x % i == 0) {
      divisors[i] = 0;
      divisors[x/i] = 0;
      if (i > 1 && tmp % i == 0) {
        prime_divisors[p++] = i;
        while (tmp % i == 0) {
          tmp /= i;
        }
      }
    }
  }
  if (tmp > 1) {
    prime_divisors[p++] = tmp;
  }
}

int main() {
//  freopen("strongbox.in", "r", stdin);

  scanf("%lld %d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%lld", &values[i]);
  }

  values[m] = GCD(n, values[m]);
  FindDivisors(values[m]);

  for (int i = 1; i < m; ++i) {
    divisors[GCD(values[i], values[m])] = 1;
  }

  map<long long, int> :: iterator it = divisors.end();
  do {
    --it;
    if (it->second == 1) {
      for (int i = 0; i < p; ++i) {
        if (it->first % prime_divisors[i] == 0) {
          divisors[it->first / prime_divisors[i]] = 1;
        }
      }
    }
  } while (it != divisors.begin());

  for (it = divisors.begin(); it != divisors.end(); ++it) {
    if (it->second == 0) {
      printf("%lld\n", n / it->first);
      break;
    }
  }

  return 0;
}
