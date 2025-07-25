#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll a, b, p;
ll Mul(ll a, ll b, ll p){
    a%=p, b%=p;
    ull c=(long double)a*b/p;
    ull x=a*b, y=c*p;
    ll ans=(x%p)-(y%p);
    ans+=(ans<0?p:0);
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> a >> b >> p;
    printf("%lld\n", Mul(a, b, p));

    return 0;
}