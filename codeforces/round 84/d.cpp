#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 100010;

int n;
int a[MAX_N], pos[MAX_N];
vector<pair<int, int> > sol;

int IsLuckyNumber(int x) {
  while (x) {
    int digit = x % 10;
    if (digit != 4 && digit != 7) {
      return 0;
    }
    x /= 10;
  }
  return 1;
}

int cmp(int i, int j) {
  return a[i] < a[j];
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("d.in", "r", stdin);
#endif

  scanf("%d", &n);
  int lucky_pos = 0, sorted = 1;
  for (int i = 1; i <= n; ++i) {
    scanf("%d ", &a[i]);
    if (IsLuckyNumber(a[i])) {
      lucky_pos = i;
    }
    pos[i] = i;
    sorted &= a[i-1] <= a[i];
  }

  if (sorted) {
    printf("0\n");
    return 0;
  }
  if (lucky_pos == 0) {
    printf("-1\n");
    return 0;
  }

  sort(pos+1, pos+n+1, cmp);

  for (int i = 1; i <= n; ++i) {
    a[pos[i]] = i;
  }
  int last = a[lucky_pos];

  for (int i = 1; i < last; ++i) {
    if (a[i] != i) {
      if (i != lucky_pos) {
        sol.push_back(make_pair(i, lucky_pos));
      }
      if (i != pos[i]) {
        sol.push_back(make_pair(i, pos[i]));
      }
      pos[a[i]] = lucky_pos;
      a[lucky_pos] = a[i];
      lucky_pos = pos[i];
    }
  }

  for (int i = n; i > last; --i) {
    if (a[i] != i) {
      if (i != lucky_pos) {
        sol.push_back(make_pair(i, lucky_pos));
      }
      if (i != pos[i]) {
        sol.push_back(make_pair(i, pos[i]));
      }
      pos[a[i]] = lucky_pos;
      a[lucky_pos] = a[i];
      lucky_pos = pos[i];
    }
  }

  printf("%d\n", sol.size());
  for (size_t i = 0; i < sol.size(); ++i) {
    printf("%d %d\n", sol[i].first, sol[i].second);
  }

  return 0;
}
