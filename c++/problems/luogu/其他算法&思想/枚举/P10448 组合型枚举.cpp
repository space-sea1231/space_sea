#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
bool vis[N];
int n, m, a[N];
void print(){
	for (int i=1; i<=m; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
}
void serch(int dep, int now){
	if (dep>m){
		print();
		return ;
	}
	for (int i=now+1; i<=n; i++){
		if (!vis[i]){
			vis[i]=1;
			a[dep]=i;
			serch(dep+1, i);
			vis[i]=0;
		}
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	serch(1, 0);

	return 0;
}