#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n;
struct Union_Find{
    int fa[N], dis[N], siz[N];
    void Init(){
        for (int i=1; i<=n; i++){
            fa[i]=i;
            siz[i]=1;
        }
    }
    int Find(int x){
        if (fa[x]==x){
            return x;
        }
        int root=Find(fa[x]);
        dis[x]+=dis[fa[x]];
        return fa[x]=root;
    }
    void Merge(int x, int y){
        x=Find(x), y=Find(y);
        fa[x]=y;
        dis[x]=siz[y];
        siz[y]+=siz[x];
    }
    int Dis(int x, int y){
        return abs(dis[x]-dis[y])-1;
    }
}unf;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    unf.Init();
    for (int i=1; i<=n; i++){
        char opt;
        int x, y;
        cin >> opt >> x >> y;
        if (opt=='M'){
            unf.Merge(x, y);
        }
        if (opt=='C'){
            int fx=unf.Find(x);
            int fy=unf.Find(y);
            if (fx==fy){
                printf("%d\n", unf.Dis(x, y));
            }else{
                printf("-1\n");
            }
        }
    }
    return 0;
}