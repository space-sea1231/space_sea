#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int t, n;
struct Node{
    int x, y, opt;
    bool operator<(const Node &a){
        return opt>a.opt;
    }
}e[N];
struct Discretization{
    int num, len;
    int idx[N<<1];
    void Add(int x){
        idx[++num]=x;
    }
    void Get(){
        sort(idx+1, idx+num+1);
        len=unique(idx+1, idx+num+1)-idx-1;
        for (int i=1; i<=n; i++){
            e[i].x=lower_bound(idx+1, idx+len+1, e[i].x)-idx-1;
            e[i].y=lower_bound(idx+1, idx+len+1, e[i].y)-idx-1;
        }
    }
    void Init(){
        memset(idx, 0, sizeof(idx));
        num=0, len=0;
    }
}dca;
struct Union_Find{
    int fa[N];
    int Find(int x){
        if (fa[x]==x){
            return x;
        }
        return fa[x]=Find(fa[x]);
    }
    void Add(int x, int y){
        fa[Find(x)]=Find(y);
    }
    bool Match(int x, int y){
        int fx=Find(x);
        int fy=Find(y);
        if (fx==fy){
            return 1;
        }
        return 0;
    }
    void Init(){
        for (int i=0; i<N; i++){
            fa[i]=i;
        }
    }
}unf;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        unf.Init();
        dca.Init();
        cin >> n;
        for (int i=1; i<=n; i++){
            cin >> e[i].x >> e[i].y >> e[i].opt;
            dca.Add(e[i].x), dca.Add(e[i].y);
        }
        dca.Get();
        sort(e+1, e+n+1);
        bool flag=1;
        for (int i=1; i<=n; i++){
            if (e[i].opt==0){
                if (unf.Match(e[i].x, e[i].y)){
                    flag=0;
                }
            }
            if (e[i].opt==1){
                unf.Add(e[i].x, e[i].y);
            }
        }
        if (flag){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }
    return 0;
}