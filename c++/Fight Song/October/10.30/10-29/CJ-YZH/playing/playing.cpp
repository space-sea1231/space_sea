#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;
constexpr int N=1005;
bool m1;
int n,a[N];
int f[N][(1<<13)+1];
pair<pii,bool>g[N][(1<<13)+1];
bool m2;
inline void upd(int a,int b,int c,int d,bool cur)
{
	if(f[c][d])
		f[a][b]=1,g[a][b]=mp(mp(c,d),cur);
}
inline int hbit(int x)
{
	x|=x>>1,x|=x>>2,x|=x>>4,x|=x>>8,x|=x>>16;return x-(x>>1);
}
void dfs(int x,int y)
{
	if(!x)return;
	dfs(g[x][y].fi.fi,g[x][y].fi.se);
	cout<<(g[x][y].se?'r':'l');
}
int main()
{
    freopen("playing.in", "r", stdin);
    freopen("playing.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;cin>>T;
	while(T--)
	{
		cin>>n;
        if (n > 40) return 0;
		int sum=0;
		for(int i=1;i<=n;i++)
			cin>>a[i],sum+=a[i];
		if(__builtin_popcount(sum)!=1){cout<<"no\n";continue;}
		f[0][0]=1;
		sum=0;
		for(int i=1;i<=n;i++)
		{
			for(int S=0;S<=sum+a[i];S++)
				f[i][S]=0,g[i][S]=mp(mp(-1,-1),0);
			for(int S=0;S<=sum;S++)
			{
				int l=S,r=sum-S;
				int low_l=l&-l,low_r=r&-r;
//				cout<<low_l<<' '<<low_r<<'\n';
				if(low_l>=a[i] || !l)
					upd(i,l+a[i],i-1,l,0);
				int d=(hbit(l)<=hbit(r+a[i])?1:0)*hbit(r+a[i]);
				if(low_r>=a[i] || !r)
					upd(i,l+d,i-1,l,1);
			}
			sum+=a[i];
		}
		if(f[n][sum])
			dfs(n,sum),cout<<'\n';
		else
			cout<<"no\n";
	}
	return 0;
}
