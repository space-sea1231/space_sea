#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int l[N], r[N];
int n, maxn;
void serch(int now, int dep){
	if (now==0){
		return ;
	}
	maxn=max(maxn, dep);
	serch(l[now], dep+1);
	serch(r[now], dep+1);
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; i++){
		cin >> l[i] >> r[i];
	}
	serch(1, 1);
	printf("%d", maxn);

	return 0;
}