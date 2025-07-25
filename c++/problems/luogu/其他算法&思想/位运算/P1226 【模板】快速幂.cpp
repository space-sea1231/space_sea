#include <bits/stdc++.h>
using namespace std;
#define int long long 
int a, b, p;
int Power(int a, int b, int p){
    int sum=1;
    while (b){
        if (b&1){
            sum=(sum*a)%p;
        }
        a=(a*a)%p;
        b>>=1;
    }
    return sum;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> a >> b >> p;
    printf("%lld^%lld mod %lld=%lld\n", a, b, p, Power(a, b, p));

    return 0;
}