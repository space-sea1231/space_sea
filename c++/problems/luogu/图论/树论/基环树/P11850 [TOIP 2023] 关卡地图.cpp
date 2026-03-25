#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

typedef long long ll;

const int N=2e5+10;
const int INF=0x3f3f3f3f3f3f3f3f;
int n, m;
ll cnt, ans=-INF, num;
ll val[N], dp[N], fa[N];
ll dfn[N], dis[N], father[N];
ll loop_sum[N], loop_val[N];
int head[N], to[N<<1], nxt[N<<1];
bool loop[N];
vector<int> loop_node;

inline void Add(int u, int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

inline int Find(int x){
	if (x==fa[x]){
		return x;
	}
	return fa[x]=Find(fa[x]);
}

inline void Dfs(int u, int fa){
	dp[u]=val[u];
	ans=max(ans, dp[u]);
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa||loop[v]){
			continue;
		}
		Dfs(v, u);
		ans=max(ans, dp[u]+dp[v]);
		dp[u]=max(dp[u], dp[v]+val[u]);
		dis[u]=max(dis[u], dp[v]);
	}
	dp[u]=max(0LL, dp[u]);
}

void Loop(int u, int fa){
    dfn[u]=++num;
    father[u]=fa;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa) continue;
        if (dfn[v]){
            if (dfn[v]>dfn[u]){
                while (v!=u){
                    loop[v]=1;
                    loop_node.push_back(v);
                    v=father[v];
                }
                loop[v]=1;
                loop_node.push_back(v);
            }
        }else{
            Loop(v, u);
        }
    }
}
    
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		fa[i]=i;
	}
	for (int i=1; i<=m; i++){
		int u, v;
		cin >> u >> v;
		if (Find(u)==Find(v)){
			continue;
		}
		Add(u, v);
		Add(v, u);
		fa[Find(u)]==Find(v);
	}
	for (int i=1; i<=n; i++){
		cin >> val[i];
	}
	if (1){
		Dfs(1, 0);
		printf("%lld\n", ans);
	}else{
		Loop(1, 0);
		for (auto u:loop_node){
			Dfs(u, 0);
		}
		ll u=loop_node[0], fa=0, top=0, tot=0, siz=loop_node.size();
		do{
	        for (int i=head[u]; i; i=nxt[i]){
	            int v=to[i], w=val[v];
	            if (loop[v]&&v!=fa){
	                loop_val[++top]=dis[v];
	                loop_sum[top]=loop_sum[top-1]+w;
//	                printf("Debug1: val[%d]=%d sum[%d]=%d v=%d\n", top, loop_val[top], top, loop_sum[top], v);
	                tot+=w;
	                fa=u, u=v;
	                break;
	            }
	        }
	    }while(u!=loop_node[0]);
	    ll maxn1=0, maxn2=0;
	    for (int i=1; i<=top; i++){
	    	ans=max(ans, loop_val[i]+loop_sum[i]+maxn1);
	    	ans=max(ans, loop_val[i]-loop_sum[i-1]+tot+maxn2);
			maxn1=max(maxn1, loop_val[i]-loop_sum[i-1]);
			maxn2=max(maxn2, loop_val[i]+loop_sum[i]);
		}
		printf("%lld\n", ans);
	}
	
	return 0;
}
