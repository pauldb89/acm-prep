#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

const int MAX_N = 200010;

int n, m;
vector<int> graph[MAX_N];
int dist[MAX_N];

void BFS(int node) {
  dist[node] = 1;
  queue<int> q;
  q.push(node);

  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (size_t i = 0; i < graph[node].size(); ++i) {
      if (!dist[graph[node][i]]) {
        dist[graph[node][i]] = dist[node] + 1;
        q.push(graph[node][i]);
      }
    }
  }
}

int main() {
//  freopen("guilds.in", "r", stdin);

  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  for (int i = 1; i <= n; ++i) {
    if (graph[i].size() == 0) {
      printf("NIE\n");
      return 0;
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (!dist[i]) {
      BFS(i);
    }
  }

  printf("TAK\n");
  for (int i = 1; i <= n; ++i) {
    printf("%c\n", dist[i] % 2 ? 'K' : 'S');
  }

  return 0;
}
