#include <cstdio>
#include <map>

using namespace std;

const int MAX_N = 1000010;
const int MAX_TREE = 1 << 21;

int n, m;
int a[MAX_N], next[MAX_N], prev[MAX_N];
map<int, int> hash;
int tree_max[MAX_TREE], tree_min[MAX_TREE];

void ComputePrevNext(int result[], int start, int end, int delta) {
  hash.clear();
  for (int i = start; i != end; i += delta) {
    if (hash.find(a[i]) != hash.end()) {
      result[i] = hash[a[i]];
    } else {
      result[i] = start-delta;
    }
    hash[a[i]] = i;
  }
}

void BuildTrees(int left, int right, int node) {
  if (left == right) {
    tree_max[node] = prev[left];
    tree_min[node] = next[left];
  } else {
    int middle = (left+right) / 2;
    BuildTrees(left, middle, node*2);
    BuildTrees(middle+1, right, node*2+1);
    tree_max[node] = max(tree_max[node*2], tree_max[node*2+1]);
    tree_min[node] = min(tree_min[node*2], tree_min[node*2+1]);
  }
}

pair<int, int> QueryTrees(int left, int right, int node, int query_left, int query_right) {
  if (query_left <= left && right <= query_right) {
    return make_pair(tree_min[node], tree_max[node]);
  } else {
    int middle = (left+right) / 2;
    pair<int, int> result1 = make_pair(n+1, 0), result2 = make_pair(n+1, 0);
    if (query_left <= middle) {
      result1 = QueryTrees(left, middle, node*2, query_left, query_right);
    }
    if (query_right > middle) {
      result2 = QueryTrees(middle+1, right, node*2+1, query_left, query_right);
    }
    return make_pair(min(result1.first, result2.first), max(result1.second, result2.second));
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("5881.in", "r", stdin);
#endif

  scanf("%d %d", &n, &m);
  while (n != 0 || m != 0) {
    for (int i = 1; i <= n; ++i) {
      scanf("%d ", &a[i]);
    }

    ComputePrevNext(prev, 1, n+1, 1);
    ComputePrevNext(next, n, 0, -1);

    BuildTrees(1, n, 1);

    for (int i = 1; i <= m; ++i) {
      int x, y;
      scanf("%d %d", &x, &y);
      pair<int, int> result = QueryTrees(1, n, 1, x, y);
      if (result.first > y && result.second < x) {
        printf("OK\n");
      } else if (result.first <= y) {
        printf("%d\n", a[result.first]);
      } else {
        printf("%d\n", a[result.second]);
      }
    }
    printf("\n");

    scanf("%d %d", &n, &m);
  }

  return 0;
}
