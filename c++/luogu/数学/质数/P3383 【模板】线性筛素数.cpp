#include <bits/stdc++.h>
using namespace std;
const int N=1e8+10;
const int M=1e6+10;
int n, m, cnt;
int prime[N];
bool vis[N];
void init(){
	for (int i=2; i<=n; i++){
		if (!vis[i]) prime[++cnt]=i;
		for (int j=1; j<=cnt&&i*prime[j]<=n; j++){
			vis[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	init();
	int x;
	for (int i=1; i<=m; i++){
		cin >> x;
		printf("%d\n", prime[x]);
	}
	return 0;
}