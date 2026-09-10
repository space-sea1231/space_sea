#include<bits/stdc++.h>
using namespace std;

#define int long long 

const int M=1e4+5;

int t,n;
int a[M];

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);

//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	
	cin>>t;
	while(t--)
	{
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++)
			ans+=a[i];
		cout<<ans+a[n]<<endl;
	}	
 } 