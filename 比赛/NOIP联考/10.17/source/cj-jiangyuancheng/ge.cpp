#include <bits/stdc++.h>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0') x=x*10+(ch^48),ch=getchar();
	return x*f;
}
const int mod=998442353;
int p[17][17],n,m,s[17];
long long dist[17][17];
long long f[1<<17][17];
long long step[1<<17][17],S[17][17];
long long fac[3500000],inv_fac[3500000];
long long power(long long a,long long b,long long p){
	a%=p;
	long long ans=1;
	while(b){
		if(b&1) ans=ans*a%p;
		b>>=1;
		a=a*a%p; 
	}
	return ans;
}
int Abs(int x){
	return x>0?x:-x;
}
int main(){
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	fac[0]=1;
	for(int i=1;i<=3400000;i++) fac[i]=fac[i-1]*i%mod;
	inv_fac[3400000]=power(fac[3400000],mod-2,mod);
	for(int i=3399999;i>=0;i--) inv_fac[i]=inv_fac[i+1]*(i+1)%mod;
	int t=read();
	while(t--){
		n=read(),m=read();
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				p[i][j]=read();
			}
		}
		for(int i=1;i<=m;i++) s[i]=read();
		for(int i=1;i<=m;i++){
			for(int j=1;j<=m;j++){
				dist[i][j]=0;
				S[i][j]=1;
				for(int k=1;k<=n;k++){
					S[i][j]=S[i][j]*inv_fac[Abs(p[i][k]-p[j][k])]%mod;
					dist[i][j]=dist[i][j]+Abs(p[i][k]-p[j][k]);
				}
				S[i][j]=S[i][j]*fac[dist[i][j]]%mod;
			}
		}
		for(int i=0;i<(1<<m);i++){
			for(int j=1;j<=m;j++) f[i][j]=0x3f3f3f3f3f3f3f3f,step[i][j]=0;
		}
		for(int i=1;i<=m;i++){
			if(s[i]){
				f[1<<(i-1)][i]=0;
				step[1<<(i-1)][i]=1;
			}
		}
		for(int i=1;i<(1<<m);i++){
			int kkk=i,num1=0;
			while(kkk){
				num1+=(kkk&1);
				kkk>>=1;
			}
			if(num1==1) continue;
			for(int j=1;j<=m;j++){
				for(int k=1;k<=m;k++){
					if(((i>>(j-1))&1)&&((i>>(k-1))&1)&&k!=j){
						if(f[i^(1<<(j-1))][k]+dist[k][j]<f[i][j]){
							f[i][j]=f[i^(1<<(j-1))][k]+dist[k][j];
							step[i][j]=step[i^(1<<(j-1))][k]*S[k][j]%mod;
						}else if(f[i^(1<<(j-1))][k]+dist[k][j]==f[i][j]){
							step[i][j]=(step[i][j]+step[i^(1<<(j-1))][k]*S[k][j]%mod)%mod;
						}
					}
				}
			}
		}
		long long ans=0x3f3f3f3f3f3f3f3f,sum=0;
		for(int i=1;i<=m;i++){
			if(f[(1<<m)-1][i]<ans){
				ans=f[(1<<m)-1][i];
				sum=step[(1<<m)-1][i];
			}else if(f[(1<<m)-1][i]==ans){
				sum=(sum+step[(1<<m)-1][i])%mod;
			}
		}
		printf("%lld %lld\n",ans,sum);
	}
}
