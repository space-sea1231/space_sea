#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int t, n, L, R;
int l[N], mid[N], r[N];
int l_top, mid_top, r_top;
int l_tail, mid_tail, r_tail;
int tmp1, tmp2, ans, sum;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        n, L, R, ans=0, sum=0;
        l_top=0, mid_top=0, r_top=0;
        l_tail=0, mid_tail=0, r_tail=0;
        tmp1=0, tmp2=0;
        cin >> n >> L >> R;
        for (int i=1; i<=n; i++){
            if (i<L){
                cin >> l[++l_top];
            }
            if (L<=i&&i<=R){
                cin >> mid[++mid_top];
                sum+=mid[mid_top];
                mid[mid_top]=-mid[mid_top];
            }
            if (i>R){
                cin >> r[++r_top];
            }
        }
        sort(l+1, l+l_top+1);
        sort(mid+1, mid+mid_top+1);
        sort(r+1, r+r_top+1);
        while (++l_tail<=l_top&&++mid_tail<=mid_top&&l[l_tail]<-mid[mid_tail]){
            tmp1+=-mid[mid_tail]-l[l_tail];
        }
        mid_tail=0;
        while (++r_tail<=r_top&&++mid_tail<=mid_top&&r[r_tail]<-mid[mid_tail]){
            tmp2+=-mid[mid_tail]-r[r_tail];
        }
        ans=max(tmp1, tmp2);
        printf("%lld\n", sum-ans);
    }

    return 0;
}