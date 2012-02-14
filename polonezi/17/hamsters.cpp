#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int MAX_N = 210;
const int MAX_LEN = 100010;
const long long INF = 1000000000000000LL;

int n, m;
string words[MAX_N];
int len[MAX_N];
int prefix[MAX_LEN];
long long mat[MAX_N][MAX_N], dist[MAX_N][MAX_N];

void CalcPrefix(const string& pattern, int pattern_len) {
  int p = 0;
  for (int i = 2; i <= pattern_len; ++i) {
    while (p > 0 && pattern[p+1] != pattern[i]) {
      p = prefix[p];
    }
    if (pattern[p+1] == pattern[i]) {
      ++p;
    }
    prefix[i] = p;
  }
}

int LongestSuffixPrefix(const string& pattern, int pattern_len, const string& text, int text_len) {
  int p = 0;
  for (int i = 1; i <= text_len; ++i) {
    while (p > 0 && (p+1 == pattern_len || pattern[p+1] != text[i])) {
      p = prefix[p];
    }
    if (pattern[p+1] == text[i]) {
      ++p;
    }
  }
  return p;
}

void ComposeMatrices(long long a[MAX_N][MAX_N], long long b[MAX_N][MAX_N], long long c[MAX_N][MAX_N]) {
  long long tmp[MAX_N][MAX_N];
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      tmp[i][j] = INF;
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      for (int k = 1; k <= n; ++k) {
        tmp[i][j] = min(tmp[i][j], b[i][k] + c[k][j] - len[k]);
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      a[i][j] = tmp[i][j];
    }
  }
}

int main() {
//  ifstream cin("hamsters.in");

  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> words[i];
    words[i] = " " + words[i];
    len[i] = words[i].size() - 1;
  }

  for (int i = 1; i <= n; ++i) {
    CalcPrefix(words[i], len[i]);
    mat[i][i] = 2*len[i] - prefix[len[i]];
    dist[i][i] = len[i];

    for (int j = 1; j <= n; ++j) {
      if (i != j) {
        mat[j][i] = len[i] + len[j] - LongestSuffixPrefix(words[i], len[i], words[j], len[j]);
        dist[j][i] = INF;
      }
    }
  }

  --m;
  while (m > 0) {
    if (m&1) {
      ComposeMatrices(dist, dist, mat);
    }
    ComposeMatrices(mat, mat, mat);
    m >>= 1;
  }

  long long solution = INF;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      solution = min(solution, dist[i][j]);
    }
  }
  printf("%lld\n", solution);

  return 0;
}
