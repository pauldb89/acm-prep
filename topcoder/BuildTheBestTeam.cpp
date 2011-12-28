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

const int MAX_PLAYERS = 55;

int cmp(pair <int, int> p1, pair <int, int> p2) {
  return p1.first > p2.first || (p1.first == p2.first && p1.second > p2.second);
}

class BuildTheBestTeam {
	public:
  int dp[MAX_PLAYERS][MAX_PLAYERS];

	int maximalStrength(vector <int> usualSkills, vector <int> powerplaySkills, int teams, int ind) {
    memset(dp, 0, sizeof(dp));
    vector <pair <int, int> > skills;
    int players = usualSkills.size();
    for (int i = 0; i < players; ++i) {
      skills.push_back(make_pair(usualSkills[i], powerplaySkills[i]));
    }
    sort(skills.begin(), skills.end(), cmp);

    vector <int> max_players(players+1);
    for (int i = ind; i <= players; i += 2*teams) {
      ++max_players[i];
    }
    for (int i = 2*teams-ind+1; i <= players; i += 2*teams) {
      ++max_players[i];
    }
    for (int i = 1; i <= players; ++i) {
      max_players[i] += max_players[i-1];
    }

    for (int i = 1; i <= players; ++i) {
      for (int j = 1; j <= max_players[i]; ++j) {
        dp[i][j] = dp[i-1][j];
        for (int k = 0; k < i; ++k) {
          dp[i][j] = max(dp[i][j], dp[k][j-1]+skills[i-1].second);
        }
      }
    }

    return dp[players][max_players[players]];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {10, 10, 10, 10, 10, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20, 20, 20, 20, 20, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 2; int Arg4 = 40; verify_case(0, Arg4, maximalStrength(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {10, 10, 10, 10, 10, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 30, 10, 10, 30, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 3; int Arg4 = 20; verify_case(1, Arg4, maximalStrength(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {1, 2, 3, 4, 5, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 5, 4, 3, 2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 1; int Arg4 = 11; verify_case(2, Arg4, maximalStrength(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {1, 2, 3, 4, 5, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 2, 4, 3, 5, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 1; int Arg4 = 11; verify_case(3, Arg4, maximalStrength(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {88, 82, 82, 73}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {68, 74, 14, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 1; int Arg4 = 75; verify_case(4, Arg4, maximalStrength(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
};

// BEGIN CUT HERE 
int main()
{
   BuildTheBestTeam ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE 
    
