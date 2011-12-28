#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>

using namespace std;

const int MAX_N = 25;
const int MAX_VARIABLES = 465;
const double EPS = 0.00000001;

int n, m, room1, room2;
int adj[MAX_N][MAX_N];
int degree[MAX_N];
double prob[MAX_N];

int equations, variables;
map < pair <int, int>, int> var;
double mat[MAX_VARIABLES][MAX_VARIABLES];
double result[MAX_VARIABLES][MAX_N];

void BuildSystem() {
  variables = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i != j) {
        var[make_pair(i, j)] = ++variables;
      }
    }
  }

  equations = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (i != j) {
        ++equations;
        mat[equations][var[make_pair(i , j)]] = -1 + prob[i]*prob[j];
        for (int x = 1; x <= n; ++x) {
          if (adj[i][x]) {
            if (x != j) {
              mat[equations][var[make_pair(x, j)]] = (1-prob[i])*prob[j]/degree[i];
            } else {
              result[equations][x] = -(1-prob[i])*prob[j]/degree[i];
            }
            for (int y = 1; y <= n; ++y) {
              if (adj[j][y]) {
                if (x != y) {
                  mat[equations][var[make_pair(x, y)]] =
                    (1-prob[i])*(1-prob[j]) / (degree[i]*degree[j]);
                } else {
                  result[equations][x] = -(1-prob[i])*(1-prob[j]) / (degree[i]*degree[j]);
                }
              }
            }
          }
          if (adj[j][x]) {
            if (i != x) {
              mat[equations][var[make_pair(i, x)]] = prob[i]*(1-prob[j])/degree[j];
            } else {
              result[equations][x] = -prob[i]*(1-prob[j])/degree[j];
            }
          }
        }
      }
    }
  }
}

void SwapRows(int x, int y, int start) {
  for (int i = start; i <= variables; ++i) {
    swap(mat[x][i], mat[y][i]);
  }
  for (int i = 1; i <= n; ++i) {
    swap(result[x][i], result[y][i]);
  }
}

void ReduceEquations(int x, int y, int start) {
  for (int i = 1; i <= n; ++i) {
    result[y][i] -= result[x][i] * mat[y][start] / mat[x][start];
  }
  for (int i = variables; i >= start; --i) {
    mat[y][i] -= mat[x][i] * mat[y][start] / mat[x][start];
  }
}

void SolveSystem() {
  int has_single_solution = 1;
  for (int i = 1; i <= equations; ++i) {
    if (fabs(mat[i][i]) < EPS) {
      int swapped = 0;
      for (int j = i+1; j <= equations; ++j) {
        if (fabs(mat[j][i]) > EPS) {
          SwapRows(i, j, i);
          swapped = 1;
          break;
        }
      }
      if (!swapped) {
        has_single_solution = 0;
        break;
      }
    }

    for (int j = 1; j <= equations; ++j) {
      if (j != i) {
        ReduceEquations(i, j, i);
      }
    }
  }
  assert(has_single_solution);
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("d.in", "r", stdin);
#endif
  scanf("%d %d %d %d", &n, &m, &room1, &room2);
  if (room1 == room2) {
    for (int i = 1; i <= n; ++i) {
      printf("%.10lf ", room1 == i ? 1.0 : 0.0);
    }
    return 0;
  }
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    adj[x][y] = adj[y][x] = 1;
    ++degree[x];
    ++degree[y];
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%lf", &prob[i]);
  }

  BuildSystem();
  SolveSystem();
  
  int pos = var[make_pair(room1, room2)];
  for (int i = 1; i < n; ++i) {
    printf("%.10lf ", result[pos][i] / mat[pos][pos]);
  }
  printf("%.10lf\n", result[pos][n] / mat[pos][pos]);

  return 0;
}
