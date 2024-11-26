#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
    return;
}
const int N=4e5+1;
int a[N];
bool dp[5001][5001];
int n;
int qwq()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==j) dp[i][i]=1;
			else dp[i][j]=0;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int l=1;l+i<=n;l++)
		{
			int r=l+i;
			if(a[r-1]<a[r])
			{
				dp[l][r]|=dp[l][r-1];
			}
			if(a[l+1]>a[l])
			{
				dp[l][r]|=dp[l][r-1];
			}
			if(a[l+1]>a[l]&&a[r-1]<a[r])
			{
				dp[l][r]|=dp[l+1][r-1];
			}
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			if(dp[i][j]) cnt++;
		}
	}
	return cnt;
}
signed main()
{
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	int t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		int maxn=qwq();
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(a[j]<a[i])
				{
					swap(a[j],a[i]);
					maxn=max(maxn,qwq());
					swap(a[i],a[j]);
				}
			}
		}
		write(maxn);
		putchar('\n');
	}
	
    return 0;
}

