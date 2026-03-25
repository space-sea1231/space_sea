#include <iostream>
#include <stdio.h>
#define int long long

using namespace std;
typedef long long ll;

int a, b;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;
    printf("%lld\n", (a-1)*(b-1)-1);

    return 0;
}