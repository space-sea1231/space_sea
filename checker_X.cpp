#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
const int N = 1e5 + 5;
int T;
int n[6], k[6];
vector<pair<int, int> > g[6];
int gcd(int x, int y) {
	return (y == 0) ? x : gcd(y, x % y);
}
int unsol[6];
int main() {
	freopen("restore.in", "r", stdin);
	cin >> T;
	for(int ti = 1; ti <= T; ti++) {
		cin >> n[ti] >> k[ti];
		int x, y;
		for(int i = 1; i <= n[ti]; i++) cin >> x >> y, g[ti].push_back((pair<int, int>){x, y});
	}
	fclose(stdin);
	freopen("restore.out", "r", stdin);
	string str;
	for(int ti = 1; ti <= T; ti++) {
		cin >> str;
		if(str == "No") unsol[ti] = 1;
		else {
			int x;
			int gd = 0;
			for(int i = 0; i < n[ti]; i++) {
				cin >> x;
				if(x < g[ti][i].first || x > g[ti][i].second) {
					printf("Wrong answer on case %d.", ti);
					return 0;
				}
				gd = gcd(x, gd);
			}
			if(gd < k[ti]) {
				printf("Wrong answer on case %d, expect gcd >= %d, output = %d.", ti, k[ti], gd);
				return 0;
			}
		}
	}
	fclose(stdin);
	freopen("restore.ans", "r", stdin);
	for(int ti = 1; ti <= T; ti++) {
		cin >> str;
		if(str == "Yes" && unsol[ti]) {
			printf("Wrong answer on case %d.", ti);
			return 0;
		}
		if(str == "Yes") {
			int x;
			for(int i = 1; i <= n[ti]; i++) cin >> x;
		}
	}
	printf("Well done!");
	return 0;
}
