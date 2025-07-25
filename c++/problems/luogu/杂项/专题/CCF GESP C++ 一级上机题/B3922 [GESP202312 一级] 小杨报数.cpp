#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

int n, m;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i=1; i<=n; i++){
        if (i%m==0) continue;
        printf("%d\n", i);
    }

    return 0;
}