#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
// struct node{
	// int l, r, sum, vis;
// }e[N*4];
int n, m;
int a[N];
// void down(int x){
// 	e[x*2].vis+=e[x].vis;
// 	e[x*2+1].vis+=e[x].vis;
// 	e[x*2].sum+=(e[x*2].r-e[x*2].l+1)*e[x].vis;
// 	e[x*2+1].sum+=(e[x*2+1].r-e[x*2+1].l+1)*e[x].vis;
// 	e[x].vis=0;
// }
// void build(int x, int l, int r){
// 	int mid=(l+r)>>1;
// 	e[x].l=l;
// 	e[x].r=r;
// 	if (l==r){
// 		e[x].sum=a[l];
// 		return ;
// 	}
// 	build(x*2, l, mid);
// 	build(x*2+1, mid+1, r);
// 	e[x].sum=e[x*2].sum+e[x*2+1].sum;
// }
// void minn(int x, int l, int r, int w){
// 	if (e[x].l>r||e[x].r<l){
//         return;
//     }
//     // if (e[x].vis){
//     //     down(x);
//     // }
// 	if (e[x].l==e[x].r){
// 		e[x].sum=min(e[x].sum, w);
// 		return ;
// 	}
//     minn(x*2, l, r, w);
//     minn(x*2+1, l, r, w);
//     e[x].sum=e[x*2].sum+e[x*2+1].sum;
// }
// void add(int x, int l, int r){
//     if (e[x].l>r||e[x].r<l){
//         return;
//     }
//     // if (e[x].vis){
//     //     down(x);
//     // }
// 	if (e[x].l==e[x].r){
// 		e[x].sum+=l;
// 		return ;
// 	}
//     add(x*2, l, r);
//     add(x*2+1, l, r);
//     e[x].sum=e[x*2].sum+e[x*2+1].sum;
// }
// int sum(int x, int l, int r){
//     if (e[x].l>r||e[x].r<l){
//         return 0;
//     }
//     if (e[x].l>=l&&e[x].r<=r){
//         return e[x].sum;
//     }
//     // if (e[x].vis){
//     //     down(x);
//     // }
//     return sum(x*2, l, r)+sum(x*2+1, l, r);
// }
signed main(){
	freopen("ds.in", "r", stdin);
	freopen("ds.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		cin >> a[i];
	}
	int tot=0;
	for (int i=1; i<=m; i++){
		int opt;
		cin >> opt;
		if (opt==1){
			int x;
			cin >> x;
			for (int i=1; i<=n; i++){
				a[i]+=tot*i;
				a[i]=min(a[i], x);
			}
			tot=0;
		}
		if (opt==2){
			tot++;
		}
		if (opt==3){
			int l, r, sum=0;
			cin >> l >> r;
			for (int j=l; j<=r; j++){
				sum+=a[j];
			}
			printf("%lld\n", sum);
		}
	}
	// cin >> n >> m;
	// for (int i=1; i<=n; i++){
	// 	cin >> a[i];
	// }
	// build(1, 1, n);
	// for (int i=1; i<=m; i++){
	// 	int opt;
	// 	cin >> opt;
	// 	if (opt==1){
	// 		int x;
	// 		cin >> x;
	// 		minn(1, 1, n, x);
	// 	}
	// 	if (opt==2){
	// 		add(1, 1, n);
	// 	}
	// 	if (opt==3){
	// 		int l, r;
	// 		cin >> l >> r;
	// 		printf("%d\n", sum(1, l, r));
	// 	}
	// }
	return 0;
}
/*
6 9 9 6 3 6 4 9 9 3 9 5 9 9 6
2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
5 5 5 5 5 5 5 5 5 5 5 5 5 5 5
9 9 9 9 9 9 9 9 9 9 9 9 9 9 9
14 14 14 14 14 14 14 14 14 14 14 14 14 14 14
11 11 11 11 11 11 11 11 11 11 11 11 11 11 11
33
19 19 19 19 19 19 19 19 19 19 19 19 19 19 19
6 6 6 6 6 6 6 6 6 6 6 6 6 6 6
16 16 16 16 16 16 16 16 16 16 16 16 16 16 16
9 9 9 9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9 9 9 9
9 9 9 9 9 9 9 9 9 9 9 9 9 9 9
*/