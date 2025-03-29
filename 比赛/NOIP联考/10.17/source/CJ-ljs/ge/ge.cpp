#include<bits/stdc++.h>
#define int int64_t
using namespace std;
const int mod=998442353,inf=0x3f3f3f3f3f3f3f3f;
int T,n=5e6,m,f[65536][16],g[65536][16],a[16][25],d[16][16],mul[16][16],fac[5000005],inv[5000005],ansa,ansb;
int chk(int x){
	return x>=mod?x-mod:x;
}
int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1)
			ret=ret*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ret;
}
int qwq(int x,int y){
	return fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int dist(int i,int j){
	int ret=0;
	for(int k=1;k<=n;k++)
		ret+=abs(a[i][k]-a[j][k]);
	return ret;
}
int calc(int i,int j){
	int ret=1,dis=0;
	for(int k=1,x;k<=n;k++)
		x=abs(a[i][k]-a[j][k]),dis+=x,ret=ret*qwq(dis,x)%mod;
	return ret;
}
int32_t main(){
	freopen("ge.in","r",stdin),freopen("ge.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cin>>T,fac[0]=inv[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%mod;
	inv[n]=qpow(fac[n],mod-2);
	for(int i=n-1;i>=1;i--)
		inv[i]=inv[i+1]*(i+1)%mod;
	while(T--){
		cin>>n>>m,ansa=inf,ansb=0;
		for(int i=0;i<m;i++)
			for(int j=1;j<=n;j++)
				cin>>a[i][j];
		for(int i=0;i<m;i++)
			for(int j=0;j<m;j++)
				d[i][j]=dist(i,j),mul[i][j]=calc(i,j);
		n=(1<<m)-1;
		for(int i=0;i<=n;i++)
			for(int j=0;j<m;j++)
				f[i][j]=inf,g[i][j]=0;
		for(int i=0,x;i<m;i++){
			cin>>x;
			if(x)
				f[1<<i][i]=0,g[1<<i][i]=1;
		}
		for(int s=0;s<=n;s++)
			if(__builtin_popcount(s)>1)
				for(int i=0;i<m;i++)
					if((s>>i)&1){
						int t=s^(1<<i);
						for(int j=0;j<m;j++)
							if((t>>j)&1){
								int tmp=f[t][j]+d[i][j];
								if(tmp<f[s][i])
									f[s][i]=tmp,g[s][i]=g[t][j]*mul[i][j]%mod;
								else if(tmp==f[s][i])
									g[s][i]=(g[s][i]+g[t][j]*mul[i][j])%mod;
							}
					}
		for(int i=0;i<m;i++){
			if(f[n][i]<ansa)
				ansa=f[n][i],ansb=g[n][i];
			else if(f[n][i]==ansa)
				ansb=chk(ansb+g[n][i]);
		}
		if(!ansb)
			cout<<"NIE\n";
		else
			cout<<ansa<<' '<<ansb<<'\n';
	}
	return 0;
}