#include <bits/stdc++.h>
#define Pair pair<int, double>
using namespace std;
const int N=1e5+10;
const int Mod1=39989;
const int Mod2=1e9+1;
const double eps=1e-9;
int n, last;
struct Li_Chao_Segment_Tree{
    int cnt;
    int vis[N<<1];
    struct Node{
        double k, b;
    }e[N<<1];
    void Add(int sx, int sy, int fx, int fy){
        cnt++;
        if (sx==sy){
            e[cnt].k=0;
            e[cnt].b=max(sy, fy);
        }else{
            e[cnt].k=1.0*(fy-sy)/(fx-sx);
            e[cnt].b=sy-e[cnt].k*sx;
        }
    }
    double Calc(int x, int val){
        return e[x].k*val+e[x].b;
    }
    int Check(double x, double y){
        if (x-y>eps){
            return 1;
        }
        if (y-x>eps){
            return -1;
        }
        return 0;
    }
    void Down(int root, int l, int r, int u){
        int &v=vis[root], mid=(l+r)>>1;
        int check_mid=Check(Calc(u, mid), Calc(v, mid));
        if (check_mid==1||(check_mid==0&&u<v)){
            swap(u, v);
        }
        int check_l=Check(Calc(u, l), Calc(v, l));
        int check_r=Check(Calc(u, r), Calc(v, r));
        if (check_l==1||(check_l==0&&u<v)){
            Down(root<<1, l, mid, u);
        }
        if (check_r==1||(check_r==0&&u<v)){
            Down(root<<1|1, mid+1, r, u);
        }
    }
    void Update(int root, int l, int r, int L, int R, int u){
        if (L<=l&&r<=R){
            Down(root, l, r, u);
            return ;
        }
        int mid=(l+r)>>1;
        if (L<=mid){
            Update(root<<1, l, mid, L, R, u);
        }
        if (mid+1<=R){
            Update(root<<1|1, mid+1, r, L, R, u);
        }
    }
    Pair Max(Pair x, Pair y){
        if (x.second-y.second>eps){
            return x;
        }
        if (y.second-x.second>eps){
            return y;
        }
        if (x.first<y.first){
            return x;
        }else{
            return y;
        }
    }
    Pair Query(int root, int l, int r, int x){
        if (x<l||r<x){
            return {0, 0};
        }
        int mid=(l+r)>>1;
        double ans=Calc(vis[root], x);
        if (l==r){
            return {vis[root], ans};
        }
        return Max({vis[root], ans}, Max(Query(root<<1, l, mid, x), Query(root<<1|1, mid+1, r, x)));
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        int opt;
        cin >> opt;
        if (opt==0){
            int x;
            cin >> x;
            x=(x+last-1+Mod1)%Mod1+1;
            last=tree.Query(1, 1, Mod1, x).first;
            printf("%d\n", last);
        }
        if (opt==1){
            int sx, sy, fx, fy;
            cin >> sx >> sy >> fx >> fy;
            sx=(sx+last-1+Mod1)%Mod1+1;
            fx=(fx+last-1+Mod1)%Mod1+1;
            sy=(sy+last-1+Mod2)%Mod2+1;
            fy=(fy+last-1+Mod2)%Mod2+1;
            if (sx>fx){
                swap(sx, fx);
                swap(sy, fy);
            }
            tree.Add(sx, sy, fx, fy);
            tree.Update(1, 1, Mod1, sx, fx, tree.cnt);
        }
    }

    return 0;
}