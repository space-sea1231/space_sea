#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t, n, ans;
int a[N];
int l[N], r[N];
void init(){
    memset(l, 0, sizeof(l));
    memset(a, 0, sizeof(a));
    memset(r, 0, sizeof(r));
    ans=0;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        init();
        cin >> n;
        for (int i=1; i<=n; i++){
            cin >> a[i];
        }
        for (int i=1; i<=n; i++){
            l[i]=max(l[i-1]-1, a[i]);
        }
        for (int i=n; i>=1; i--){
            r[i]=max(r[i+1]-1, a[i]);
        }
        for (int i=2; i<n; i++){
            ans=max(ans, l[i-1]+a[i]+r[i+1]);
        }
        printf("%d\n", ans-2);
    }

    return 0;
}