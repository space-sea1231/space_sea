#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=60;
int n, m;
int cnt[N], len[N];
void init(){
    cnt[0]=1;
    len[0]=1;
    for (int i=1; i<N; i++){
        cnt[i]=(cnt[i-1]<<1LL)+1;
        len[i]=(len[i-1]<<1LL)+3;
    }
}
int dfs(int n, int m){
    if (n==0){
        return 1;
    }
    if (m<=1){
        return 0;
    }
    if (m<=len[n-1]+1){
        return dfs(n-1, m-1);
    }
    if (m<=len[n-1]+2){
        return cnt[n-1]+1;
    }
    if (m<=(len[n-1]<<1LL)+2){
        return cnt[n-1]+1+dfs(n-1, m-len[n-1]-2);
    }
    if (m<=len[n]){
        return cnt[n];
    }
    return 0;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    init();
    cin >> n >> m;
    printf("%lld\n", dfs(n, m));

    return 0;
}