#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF32 = 1e9 + 1;
const ll INF64 = 1e18 + 1;
const int N = 2e2 + 10;

int n, m;
int c[N][N];
ll g[N][N];
int f[N];
pair<int, int> dis[N];
ll k;

ll Calc() {
	memset(g, 0, sizeof(g));
	g[0][0] = 1;
	for (int i = 1; i <= n + m - 1; i++) {
        for (int j = 0; j <= i; j++) {
            if(j != i && f[i] != 1) g[i][j] += g[i - 1][j + 1];
            g[i][j] = min(g[i][j], INF64);
            if(j && f[i] != 2) g[i][j] += g[i - 1][j - 1];
            g[i][j] = min(g[i][j], INF64);
	    }
    }
	return g[n + m - 1][0];
}
signed main(){
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m >> k;
    for (int i = 1; i <= n + m - 1; i++) dis[i] = make_pair(INF32, i);
	for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> c[i][j];
            dis[i + j - 1].first = min(dis[i + j - 1].first, c[i][j]);
        }
    }
	ll sum = 0;
	sort(dis + 1, dis + n + m);
	for (int i = 1; i <= n + m - 1; i++) {
		f[dis[i].second] = 1;
		ll res = Calc();
		if(sum + res < k) {
            sum += res;
            f[dis[i].second] = 2;
        }
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
            printf("%c", f[i + j - 1] == 1 ? '(' : ')');
        }
		printf("\n");
	}
	return 0;
}


/*
Mist rolls over t he hills like a slow song
雾漫过山丘，像一首舒缓的歌
*/