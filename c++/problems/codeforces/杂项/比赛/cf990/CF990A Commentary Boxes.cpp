#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;


ll n, m, a, b;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> a >> b;
    printf("%lld\n", min((n-n/m*m)*b, ((n/m+1)*m-n)*a));

    return 0;
}