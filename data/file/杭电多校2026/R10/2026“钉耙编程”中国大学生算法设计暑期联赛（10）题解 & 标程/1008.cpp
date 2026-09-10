#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int ll
#define F(i,a,b) for(int (i)=(a);(i)<=(b);++(i))
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
signed main()
{
	int T=read();
	while(T--)
	{
		int n=read();
		int pref=0,mx=0,best=0,ans=LLONG_MIN;
		F(i,1,n)
		{
			int x=read();
			pref+=x;
			ans=max(ans,pref);
			ans=max(ans,pref+best);
			best=max(best,mx-pref);
			mx=max(mx,pref);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
