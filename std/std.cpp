#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
struct node{
	int l, r;
}e[N];
int t, n, m;
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> t;
	while (t--){
		cin >> n >> m;
		for (int i=1; i<=n; i++){
			cin >> e[i].l >> e[i].r;
		}
	}

	return 0;
}