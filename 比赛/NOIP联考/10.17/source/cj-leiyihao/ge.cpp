#include<bits/stdc++.h>
using namespace std;
int a[25][25],n,m,p[25];
bool vis[25];
long long fac[1000005],len,ans,b[25];
long long ksm(long long x,int y)
{
	long long ans=1;
	while(y)
	{
		if(y&1) ans=(ans*x)%998244353;
		x=(x*x)%998244353;
		y/=2;
	}
	return ans;
}
void dfs(int deep,int x,int w,long long s)
{
	if(w>len) return ;
	if(deep==n)
	{
		if(len==w) ans=(ans+s)%998244353;
		else len=w,ans=s;
		return ;
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			vis[i]=1;
			long long q=s;
			long long sum=abs(a[x][1]-a[i][1]);
			w+=sum;
			for(int j=2;j<=m;j++)
			{
				long long f=abs(a[x][j]-a[i][j]);
				if(sum+1>f+1)
				q=(q*fac[sum+1]%998244353*ksm(fac[f-1],998244351)%998244353);
				else
				q=(q*fac[f+1]%998244353*ksm(fac[sum-1],998244351)%998244353);
				w+=abs(a[x][j]-a[i][j]);
				sum+=f;
			}
			dfs(deep+1,i,w,q);
			vis[i]=0;
			for(int j=1;j<=m;j++)
			{
				w-=abs(a[x][j]-a[i][j]);
			}
		}
	}
}
int main()
{
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	fac[0]=1;
	for(int i=1;i<=1000000;i++)
	{
		fac[i]=(1ll*i*fac[i-1])%998244353;
	}
	int t;
	scanf("%d",&t);
	while(t--) 
	{
		len=LONG_LONG_MAX;
		ans=0;
		scanf("%d%d",&m,&n);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				scanf("%d",&a[i][j]);
			}
		}
		for(int i=1;i<=n;i++) scanf("%d",&p[i]);
		for(int i=1;i<=n;i++)
		{
			if(p[i])
			{
				vis[i]=1;
				dfs(1,i,0,1);
				vis[i]=0;
			}
		}
		if(ans)
		printf("%lld %lld\n",len,ans);
		else
		printf("NIE\n");
	}
	return 0;
}
