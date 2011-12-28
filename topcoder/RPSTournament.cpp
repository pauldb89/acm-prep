#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class RPSTournament {
	public:
	int works(int first_player, int rounds, int C) {
		set <int> players;
		for (int i = 1; i <= 1<<rounds; ++i) {
			players.insert(i);
		}

		players.erase(first_player);
		queue <pair <int, int> > tree_queue;
		tree_queue.push(make_pair(first_player, rounds));
		while (!tree_queue.empty()) {
			pair <int, int> top = tree_queue.front();
			tree_queue.pop();
			if (top.second >= 1) {
				set <int> :: iterator it = players.lower_bound(top.first-(int) sqrt(C*top.first));
				if (it == players.end()) {
					return 0;
				}
				tree_queue.push(make_pair(*it, top.second-1));
				tree_queue.push(make_pair(top.first, top.second-1));
				players.erase(*it);
			}
		}
		return 1;
	}

	int greatestSeed(int rounds, int C) {
		int sol = 1;
		int front = 1, back = 1 << rounds;
		while (front <= back) {
			int middle = (front+back) / 2;
			if (works(middle, rounds, C)) {
				sol = middle;
				front = middle+1;
			} else {
				back = middle-1;
			}
		}
		return sol;
	}

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 1; verify_case(0, Arg2, greatestSeed(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 6; verify_case(1, Arg2, greatestSeed(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 9; verify_case(2, Arg2, greatestSeed(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 7; int Arg1 = 3; int Arg2 = 50; verify_case(3, Arg2, greatestSeed(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 15; int Arg1 = 180; int Arg2 = 9755; verify_case(4, Arg2, greatestSeed(Arg0, Arg1)); }

// END CUT HERE
 
};

// BEGIN CUT HERE 
int main()
{
   RPSTournament ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE 
    
