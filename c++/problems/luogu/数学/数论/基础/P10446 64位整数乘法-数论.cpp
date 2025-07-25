#include <bits/stdc++.h>
using namespace std;
#define int long long 
int a, b, p;
int Mul(int a, int b, int p){
    int sum=0;
    while (b){
        if (b&1){
            sum=(sum+a)%p;
        }
        a=(a<<1)%p;
        b>>=1;
    }
    return sum;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> a >> b >> p;
    printf("%lld\n", Mul(a, b, p));

    return 0;
}