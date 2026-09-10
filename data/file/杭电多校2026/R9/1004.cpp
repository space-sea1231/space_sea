#include<bits/stdc++.h>
using namespace std;

#define int long long 

const int M=1e5+5;

int t,len,n,q,x;
int a[M],pre[M],p[M];

void insert(int x)
{
	for(int i=60;i>=0;i--)
	{
		if(x&(1ll<<i))
		{
			if(p[i])
				x=x^p[i];
			else 
			{
				p[i]=x;
				break;
			}
		}
	}
} 

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	
	cin>>t;
	while(t--)
	{
		for(int i=0;i<=60;i++)
			p[i]=0;
		cin>>n>>len>>q;
		for(int i=1;i<=n;i++)
			cin>>a[i],pre[i]=pre[i-1]^a[i];
		for(int i=len;i<=n;i++)
		{
			insert(pre[i]^pre[i-len]);
		}
		while(q--)
		{
			cin>>x;
			for(int i=60;i>=0;i--)
				x=max(x,x^p[i]);
			cout<<x<<"\n";
		}
	}
}