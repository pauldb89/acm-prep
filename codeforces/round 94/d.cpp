#include <algorithm>
#include <cstdio>
#include <map>

using namespace std;

const int INF = 1000000000;

int n;
map<int, int> cnt;

int main() {
#ifndef ONLINE_JUDGE
  freopen("d.in", "r", stdin);
#endif

  int lower = INF, upper = 0;
  scanf("%d", &n);
  if (n%2 != 0) {
    printf("NO\n");
    return 0;
  }
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    lower = min(lower, x);
    upper = max(upper, x);
    ++cnt[x];
  }

  int spots = 0;
  for (int i = lower; i <= upper; ++i) {
    if (cnt.find(i) == cnt.end()) {
      printf("NO\n");
      return 0;
    }
    if (cnt[i] > spots || (i == upper && cnt[i]==spots)) {
      spots = cnt[i]-spots;
    } else {
      printf("NO\n");
      return 0;
    }
  }

  if (spots == 0) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

  return 0;
}
