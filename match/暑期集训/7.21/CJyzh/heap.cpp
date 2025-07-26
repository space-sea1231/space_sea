#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=5e3+10;
const int MOD=1e9+7;

int n;
int a[N];
int tree[N<<1];

int Lowbit(int x){
	return x&-x;
}
void Add(int x){
	while (x<=n){
		tree[x]++;
		x+=Lowbit(x);
	}
}
int Sum(int x){
	int ans=0;
	while (x>0){
		ans+=tree[x];
		x-=Lowbit(x);
	}
	return ans;
}
signed main(){
    freopen("heap.in", "r", stdin);
    freopen("heap.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=1; i<n; i++){
        int u;
        cin >> u;
    }
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    if (a[1]>1){
		a[1]=1;
        for (int i=2; i<=n; i++){
            a[i]=n-i+2;
        }
    }
    for (int i=1; i<=n; i++){
        printf("%d ", a[i]);
        int tmp=a[i];
        tmp-=Sum(a[i]);
        Add(a[i]);
        a[i]=tmp-1;
    }
    printf("\n");
    int ans=0;
	for (int i=1; i<n; i++){
		ans=1LL*(ans+a[i])*(n-i)%MOD;
	}
	printf("%d", (ans+1)%MOD);
    return 0;
}
/*
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
*/