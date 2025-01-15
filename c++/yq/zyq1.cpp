#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define lson(x) x<<1
#define rson(x) x<<1|1
using namespace std;
const ll N=5e5+9;
struct Decomposition{
    ll top[N],fa[N],hson[N],siz[N],dep[N];
    vector<ll>to[N];          
    inline void dfs1(int x,int fat){
        dep[x]=dep[fat]+1;
        siz[x]=1;fa[x]=fat;
        for(auto i:to[x])
            if(i!=fat){
                dfs1(i,x);
                siz[x]+=siz[i];
                if(siz[hson[x]]<siz[i])
                    hson[x]=i;
            }
    }
    inline void dfs2(int x,int tp){
        top[x]=tp;
        dfs2(hson[x],tp);
        for(auto i:to[x])
            if(i!=fa[x] && i!=hson[x])
                dfs2(i,i);
    }
    inline ll LCA(int x,int y){
        while(top[x]!=top[y]){
            if(dep[top[x]]>dep[top[y]])
                x=fa[top[x]];
            else y=fa[top[y]];
        }
        return ((dep[x]>dep[y])?fa[top[x]]:fa[top[y]]);
    }
}seg;
ll n,m,s;
int main(){
    cin>>n>>m>>s;
    for(int i=1,x,y;i<n;i++)
        cin>>x>>y,
        seg.to[x].pb(y),
        seg.to[y].pb(x);
    seg.dfs1(1,1);seg.dfs2(1,1);
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        cout<<seg.LCA(x,y)<<endl;
    }
    return 0;
}
//Heavy-Light-Decomposition
//在线吗？？？
