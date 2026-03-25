#include <bits/stdc++.h>
using namespace std;
const int N=13;
const int Mod=1e8;
int n, m;
int cnt=1;
int vis[N];
int sit[1<<N];
int dp[N][1<<N];
inline int lowbit(int x){
    return x&-x;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            int x;
            cin >> x;
            vis[i]=(vis[i]<<1)+x;
        }
    }
    for (int i=1; i<(1<<m); i++){
        if (i&(i<<1)||i&(i>>1)){
            continue;
        }
        sit[++cnt]=i;
        int tmp=i;
    }
    for (int j=1; j<=cnt; j++){
        if ((sit[j]&vis[1])==sit[j]){
            dp[1][j]=1;
        }
    }
    for (int i=2; i<=n; i++){
        for (int j=1; j<=cnt; j++){
            if ((sit[j]&vis[i])!=sit[j]){
                continue;
            }
            for (int k=1; k<=cnt; k++){
                if ((sit[k]&vis[i-1])!=sit[k]){
                    continue;
                }
                if ((sit[j]&sit[k])==0){
                    dp[i][j]=(dp[i][j]+dp[i-1][k])%Mod;
                }
            }
        }
    }
    int ans=0;
    for (int i=1; i<=cnt; i++){
        ans=(ans+dp[n][i])%Mod;
    }
    printf("%d\n", ans);
    
    return 0;
}