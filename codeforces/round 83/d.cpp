#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int SIGMA = 26;
const int MOD = 12345;
const int MAX_CONFIGS = 125;

long long n;
int total_configs, sol;
vector<int> restrictions[SIGMA];
int mult[SIGMA];
map<vector<int>, int> config_map;
int mat[MAX_CONFIGS][MAX_CONFIGS], result[MAX_CONFIGS][MAX_CONFIGS];

void ReadInput() {
#ifndef ONLINE_JUDGE
  ifstream cin("d.in");
#endif

  int conditions;
  cin >> n >> conditions;
  for (int i = 0; i < SIGMA; ++i) {
    mult[i] = 1;
  }
  for (int i = 1; i <= conditions; ++i) {
    char letter;
    int multiple;
    cin >> letter >> multiple;
    mult[letter-'A'] *= multiple;
    restrictions[letter-'A'].push_back(multiple);
  }
}

void GenerateConfigurations(int pos, vector<int> &config) {
  if (pos == SIGMA) {
    config_map[config] = ++total_configs;
  } else {
    for (int i = 0; i < mult[pos]; ++i) {
      config.push_back(i);
      GenerateConfigurations(pos+1, config);
      config.pop_back();
    }
  }
}

void BuildMatrix() {
  for (map<vector<int>, int> :: iterator it = config_map.begin(); it != config_map.end(); ++it) {
    vector<int> config = it->first;
    int index = it->second;
    for (int j = 0; j < SIGMA; ++j) {
      if (restrictions[j].size() > 0) {
        int tmp = config[j];
        config[j] = (config[j]+1) % mult[j];
        ++mat[index][config_map[config]];
        config[j] = tmp;
      }
    }
  }
}

void MultiplyMatrix(int a[][MAX_CONFIGS], int b[][MAX_CONFIGS], int c[][MAX_CONFIGS]) {
  int tmp[MAX_CONFIGS][MAX_CONFIGS];
  memset(tmp, 0, sizeof(tmp));
  for (int k = 1; k <= total_configs; ++k) {
    for (int i = 1; i <= total_configs; ++i) {
      for (int j = 1; j <= total_configs; ++j) {
        tmp[i][j] = (tmp[i][j] + b[i][k]*c[k][j]) % MOD;
      }
    }
  }
  memcpy(a, tmp, sizeof(tmp));
}

void RaiseToPower(long long n) {
  for (int i = 1; i <= total_configs; ++i) {
    result[i][i] = 1;
  }

  while (n > 0) {
    if (n&1) {
      MultiplyMatrix(result, result, mat);
    }
    MultiplyMatrix(mat, mat, mat);
    n >>= 1;
  }
}

void CountSolutions() {
  for (map<vector<int>, int> :: iterator it = config_map.begin(); it != config_map.end(); ++it) {
    vector<int> config = it->first;
    int index = it->second;
    int is_valid_config = 1;
    for (int j = 0; j < SIGMA; ++j) {
      if (restrictions[j].size() > 0) {
        int is_multiple = 0;
        for (size_t k = 0; k < restrictions[j].size(); ++k) {
          if (config[j] % restrictions[j][k] == 0) {
            is_multiple = 1;
            break;
          }
        }
        if (!is_multiple) {
          is_valid_config = 0;
          break;
        }
      }
    }
    if (is_valid_config) {
      sol = (sol + result[index][1]) % MOD;
    }
  }
}

int main() {
  ReadInput();
  vector<int> config;
  GenerateConfigurations(0, config);
  BuildMatrix();
  RaiseToPower(n);
  CountSolutions();
  cout << sol << endl;
  return 0;
}
