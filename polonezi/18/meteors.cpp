#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 300010;
const int MAX_TREE = 1 << 20;
const long long INF = 1e18;

int planets, len, updates;
vector<int> orbits[MAX_N];
int quantity[MAX_N];
pair<pair<int, int>, int> update[MAX_N];
int solution[MAX_N], front[MAX_N], back[MAX_N], middle[MAX_N];
long long tree[MAX_TREE];

void ClearTree(int node, int left, int right) {
  tree[node] = 0;
  if (left < right) {
    int mid = (left+right) / 2;
    ClearTree(node*2, left, mid);
    ClearTree(node*2+1, mid+1, right);
  }
}

void UpdateTree(int query_left, int query_right, int value, int node, int left, int right) {
  if (query_left <= left && right <= query_right) {
    tree[node] += value;
  } else {
    int mid = (left+right) / 2;
    if (query_left <= mid) {
      UpdateTree(query_left, query_right, value, node*2, left, mid);
    }
    if (query_right > mid) {
      UpdateTree(query_left, query_right, value, node*2+1, mid+1, right);
    }
  }
}

long long QueryTree(int position, int node, int left, int right) {
  if (left == right) {
    return tree[node];
  } else {
    int mid = (left+right) / 2;
    if (position <= mid) {
      return min(QueryTree(position, node*2, left, mid) + tree[node], INF);
    } else {
      return min(QueryTree(position, node*2+1, mid+1, right) + tree[node], INF);
    }
  }
}

int main() {
//  freopen("meteors.in", "r", stdin);

  scanf("%d %d", &planets, &len);
  for (int i = 1; i <= len; ++i) {
    int x;
    scanf("%d", &x);
    orbits[x].push_back(i);
  }
  for (int i = 1; i <= planets; ++i) {
    scanf("%d", &quantity[i]);
  }
  scanf("%d", &updates);
  for (int i = 1; i <= updates; ++i) {
    int x, y, value;
    scanf("%d %d %d", &x, &y, &value);
    update[i] = make_pair(make_pair(x, y), value);
  }

  for (int i = 1; i <= planets; ++i) {
    front[i] = 1;
    back[i] = updates;
    solution[i] = updates+1;
  }

  for (int step = 0; 1 << step <= updates; ++step) {
    ClearTree(1, 1, len);
    vector<pair<int, int> > events;
    for (int i = 1; i <= planets; ++i) {
      if (front[i] <= back[i]) {
        middle[i] = (front[i] + back[i]) / 2;
        events.push_back(make_pair(middle[i], i));
      }
    }
    sort(events.begin(), events.end());
    for (int i = 1, j = 0; i <= updates; ++i) {
      int left = update[i].first.first;
      int right = update[i].first.second;
      int value = update[i].second;
      if (left <= right) {
        UpdateTree(left, right, value, 1, 1, len);
      } else {
        UpdateTree(left, len, value, 1, 1, len);
        UpdateTree(1, right, value, 1, 1, len); 
      }

      while (j < (int) events.size() && events[j].first == i) {
        int planet = events[j].second;
        long long sum = 0;
        for (size_t k = 0; k < orbits[planet].size(); ++k) {
          sum = min(sum + QueryTree(orbits[planet][k], 1, 1, len), INF);
        }

        if (sum >= quantity[planet]) {
          solution[planet] = i;
          back[planet] = middle[planet] - 1;
        } else {
          front[planet] = middle[planet] + 1;
        }
        ++j;
      }
    }
  }

  for (int i = 1; i <= planets; ++i) {
    if (solution[i] == updates+1) {
      printf("NIE\n");
    } else {
      printf("%d\n", solution[i]);
    }
  }

  return 0;
}
