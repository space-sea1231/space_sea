```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5;
const int mod=1e9+7;
int T,tot;
int lg[N],inv[N],fac[N];
int mi[N],cnt;
int ksm(int x,int y){
    int ans=1,base=x;
    while(y){
        if(y&1)ans*=base;
        base*=base;
        ans%=mod;base%=mod;
        y/=2;
    }
    return ans;
}
int C(int a,int b){
    if(a<b)return 0;
    return (fac[a]*inv[b]%mod)*inv[a-b]%mod;
}
void init(){
    lg[0]=0;
    cnt=-1;
    for(int i=1;i<N;i*=2){
        mi[++cnt]=i;
    }
    mi[++cnt]=1e9;
    int lt=0;
    inv[0]=fac[0]=1;
    for(int i=1;i<N;i++){
        if(i>mi[lt])lt++;
        lg[i]=lt;
        fac[i]=(fac[i-1]*(i))%mod;
    }
    inv[N-1]=ksm(fac[N-1],mod-2);
    for(int i=N-2;i>=1;i--){
        inv[i]=(inv[i+1]*(i+1))%mod;
    }
    // cout << inv[1]<<"\n";
    return ;
}
signed main(){
    cin >> T;
    // lg[0]=0;
    init();
    // cout << lg[7];
    while(T--){
        int n;
        cin >> n;
        int m=lg[n];
        int res=0;
        for(int i=0;i<=m;i++){
            if(i%2==0){
                res+=(C(m,i)*C(mi[m-i],n)%mod)%mod;
                res%=mod;
            }else{
                res-=(C(m,i)*C(mi[m-i],n)%mod)%mod;
                res+=mod;
                res%=mod;
            }
            // cout << mi[m-i] << " ";
        }
        cout << (res*fac[n]%mod)*inv[m]%mod<<"\n";
    }
    return 0;
}
```