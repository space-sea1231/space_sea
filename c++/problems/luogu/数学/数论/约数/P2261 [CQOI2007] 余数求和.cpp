#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

int n, k;
int l, r, t;
ll sum;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (l=1; l<=n; l=r+1){
        t=k/l;
        if (t>0){
            r=min(k/t, n);
        }else{
            r=n;
        }
        sum-=(ll)t*(r-l+1)*(r+l)>>1;
    }
    printf("%lld\n", sum+(ll)n*k);

    return 0;
}