#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 150010;
const int MAX_TREE = 1 << 19;

int n, m, tax;
int position[MAX_N];
int prob[MAX_N];
long long sum[MAX_TREE], best[MAX_TREE], left_sum[MAX_TREE], right_sum[MAX_TREE];

void BuildTrees(int left, int right, int node) {
  if (left == right) {
    sum[node] = 50LL*(position[left+1]-position[left]) - tax*prob[left];
    left_sum[node] = right_sum[node] = best[node] = max(0LL, sum[node]);
  } else {
    int middle = (left+right) / 2;
    BuildTrees(left, middle, node*2);
    BuildTrees(middle+1, right, node*2+1);

    sum[node] = sum[node*2] + sum[node*2+1];
    left_sum[node] = max(left_sum[node*2], sum[node*2] + left_sum[node*2+1]);
    right_sum[node] = max(right_sum[node*2+1], sum[node*2+1] + right_sum[node*2]);
    best[node] = max(max(best[node*2], best[node*2+1]), right_sum[node*2]+left_sum[node*2+1]);
  }
}

void Query(int left, int right, int node, int query_left, int query_right,
           long long &best_, long long &sum_, long long &left_sum_, long long &right_sum_) {
  if (query_left <= left && right <= query_right) {
    best_ = best[node];
    sum_ = sum[node];
    left_sum_ = left_sum[node];
    right_sum_ = right_sum[node];
  } else {
    int middle = (left+right) / 2;
    long long best1 = 0, best2 = 0, sum1 = 0, sum2 = 0;
    long long left_sum1 = 0, left_sum2 = 0, right_sum1 = 0, right_sum2 = 0;
    if (query_left <= middle) {
      Query(left, middle, node*2, query_left, query_right, best1, sum1, left_sum1, right_sum1);
    }
    if (query_right > middle) {
      Query(middle+1, right, node*2+1, query_left, query_right, best2, sum2, left_sum2, right_sum2);
    }

    sum_ = sum1 + sum2;
    left_sum_ = max(left_sum1, sum1 + left_sum2);
    right_sum_ = max(right_sum2, sum2 + right_sum1);
    best_ = max(max(best1, best2), right_sum1+left_sum2);
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("c.in", "r", stdin);
#endif

  scanf("%d %d %d", &n, &m, &tax);

  for (int i = 1; i <= n; ++i) {
    scanf("%d ", &position[i]);
  }
  for (int i = 1; i < n; ++i) {
    scanf("%d ", &prob[i]);
  }

  BuildTrees(1, n-1, 1);

  long long solution = 0;
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    long long best_ = 0, sum_ = 0, left_sum_ = 0, right_sum_ = 0;
    Query(1, n-1, 1, x, y-1, best_, sum_, left_sum_, right_sum_);
    solution +=  best_;
  }

  printf("%.10lf\n", solution / 100.0);

  return 0;
}
