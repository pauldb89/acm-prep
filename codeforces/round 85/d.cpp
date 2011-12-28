#include <cstdio>
#include <cassert>
#include <map>

using namespace std;

const int MOD = 1000000007;
const int MAX_N = 1010;

int n, m, k, sol;
int cmb[MAX_N][MAX_N];
map<pair<int, int>, int> cmb_map, dp;

void CalculateCmb() {
  for (int i = 0; i < MAX_N; ++i) {
    cmb[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      cmb[i][j] = cmb[i-1][j-1] + cmb[i-1][j];
      if (cmb[i][j] >= MOD) {
        cmb[i][j] -= MOD;
      }
    }
  }
}

void ExtendedGCD(int x, int y, int& a, int& b) {
  int prev_a = 1, prev_b = 0;
  a = 0, b = 1;
  while (y > 1) {
    int r = x%y;
    int q = x/y;
    x = y;
    y = r;
    int next_a = prev_a - q*a;
    int next_b = prev_b - q*b;
    prev_a = a;
    prev_b = b;
    a = next_a;
    b = next_b;
  }
}

int ModularInverse(int x) {
  int a, b;
  ExtendedGCD(x, MOD, a, b);
  if (a < 0) {
    a += MOD;
  }
  assert((((long long) a*x + (long long) b*MOD) % MOD + MOD) % MOD == 1);
  return a;
}

long long GetBruteForceCmb(int n, int k) {
  long long result = 1;
  for (int i = n-k+1; i <= n; ++i) {
    result = (result*i) % MOD;
  }
  for (int i = 1; i <= k; ++i) {
    result = (result*ModularInverse(i)) % MOD;
  }
  return result;
}

long long GetCmb(int n, int k) {
  if (n < MAX_N && k < MAX_N) {
    return cmb[n][k];
  }
  pair<int, int> p = make_pair(n, k);
  if (cmb_map.find(p) != cmb_map.end()) {
    return cmb_map[p];
  }
  if (cmb_map.find(make_pair(n, k-1)) != cmb_map.end()) {
    long long tmp = cmb_map[make_pair(n, k-1)];
    tmp = (tmp*(n-k+1)) % MOD;
    cmb_map[p] = (tmp*ModularInverse(k)) % MOD;
  }
  if (cmb_map.find(make_pair(n+1, k)) != cmb_map.end()) {
    long long tmp = cmb_map[make_pair(n+1, k)];
    tmp = (tmp*(n+1-k)) % MOD;
    cmb_map[p] = (tmp*ModularInverse(n+1)) % MOD;
    return cmb_map[p];
  }
  cmb_map[p] = GetBruteForceCmb(n, k);
  return cmb_map[p];
}

long long RaiseToPower(long long a, long long b) {
  long long result = 1;
  while (b) {
    if (b&1) {
      result = (result*a) % MOD;
    }
    a = (a*a) % MOD;
    b >>= 1;
  }
  return result;
}

long long GetDp(int n, int k) {
  if (k == 1) {
    return 1;
  }
  pair<int, int> p = make_pair(n, k);
  if (dp.find(p) != dp.end()) {
    return dp[p];
  }

  long long tmp = RaiseToPower(k, n);
  for (int i = 1; i < k; ++i) {
    tmp = (tmp-GetCmb(k, i)*GetDp(n, i)) % MOD;
  }
  if (tmp < 0) {
    tmp += MOD;
  }
  dp[p] = tmp;
  return dp[p];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("d.in", "r", stdin);
#endif

  scanf("%d %d %d", &n, &m, &k);

  CalculateCmb();

  if (m == 1) {
    for (int i = 1; i <= min(n, k); ++i) {
      sol = (sol + GetCmb(k, i)*GetDp(n, i)) % MOD;
    }
  } else if (m == 2) {
    for (int i = 1; i <= min(n, k); ++i) {
      long long term = (GetCmb(k, i)*GetDp(n, i)) % MOD;
      sol = (sol + term*term) % MOD;
    }
  } else {
    for (int i = 1; i <= min(n, k); ++i) {
      for (int j = 0; i+j <= min(n, k); ++j) {
        long long factor1 = (GetCmb(k-i, j) * GetDp(n, i+j)) % MOD;
        factor1 = (factor1*factor1) % MOD;
        long long factor2 = (GetCmb(k, i) * GetDp((m-2)*n, i)) % MOD;
        sol = (sol + factor1*factor2) % MOD;
      }
    }
  }

  printf("%d\n", sol);

  return 0;
}
