#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=70;
const int Mod=1e9+7;
int n, ans=1;
int a[N];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    sort(a+1, a+n+1);
    for (int i=1; i<=n; i++){
        ans=ans*(a[i]-i+1)%Mod;
    }
    printf("%lld\n", ans);

    return 0;
}