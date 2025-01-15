#include<iostream>
#include<algorithm>
using namespace std;
struct Node{
    int l,r;
    bool operator <(Node &x)const{
        return l+r>x.l+x.r;
    }
}a[1000006];
int fact[1000006];
int inv[1000006];
const int mod=998244353;
int qow(int base,int power){
    if(power==1) return base;
    int tmp=qow(base,power>>1);
    if(power&1){
        return 1ll*tmp*tmp%mod*base%mod;
    }
    else{
        return 1ll*tmp*tmp%mod;
    }
}
int n;
void work(){
    scanf("%d",&n);
    int c[2]={n,n};
    for(int i=1;i<=n;i++){
        scanf("%d%d",&a[i].l,&a[i].r);
        if(a[i].l!=0){
            a[i].l=a[i].l>n;
            c[a[i].l]--;
        }
        else
        a[i].l=-2;
        if(a[i].r!=0){
            a[i].r=a[i].r>n;
            c[a[i].r]--;
        }
        else
        a[i].r=-2;
        if(a[i].l<a[i].r) swap(a[i].l,a[i].r);
    }
    sort(a+1,a+n+1);
    long long ans=1;
    int left=0;
    if(c[0]-(n-c[1])==0) left=1;
    else left=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            
        }
    }
    printf("%lld\n",ans);
}
int main(){
    // freopen("wo3.in","r",stdin);
    // freopen("wo.out","w",stdout);
    int t;
    scanf("%d",&t);
    fact[0]=1;
    for(int i=1;i<=1000000;i++){
        fact[i]=1ll*fact[i-1]*i%mod*i%mod*2%mod;
        inv[i]=qow(i,mod-2);
    }
    while(t--){
        work();
    }
    return 0;
}
/*
1
3
2 3 6 0 0 0
*/