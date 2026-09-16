#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int sum=0,fh=1;
	char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-')fh=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		sum*=10;
		sum+=c-'0';
		c=getchar();
	}
	return sum*fh;
}
#define maxn 100009
int n;
int tot=0,siz[3200009],to[3200009][2];
int newnode(){
	++tot;
	siz[tot]=to[tot][0]=to[tot][1]=0;
	return tot;
}
void ins(int now,int x,int lim=30){
	siz[now]++;
	if(lim<0)return ;
	int opt=x&1;x>>=1;
	if(!to[now][opt])to[now][opt]=newnode();
	ins(to[now][opt],x,lim-1);
	return ;
}
int cnt[35];
void dfs(int u,int dep=0){
	if(siz[u]<=1)return ;
	cnt[dep]^=(1ll*siz[to[u][0]]*siz[to[u][1]])&1;
	if(to[u][0])dfs(to[u][0],dep+1);
	if(to[u][1])dfs(to[u][1],dep+1);
	return ;
}	
void sol(){
	n=read();
	tot=0;
	int rot=newnode();
	long long ans=0;
	for(int i=0;i<35;i++)cnt[i]=0;
	for(int i=1;i<=n;i++){
		int x=read()-1;
		ans^=x;
		ins(rot,x);
	}
	dfs(rot);
	for(int i=0;i<35;i++)if(cnt[i]){
		ans^=(1ll<<(i+1))-1;
	}
	if(ans)puts("YES");
	else puts("NO");
	return ;
}
int main(){
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	int t=read();
	while(t--){
		sol();
	}
	return 0;
}