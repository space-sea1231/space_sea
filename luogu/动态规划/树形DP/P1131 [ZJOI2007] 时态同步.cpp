#include <bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	char c=getchar();
	int sum=0, flag=1;
	while (c<'0'||c>'9'){
		if (c=='-'){
			flag=-1;
		}
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		sum=(sum<<1)+(sum<<3)+(c^48);
		c=getchar();
	}
	return sum*flag;
}
const int N=5e5+1;
int dp[N], head[N], cnt, sum;
struct node{
	int to, next, w;
}e[N*2];
void add(int u, int v, int w){
	e[++cnt].to=v;
	e[cnt].w=w;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void serch(int now, int fa){
	for (int i=head[now]; i; i=e[i].next){
		int v=e[i].to, w=e[i].w;
		if (v==fa){
			continue;
		}
		serch(v, now);
		dp[now]=max(dp[now], dp[v]+w);
	}
	for (int i=head[now]; i; i=e[i].next){
		int v=e[i].to, w=e[i].w;
		if (v==fa){
			continue;
		}
		sum+=dp[now]-dp[v]-w;
	}
}
signed main(){
	int n=read(), m=read();
	for (int i=1; i<n; i++){
		int u=read(), v=read(), w=read();
		add(u, v, w);
		add(v, u, w);
	}
	serch(m, 0);
	cout << sum;
	
	return 0;
}