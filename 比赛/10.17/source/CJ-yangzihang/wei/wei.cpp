#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod=(1LL<<32);
const int N=4e5+10;
int t, n, a[N], cnm[N];
void init(){
    int sum=0;
    for (int i=1; i<N; i++){
        sum=(sum+i)%Mod;
        cnm[i]=sum;
    }
}
signed main(){
    freopen("wei.in", "r", stdin);
    freopen("wei.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    init();
    cin >> t;
    while (t--){
        cin >> n;
        for (int i=1; i<=n; i++){
            cin >> a[i];
        }
        printf("%lld\n", cnm[n]);
    }

    return 0;
}