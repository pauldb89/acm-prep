#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 500010;
const int MAX_TREE = 1<<21;
const int MAX_BUFFER = 3500010;

int n, m, result;
int number[MAX_N], parent[MAX_N];
char buffer[MAX_BUFFER];
char sign[MAX_N];
int max_tree[MAX_TREE], position[MAX_TREE];
int newer_value[MAX_TREE], newer_value_pos[MAX_TREE];
vector<int> solution;

void ExtendNewerValues(int node, int son) {
  if (newer_value[node] > newer_value[son]) {
    newer_value[son] = newer_value[node];
    newer_value_pos[son] = newer_value_pos[node];
  }
}

void UpdateTreeValue(int node) {
  if (max_tree[node*2] > max_tree[node]) {
    max_tree[node] = max_tree[node*2];
    position[node] = position[node*2];
  }
  if (max_tree[node*2+1] > max_tree[node]) {
    max_tree[node] = max_tree[node*2+1];
    position[node] = position[node*2+1];
  }
}

void UpdateWithNewerValue(int node) {
  if (max_tree[node] < newer_value[node]) {
    max_tree[node] = newer_value[node];
    position[node] = newer_value_pos[node];
  }
}

pair<int, int> Query(int left, int right, int node, int query_pos) {
  if (left == right) {
    UpdateWithNewerValue(node);
    return make_pair(max_tree[node], position[node]);
  } else {
    int middle = (left+right) / 2;
    pair<int, int> result;

    if (newer_value[node] > 0) {
      ExtendNewerValues(node, node*2);
      ExtendNewerValues(node, node*2+1);
      newer_value[node] = 0;
      newer_value_pos[node] = 0;
    }

    if (query_pos <= middle) {
      result = Query(left, middle, node*2, query_pos);
    } else {
      result = Query(middle+1, right, node*2+1, query_pos);
    }
    UpdateTreeValue(node);

    return result;
  }
}

void Update(int left, int right, int node, int query_left, int query_right, int new_value, int new_pos) {
  if (query_left <= left && right <= query_right) {
    if (new_value > newer_value[node]) {
      newer_value[node] = new_value;
      newer_value_pos[node] = new_pos;
    }
    UpdateWithNewerValue(node);
  } else {
    int middle = (left+right) / 2;

    if (newer_value[node] > 0) {
      ExtendNewerValues(node, node*2);
      ExtendNewerValues(node, node*2+1);
      newer_value[node] = 0;
      newer_value_pos[node] = 0;
    }
    
    if (query_left <= middle) {
      Update(left, middle, node*2, query_left, query_right, new_value, new_pos);
    }
    if (query_right > middle) {
      Update(middle+1, right, node*2+1, query_left, query_right, new_value, new_pos);
    }

    UpdateTreeValue(node);
  }
}

int Read(int &index) {
  int result = 0;
  while (!(buffer[index] >= '0' && buffer[index] <= '9')) {
    ++index;
  }
  while (buffer[index] >= '0' && buffer[index] <= '9') {
    result = result * 10 + buffer[index] - '0';
    ++index;
  }
  return result;
}

int main() {
//  freopen("monotonicity.in", "r", stdin);

  scanf("%d %d ", &n, &m);

  int max_number = 0;
  fgets(buffer, MAX_BUFFER, stdin);
  int buffer_index = 0;
  for (int i = 1; i <= n; ++i) {
    number[i] = Read(buffer_index);
    max_number = max(max_number, number[i]);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%c ", &sign[i]);
  }
  for (int i = m+1; i <= n; ++i) {
    sign[i] = sign[i-m];
  }

  int last_pos = 0;
  for (int i = 1; i <= n; ++i) {
    pair<int, int> answer = Query(1, max_number, 1, number[i]);
    int new_value = answer.first + 1;
    parent[i] = answer.second;
    if (new_value > result) {
      result = new_value;
      last_pos = i;
    }
    if (sign[new_value] == '=') {
      Update(1, max_number, 1, number[i], number[i], new_value, i);
    } else if (sign[new_value] == '<') {
      if (number[i] + 1 <= max_number) {
        Update(1, max_number, 1, number[i]+1, max_number, new_value, i);
      }
    } else {
      if (number[i] > 1) {
        Update(1, max_number, 1, 1, number[i]-1, new_value, i);
      }
    }
  }

  while (last_pos > 0) {
    solution.push_back(number[last_pos]);
    last_pos = parent[last_pos];
  }

  printf("%d\n", solution.size());
  for (int i = solution.size()-1; i >= 0; --i) {
    printf("%d ", solution[i]);
  }
  printf("\n");

  return 0;
}
