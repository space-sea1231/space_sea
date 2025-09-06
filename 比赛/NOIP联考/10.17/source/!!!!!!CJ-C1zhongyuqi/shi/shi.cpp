#include<bits/stdc++.h>
#define ll long long
#define p pair<ll,ll>
#define se second 
#define fi first
#define pb push_back
using namespace std;
map<ll,ll>mp; 
ll n,T;
const ll N=1e6+9,M=26;
struct node{ll a[M],sum;vector<ll>stp;}st,ans;
inline ll cg(node x){ll ans=0;for(int i=1;i<=n;i++)ans=ans*2+x.a[i];return ans;}
inline ll feiyu(int x,int y){return ((!x)&(!y));}
inline void BFS()
{
	ans.sum=0;
	mp.clear();
	queue<node>que;
	que.push(st);
	while(!que.empty())
	{
		node now=que.front();que.pop();
		if(ans.sum<now.sum) ans=now;
		if(mp[cg(now)])continue;mp[cg(now)]=1;
		for(int i=2;i<n;i++)
		{
			node newnow=now;newnow.stp.pb(i);
			newnow.a[i-1]=feiyu(now.a[i-1],now.a[i]);
			newnow.a[i+1]=feiyu(now.a[i+1],now.a[i]);
			newnow.sum+=(newnow.a[i-1]-now.a[i-1])+(newnow.a[i+1]-now.a[i+1]);
			que.push(newnow);
		}
	}
	cout<<ans.sum<<' '<<ans.stp.size()<<endl;
	for(auto i:ans.stp)
		cout<<i<<' ';
	cout<<endl;
}
int main()
{
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	cin>>T;
	while(T--)
	{
		st.sum=0;while(!st.stp.empty())st.stp.pop_back();
		string tmp;cin>>tmp;n=tmp.size();
		for(int i=1;i<=n;i++)st.a[i]=tmp[i-1]-'0',st.sum+=st.a[i];
		if(n<=20)BFS();
		else
		{
			ll ans=count(tmp.begin(),tmp.end(),'1');
			cout<<ans<<endl;
		}
	}
	return 0;
 } 
