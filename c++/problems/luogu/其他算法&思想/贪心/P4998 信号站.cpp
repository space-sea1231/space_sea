#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int L=1e6;
int n, m;
int a[N<<1],num[N<<1], dis[N<<1];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        int x;
        cin >> x;
        a[x+L]++;
    }
    for (int i=0; i<=(L<<1); i++){
        dis[0]+=a[i]*i;
    }
    int l=0, r=n;
    for (int i=1; i<=(L<<1); i++){
        l+=a[i-1];
        dis[i]=dis[i-1]+l-r;
        r-=a[i];
    }
    sort(dis+1, dis+(L<<1)+1);
    int ans=0;
    for (int i=0; i<m; i++){
        ans+=dis[i];
    }
    printf("%lld\n", ans);

    return 0;
}