#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_N = 1000010;
const int MAX_SUM = 2000010;

int n, m, best, reversed;
int sum_pos[MAX_SUM];
char str[MAX_N];

int Count(int start, int end, int dir) {
  int cnt = 0;
  for (int i = start; i != end; i += dir) {
    if (str[i] == 'T') {
      ++cnt;
    } else {
      return cnt;
    }
  }
  return cnt;
}

int Reverse(int pos) {
  if (!reversed) {
    return pos;
  }
  return n-pos+1;
}

void print(int x, int y) {
  printf("%d %d\n", min(x, y), max(x, y));
}

int main() {
  //  freopen("lollipop.in", "r", stdin);

  scanf("%d %d ", &n, &m);
  fgets(str+1, MAX_N-1, stdin);

  int cnt_left = Count(1, n, 1);
  int cnt_right = Count(n, 1, -1);
  if (cnt_left < cnt_right) {
    best = cnt_left;
    reversed = 1;
  } else {
    best = cnt_right;
  }

  memset(sum_pos, -1, sizeof(sum_pos));
  int sum = 0;
  sum_pos[0] = 0;
  for (int i = 1; i <= n; ++i) {
    int x = Reverse(i);
    sum += (str[x] != 'T') ? 1 : 2;
    sum_pos[sum] = i;
  }

  for (int i = 1; i <= m; ++i) {
    int s;
    scanf("%d", &s);
    if (s > sum || (s > sum-best*2 && (sum-s)%2 == 1)) {
      printf("NIE\n");
    } else if (s >= sum-best*2) {
      print(Reverse(1), Reverse(n-(sum-s)/2));
    } else {
      int rest = sum-2*best-s;
      if (sum_pos[rest] != -1) {
        print(Reverse(sum_pos[rest]+1), Reverse(n-best));
      } else {
        print(Reverse(sum_pos[rest-1]+1), Reverse(n-best-1));
      }
    }
  }

  return 0;
}
