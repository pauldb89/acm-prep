#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_LEN = 200010;

int len;
char str[MAX_LEN], solution[MAX_LEN];
int prefix[MAX_LEN], new_prefix[MAX_LEN];

void CalcPrefix(int start, int end, char str[], int prefix[]) {
  int p = prefix[start-1];
  for (int i = start; i <= end; ++i) {
    while (p > 0 && str[i] != str[p+1]) {
      p = prefix[p];
    }
    if (str[i] == str[p+1]) {
      ++p;
    }
    prefix[i] = p;
  }
}

void CopyPrefix(int prefix_len, int end) {
  for (int i = max(end - prefix_len, prefix_len) + 1; i <= end; ++i) {
    solution[i] = solution[i - (end - prefix_len)];
  }
}

void FillSequence(int prefix_len, int end) {
  for (int i = prefix_len + 1; i <= end-prefix_len; ++i) {
    solution[i] = 0;
  }
  CalcPrefix(prefix_len + 1, end, solution, new_prefix);
  if (new_prefix[end] != prefix[end]) {
    solution[end-prefix_len] = 1;
    CalcPrefix(prefix_len + 1, end, solution, new_prefix);
  }
}

void FindSolution() {
  vector<int> prefixes;
  int p = len;
  while (prefix[p] > 0) {
    prefixes.push_back(p);
    p = prefix[p];
  }
  reverse(prefixes.begin(), prefixes.end());

  int step = p;
  if (step == 1) {
    solution[step] = 0;
    new_prefix[step] = 0;
  } else {
    for (int i = 1; i < step; ++i) {
      solution[i] = 0;
      new_prefix[i] = i-1;
    }
    solution[step] = 1;
    new_prefix[step] = 0;
  }
  for (vector<int> :: iterator it = prefixes.begin(); it != prefixes.end(); ++it) {
    CopyPrefix(step, *it);
    FillSequence(step, *it);
    step = *it;
  }
}

int main() {
//  freopen("periodicity.in", "r", stdin);

  int tests;
  scanf("%d ", &tests);
  for (int t = 1; t <= tests; ++t) {
    fgets(str+1, MAX_LEN-1, stdin);
    len = strlen(str+1)-1;

    CalcPrefix(2, len, str, prefix);
    FindSolution();

    for (int i = 1; i <= len; ++i) {
      printf("%d", solution[i]);
    }
    printf("\n");
  }

  return 0;
}
