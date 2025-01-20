#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
int n, m, num;
int fa[N], dis[N], idx[N<<1];
struct Node{
    int l, r;
    bool flag;
}e[N];
int Find(int x){
    if (fa[x]==x){
        return x;
    }
    int root=Find(fa[x]);
    dis[x]^=dis[fa[x]];
    return fa[x]=root;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=m; i++){
        char c[5];
        cin >> e[i].l >> e[i].r >> c;
        if (c[0]=='o'){
            e[i].flag=1;
        }
        idx[++num]=e[i].l-1;
        idx[++num]=e[i].r;
    }
    sort(idx+1, idx+num+1);
    n=unique(idx+1, idx+num+1)-idx-1;
    for (int i=1; i<=n; i++){
        fa[i]=i;
    }
    for (int i=1; i<=m; i++){
        int x=lower_bound(idx+1, idx+n+1, e[i].l-1)-idx-1;
        int y=lower_bound(idx+1, idx+n+1, e[i].r)-idx-1;
        int fx=Find(x), fy=Find(y);
        if (fx==fy){
            if ((dis[x]^dis[y])!=e[i].flag){
                printf("%d\n", i-1);
                return 0;
            }
        }else{
            fa[fx]=fy;
            dis[fx]=dis[x]^dis[y]^e[i].flag;
        }
    }
    printf("%d\n", m);

    return 0;
}