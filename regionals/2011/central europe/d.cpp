#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAX_N = 110;
const int MAX_NODES = 10010;
const int MAX_DIR = 4;
const int DIRX[MAX_DIR] = {-1, 0, 1, 0};
const int DIRY[MAX_DIR] = {0, -1, 0, 1};

int n, m;
int cells[2];
char board[MAX_N][MAX_N];
int numbers[MAX_N][MAX_N];
vector<int> graph[2][MAX_NODES];
int matcher[MAX_NODES], visited[MAX_NODES];
char loser[2][MAX_NODES];

int DFS(int type, int node, int marker) {
  if (visited[node] == marker) {
    return 0;
  }
  visited[node] = marker;
  for (size_t i = 0; i < graph[type][node].size(); ++i) {
    if (matcher[graph[type][node][i]] == -1 || DFS(type, matcher[graph[type][node][i]], marker)) {
      matcher[graph[type][node][i]] = node;
      return 1;
    }
  }
  return 0;
}

void MaximumMatching(int type) {
  memset(visited, 0, sizeof(visited));
  memset(matcher, -1, sizeof(matcher));
  queue<int> q;

  for (int i = 1; i <= cells[type]; ++i) {
    if (!DFS(type, i, i)) {
      loser[type][i] = 1;
      q.push(i);
    }
  }

  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (size_t i = 0; i < graph[type][node].size(); ++i) {
      if (matcher[graph[type][node][i]] != -1 && !loser[type][matcher[graph[type][node][i]]]) {
        loser[type][matcher[graph[type][node][i]]] = 1;
        q.push(matcher[graph[type][node][i]]);
      }
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("5882.in", "r", stdin);
  freopen("5882.out", "w", stdout);
#endif

  scanf("%d %d", &n, &m);
  while (n != 0 || m != 0) {
    cells[0] = cells[1] = 0;
    for (int i = 0; i < MAX_NODES; ++i) {
      for (int j = 0; j < 2; ++j) {
        graph[j][i].clear();
      }
    }
    memset(loser, 0, sizeof(loser));
    memset(numbers, 0, sizeof(numbers));

    for (int i = 0; i < n; ++i) {
      scanf("%s", board[i]);
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board[i][j] != 'X') {
          numbers[i][j] = ++cells[(i+j) % 2];
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board[i][j] != 'X' && (i+j) % 2 == 0) {
          for (int k = 0; k < MAX_DIR; ++k) {
            int x = i + DIRX[k];
            int y = j + DIRY[k];
            if (x >= 0 && x < n && y >= 0 && y < m && board[x][y] != 'X') {
              graph[0][numbers[i][j]].push_back(numbers[x][y]);
              graph[1][numbers[x][y]].push_back(numbers[i][j]);
            }
          }
        }
      }
    }

    for (int i = 0; i < 2; ++i) {
      MaximumMatching(i);
    }

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (board[i][j] == 'X') {
          printf("X");
        } else if (loser[(i+j)%2][numbers[i][j]]) {
          printf("B");
        } else {
          printf("A");
        }
      }
      printf("\n");
    }
    printf("\n");

    scanf("%d %d", &n, &m);
  }

  return 0;
}
