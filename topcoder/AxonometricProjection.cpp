// SRM 524, Level 3

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

const int MOD = 1000000009;
const int MAX_N = 55;

class AxonometricProjection {
	public:
  
  long long dp[MAX_N][MAX_N], cmb[MAX_N][MAX_N];

  void CalculateCmb() {
    for (int i = 0; i < MAX_N; ++i) {
      cmb[i][0] = 1;
      for (int j = 1; j <= i; ++j) {
        cmb[i][j] = (cmb[i-1][j] + cmb[i-1][j-1]) % MOD;
      }
    }
  }

  long long RaiseToPower(int a, int b) {
    long long result = 1;
    for (int i = 1; i <= b; ++i) {
      result = (result*a) % MOD;
    }
    return result;
  }

  long long Count(int height, int lines_equal, int lines_greater, int columns_equal, int columns_greater) {
    long long result = 0;
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 0; i < columns_equal; ++i) {
      for (int j = 0; j <= lines_equal; ++j) {
        long long rest = RaiseToPower(height+1, lines_greater+j);
        long long rest_diff = (rest - RaiseToPower(height, lines_greater+j)) % MOD; 
        if (rest_diff < 0) {
          rest_diff += MOD;
        }

        // k = 0
        long long factor = (RaiseToPower(height, lines_equal-j)*rest_diff) % MOD;
        dp[i+1][j] = (dp[i+1][j] + dp[i][j]*factor) % MOD;

        // k > 0
        for (int k = 1; j+k <= lines_equal; ++k) {
          factor = (cmb[lines_equal-j][k]*RaiseToPower(height, lines_equal-j-k)) % MOD;
          factor = (factor*RaiseToPower(height+1, j+lines_greater)) % MOD;
          dp[i+1][j+k] = (dp[i+1][j+k] + dp[i][j]*factor) % MOD;
        }
      }
    }
    
    long long rest = RaiseToPower(height+1, columns_greater);
    long long rest_diff = (rest - RaiseToPower(height, columns_greater)) % MOD;
    if (rest_diff < 0) {
      rest_diff += MOD;
    }
    for (int i = 0; i <= lines_equal; ++i) {
      long long factor = (RaiseToPower(rest, i)*RaiseToPower(rest_diff, lines_equal-i)) % MOD;
      result = (result + dp[columns_equal][i]*factor) % MOD;
    }
    return result;
  }

	int howManyWays(vector <int> lines, vector <int> columns) {
    set<int> heights;
    for (size_t i = 0; i < lines.size(); ++i) {
      heights.insert(lines[i]);
    }
    for (size_t i = 0; i < columns.size(); ++i) {
      heights.insert(columns[i]);
    }

    CalculateCmb();

    long long sol = 1;
    for (set<int>::iterator it = heights.begin(); it != heights.end(); ++it) {
      int lines_equal = 0, lines_greater = 0, columns_equal = 0, columns_greater = 0;
      for (size_t i = 0; i < lines.size(); ++i) {
        lines_equal += lines[i] == *it;
        lines_greater += lines[i] > *it;
      }
      for (size_t i = 0; i < columns.size(); ++i) {
        columns_equal += columns[i] == *it;
        columns_greater += columns[i] > *it;
      }

      sol = (sol * Count(*it, lines_equal, lines_greater, columns_equal, columns_greater)) % MOD;
    }

    return sol;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) ||
  (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) ||
  (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) ||
  (Case == 5)) test_case_5();}
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(0, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {50,50,50,50,524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {524,524}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 104060401; verify_case(1, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5,6,7,8,9,10,11}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {5,2,4,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,2,4,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 429287; verify_case(3, Arg2, howManyWays(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {5,2,4,52,24,524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,4,20,24,500,504,520,524}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 97065655; verify_case(4, Arg2, howManyWays(Arg0, Arg1)); }
  void test_case_5() { int Arr0[] = {0, 1, 3, 4, 4, 9, 9, 10}; vector <int> Arg0(Arr0, Arr0 +
  (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 6, 7, 8, 9, 10, 10}; vector <int> Arg1(Arr1,
  Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 845010484; verify_case(5, Arg2, howManyWays(Arg0, Arg1)); }


// END CUT HERE
 
};

// BEGIN CUT HERE 
int main()
{
   AxonometricProjection ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE 
    
