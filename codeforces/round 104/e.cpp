#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAX_N = 1000010;
const int MAX_TREE = 1 << 21;

int n, m;
char str[MAX_N];
int cnt0[MAX_TREE], cnt1[MAX_TREE], best[MAX_TREE], best_rev[MAX_TREE];
char rev[MAX_TREE];

void BuildTree(int node, int left, int right) {
  if (left == right) {
    cnt0[node] = str[left] == '4';
    cnt1[node] = str[left] == '7';
    best[node] = best_rev[node] = 1;
  } else {
    int mid = (left+right) / 2;
    BuildTree(node*2, left, mid);
    BuildTree(node*2+1, mid+1, right);

    cnt0[node] = cnt0[node*2] + cnt0[node*2+1];
    cnt1[node] = cnt1[node*2] + cnt1[node*2+1];
    best[node] = max(best[node*2] + cnt1[node*2+1],
                     cnt0[node*2] + best[node*2+1]);
    best_rev[node] = max(best_rev[node*2] + cnt0[node*2+1],
                         cnt1[node*2] + best_rev[node*2+1]);
  }
}

void SwapAll(int node) {
  swap(cnt0[node], cnt1[node]);
  swap(best[node], best_rev[node]);
}

void Reverse(int node, int left, int right, int x, int y) {
  if (x <= left && right <= y) {
    rev[node] ^= 1;
    SwapAll(node);
  } else {
    if (rev[node]) {
      SwapAll(node*2);
      SwapAll(node*2+1);
      rev[node*2] ^= 1;
      rev[node*2+1] ^= 1;
      rev[node] = 0;
    }

    int mid = (left+right) / 2;
    if (x <= mid) {
      Reverse(node*2, left, mid, x, y);
    }
    if (y > mid) {
      Reverse(node*2+1, mid+1, right, x, y);
    }
    cnt0[node] = cnt0[node*2] + cnt0[node*2+1];
    cnt1[node] = cnt1[node*2] + cnt1[node*2+1];
    best[node] = max(best[node*2] + cnt1[node*2+1],
                     cnt0[node*2] + best[node*2+1]);
    best_rev[node] = max(best_rev[node*2] + cnt0[node*2+1],
                         cnt1[node*2] + best_rev[node*2+1]);
  }
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("e.in", "r", stdin);
#endif

  cin >> n >> m;
  cin >> (str+1);

  BuildTree(1, 1, n);

  for (int i = 1; i <= m; ++i) {
    string oper;
    cin >> oper;
    if (oper == "count") {
      cout << best[1] << '\n';
    } else {
      int x, y;
      cin >> x >> y;
      Reverse(1, 1, n, x, y);
    }
  }

  return 0;
}
