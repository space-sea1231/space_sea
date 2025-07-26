#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls u<<1
#define rs u<<1|1
const int N=4e5+5,M=1ll<<32;
int t,n,a[N],F[N],R[N],p[N];
int T[N<<2],ans,bs;
bool fl,v[N];
int g(int x){return R[F[x]]-F[x]+1;}
void pushup(int u){T[u]=max(T[ls],T[rs]);}
void build(int l,int r,int u){
    if(l==r){
        if(!fl){
            int x=p[l];T[u]=-(R[F[x]]-x+1)*(x-F[x]);
            if(R[F[x]]==x&&x<n)T[u]+=g(x+1);
        } else {
            int x=p[l];T[u]=-(R[F[x]]-x)*(x-F[x]+1);
            if(F[x]==x&&x>1)T[u]+=g(x-1);
        } return;
    } int mid=l+r>>1;
    build(l,mid,ls),build(mid+1,r,rs);
    pushup(u);
}
void upt(int l,int r,int u,int x,int v){
    if(l==r){T[u]+=v;return;}
    int mid=l+r>>1;
    x<=mid?upt(l,mid,ls,x,v):upt(mid+1,r,rs,x,v);
    pushup(u);
}
int que(int l,int r,int u,int lx,int rx){
    if(r<lx||rx<l)return -2e18;
    if(lx<=l&&r<=rx)return T[u];
    int mid=l+r>>1;
    return max(que(l,mid,ls,lx,rx),que(mid+1,r,rs,lx,rx));
}
signed main(){
    ios::sync_with_stdio(false);
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    int i,j,k,l,r,x,y,z;
    cin>>t,a[0]=2e9;
    while(t--){
        cin>>n,bs=0,ans=2e18,fl=0;
        for(i=1;i<=n;++i){
            cin>>a[i],F[i]=p[i]=i;
            if(a[i]>a[i-1])F[i]=F[i-1];
            R[F[i]]=i,bs+=g(i),ans=bs;
        } sort(p+1,p+1+n,[&](int x,int y){return a[x]<a[y];});
        for(build(1,n,1),i=1;i<=n;++i){
            x=p[i],v[x]=true,r=R[F[x]];
            if(x>1&&F[x]==x){
                y=F[x-1];
                if(y>1&&a[y]>a[x])upt(1,n,1,a[y-1],(v[y-1]?g(y-1):1)*g(x));
                ans=max(ans,bs+g(x)*g(x-1)+que(1,n,1,a[x-1]+1,(g(x)>1?a[x+1]-1:n)));
                if(y>1&&a[y]>a[x])upt(1,n,1,a[y-1],-(v[y-1]?g(y-1):1)*g(x));
                upt(1,n,1,a[x-1],-(v[x-1]?g(x-1):1)*g(x));
                if((g(x-1)==1||a[x]>a[x-2])&&(g(x)==1||a[x-1]<a[x+1]))
                    ans=max(ans,bs+g(x)*g(x-1));
            } if(x<r)v[x+1]=true;
            if(x<r-1)upt(1,n,1,a[x+1],(r-x)*(x-F[x]+1));
            if(x==r-1)upt(1,n,1,a[x+1],(r<n&&!v[r+1]?g(r+1)+1:1)*(x-F[x]+1));
        } for(i=1;i<=n;++i)v[i]=0; reverse(p+1,p+1+n),fl=1;
        for(build(1,n,1),i=1;i<=n;++i){
            x=p[i],v[x]=true,r=R[F[x]];
            if(x<n&&r==x){
                y=x+1;
                if(R[y]<n&&a[R[y]]<a[x])upt(1,n,1,a[R[y]+1],(v[R[y]+1]?g(R[y]+1):1)*g(x));
                ans=max(ans,bs+g(x)*g(x+1)+que(1,n,1,g(x)>1?a[x-1]+1:1,a[x+1]-1));
                if(R[y]<n&&a[R[y]]<a[x])upt(1,n,1,a[R[y]+1],-(v[R[y]+1]?g(R[y]+1):1)*g(x));
                upt(1,n,1,a[x+1],-(v[x+1]?g(x+1):1)*g(x));
            } if(x>F[x])v[x-1]=true;
            if(x>F[x]+1)upt(1,n,1,a[x-1],(r-x+1)*(x-F[x]));
            if(x==F[x]+1)upt(1,n,1,a[x-1],(F[x]>1&&!v[F[x]-1]?g(F[x]-1)+1:1)*(r-x+1));
        } for(i=1;i<=n;++i)v[i]=0; printf("%lld\n",ans%M);
    }
    return 0;
}