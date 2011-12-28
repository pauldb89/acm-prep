#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX_N = 100010;

int n;
vector<pair<int, int> > graph[MAX_N];
int visited[MAX_N];

int IsLuckyNumber(int x) {
  while (x) {
    int digit = x % 10;
    if (digit != 4 && digit != 7) {
      return 0;
    }
    x /= 10;
  }
  return 1;
}

int BFS(int node) {
  int result = 1;
  queue<int> q;
  q.push(node);
  visited[node] = 1;

  while (!q.empty()) {
    node = q.front();
    q.pop();
    for (size_t i = 0; i < graph[node].size(); ++i) {
      if (!visited[graph[node][i].first] && !IsLuckyNumber(graph[node][i].second)) {
        ++result;
        visited[graph[node][i].first] = 1;
        q.push(graph[node][i].first);
      }
    }
  }
  return result;
}

int main() {
#ifndef ONLINE_JUDGE
  ifstream cin("c.in");
#endif

  cin >> n;
  for (int i = 1; i < n; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    graph[x].push_back(make_pair(y, z));
    graph[y].push_back(make_pair(x, z));
  }

  long long sol = 0;
  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      int d = BFS(i);
      sol += (long long) d*(n-d)*(n-d-1);
    }
  }

  cout << sol << '\n';

  return 0;
}
