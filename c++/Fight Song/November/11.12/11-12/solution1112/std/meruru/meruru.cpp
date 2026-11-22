#include<bits/stdc++.h>
using namespace std;
#define pr pair<int,int>
#define fi first
#define sc second
#define hsh(x,y) (((x)-1)*m+(y))
#define lb(x) ((x)&(-(x)))

const int N = 801;
const int P = N*N;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};
const int lg2[] = {0,0,1,1,2,2,2,2,3,3,3,3,3,3,3};
map<char,int> tox;
int n, m, k, u[N][N], typ[20], mxlen[20], f[P], sz[P];
bool isc[20];
string s;
int cntcfr;
struct Pts{
	int fr[4];
	int to;
	bool usd;
	void psb(int x){
		for(int j = 0; j <= 3; j++) if(fr[j] == 0){fr[j] = x;return;}
	}
	int size(){
		for(int j = 0; j <= 3; j++) if(fr[j] == 0) return j;
		return 4;
	}
	void init(){
		fr[0] = fr[1] = fr[2] = fr[3] = to = usd = 0;
	}
}cfr[P*6];
vector<int> chp[P];

bool vis[P], del[P];
stack<int> sk;
vector<int> mp[P];
vector<pr> amp;
vector<int> clp[P];

inline int find(int x){return (f[x]==x?x:f[x]=find(f[x]));}

void tab(Pts &x){
	if(x.usd) return;
	int t0 = find(x.fr[0]);
	for(int j = 1; j < x.size(); j++){
		if(find(x.fr[j]) != t0){
			return;
		}
	}
	x.usd = 1;
	mp[t0].push_back(x.to);
}

void mrg(int u,int v){
	u = find(u);
	v = find(v);
	if(u==v)return;
	if(sz[v] > sz[u]) swap(u,v);
	f[v] = u;
	sz[u] += sz[v];
	for(auto vx : mp[v])
		mp[u].push_back(vx);
	vector<int>().swap(mp[v]);
	for(auto g : clp[v]){
		for(auto p : chp[g])
			tab(cfr[p]);
		clp[u].push_back(g);
	}
	vector<int>().swap(clp[v]);
}

void dfs(int x){
	if(del[x]) return;
	if(vis[x]){
		int T = find(x);
		while(sk.top() != T){
			int u = sk.top();
			sk.pop();
			mrg(u,T);
		}
		sk.pop();
		sk.push(find(T));
		return;
	}
	vis[x] = 1;
	clp[x].push_back(x);
	sk.push(x);
	while(mp[find(x)].size() > 0){
		int X = find(x);
		int u = mp[X][mp[X].size()-1];
		mp[X].pop_back();
		amp.push_back({X,find(u)});
		dfs(find(u));
		while(sk.top() != find(x)) sk.pop();
	}
	del[x] = 1;
}

int ans, cnt, deg[P], chd[P];

signed main(){
	freopen("meruru.in","r",stdin);
	freopen("meruru.out","w",stdout);
	tox['S'] = 0;
	tox['N'] = 1;
	tox['E'] = 2;
	tox['W'] = 3;
	cin >> k >> n >> m;
	cin >> s;
	s = s+s;
	for(int i = 0; i < 16; i++){
		int nowlen = 0;
		for(int j = 1; j <= k+k; j++){
			if((i>>tox[s[j-1]])&1){
				++nowlen;
			} else {
				mxlen[i] = max(mxlen[i],nowlen);
				nowlen = 0;
			}
		}
		mxlen[i] = max(mxlen[i],nowlen);
		if(mxlen[i] > k) mxlen[i] = 1e9;
	}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			f[hsh(i,j)] = hsh(i,j);
			sz[hsh(i,j)] = 1;
			cin >> u[i][j];
			if(u[i][j] == 0) continue;
			for(int k = 0; k < 16; k++){
				isc[k] = 0;
				for(int j = 0; j < k; j++)
					if(isc[j] && ((j&k) == j)) isc[k] = 1;

				for(int _ = 0; _ <= 3; _++)
					if((k>>_)&1)
						if(i+dx[_]<=0||i+dx[_]>n||j+dy[_]<=0||j+dy[_]>m) isc[k] = 1;
				if(isc[k]) continue;
				if(u[i][j] <= mxlen[k]){
					isc[k] = 1;
					Pts rft;
					rft.init();
					int _ = k;
					while(_){
						int c = lg2[lb(_)];
						rft.psb(hsh(i+dx[c],j+dy[c]));
						_ -= lb(_);
					}
					if(rft.size() == 1){
						mp[rft.fr[0]].push_back(hsh(i,j));
						continue;
					}
					rft.to = hsh(i,j);
					rft.usd = 0;
					cfr[++cntcfr] = rft;
					for(auto v : rft.fr){
						chp[v].push_back(cntcfr);
					}
				}
			}
		}
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			if(u[i][j]==0) continue;
			dfs(hsh(i,j));
		}
	for(auto ed : amp){
		int u = ed.fi, v = ed.sc;
		u = find(u), v = find(v);
		if(u==v) continue;
		deg[u]++;
	}
	ans = n*m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			if(u[i][j] == 0) continue;
			int X = find(hsh(i,j));
			if(chd[X]) continue;
			chd[X] = 1;
			if(deg[X]) continue;
			if(sz[X] > ans) continue;
			if(sz[X] < ans){
				ans = sz[X];
				cnt = 0;
			}
			cnt += sz[X];
		}
	cout << ans << "\n" << cnt << "\n";
}