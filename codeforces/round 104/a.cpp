#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_N = 100010;

int n;
char str1[MAX_N], str2[MAX_N];

int main() {
#ifndef ONLINE_JUDGE
  freopen("a.in", "r", stdin);
#endif

  fgets(str1, MAX_N, stdin);
  fgets(str2, MAX_N, stdin);

  n = strlen(str1) - 1;

  int x = 0, y = 0;
  for (int i = 0; i < n; ++i) {
    if (str1[i] < str2[i]) {
      ++x;
    }
    if (str1[i] > str2[i]) {
      ++y;
    }
  }

  printf("%d\n", max(x, y));

  return 0;
}
