/* 年挽红枫，溪傍芦荻。*/
#define DEBUG false
#if DEBUG
    #include <cassert>
    #include <iostream>
    #include <cmath>
    #include <ctime>
    bool Mbe;
    void _dihan();
#endif
#include <cstdio>
#include <string>
#include <vector>
#define i128 __int128
#define i64 long long
#define mod 998244353
#define uit unsigned int
#define ull unsigned i64
template <class T> bool chkmax(T &x,T y){ return x<y?x=y,true:false; }
template <class T> bool chkmin(T &x,T y){ return x>y?x=y,true:false; }
using namespace std;
namespace io{
    #define file(s,x)\
        freopen(#s#x".in","r",stdin);\
        freopen(#s".out","w",stdout);
    const int SIZE=1<<21;
    short plc[50],rof=0;
    char ibuf[SIZE],*p1=ibuf,*p2=ibuf,obuf[SIZE],*p3=obuf;
    #define flush() (fwrite(obuf,1,p3-obuf,stdout),p3=obuf)
    #define gc() (p1==p2&&(p2=(p1=ibuf)+fread(ibuf,1,SIZE,stdin),p1==p2)?EOF:*p1++)
    #define pc(ch) (p3==obuf+SIZE&&flush(),*p3++=ch)
    class Flush{ public: ~Flush(){ flush(); } }_;
    template <class T> inline void read(T &x){
        x=0; bool flag=true; char c=gc();
        while(!isdigit(c)){ if(c=='-') flag=false; c=gc(); }
        while(isdigit(c)){ x=(x<<1)+(x<<3)+(c^48); c=gc(); }
        !flag&&(x=~(x-1));
    }
    inline void read(char &c){ while((c=gc())<'a'||c>'z'); }
    inline void read(string &s){
        s=""; char c; while((c=gc())<'a'||c>'z') ;
        s+=c; while((c=gc())>='a'&&c<='z') s+=c;
    }
    template <class T,class ...Args>
    inline void read(T &first,Args &...args){
        read(first);
        read(args...);
    }
    template <class T> inline void print(T x){
        x<0?pc('-'),x=-x:0;
        do plc[++rof]=x%10; while(x/=10);
        while(rof) pc(plc[rof--]|48);
    }
    inline void print(char c){ pc(c); }
    inline void print(string s){ for(char c : s) pc(c); }
    inline void print(const char *s){ print(string(s)); }
    template <class T,class ...Args>
    inline void print(T first,Args ...args){
        print(first);
        print(args...);
    }
}
using namespace io;
namespace math{
    inline i64 Qpow(i64 a,int x,i64 res=1){
        do
            x&1&&(res=res*a%mod),a=a*a%mod;
        while(x>>=1); return res;
    }
}
using namespace math;
const int N=1000100;
int T;
int n,m,a[N];
bool use[N];
vector<int>b;
i64 pw[N];
i64 fac[N],inv[N];
i64 A(int n,int m){
    return fac[n]*inv[n-m]%mod;
}
int main(){
    file(wo,);
    m=1e6,pw[0]=1;
    for(int i=1;i<=m;i++)
        pw[i]=pw[i-1]*2%mod;
    fac[0]=1;
    for(int i=1;i<=m;i++)
        fac[i]=fac[i-1]*i%mod;
    inv[m]=Qpow(fac[m],mod-2);
    for(int i=m;i>=1;i--)
        inv[i-1]=inv[i]*i%mod;
    for(read(T);T;T--){
        read(n);
        for(int i=1;i<=n*2;i++)
            use[i]=false;
        for(int i=1;i<=n*2;i++)
            read(a[i]);
        for(int i=1;i<=n*2;i+=2)
            if(a[i]&&a[i+1])
                use[a[i]]=use[a[i+1]]=true;
        b.clear();
        for(int i=1;i<=n*2;i++)
            if(!use[i])
                b.push_back(i);
        int mid=b[b.size()/2-1];
        int x=0,y=0,tot=0;
        for(int i=1;i<=n*2;i+=2){
            if(a[i]&&!a[i+1]
            || !a[i]&&a[i+1]){
                if((a[i]|a[i+1])<=mid)
                    x++;
                else
                    y++;
            }
            tot+=!a[i]||!a[i+1];
        }
        print(pw[tot-x-y]
            *fac[tot-x-y]%mod
            *fac[tot-x-y]%mod
            *A(tot-y,x)%mod
            *A(tot-x,y)%mod
        ,'\n');
    }
#if DEBUG
    _dihan();
#endif
    return 0;
}
#if DEBUG
    bool Med;
    void _dihan(){
        cerr<<"Memory: "<<abs(&Med-&Mbe)/1048576.0<<" MB\n";
        cerr<<"Time: "<<1e3*clock()/CLOCKS_PER_SEC<<" ms\n";
    }
#endif