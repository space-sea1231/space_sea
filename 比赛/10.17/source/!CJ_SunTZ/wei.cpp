#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int pos[400005];
int p[55];
int n;
int getans(){
    int all=0;
    int ans=0;
    for(int i=1;i<=n;i++){
        if(pos[i]<pos[i-1])all=0;
        all++;
        ans+=all;
    }
    return ans;
}
void solve(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&pos[i]);
    }
    int ans=getans();
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            swap(pos[i],pos[j]);
            ans=max(ans,getans());
            // printf("swap %lld %lld ans=%lld\n",i,j,getans());
            swap(pos[i],pos[j]);
        }
    }
    printf("%lld\n",ans%(1<<32));
    return;
}
signed main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    scanf("%lld",&T);
    while(T--){
        solve();
    }
    return 0;
}
/*

写成01的话很容易给出矩阵转移,这样就可以拿到27分

常数太大
*/