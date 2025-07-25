#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=60;
const int INF=(1<<30);
int n, m;
int a[N];
bool check(int mid){
    int cnt=0;
    for (int i=1; i<=n; i++){
        if (a[i]<mid){
            cnt+=mid-a[i];
        }
    }
    if (cnt<=m&&cnt<=mid){
        return 1;
    }
    return 0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    int l=0, r=INF, ans=0;
    while (l<=r){
        int mid=(l+r)>>1;
        if (check(mid)){
            l=mid+1;
            ans=mid;
        }else{
            r=mid-1;
        }
    }
    printf("%lld\n", ans);

    return 0;
}