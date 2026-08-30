#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=505,inf=1e18;
int n,m,s,ln[N],c[N];
int dp[2][N][N],K[N];
int le[N],ri[N],vl[N],tot;
int Q[N],L,R;
void solve(){
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++)cin>>ln[i]>>c[i];
	for(int i=1;i<=n;i++)cin>>K[i];
	for(int i=0;i<=m;i++)for(int j=1;j<=n;j++)dp[0][i][j]=inf;
	int P=0;
	dp[0][0][s]=0; 
	for(int t=1;t<=m;t++){
		P^=1;
		for(int i=0;i<=m;i++)for(int j=1;j<=n;j++)dp[P][i][j]=inf;
		for(int i=0;i<t;i++){
			tot=0;
			for(int j=1,l,r;j<=n;j++)if(dp[P^1][i][j]<inf){
				l=j-ln[t],r=j+ln[t];
				if(l<1)dp[P][i+1][1]=min(dp[P][i+1][1],dp[P^1][i][j]+c[t]);
				if(r>n)dp[P][i+1][n]=min(dp[P][i+1][n],dp[P^1][i][j]+c[t]);
				dp[P][i][max(l,1ll)]=min(dp[P][i][max(l,1ll)],dp[P^1][i][j]+c[t]);
				dp[P][i][min(r,n)]=min(dp[P][i][min(r,n)],dp[P^1][i][j]+c[t]);
				l=max(0ll,l)+1,r=min(r,n+1)-1;
				le[++tot]=l,ri[tot]=r,vl[tot]=dp[P^1][i][j];
			}
			L=1,R=0;
			for(int pt=1,j=1;j<=n;j++){
				while(pt<=tot&&le[pt]==j){
					while(L<=R&&vl[Q[R]]>=vl[pt])R--;
					Q[++R]=pt,pt++;
				}
				while(L<=R&&ri[Q[L]]<j)L++;
				if(L<=R)dp[P][i][j]=min(dp[P][i][j],vl[Q[L]]);
			}
		}
	}
	for(int i=1;i<=n;i++){
		int ans=-1;
		for(int j=0;j<=m;j++)if(dp[P][j][i]<=K[i])ans=j;
		cout<<ans<<' ';
	}
	cout<<'\n';
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc;
    cin>>tc;
    while(tc--)solve();
    return 0;
}