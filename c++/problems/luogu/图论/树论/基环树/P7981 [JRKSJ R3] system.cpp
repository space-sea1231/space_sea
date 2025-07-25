#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const int N=5e5+10;
const int K=20;
int n, m;
int num;
int fa[N][K];
int siz[N], top[N], dfn[N], rev[N], sum[N];
bool vis[N];
int Pow(int a, int b, int mod){
    int sum=1;
    while (b){
        if (b&1){
            sum=((ll)sum*a)%mod;
        }
        a=((ll)a*a)%mod;
        b>>=1LL;
    }
    return sum;
}
void Loop(int u){
    // cerr<<"Debug2: " << u << " " << fa[u][K-1] << " " << top[fa[u][K-1]] << endl;
    if (top[fa[u][K-1]]){
        top[u]=top[fa[u][K-1]];
        return ;
    }
    top[u]=++num;
    int now, cnt=0;
    for (now=u; !vis[fa[now][0]]; now=fa[now][0]){
        vis[now]=1;
    }
    u=now;
    for (now=fa[now][0]; now!=u; now=fa[now][0]){
        dfn[now]=++cnt;
        rev[sum[num-1]+cnt]=now;
        top[now]=num;
        if (now==8){
            // cerr<<"Debug3: " << now << endl;
        }
        // cerr<<"Debug3.2: " << now << endl;
    }
    dfn[now]=++cnt;
    rev[sum[num-1]+cnt]=now;
    top[now]=num;
    if (now==8){
        // cerr<<"Debug3.1: " << top[8] << endl;
    }
    siz[num]=cnt;
    sum[num]=sum[num-1]+cnt;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> fa[i][0];
        // cerr << i << " " << fa[i][0] << endl;
    }
    for (int j=1; j<K; j++){
        for (int i=1; i<=n; i++){
            fa[i][j]=fa[fa[i][j-1]][j-1];
        }
    }
    for (int i=1; i<=n; i++){
        if (!top[i]){
            Loop(i);
        }
        // cerr<<i<<endl;
    }
    for (int i=1; i<=n; i++){
        if (m<=19){
            printf("%lld ", fa[i][m]);
        }else{
            int now=fa[i][K-1];
            int row=(Pow(2, m, siz[top[i]])-Pow(2, K-1, siz[top[i]])+siz[top[i]])%siz[top[i]];
            // cerr<<"Debug1: " << row << endl;
            now=dfn[now]+row;
            if (now>siz[top[i]]){
                now%=siz[top[i]];
            }
            printf("%lld ", rev[sum[top[i]-1]+now]);
        }
    }
    // printf("Done\n");
    return 0;
}