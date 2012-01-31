#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 200010;
const int MAX_HASH = 3;
const int HASH_MOD = 666013;
const int MOD[MAX_HASH] = {HASH_MOD, 167772161, 175781251};
const int BASE[MAX_HASH] = {29, 71, 127};

int n;
int a[MAX_N];
int hash_left[MAX_HASH][MAX_N], hash_right[MAX_HASH][MAX_N];
int base[MAX_HASH][MAX_N];
vector<pair<int, int> > hash[HASH_MOD];

void ComputeBasePowers() {
  for (int j = 0; j < MAX_HASH; ++j) {
    base[j][0] = 1;
    for (int i = 1; i <= n; ++i) {
      base[j][i] = ((long long) base[j][i-1] * BASE[j]) % MOD[j];
    }
  }
}

void BuildHash(int hash[MAX_HASH][MAX_N], int start, int end, int delta) {
  for (int i = start; i != end; i += delta) {
    for (int j = 0; j < MAX_HASH; ++j) {
      hash[j][i] = ((long long) hash[j][i-delta] * BASE[j] + a[i]) % MOD[j];
    }
  }
}

pair<int, pair<int, int> > GetHashValue(int start, int len, int dir) {
  int result[MAX_HASH];

  for (int j = 0; j < MAX_HASH; ++j) {
    if (dir == 0) {
      int red = ((long long) hash_left[j][start-1] * base[j][len]) % MOD[j];
      result[j] = hash_left[j][start+len-1] - red;
      if (result[j] < 0) {
        result[j] += MOD[j];
      }
    } else {
      int red = ((long long) hash_right[j][start+1] * base[j][len]) % MOD[j];
      result[j] = hash_right[j][start-len+1] - red;
      if (result[j] < 0) {
        result[j] += MOD[j];
      }
    }
  }

  return make_pair(result[0], make_pair(result[1], result[2]));
}

int SearchHash(int key, pair<int, int> value) {
  for (size_t i = 0; i < hash[key].size(); ++i) {
    if (hash[key][i] == value) {
      return 1;
    }
  }
  return 0;
}

void AddHash(int key, pair<int, int> value) {
  hash[key].push_back(value);
}

int CountDistinctSubsequences(int len) {
  int result = 0;
  vector<int> keys;
  for (int i = 1; i+len-1 <= n; i += len) {
    pair<int, pair<int, int> > seq = GetHashValue(i, len, 0);
    pair<int, pair<int, int> > rev = GetHashValue(i+len-1, len, 1);
    if (!SearchHash(seq.first, seq.second) && !SearchHash(rev.first, rev.second)) {
      ++result;
      AddHash(seq.first, seq.second);
      keys.push_back(seq.first);
    }
  }

  for (size_t i = 0; i < keys.size(); ++i) {
    hash[keys[i]].clear();
  }

  return result;
}

int main() {
//  freopen("beads.in", "r", stdin);

  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }

  ComputeBasePowers();
  BuildHash(hash_left, 1, n+1, 1);
  BuildHash(hash_right, n, 0, -1);

  int best = 0;
  vector<int> solutions;
  for (int i = 1; i <= n; ++i) {
    int count = CountDistinctSubsequences(i);
    if (count > best) {
      best = count;
      solutions.clear();
    }
    if (best == count) {
      solutions.push_back(i);
    }
  }

  printf("%d %d\n", best, solutions.size());
  for (size_t i = 0; i < solutions.size(); ++i) {
    printf("%d ", solutions[i]);
  }
  printf("\n");

  return 0;
}
