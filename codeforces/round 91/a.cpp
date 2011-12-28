#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_DIGITS = 10;
const int ALL_DIGITS[2] = {4, 7};

int start, end;
long long sol;
vector <long long> lucky_numbers;
int digits[MAX_DIGITS];

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

long long CalcSum(long long num) {
  long long result = 0;
  for (size_t i = 1; i < lucky_numbers.size(); ++i) {
    result += (min(num, lucky_numbers[i])-lucky_numbers[i-1])*lucky_numbers[i];
    if (lucky_numbers[i] > num) {
      break;
    }
  }
  return result;
}

int main() {
//  ifstream cin("a.in");

  cin >> start >> end;

  for (int i = 0; i <= MAX_DIGITS; ++i) {
    back(0, i);
  }

  cout << CalcSum(end) - CalcSum(start-1) << endl;

  return 0;
}
