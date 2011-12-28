#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_LEN = 1000010;

char str1[MAX_LEN], str2[MAX_LEN];
char rev_str1[MAX_LEN];
int prefix[MAX_LEN], z[MAX_LEN];
// p[i] = cel mai lung sufix al lui str2[1..i] care este prefix pentru rev(str1)
int p[MAX_LEN];
// l[i] = lungimea celui mai lung substring care incepe pe pozitia i in str1 si
// e prefix pentru str2
int l[MAX_LEN];
pair <int, int> sol;

void CalculatePrefixFunction(int len, int start, int prefix[],
                             int output[], char text[], char pattern[]) {
  int p = 0;
  for (int i = start; i <= len; ++i) {
    while (p > 0 && text[i] != pattern[p+1]) {
      p = prefix[p];
    }
    if (text[i] == pattern[p+1]) {
      ++p;
    }
    output[i] = p;
  }
}

void KMP(int len, int output[], char text[], char pattern[]) {
  CalculatePrefixFunction(len, 2, prefix, prefix, pattern, pattern);
  CalculatePrefixFunction(len, 1, prefix, output, text, pattern);
}

void CalculateZFunction(int len, int start, int z[],
                        int output[], char text[], char pattern[]) {
  int left = 0, right = 0, prefix = 0;
  for (int i = start; i <= len; ++i) {
    if (right < i) {
      right = i;
      prefix = 0;
    } else {
      if (z[i-left+1] < right-i) {
        prefix = z[i-left+1];
      } else {
        prefix = right-i;
      }
    }

    while (right <= len && text[right] == pattern[prefix+1]) {
      ++right;
      ++prefix;
      left = i;
    }
    output[i] = prefix;
  }
}

void BoyerMoore(int len, int output[], char text[], char pattern[]) {
  CalculateZFunction(len, 2, z, z, pattern, pattern);
  CalculateZFunction(len, 1, z, output, text, pattern);
}

void Preprocess(int len) {
  for (int i = 1; i <= len; ++i) {
    rev_str1[i] = str1[len-i+1];
  }

  KMP(len, p, str2, rev_str1);
  BoyerMoore(len, l, str1, str2);
}

void Solve(int len) {
  sol = make_pair(0, 0);
  for (int i = 1; i < len && str1[i] == str2[len-i+1]; ++i) {
    if (l[i+1] + p[len-i] >= len-i) {
      sol = make_pair(i, len-p[len-i]+1);
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("d.in", "r", stdin);
#endif

  fgets(str1+1, MAX_LEN-1, stdin);
  fgets(str2+1, MAX_LEN-1, stdin);
  int str1_len = strlen(str1+1) - 1;
  int str2_len = strlen(str2+1) - 1;

  if (str1_len != str2_len) {
    printf("-1 -1\n");
    return 0;
  }

  Preprocess(str1_len);
  Solve(str1_len);

  printf("%d %d\n", sol.first-1, sol.second-1);

  return 0;
}
