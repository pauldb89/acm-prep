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

class CakeParty {
	public:
	int minLex(int x, int y) {
		stringstream ss1, ss2;
		ss1 << x; ss2 << y;
		if (ss1.str() < ss2.str())
			return x;
		return y;
	}

	int findMin(int x, int y) {
		int tmp = x, ten = 1;
		while (x) {
			x /= 10;
			y /= 10;
			ten *= 10;
		}
		if (y > 0) {
			return minLex(tmp, ten);
		}
		return tmp;
	}

	string makeMove(vector <int> pieces) {
		size_t n = pieces.size();
		int bestPos = 0, secondMax = -1, nrMax = 0, nrSecond = 0;
		for (size_t i = 0; i < n; ++i) {
			if (pieces[i] > pieces[bestPos]) {
				bestPos = i;
				nrMax = 1;
			} else if (pieces[i] == pieces[bestPos]) {
				bestPos = minLex(i, bestPos);
				++nrMax;
			}
		}

		for (size_t i = 0; i < n; ++i)
			if (pieces[i] < pieces[bestPos]) {
				if (pieces[i] > secondMax) {
					secondMax = pieces[i];
					nrSecond = 1;
				} else if (pieces[i] == secondMax) {
					++nrSecond;
				}
			}

		stringstream ss;

		ss << "CAKE " << bestPos << " PIECES ";
		if (nrMax % 2 == 0 || nrMax > 1) {
			ss << 1; 
		} else if (n == 1) {
			ss << pieces[bestPos];
		} else if (nrSecond % 2 == 1) {
			ss << pieces[bestPos]-secondMax;
		} else {
			ss << findMin(pieces[bestPos]-secondMax+1, pieces[bestPos]);
		}

		return ss.str();
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {47}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 0 PIECES 47"; verify_case(0, Arg1, makeMove(Arg0)); }
	void test_case_1() { int Arr0[] = {3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 0 PIECES 1"; verify_case(1, Arg1, makeMove(Arg0)); }
	void test_case_2() { int Arr0[] = {3,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 1 PIECES 2"; verify_case(2, Arg1, makeMove(Arg0)); }
	void test_case_3() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 0 PIECES 1"; verify_case(3, Arg1, makeMove(Arg0)); }
	void test_case_4() { int Arr0[] = {3,3,112}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 2 PIECES 110"; verify_case(4, Arg1, makeMove(Arg0)); }
	void test_case_5() { int Arr0[] = {3,3,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 0 PIECES 1"; verify_case(5, Arg1, makeMove(Arg0)); }
	void test_case_6() { int Arr0[] = {4,7,4,7,4,7,4,7,47,47,47,47}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 10 PIECES 1"; verify_case(6, Arg1, makeMove(Arg0)); }

// END CUT HERE
 
};

// BEGIN CUT HERE 
int main()
{
   CakeParty ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE 
    
