#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int Mod=998244353;
int n, a[N], tree[N*2];
int lowbit(int x){
	return x&-x;
}
void add(int x){
	while (x<=n){
		tree[x]++;
		x+=lowbit(x);
	}
}
int sum(int x){
	int ans=0;
	while (x){
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	for (int i=1; i<=n; i++){
		cin >> a[i];
		int tmp=a[i];
		tmp-=sum(a[i]);
		add(a[i]);
		a[i]=tmp-1;
	}
	int ans=0;
	for (int i=1; i<n; i++){
		ans=1LL*(ans+a[i])*(n-i)%Mod;
	}
	printf("%lld", (ans+1)%Mod);

	return 0;
}