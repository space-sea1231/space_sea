#include<bits/stdc++.h>
#define int __int128
using namespace std;
int fa[200010],f[200010],a[200010],b[200010];
bool vis[200010];
int find(int x){
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
struct node{
    int x;
    bool friend operator<(node i,node j){
        return b[i.x]*a[j.x]>b[j.x]*a[i.x];
    }
};
priority_queue<node>q;
inline int read(){
    int x=0;
    char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x;
}
inline void print(int x){
    if(x>9)print(x/10);
    putchar(x%10+'0');
}

signed main(){
    int T=read();
    while(T--){
        int n=read();
        for(int i=1;i<=n;i++)a[i]=read();
        for(int i=1;i<=n;i++)b[i]=read();
        for(int i=1;i<=n;i++)f[i]=read();
        for(int i=1;i<=n;i++)fa[i]=i;
        for(int i=1;i<=n;i++){
            q.push({i});
        }
        int sum=0;
        while(q.size()){
            node u=q.top();
            q.pop();
            if(u.x==1)continue;
            if(vis[u.x])continue;
            vis[u.x]=1;
            int Fa=find(f[u.x]);
            sum+=a[u.x]*b[Fa];
            fa[u.x]=Fa;
            a[Fa]+=a[u.x],b[Fa]+=b[u.x];
            if(Fa!=1)q.push({Fa});
        }
        print(sum),puts("");
        while(q.size())q.pop();
        for(int i=1;i<=n;i++)vis[i]=0;
    }
    return 0;
}