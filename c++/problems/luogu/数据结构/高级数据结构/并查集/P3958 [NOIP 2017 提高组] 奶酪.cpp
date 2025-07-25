#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e4+10;
int T, n, h, r, s, t;
int cnt;
bool vis[N];
struct Node{
    int x, y, z;
}e[N];
struct Union_Find{
    int fa[N];
    inline int Find(int x){
        if (x==fa[x]) return x;
        return fa[x]=Find(fa[x]);
    }
    inline void Insert(int x, int y){
        fa[Find(x)]=Find(y);
    }
    inline void Init(){
        for (int i=0; i<N; i++) fa[i]=i;
    }
}Uf;
inline int Pow(int x, int y){
    int sum=1;
    while (y){
        if (y&1){
            sum=sum*x;
        }
        x=x*x;
        y>>=1;
    }
    return sum;
}
inline int Dist(Node a, Node b){
    return Pow(a.x-b.x, 2)+Pow(a.y-b.y, 2)+Pow(a.z-b.z, 2);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> T;
    while (T--){
        Uf.Init();
        cin >> n >> h >> r;
        s=0, t=n+1;
        for (int i=1; i<=n; i++){
            cin >> e[i].x >> e[i].y >> e[i].z;
            for (int j=1; j<i; j++){
                if (Dist(e[i], e[j])<=(Pow(r, 2)<<2)){
                    Uf.Insert(i, j);
                }
            }
            if (e[i].z<=r) Uf.Insert(s, i);
            if (h-e[i].z<=r) Uf.Insert(i, t);
        }
        if (Uf.Find(s)==Uf.Find(t)) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}