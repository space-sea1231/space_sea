/* 年挽红枫，溪傍芦荻。*/
#define DEBUG true
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
#define i128 __int128
#define i64 long long
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
const int N=2100;
const int inf=1e9;
int T;
int n,a[N];
int f[N],t[N],res;
int main(){
    for(read(T);T;T--){
        read(n);
        for(int i=1;i<=n;i++)
            read(a[i]);
        for(int i=1,j;i<=n;i++){
            j=i;
            while(a[j+1]>a[j]) j++;
            res+=(j-i+2)*(j-i+1)/2;
            for(int k=i;k<=j;k++)
                f[k]=i,t[k]=j;
        }
        int cur=res;
        a[0]=-inf,a[1]=inf;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(f[i]==f[j]) continue;
                int sum=res;
                sum-=(i-f[i]+1)*(t[i]-i+1)-1;
                sum-=(j-f[j]+1)*(t[j]-j+1)-1;
                if(a[i-1]<a[j]&&a[j]<a[i+1])
                    sum+=(i-f[i-1]+1)*(t[i+1]-i+1)-1;
                else if(a[i-1]<a[j]) sum+=i-f[i-1]+1;
                else if(a[i]<a[i+1]) sum+=t[i+1]-i+1;
                if(a[j-1]<a[i]&&a[i]<a[j+1])
                    sum+=(j-f[j-1]+1)*(t[j+1]-j+1)-1;
                else if(a[j-1]<a[i]) sum+=j-f[j-1]+1;
                else if(a[j]<a[j+1]) sum+=t[j+1]-j+1;
                chkmax(cur,sum);
            }
        }
        print(cur,'\n');
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