#include<bits/stdc++.h>
#define N 2000005
#define mod 998244353
#define int long long
using namespace std;
int T;
int n;
int p[N];
int ans;
bool vis[N];
int cntl,cntr;
int numl[N],numr[N];
int zy; 
int jie[N];
int kong[N];
void tian(){
	ans=1;
	int cnt=0;
	int yu=0;
	for(int i=1;i<=n*2;++i){
		if(p[i]==0){
			yu++;
		}
	}
	yu--;
	for(int i=1;i<=n*2;i+=2){
		if(p[i]==0 && p[i+1]==0){
			cnt++;
		}
		else if((p[i]==0&&p[i+1]!=0) || (p[i]!=0&&p[i+1]==0)){
			ans*=(yu+1)/2;
			yu-=1;
			ans%=mod;
		}
	} 
	ans=(ans*kong[cnt])%mod;
	ans%=mod;
} 
void init(){
	cntl=0; cntr=0;
	memset(numl,0,sizeof numl);
	memset(numr,0,sizeof numr);
	ans=1;
	zy=0;
}
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0); 
	cin>>T;
	kong[0]=1;
	for(int i=1;i<=N-5;++i){
		kong[i]=kong[i-1]*(i*i*2);
		kong[i]%=mod;
	}
//	cout<<kong[1]<<'\n';
	while(T--){
		init();
		cin>>n;
		for(int i=1;i<=n*2;++i){
			cin>>p[i];
		}
		tian();
		cout<<ans%mod<<'\n';
	}
	return 0;
}

