#include <cstdio>
#include <vector>

using namespace std;

const int MAX_TREE = 400010;
const int MAX_N = 200010;

int n, current_index, cnt_leaves;
int left[MAX_TREE], right[MAX_TREE], size[MAX_TREE];
int label[MAX_TREE], min_position[MAX_TREE];
long long left_inv[MAX_TREE], right_inv[MAX_TREE];
int position[MAX_N], AIB[MAX_N];
vector<pair<pair<int, int>, pair<int, int> > > queries[MAX_N], current_queries;

void BuildTree() {
  int node = ++current_index, value;
  scanf("%d", &value);
  if (value > 0) {
    left[node] = right[node] = 0;
    size[node] = 1;
    label[node] = value;
    position[value] = ++cnt_leaves;
    min_position[node] = position[value];
  } else {
    left[node] = current_index+1;
    BuildTree();
    right[node] = current_index+1;
    BuildTree();
    size[node] = size[left[node]] + size[right[node]];
    min_position[node] = min_position[left[node]];
  }
}

pair<int, int> MakeInterval(int left_end, int length) {
  return make_pair(left_end-1, left_end+length-1);
}

void SetQueries() {
  int node = ++current_index;
  if (label[node] > 0) {
    queries[label[node]] = current_queries;
  } else {
    if (size[left[node]] < size[right[node]]) {
      current_queries.push_back(make_pair(
          MakeInterval(min_position[right[node]], size[right[node]]),
          make_pair(node, 0)));
      SetQueries();
      current_queries.pop_back();
      SetQueries();
    } else {
      SetQueries();
      current_queries.push_back(make_pair(
          MakeInterval(min_position[left[node]], size[left[node]]),
          make_pair(node, 1)));
      SetQueries();
      current_queries.pop_back();
    }
  }
}

int LSB(int x) {
  return (x&(x-1))^x;
}

int QueryAIB(int position) {
  int result = 0;
  while (position > 0) {
    result += AIB[position];
    position -= LSB(position);
  }
  return result;
}

void UpdateAIB(int position) {
  while (position <= n) {
    ++AIB[position];
    position += LSB(position);
  }
}

int main() {
//  freopen("tree_rotations.in", "r", stdin);

  scanf("%d", &n);
  current_index = 0;
  BuildTree();

  current_index = 0;
  SetQueries();

  for (int i = 1; i <= n; ++i) {
    for (size_t j = 0; j < queries[i].size(); ++j) {
      int left_end = queries[i][j].first.first;
      int right_end = queries[i][j].first.second;
      int dest = queries[i][j].second.first;
      int type = queries[i][j].second.second;
      int result = QueryAIB(right_end) - QueryAIB(left_end);
      if (type == 0) {
        left_inv[dest] += result;
        right_inv[dest] += size[right[dest]] - result;
      } else {
        left_inv[dest] += size[left[dest]] - result;
        right_inv[dest] += result;
      }
    }
    UpdateAIB(position[i]);
  }

  long long solution = 0;
  for (int i = 1; i <= 2*n-1; ++i) {
    solution += min(left_inv[i], right_inv[i]);
  }
  printf("%lld\n", solution);

  return 0;
}
