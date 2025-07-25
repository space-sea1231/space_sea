#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

ll a, b, c, x, y;

ll Exgcd(ll a, ll b, ll &x, ll &y){
    if (b==0){x=1, y=0; return a;}
    ll d=Exgcd(b, a%b, x, y);
    ll z=x; x=y, y=z-y*(a/b);
    return d;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> c;
    int d=Exgcd(a, b, x, y);
    if (-c%d!=0){
        printf("-1\n");
    }
    else{
        printf("%lld %lld\n", x*(-c/d), y*(-c/d));
    }

    return 0;
}