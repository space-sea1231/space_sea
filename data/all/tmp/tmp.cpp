#include <bits/stdc++.h>
using namespace std;
signed main(){
    freopen("tmp.in", "r", stdin);
    freopen("tmp.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int sum=0;
    for (int i=1; i<=10; i++){
        int a;
        cin >> a;
        sum+=a;
    }
    printf("%d\n", sum);

    return 0;
}