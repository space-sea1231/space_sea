#include<bits/stdc++.h>
#define int long long
using namespace std;
const int T=100001,F=-100001,U=0;//三值逻辑
int c,t,n,m,a,b,fa[100005];
char ch[100005];
bool book[300005];
int find(int x) {
	int re;
	if(x==T||x==F)re=x;
	else if(book[n-x]||x==U)re=U;
	else if(book[x+n])re=T;
	else if(x<0) {
		if(x==-fa[-x])re=x;
		else {
			book[x+n]=1;
			re=find(-fa[-x]);//这里注意细节
			book[x+n]=0;//清空
		}
	} else {
		if(x==fa[x])re=x;
		else {
			book[x+n]=1;
			re=fa[x]=find(fa[x]);
			book[x+n]=0;//清空
		}
	}
	return re;
}
signed main() {
	cin>>c>>t;
	while(t--) {
		cin>>n>>m;
		for(int i=1; i<=n; i++)fa[i]=i;
		for(int i=1; i<=m; i++) {
			cin>>ch[i];
			if(ch[i]=='T') {
				cin>>a;
				fa[a]=T;
			} else if(ch[i]=='F') {
				cin>>a;
				fa[a]=F;
			} else if(ch[i]=='U') {
				cin>>a;
				fa[a]=U;
			} else {
				cin>>a>>b;
				if(ch[i]=='+')fa[a]=fa[b];
				else fa[a]=-fa[b];
			}
		}
		int ans=0;
		for(int i=1; i<=n; i++) {
			if(find(i)==U)ans++;
		}
		cout<<ans<<endl;
	}
	return 0;
}