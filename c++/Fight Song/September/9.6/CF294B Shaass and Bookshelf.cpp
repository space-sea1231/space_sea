#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;

int n;
vector<int> q1, q2; 
vector<int> sum1(N), sum2(N); 

inline bool Cmp(int a, int b) {return a > b;}

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int l, w;
		cin >> l >> w;
		if (l == 1) q1.emplace_back(w);
		if (l == 2) q2.emplace_back(w);
	}
	sort(q1.begin(), q1.end(), Cmp);
	sort(q2.begin(), q2.end(), Cmp);
	int len1 = q1.size(), len2 = q2.size();
	for (int i = 1; i <= len1; i++) sum1[i] = sum1[i - 1] + q1[i - 1];
	for (int i = 1; i <= len2; i++) sum2[i] = sum2[i - 1] + q2[i - 1];
	int ans = INF;
	for (int i = 0; i <= len1; i++) {
		for (int j = 0; j <= len2; j++) {
			int len = i + j * 2;
			if (len >= sum1[len1] - sum1[i] + sum2[len2] - sum2[j]) ans = min(ans, len);
			// if (i == 0 && j == 0) printf("%d %d\n", sum1[])
		}
	}
	printf("%d\n", ans);
	return 0;
}