#include <cstdio>
#include <deque>

using namespace std;

const int MAX_N = 1000010;

int n, solution;
int min_temp[MAX_N];
deque<int> positions;

int main() {
//  freopen("temperature.in", "r", stdin);

  scanf("%d ", &n);
  int last = 0;
  for (int i = 1; i <= n; ++i) {
    int max_temp;
    scanf("%d %d ", &min_temp[i], &max_temp);

    while (positions.size() > 0 && min_temp[positions.back()] <= min_temp[i]) {
      positions.pop_back();
    }
    positions.push_back(i);

    while (min_temp[positions.front()] > max_temp) {
      last = positions.front();
      positions.pop_front();
    }
    solution = max(solution, i-last);
  }

  printf("%d\n", solution);
}
