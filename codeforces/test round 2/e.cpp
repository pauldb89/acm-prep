#include <algorithm>
#include <cassert>
#include <cstdio>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const int MAX_N = 5010;
const int INF = 1000000;
const double EPS = 0.5;

int n, m, k;
vector<pair<pair<int, int>, int> > edges;
vector<int> graph[MAX_N];
int visited[MAX_N];

int FindRoot(vector<int>& parent, int node) {
  if (parent[node] != node) {
    parent[node] = FindRoot(parent, parent[node]);
  }
  return parent[node];
}

vector<int> FinishMST(double delta, vector<int>& parent, vector<int>& mst, int is_started) {
  vector<pair<pair<double, int>, pair<int, int> > > tmp_edges;
  for (size_t i = 0; i < edges.size(); ++i) {
    if (edges[i].first.first == 1 || edges[i].first.second == 1) {
      if (!is_started) {
        tmp_edges.push_back(make_pair(make_pair(edges[i].second-delta, i), edges[i].first));
      }
    } else {
      tmp_edges.push_back(make_pair(make_pair(edges[i].second, i), edges[i].first));
    }
  }
  sort(tmp_edges.begin(), tmp_edges.end());

  for (size_t i = 0; i < tmp_edges.size(); ++i) {
    int x = tmp_edges[i].second.first;
    int y = tmp_edges[i].second.second;
    if (FindRoot(parent, x) != FindRoot(parent, y)) {
      mst.push_back(tmp_edges[i].first.second);
      parent[parent[x]] = parent[y];
    }
  }
  return mst;
}

vector<int> BuildMST(double delta) {
  vector<int> parent(n+1);
  for (int i = 1; i <= n; ++i) {
    parent[i] = i;
  }
  vector<int> mst;
  return FinishMST(delta, parent, mst, 0);
}

int FindMSTDegree(double delta) {
  vector <int> mst = BuildMST(delta);
  int degree = 0;
  for (size_t i = 0; i < mst.size(); ++i) {
    degree += edges[mst[i]].first.first == 1 || edges[mst[i]].first.second == 1;
  }
  return degree;
}

set<int> BuildSet(const vector<int>& mst) {
  set<int> result;
  for (size_t i = 0; i < mst.size(); ++i) {
    if (edges[mst[i]].first.first == 1 || edges[mst[i]].first.second == 1) {
      result.insert(mst[i]);
    }
  }
  return result;
}

vector<int> BuildKthDegreeMST(int best) {
  vector <int> mst;
  vector<int> higher_mst = BuildMST(best+EPS);
  vector<int> lower_mst = BuildMST(best-EPS);
  set<int> optional_edges = BuildSet(higher_mst);
  set<int> fixed_edges = BuildSet(lower_mst);
  int extra_edges = k - FindMSTDegree(best-EPS);
  vector <int> parent(n+1);
  for (int i = 1; i <= n; ++i) {
    parent[i] = i;
  }
  for (size_t i = 0; i < edges.size(); ++i) {
    if (edges[i].first.first == 1 || edges[i].first.second == 1) {
      if (fixed_edges.find(i) != fixed_edges.end()) {
        mst.push_back(i);
        parent[edges[i].first.first] = parent[edges[i].first.second] = 1;
      } else if (extra_edges > 0 && optional_edges.find(i) != optional_edges.end()) {
        --extra_edges;
        mst.push_back(i);
        parent[edges[i].first.first] = parent[edges[i].first.second] = 1;
      }
    }
  }

  return FinishMST(best, parent, mst, 1);
}

int BFS(int start_node) {
  int result = 0;
  queue<int> q;
  q.push(start_node);
  visited[start_node] = 1;

  while (!q.empty()) {
    int node = q.front();
    q.pop();
    for (size_t i = 0; i < graph[node].size(); ++i) {
      if (!visited[graph[node][i]]) {
        if (graph[node][i] != 1) {
          visited[graph[node][i]] = 1;
          q.push(graph[node][i]);
        } else {
          result = 1;
        }
      }
    }
  }
  return result;
}

int FindMinimumDegree() {
  int min_degree = 0, is_connected = 1;
  for (int i = 2; i <= n; ++i) {
    if (!visited[i]) {
      ++min_degree;
      is_connected |= BFS(i);
    }
  }
  if (!is_connected) {
    return n+1;
  }
  return min_degree;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("e.in", "r", stdin);
#endif

  scanf("%d %d %d", &n, &m, &k);
  int max_roads = 0;
  for (int i = 0; i < m; ++i) {
    int x, y, cost;
    scanf("%d %d %d", &x, &y, &cost);
    graph[x].push_back(y);
    graph[y].push_back(x);
    edges.push_back(make_pair(make_pair(x, y), cost));
    if (x == 1 || y == 1) {
      ++max_roads;
    }
  }

  if (k < FindMinimumDegree() || k > max_roads) {
    printf("-1\n");
    return 0;
  }

  int best = INF;
  int front = -INF, back = INF;
  while (front <= back) {
    int middle = (front+back) / 2;
    if (FindMSTDegree(middle+EPS) >= k) {
      best = middle;
      back = middle-1;
    } else {
      front = middle+1;
    }
  }

  vector<int> mst = BuildKthDegreeMST(best);
  printf("%d\n", mst.size());
  //assert(mst.size() == n-1);
  for (size_t i = 0; i+1 < mst.size(); ++i) {
    printf("%d ", mst[i]+1);
  }
  if (mst.size() > 0) {
    printf("%d\n", mst.back()+1);
  }

  return 0;
}
