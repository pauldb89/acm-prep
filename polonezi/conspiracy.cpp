#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_N = 5010;
const int MAX_DIGITS = 310;

class BigInteger {
  int len;
  int digits[MAX_DIGITS];
  const static int BASE, LG;

 public:
  BigInteger(int number) {
    len = 1;
    digits[1] = number;
  }

  void operator+=(const BigInteger& num) {
    int t = 0, i;
    for (i = 1; i <= len || i <= num.len || t > 0; ++i) {
      int tmp = (digits[i] + num.digits[i] + t) % BASE;
      t = (digits[i] + num.digits[i] + t) / BASE;
      digits[i] = tmp;
    }
    len = i-1;
  }

  void operator*=(const int factor) {
    int t = 0, i;
    for (i = 1; i <= len || t > 0; ++i) {
      int tmp = (digits[i] * factor + t) % BASE;
      t = (digits[i] * factor + t) / BASE;
      digits[i] = tmp;
    }
    len = i-1;
  }

  void print() {
    char format[10];
    sprintf(format, "%%0%dd", LG);
    printf("%d", digits[len]);
    for (int i = len-1; i > 0; --i) {
      printf(format, digits[i]); 
    }
    printf("\n");
  }
};

const int BigInteger :: BASE = 100000;
const int BigInteger :: LG = 5;

int n;
int freq[MAX_N], degree[MAX_N];
int divisors[MAX_N];

int cmp(int i, int j) {
  return i > j;
}

int TestCondition(int sum, int pos, int rest) {
  return sum == pos*(pos-1) + rest;
}

void MarkDivisors(int n, int value) {
  for (int i = 2; i <= n; ++i) {
    while (n % i == 0) {
      divisors[i] += value;
      n /= i;
    }
  }
}

BigInteger CalcCombination(int n, int k) {
  memset(divisors, 0, sizeof(divisors));
  BigInteger res = 1;
  for (int i = n-k+1; i <= n; ++i) {
    MarkDivisors(i, 1);
  }
  for (int i = 1; i <= k; ++i) {
    MarkDivisors(i, -1);
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= divisors[i]; ++j) {
      res *= i;
    }
  }
  return res;
}

int main() {
  // freopen("kon0.in", "r", stdin);

  scanf("%d", &n);
  int rest = 0;

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &degree[i]);
    ++freq[degree[i]];
    rest += degree[i];
    for (int j = 1; j <= degree[i]; ++j) {
      int x;
      scanf("%d", &x);
    }
  }

  sort(degree+1, degree+n+1, cmp);

  BigInteger solution(0);
  int sum = 0, same_degree = 0;
  for (int i = 1; i < n; ++i) {
    sum += degree[i];
    rest -= degree[i];
    if (degree[i] == degree[i-1]) {
      ++same_degree;
    } else {
      same_degree = 1;
    }
    if (TestCondition(sum, i, rest)) {
      solution += CalcCombination(freq[degree[i]], same_degree);
    }
  }

  solution.print();

  return 0;
}
