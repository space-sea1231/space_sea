#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t, n, ans;
int a[N];
int gcd(int a, int b){
    if (a<b){
        swap(a, b);
    }
    while (b){
        int tmp=a%b;
        a=b;
        b=tmp;
    }
    return a;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        cin >> n;
        for (int i=1; i<=n; i++){
            cin >> a[i];
        }
        ans=0;
        for (int i=1; i*2<=n; i++){
            ans=gcd(ans, abs(a[i]-a[n-i+1]));
        }
        printf("%d\n", ans);
    }

    return 0;
}