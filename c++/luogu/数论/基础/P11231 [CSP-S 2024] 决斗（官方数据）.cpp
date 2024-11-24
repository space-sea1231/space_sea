#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int cnt[N], n;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int maxn=0;
    for (int i=1; i<=n; i++){
        int a;
        cin >> a;
        maxn=max(maxn, ++cnt[a]);
    }
    printf("%d", maxn);
    
    return 0;
}