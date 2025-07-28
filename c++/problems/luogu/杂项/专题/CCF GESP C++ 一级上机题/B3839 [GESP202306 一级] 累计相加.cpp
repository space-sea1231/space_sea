#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

int n;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int sum=0;
    for (int i=1; i<=n; i++){
        sum+=i*(n-i+1);
    }
    printf("%d\n", sum);
    
    return 0;
}