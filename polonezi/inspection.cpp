#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_N = 1000010;

int n;
vector<int> tree[MAX_N];
char visited[MAX_N];
int cnt[MAX_N], dist[MAX_N], from[MAX_N], second_dist[MAX_N];
long long cost[MAX_N], sol[MAX_N];

void DFS(int node) {
  visited[node] = 1;
  cnt[node] = 1;
  cost[node] = 0;

  for (vector<int> :: iterator it = tree[node].begin(); it != tree[node].end(); ++it) {
    if (!visited[*it]) {
      DFS(*it);
      cnt[node] += cnt[*it];
      cost[node] += cost[*it] + 2*cnt[*it];
      if (dist[*it]+1 > dist[node]) {
        second_dist[node] = dist[node];
        from[node] = *it;
        dist[node] = dist[*it]+1;
      } else if (dist[*it]+1 > second_dist[node]) {
        second_dist[node] = dist[*it]+1;
      }
    }
  }
}

void ReverseDFS(int node) {
  visited[node] = 1;

  int v = tree[node].front();
  for (vector<int> :: iterator it = tree[node].begin(); it != tree[node].end(); ++it) {
    if (cnt[*it] > cnt[v]) {
      v = *it;
    }
  }

  int rest = n-1-cnt[v];
  if (cnt[v] > rest+1) {
    sol[node] = -1;
  } else if (cnt[v] == rest+1) {
    sol[node] = cost[node];
    sol[node] -= dist[v]+1;
  } else {
    sol[node] = cost[node] - dist[node];
  }

  for (vector<int> :: iterator it = tree[node].begin(); it != tree[node].end(); ++it) {
    if (!visited[*it]) {
      cnt[node] -= cnt[*it];
      cost[node] -= cost[*it] + 2*cnt[*it];
      cnt[*it] += cnt[node];
      cost[*it] += cost[node] + 2*cnt[node];

      int tmp_dist = dist[node];
      if (from[node] == *it) {
        dist[node] = second_dist[node];
      }
      if (dist[node]+1 > dist[*it]) {
        second_dist[*it] = dist[*it];
        from[*it] = node;
        dist[*it] = dist[node] + 1;
      } else if (dist[node]+1 > second_dist[*it]) {
        second_dist[*it] = dist[node]+1;
      }

      ReverseDFS(*it);

      cost[*it] -= cost[node] + 2*cnt[node];
      cnt[*it] -= cnt[node];
      cost[node] += cost[*it] + 2*cnt[*it];
      cnt[node] += cnt[*it];
      dist[node] = tmp_dist;
    }
  }
}

int main() {
  // freopen("inspection.in", "r", stdin);
  // freopen("inspection.out", "w", stdout);

  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int x, y;
    scanf("%d %d ", &x, &y);
    tree[x].push_back(y);
    tree[y].push_back(x);
  }

  if (n > 1) {
    DFS(1);
    memset(visited, 0, sizeof(visited));
    ReverseDFS(1);
  }

  for (int i = 1; i <= n; ++i) {
    printf("%lld\n", sol[i]);
  }

  return 0;
}
