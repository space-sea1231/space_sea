#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 7;
const double Phi = 3.1415926;

int n;
int sx, sy, fx, fy;
double x[N], y[N], len[N];
int pos[N];
bool vis[N];
double ans;

double Dist(int x1, int y1, int x2, int y2) {return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));}
void Go() {
	double sum = 0;
	for (int i = 1, p; p = pos[i], i <= n; i++) {
		double minn = min(min(x[p] - sx, fx - x[p]), min(y[p] - sy, fy - y[p]));
		// printf("a = %d b = %d c = %d\n", min(x[p] - sx, fx - x[p]), min(y[p] - sy, fy - y[p]), minn);
		for (int j = 1, q; q = pos[j], j < i; j++) {
			minn = min(minn, max(0.0, Dist(x[p], y[p], x[q], y[q]) - len[q]));
			// cerr << p << " " << pos[j] << " " << Dist(x[p], y[p], x[q], y[q]) << endl;
		}
		len[p] = minn; sum += (double)minn * minn * Phi;
		// printf("%d %lf\n", i, minn);
	}
	ans = max(ans, sum);
	// cerr<<ans << endl;
}
void Dfs(int cur) {
	if (cur == n + 1) {
		// for (int i = 1; i <= n; i++) printf("%d ", pos[i]);
		// printf("\n");
		Go();
		return;
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			pos[cur] = i;
			vis[i] = true;
			Dfs(cur + 1);
			vis[i] = false;
		}
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> sx >> sy >> fx >> fy;
	int a = sx, b = fx;
	sx = min(a, b); fx = max(a, b);
	a = sy, b = fy;
	sy = min(a, b); fy = max(a, b);
	for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	Dfs(1);
	printf("%d\n", (int)round((double)(fx - sx) * (fy - sy) - ans));
	return 0;
}
//