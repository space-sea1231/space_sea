#include<bits/stdc++.h>
#define ll long long
#define ljc 998244353
using namespace std;
#define gc getchar
inline ll read(){
    register ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
    while (isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=gc();}
    return (f==1)?x:-x;
}
struct edge{
    int to,nxt;
}g[2000001];
int tot,head[2000001],len,n,A,B,m,col[2000001];
int pre[1000001],id,a1[1000001],b1[1000001];
int vis[2000001],pos[11],all,d,dfn[2000001],low[2000001];
char s[1000001],a2[1000001],b2[1000001];
stack<int> S;
inline void made(int from,int to){
    g[++tot].to=to;g[tot].nxt=head[from];head[from]=tot;
}
void tarjan(int u){
    low[u]=dfn[u]=++id;S.push(u);vis[u]=1;
    for (int i=head[u];i;i=g[i].nxt){
        int v=g[i].to;
        if (!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }else if (vis[v]){
            low[u]=min(low[u],dfn[v]);
        }
    }
    if (low[u]==dfn[u]){
        len++;
        while (S.top()!=u){
            int x=S.top();S.pop();
            col[x]=len;vis[x]=0;
        }
        col[u]=len;S.pop();vis[u]=0;
    }
}
inline int trans(int a,char B){
	char A=s[a];
	if (A=='c'){
		if (B=='A') return 0;
		else return 1;
	}else if (A=='b'){
		if (B=='A') return 0;
		else return 1;
	}else if (A=='a'){
		if (B=='B') return 0;
		else return 1;
	}else{
		if (B=='C') return 1;
		return 0;
	}
}
inline char upr(char y){
	return (char)(y-32);
}
signed main(){
	n=read(),d=read();
	for (int i=1;i<=n;i++){
		char ch=gc();
		while (!isalpha(ch)) ch=getchar();
		s[i]=ch;
		if (s[i]=='x') pre[i]=++all;
	}
	m=read();
	for (int i=1;i<=m;i++){
		a1[i]=read();char ch=gc();
		while (!isalpha(ch)) ch=getchar();
		a2[i]=ch;b1[i]=read();ch=gc();
		while (!isalpha(ch)) ch=getchar();
		b2[i]=ch;
	}
	int MX=(1<<d)-1;
	for (int zt=0;zt<=MX;zt++){
		//0 AC    1 BC
		tot=id=len=0;
		while (!S.empty()) S.pop();
		for (int i=1;i<=2*n;i++){
			head[i]=low[i]=col[i]=dfn[i]=vis[i]=0;
		}
		for (int i=1;i<=m;i++){
			if (s[a1[i]]=='x'&&s[b1[i]]=='x'){
				int zta=(zt&(1<<(pre[a1[i]]-1)));
				int ztb=(zt&(1<<(pre[b1[i]]-1)));
				if (!zta&&a2[i]=='B') continue;
				if (zta&&a2[i]=='A') continue;
				int I=trans(a1[i],a2[i]),J=trans(b1[i],b2[i]);
				if (!ztb&&b2[i]=='B'){
					made(a1[i]+n*I,a1[i]+n*(I^1));continue;
				}
				if (ztb&&b2[i]=='A'){
					made(a1[i]+n*I,a1[i]+n*(I^1));continue;
				}
				made(a1[i]+n*I,b1[i]+n*J);made(b1[i]+n*(J^1),a1[i]+n*(I^1));
			}else if (s[a1[i]]!='x'&&s[b1[i]]=='x'){
				int ztb=(zt&(1<<(pre[b1[i]]-1)));
				int I=trans(a1[i],a2[i]),J=trans(b1[i],b2[i]);
				if (upr(s[a1[i]])==a2[i]) continue;
				if (!ztb&&b2[i]=='B'){
					made(a1[i]+n*I,a1[i]+n*(I^1));continue;
				}
				if (ztb&&b2[i]=='A'){
					made(a1[i]+n*I,a1[i]+n*(I^1));continue;
				}
				made(a1[i]+n*I,b1[i]+n*J);made(b1[i]+n*(J^1),a1[i]+n*(I^1));
			}else if (s[a1[i]]=='x'&&s[b1[i]]!='x'){
				int zta=(zt&(1<<(pre[a1[i]]-1)));
				int I=trans(a1[i],a2[i]),J=trans(b1[i],b2[i]);
				if (!zta&&a2[i]=='B') continue;
				if (zta&&a2[i]=='A') continue;
				if (upr(s[b1[i]])==b2[i]){
					made(a1[i]+n*I,a1[i]+n*(I^1));continue;
				}
				made(a1[i]+n*I,b1[i]+n*J);made(b1[i]+n*(J^1),a1[i]+n*(I^1));
			}else{
				int I=trans(a1[i],a2[i]),J=trans(b1[i],b2[i]);
				if (upr(s[a1[i]])==a2[i]) continue;
				if (upr(s[b1[i]])==b2[i]){
					made(a1[i]+n*I,a1[i]+n*(I^1));continue;
				}
				made(a1[i]+n*I,b1[i]+n*J);made(b1[i]+n*(J^1),a1[i]+n*(I^1));
			}
		}
		for (int i=1;i<=2*n;i++){
			if (!dfn[i]) tarjan(i);
		}
		bool flag=1;
		for (int i=1;i<=n;i++){
			if (col[i]==col[i+n]){
				flag=0;break;
			}
		}
		if (!flag) continue;
		for (int i=1;i<=n;i++){
			int op=(col[i]>col[i+n]);
			if (s[i]=='x'){
				int ZT=(zt&(1<<(pre[i]-1)));
				if (!ZT){
					if (op)	printf("C");
					else printf("A");
				}else{
					if (op)	printf("C");
					else printf("B");
				}
			}else{
				if (s[i]=='a'){
					if (op)	printf("C");
					else printf("B");
				}else if (s[i]=='b'){
					if (op)	printf("C");
					else printf("A");
				}else{
					if (op)	printf("B");
					else printf("A");
				}
			}
		}
		return 0;
	}
	printf("-1");
    return 0;
}

/*
*/