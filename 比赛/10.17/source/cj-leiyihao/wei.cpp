#include<bits/stdc++.h>
using namespace std;
int a[400005];
int main()
{
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]); 
		long long sum=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				swap(a[i],a[j]);
				long long ans=0,len=1;
				for(int k=2;k<=n;k++)
				{
					if(a[k]<a[k-1])
					{
						ans+=len*(len-1)/2;
						len=1;
					}
					else
					{
						len++;
					}
				}
				ans+=len*(len-1)/2;
				swap(a[i],a[j]);
				sum=max(sum,ans+n);
			}
		}
		printf("%lld\n",sum);
	}
	return 0;
}
