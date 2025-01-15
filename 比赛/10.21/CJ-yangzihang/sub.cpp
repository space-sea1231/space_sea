#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod=998244353;
const int N=1e6+10;
int n,m,a[N],sum[N];
int mi(int a, int b){
    int sum=1;
    while(b){
        if (b&1){
            sum=sum*a%Mod;
        }
        a=a*a%Mod;
        b>>=1;
    }
    return sum;
}
signed main(){
    freopen("sub.in", "r", stdin);
    freopen("sub.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
        if (a[i]==0){
            sum[i]++;
        }
        sum[i]+=sum[i-1];
    }
    int l, r;
    for (int i=1; i<=m; i++){
        cin >> l >> r;
        if (r-l+1>=6){
            printf("0\n");
            continue;
        }
        printf("%lld\n", mi(3,(sum[r]-sum[l-1])));
    }

    return 0;
}