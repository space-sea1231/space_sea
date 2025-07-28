#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&-x;
#define fr first
#define sc second
using namespace std;

const int mod=998442353,inf=0x3f3f3f3f3f3f3f3f,lim=2800000;

inline int ksm(int base,int t){
	int res=1;
	while(t>0){
		if(t&1)res=res*base%mod;
		base=base*base%mod,t>>=1;
	}return res;
}

int fac[lim+5],inv[lim+5];

inline int C(int x,int y){return fac[x]*inv[y]%mod*inv[x-y]%mod;}

int T;

int n,m,p[25][25],tag[25],flag;

int dis[25][25],cnt[25][25],in[25][25][25];

pair<int,int> dp[1<<20];

vector <int> vec;

inline int solve(int st,int ed){
	int res=cnt[st][ed];
	for(int i=1;i<=n;i++){
		if(i==st||i==ed)continue;
		if(in[st][ed][i]){
			res=(res+mod-cnt[st][i]*cnt[i][ed]%mod)%mod;
		}
	}return res;
}

inline int read(){
	register int x=0,t=0;
	static char ch=getchar();
	while(!isdigit(ch)) t|=(ch=='-'),ch=getchar();
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return t?-x:x;
}

signed main(){
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	
	fac[0]=1;
	for(int i=1;i<=lim;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[lim]=ksm(fac[lim],mod-2);
	for(int i=lim-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
	
	T=read();while(T--){
	
	m=read(),n=read(),flag=0;
	for(int i=0;i<(1<<n);i++){
		dp[i]={inf,0};
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			p[i][j]=read();
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			dis[i][j]=0,cnt[i][j]=1;
			for(int k=1;k<=m;k++){
				dis[i][j]+=llabs(p[i][k]-p[j][k]);
				(cnt[i][j]*=C(dis[i][j],llabs(p[i][k]-p[j][k])))%=mod;
//				cout<<dis[i][j]<<' '<<i<<' '<<j<<' '<<k<<' '<<cnt[i][j]<<" kdsb\n";
			}
			for(int k=1;k<=n;k++){
				if(i==k||j==k)continue;
				in[i][j][k]=1;
				for(int h=1;h<=m;h++){
					in[i][j][k]&=(min(p[i][h],p[j][h])<=p[k][h]&&max(p[i][h],p[j][h])>=p[k][h]);
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		tag[i]=read(),flag|=tag[i];
		if(tag[i])dp[1<<i-1]={0,1};
	}
	if(!flag){cout<<"NIE\n";continue;}
	
	for(int i=1;i<(1<<n);i++){
		vec.clear();
		for(int j=0;j<n;j++){
			if(i>>j&1)vec.push_back(j+1);
		}
		if(vec.size()<=1)continue;
		for(int j:vec){
			for(int k:vec){
				if(k==j||!tag[k])continue;
				if(dp[i^(1<<j-1)].fr+dis[k][j]<dp[i].fr){
					dp[i]={dp[i^(1<<j-1)].fr+dis[k][j],0};
				}
//				cout<<(i^j)<<' '<<j<<' '<<cnt[k][j]<<" kdsb\n";
				if(dp[i^(1<<j-1)].fr+dis[k][j]==dp[i].fr){
					(dp[i].sc+=solve(k,j)*dp[i^(1<<j-1)].sc%mod)%=mod;
				}
			}
		}
	}
	cout<<dp[(1<<n)-1].fr<<' '<<dp[(1<<n)-1].sc<<'\n';
	
	}return 0;
}
/*
1
1 3
-41719
100
41719
0 1 0
*/
