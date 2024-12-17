#include<bits/stdc++.h>
#define int long long 
using namespace std;
int q,n,m;
struct node{
	int op,a;
}qwq[10005];
bool cmp(node x,node y){ return x.a<y.a; }
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
signed main(){
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	q=read();
	while(q--){
		n=read(); m=read();
		for(int i=1;i<=m;i++) qwq[i].a=read();
		for(int i=1;i<=m;i++) qwq[i].op=read();
		sort(qwq+1,qwq+m+1,cmp);
		int ans=1e18;
		for(int i=1;i<=m;i++){
			if(qwq[i].op){
				ans=min(ans,qwq[i].a-qwq[1].a+qwq[m].a-qwq[1].a);
				ans=min(ans,qwq[m].a-qwq[i].a+qwq[m].a-qwq[1].a);
			}
		}
		if(ans==1e18) printf("NIE\n");
		else{
			int cnt=0;
			for(int i=1;i<=m;i++){
				if(qwq[i].a-qwq[1].a+qwq[m].a-qwq[1].a==ans) cnt++;
				if(qwq[m].a-qwq[i].a+qwq[m].a-qwq[1].a==ans) cnt++;
			}
			printf("%lld %lld\n",ans,cnt);
		}
	}
	return 0;
}
