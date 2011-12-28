#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 100010;
const int MAX_LENGTH = 18;
const long long INF = 1000000000000000001LL;

int num_intervals, sol;
long long num_steps, max_diff;
long long start[MAX_N], end[MAX_N];
vector <long long> lucky_numbers;
vector <long long> move_to_left, move_to_right;

long long add(long long a, long long b) {
  if (a+b <= INF) {
    return a+b;
  }
  return INF;
}

long long mult(long long a, long long b) {
  if ((long double) a*b <= INF) {
    return a*b;
  }
  return INF;
}

int main() {
#ifndef ONLINE_JUDGE
  ifstream cin("d.in");
#endif

  for (int i = 0; i <= MAX_LENGTH; ++i) {
    for (int j = 0; j < 1<<i; ++j) {
      long long num = 0;
      for (int k = 1; k <= i; ++k) {
        num *= 10;
        if ((j&(1<<(i-k))) == 0) {
          num += 4;
        } else {
          num += 7;
        }
      }
      lucky_numbers.push_back(num);
    }
  }
  lucky_numbers.push_back(INF);

  /*
  int total_lucky_numbers;
  cin >> total_lucky_numbers;
  for (int i = 0; i < total_lucky_numbers; ++i) {
    long long x;
    cin >> x;
    lucky_numbers.push_back(x);
  }
  */

  cin >> num_intervals >> num_steps;
  max_diff = INF;
  for (int i = 0; i < num_intervals; ++i) {
    cin >> start[i] >> end[i];
    max_diff = min(max_diff, end[i]-start[i]+1);
  }

  sort(start, start+num_intervals);
  sort(end, end+num_intervals);

  move_to_right.resize(lucky_numbers.size());
  move_to_left.resize(lucky_numbers.size());
  int interv_right = 0, cnt_right = 0;
  for (size_t i = 1; i+1 < lucky_numbers.size(); ++i) {
    move_to_right[i] = add(move_to_right[i-1],
                           mult(cnt_right, lucky_numbers[i]-lucky_numbers[i-1]));
    while (interv_right < num_intervals && end[interv_right] < lucky_numbers[i]) {
      move_to_right[i] = add(move_to_right[i], lucky_numbers[i]-end[interv_right]);
      ++cnt_right;
      ++interv_right;
    }
  }

  int interv_left = num_intervals-1, cnt_left = 0;
  for (size_t i = lucky_numbers.size()-2; i > 0; --i) {
    move_to_left[i] = add(move_to_left[i+1],
                          mult(cnt_left, lucky_numbers[i+1]-lucky_numbers[i]));
    while (interv_left >= 0 && start[interv_left] > lucky_numbers[i]) {
      move_to_left[i] = add(move_to_left[i], start[interv_left]-lucky_numbers[i]);
      ++cnt_left;
      --interv_left;
    }
  }

  for (size_t x = 1, y = 0; x+1 < lucky_numbers.size(); ++x) {
    if (y < x) {
      y = x;
      if (add(move_to_left[x], move_to_right[y]) <= num_steps) {
        sol = max(sol, int(y-x+1));
      }
    }
    while (y+2 < lucky_numbers.size() && add(move_to_left[x], move_to_right[y+1]) <= num_steps &&
           lucky_numbers[y+1]-lucky_numbers[x]+1 <= max_diff) {
      ++y;
      sol = max(sol, int(y-x+1));
    }
  }

  printf("%d\n", sol);

  return 0;
}
