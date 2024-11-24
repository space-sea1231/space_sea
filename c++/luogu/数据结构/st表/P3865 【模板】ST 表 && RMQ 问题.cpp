#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, m;
int lg[N], st[N][31], a[N];
void init(){
	for (int i=2; i<N; i++){
		lg[i]=lg[i>>1]+1;
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	init();
	for (int i=1; i<=n; i++){
		cin >> a[i];
		st[i][0]=a[i];
	}
	for (int j=1; j<=lg[n]; j++){
		for (int i=1; i+(1<<(j-1))-1<=n; i++){
			st[i][j]=max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
		}
	}
	for (int i=1; i<=m; i++){
		int l, r;
		cin >> l >> r;
		int len=lg[r-l+1];
		printf("%d\n", max(st[l][len], st[r-(1<<len)+1][len]));
	}
	return 0;
}