#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x;
    cin >> x;
    int cnt=0;
    for (int i=1; i*i<=x; i++){
        if (x%i==0){
            cnt++;
        }
    }
    printf("%d\n", cnt);

    return 0;
}