#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 510;

int n, m, task_time, total_time, pairs;
long long penalty;
vector<int> graph[MAX_N];
int matchable[MAX_N], computers[MAX_N];
int matched[MAX_N], visited[2*MAX_N];
int computer_type[2*MAX_N], computer_start_time[2*MAX_N];

int DFS(int node, int marker) {
  if (visited[node] == marker) {
    return 0;
  }
  visited[node] = marker;
  int real_node = computer_type[node];
  for (vector<int> :: iterator it = graph[real_node].begin(); it != graph[real_node].end(); ++it) {
    if (matched[*it] == 0) {
      matched[*it] = node;
      return 1;
    }
  }
  for (vector<int> :: iterator it = graph[real_node].begin(); it != graph[real_node].end(); ++it) {
    if (DFS(matched[*it], marker)) {
      matched[*it] = node;
      return 1;
    }
  }
  return 0;
}

int main() {
//  freopen("contest.in", "r", stdin);
//  freopen("contest.out", "w", stdout);

  scanf("%d %d %d %d %d ", &n, &m, &task_time, &total_time, &pairs);

  for (int i = 1; i <= pairs; ++i) {
    int x, y;
    scanf("%d %d ", &x, &y);
    graph[x].push_back(y);
  }

  int comps = n;
  for (int i = 1; i <= n; ++i) {
    matchable[i] = 1;
    computers[i] = i;
  }

  int matching = 0, new_node = 0;
  for (int step = 1, start_time = 0;
       step <= m && start_time + task_time <= total_time && matching < m && comps > 0;
       ++step, start_time += task_time) {
    for (int i = 1; i <= comps; ++i) {
      ++new_node;
      computer_type[new_node] = computers[i];
      computer_start_time[new_node] = start_time;
      if (DFS(new_node, new_node)) {
        ++matching;
        penalty += start_time + task_time;
      } else {
        matchable[computers[i]] = 0;
      }
    }

    int rem_comps = 0;
    for (int i = 1; i <= comps; ++i) {
      if (matchable[computers[i]]) {
        computers[++rem_comps] = computers[i];
      }
    }
    comps = rem_comps;
  }

  printf("%d %lld\n", matching, penalty);
  for (int i = 1; i <= m; ++i) {
    if (matched[i]) {
      printf("%d %d %d\n", computer_type[matched[i]], i, computer_start_time[matched[i]]);
    }
  }

  return 0;
}
