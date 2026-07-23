#include<bits/stdc++.h>
using namespace std;
const int N=100010,M=1000010,INF=0x3f3f3f3f;
int T,n,sz[N],son[N],tag[N];
array<int,2> ans[N],ch[N];
void dfs(int p,int a,int b,int B){
	if(ch[p][0]&&2*(sz[ch[p][1]]+a)<=B)son[p]=ch[p][0],b=max(b,sz[ch[p][1]]);
	else if(ch[p][1]&&2*(sz[ch[p][0]]+b)<=B)son[p]=ch[p][1],a=max(a,sz[ch[p][0]]);
	if(!son[p])return;
	int q=ch[p][son[p]==ch[p][0]];
	if(q)dfs(q,0,0,sz[q]);
	dfs(son[p],a,b,B);
}
void add(int p){
	if(p)ans[p][0]+=tag[p];
	if(ch[p][0])tag[ch[p][0]]+=tag[p],add(ch[p][0]);
	if(ch[p][1])tag[ch[p][1]]+=tag[p],add(ch[p][1]);
}
array<int,2> draw(int p,int y){
	array<int,2> c={0,0};
	for(int i=p,j=y;i;i=son[i]){
		ans[i][1]=j;
		if(!son[i])continue;
		int chk=(son[i]==ch[i][0]),q=ch[i][chk];
		if(q){
			array<int,2> w=draw(q,j+1);
			tag[q]+=chk?w[0]+1:-w[1]-1;
			c[chk]=max(c[chk],w[0]+w[1]+1);
		}
		j+=sz[q]+1;
	}
	// printf("p=%d y=%d c[0]=%d c[1]=%d\n", p, y, c[0], c[1]);
	return c;
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>ch[i][0]>>ch[i][1];
	for(int i=n;i;i--)
		sz[i]=sz[ch[i][0]]+sz[ch[i][1]]+1,
		son[i]=tag[i]=ans[i][0]=ans[i][1]=0;
	dfs(1,0,0,n),draw(1,0),add(1);
	// for (int i = 1; i <= n; i++) printf("son[%d]=%d\n", i, son[i]);
	for(int i=1;i<=n;i++)
		cout<<ans[i][0]<<' '<<ans[i][1]<<'\n';
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
