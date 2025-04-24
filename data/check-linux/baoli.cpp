#include<bits/stdc++.h>
using namespace std;
int fa[1000006];
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y){
	fa[find(x)]=find(y);
}
struct Edge{
	int v,w;
	Edge *next;
    static int cnt;
    void *operator new(size_t x);
};
Edge *p;
int Edge::cnt=0;
void *Edge::operator new(size_t x){
    return p+(++cnt);
}
struct Node{
	Edge *head;
    bool vis,ring;
    long long dep,rdep,belong;
}node[1000006];
int f[1000006][20];
vector<pair<int,vector<int>>> rings;
void add(int u,int v,int w){
	Edge *tmp=new Edge;
	tmp->v=v;
    tmp->w=w;
	tmp->next=node[u].head;
	node[u].head=tmp;
}
int mgop=-1;
void FindRing(int now,int fa){
    node[now].vis=1;
    for(Edge *i=node[now].head;i;i=i->next){
        // if(i->v!=fa){
            if(!node[i->v].vis){
                FindRing(i->v,now);
            }
            else{
                node[now].ring=1;
                node[i->v].ring=1;
                node[now].belong=mgop;
                node[i->v].belong=mgop;
                node[i->v].vis=0;
            }
            if(node[i->v].ring&&node[i->v].vis) node[now].ring=1,node[now].belong=mgop;
        // }
    }
}
void dfs(int now,int fa){
    f[now][0]=fa;
	for(Edge *i=node[now].head;i;i=i->next){
		if(i->v!=fa&&!node[i->v].ring){
            node[i->v].dep=node[now].dep+i->w;
            dfs(i->v,now);
		}
	}
}
void rfs(int now,int fa,pair<int,vector<int>> &v){
    v.second.push_back(now);
    node[now].vis=1;
    node[now].belong=mgop;
    for(Edge *i=node[now].head;i;i=i->next){
        if(node[i->v].ring&&!node[i->v].vis){
            node[i->v].rdep=node[now].rdep+i->w;
            rfs(i->v,now,v);
		}
        if(node[i->v].ring&&node[i->v].vis){
            v.first+=i->w;
        }
	}
}
int read(){
    int xx=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        xx=(xx<<1)+(xx<<3)+(ch^48);
        ch=getchar();
    }
    return xx;
}
pair<int,int> LCA(int x,int y){
    bool swapp=0;
    if(node[x].dep<node[y].dep){
        swap(x,y);
        swapp=1;
    }
    for(int i=19;i>=0;i--){
        if(node[x].dep-(1<<i)>node[y].dep){
            x=f[x][i];
        }
    }
    if(f[x][0]==y){
        return make_pair(x,x);
    }
    if(node[x].dep>node[y].dep)
    x=f[x][0];
    for(int i=19;i>=0;i--){
        if(f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    if(swapp) return make_pair(y,x);
    return make_pair(x,y);
}
bool flag;
int n,k;
vector<pair<int,int> > vec;
signed main(){
    p=(Edge*)calloc(3000005,sizeof(Edge));
    ios::sync_with_stdio(0);
    cin.tie(0);
    n=read();
    k=read();
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=n;i++){
		int u=i,v=read(),w=1;
        if(find(u)==find(v)){
            vec.push_back(make_pair(u,v));
        }
        add(v,u,w);
        merge(u,v);
	}
    for(int i=1;i<=n;i++){
        if(fa[i]==i){
            FindRing(i,0);
        }
    }
    for(int i=1;i<=n;i++){
        node[i].vis=0;
    }
    for(int i=1;i<=n;i++){
        if(fa[i]==i){
            mgop++;
            rings.push_back(make_pair(0,vector<int>()));
            rfs(i,i,rings.back());
        }
    }
    for(int i=1;i<=n;i++){
        node[i].vis=0;
        if(node[i].ring){
            node[i].dep=0;
            dfs(i,0);
        }
    }
    for(int j=1;j<20;j++){
        for(int i=1;i<=n;i++){
            f[i][j]=f[f[i][j-1]][j-1];
        }
    }
    // for(int i=1;i<=n;i++){
    //     printf("ring[%d]=%d\n",i,node[i].ring);
    //     for(int j=0;j<3;j++){
    //         printf("fa[%d][%d]=%d\n",i,j,f[i][j]);
    //     }
    // }
    for(int i=1;i<=k;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        if(x==y){
            printf("0 0\n");
            continue;
        }
        if(find(x)!=find(y)){
            printf("-1 -1\n");
            continue;
        }
        auto tp=LCA(x,y);
        int fx=tp.first,fy=tp.second;
        if(f[fx][0]!=0){
            printf("%lld %lld\n",node[x].dep-node[fx].dep+1,node[y].dep-node[fy].dep+1);
        }
        else{
            bool swapp=0;
            int bel=node[fx].belong;
            if(node[fx].rdep<node[fy].rdep){
                swap(fx,fy);
                swap(x,y);
                swapp=1;
            }
            int dx=node[x].dep-node[fx].dep;
            int dy=node[y].dep-node[fy].dep;
            // printf("Debug:%d %d %lld,%d %d %lld,%d\n",fx,dx,node[fx].rdep,fy,dy,node[fy].rdep,bel);
            int cx=node[fx].rdep-node[fy].rdep;
            int cy=rings[bel].first-node[fx].rdep+node[fy].rdep;
            // printf("cx:%d cy:%d\n",cx,cy);
            if(dx+cx<dy+cy){//case 2
                dx+=cx;
            }
            else if(dx+cx>dy+cy){
                dy+=cy;
            }
            else{//==, case 3
                if(dx<dy){
                    dy+=cy;
                }
                else if(dx>dy){
                    dx+=cx;
                }
                else{//==,case 4
                    if(!swapp){
                        dx+=cx;
                    }
                    else{
                        dy+=cy;
                    }
                }
            }
            if(swapp){
                swap(dx,dy);
            }
            printf("%d %d\n",dx,dy);
        }
    }
	return 0;
}
/*
*/