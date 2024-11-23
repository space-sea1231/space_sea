#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int M=1e6+10;
int t, n, sum, a[N], vis[M];
int edge[N], w[N], dp[N];
void init(){
    for (int i=0; i<N; i++){
        edge[i]=0, dp[i]=0;
    }
    for (int i=0; i<M; i++){
        vis[i]=0;
    }
    sum=0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        init();
        cin >> n;
        for (int i=1; i<=n; i++){
            cin >> a[i];
            if (vis[a[i]]){
                if (vis[a[i]]==i-1){
                    sum+=a[i];
                }else{
                    edge[i-1]=vis[a[i]]+1;
                    w[i-1]=a[i];
                }
            }
            vis[a[i]]=i;
        }
        for (int i=1; i<=n; i++){
            dp[i]=dp[i-1];
            if (edge[i]){
                dp[i]=max(dp[i], dp[edge[i]-1]+w[i]);
            }
        }
        sum+=dp[n];
        printf("%lld\n", sum);
    }

    return 0;
}