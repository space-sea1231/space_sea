#include <bits/stdc++.h>
using namespace std;
int n, m;
int main(){
    freopen("life.in", "r", stdin);
    freopen("life.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    if (n>=m){
        printf("YES\n%d\n", m);
    }else{
        printf("NO\n0\n");
    }

    return 0;
}