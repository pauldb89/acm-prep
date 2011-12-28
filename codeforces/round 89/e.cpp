#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 100010;

int n, m, solution_exists;
char visited[MAX_N];
int level[MAX_N], min_level[MAX_N];
vector <int> graph[MAX_N];
vector <pair <int, int> > sol;

void DFS(int node, int parent) {
  visited[node] = 1;
  min_level[node] = level[node]+1;

  for (size_t i = 0; i < graph[node].size(); ++i) {
    if (!visited[graph[node][i]]) {
      sol.push_back(make_pair(node, graph[node][i]));
      level[graph[node][i]] = level[node]+1;
      DFS(graph[node][i], node);
      min_level[node] = min(min_level[node], min_level[graph[node][i]]);
      if (min_level[graph[node][i]] > level[node]) {
        solution_exists = 0;
      }
    } else if (level[node] > level[graph[node][i]] && graph[node][i] != parent) {
      sol.push_back(make_pair(node, graph[node][i]));
      min_level[node] = min(min_level[node], level[graph[node][i]]);
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("e.in", "r", stdin);
#endif

  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  solution_exists = 1;
  DFS(1, 0);

  if (solution_exists) {
    for (size_t i = 0; i < sol.size(); ++i) {
      printf("%d %d\n", sol[i].first, sol[i].second);
    }
  } else {
    printf("0\n");
  }

  return 0;
}
