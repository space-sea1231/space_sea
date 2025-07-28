#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
int n;
double ans, sum, cnt;
int a[N];
bool cmp(int a, int b){
    return a>b;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    sort(a+1, a+n+1, cmp);
    for (int i=1; i<=n; i++){
        sum+=a[i];
        cnt++;
        ans=max(ans, sum*sum/cnt);
    }
    printf("%.8lf", ans);
    
    return 0;
}