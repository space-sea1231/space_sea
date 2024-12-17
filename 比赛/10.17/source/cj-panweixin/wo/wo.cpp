#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&-x;
#define ls k<<1
#define rs k<<1|1
using namespace std;

const int mod=998244353;

inline int ksm(int base,int t){
	int res=1;
	while(t>0){
		if(t&1)res=res*base%mod;
		base=base*base%mod,t>>=1;
	}return res;
}

int fac[2000005];

int T;

int n,a[2000005],vis[2000005],ans;

int vec[2000005],cnt;

vector <int> pos;

inline int read(){
	register int x=0,t=0;
	static char ch=getchar();
	while(!isdigit(ch)) t|=(ch=='-'),ch=getchar();
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return t?-x:x;
}

signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	
	T=read();while(T--){

	n=read(),fac[0]=1,ans=1;
	cnt=0,pos.clear();
	for(int i=1;i<=2*n;i++){
		a[i]=read(),vis[i]=1;
		fac[i]=fac[i-1]*i%mod;
	}
	for(int i=1;i<=2*n;i+=2){
		if(a[i]>0&&a[i+1]>0){
			vis[a[i]]=vis[a[i+1]]=0;
		}else if(a[i]>0||a[i+1]>0){
			pos.push_back(a[i]+a[i+1]);
			vis[a[i]+a[i+1]]=2;
		}
	}
	for(int i=1;i<=2*n;i++){
		if(vis[i]>0)vec[++cnt]=i;
	}
	
	int t1=cnt/2,t2=cnt/2;
	for(int i=1;i<=cnt;i++){
		if(vis[vec[i]]==2){
			i<=cnt/2?t1--:t2--;
		}
		vis[vec[i]]=(i<=cnt/2);
	}
	for(int i:pos){
		if(vis[i]){
			(ans*=t2)%=mod,t2--;
		}else{
			(ans*=t1)%=mod,t1--;
		}
	}
	
	ans=ans*fac[t1]%mod*fac[t2]%mod*ksm(2,t1)%mod;
	
	cout<<ans<<'\n';
	
	}return 0;
}

/*
1
10
13 0 18 15 20 0 0 4 2 0 3 5 10 9 14 19 6 7 17 12

4
*/
