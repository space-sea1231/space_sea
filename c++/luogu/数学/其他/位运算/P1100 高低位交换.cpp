#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=20;
int a, ans;
int high[N], low[N];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> a;
    for (int i=16; i<=31; i++){
        ans+=(a&1)<<i;
        a>>=1;
    }
    for (int i=0; i<=15; i++){
        ans+=(a&1)<<i;
        a>>=1;
    }
    printf("%lld\n", ans);
    
    return 0;
}