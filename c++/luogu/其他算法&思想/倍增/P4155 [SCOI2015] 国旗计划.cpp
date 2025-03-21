#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int st[N<<1][32], sum[N];
int n, m;
struct node{
	int id, l, r;
	bool operator < (const node &x){
		return l<x.l;
	}
}e[N<<1];
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		cin >> e[i].l >> e[i].r;
		if (e[i].l>e[i].r){
			e[i].r+=m;
		}
		e[i].id=i;
	}
	sort(e+1, e+n+1);
	for (int i=1; i<=n; i++){
		e[i+n].l=e[i].l+m;
		e[i+n].r=e[i].r+m;
	}
	int j=1;
	for (int i=1; i<=(n<<1); i++){
		while (j<=(n<<1)&&e[j].l<=e[i].r){
			j++;
		}
		st[i][0]=j-1;
	}
	for (int j=1; j<=19; j++){
		for (int i=1; i<=(n<<1); i++){
			st[i][j]=st[st[i][j-1]][j-1];
		}
	}
	for (int i=1; i<=n; i++){
		int ed=e[i].l+m;
		int ans=0, p=i;
		for (int j=19; j>=0; j--){
			if (st[p][j]&&e[st[p][j]].r<ed){
				p=st[p][j];
				ans+=(1<<j);
			}
		}
		sum[e[i].id]=ans+2;
	}
	for (int i=1; i<=n; i++){
		printf("%d ", sum[i]);
	}

	return 0;
}