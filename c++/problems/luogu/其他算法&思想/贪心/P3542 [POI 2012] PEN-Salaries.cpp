#include <iostream>
#include <stdio.h>
#include <stack>

using namespace std;

const int N=1e6+10;

int n;
int cnt, root;
int fa[N];
int maxn[N], cnt_num[N], idx[N];
int father[N], val[N];
int head[N], to[N], nxt[N];

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

inline void IterativeDfs(int u){
	stack<int> s;
	s.push(u);
	while (!s.empty()){
		int u=s.top();
		s.pop();
		if (maxn[u]==0){
			maxn[u]=Find(maxn[father[u]]-1);
			cnt_num[maxn[u]]++;
			idx[maxn[u]]=u;
		}
		for (int i=head[u]; i; i=nxt[i]){
			int v=to[i];
			s.push(v);
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n;
    for (int i=1; i<=n; i++){
        fa[i]=i;
    }
    
	for (int i=1; i<=n; i++){
        int x;
		cin >> x >> val[i];
        maxn[i]=val[i];
		if (x==i){
			root=i;
			maxn[i]=val[i]=n;
		}else{
            father[i]=x;
			Add(father[i], i);
		}
		fa[val[i]]=val[i]-1;
	}
	IterativeDfs(root);
    
	int tmp=0;
	for (int i=1; i<=n; i++){
		if (fa[i]==i){
			tmp++;
		}
		if (tmp==1&&cnt_num[i]){
			val[idx[i]]=i;
		}
		tmp-=cnt_num[i];
	}
    
    for (int i=1; i<=n; i++){
        printf("%d\n", val[i]);
    }
	return 0;
}