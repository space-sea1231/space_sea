#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace IO{
    const int BUF=1<<21;
    char buff[BUF],*p1=buff,*p2=buff;
    #define gc() (p1==p2&&(p2=((p1=buff)+fread(buff,1,BUF,stdin)),p1==p2)?EOF:*p1++)
    template<typename T>inline void read(T &x){
        char ch=gc();x=0;int f=1;
        while(!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
        while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=gc();
        x*=f;
    }
    char obuf[BUF],*p3=obuf;
    inline void pc(char ch){
        if(p3-obuf<BUF) *p3++=ch;
        else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;
    }
    inline void put(const char *s){while(*s) pc(*s),++s;}
    char ch[64];int ctop;
    template<typename T>inline void print(T x){
    	if(x<0) x=~x+1,pc('-');
        if(!x) return pc(48);
        while(x) ch[++ctop]=x%10^48,x/=10;
        while(ctop) pc(ch[ctop--]);
    }
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);p3=obuf;}
}
using namespace IO;
const int N = 1e6+5,mod = 998244353;
inline int qpow(int x,int y)
{
	int res = 1;
	while(y)
	{
		if(y&1) res = res*x%mod;
		y>>=1;
		x = x*x%mod;
	}
	return res;
}
int n,a[N],p[N],lt[N],rt[N],f[N],now[N],pw[N],stk[N],top,t[N],s[N];
inline int work(int fir,int q,int l,int r)//����Ϊ fir������Ϊ q��l~r �ĵȱ����� 
{
	fir = fir*qpow(q,l)%mod;
	if(q==1) return fir*(r-l+1);
	return fir*(qpow(q,r-l+1)-1)%mod*qpow(q-1,mod-2)%mod;
}
signed main()
{
	freopen("god.in","r",stdin);
	freopen("god.out","w",stdout);
	read(n);
	pw[0] = 1;
	for(int i = 1;i<N;i++) pw[i] = pw[i-1]*2%mod;
	for(int i = 1;i<=n;i++)
		read(a[i]),p[a[i]] = i;
	stk[top = 0] = 0;
	for(int i = 1;i<=n;i++) // lt[i] 前面第一个比ai大的数的位置
	{
		while(top&&a[stk[top]]<a[i]) top--;
		lt[i] = stk[top],stk[++top] = i;
	}
	stk[top = 0] = n+1;
	for(int i = n;i;i--) // lt[i] 后面第一个比ai大的数的位置
	{
		while(top&&a[stk[top]]<a[i]) top--;
		rt[i] = stk[top],stk[++top] = i;
	}
	f[n+1] = 1,now[n+1] = 0,a[n+1] = 2e18;
	for(int i = 1;i<=n+1;i++) t[i] = n;
	int ans = 0;
	for(int i = n;i;i--)
	{
		int x = p[i],j = rt[x];
		if(t[j]!=i) (ans+=work(f[j]*qpow(2,(n-(j-now[j]-1))*t[j]-1)%mod,pw[j-now[j]+1],i+1,t[j]-1))%=mod;
		f[j] = f[j]*qpow(pw[n-(j-now[j]-1)],t[j]-i)%mod;
		f[x] = f[j];
		now[x] = now[rt[x]],now[rt[x]] = x;
		t[x] = t[j] = i;
	}
	for(int i = 1;i<=n+1;i++)
	{
		(ans+=work(f[i]*qpow(2,(n-(i-now[i]-1))*t[i]-1)%mod,pw[i-now[i]+1],1,t[i]-1))%=mod;
		f[i] = f[i]*qpow(pw[n-(i-now[i]-1)],t[i])%mod;
		(ans+=f[i])%=mod;
	}
	print(ans);
	flush();
	return 0;
}
