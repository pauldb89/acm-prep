#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_N = 100010;

int n;
long long total_edist, sum_edist;
vector <int> tree[MAX_N];
char visited[MAX_N];
int prob_start[MAX_N], prob_finish[MAX_N];
int cnt[MAX_N];
int edist[MAX_N];

void DFS(int node) {
  visited[node] = 1;
  cnt[node] = 1;
  for (size_t i = 0; i < tree[node].size(); ++i) {
    if (!visited[tree[node][i]]) {
      DFS(tree[node][i]);
      cnt[node] += cnt[tree[node][i]];
    }
  }
}

void CalcExpectedDist(int node) {
  visited[node] = 1;
  for (size_t i = 0; i < tree[node].size(); ++i) {
    if (!visited[tree[node][i]]) {
      edist[tree[node][i]] = edist[node] + cnt[node] - cnt[tree[node][i]];
      sum_edist += (long long) prob_finish[tree[node][i]]*edist[tree[node][i]];
      CalcExpectedDist(tree[node][i]);
    }
  }
}

void CalcTotalExpectedDist(int node) {
  visited[node] = 1;
  total_edist += prob_start[node]*sum_edist;
  for (size_t i = 0; i < tree[node].size(); ++i) {
    if (!visited[tree[node][i]]) {
      sum_edist += (long long) prob_finish[node]*cnt[tree[node][i]];
      cnt[node] -= cnt[tree[node][i]];
      cnt[tree[node][i]] += cnt[node];
      sum_edist -= (long long) prob_finish[tree[node][i]]*cnt[node];
      CalcTotalExpectedDist(tree[node][i]);
      sum_edist += (long long) prob_finish[tree[node][i]]*cnt[node];
      cnt[tree[node][i]] -= cnt[node];
      cnt[node] += cnt[tree[node][i]];
      sum_edist -= (long long) prob_finish[node]*cnt[tree[node][i]];
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("e.in", "r", stdin);
#endif
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    tree[x].push_back(y);
    tree[y].push_back(x);
  }
  int total_prob_start = 0, total_prob_finish = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &prob_start[i], &prob_finish[i]);
    total_prob_start += prob_start[i];
    total_prob_finish += prob_finish[i];
  }
  long long total_prob = (long long) total_prob_start*total_prob_finish;

  DFS(1);
  memset(visited, 0, sizeof(visited));
  CalcExpectedDist(1);
  memset(visited, 0, sizeof(visited));
  CalcTotalExpectedDist(1);

  printf("%.12lf\n", (double) total_edist / total_prob);

  return 0;
}
