#include<bits/stdc++.h>
#define pb push_back
#define se second
#define fi first
#define ll long long
using namespace std;
const int N=2e5+9;
ll n,q,fa[N][26],jp[N][26][2],num[N][2],dep[N];
vector<pair<ll,pair<ll,ll> > >e[N];
inline void dfs(int x,int fat){
    fa[x][0]=fat;dep[x]=dep[fat]+1;
    for(int i=1;i<=25;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1],
        jp[x][i][0]=jp[x][i-1][0]+jp[fa[x][i-1]][i-1][0],
        jp[x][i][1]=jp[x][i-1][1]+jp[fa[x][i-1]][i-1][1];
    for(auto i:e[x])
        if(i.fi!=fat)
            jp[i.fi][0][0]=i.se.fi,
            jp[i.fi][0][1]=i.se.se,
            dfs(i.fi,x);
}
inline bool LCA(int x,int y){
    int xx=x,yy=y;
    if(dep[x]<dep[y]) swap(x,y);
    ll sum1=0,sum2=0;
    for(int i=25;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y])
            sum1+=jp[x][i][0],
            sum2+=jp[x][i][1],
            x=fa[x][i];
    if(x==y) return ((num[xx][0]>=sum1) && (num[xx][1]>=sum2));
    for(int i=22;i>=0;i--)
        if(fa[x][i]!=fa[y][i])
            sum1+=jp[x][i][0]+jp[y][i][0],
            sum2+=jp[x][i][1]+jp[y][i][1],
            x=fa[x][i],y=fa[y][i];
    sum1+=jp[x][0][0]+jp[y][0][0];
    sum2+=jp[x][0][1]+jp[y][0][1];
    return ((num[xx][0]>=sum1) && (num[xx][1]>=sum2));
}
int main(){
   // freopen("input.in","r",stdin);
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        if(x==0){
            num[i][0]=num[i][1]=INT_MAX;
            continue;
        }
        while(x%2==0)x/=2,num[i][0]++;
        while(x%5==0)x/=5,num[i][1]++;
    }
    for(int i=1;i<n;i++){
        int x,y;double z;
        cin>>x>>y>>z;
        if(z==0){
            e[x].pb({y,{INT_MIN,INT_MIN}});
            e[y].pb({x,{INT_MIN,INT_MIN}});
            continue;
        }
        ll tmp=0;
        while((double)((ll)z)!=z)tmp++,z*=10;
        ll tmp1,tmp2,zz=z;tmp1=tmp2=tmp;
        while(zz%2==0) tmp1--,zz/=2;
        while(zz%5==0) tmp2--,zz/=5;
        e[x].pb({y,{tmp1,tmp2}});
        e[y].pb({x,{tmp1,tmp2}});
    }
    dfs(1,1);
    while(q--){
        int x,y;
        cin>>x>>y;
        if(LCA(x,y)) cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
/*
5 3
1 2 3 4 5
1 2 0.1
2 3 0.20
3 4 0.5
2 5 0.99
1 5
1 4
4 3

*/