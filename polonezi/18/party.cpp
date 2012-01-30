#include <cstdio>

const int MAX_N = 3010;

int n, m;
int adj[MAX_N][MAX_N];
int in_clique[MAX_N];

int main() {
//  freopen("party.in", "r", stdin);

  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    adj[x][y] = adj[y][x] = 1;
  }

  int last_node = n/3;
  for (int i = 1; i <= last_node; ++i) {
    in_clique[i] = 1;
  }

  for (int i = 1; i <= last_node; ++i) {
    if (in_clique[i]) {
      for (int j = 1; j <= last_node; ++j) {
        if (i != j && in_clique[j] && !adj[i][j]) {
          in_clique[i] = 0;
          in_clique[j] = 0;
          in_clique[++last_node] = 1;
          in_clique[++last_node] = 1;
          break;
        }
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (in_clique[i]) {
      printf("%d ", i);
    }
  }
  printf("\n");

  return 0;
}
