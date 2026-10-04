#include <iostream>
#include <stdio.h>
#include <algorithm>
#define Mod(x) (x%MOD+MOD)%MOD
#define __Debug

using namespace std;
typedef long long ll;

const int N=2e3+10;
const int MOD=1e9+7;

int n;
int cnt;
int a[N];
int fa[N], vis[N];

struct Node{
    int x, y;
    int sum;
    bool operator<(const Node &src)const{
        return sum>src.sum;
    }
}node[N*N];

int Pow(int a, int b){
    int sum=1;
    while (b>0){
        if (b&1==true){
            sum=Mod((ll)sum*a);
        }
        a=Mod((ll)a*a);
        b=b>>1;
    }
    return sum;
}
int Find(int x){
    if (fa[x]==x) return x;
    return fa[x]=Find(fa[x]);
}
void Init(){
    for (int i=1; i<=n; i++){
        fa[i]=i;
    }
}
signed main(){
    freopen("Q.in", "r", stdin);
    freopen("Q.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n; Init();
    for (int i=1; i<=n; i++){
        cin >> a[i];
        for (int j=1; j<i; j++){
            node[++cnt].sum=min(Pow(a[i], a[j]), Pow(a[j], a[i]));
            node[cnt].x=i, node[cnt].y=j;
        }
    }
    sort(node+1, node+cnt+1);
    for (int i=1; i<=cnt; i++){
        int x=Find(node[i].x);
        int y=Find(node[i].y);
        if (x==y){
            printf("%d\n", node[i].sum);
            return 0;
        }
        if (vis[x]==0){
            vis[x]=y;
        }
        else{
            fa[Find(vis[x])]=y;
        }
        if (vis[y]==0){
            vis[y]=x;
        }
        else{
            fa[Find(vis[y])]=x;
        }
    }
    printf("0\n");

    return 0;
}
// 1 2 3 4 5
//1 2
//2 3
//3 4
//1 5
//fa: 1 4 3 5 5
//vis: 2 1 2 3 1