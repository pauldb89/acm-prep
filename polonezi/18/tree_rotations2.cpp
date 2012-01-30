#include <cassert>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>

using namespace std;

const int MAX_TREE = 2000010;
const int MAX_N = 1000010;
const int MAX_BUFFER = 10;

int n, paths_num;
char state[MAX_TREE];
char buffer[MAX_BUFFER];
stack<int> st;
int left[MAX_TREE], right[MAX_TREE], parent[MAX_TREE], size[MAX_TREE];
int root[MAX_N], path[MAX_TREE], min_path[MAX_TREE], label[MAX_TREE];
long long inversions[MAX_TREE];
int leaf[MAX_N], AIB[MAX_N];

int ParseNumber() {
  int result = 0;
  fgets(buffer, MAX_BUFFER, stdin);
  for (int i = 0; buffer[i] >= '0' && buffer[i] <= '9'; ++i) {
    result = result*10 + buffer[i]-'0';
  }
  return result;
}

void BuildTree() {
  int current_index = 1;
  st.push(current_index);
  while (st.size() > 0) {
    int node = st.top();
    if (state[node] == 0) {
      int label = ParseNumber();
      if (label > 0) {
        left[node] = right[node] = 0;
        size[node] = 1;
        ++paths_num;
        path[node] = min_path[node] = paths_num;
        root[path[node]] = node;
        leaf[label] = node;
      } else {
        left[node] = ++current_index;
        parent[left[node]] = node;
        st.push(left[node]);
        state[node] = 1;
        continue;
      }
    } else if (state[node] == 1) {
      right[node] = ++current_index;
      parent[right[node]] = node;
      st.push(right[node]);
      state[node] = 2;
      continue;
    } else {
      size[node] = size[left[node]] + size[right[node]];
      min_path[node] = min_path[left[node]];
      if (size[left[node]] < size[right[node]]) {
        path[node] = path[right[node]];
      } else {
        path[node] = path[left[node]];
      }
      root[path[node]] = node;
    }
    st.pop();
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
//  freopen("tree_rotations2.in", "r", stdin);

  scanf("%d ", &n);
  BuildTree();

  for (int i = 1; i <= n; ++i) {
    int node = parent[root[path[leaf[i]]]];
    int queries = 0;
    while (path[node] > 0) {
      queries <<= 1;
      int left_end, right_end;
      if (size[left[node]] < size[right[node]]) {
        left_end = min_path[right[node]]-1;
        right_end = left_end + size[right[node]];
      } else {
        left_end = min_path[left[node]]-1;
        right_end = left_end + size[left[node]];
      }
      inversions[node] += QueryAIB(right_end) - QueryAIB(left_end);
      node = parent[root[path[node]]];
    }
    UpdateAIB(path[leaf[i]]);
  }

  long long solution = 0;
  for (int i = 1; i < 2*n; ++i) {
    solution += min(inversions[i], (long long) size[left[i]]*size[right[i]] - inversions[i]);
  }
  printf("%lld\n", solution);

  return 0;
}
