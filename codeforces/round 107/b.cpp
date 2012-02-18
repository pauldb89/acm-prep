#include <cstdio>
#include <vector>

using namespace std;

const int MOD = 1000000007;
const int MAX_N = 2010;

int n, m, k;
int visited[MAX_N];
vector<int> graph[MAX_N];

void DFS(int node) {
  visited[node] = 1;
  for (size_t i = 0; i < graph[node].size(); ++i) {
    if (!visited[graph[node][i]]) {
      DFS(graph[node][i]);
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("b.in", "r", stdin);
#endif

  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n-k+1; ++i) {
    int left = i;
    int right = i+k-1;
    while (left < right) {
      graph[left].push_back(right);
      graph[right].push_back(left);
      ++left;
      --right;
    }
  }

  int solution = 1;
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      DFS(i);
      solution = ((long long) solution * m) % MOD;
    }
  }

  printf("%d\n", solution);

  return 0;
}
