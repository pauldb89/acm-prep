#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 100010;
const int MAX_M = 1000010;

int n, m;
vector<pair<int, int> > graph[MAX_N];
char degree[MAX_N], marked[MAX_N];
int pos[MAX_N];
char visited[MAX_M];
vector<int> output, stack;
vector<vector<int> > cycles;

inline void DFS(int node) {
  stack.push_back(node);
  while (stack.size() > 0) {
    int node = stack.back();
    int erase = 1;
    while (pos[node] < graph[node].size()) {
      pair<int, int> p = graph[node][pos[node]];
      ++pos[node];
      if (!visited[p.second]) {
        stack.push_back(p.first);
        visited[p.second] = 1;
        erase = 0;
        break;
      }
    }
    if (erase) {
      node = stack.back();
      stack.pop_back();
      output.push_back(node);
      if (marked[node]) {
        cycles.push_back(vector<int>());
        do {
          cycles.back().push_back(output.back());
          marked[output.back()] = 0;
          output.pop_back();
        } while (output.back() != node);
        cycles.back().push_back(node);
      }
      marked[node] = 1;
    }
  }
}

int main() {
  // freopen("garbage.in", "r", stdin);

  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int x, y, init_value, final_value;
    scanf("%d %d %d %d", &x, &y, &init_value, &final_value);
    if (init_value ^ final_value) {
      graph[x].push_back(make_pair(y, i));
      graph[y].push_back(make_pair(x, i));
      degree[x] ^= 1;
      degree[y] ^= 1;
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (degree[i]) {
      printf("NIE\n");
      return 0;
    }
  }

  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      DFS(i);
    }
  }

  printf("%d\n", cycles.size());
  for (size_t i = 0; i < cycles.size(); ++i) {
    printf("%d ", cycles[i].size()-1);
    for (size_t j = 0; j < cycles[i].size(); ++j) {
      printf("%d ", cycles[i][j]);
    }
    printf("\n");
  }

  return 0;
}
