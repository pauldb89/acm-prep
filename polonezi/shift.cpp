#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 2010;

int n;
int perm[MAX_N], position[MAX_N];
vector<pair<int, char> > solution;

int NoSolution() {
  if (n % 2 == 0) {
    return 0;
  }
  int inversions = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      inversions += perm[j] > perm[i];
    }
  }
  return inversions % 2 == 1;
}

int FindDist(int pos1, int pos2) {
  return (pos1 - pos2 + n) % n;
}

void AddMove(int value, char type) {
  if (solution.size() > 0 && solution.back().second == type) {
    solution.back().first += value;
  } else {
    solution.push_back(make_pair(value, type));
  }

  if (solution.size() > 0 && solution.back().first == 0) {
    solution.pop_back();
  }
}

void Rotate(int start, int dest, int& shift) {
  int dist = FindDist(dest, (start+shift) % n);
  AddMove(dist, 'a');
  shift += dist;
}

void JumpTwo(int pos, int& shift) {
  if (pos == 3 && shift == 1) {
    printf("intra\n");
  }
  Rotate(pos, 2, shift);
  int tmp = perm[pos];
  int middle_pos = (pos-1+n) % n;
  perm[pos] = perm[middle_pos];
  position[perm[pos]] = pos;
  int left_pos = (middle_pos-1+n) % n;
  perm[middle_pos] = perm[left_pos];
  position[perm[middle_pos]] = middle_pos;
  perm[left_pos] = tmp;
  position[perm[left_pos]] = left_pos;
  AddMove(1, 'b');
}

void Debug() {
  for (int i = 0; i < n; ++i) {
    printf("%d ", perm[i]);
  }
  printf("\n");
  for (int i = 1; i <= n; ++i) {
    printf("%d ", position[i]);
  }
  printf("\n");
}

int main() {
//  freopen("shift.in", "r", stdin);

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &perm[i]);
    position[perm[i]] = i;
  }

  if (NoSolution()) {
    printf("NIE DA SIE\n");
    return 0;
  }

  int shift = 0;
  for (int i = 2; i <= n; ++i) {
    while (FindDist(position[i], position[i-1]) > 2) {
      JumpTwo(position[i], shift);
    }
    if (FindDist(position[i], position[i-1]) > 1) {
      int right = (position[i]+1) % n;
      if (perm[right] != 1) {
        JumpTwo(right, shift);
        JumpTwo(position[i], shift);
      } else {
        JumpTwo(position[i], shift);
        while (FindDist(position[i], position[i-1]) > 1) {
          JumpTwo(position[i], shift);
        }
      }
    }
  }
  Rotate(position[1], 0, shift);

  printf("%d\n", solution.size());
  for (size_t i = 0; i < solution.size(); ++i) {
    printf("%d%c ", solution[i].first, solution[i].second);
  }
  printf("\n");

  return 0;
}
