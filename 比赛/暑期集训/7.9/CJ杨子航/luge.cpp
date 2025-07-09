#include <iostream>
#include <stdio.h>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N=5e3+10;
const int MOD=998244353;

int n, k;
int cnt, ans, siz;
int val[N], dp[N][2], father[N];
int head[N], to[N<<1], nxt[N<<1];
bool vis[N];
vector<int> node;

// ll Pow(ll a, ll b){
//     ll sum=1;
//     while (b){
//         if (b&1){
//             sum=(sum*a)%MOD;
//         }
//         a=(a*a)%MOD;
//         b>>=1;
//     }
//     return sum;
// }
void Add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void Dfs1(int u, int fa){
    dp[u][0]=((ll)dp[u][0]*dp[fa][0])%MOD;
    dp[fa][1]=((ll)dp[fa][1]*((MOD>>1)+1))%MOD;
    father[u]=fa;
    node.push_back(u);
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa) continue;
        Dfs1(v, u);
    }
}
void Dfs2(int cur, int sum, int tot){
    if (cur==siz){
        return;
    }
    if (sum==k&&vis[father[node[cur]]]==true){
        ans=(ans+(ll)tot*dp[father[node[cur]]][1])%MOD;
    }
    Dfs2(cur+1, sum, tot);
    if (vis[father[node[cur]]]==true&&sum+val[node[cur]]<=k){
        vis[node[cur]]=true;
        Dfs2(cur+1, sum+val[node[cur]], (ll)tot*dp[node[cur]][0]%MOD);
        vis[node[cur]]=false;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    for (int i=1; i<=n; i++){
        cin >> val[i];
        dp[i][0]=(MOD>>1)+1;
        dp[i][1]=1;
    }
    for (int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        Add(u, v);
        Add(v, u);
    }
    dp[0][0]=dp[1][0]=1;
    Dfs1(1, 0);
    siz=node.size();
    vis[1]=1;
    Dfs2(1, val[1], 1);
    printf("%d\n", ans);

    return 0;
}
/*
1->998244353(逆元下)
1/2->499122177(逆元下)
1-1/2->499122176????
*/