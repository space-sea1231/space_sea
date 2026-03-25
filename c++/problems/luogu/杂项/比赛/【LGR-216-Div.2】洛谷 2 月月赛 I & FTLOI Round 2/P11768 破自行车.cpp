#include <bits/stdc++.h>
using namespace std;
int t, a, b, k, l;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        cin >> a >> b >> k >> l;
        if (!l){
            printf("%d\n", a+b);
            continue;
        }
        int cnt=a/l+b/l;
        int last=a+b;
        if (cnt>k){
            cnt=k;
        }
        last-=cnt*l;
        int xl=a-a/l*l;
        int xr=(a/l+1)*l-a;
        int yl=b-b/l*l;
        int yr=(b/l+1)*l-b;
        if (xl-xr<yl-yr){
            swap(xl, yl);
            swap(xr, yr);
        }
        if (cnt<k&&xr<xl){
            cnt++;
            last+=xr-xl;
        }
        if (cnt<k&&yr<yl){
            cnt++;
            last+=yr-yl;
        }
        printf("%d\n", last);
    }
    return 0;
}