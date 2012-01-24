#include <cstdio>
#include <map>

using namespace std;

const int MAX_N = 100010;
const int MOD = 1000000007;

int n, m, non_lucky;
int a[MAX_N];
map<int, int> cnt;
int dp[MAX_N];

int IsLucky(int x) {
  while (x > 0) {
    int digit = x % 10;
    if (digit != 4 && digit != 7) {
      return 0;
    }
    x /= 10;
  }
  return 1;
}

int Inverse(int a, int b) {
  int prev_x = 1, prev_y = 0;
  int x = 0, y = 1;
  while (b != 1) {
    int q = a / b;
    int tmp_x = (prev_x - (long long) q*x) % MOD;
    int tmp_y = (prev_y - (long long) q*y) % MOD;
    prev_x = x;
    prev_y = y;
    x = tmp_x;
    y = tmp_y;
    int rest = a % b;
    a = b;
    b = rest;
  }

  if (y < 0) {
    y += MOD;
  }

  return y;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("c.in", "r", stdin);
#endif

  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    if (IsLucky(a[i])) {
      ++cnt[a[i]];
    } else {
      ++non_lucky;
    }
  }
  
  dp[0] = 1;
  for (map<int, int> :: iterator it = cnt.begin(); it != cnt.end(); ++it) {
    for (int i = m; i >= 1; --i) {
      dp[i] = (dp[i] + (long long) dp[i-1] * (it->second)) % MOD; 
    }
  }

  int cmb = 1;
  int solution = 0;
  for (int i = m; i >= 0 && m-i <= non_lucky; --i) {
    int k = m-i;
    solution = (solution + (long long) dp[i]*cmb) % MOD;
    cmb = ((long long) cmb*(non_lucky-k)) % MOD;
    cmb = ((long long) cmb*Inverse(MOD, k+1)) % MOD;
  }
  printf("%d\n", solution);

  return 0;
}
