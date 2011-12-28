#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 100010;
const int SIGMA = 26;

int n, k, len;
char str[MAX_N], sol[MAX_N];
int suffix[MAX_N], indexes[MAX_N];
pair<int, int> suffix_pairs[MAX_N];
long long sum[MAX_N];

int cmp(int i, int j) {
  return suffix_pairs[i] < suffix_pairs[j];
}

void BuildSuffixArray() {
  for (int i = 0; i < n; ++i) {
    suffix[i] = str[i]-'a';
  }
  suffix[n++] = SIGMA;

  for (int step = 0; 1<<(step)<=n; ++step) {
    for (int i = 0; i < n; ++i) {
      suffix_pairs[i] = make_pair(suffix[i], suffix[min(i+(1<<step), n-1)]);
      indexes[i] = i;
    }
    sort(indexes, indexes+n, cmp);
    int j = 0;
    while (j < n) {
      for (int i = j; j < n && suffix_pairs[indexes[i]] == suffix_pairs[indexes[j]]; ++j) {
        suffix[indexes[j]] = i;
      }
    }
  }
}

void FindKthSubstring() {
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i-1] + n-indexes[i-1]-1;
  }

  int lower = 1, upper = n;
  for (int len = 0; len < n; ++len) {
    int front = lower, back = upper, pos = lower;
    while (front <= back) {
      int middle = (front+back)/2;
      if ((sum[middle]-sum[lower-1]-len*(middle-lower+1)) >= k) {
        pos = middle;
        back = middle-1;
      } else {
        front = middle+1;
      }
    }

    sol[len] = str[indexes[pos-1]+len];
    while (str[indexes[lower-1]+len] != str[indexes[pos-1]+len]) {
      k -= n-indexes[lower-1]-1-len;
      ++lower;
    }
    while (str[indexes[upper-1]+len] != str[indexes[pos-1]+len]) {
      --upper;
    }
    if (upper-lower+1 >= k) {
      break;
    } else {
      k -= upper-lower+1;
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("b.in", "r", stdin);
#endif

  scanf("%s %d", str, &k);
  n = strlen(str);
  if ((long long) n*(n+1)/2 < k) {
    printf("No such line.\n");
    return 0;
  }

  BuildSuffixArray();
  FindKthSubstring();

  printf("%s\n", sol);

  return 0;
}
