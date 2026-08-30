#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define P(x) (ll(x)*(x))
#define p(x) ((x)*(x))
const int N=4e5+5;
const ll T=0x3f3f3f3f3f3f3f3f;
char buf[1<<23],*p1,*p2,c;
#define gc (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<22,stdin),p1==p2))?EOF:*p1++
inline void read(int &x){
    bool flag=x=0;while(!isdigit(c=gc))if(c=='-')flag=1;
    do x=(x<<3)+(x<<1)+(c^'0');while(isdigit(c=gc));if(flag)x=-x;
}
ll ans=T;
int lc[N],rc[N],lx[N],ly[N],rx[N],ry[N],nowt,Id[N],n,Root;
struct Node{int x,y;}a[N];
inline bool cmpx(const int &x,const int &y){return a[x].x<a[y].x;}
inline bool cmpy(const int &x,const int &y){return a[x].y<a[y].y;}
#define Dis(a1,a2) (P(a[a1].x-a[a2].x)+P(a[a1].y-a[a2].y))
inline ll fac(int x){
    if(!x)return T+50;ll res=0;
    if(lx[x]>a[nowt].x)res+=P(lx[x]-a[nowt].x);
    if(rx[x]<a[nowt].x)res+=P(a[nowt].x-rx[x]);
    if(ly[x]>a[nowt].y)res+=P(ly[x]-a[nowt].y);
    if(ry[x]<a[nowt].y)res+=P(a[nowt].y-ry[x]);
    return res;
}
inline void Maintain(int x){
    #define Max(a,b) (a>b?a:b)
    #define Min(a,b) (a<b?a:b)
    lx[x]=rx[x]=a[x].x;ly[x]=ry[x]=a[x].y;
    if(lc[x])lx[x]=Min(lx[x],lx[lc[x]]),rx[x]=Max(rx[x],rx[lc[x]]),
    ly[x]=Min(ly[x],ly[lc[x]]),ry[x]=Max(ry[x],ry[lc[x]]);
    if(rc[x])lx[x]=Min(lx[x],lx[rc[x]]),rx[x]=Max(rx[x],rx[rc[x]]),
    ly[x]=Min(ly[x],ly[rc[x]]),ry[x]=Max(ry[x],ry[rc[x]]);
    #undef Max
    #undef Min
}
double px,py,fx,fy;
int build(int l,int r){
    if(r<l)return 0;int mid=l+((r-l)>>1),x;px=py=fx=fy=0;
    for(x=l;x<=r;++x)px+=a[Id[x]].x,py+=a[Id[x]].y;px/=r-l+1;py/=r-l+1;
    for(x=l;x<=r;++x)fx+=p(px-a[Id[x]].x),fy+=p(py-a[Id[x]].y);
    if(fx>fy)nth_element(Id+l,Id+mid,Id+r+1,cmpx);
    else nth_element(Id+l,Id+mid,Id+r+1,cmpy);x=Id[mid];
    lc[x]=build(l,mid-1);rc[x]=build(mid+1,r);Maintain(x);
    return x;
}
void asks(int x){
    if(x!=nowt)ans=min(ans,Dis(x,nowt));
    ll fl=fac(lc[x]),fr=fac(rc[x]);
    if(fl<fr){if(fl<ans){asks(lc[x]);if(fr<ans)asks(rc[x]);}}
    else{if(fr<ans)asks(rc[x]);if(fl<ans)asks(lc[x]);}
}
int main(){
    int i;read(n);
    for(i=1;i<=n;Id[i]=i,++i)read(a[i].x),read(a[i].y);
    Root=build(1,n);
    for(i=1;i<=n;++i)nowt=Id[i],asks(Root);
    printf("%lld\n",ans);
    return 0;
}
