#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
const int INF=1e18+10;
int n, k;
bool a[N];
string s;
bool check(int mid){
    int cnt=0;
    int x=0, y=0;
    for (int i=1; i<=n; i++){
        if (a[i]){
            y++;
        }else{
            x++;
        }
        if (x*y>mid){
            cnt++;
            x=0, y=0;
            i--;
        }
    }
    if (x||y){
        cnt++;
    }
    if (cnt>k){
        return 0;
    }
    return 1;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> k >> s;
    for (int i=0; i<s.size(); i++){
        a[i+1]=s[i]-'0';
    }
    int l=0, r=INF, ans=0;
    while (l<=r){
        int mid=(l+r)>>1LL;
        if (check(mid)){
            r=mid-1;
            ans=mid;
        }else{
            l=mid+1;
        }
    }
    printf("%lld\n", ans);

    return 0;
}