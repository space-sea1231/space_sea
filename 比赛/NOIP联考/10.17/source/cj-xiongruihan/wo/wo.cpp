#include <bits/stdc++.h>
#define int long long
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
const int N=2e6+1;
int a[N];
int b[N];
int c[N];
int d[N];
int e[N];
int cnt=0,cnt1=0;
int qwq(int e[],int x)
{
	int sum=0;
	for(int i=1;i<=x/2;i++)
	{
		sum+=abs(e[i]-e[x-i+1]);
	}
	return sum;
}
int qwq1(int a,int b,int c)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%c;
		a=a*a%c;
		b>>=1;
	}
	return ans;
}
const int mod=998244353;
int maxn=-1,maxcnt=0;
void dfs(int x,int sum)
{
	if(x>cnt1)
	{
		int cnt2=0;
		for(int i=1;i<=cnt;i++)
		{
			if(c[i])
			{
				e[++cnt2]=c[i];
				
			}
//			cout<<c[i]<<" ";
		}
//		cout<<cnt1<<endl;
		int sum1=sum+qwq(e,cnt2);
		if(sum1>maxn)
		{
			maxn=sum1;
			maxcnt=qwq1(2,cnt2/2,mod);
		}
		else if(sum1==maxn)
		{
			maxcnt+=qwq1(2,cnt2/2,mod);
			maxcnt%=mod;
		}
		return;
	}
	for(int i=1;i<=cnt;i++)
	{
		if(c[i])
		{
			int sum2=c[i];
			c[i]=0;
			dfs(x+1,sum+abs(d[x]-sum2));
			c[i]=sum2;
		}
	}
}
signed main()
{
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	int t=read();
	while(t--)
	{
		memset(b,0,sizeof(b));
		int n=read();
		for(int i=1;i<=n*2;i++)
		{
			a[i]=read();
			b[a[i]]++;
		}
		cnt=0;
		for(int i=1;i<=n*2;i++)
		{
			if(b[i]==0)
			{
				c[++cnt]=i;
			}
		}
		cnt1=0;
		for(int i=1;i<=n*2;i+=2)
		{
			if(a[i]==0&&a[i+1]!=0)
			{
				d[++cnt1]=a[i+1];
			}
			if(a[i]!=0&&a[i+1]==0)
			{
				d[++cnt1]=a[i];
			}
		}
//		cout<<cnt<<endl;
		dfs(1,0);
		cout<<maxcnt<<endl;
	}
    return 0;
}

