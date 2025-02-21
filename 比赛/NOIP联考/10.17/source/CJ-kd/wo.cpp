#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N=2e6+5,mod=998244353;
int n,fac[N];
pair<int,int> a[N];
inline int read(){
    register int x=0,t=0;
    static char ch=getchar();
    while(!isdigit(ch)) t|=(ch=='-'),ch=getchar();
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return t?-x:x;
}
inline int ksm(int a,int b){
	int x=1;
	while(b){
		if(b&1) x=x*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return x;
}
inline int A(int x,int y){
	if(y==0) return 1;
	return fac[x]*ksm(fac[x-y],mod-2)%mod;
}
inline void work(){
	n=read();
	int cnt1=0,cnt0=0,cntbig=0,cntlit=0;
	int sizbig,sizlit;
	sizbig=sizlit=n;
	for(register int i=1;i<=n;i++){
		a[i].first=read();
		a[i].second=read();
		if(a[i].first>a[i].second) swap(a[i].first,a[i].second);
		if(a[i].first&&a[i].second) cnt1++;
		if(!a[i].first&&!a[i].second) cnt0++;
		if(!a[i].first&&a[i].second) a[i].second>n?cntbig++:cntlit++;
		if(a[i].first) a[i].first>n?sizbig--:sizlit--;
		if(a[i].second) a[i].second>n?sizbig--:sizlit--;
	}
	printf("%lld\n",ksm(2,cnt0)*A(sizbig,cntlit)%mod*A(sizlit,cntbig)%mod*A(cnt0,cnt0)%mod*A(cnt0,cnt0)%mod);
}
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	fac[0]=1;
	for(register int i=1;i<=2e6;i++) fac[i]=fac[i-1]*i%mod;
	int T=read();
	while(T--) work();
	return 0;
}