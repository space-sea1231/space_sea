#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod=998244353;
int now, n;
__int128 sum;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    bool flag=0;
    int last;
    for (int i=1; n>=(1LL<<now); i++){
        n-=(1LL<<now);
        sum=(__int128)(sum+(1LL<<now)%Mod*i%Mod)%Mod;
        now++;
        if (!flag){
            flag=1;
            now=0;
        }
        last=i;
    }
    if (n){
        sum=(__int128)(sum+n*(last+1)%Mod)%Mod;
    }
    printf("%lld\n", (int)sum);

    return 0;
}