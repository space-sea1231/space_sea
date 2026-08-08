// @Nullptr_qwq_ @Nullptr_qwQ_ @Nullptr_qWq_ @Nullptr_qWQ_ @Nullptr_Qwq_ @Nullptr_QwQ_ @Nullptr_QWq_ @Nullptr_QWQ_
// File uses UTF-8 encoding.
// Genshin@tzl_index545(UID:273152640)
// Ayaka bless me!
#include <bits/stdc++.h>
#define int long long
#define i64 long long
#define i32 signed
#define ui32 unsigned
#define ui64 unsigned long long
#define i128 __int128_t
#define ui128 __uint128_t
#define rep(i,x,y,z) for(int i=(x),i##misaka=(y);i<=i##misaka;i+=(z))
#define per(i,x,y,z) for(int i=(x),i##mik0t0=(y);i>=i##mik0t0;i-=(z))
#define pb push_back
#define eb emplace_back
#define pii pair<int,int>
#define _1 first
#define _2 second
#define ld long double
#define cint const int
#define pcnt __builtin_popcountll
#define vint vector<int>
#define vpii vector<pair<int,int> >
using namespace std;

constexpr int inf=(sizeof(int)==4?0x3f3f3f3f:0x3f3f3f3f3f3f3f3f);
constexpr int mod=998244353;
constexpr long double EPS=1e-7;
constexpr int maxn=(1<<21)+10;
int gcd(int a,int b){
    if(!a || !b)	return a+b;
    unsigned az=__builtin_ctzll(a),bz=__builtin_ctzll(b);unsigned z=min(az,bz);b>>=bz;
    while(a){	a>>=az;int d=a-b;az=__builtin_ctzll(d),b=min(a,b),a=(d<0?-d:d);}
    return b<<z;
}
template<typename T>void chkmin(T& x,const T& y){return y<x?(x=y,void()):void();}
template<typename T>void chkmax(T& x,const T& y){return x<y?(x=y,void()):void();}
bool Mbe;
inline void inc(int &x,int y){	x=(x+y>=mod?x+y-mod:x+y);}
inline void dec(int &x,int y){	x=(x-y<0?x-y+mod:x-y);}

int fac[maxn],finv[maxn];
i64 fpow(i64 x,int y){
    i64 rt=1;
    for(;y;y>>=1,x=1ll*x*x%mod) if(y&1) rt=1ll*rt*x%mod;
    return rt;
}int inv(int x){	return fpow(x,mod-2);}
void init(int n){
    fac[0]=fac[1]=1;finv[0]=finv[1]=1;
    rep(i,2,n,1){	fac[i]=1ll*fac[i-1]*i%mod;}finv[n]=inv(fac[n]);
    per(i,n-1,1,1){	finv[i]=1ll*finv[i+1]*(i+1)%mod;}
}inline int C(int n,int m){
    if(n<m || n<0 || m<0)	return 0;
    return 1ll*fac[n]*finv[m]%mod*finv[n-m]%mod;
}
#ifdef ONLINE_JUDGE
constexpr bool IS_DEBUG=0;
#else
constexpr bool IS_DEBUG=1;
#endif 
template<class T> void debug_out(const T&x){if(IS_DEBUG){cerr<<x;}}
template<class T1,class T2> void debug_out(const pair<T1,T2> &x){if(IS_DEBUG){cerr<<"(";debug_out(x._1);cerr<<",";debug_out(x._2);cerr<<")";}}
template<class T> void debug_out(const vector<T> &x){if(IS_DEBUG){cerr<<"{";if(!x.empty()){rep(i,0,(int)x.size()-2,1) debug_out(x[i]),cerr<<",";debug_out(x.back());}cerr<<"}";}}
void debug(){	if(IS_DEBUG) cerr<<endl;}
template <class T,class... types>void debug(const T val,const types... args){	if(IS_DEBUG){ debug_out(val);cerr<<" ";debug(args...);}}

namespace iobuff{const int LEN=1000000;char in[LEN+5], out[LEN+5];char *pin=in, *pout=out, *ed=in, *eout=out+LEN;
    #ifndef INDEX545
    inline char gc(void){	return pin==ed&&(ed=(pin=in)+fread(in, 1, LEN, stdin), ed==in)?EOF:*pin++;}
    inline void pc(const char &c){	pout==eout&&(fwrite(out,1,LEN,stdout),pout=out);(*pout++)=c;}inline void flush()	{fwrite(out,1,pout-out,stdout),pout=out;}
    #else
    char gc(void){	return getchar();}void pc(const char &c){putchar(c);}void flush(){}
    #endif
    template<typename T> inline void scan(T &x){static int f;static char c;c=gc(), f=1, x=0;while(c<'0'||c>'9') f=(c=='-'?-1:1), c=gc();while(c>='0'&&c<='9') x=10*x+c-'0', c=gc();x*=f;}
    template<typename T> inline void putint(T x, char div){static char s[100];static int top;top=0;x<0?pc('-'), x=-x:0;while(x) s[top++]=x%10,x/=10;!top?pc('0'),0:0;while(top--) pc(s[top]+'0');pc(div);}
}using namespace iobuff;//Remember to add flush() in the end of main()
//Think at :

int a[maxn],tail[20],pre[20],has[20],rho[20],nf[20],ma[20],tmp[20],id[20];
int f[maxn];

void solve(){
    int n,k;scan(n);scan(k);  
    rep(i,0,19,1)   tail[i]=pre[i]=has[i]=rho[i]=nf[i]=ma[i]=tmp[i]=id[i]=0;
    rep(s,0,(1<<k)-1,1) f[s]=0;
    rep(i,1,n,1)    scan(a[i]);
    a[0]=a[1];
    int m=(1<<k)-1;
    rep(i,1,n,1){
        auto calc=[&](){
            rep(i,0,k-1,1)  id[i]=i;
            sort(id,id+k,[&](int x,int y){
                return tmp[x]>tmp[y];
            });
            int s=0,it=0;
            while(it<k && tmp[id[it]]>0){
                s|=1<<id[it],it++;
                chkmax(f[s],tmp[id[it-1]]);
            }
        };
        rep(b,0,k-1,1){
            if((a[i]>>b&1)==(a[i-1]>>b&1)){
                tail[b]++;
            }else{
                int ext=min(tail[b],1ll<<b);
                if(tail[b]==(1<<b)) ext+=pre[b];
                pre[b]=ext;tail[b]=1;
            }
            has[b]=0;rho[b]=-1;
            if(tail[b]>(1<<b)){
                nf[b]=(1<<b);ma[b]=(1<<b);
            }else{
                nf[b]=tail[b];ma[b]=tail[b]+pre[b];
                if(pre[b]>0){
                    has[b]=-1;
                    if(a[i]>>b&1)    rho[b]=(i-tail[b])&((1<<b+1)-1);
                    else             rho[b]=(i-tail[b]+(1<<b))&((1<<b+1)-1);
                }
            }
        }
        rep(i,0,k-1,1)  tmp[i]=nf[i];
        calc();
        rep(h,0,k-1,1)  if(has[h]){
            rep(b,0,h,1){
                int x=(rho[h]-(i&(((1<<b+1)-1)))+(1<<(b+1)))&((1<<b+1)-1);
                if((x>>b&1)==(a[i]>>b&1)){
                    if(has[b] && (rho[h]&((1<<(b+1))-1))==rho[b])    tmp[b]=ma[b];
                    else    tmp[b]=min((~a[i]>>b&1)?(1<<b)-x:(1<<(b+1))-x,tail[b]);
                }else   tmp[b]=0;
            }
            rep(b,h+1,k-1,1){
                tmp[b]=min(tail[b],(1<<b)-((rho[h]-(i&((1<<h+1)-1))+(1<<(h+1)))&((1<<(h+1))-1)));
            }
            calc();
        }
    }
    f[0]=n;
    rep(i,0,k-1,1)  rep(s,0,(1<<k)-1,1) if(s>>i&1)  chkmax(f[s^(1<<i)],f[s]);
    ui64 ha=0,pw=1;
    rep(s,0,(1<<k)-1,1){
        ha+=(pw*f[s])%mod;
        (pw*=0x0d000721)%=mod;
    }
    putint(ha,'\n');
}

bool Med;
signed main()
{
    int T;scan(T);
    while(T--)  solve();
    flush();
    return 0;
}
