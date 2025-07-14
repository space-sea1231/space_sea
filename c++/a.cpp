#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

ll n=1e12;
int cnt[11];

bool Check(ll x){
    memset(cnt, 0, sizeof(cnt));
    ll y=x<<1ll;
    while (x){
        cnt[x%10]++;
        x/=10ll;
    }
    while (y){
        cnt[y%10ll]--;
        y/=10ll;
    }
    for (int i=0; i<=9; i++){
        if (cnt[i]!=0){
            return false;
        }
    }
    return true;
}
signed main(){
    freopen("a.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (ll i=100000000000; i<=n; i++){
        if (Check(i)==true){
            cerr << i << endl;
            printf("%lld, ", i);
        }
    }
    return 0;
}