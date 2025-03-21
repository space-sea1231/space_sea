#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+10;
const int M=1e7+10;
int n, m, cnt;
int dp[M], val[M], vis[M];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> m >> n;
    for (int i=1; i<=n; i++){
        int v, w, c;
        cin >> v >> w >> c;
        for (int j=30; j>=0; j--){
            if (c>=(1<<j)){
                c-=((1<<j));
                vis[cnt]=v*(1<<j);
                val[++cnt]=w*(1<<j);
            }
        }
    }
    for (int i=1; i<=cnt; i++){
        for (int j=m; j>=vis[i]; j--){
            dp[j]=max(dp[j], dp[j-vis[i]]+val[i]);
        }
    }
    printf("%lld\n", dp[m]);

    return 0;
}