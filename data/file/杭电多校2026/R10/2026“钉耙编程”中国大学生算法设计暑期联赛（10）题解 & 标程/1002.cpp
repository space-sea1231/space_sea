#include<bits/stdc++.h>
#define siz(x) int((x).size())
#define all(x) std::begin(x),std::end(x)
#define fi first
#define se second
using namespace std;
using unt=unsigned;
using loli=long long;
using lolu=unsigned long long;
using pii=pair<int,int>;
mt19937_64 rng(random_device{}());
constexpr int P=998244353;
struct mint{
	int d;
	mint()=default;
	mint(int x):d(x){}
	friend std::istream&operator>>(std::istream&x,mint&y){return x>>y.d;}
	friend std::ostream&operator<<(std::ostream&x,mint y){return x<<y.d;}
	friend mint operator+(mint x,mint y){return (x.d+=y.d)<P?x.d:x.d-P;}
	mint&operator+=(mint z){return (d+=z.d)<P?d:d-=P,*this;}
	friend mint operator-(mint x,mint y){return (x.d-=y.d)<0?x.d+P:x.d;}
	mint&operator-=(mint z){return (d-=z.d)<0?d+=P:d,*this;}
	friend mint operator*(mint x,mint y){return int(1ll*x.d*y.d%P);}
	mint&operator*=(mint z){return d=int(1ll*d*z.d%P),*this;}
	static mint qpow(int x,int y=P-2){int z=1;for(;y;y>>=1,x=int(1ll*x*x%P))if(y&1)z=int(1ll*x*z%P);return z;}
	friend mint operator/(mint x,mint y){return x*=qpow(y.d);}
	mint&operator/=(mint z){return (*this)*=qpow(z.d);}
	friend mint operator^(mint x,mint y){return qpow(x.d,y.d);}
	mint&operator^=(mint z){return *this=qpow(d,z.d);}
	mint operator()(mint z)const{return qpow(d,z.d);}
	mint&operator[](mint z){return *this=qpow(d,z.d);}
	mint inv()const{return qpow(d);}
	mint pow(mint z)const{return qpow(d,z.d);}
	int operator+()const{return d;}
	mint operator-()const{return P-d;}
	int operator~()const{return ~d;}
};
mint operator""_m(lolu x){return mint(int(x%P));}
struct poly:vector<mint>{
	using vector<mint>::vector;
	static unt bswp(unt num,int len=32){
		num=(num>>16)|(num<<16);
		num=(num&0xff00ff00)>>8|(num&0x00ff00ff)<<8;
		num=(num&0xf0f0f0f0)>>4|(num&0x0f0f0f0f)<<4;
		num=(num&0xcccccccc)>>2|(num&0x33333333)<<2;
		num=(num&0xaaaaaaaa)>>1|(num&0x55555555)<<1;
		return num>>(32-len);
	}
	void dft(int T){
#define F (*this)
		for(int i=0;i<siz(F);i++)
			if(int j=bswp(i,__lg(siz(F)));i<j)std::swap(F[i],F[j]);
		for(int k=1;k<siz(F);k<<=1){
			mint w1=mint(3)^(mint(P-1)/(k*2)),u;
			if(T!=1)w1=1/w1;
			for(int i=0;i<siz(F);i+=k*2){
				u=1;
				for(int j=i;j<i+k;j++,u*=w1){
					mint c1=F[j],c2=u*F[j+k];
					F[j]=c1+c2;
					F[j+k]=c1-c2;
				}
			}
		}
#undef F
	}
	friend std::istream&operator>>(std::istream&x,poly&y){
		int len;x>>len;y.resize(len+1);
		return x;
	}
	friend poly operator*(poly F,poly G){
		int tmp=siz(F)+siz(G)-1;
		int len=1<<(__lg(tmp-1)+1);
		F.resize(len);G.resize(len);
		F.dft(1);G.dft(1);
		for(int i=0;i<siz(F);i++)F[i]*=G[i];
		F.dft(-1);
		mint ziv=mint(siz(F)).inv();
		for(int i=0;i<siz(F);i++)F[i]*=ziv;
		F.resize(tmp);
		return F;
	}
	poly&operator*=(const poly&f){return(*this)=(*this)*f;}
};
constexpr int N=1e6+7;
mint p,fac[N],inv[N];
mint EXk(int n){
	poly F(n+1),G(n+1);
	for(int i=0;i<=n;i++){
		F[i]=(i&1?P-1:1)*inv[i];
		G[i]=mint(i)(n)*inv[i];
	}
	poly H=F*G;
	mint ans=0;
	for(int i=1;i<=n;i++)
		ans+=H[i]*fac[i]*(1-p)(i-1)/p(i);
	return ans;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr);
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=fac[i-1]*i;
	inv[N-1]=fac[N-1].inv();
	for(int i=N-2;i;i--)inv[i]=inv[i+1]*(i+1);
	int T;cin>>T;while(T--){
		int n;
		cin>>n>>p;
		mint t1=EXk(2*n),t2=EXk(n);
		cout<<t1-t2*t2<<'\n';
	}
	return 0;
}