#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_N = 100010;
const int MAX_P = 1010;

int n, m, solution;
char text[MAX_N];
char pattern[MAX_P];
int prefix[MAX_P];
int best_match[2][MAX_N];

void CalcPrefix() {
  int p = 0;
  for (int i = 2; i <= m; ++i) {
    while (p > 0 && pattern[p+1] != pattern[i]) {
      p = prefix[p];
    }
    if (pattern[p+1] == pattern[i]) {
      ++p;
    }
    prefix[i] = p;
  }
}

void KMP(int best_match[]) {
  int p = 0;
  for (int i = 1; i <= n; ++i) {
    while (p > 0 && (p == m || pattern[p+1] != text[i])) {
      p = prefix[p];
    }
    if (pattern[p+1] == text[i]) {
      ++p;
    }
    best_match[i] = p;
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("e.in", "r", stdin);
#endif

  scanf("%s ", text+1);
  n = strlen(text+1);

  int tests;
  scanf("%d ", &tests);
  for (int t = 1; t <= tests; ++t) {
    scanf("%s", pattern+1);
    m = strlen(pattern+1);

    if (m == 1) {
      continue;
    }

    CalcPrefix();
    KMP(best_match[0]);
    reverse(pattern+1, pattern+m+1);
    reverse(text+1, text+n+1);

    CalcPrefix();
    KMP(best_match[1]);
    reverse(text+1, text+n+1);

    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j < 2; ++j) {
        best_match[j][i] = max(best_match[j][i], best_match[j][i-1]);
      }
    }

    for (int i = 1; i < n; ++i) {
      if (best_match[0][i] + best_match[1][n-i] >= m) {
        ++solution;
        break;
      }
    }
  }

  printf("%d\n", solution);

  return 0;
}
