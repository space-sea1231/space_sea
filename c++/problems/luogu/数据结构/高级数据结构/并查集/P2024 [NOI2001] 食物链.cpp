#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n, m, cnt;
struct Union_Find{
    int fa[N<<2];
    int Find(int x){
        if (fa[x]==x){
            return x;
        }
        return fa[x]=Find(fa[x]);
    }
    void Merge(int x, int y){
        if (Find(x+n)==Find(y)||Find(x)==Find(y+n)){
            cnt++;
            return ;
        }
        fa[Find(x)]=fa[Find(y)];
        fa[Find(x+n)]=fa[Find(y+n)];
        fa[Find(x+(n<<1))]=fa[Find(y+(n<<1))];
    }
    void Check(int x, int y){
        if (Find(x)==Find(y)||Find(x)==Find(y+n)){
            cnt++;
            return ;
        }
        fa[Find(x)]=fa[Find(y+(n<<1))];
        fa[Find(x+n)]=fa[Find(y)];
        fa[Find(x+(n<<1))]=fa[Find(y+n)];
    }
    Union_Find(){
        for (int i=1; i<(N<<2); i++){
            fa[i]=i;
        }
    }
}unf;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=m; i++){
        int opt, x, y;
        cin >> opt >> x >> y;
        if (x>n||y>n){
            cnt++;
            continue;
        }
        if (opt==1){
            unf.Merge(x, y);
        }
        if (opt==2){
            unf.Check(x, y);
        }
    }
    printf("%d\n", cnt);

    return 0;
}