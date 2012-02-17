#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAX_M = 5010;
const long long INF = 1LL << 62;

int n, m;
int perm[MAX_M], a[MAX_M];
int position[6][MAX_M];
int dest_perm[6], len[6];

void BuildPermutation() {
  for (int i = 0; i < n; ++i) {
    perm[2*i+1] = 5*i+1;
    perm[2*i+2] = 5*i+2;
    perm[2*n+2*i+1] = 5*i+3;
    perm[2*n+2*i+2] = 5*i+4;
    perm[4*n+i+1] = 5*i+5;
  }
}

void BuildCycle(int value) {
  memset(position[value], -1, sizeof(position[value]));
  len[value] = 0;
  for (int i = 1; i <= m; ++i) {
    if (a[i] == value) {
      int steps = 0;
      do {
        position[value][i] = steps;
        i = perm[i];
        ++steps;
        ++len[value];
      } while (a[i] != value);
    }
  }
}

long long GCD(long long a, long long b, long long &x, long long &y) {
  long long prev_x = 1, prev_y = 0;
  x = 0, y = 1;

  while (b != 0) {
    long long q = a / b;
    long long next_x = prev_x - q * x;
    long long next_y = prev_y - q * y;
    prev_x = x;
    prev_y = y;
    x = next_x;
    y = next_y;

    long long rest = a % b;
    a = b;
    b = rest;
  }

  x = prev_x;
  y = prev_y;
  return a;
}

long long Inverse(long long a, long long mod) {
  long long x, y;
  assert(GCD(a, mod, x, y) == 1);
  if (x < 0) {
    x += mod;
  }
  assert(a == 0 || (a*x) % mod == 1);
  x %= mod;
  if (x < 0) {
    x += mod;
  }
  return x;
}

long long ComputeResult(int dest_perm[]) {
  for (int i = 1; i <= 5; ++i) {
    if (position[i][dest_perm[i]] == -1) {
      return INF;
    }
  }

  long long p1 = position[1][dest_perm[1]];
  long long l1 = len[1];
  for (int i = 2; i <= 5; ++i) {
    long long p2 = position[i][dest_perm[i]];
    long long l2 = len[i];
    
    long long x, y;
    long long d = GCD(l1, l2, x, y);
    long long l = l1*l2 / d;

    if (p1 % d != p2 % d) {
      return INF;
    }

    long long c = l2 / d;
    long long a = (l1 / d) % c;
    long long b = ((p2-p1) / d) % c;
    if (b < 0) {
      b += c;
    }
    long long inv = Inverse(a, c);
    long long k = ((inv % c) * (b % c)) % c;

    p1 = (p1 + k * l1) % l;
    l1 = l;
  }

  if (p1 == 0) {
    p1 = l1;
  }

  return p1;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("5879.in", "r", stdin);
  freopen("5879.out", "w", stdout);
#endif

  scanf("%d ", &n);
  while (n != 0) {
    m = n*5;
    for (int i = 1; i <= m; ++i) {
      scanf("%d ", &a[i]);
    }

    long long solution = INF;
    int best_player = 0;
    BuildPermutation();
    for (int i = 1; i <= 5; ++i) {
      BuildCycle(i);
    }
    
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= 5; ++j) {
        dest_perm[j] = (i-1)*5 + j;
      }

      do {
        long long result = ComputeResult(dest_perm);
        if (result < solution) {
          solution = result;
          best_player = i;
        }
      } while (next_permutation(dest_perm+1, dest_perm+6));
    }

    if (solution == INF) {
      cout << "Neverending game.\n";
    } else {
      cout << "Player " << best_player << " wins game number " << solution << ".\n";
    }

    scanf("%d ", &n);
  }

  return 0;
}
