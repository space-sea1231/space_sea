#include<bits/stdc++.h>
using namespace std;
bool vis[1000005];
int ans[3000005];
int main()
{
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		long long n=s.size(),ans1=0;
		for(int i=0;i<n;i++)
		{
			if(s[i]=='1') ans1++;
			vis[i+1]=s[i]-'0';
		}
		int cnt=0,sum=ans1;
		for(int i=n-1;i>=2;i--)
		{
			if(!vis[i+1]&&!vis[i])
			{
				if(!vis[i-1])
				{
					ans[++cnt]=i;
					sum+=2;
					vis[i-1]=vis[i+1]=1;
				}
				else
				{
					int y=i;
					while(y>1&&vis[y-1])
					{
						ans[++cnt]=y;
						swap(vis[y-1],vis[y+1]);
						y--;
					}
					if(y>1)
					{
						ans[++cnt]=y;
						sum+=2;
						vis[y+1]=vis[y-1]=1;
					}
				}
			}
		}
		for(int i=n-1;i>=3;i--)
		{
			if(!vis[i+1]&&vis[i-1])
			{
				ans[++cnt]=i-1;
				sum-=vis[i-2];
				vis[i]=vis[i-2]=0;
				sum--;
				int y=i;
				while(y>1&&vis[y-1])
				{
					ans[++cnt]=y;
					swap(vis[y-1],vis[y+1]);
					y--;
				}
				if(y>1)
				{
					ans[++cnt]=y;
					sum+=2;
					vis[y+1]=vis[y-1]=1;
				}
			}
			else if(!vis[i+1]&&!vis[i-1]&&!vis[i-2])
			{
				ans[++cnt]=i-1;
				vis[i]=0;
				vis[i-2]=1;
				sum--;
				int y=i;
				while(y>1&&vis[y-1])
				{
					ans[++cnt]=y;
					swap(vis[y-1],vis[y+1]);
					y--;
				}
				if(y>1)
				{
					ans[++cnt]=y;
					sum+=2;
					vis[y+1]=vis[y-1]=1;
				}
			}
		}
		cout<<sum<<' '<<cnt<<'\n';
		for(int i=1;i<=cnt;i++)
		{
			cout<<ans[i]<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
