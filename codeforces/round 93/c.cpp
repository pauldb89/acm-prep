#include <cstdio>

const int MAX_N = 2010;

int n, sol;
char a[MAX_N][MAX_N];
int line[MAX_N], line2[MAX_N];
int col[MAX_N], col2[MAX_N];

int main() {
#ifndef ONLINE_JUDGE
  freopen("c.in", "r", stdin);
#endif

  scanf("%d ", &n);

  for (int i = 1; i <= n; ++i) {
    fgets(a[i]+1, MAX_N-1, stdin);
  }

  for (int pas = n; pas > 1; --pas) {
    for (int i = 1; i <= n-pas+1; ++i) {
      int j = pas+i-1;
      int val = a[i][j] == '1';
      if (val ^ line[i] ^ col[j]) {
        col[j] ^= 1;
        line[i] ^= 1;
        ++sol;
      } 

      int val2 = a[j][i] == '1';
      if (val2 ^ line2[j] ^ col2[i]) {
        col2[i] ^= 1;
        line2[j] ^= 1;
        ++sol;
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    int val = a[i][i] == '1';
    if (val^col[i]^col2[i]^line[i]^line2[i]) {
      ++sol;
    }
  }

  printf("%d\n", sol);

  return 0;
}
