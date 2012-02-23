#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_N = 1000010;

int n, k;
long long steps;
long long position[MAX_N];
int next[MAX_N], parent[MAX_N], dest[MAX_N];
char visited[MAX_N], on_cycle[MAX_N];
vector<int> graph[MAX_N];
vector<int> stack;

void ComputeNext() {
  int first = 1, last = k+1;
  for (int i = 1; i <= n; ++i) {
    while (last < n && position[i] - position[first] > position[last+1] - position[i]) {
      ++first;
      ++last;
    }

    if (position[i] - position[first] >= position[last] - position[i]) {
      next[i] = first;
      graph[first].push_back(i);
    } else {
      next[i] = last;
      graph[last].push_back(i);
    }
  }
}

void FindCycle(int node) {
  visited[node] = 1;

  if (visited[next[node]] == 0) {
    FindCycle(next[node]);
    if (on_cycle[node]) {
      dest[node] = parent[dest[next[node]]];
    }
  } else if (visited[next[node]] == 1) {
    vector<int> cycle;
    int head = node;
    do {
      cycle.push_back(node);
      on_cycle[node] = 1;
      parent[next[node]] = node;
      node = next[node];
    } while (node != head);
    dest[node] = cycle[steps % cycle.size()];
  }

  visited[node] = 2;
}

void SolveCycles() {
  memset(visited, 0, sizeof(visited));

  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      FindCycle(i);
    }
  }
}

void DFS(int node) {
  if (steps <= stack.size()) {
    dest[node] = stack[stack.size() - steps];
  } else {
    dest[node] = parent[dest[next[node]]];
  }

  visited[node] = 1;
  stack.push_back(node);

  for (size_t i = 0; i < graph[node].size(); ++i) {
    if (!on_cycle[graph[node][i]] && !visited[graph[node][i]]) {
      DFS(graph[node][i]);
    }
  }

  stack.pop_back();
}

void SolveRest() {
  memset(visited, 0, sizeof(visited));

  for (int i = 1; i <= n; ++i) {
    if (!visited[i] && on_cycle[i]) {
      DFS(i);
    }
  }
}

int main() {
//  freopen("frog.in", "r", stdin);

  scanf("%d %d %lld ", &n, &k, &steps);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld ", &position[i]);
  }

  ComputeNext();
  SolveCycles();
  SolveRest();

  for (int i = 1; i <= n; ++i) {
    printf("%d ", dest[i]);
  }
  printf("\n");

  return 0;
}
