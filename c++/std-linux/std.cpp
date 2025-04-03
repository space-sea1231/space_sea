#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int K=4;
int n, m;
int val[N], opt[N];
int calc(int bit, int ans){
    for (int i=1; i<=n; i++){
        int x=(val[i]>>bit)&1;
        if (opt[i]==1) ans&=x;
        if (opt[i]==2) ans^=x;
        if (opt[i]==3) ans|=x;
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        char c[4];
        cin >> c >> val[i];
        if (c=="AND") opt[i]=1;
        if (c=="XOR") opt[i]=2;
        if (c=="OR") opt[i]=3;
    }
    int sum=0, ans=0;
    for (int i=30; i>=0; i--){
        int res0=calc(i, 0);
        int res1=calc(i, 1);
        if (sum+(1<<i)<=m&&res1>res0){
            sum+=(1<<i);
            ans+=(res1<<i);
        }
        else{
            ans+=(res0<<i);
        }
    }
    printf("%d\n", ans);

    return 0;
}