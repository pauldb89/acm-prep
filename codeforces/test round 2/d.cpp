#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 30010;

int n;
int a[MAX_N];
char is_sequence[MAX_N];

int TestExtendSequence(int prev, int current, int next) {
  return current-prev == next-current;
}

int TestFullyExtendSequence(const vector<int>& seq, int pos) {
  if (pos == n) {
    return 1;
  }
  if (!is_sequence[pos]) {
    return 0;
  }
  if (seq.size() == 0) {
    return 1;
  }
  if (seq.size() == 1) {
    return TestExtendSequence(seq.back(), a[pos], a[pos+1]);
  }
  return TestExtendSequence(seq[seq.size()-1], a[pos], a[pos+1]) &&
         TestExtendSequence(seq[seq.size()-2], seq[seq.size()-1], a[pos]);
}

int FindSolution(int pos, vector<int>& seq1, vector<int>& seq2) {
  if (pos > n) {
    if (seq2.size() == 0) {
      seq2.push_back(seq1.back());
      seq1.pop_back();
    }
    return 1;
  } else {
    int len1 = seq1.size();
    int len2 = seq2.size();
    int extend1 = 0, extend2 = 0;
    if (len1 < 2 || TestExtendSequence(seq1[seq1.size()-2], seq1[seq1.size()-1], a[pos])) {
      extend1 = 1;
    }
    if (len2 < 2 || TestExtendSequence(seq2[seq2.size()-2], seq2[seq2.size()-1], a[pos])) {
      extend2 = 1;
    }

    if (extend1 && !(extend2 && len2 >= 2 && !TestFullyExtendSequence(seq1, pos))) {
      seq1.push_back(a[pos]);
      if (FindSolution(pos+1, seq1, seq2)) {
        return 1;
      }
      seq1.pop_back();
    }

    if (extend2 && !(extend1 && len1 >= 2 && !TestFullyExtendSequence(seq2, pos))) {
      seq2.push_back(a[pos]);
      if (FindSolution(pos+1, seq1, seq2)) {
        return 1;
      }
      seq2.pop_back();
    }
  }

  return 0;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("d.in", "r", stdin);
#endif

  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }

  is_sequence[n] = is_sequence[n-1] = 1;
  for (int i = n-2; i > 0; --i) {
    is_sequence[i] = is_sequence[i+1];
    if (a[i+1]-a[i] != a[i+2]-a[i+1]) {
      is_sequence[i] = 0;
    }
  }

  vector<int> seq1, seq2;
  seq1.push_back(a[1]);
  if (FindSolution(2, seq1, seq2)) {
    for (size_t i = 0; i+1 < seq1.size(); ++i) {
      printf("%d ", seq1[i]);
    }
    printf("%d\n", seq1.back());
    for (size_t i = 0; i+1 < seq2.size(); ++i) {
      printf("%d ", seq2[i]);
    }
    printf("%d\n", seq2.back());
  } else {
    printf("No solution\n");
  }

  return 0;
}
