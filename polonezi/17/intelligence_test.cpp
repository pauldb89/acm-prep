#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 1000010;

int n, m;
int a[MAX_N];
vector<vector<int> > subsequences;
vector<size_t> current_index;
vector<int> awaits_value[MAX_N];

int main() {
//  freopen("intelligence_test.in", "r", stdin);

  scanf("%d ", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d ", &a[i]);
  }

  scanf("%d ", &m);
  subsequences.resize(m);
  current_index.resize(m);
  for (int i = 0; i < m; ++i) {
    int len;
    scanf("%d", &len);
    for (int j = 0; j < len; ++j) {
      int x;
      scanf("%d", &x);
      subsequences[i].push_back(x);
    }
    awaits_value[subsequences[i][0]].push_back(i);
  }

  for (int i = 1; i <= n; ++i) {
    vector<int> awaits_current;
    for (vector<int> :: iterator it = awaits_value[a[i]].begin(); it != awaits_value[a[i]].end(); ++it) {
      ++current_index[*it];
      if (current_index[*it] < subsequences[*it].size()) {
        if (subsequences[*it][current_index[*it]] != a[i]) {
          awaits_value[subsequences[*it][current_index[*it]]].push_back(*it);
        } else {
          awaits_current.push_back(*it);
        }
      }
    }
    awaits_value[a[i]] = awaits_current;
  }

  for (int i = 0; i < m; ++i) {
    printf("%s\n", current_index[i] == subsequences[i].size() ? "TAK" : "NIE");
  }

  return 0;
}
