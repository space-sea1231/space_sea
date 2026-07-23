#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N=5010, M=N*50;
int n, num=1, a[N], tr[M][2], sz[M], dif[M];

void clear() {
    for (int i=1; i<=num; i++) {
        tr[i][0]=tr[i][1]=0;
        sz[i]=dif[i]=0;
    }
    num=1;
}

void insert(int x, int c) {
    int p=1;
    sz[p]+=c, dif[p]++;
    for (int i=0; i<50; i++) {
        int v=x>>i&1;
        if (!tr[p][v]) tr[p][v]=++num;
        p=tr[p][v];
        sz[p]+=c, dif[p]++;
    }
}

int dp(int p, int k, int d) {
    if (dif[p]<=k) return 0;
    int l=tr[p][0], r=tr[p][1];
    if (!l) return dp(r, k, d+1);
    if (!r) return dp(l, k, d+1);
    if (dif[l]<dif[r]) swap(l, r);
    int w=1ll<<d;
    if (dif[l]-dif[r]<=k) return (dif[l]+dif[r]-k)*w;
    if (dif[l]-sz[r]<=k) return 2*(dif[l]-k)*w;
    return 2*sz[r]*w+dp(l, k+sz[r], d+1);
}

void solve() {
    cin>>n;
    for (int i=1; i<=n; i++) cin>>a[i];
    sort(a+1, a+n+1);
    for (int i=1, j; i<=n; i=j) {
        for (j=i; j<=n && a[j]==a[i]; j++);
        insert(a[i], j-i);
    }
    cout<<dp(1, 1, 0)<<endl;
    clear();
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T;
    cin>>T;
    while (T--) solve();
    return 0;
}