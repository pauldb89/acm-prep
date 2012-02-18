#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 155;
const int INF = 1000000000;

int n;
int cost[MAX_N];
int dp[MAX_N][MAX_N][MAX_N][2];
int best[MAX_N][MAX_N][2];
char str[MAX_N];

int main() {
#ifndef ONLINE_JUDGE
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &cost[i]);
  }
  scanf("%s", str+1);

  for (int len = 1; len <= n; ++len) {
    for (int i = 1, j = len; j <= n; ++i, ++j) {
      dp[i][j][0][1] = -INF;
      for (int k = 0; k <= n; ++k) {
        dp[i][j][k][0] = dp[i][j][k][1] = -INF;
      }
      if (i == j) {
        dp[i][j][1][1] = 0;
      }

      if (i < j && str[i] == str[j]) {
        for (int k = 2; k <= len; ++k) {
          for (int t = i; t < j-(k-2); ++t) {
            dp[i][j][k][1] = max(dp[i][j][k][1], best[i+1][t][0] + dp[t+1][j-1][k-2][0]);
          }
        }
      }

      for (int k = 1; k <= len; ++k) {
        dp[i][j][k][0] = max(dp[i][j][k][0], dp[i][j][k][1]);
        for (int t = i; t < j; ++t) {
          dp[i][j][k][0] = max(dp[i][j][k][0], dp[i][t][k][1] + best[t+1][j][0]);
        }
      }

      best[i][j][0] = -INF;
      for (int k = 1; k <= len; ++k) {
        if (cost[k] != -1) {
          best[i][j][0] = max(best[i][j][0], dp[i][j][k][1] + cost[k]);
        }
      }
      best[i][j][1] = max(best[i][j][0], 0);
      for (int k = i; k < j; ++k) {
        best[i][j][0] = max(best[i][j][0], best[i][k][0] + best[k+1][j][0]);
        best[i][j][1] = max(best[i][j][1], best[i][k][1] + best[k+1][j][1]);
      }
    }
  }

  /*
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      printf("(%d %d) ", best[i][j][0], best[i][j][1]);
    }
    printf("\n");
  }
  */
  printf("%d\n", best[1][n][1]);

  return 0;
}
