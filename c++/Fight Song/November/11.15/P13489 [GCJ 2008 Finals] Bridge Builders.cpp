#include<bits/stdc++.h>
#define int long long

const int N=35; 

using namespace std;

const int f[4][2]={{-1,0},{0,-1},{1,0},{0,1}};

int T,n,m,tim,tt,tot0,tot,cnt,fa[N*N],t[N*N],lnk[N*N],vis[N*N],dis[N*N][N*N],ans;

char c[N][N];

struct node{
	int x,dis;
	bool operator<(const node &b)const{return dis>b.dis;}
};

struct edge0{
	int to,w,nxt;
}e0[N*N*N*N*2];

struct edge{
	int u,v,w;
	bool operator<(const edge &b)const{return w<b.w;}
}e[N*N*N*N];

priority_queue<node>q;

inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')ret=ret*10+(ch&15),ch=getchar();
	return ret*f;
}

inline char read1(){
	char ch=getchar();
	while(ch!='T'&&ch!='#'&&ch!='.')ch=getchar();
	return ch;
}

bool chk(int i,int j){
	if(i<1||j<1||i>n||j>m)return 0;
	return c[i][j]!='.';
}

int getid(int i,int j){
	return (i-1)*m+j;
}

void add_e(int x,int y,int z){
	e0[++tot0]=(edge0){y,1,lnk[x]};
	lnk[x]=tot0;
}

void Dij(int st){
	for(int i=1;i<=n*m;i++)vis[i]=0;
	dis[st][st]=0;
	while(!q.empty())q.pop();
	q.push({st,0});
	while(!q.empty()){
		int u=q.top().x;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=lnk[u];i;i=e0[i].nxt){
			int v=e0[i].to;
			if(dis[st][u]+e0[i].w<dis[st][v]){
				dis[st][v]=dis[st][u]+e0[i].w;
				q.push({v,dis[st][v]});
			}
		}
	}
}

void _init(){
	tt=tot0=tot=cnt=0;
	for(int i=1;i<=n*m;i++){
		fa[i]=i;
		lnk[i]=0;
		for(int j=1;j<=n*m;j++)dis[i][j]=1e9;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!chk(i,j))continue;
			if(c[i][j]=='T')t[++tt]=getid(i,j);
			for(int k=0;k^4;k++){
				int x=i+f[k][0],y=j+f[k][1];
				if(!chk(x,y))continue;
				int u=getid(i,j),v=getid(x,y);
				add_e(u,v,1);
			}
		}
	}
	for(int i=1;i<=n*m;i++)Dij(i);
}

int _calc(int u,int v){
	int d=dis[u][v];
	if(d&1)return (d+1)*((d/2)+1)/2;
	return d*d/4+d/2;
}

int getfa(int x){
	return (fa[x]==x)?x:(fa[x]=getfa(fa[x]));
}

void _solve(){
	tim++;
	n=read(),m=read(),ans=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)c[i][j]=read1();
	_init();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(c[i][j]=='#'){
				int id=getid(i,j),w=1e9;
				for(int k=1;k<=tt;k++)w=min(w,dis[id][t[k]]);
				ans+=w;
			}
		}
	}
	for(int i=1;i<=tt;i++)for(int j=i+1;j<=tt;j++)e[++tot]=(edge){t[i],t[j],_calc(t[i],t[j])};
	sort(e+1,e+tot+1);
	for(int i=1;i<=tot;i++){
		int fx=getfa(e[i].u),fy=getfa(e[i].v);
		if(fx^fy){
			fa[fx]=fy;
			ans+=e[i].w;
			cnt++;
			if(cnt==tt-1)break;
		}
	}
	printf("Case #%lld: %lld\n",tim,ans);
}

signed main(){
	T=read();
	while(T--)_solve();
	return 0;
}
/*
True friends are few.Keep those who truly knows you.
挚友贵真知，得三五足矣。
*/