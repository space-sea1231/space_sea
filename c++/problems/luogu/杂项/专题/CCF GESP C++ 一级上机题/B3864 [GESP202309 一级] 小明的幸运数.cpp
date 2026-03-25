#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

int k, l, r;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> k >> l >> r;
    int sum=0;
    for (int i=l; i<=r; i++){
        if (i%10==k||i%k==0){
            sum+=i;
        }
    }
    printf("%d\n", sum);

    return 0;
}