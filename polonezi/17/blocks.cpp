#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_N = 1000010;

int n;
int a[MAX_N];
long long sum[MAX_N], min_sum[MAX_N];

int Solve(int k) {
  int result = 0;
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i-1] + a[i] - k;
    min_sum[i] = min(min_sum[i-1], sum[i]);
  }

  long long max_sum = sum[n]-1;
  for (int i = n, j = n; i > 0; --i) {
    if (sum[i] > max_sum) {
      while (j >= 0 && min_sum[j] <= sum[i]) {
        --j;
      }
    }
    max_sum = max(max_sum, sum[i]);
    result = max(result, i-j-1);
  }

  return result;
}

int main() {
//  freopen("blocks.in", "r", stdin);
  
  int tests;
  scanf("%d %d", &n, &tests);

  for (int i = 1; i <= n; ++i) {
    scanf("%d ", &a[i]);
  }

  for (int t = 1; t <= tests; ++t) {
    int k;
    scanf("%d ", &k);
    printf("%d ", Solve(k));
  }
  printf("\n");

  return 0;
}
