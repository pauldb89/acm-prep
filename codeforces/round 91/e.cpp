#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <cassert>

using namespace std;

const int MAX_DIGITS = 4;
const int ALL_DIGITS[2] = {4, 7};
const int MAX_N = 100010;
const int MAX_SQRT = 320;
const int MAX_OPER = 10;
const int MAX_VAL = 10010;

int n, m, len;
int a[MAX_N];
vector <int> lucky_numbers;
int digits[MAX_DIGITS];
int start[MAX_SQRT], end[MAX_SQRT], add[MAX_SQRT];
short hash[MAX_SQRT][MAX_VAL];
int interv[MAX_N];
char is_lucky_number[MAX_VAL];
char oper[MAX_OPER];

void back(int pos, int len) {
  if (pos == len) {
    int num = 0;
    for (int i = 0; i < len; ++i) {
      num = num * 10 + digits[i];
    }
    lucky_numbers.push_back(num);
  } else {
    for (int i = 0; i < 2; ++i) {
      digits[pos] = ALL_DIGITS[i];
      back(pos+1, len);
    }
  }
}

void AddValue(int x, int y, int value) {
  if (interv[x] == interv[y]) {
    for (int i = x; i <= y; ++i) {
      --hash[interv[x]][a[i]];
      a[i] += value;
      ++hash[interv[x]][a[i]];
    }
  } else {
    for (int i = x; i <= end[interv[x]]; ++i) {
      --hash[interv[x]][a[i]];
      a[i] += value;
      ++hash[interv[x]][a[i]];
    }
    for (int i = interv[x]+1; i < interv[y]; ++i) {
      add[i] += value;
    }
    for (int i = start[interv[y]]; i <= y; ++i) {
      --hash[interv[y]][a[i]];
      a[i] += value;
      ++hash[interv[y]][a[i]];
    }
  }
}

int Query(int x, int y) {
  int result = 0;
  if (interv[x] == interv[y]) {
    for (int i = x; i <= y; ++i) {
      result += is_lucky_number[a[i]+add[interv[x]]];
    }
  } else {
    for (int i = x; i <= end[interv[x]]; ++i) {
      result += is_lucky_number[a[i]+add[interv[x]]];
    }
    for (size_t i = 0; i < lucky_numbers.size(); ++i) {
      for (int j = interv[x]+1; j < interv[y]; ++j) 
        if (lucky_numbers[i]-add[j] > 0) {
        result += hash[j][lucky_numbers[i]-add[j]];
      }
    }
    for (int i = start[interv[y]]; i <= y; ++i) {
      result += is_lucky_number[a[i]+add[interv[y]]];
    }
  }
  return result;
}

int main() {
//  freopen("e.in", "r", stdin);

  for (int i = 1; i <= MAX_DIGITS; ++i) {
    back(0, i);
  }
  for (size_t i = 0; i < lucky_numbers.size(); ++i) {
    is_lucky_number[lucky_numbers[i]] = 1;
  }

  scanf("%d %d ", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d ", &a[i]);
  }

  len = sqrt(n);
  for (int i = 1, j = 1; i <= n; i += len, ++j) {
    start[j] = i;
    end[j] = min(n, i+len-1);
    for (int k = start[j]; k <= end[j]; ++k) {
      interv[k] = j;
      ++hash[j][a[k]];
    }
  }

  int x, y;
  for (int i = 1; i <= m; ++i) {
    scanf("%s %d %d ", oper, &x, &y);
    if (strcmp(oper, "add") == 0) {
      int value;
      scanf("%d ", &value);
      AddValue(x, y, value);
    } else {
      printf("%d\n", Query(x, y));
    }
  }

  return 0;
}
