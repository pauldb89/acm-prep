#include <algorithm>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

int a1, a2, a3, a4;

void Print(int times, string msg) {
  for (int i = 0; i < times; ++i) {
    printf("%s", msg.c_str());
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  scanf("%d %d %d %d", &a1, &a2, &a3, &a4);

  if (abs(a4-a3) >= 2) {
    printf("-1\n");
    return 0;
  }

  if (min(a1, a2) < max(a3, a4)) {
    printf("-1\n");
    return 0;
  }

  if (a3 == a4+1) {
    // 4.....47474747...777
    Print(a1-a3, "4");
    Print(a3, "47");
    Print(a2-a3, "7");
    printf("\n");
  } else if (a4 == a3+1) {
    // 77...747474...4
    // 74.....47
    if (a4 == 1) {
      Print(a2, "7");
      Print(a1, "4");
      printf("\n");
    } else {
      Print(1, "74");
      Print(a1-a4, "4");
      Print(a4-2, "74");
      Print(a2-a4, "7");
      Print(1, "74");
      printf("\n");
    }
  } else {
    // a3 == a4
    if (a1 > a3) {
      Print(a1-a3-1, "4");
      Print(a3, "47");
      Print(a2-a3, "7");
      Print(1, "4");
      printf("\n");
    } else if (a2 > a4) {
        Print(a4, "74");
        Print(a2-a4, "7");
        printf("\n");
    } else {
      printf("-1\n");
    }
  }

  return 0;
}
