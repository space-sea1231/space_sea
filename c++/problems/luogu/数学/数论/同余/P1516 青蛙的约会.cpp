#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

ll xa, xb, va, vb, l, x, y;

ll Exgcd(ll a, ll b, ll &x, ll &y){
    if (b==0){x=1, y=0; return a;}
    ll d=Exgcd(b, a%b, x, y);
    ll z=x; x=y, y=z-y*(a/b);
    return d;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> xa >> xb >> va >> vb >> l;
    int d=Exgcd(vb-va, l, x, y);
    if ((xa-xb)%d!=0){
        printf("Impossible\n");
    }
    else{
        x=((x*(xa-xb)/d)%l+abs(l/d))%abs(l/d);
        printf("%lld\n", x);
    }

    return 0;
}