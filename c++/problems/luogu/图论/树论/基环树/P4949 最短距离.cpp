#include <iostream>

using namespace std;

const int N=1e5+10;
int n, m;
int cnt;
int cu, cv, cw, ch;
int fa[N];
int head[N], to[N<<1], nxt[N<<1], weight[N<<1];

struct Node{
	int u, v, w;
}e[N];

inline void Add(int u, int v, int w){
	to[++cnt]=v;
	weight[cnt]=w;
	nxt[cnt]=head[u];
	head[u]=cnt;
}

inline int Find(int x){
	if (x==fa[x]){
		return x;
	}
	return fa[x]=Find(fa[x]);
}

struct Binary_Indexed_lca{
    int sum[N];
    inline int Lowbit(int x){
        return x&-x;
    }
    inline void Add(int x, int y){
        for (int i=x; i<=n; i+=Lowbit(i)){
            sum[i]+=y;
		}
    }
    inline int Query(int l, int r){
        int ans=0;
        for (int i=r; i>=1; i-=Lowbit(i)){
            ans+=sum[i];
		}
		for (int i=l; i>=1; i-=Lowbit(i)){
            ans-=sum[i];
		}
        return ans;
    }
}Bin;

struct Chain_Tree{
    int num, root;
    int father[N], son[N], top[N];
    int size[N], dep[N];
    int bin[N], wei[N];
    inline void Dfs1(int u, int fa){
        father[u]=fa;
        dep[u]=dep[fa]+1;
        size[u]=1;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa){
                continue;
            }
            Dfs1(v, u);
            size[u]+=size[v];
            if (size[v]>size[son[u]]){
                son[u]=v;
            }
        }
    }
    inline void Dfs2(int u, int fa, int w){
    	top[u]=u;
    	bin[u]=++num;
    	wei[num]=w;
    	for (int i=head[u]; i; i=nxt[i]){
	        int v=to[i], w=weight[i];
			if (v==son[u]){
	            top[v]=top[u];
	            Dfs2(v, u, w);
	        }
		}
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i], w=weight[i];
            if (v==fa||v==son[u]){
                continue;
            }
            Dfs2(v, u, w);
        }
    }
    inline int QueryLine(int x, int y){
        int fx=top[x], fy=top[y], ans=0;
        while (fx!=fy){
            if (dep[fx]<dep[fy]){
                swap(fx, fy);
                swap(x, y);
            }
            ans+=Bin.Query(bin[fx]-1, bin[x]);
            x=father[top[x]], fx=top[x];
        }
        if (dep[x]>dep[y]){
            swap(x, y);
        }
        ans+=Bin.Query(bin[x], bin[y]);
        return ans;
    }
	inline int Query(int x, int y){
		int ans1=QueryLine(x, y);
		int ans2=QueryLine(x, cu)+cw+QueryLine(cv, y);
		int ans3=QueryLine(x, cv)+cw+QueryLine(cu, y);
		return min(ans1, min(ans2, ans3)); 
	}
    inline void Change(int x, int y){
    	if (father[e[x].v]==e[x].u){
    		Bin.Add(bin[e[x].v], y-e[x].w);
		}else{
    		Bin.Add(bin[e[x].u], y-e[x].w);
		}
		e[x].w=y;
	}
    inline void Init(){
        root=1;
        Dfs1(root, 0);
        Dfs2(root, 0, 0);
        for (int i=2; i<=n; i++){
        	Bin.Add(i, wei[i]);
		}
    }
}Tree;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		fa[i]=i;
	}
	for (int i=1; i<=n; i++){
		int u, v, w;
		cin >> u >> v >> w;
		if (Find(u)==Find(v)){
			cu=u;
			cv=v;
			cw=w;
			ch=i;
			continue;
		}
		Add(u, v, w);
		Add(v, u, w);
		e[i].u=u;
		e[i].v=v;
		e[i].w=w;
		fa[Find(u)]=Find(v);
	}
	Tree.Init();
	for (int i=1; i<=m; i++){
		int opt, x, y;
		cin >> opt >> x >> y;
		switch (opt){
			case 1:
				if (x==ch){
					cw=y;
				}else{
					Tree.Change(x, y);
				}
				break;
			case 2:
				printf("%d\n", Tree.Query(x, y));
				break;
		}
	}
	return 0;
}