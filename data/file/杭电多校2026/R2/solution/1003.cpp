#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N=5010, M=N*50;;
vector<int> f[M];
int n, num=1, tr[M][2], sz[M], st[N][14], lg[N];

void clear() {
    for (int i=1; i<=num; i++) {
        sz[i]=0;
        tr[i][0]=tr[i][1]=0;
    }
    num=1;
}

void insert(int s) {
    int p=1;
    for (int i=0; i<50; i++) {
        int c=s%2; s/=2;
        if (!tr[p][c]) tr[p][c]=++num;
        p=tr[p][c];
    }
    sz[p]++;
}

void dfs(int p, int w) {
    int l=tr[p][0], r=tr[p][1];
    if (!l && !r) {
        f[p].resize(sz[p]+1);
        fill(f[p].begin(), f[p].end(), 0);
        return;
    }
    if (!l) {
        dfs(r, w<<1);
        f[p]=move(f[r]);
        return;
    }
    if (!r) {
        dfs(l, w<<1);
        f[p]=move(f[l]);
        return;
    }
    dfs(l, w<<1), dfs(r, w<<1);
    if (f[l].size()>f[r].size()) swap(l, r);
    int n=f[l].size()-1, m=f[r].size()-1;
    f[p].resize(n+m+1);
    for (int i=1; i<=m; i++) st[i][0]=f[r][i]+i*w;
    for (int j=1; j<=lg[m]; j++)
            for (int i=1; i<=m-(1<<j)+1; i++)
                st[i][j]=min(st[i][j-1], st[i+(1<<j-1)][j-1]);
    for (int z=1; z<=n+m; z++) {
        f[p][z]=4e18;
        for (int x=1; x<=n; x++) {
            int L=max(1ll, abs(x-z));
            int R=min(m, x+z);
            if (L>R) continue;
            int t=lg[R-L], mn=min(st[L][t], st[R-(1<<t)+1][t]);
            f[p][z]=min(f[p][z], -z*w+f[l][x]+x*w+mn);
        }
    }
    f[l].clear(), f[l].shrink_to_fit();
    f[r].clear(), f[r].shrink_to_fit();
}

void solve() {
    cin>>n;
    for (int i=1; i<=n; i++) {
        int x;
        cin>>x;
        insert(x);
    }
    dfs(1, 1);
    cout<<f[1][1]<<endl;
    f[1].clear(), f[1].shrink_to_fit();
    clear();
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    lg[1]=0;
    for (int i=2; i<N; i++) lg[i]=lg[i>>1]+1;
    int T=1;
    cin>>T;
    while (T--) solve();
    return 0;
}