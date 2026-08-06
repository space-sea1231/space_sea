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
const int N = 1e8 + 10;
const int K = 6e6 + 10;
const int M = 1e4 + 10;

int t;
int cnt;
int a[10], mul[10];
int prime[K];
int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool vis[N], flag2[M];
vector<int> q2, q3, ok;

void Init() {
	vis[0] = vis[1] = true;
	for (int i = 2; i < N; i++) {
		if (!vis[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt && (ll)i * prime[j] < N; j++) {
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (int i = 1; i <= cnt; i++) {
		if (prime[i] < 10000) q2.emplace_back(prime[i]);
		if (10000 <= prime[i] && prime[i] < 100000000) q3.emplace_back(prime[i]);
	}
	// cerr<<q2.size() << " " << q3.size() << endl;
	// for (auto cur:q2) printf("%d\n", cur);
	for (auto cur:q2) if (!vis[cur % 10000] && !vis[cur % 100]) {
		flag2[cur] = true;
		// printf("%d\n", cur);
	}
	for (auto cur:q3) if (flag2[cur % 10000]) {
		int mth = cur / 100 % 100, dy = cur % 100;
		if (mth < 1 || mth > 12) continue;
		int year = cur / 10000;
		bool run = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
		int day_limit = month[mth] + (mth == 2 && run);  
		if (1 <= dy && dy <= day_limit) ok.emplace_back(cur);
		// printf("%d\n", cur);
	}
	mul[0] = 1;
	for (int i = 1; i <= 8; i++) mul[i] = mul[i - 1] * 10;
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	Init();
	cin >> t;
	// cerr<<ok.size();
	while (t--) {
		for (int i = 1; i <= 8; i++) {
			char c;
			cin >> c;
			a[i] = (c == '-' ? -1 : c - '0');
		}
		int ans = 0;
		for (auto cur:ok) {
			// cerr<<cur<<endl;
			bool flag = true;
			for (int i = 1; i <= 8; i++) {
				if (a[i] != -1 && a[i] != (cur / mul[8 - i] % 10)) {
					flag = false; 
				}
			}
			ans += (int)flag;
			// if (flag) printf("%d\n", cur);
		}
		printf("%d\n", ans);
	}
	return 0;
}