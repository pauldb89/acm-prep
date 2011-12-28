#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 1000010;
const int SIGMA = 26;

int n, sol;
char word[MAX_N], marked[MAX_N];
int min_sum[MAX_N];
int last[SIGMA], prev_last[SIGMA], freq[SIGMA];

void SolveFirstCase() {
  memset(last, -1, sizeof(last));
  for (char letter = 'a'; letter <= 'z'; ++letter) {
    int sum = 0, prev_sum = 0, left_index = 0;

    for (int i = 0; i < n; ++i) {
      if (word[i] == letter) {
        ++sum;
      } else {
        if (last[word[i]-'a'] >= 0) {
          --marked[last[word[i]-'a']];
        }
        last[word[i]-'a'] = i;
        ++marked[i];
      }

      while (left_index <= i && !marked[left_index]) {
        prev_sum += word[left_index] == letter;
        ++left_index;
      }
      if (letter == word[i]) {
        sol = max(sol, sum-prev_sum-1);
      }
    }

    for (int i = 0; i < SIGMA; ++i) {
      if (last[i] >= 0) {
        marked[last[i]] = 0;
        last[i] = -1;
      }
    }
  }
}

void SolveSecondCase() {
  for (char letter = 'a'; letter <= 'z'; ++letter) {
    memset(freq, 0, sizeof(freq));
    memset(last, -1, sizeof(last));
    memset(prev_last, -1, sizeof(prev_last));
    int left_index = 0;

    for (int i = 0; i < n; ++i) {
      if (word[i] == letter) {
        while (left_index < i) {
          prev_last[word[left_index]-'a'] = left_index;
          ++left_index;
        }
      } else {
        if (prev_last[word[i]-'a'] >= 0 && freq[letter-'a'] > 0) {
          sol = max(sol, freq[word[i]-'a']+1-freq[letter-'a'] - min_sum[prev_last[word[i]-'a']]);
        }
        min_sum[i] = freq[word[i]-'a']-freq[letter-'a'];
        if (last[word[i]-'a'] >= 0) {
          min_sum[i] = min(min_sum[i], min_sum[last[word[i]-'a']]);
        }
      }
      last[word[i]-'a'] = i;
      ++freq[word[i]-'a'];
    }
  }
}

int main() {
  // freopen("difference.in", "r", stdin);

  scanf("%d ", &n);
  fgets(word, MAX_N, stdin);

  // First case
  SolveFirstCase();
  reverse(word, word+n);
  SolveFirstCase();

  // Second case
  SolveSecondCase();

  printf("%d\n", sol);

  return 0;
}
