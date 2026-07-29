#include <iostream>
#include <stdio.h>
#define __Debug
#define int long long
using namespace std;
typedef long long ll;

const int N=5e5+10;

int n;

int Sum(int l, int r){
    return (r+l)*(r-l+1)/2;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
    }
    for (int i=1; i<=n; i++){
        int x, y, z;
        cin >> x >> y >> z;
        if (i-1<x||n-i<y){
            printf("-1 ");
            continue;
        }
        if (Sum(i-x, i-1)+z>=Sum(i+1, i+y)){
            if (Sum(1, x)+z<=Sum(n-y+1, n)){
                printf("0 ");
            }
            else{
                printf("%lld ", Sum(1, x)+z-Sum(n-y+1, n));
            }
        }
        else{
            printf("%lld ", Sum(i+1, i+y)-z-Sum(i-x, i-1));
        }
    }
    return 0;
}