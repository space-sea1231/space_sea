#include <bits/stdc++.h>
#define int long long
using namespace std;
using i32=int32_t;
int mod;
struct barrett{
	uint32_t m;
	uint64_t im;
	void init(uint32_t _m){
		m=_m;
		im=uint64_t(-1)/m+1;
	}
	inline uint32_t reduce(uint64_t z) const{
		uint64_t x=(uint64_t)((__uint128_t)z*im>>64);
		uint64_t y=x*m;
		return z-y+(z<y?m:0);
	}
	inline uint32_t mul(uint32_t a,uint32_t b) const{
		return reduce((uint64_t)a*b);
	}
}bt;
inline void add(int &i,int j){
	i+=j;
	if(i>=mod) i-=mod;
}
inline void del(int &i,int j){
	i-=j;
	if(i<0) i+=mod;
}
inline int mul(int i,int j){
	return bt.mul(i,j);
}
struct degree_dp{
	int n,w;
	vector<i32> f[3],g,num,c2,c3;
	degree_dp(int _n):n(_n),w(n+1),g(w*w),num(w),c2(w),c3(w){
		for(int i=0;i<3;i++) f[i].resize(w*w);
		vector<i32> zero(w);
		for(int i=0;i<=n;i++){
			num[i]=i%mod;
			c2[i]=(__int128)i*(i-1)/2%mod;
			c3[i]=(__int128)i*(i-1)*(i-2)/6%mod;
		}
		for(int s=0;s<=n;s++){
			auto &now=f[s%3];
			auto &pre=f[(s+2)%3];
			auto &pre2=f[(s+1)%3];
			if(s==0){
				now[0]=g[0]=1%mod;
				continue;
			}
			for(int b=(s&1);b<=s;b+=2){
				int c=s-b,ret=0;
				if(b){
					uint64_t z=0;
					if(c>=2) z+=(uint64_t)c2[c]*pre[b+1];
					if(b>=2&&c) z+=(uint64_t)mul(num[b-1],num[c])*pre[w+b-1];
					if(b>=3) z+=(uint64_t)c2[b-1]*pre[2*w+b-3];
					ret=bt.reduce(z);
				}
				else{
					if(c>=4) ret=mul(c3[c-1],pre[3]);
					g[c]=ret;
				}
				now[b]=ret;
			}
			for(int a=1;a<=s;a++){
				const i32 *p2=a>=2?pre2.data()+(a-2)*w:zero.data();
				const i32 *p0=pre.data()+a*w;
				const i32 *p1=pre.data()+(a-1)*w;
				int ca=num[a-1];
				if(!(s&1)){
					int c=s-a;
					uint64_t z=(uint64_t)ca*p2[0]+(uint64_t)num[c]*p1[1];
					int ret=bt.reduce(z);
					now[a*w]=ret;
					g[a*w+c]=ret;
				}
				for(int b=(s&1)?1:2;a+b<=s;b+=2){
					int c=s-a-b;
					uint64_t z=(uint64_t)ca*p2[b]+(uint64_t)num[b]*p0[b-1]+(uint64_t)num[c]*p1[b+1];
					now[a*w+b]=bt.reduce(z);
				}
			}
		}
	}
	int get(int a,int b){
		return g[a*w+b];
	}
};
void solve(){
	int n,K;
	cin>>n>>K>>mod;
	bt.init(mod);
	if((n&1)||n<4){
		for(int k=0;k<=K;k++) cout<<0<<" \n"[k==K];
		return;
	}
	int w=n+1;
	vector<vector<i32>> C(w,vector<i32>(w));
	for(int i=0;i<=n;i++){
		C[i][0]=C[i][i]=1%mod;
		for(int j=1;j<i;j++){
			int x=C[i-1][j-1]+C[i-1][j];
			if(x>=mod) x-=mod;
			C[i][j]=x;
		}
	}
	degree_dp gd(n);
	vector<vector<i32>> f(5,vector<i32>(w*w));
	vector<i32> zero(w);
	vector<int> F(w);
	f[0][0]=1%mod;
	F[0]=gd.get(0,n);
	for(int s=3;s<=n;s++){
		auto &now=f[s%5];
		auto &pre3=f[(s+2)%5];
		auto &pre4=f[(s+1)%5];
		int c3=C[s-1][2],c4=s>=4?C[s-1][3]:0;
		int choose=C[n][s];
		for(int a=(s&1);a<=s;a+=2){
			i32 *cur=now.data()+a*w;
			if(s>=10&&a<=s-10){
				int os=s-10,ol=(os+2)/3;
				ol=max(ol,(os-a+1)/2);
				if(3*os>5*a) ol=max(ol,(3*os-5*a+3)/4);
				int oh=(3*os-2*a)/3;
				if(ol<=oh) memset(cur+ol,0,(oh-ol+1)*sizeof(i32));
			}
			int lo=(s+2)/3;
			lo=max(lo,(s-a+1)/2);
			if(3*s>5*a) lo=max(lo,(3*s-5*a+3)/4);
			int hi=(3*s-2*a)/3;
			if(lo>hi) continue;
			const i32 *p31=a>=3?pre3.data()+(a-3)*w:zero.data();
			const i32 *p32=a>=1?pre3.data()+(a-1)*w:zero.data();
			const i32 *p4d=a>=2?pre4.data()+(a-2)*w:zero.data();
			const i32 *p4k=pre4.data()+a*w;
			int ways=mul(choose,gd.get(a,n-s));
			for(int j=lo;j<=hi;j++){
				int x=p31[j-1]-3ll*p32[j-1];
				if(x<0) x+=3*mod;
				if(x>=mod) x-=mod;
				if(x>=mod) x-=mod;
				uint64_t y=0;
				if(s>=4){
					y=6ull*p4d[j-2];
					if(j>=3) y+=4ull*p4k[j-3];
					if(j>=4) y+=p4k[j-4];
				}
				int v=bt.reduce((uint64_t)c3*x+(uint64_t)c4*y);
				cur[j]=v;
				if(ways) F[j]=bt.reduce((uint64_t)ways*v+F[j]);
			}
		}
	}
	vector<int> ans(w);
	for(int k=0;k<=n;k++){
		for(int j=k;j<=n;j++){
			int v=mul(C[j][k],F[j]);
			if((j-k)&1) del(ans[k],v);
			else add(ans[k],v);
		}
	}
	for(int k=0;k<=K;k++) cout<<(k<=n?ans[k]:0)<<" \n"[k==K];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--) solve();
	return 0;
}
