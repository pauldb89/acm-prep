#include <cstdio>

using namespace std;

const int MAX_N = 100010;

int n, turns;
char num[MAX_N];

int main() {
//  freopen("b.in", "r", stdin);

  scanf("%d %d ", &n, &turns);
  fgets(num+1, MAX_N-1, stdin);

  int i = 1;
  while (turns > 0 && i < n) {
    while (i < n && (num[i] != '4' || num[i+1] != '7')) {
      ++i;
    }

    // at least one pair left
    if (i < n) {
      if (i % 2 == 1) {
        if (i+2 > n || num[i+2] != '7') {
          num[i] = num[i+1] = '4';
          --turns;
        } else {
          if (turns % 2 == 1) {
            num[i] = num[i+1] = '4';
          }
          break;
        }
      } else {
        if (i == 1 || num[i-1] != '4') {
          num[i] = num[i+1] = '7';
          --turns;
        } else {
          if (turns % 2 == 1) {
            num[i] = num[i+1] = '7';
          }
          break;
        }
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    printf("%c", num[i]);
  }
  printf("\n");

  return 0;
}
