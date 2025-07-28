#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=20,K=2e6,MOD=998442353;
int T,m,n,a[N],x,dp[K][N],f[K][N];
signed main(){
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		memset(dp,0x3f,sizeof(dp));
		memset(f,0,sizeof(f));
		cin>>m>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++){
			cin>>x;
			if(x==1) dp[(1<<(i-1))][i-1]=0;
		}
		for(int i=0;i<=(1<<n)-1;i++){
			for(int j=0;j<=n-1;j++){
				if(i&(1<<j)){
					for(int k=0;k<=n-1;k++){
						if((i^(1<<j))&(1<<k)){
							if(dp[(i^(1<<j))][k]+abs(a[k+1]-a[j+1])<dp[i][j]){
								dp[i][j]=dp[(i^(1<<j))][k]+abs(a[k+1]-a[j+1]);
								f[i][j]=1;
							}
							else if(dp[(i^(1<<j))][k]+abs(a[k+1]-a[j+1])==dp[i][j]){
								f[i][j]=(f[i][j]+1)%MOD;
							}
						}
					}
				}
			}
		}
		cout<<dp[(1<<n)-1][n-1]<<" "<<f[(1<<n)-1][n-1]<<'\n';
	}
	return 0;
}

