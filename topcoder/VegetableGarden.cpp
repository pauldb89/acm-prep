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

const int MAX_DIR = 4;
const int MAX_CONFIG = 3000010;
const int DIRX[MAX_DIR] = {-1, 0, 1, 0};
const int DIRY[MAX_DIR] = {0, -1, 0, 1};

class Plot {
 public:
	char x, y;
	char type;

	Plot() {}
	Plot(int x, int y, char type) {
		this->x = x;
		this->y = y;
		this->type = type;
	}
};

class Config {
 public:
	static int n, m, len;
	char x, y;
	short state;

	Config() {}
	Config(int x, int y, int state) {
		this->x = x;
		this->y = y;
		this->state = state; 
	}
	
	operator int() const {
		return (x*(m+1) + y)*(1<<len)+state;
	}
};

int Config::n = 0;
int Config::m = 0;
int Config::len = 0;

class VegetableGarden {
	public:
	int n, m;
	short configs[MAX_CONFIG];

	int getBit(int state, int bit) {
		return (state&(1<<bit)) != 0;
	}

	void changeBit(short &state, int bit) {
		state ^= 1 << bit;	
	}

	vector <int> getMinDistances(vector <string> garden) {
		n = garden.size();
		m = garden[0].size();
		vector <Plot> plots;

		int good_plots = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (garden[i][j] != '.') {
					plots.push_back(Plot(i, j, garden[i][j]));
					good_plots += garden[i][j] == 'I';
				}
			}
		}
		int len = plots.size();
		vector <int> dists(good_plots);

		Config::n = n;
		Config::m = m;
		Config::len = len;
		memset(configs, -1, sizeof(configs));
		queue <Config> configs_queue;
		configs[Config(0, 0, 0)] = 0;
		configs_queue.push(Config(0, 0, 0));

		short computedDists = 0;
		while (!configs_queue.empty() && computedDists != (1<<good_plots)-1) {
			Config top = configs_queue.front();
			configs_queue.pop();
			for (int i = 0; i < MAX_DIR; ++i) {
				Config tmp = Config(top.x + DIRX[i], top.y + DIRY[i], top.state);
				if (tmp.x >= 0 && tmp.y >= 0 && tmp.x <= n && tmp.y <= m) {
					for (int j = 0; j < len; ++j) {
						if (min(top.y, tmp.y) == plots[j].y && max(top.y, tmp.y) == plots[j].y+1 &&
								tmp.x <= plots[j].x) {
							changeBit(tmp.state, j);
						}
					}

					// printf("%d %d %d -> %d %d %d\n", top.x, top.y, top.state, tmp.x, tmp.y, tmp.state);
					// printf("%d -> %d\n", (int) top, (int) tmp);

					if (configs[tmp] == -1) {
						configs[tmp] = configs[top] + 1;
						configs_queue.push(tmp);
						if (tmp.x == 0 && tmp.y == 0) {
							int cnt = 0, bad_includes = 0;
							for (int j = 0; j < len; ++j) {
								if (getBit(tmp.state, j)) {
									if (plots[j].type == 'I') {
										++cnt;
									} else {
										bad_includes = 1;
									}
								}
							}

							if (cnt > 0 && !bad_includes && !getBit(computedDists, cnt-1)) {
								dists[cnt-1] = configs[tmp];
								changeBit(computedDists, cnt-1);
							}
						}
					}
				} 
			}
		} 

		return dists;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"I"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getMinDistances(Arg0)); }
	void test_case_1() { string Arr0[] = {"XX", 
 "XI"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getMinDistances(Arg0)); }
	void test_case_2() { string Arr0[] = {"III", 
 "IXI",
 "III"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 6, 8, 10, 12, 14, 16, 18 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getMinDistances(Arg0)); }
	void test_case_3() { string Arr0[] = {"X.I", 
 ".I.", 
 "I.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8, 10, 14 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getMinDistances(Arg0)); }
	void test_case_4() { string Arr0[] = {"IIXIIXIXII"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 6, 12, 14, 20, 26, 28 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, getMinDistances(Arg0)); }

// END CUT HERE
 
};

// BEGIN CUT HERE 
int main()
{
   VegetableGarden ___test; 
    ___test.run_test(-1); 
} 
// END CUT HERE 
    
