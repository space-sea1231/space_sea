#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

int x, y, z, money;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x >> y >> z >> money;
    printf("%s\n%d\n", (money-2*x-5*y-3*z>0?"Yes":"No"), abs(money-2*x-5*y-3*z));

    return 0;
}s