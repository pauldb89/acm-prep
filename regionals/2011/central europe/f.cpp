#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <stack>
#include <vector>

using namespace std;

const int MAX_N = 8010;
const int MAX_COMPS = 110;

struct Interval {
  int head, tail;
  Interval *prev, *next;
  int rev;
  vector<int> values;

  Interval() {
    rev = 0;
    prev = next = NULL;
  }

  Interval(int value) {
    head = tail = value;
    values.push_back(value);
    rev = 0;
    prev = next = NULL;
  }

  void MaybeReverse() {
    if (rev) {
      rev = 0;
      reverse(values.begin(), values.end());
    }
  }
};

int n, m, comps, tests, limit;
map<pair<int, int>, int> edges;
int deg[MAX_COMPS][MAX_N];
Interval *interval[MAX_COMPS][MAX_N];
stack<int> indexes[MAX_COMPS];

int Test(int comp, int x, int y) {
  if (interval[comp][x]->head == x) {
    return interval[comp][x]->tail == y;
  } else {
    return interval[comp][x]->head == y;
  }
}

void Reverse(Interval *interval) {
  Interval *prev = interval;
  Interval *crt = interval->next;
  prev->next = NULL;
  swap(prev->head, prev->tail);
  prev->rev ^= 1;

  while (crt != NULL) {
    swap(crt->head, crt->tail);
    crt->rev ^= 1;
    Interval *next = crt->next;
    crt->next = prev;
    prev->prev = crt;
    prev = crt;
    crt = next;
  }
  prev->prev = NULL;
}

void UpdateEndValues(Interval *interval, int new_head, int new_tail) {
  while (interval != NULL) {
    interval->head = new_head;
    interval->tail = new_tail;
    interval = interval->next;
  }
}

void JoinIntervals(int comp, Interval *I1, Interval *I2) {
  I1->MaybeReverse();
  I2->MaybeReverse();
  for (size_t i = 0; i < I2->values.size(); ++i) {
    I1->values.push_back(I2->values[i]);
    interval[comp][I2->values[i]] = I1;
  }

  I1->next = I2->next;
  if (I2->next != NULL) {
    I2->next->prev = I1;
  }
  delete I2;
}

void Join(int comp, int x, int y) {
  Interval *I1 = interval[comp][x];
  Interval *I2 = interval[comp][y];
  if (I1->head == x) {
    Reverse(interval[comp][x]);
  }
  if (I2->tail == y) {
    Reverse(interval[comp][I2->head]);
  }

  UpdateEndValues(interval[comp][I1->head], I1->head, I2->tail);
  UpdateEndValues(interval[comp][y], I1->head, I2->tail);

  if ((int) (I1->values.size() + I2->values.size()) <= limit) {
    JoinIntervals(comp, interval[comp][x], interval[comp][y]); 
  } else {
    I1->next = I2; 
    I2->prev = I1;
  }
}

void SplitInterval(Interval *I, int comp, int x, int y) {
  I->MaybeReverse();
  int start = 0;
  for (size_t i = 0; i < I->values.size(); ++i) {
    if (I->values[i] == x || I->values[i] == y) {
      start = i+1;
      break;
    }
  }
  Interval *I2 = new Interval();
  for (size_t i = start; i < I->values.size(); ++i) {
    I2->values.push_back(I->values[i]);
    interval[comp][I->values[i]] = I2;
  }
  I->values.resize(start);

  I2->prev = NULL;
  I2->next = I->next;
  if (I->next != NULL) {
    I->next->prev = I2;
  }
  I->next = NULL;

  int left_head = I->head, left_tail = I->values.back();
  int right_head = I2->values.front(), right_tail = I->tail;
  UpdateEndValues(interval[comp][I->head], left_head, left_tail);
  UpdateEndValues(I2, right_head, right_tail);

  if (I->prev != NULL && (int) (I->prev->values.size() + I->values.size()) <= limit) {
    JoinIntervals(comp, I->prev, I);
  }
  if (I2->next != NULL && (int) (I2->values.size() + I2->next->values.size()) <= limit) {
    JoinIntervals(comp, I2, I2->next);
  }
}

void Split(int comp, int x, int y) {
  Interval *I1 = interval[comp][x];
  Interval *I2 = interval[comp][y];
  if (I1 == I2) {
    SplitInterval(I1, comp, x, y);
  } else {
    if (I1->next == I2) {
      I1->next = NULL;
      I2->prev = NULL;
      UpdateEndValues(interval[comp][I1->head], I1->head, x);
      UpdateEndValues(I2, y, I2->tail);
    } else {
      I2->next = NULL;
      I1->prev = NULL;
      UpdateEndValues(interval[comp][I2->head], I2->head, y);
      UpdateEndValues(I1, x, I1->tail);
    }
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("5884.in", "r", stdin);
  freopen("5884.out", "w", stdout);
#endif

  while (1) {
    scanf("%d %d %d %d", &n, &m, &comps, &tests);
    if (n == 0 && m == 0 && comps == 0 && tests == 0) {
      break;
    }

    edges.clear();
    memset(deg, 0, sizeof(deg));
    for (int i = 1; i <= comps; ++i) {
      for (int j = 1; j <= n; ++j) {
        interval[i][j] = new Interval(j);
      }
      indexes[i] = stack<int>();
    }
    limit = 2*sqrt(n);

    for (int i = 1; i <= m; ++i) {
      int x, y, comp;
      scanf("%d %d %d", &x, &y, &comp);
      edges[make_pair(x, y)] = comp;
      ++deg[comp][x];
      ++deg[comp][y];
      Join(comp, x, y);
    }

    for (int i = 1; i <= tests; ++i) {
      int x, y, comp;
      scanf("%d %d %d", &x, &y, &comp);
      if (edges.find(make_pair(x, y)) == edges.end()) {
        printf("No such cable.\n");
      } else if (edges[make_pair(x, y)] == comp) {
        printf("Already owned.\n");
      } else if (deg[comp][x] >= 2 || deg[comp][y] >= 2) {
        printf("Forbidden: monopoly.\n");
      } else if (Test(comp, x, y)) {
        printf("Forbidden: redundant.\n");
      } else {
        printf("Sold.\n");
        int old_comp = edges[make_pair(x, y)];
        Split(old_comp, x, y);
        --deg[old_comp][x];
        --deg[old_comp][y];

        edges[make_pair(x, y)] = comp;
        ++deg[comp][x];
        ++deg[comp][y];
        Join(comp, x, y);
      }
    }
    printf("\n");
  }

  return 0;
}
