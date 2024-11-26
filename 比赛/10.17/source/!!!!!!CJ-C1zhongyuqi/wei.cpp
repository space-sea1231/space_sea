#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=309;
int n,a[N],s[N],T;
int main()
{
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	cin>>T;
	while(T--)
	{
		cin>>n;ll ans=0;
		for(int i=1;i<=n;i++)cin>>a[i],s[i]=a[i]-a[i-1];
		for(int i=1,j=1;i<=n;i++)
		{
			if(s[i]<0)j=i;
			ans+=i-j+1;
		}
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
			{
				ll nans=0;
				swap(a[i],a[j]);
				for(int k=1;k<=n;k++)
					s[k]=a[k]-a[k-1];
				for(int k=1,tmp=1;k<=n;k++)
				{
					if(s[k]<0) tmp=k;
					nans+=k-tmp+1;
				}
				ans=max(nans,ans);
				swap(a[i],a[j]);
			}
		cout<<ans<<endl;
		
	}
}
