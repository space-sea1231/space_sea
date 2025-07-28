#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int INF=LONG_LONG_MAX;
int n;
int t[N], w[N];
int maxn[N], minn[N], sum[N];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    maxn[n+1]=-INF, minn[n+1]=INF;
    for (int i=1; i<=n; i++) cin >> t[i];
    for (int i=1; i<=n; i++) cin >> w[i];
    for (int i=n; i>=1; i--){
        sum[i]=sum[i+1]+w[i];
        maxn[i]=max(maxn[i+1], sum[i]);
        minn[i]=min(minn[i+1], t[i]);
    }
    int ans=0, cnt=0;
    for (int i=1; i<=n; i++){
        if (sum[i]==maxn[i]&&sum[i]>0){
            cnt=minn[i];
        }
        ans+=cnt*w[i];
    }
    printf("%lld\n", ans);

    return 0;
}