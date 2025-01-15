#include <bits/stdc++.h>
using namespace std;
const int N=2e4+10;
int n, sum, maxn;
int a[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
        maxn=max(maxn, a[i]+a[i-1]);
        sum+=a[i];
    }
    maxn=max(maxn, a[n]+a[1]);
    sum=ceil(1.0*sum/(n/2));
    printf("%d", max(maxn, sum));
    
    return 0;
}