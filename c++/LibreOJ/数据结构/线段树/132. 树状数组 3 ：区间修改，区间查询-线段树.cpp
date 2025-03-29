#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n, m;
int a[N];
struct Segment_Tree{
    struct Node{
        int sum, vis;
    }e[N<<1];
    void Build(int x, int l, int r){
        if (l==r){
            e[x].sum=a[l];
            return ;
        }
        int mid=(l+r)>>1;
        Build(x<<1, l, mid);
        Build(x<<1|1, mid+1, r);
        e[x].sum=e[x<<1].sum+e[x<<1|1].sum;
    }
    void Down(int x, int l, int r){
        int mid=(l+r)>>1;
        e[x<<1].vis+=e[x].vis;
        e[x<<1|1].vis+=e[x].vis;
        e[x<<1].sum+=(mid-l+1)*e[x].vis;
        e[x<<1|1].sum+=(r-mid)*e[x].vis;
        e[x].vis=0;
    }
    void Add(int x, int l, int r, int L, int R, int w){
        if (L<=l&&r<=R){
            e[x].vis+=w;
            e[x].sum+=(r-l+1)*w;
            return ;
        }
        Down(x, l, r);
        int mid=(l+r)>>1;
        if (L<=mid){
            Add(x<<1, l, mid, L, R, w);
        }
        if (mid+1<=R){
            Add(x<<1|1, mid+1, r, L, R, w);
        }
        e[x].sum=e[x<<1].sum+e[x<<1|1].sum;
    }
    int Query(int x, int l, int r, int L, int R){
        if (L<=l&&r<=R){
            return e[x].sum;
        }
        Down(x, l, r);
        int mid=(l+r)>>1, ans=0;
        if (L<=mid){
            ans+=Query(x<<1, l, mid, L, R);
        }
        if (mid+1<=R){
            ans+=Query(x<<1|1, mid+1, r, L, R);
        }
        return ans;
    }
}tree;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    tree.Build(1, 1, n);
    for (int i=1; i<=m; i++){
        int opt;
        cin >> opt;
        if (opt==1){
            int x, y, z;
            cin >> x >> y >> z;
            tree.Add(1, 1, n, x, y, z);
        }
        if (opt==2){
            int x, y;
            cin >> x >> y;
            printf("%lld\n", tree.Query(1, 1, n, x, y));
        }
    }
    return 0;
}