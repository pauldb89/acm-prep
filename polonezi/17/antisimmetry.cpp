#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_N = 500010;

int n;
char str[MAX_N];
int longest_pali[MAX_N];
long long solution;

int main() {
//  freopen("antisimmetry.in", "r", stdin);

  scanf("%d ", &n);
  fgets(str+1, MAX_N-1, stdin);

  int right_end = 0, pali_center = 0;
  for (int i = 1; i <= n; ++i) {
    if (right_end <= i) {
      right_end = i;
      pali_center = i;
      longest_pali[i] = 0;
    } else {
      int dist = i-pali_center;
      longest_pali[i] = min(longest_pali[pali_center-dist], right_end-i);
    }

    if (i+longest_pali[i] >= right_end) {
      pali_center = i;
      int left = i-longest_pali[i];
      int right = i+1+longest_pali[i];
      while (left > 0 && right <= n && str[left] != str[right]) {
        right_end = right;
        --left;
        ++right;
        ++longest_pali[i];
      }
    }

    solution += longest_pali[i];
  }

  printf("%lld\n", solution);

  return 0;
}
