#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>

using namespace std;

const int MAX_N = 100010;

int n, m;
vector<int> graph[MAX_N], tree[MAX_N];
char visited[MAX_N];
stack<int> st;

vector<vector<int> > paths;
// active_nodes[path][node] = numarul de noduri active din interval corespunzator lui node de pe
// lantul path
vector<vector<int> > active_nodes;
// interval_value[path][node] = 1 <=> valorile din intregul interval si-au schimbat starea, dar
// active_nodes nu a fost actualizat
vector<vector<char> > interval_value;
int level[MAX_N]; // level[i] = nivelul nodului i in arbore
int parent[MAX_N]; // parent[i] = parintele nodului i
int path[MAX_N]; // path[i] = indicele drumului pe care se afla nodul i
int pos[MAX_N]; // pos[i] = pozitia nodului i pe lant (frunza este indexata cu 1)
int root[MAX_N]; // root[i] = cel mai dinspre radacina nod de pe drumul i
int dp[MAX_N]; // dp[i] = numarul de noduri din subarborele lui i

int root_from_cycle[MAX_N]; // root_from_cycle[i] = nodul de pe ciclu sub care se afla nodul i

int total_active_tree_nodes;

void FindCycle(int node, int parent) {
  visited[node] = 1;
  st.push(node);
  for (size_t i = 0; i < graph[node].size(); ++i) {
    if (!visited[graph[node][i]]) {
      FindCycle(graph[node][i], node);
    } else if (visited[graph[node][i]] == 1 && graph[node][i] != parent) {
      vector <int> cycle;
      while (st.top() != graph[node][i]) {
        path[st.top()] = 0;
        pos[st.top()] = cycle.size();
        cycle.push_back(st.top());
        st.pop();
      }
      path[graph[node][i]] = 0;
      pos[graph[node][i]] = cycle.size();
      cycle.push_back(graph[node][i]);
      paths.push_back(cycle);
    }
  }
  if (!st.empty()) {
    st.pop();
  }
  visited[node] = 2;
}

void BuildTree() {
  for (int i = 1; i <= n; ++i) {
    // Daca i nu e pe ciclu
    if (path[i] == -1) {
      for (size_t j = 0; j < graph[i].size(); ++j) {
        // Daca graph[node][i] e pe ciclu
        if (path[graph[i][j]] == 0) {
          tree[i].push_back(0);
          tree[0].push_back(i);
          root_from_cycle[i] = graph[i][j];
        } else {
          tree[i].push_back(graph[i][j]);
        }
      }
    } else {
      root_from_cycle[i] = i;
    }
  }
}

void HeavyPathDecomposition(int node) {
  visited[node] = 1;
  dp[node] = 1;

  int heaviest_son = -1;
  for (size_t i = 0; i < tree[node].size(); ++i) {
    if (!visited[tree[node][i]]) {
      // Preprocesari nelegate de heavy path decomposition 
      if (!root_from_cycle[tree[node][i]]) {
        root_from_cycle[tree[node][i]] = root_from_cycle[node];
      }
      level[tree[node][i]] = level[node]+1;

      // Preprocesari legate de heavy path decomposition
      parent[tree[node][i]] = node;
      HeavyPathDecomposition(tree[node][i]);
      dp[node] += dp[tree[node][i]];
      if (heaviest_son == -1 || dp[tree[node][i]] > dp[heaviest_son]) {
        heaviest_son = tree[node][i];
      }
    }
  }

  if (dp[node] == 1) {
    vector <int> new_path;
    new_path.push_back(node);
    root[paths.size()] = node;
    path[node] = paths.size();
    pos[node] = 0;
    paths.push_back(new_path);
  } else {
    path[node] = path[heaviest_son];
    pos[node] = paths[path[node]].size();
    paths[path[node]].push_back(node);
    root[path[node]] = node;
  }
}

void BuildSegmentTrees() {
  active_nodes.resize(paths.size());
  interval_value.resize(paths.size());
  for (size_t i = 0; i < paths.size(); ++i) {
    active_nodes[i].reserve(4*paths[i].size());
    active_nodes[i].resize(4*paths[i].size());
    interval_value[i].reserve(4*paths[i].size());
    interval_value[i].resize(4*paths[i].size());
  }
}

int FindLCA(int x, int y) {
  while (path[x] != path[y]) {
    if (level[root[path[x]]] > level[root[path[y]]]) {
      x = parent[root[path[x]]];
    } else {
      y = parent[root[path[y]]];
    }
  }

  return (level[x] < level[y]) ? x : y;
}

void UpdateSegmentTree(int path, int query_left, int query_right,
                       int current_left, int current_right, int node) {
  int stop = 0;
  if (query_left <= current_left && current_right <= query_right) {
    interval_value[path][node] ^= 1;
    stop = 1;
  }
  if (interval_value[path][node]) {
    interval_value[path][node] = 0;
    active_nodes[path][node] = current_right-current_left+1 - active_nodes[path][node];
    if (current_left < current_right) {
      interval_value[path][node*2] ^= 1;
      interval_value[path][node*2+1] ^= 1;
    }
  }
  if (!stop) {
    int middle = (current_left+current_right) / 2;
    if (query_left <= middle) {
      UpdateSegmentTree(path, query_left, query_right, current_left, middle, node*2);
    }
    if (query_right > middle) {
      UpdateSegmentTree(path, query_left, query_right, middle+1, current_right, node*2+1);
    }
    
    if (interval_value[path][node*2]) {
      active_nodes[path][node] = middle-current_left+1 - active_nodes[path][node*2];
    } else {
      active_nodes[path][node] = active_nodes[path][node*2];
    }
    if (interval_value[path][node*2+1]) {
      active_nodes[path][node] += current_right-middle - active_nodes[path][node*2+1];
    } else {
      active_nodes[path][node] += active_nodes[path][node*2+1];
    }
  }
}

void QueryTree(int lower_node, int upper_node) {
  while (path[lower_node] != path[upper_node]) {
    total_active_tree_nodes -= active_nodes[path[lower_node]][1];
    UpdateSegmentTree(path[lower_node], pos[lower_node]+1, paths[path[lower_node]].size(),
                      1, paths[path[lower_node]].size(), 1);
    total_active_tree_nodes += active_nodes[path[lower_node]][1];
    lower_node = parent[root[path[lower_node]]];
  }

  total_active_tree_nodes -= active_nodes[path[lower_node]][1];
  UpdateSegmentTree(path[lower_node], pos[lower_node]+1, pos[upper_node]+1,
                    1, paths[path[lower_node]].size(), 1);
  total_active_tree_nodes += active_nodes[path[lower_node]][1];
}

void QueryCycle(int x, int y) {
  int next_pos = pos[x]+1;
  if (next_pos == (int) paths[0].size()) {
    next_pos = 0;
  }
  int prev_pos = pos[x]-1;
  if (prev_pos < 0) {
    prev_pos += paths[0].size();
  }
  if (pos[x] > pos[y]) {
    swap(x, y);
    swap(prev_pos, next_pos);
  }

  int len1 = pos[y]-pos[x];
  int len2 = paths[0].size()-len1;
  if (len1 < len2 || (len1 == len2 && paths[0][next_pos] < paths[0][prev_pos])) {
    if (pos[x]+1 <= pos[y]) {
      UpdateSegmentTree(0, pos[x]+1, pos[y], 1, paths[0].size(), 1);
    }
  } else {
    UpdateSegmentTree(0, pos[y]+1, paths[0].size(), 1, paths[0].size(), 1);
    if (pos[x] > 0) {
      UpdateSegmentTree(0, 1, pos[x], 1, paths[0].size(), 1);
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("e.in", "r", stdin);
#endif

  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  memset(path, -1, sizeof(path));
  FindCycle(1, 0);
  BuildTree();
  memset(visited, 0, sizeof(visited));
  parent[0] = -1;
  HeavyPathDecomposition(0);
  BuildSegmentTrees();

  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d %d ", &x, &y);
    // Testez daca x sau y sunt pe ciclu
    int tree_x = path[x] == 0 ? 0 : x;
    int tree_y = path[y] == 0 ? 0 : y;
    int lca = FindLCA(tree_x, tree_y);
    QueryTree(tree_x, lca);
    QueryTree(tree_y, lca);
    if (lca == 0) {
      QueryCycle(root_from_cycle[x], root_from_cycle[y]);
    }

    int sol = n-paths[0].size() - total_active_tree_nodes;
    sol += max(1, (int) paths[0].size()-active_nodes[0][1]);
    printf("%d\n", sol);
  }

  return 0;
}
