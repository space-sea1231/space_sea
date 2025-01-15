#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF=1e18+10;
int n, a, b, w, h;
bool check(int mid){
    int x=a+(mid*2LL);
    int y=b+(mid*2LL);
    if ((w/x)*(h/y)>=n){
        return 1;
    }
    if ((w/y)*(h/x)>=n){
        return 1;
    }
    return 0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> a >> b >> w >> h;
    int l=0, r=INF, ans=0;
    while (l<=r){
        int mid=(l+r)/2LL;
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