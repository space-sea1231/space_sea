#include<bits/stdc++.h>
using namespace std;

const int M=1e5+5;

int t,n,m;
int c[M],dp[M];
vector<int> a[M],b[M];
map<int,int> mp;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	
	cin>>t;
	while(t--)
	{
		mp.clear();
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			a[i].resize(m+1);
		for(int i=1;i<=n;i++)
			b[i].resize(m+1);
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>a[i][j];
		int cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				cin>>b[i][j],mp[b[i][j]]=(i-1)*m+j;
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				c[++cnt]=mp[a[i][j]]; 
		
		int len=0;
		for(int i=1;i<=cnt;i++)
		{
			if(dp[len]<c[i])dp[++len]=c[i];
			else 
			{
				int id=lower_bound(dp+1,dp+len+1,c[i])-dp;
				dp[id]=c[i];
			}
		}
		cout<<cnt-len<<endl;
		
	}
}
/*
2
3 3
1 2 3
4 5 6 
7 8 9
2 4 3 
9 1 5
8 7 6
2 4
3 5 1 2
8 9 4 6
1 4 5 8
9 2 3 6
*/
