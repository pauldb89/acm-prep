#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

const int MAX_N = 100010;
const int MAX_LG = 18;
const int SIGMA = 26;

int n, len;
long long sol;
char str[MAX_N];
int suffix[MAX_LG][MAX_N];
int position[MAX_N];
pair<int, int> suffixes[MAX_N];
int lcp[MAX_N], stack[MAX_N], pos[MAX_N];

int cmp(int i, int j) {
  return suffixes[i] < suffixes[j];
}

void BuildSuffixArray() {
  for (int i = 0; i < n; ++i) {
    suffix[0][i] = str[i]-'a';
  }
  suffix[0][n++] = SIGMA+1;

  for (int step = 1; 1<<(step-1) <= n; ++step) {
    for (int i = 0; i < n; ++i) {
      position[i] = i;
      suffixes[i] = make_pair(suffix[step-1][i], suffix[step-1][min(n-1, i+(1<<(step-1)))]);
    }
    sort(position, position+n, cmp);
    int j = 0;
    while (j < n) {
      for (int i = j; suffixes[position[i]] == suffixes[position[j]]; ++j) {
        suffix[step][position[j]] = i;
      }
    }
  }
}

long long cmb2(long long x) {
  return x*(x+1)/2;
}

int FindLCP(int i, int j) {
  int step = 0, res = 0;
  while (1<<(step+1) <= n) {
    ++step;
  }
  while (step >= 0) {
    if (suffix[step][i] == suffix[step][j]) {
      i += 1<<step;
      j += 1<<step;
      res += 1<<step;
    }
    --step;
  }
  return res;
}

int main() {
#ifndef ONLINE_JUDGE
  ifstream cin("d.in");
#endif

  cin >> str;
  n = strlen(str);

  BuildSuffixArray();

  for (int i = 0; i+1 < n; ++i) {
    lcp[i] = FindLCP(position[i], position[i+1]);
    int is_removing = 0;
    while (len > 0 && stack[len] > lcp[i]) {
      is_removing = 1;
      sol += (long long) (stack[len]-max(lcp[i], stack[len-1])) * cmb2(i-pos[len]+1);
      --len;
    }
    if (len == 0 || lcp[i] > stack[len]) {
      stack[++len] = lcp[i];
      if (!is_removing) {
        pos[len] = i;
      }
    }
  }

  sol += (n-1-position[0]) - lcp[0];
  for (int i = 1; i+1 < n; ++i) {
    sol += (n-1-position[i]) - max(lcp[i], lcp[i-1]);
  }

  cout << sol << endl;

  return 0;
}
