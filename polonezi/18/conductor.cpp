#include <algorithm>
#include <cmath>
#include <cstdio>
#include <deque>

using namespace std;

const int MAX_N = 500010;

int n;
int height[MAX_N];
double sol[MAX_N];

double Intersection(int i, int j) {
  if (height[j] >= height[i] + sqrt(abs(j-i))) {
    return j;
  }
  long double alfa = (long double) (height[j]-height[i])*(height[j]-height[i]) + i + j;
  return (alfa*alfa - 4.0*i*j) / (4*(alfa-i-j));
}

void Solve(int flag) {
  deque<int> candidates;
  for (int i = 1; i <= n; ++i) {
    if (candidates.size() == 0 || height[candidates.back()] < height[i]) {
      while (candidates.size() >= 2 &&
             Intersection(candidates[candidates.size()-2], candidates.back()) >
             Intersection(candidates.back(), i)) {
        candidates.pop_back();
      }
      candidates.push_back(i);
    }
    while (candidates.size() >= 2 &&
           Intersection(candidates[0], candidates[1]) <= i) {
      candidates.pop_front();
    }
    int p = candidates.front();
    int current_pos = flag ? n-i+1 : i;
    sol[current_pos] = max(sol[current_pos], height[p]-height[i] + sqrt(abs(i-p)));
  }
}

int main() {
//  freopen("conductor.in", "r", stdin);
//  freopen("conductor.ok", "w", stdout);

  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &height[i]);
  }

  Solve(0);
  reverse(height+1, height+n+1);
  Solve(1);

  for (int i = 1; i <= n; ++i) {
    printf("%d\n", (int) ceil(sol[i]));
  }

  return 0;
}
