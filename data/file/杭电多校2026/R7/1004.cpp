#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll sz[300005],f[300005],F[300005],dep[300005],mi,n,tn,rt;
vector<ll> vct[300005],g[300005];
const ll x=998244353,y=1e9+7,mod1=1e9+9,mod2=998244853;
ll hsh[300005],hsh2[300005];

ll find(ll a) {
	if (F[a]!=a)F[a]=find(F[a]);
	return F[a];
}

void init(ll root,ll fa) {
	f[root]=fa;
	for (ll i:vct[root]) {
		if (i!=fa) {
			init(i,root);
		}
	}
}

void dfs(ll root,ll fa) {
	ll mx=0;
	dep[root]=dep[fa]+1;
	f[root]=fa;
	sz[root]=1;
	for (ll i:vct[root]) {
		if (i!=fa) {
			dfs(i,root);
			sz[root]+=sz[i];
			mx=max(mx,sz[i]);
		}
	}
	mx=max(tn-sz[root],mx);
	if (mx<mi||(mx==mi&&dep[root]>dep[rt])) {
		rt=root;
		mi=mx;
	}
}

void dfs2(ll root,ll fa) {
	hsh[root]=x%mod1,hsh2[root]=x%mod2;
	for (ll i:vct[root]) {
		if (i!=fa) {
			dfs2(i,root);
			(hsh[root]*=hsh[i])%=mod1;
			(hsh2[root]*=hsh2[i])%=mod2;
		}
	}
	(hsh[root]+=y)%=mod1;
	(hsh2[root]+=y)%=mod2;
}

int main() {
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	ll t;
	cin >> t;
	while (t--) {
		cin >> n;
		for (ll i=1; i<=n; i++)F[i]=i,f[i]=0;
		ll Q=0;
		for(ll i=1; i<=n-1; i++) {
			ll u,v;
			cin >> u >> v;
			vct[u].push_back(v);
			vct[v].push_back(u);
		}
		for (ll i=1; i<=n; i++) {
			if (vct[i].size()==1) {
				Q=i;
				break;
			}
		}
		init(Q,0);
		for (ll i=1; i<=n; i++) {
			if (f[i]==0)continue;
			if (vct[f[i]].size()==2) {
				F[find(f[i])]=find(f[f[i]]);
			}
		}
		tn=n;
		for (ll i=1; i<=n; i++) {
			if (!f[i])continue;
			if (find(i)==i) {
				ll u=i,v=find(f[i]);
				g[u].push_back(v);
				g[v].push_back(u);
			} else {
				tn--;
			}
		}
		for (ll i=1; i<=n; i++)vct[i]=g[i];
		mi=1e9,rt=0;
		dfs(Q,0);
		if (tn%2==0&&mi*2==tn) {
			dfs2(rt,f[rt]);
			dfs2(f[rt],rt);
			if (make_pair(hsh[rt],hsh2[rt])==make_pair(hsh[f[rt]],hsh2[f[rt]])) {
				cout<<"2\n1 2\n";
			} else {
				cout<<"1\n1\n";
			}
		} else {
			dfs2(rt,0);
			map<pair<ll,ll>,ll> mp;
			for (ll i:vct[rt]) {
				mp[make_pair(hsh[i],hsh2[i])]++;
			}
			ll gh=0;
			for (auto i:mp) {
				gh=__gcd(gh,i.second);
			}
			ll c=0;
			for (ll i=1; i<=gh; i++) {
				if (gh%i==0) {
					c++;
				}
			}
			cout<<c<<"\n";
			for (ll i=1; i<=gh; i++) {
				if (gh%i==0) {
					cout<<i<<" ";
				}
			}
			cout<<"\n";
		}

		for (ll i=1; i<=n; i++)vct[i].clear(),g[i].clear();
	}
	return 0;
}