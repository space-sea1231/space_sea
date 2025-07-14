#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

signed main(){
    freopen("std.out", "r", stdin);
    freopen("tmp.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll x;
    while (cin >> x){
        if (x<=1000000000){
            printf("%lld", x);
            // printf("%lld, ", x);
        }
        else{
            return 0;
        }
    }
    return 0;
}