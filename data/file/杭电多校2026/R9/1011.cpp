///*****Sellaris*****///

#include <bits/stdc++.h>
#define ll long long
#define x first
#define y second
#define int ll

using namespace std;
const int maxn=3e5+10;
const int mo=998244353;

inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f;
}

inline ll mod(ll x){return x>=mo? x%mo :x;}

inline ll qpow(int x,int k = mo - 2){
    ll res=1,base=x;
    while(k){
        if(k&1) res=mod(1ll*res*base);
        k>>=1; base=mod(1ll*base*base);
    }return res;
}
    
vector<int> g[maxn];
int dfn[maxn],top[maxn],son[maxn],dep[maxn],siz[maxn],fa[maxn],dfcc;
void dfs1(int u,int ufa,int d){
    dep[u]=d;fa[u]=ufa;siz[u]=1;
    for(int to:g[u]){
        if(to==ufa) continue;
        dfs1(to,u,d+1);
        siz[u]+=siz[to];
        if(siz[to]>siz[son[u]]) son[u]=to;
    }
}
void dfs2(int u,int ufa,int utop){
    dfn[u]=++dfcc;
    top[u]=utop;
    if(son[u]==0) return;
    dfs2(son[u],u,utop);
    for(int to:g[u]){
        if(to==ufa || to==son[u]) continue;
        dfs2(to,u,to);
    }
}
int lca(int u,int v){
    if(dep[u]<dep[v]) {swap(u,v);}
    while(top[u]!=top[v]){
        if(dep[top[u]] > dep[top[v]]) u=fa[top[u]];
        else v=fa[top[v]];
    }if(dep[u]>dep[v]) return v;
    else return u;
}

int n,m;

inline void solve(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
        g[u].push_back(v);
        g[v].push_back(u);
	}
	dfs1(1,0,0);
	dfs2(1,0,1);
    vector<int> leaf;
	for(int i=1;i<=n;i++){
        if(son[i] == 0) leaf.push_back(i);
    }
    int ff=0;
    int wwy,wwxy;
    for(int a:leaf){
    	int f=0;
    	int wy,wxy;
    	for(int b:leaf){
    		if(a==b) continue;
    		int p=lca(a,b);
    		int x=dep[a]-dep[p];
    		int y=dep[b]-dep[p];
			if(!f || (__int128)y*wxy < (__int128)wy*(x+y)){   
                f=1;
                wy = y;
                wxy = x+y;
            }
		}
		
		if(!ff || (__int128)wy*wwxy > (__int128)wwy*wxy){   
            ff=1;
            wwy = wy;
            wwxy = wxy;
        }
	}
	cout<<mod(wwy*qpow(wwxy))<<"\n";
	for(int i=1;i<=n;i++){
		dfn[i]=top[i]=son[i]=dep[i]=siz[i]=fa[i]=0;
		g[i].clear();
	}
	dfcc=0;
}

signed main(){
#ifdef Local
	system("chcp 65001 > nul");
#endif
    //std::ios::sync_with_stdio(0);std::cin.tie(NULL);std::cout.tie(NULL);
    //freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t=read();
	for(int i=1;i<=t;i++){
		// cerr<<"-------------------------\n";
        // cerr<<"test case "<<i<<"\n";
		 solve();
        // cerr<<"-------------------------\n";
	}
    return 0;
}
