#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_DIGITS = 9;
const int ALL_DIGITS[2] = {4, 7};
const int MAX_K = 20;

int n, k;
vector <long long> lucky_numbers;
int digits[MAX_DIGITS];
long long fact[MAX_K];
char used[MAX_K];

void back(int pos, int len) {
  if (pos == len) {
    long long num = 0;
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

int IsLuckyNumber(int num) {
  while (num > 0) {
    int digit = num % 10;
    if (digit != 4 && digit != 7) {
      return 0;
    }
    num /= 10;
  }
  return 1;
}

int GetNextFreeNum(int num) {
  while (used[num]) {
    ++num;
  }
  return num;
}

int CountLuckyPositions() {
  int result = 0;
  fact[0] = 1;
  int pos = n;
  while (pos >= 1 && fact[n-pos] < k) {
    fact[n-pos+1] = fact[n-pos]*(n-pos+1);
    --pos;
  }

  if (pos == 0 && k > fact[n]) {
    return -1;
  }

  for (size_t i = 0; i < lucky_numbers.size() && lucky_numbers[i] <= pos; ++i) {
      ++result;
  }

  for (int i = 1; i <= n-pos; ++i) {
    int num = GetNextFreeNum(1);
    while (k > fact[n-pos-i]) {
      k -= fact[n-pos-i];
      num = GetNextFreeNum(num+1);
    }
    used[num] = 1;
    result += IsLuckyNumber(pos+i) && IsLuckyNumber(pos+num);
  }

  return result;
}

int main() {
//  ifstream cin("c.in");

  cin >> n >> k;

  for (int i = 1; i <= MAX_DIGITS; ++i) {
    back(0, i);
  }

  cout << CountLuckyPositions() << endl;

  return 0;
}
