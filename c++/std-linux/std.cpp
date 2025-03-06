#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=15;
const int M=12;
const int INF=0x7fffffff;
int n, m, U;
int ans=INF;
int val[N][N], cost[1<<M][1<<M];
int dp[N][1<<M];
inline int subset(int x, int y){
    return x&(y-1);
}
void Init(){
    for (int i=1; i<=U; i++){
        for (int j=subset(i, i); j; j=subset(i, j)){
            for (int k=0; k<n; k++){
                if (i>>k&1&&!(j>>k&1)){
                    int tmp=INF;
                    for (int l=0; l<n; l++){
                        if (j>>l&1){
                            tmp=min(tmp, val[k][l]);
                        }
                    }
                    if (tmp==INF){
                        cost[j][i]=INF;
                        break;
                    }
                    cost[j][i]+=tmp;
                }
            }
        }
    }
}
void DP(int s){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=U; j++){
            dp[i][j]=INF;
        }
    }
    dp[1][1<<s]=0;
    for (int i=2; i<=n; i++){
        for (int j=1; j<=U; j++){
            for (int k=subset(j, j); k; k=subset(j, k)){
                if (dp[i-1][k]!=INF){
                    dp[i][j]=min(dp[i][j], dp[i-1][k]+cost[k][j]*(i-1));
                }
            }
        }
        ans=min(ans, dp[i][U]);
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    if (n==1){
        printf("0\n");
        return 0;
    }
    U=(1<<n)-1;
    memset(val, 0x3f, sizeof(val));
    for (int i=1; i<=m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        val[u][v]=min(val[u][v], w);
        val[v][u]=val[u][v];
    }
    Init();
    for (int i=0; i<n; i++){
        DP(i);
    }
    printf("%lld\n", ans);

    return 0;
}//