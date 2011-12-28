#include <cstdio>
#include <cstring>

const int MOD = 1000000007;
const int MAX_N = 1010;

int dp[MAX_N][MAX_N];
int sum_dp[MAX_N][MAX_N];

int Solve(int steps, int n) {
  memset(dp, 0, sizeof(dp));
  memset(sum_dp, 0, sizeof(sum_dp));
  dp[0][n] = 1;
  for (int i = n; i >= 1; --i) {
    sum_dp[0][i] = 1;
  }

  for (int i = 1; i <= steps; ++i) {
    for (int j = n; j >= 1; --j) {
      dp[i][j] = dp[i][j+1] + sum_dp[i-1][j+2];
      if (dp[i][j] >= MOD) {
        dp[i][j] -= MOD;
      }
      sum_dp[i][j] = sum_dp[i][j+1]+dp[i][j];
      if (sum_dp[i][j] >= MOD) {
        sum_dp[i][j] -= MOD;
      }
    }
  }

  return sum_dp[steps][1];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("c.in", "r", stdin);
#endif
  int n, m, steps;
  scanf("%d %d %d", &n, &m, &steps);

  int term1 = Solve(steps, n);
  int term2 = Solve(steps, m);
  int sol = ((long long) term1*term2) % MOD;
  printf("%d\n", sol);

  return 0;
}
