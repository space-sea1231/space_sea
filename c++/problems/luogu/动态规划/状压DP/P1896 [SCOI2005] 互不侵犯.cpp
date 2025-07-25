#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=12;
int n, m;
int cnt, ans;
int sit[1<<N], sat[1<<N];
int dp[N][1<<N][N*N];
void Dfs(int x, int num, int cur){
    if (cur>=n){
        sit[++cnt]=x;
        sat[cnt]=num;
        return ;
    }
    Dfs(x, num, cur+1);
    Dfs(x+(1<<cur), num+1, cur+2);
}
bool Check(int x, int y){
    if ((x&y)||((x<<1)&y)||(x&(y<<1))){
        return 0;
    }
    return 1;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    Dfs(0, 0, 0);
    for (int i=1; i<=cnt; i++){
       dp[1][i][sat[i]]=1; 
    }
    for (int i=1; i<=n; i++){
        for (int u=1; u<=cnt; u++){
            for (int v=1; v<=cnt; v++){
                if (Check(sit[u], sit[v])){
                    for (int j=sat[u]; j<=m; j++){
                        dp[i][u][j]+=dp[i-1][v][j-sat[u]];
                    }
                }
            }
        }
    }
    for (int i=1; i<=cnt; i++){
        ans+=dp[n][i][m];
    }
    printf("%lld\n", ans);

    return 0;
}