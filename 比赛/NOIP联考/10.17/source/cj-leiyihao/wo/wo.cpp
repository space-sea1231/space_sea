#include<bits/stdc++.h>
using namespace std;
int a[2000005],b[2000005];
int main()
{
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		int p=0,cnt=0;
		scanf("%d",&n);
		p=n*2;
		for(int i=1;i<=2*n;i++)
		{
			scanf("%d",&a[i]);
			if(!(i&1))
			{
				if(a[i]!=0&&a[i-1]!=0)
				{
					p-=2;
					b[a[i]]++;
					b[a[i-1]]++;
				}
			}
		}
		for(int i=1;i<=2*n;i++)
		{
			b[i]+=b[i-1];
			if(i-b[i]==p/2)
			{
				cnt=i;
				break;
			}
		}
		long long ans=1,ans1=p/2,ans2=p/2;
		for(int i=1;i<=2*n;i++)
		{
			if(!(i&1))
			{
				if(a[i]&&!a[i-1])
				{
					if(a[i]<=cnt) ans2--;
					else ans1--;
				}
				else if(a[i-1]&&!a[i])
				{
					if(a[i-1]<=cnt) ans2--;
					else ans1--;
				}
			}
		}
		for(int i=1;i<=2*n;i++)
		{
			b[i]=0;
			if(!(i&1))
			{
				if(!a[i-1]&&!a[i])
				{
					ans=ans*ans1%998244353*ans2%998244353*2ll%998244353;
					ans1--;
					ans2--;
				}
				else if(a[i-1]&&!a[i])
				{
					if(a[i-1]<=cnt)
					{
						ans=ans*ans1%998244353;
						ans1--;
					}
					else
					{
						ans=ans*ans2%998244353;
						ans2--;
					}
				}
				else if(a[i]&&!a[i-1])
				{
					if(a[i]<=cnt)
					{
						ans=ans*ans1%998244353;
						ans1--;
					}
					else
					{
						ans=ans*ans2%998244353;
						ans2--;
					}
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
