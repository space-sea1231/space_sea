#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int T,n,ans[N],cnt,a[N],Ans;
string s;
void g(int x){
    ans[++cnt]=x;
    a[x+1]=!a[x]&!a[x+1];
    a[x-1]=!a[x]&!a[x-1];
}
void sol(int l,int r){
    if(r-l+1==3&&a[l+1]){Ans++;return;}
    if(r-l+1<=2){
        for(int i=l;i<=r;++i)Ans+=a[i];
        return;
    } if(a[l]){Ans++,sol(l+1,r);return;}
    if(a[r]){Ans++,sol(l,r-1);return;}
    if(!a[l+1]){Ans++,g(l+1),sol(l+1,r);return;}
    if(!a[r-1]){Ans++,g(r-1),sol(l,r-1);return;}
    g(l+2),g(l+1),Ans++,sol(l+1,r);
}
signed main(){
    ios::sync_with_stdio(false);
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    int i,j,k,l,r,x,y,z;
    cin>>T;
    while(T--){
        cin>>s,n=s.size(),s=" "+s,cnt=Ans=0;
        for(x=0,i=1;i<=n;++i)x+=(a[i]=s[i]=='1');
        sol(1,n),printf("%d %d\n",Ans,cnt);
        for(i=1;i<=cnt;++i)printf("%d ",ans[i]);puts("");
    }
    return 0;
}