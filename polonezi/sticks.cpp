#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_N = 1000010;

int len;
pair<int,int> sticks[MAX_N];
pair<int,int> solution[3];

int TestTriangle(int side1, int side2, int side3) {
  return side1+side2 > side3 && side1+side3 > side2 && side2+side3 > side1;
}

int main() {
//  freopen("sticks.in", "r", stdin);

  int num_colors;
  scanf("%d", &num_colors);
  for (int i = 1; i <= num_colors; ++i) {
    int num_sticks;
    scanf("%d ", &num_sticks);
    for (int j = 1; j <= num_sticks; ++j) {
      int length;
      scanf("%d", &length);
      sticks[len++] = make_pair(length, i);
    }
  }

  sort(sticks, sticks+len);

  for (int i = 0; i < len; ++i) {
    if (sticks[i].second != solution[0].second && sticks[i].second != solution[1].second) {
      solution[2] = solution[1];
    }
    if (sticks[i].second != solution[0].second) {
      solution[1] = solution[0];
    }
    solution[0] = sticks[i];

    if (solution[2].second != 0 &&
        TestTriangle(solution[0].first, solution[1].first, solution[2].first)) {
      printf("%d %d %d %d %d %d\n",
             solution[0].second, solution[0].first, solution[1].second,
             solution[1].first, solution[2].second, solution[2].first);
      return 0;
    }
  }
  printf("NIE\n");

  return 0;
}
