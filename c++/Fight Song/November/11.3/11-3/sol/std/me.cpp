#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 5005,mod = 998244353;
int n,m,a[N],f[N][N],g[N][N],h[N][N];
signed c[N][N];
signed main()
{
	freopen("me.in","r",stdin);
	freopen("me.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	c[0][0] = 1;
	for(int i = 1;i<N;i++)
	{
		c[i][0] = 1;
		for(int j = 1;j<N;j++)
			c[i][j] = (c[i-1][j-1]+c[i-1][j])%mod;
	}
	cin>>n>>m;
	int sum = 0;
	for(int i = 1;i<=n;i++)
		cin>>a[i],sum+=a[i];
	f[0][0] = 1;
	for(int i = 1;i<=sum/m;i++)
		for(int j = i*m;j<=sum;j++)
		{
			f[i][j] = mod-f[i-1][j-m];
			for(int k = 1;k<m;k++)
				f[i][j]+=mod-f[i][j-k];
			f[i][j]%=mod;
		}
	for(int i = 1;i<=n;i++)
	{
		for(int j = 0;j<=sum/m;j++)
			for(int k = 0;k<=a[i]-j*m;k++)
			{
				int x = a[i]-k;
				(g[i][j+k]+=f[j][x]*c[j+k][j])%=mod;
			}
	}
	h[0][0] = 1;
	for(int i = 1;i<=n;i++)
		for(int j = 0;j<=sum;j++)
			for(int k = 0;k<=min(a[i],j);k++)
				(h[i][j]+=h[i-1][j-k]*g[i][k]%mod*c[j][k])%=mod;
	int ans = 0;
	for(int i = 1;i<=sum;i++) (ans+=h[n][i])%=mod;
	cout<<ans;
	return 0;
}
