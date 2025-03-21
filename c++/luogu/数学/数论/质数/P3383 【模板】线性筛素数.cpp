#include <bits/stdc++.h>
using namespace std;
const int N=1e8+10;
int n, m, top;
int sum[N];
bool vis[N];
void solve(){
	for (int i=2; i<=n; i++){
		if (!vis[i]){
			sum[++top]=i;
		}
		for (int j=1; j<=top&&i*sum[j]<=n; j++){
			vis[i*sum[j]]=1;
			if (i%sum[j]==0){
				break;
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	solve();
	for (int i=1; i<=m; i++){
		int tmp;
		cin >> tmp;
		printf("%d\n", sum[tmp]);
	}

	return 0;
}