#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int sx, sy, fx, fy;
    cin >> sx >> sy >> fx >> fy;
    printf("%d\n", (fx-sx)*60+fy-sy);
    
    return 0;
}