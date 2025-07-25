#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, m;
int a[N];
struct Segment_Tree{
    struct Node{
        long long sum, vis;
    }e[N<<2];
    void build(int x, int l, int r){
        if (l==r){
            e[x].sum=a[l];
            return ;
        }
        int mid=(l+r)>>1;
        build(x<<1, l, mid);
        build(x<<1|1, mid+1, r);
        e[x].sum=e[x<<1].sum+e[x<<1|1].sum;
    }
    void down(int x, int l, int r){
        e[x<<1].vis+=e[x].vis;
        e[x<<1|1].vis+=e[x].vis;
        int mid=(l+r)>>1;
        e[x<<1].sum+=(mid-l+1)*e[x].vis;
        e[x<<1|1].sum+=(r-mid)*e[x].vis;
        e[x].vis=0;
    }
    void add(int x, int l, int r, int L, int R, int w){
        if (L<=l&&r<=R){
            e[x].vis+=w;
            e[x].sum+=(r-l+1)*w;
            return ;
        }
        down(x, l, r);
        int mid=(l+r)>>1;
        if (L<=mid){
            add(x<<1, l, mid, L, R, w);
        }
        if (mid+1<=R){
            add(x<<1|1, mid+1, r, L, R, w);
        }
        e[x].sum=e[x<<1].sum+e[x<<1|1].sum;
    }
    long long sum(int x, int l, int r, int L, int R){
        if (L<=l&&r<=R){
            return e[x].sum;
        }
        down(x, l, r);
        int mid=(l+r)>>1;
        long long ans=0;
        if (L<=mid){
            ans+=sum(x<<1, l, mid, L, R);
        }
        if (mid+1<=R){
            ans+=sum(x<<1|1, mid+1, r, L, R);
        }
        return ans;
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    tree.build(1, 1, n);
    for (int i=1; i<=m; i++){
        int opt;
        cin >> opt;
        if (opt==1){
            int x, y, z;
            cin >> x >> y >> z;
            tree.add(1, 1, n, x, y, z);
        }
        if (opt==2){
            int x, y;
            cin >> x >> y;
            printf("%lld\n", tree.sum(1, 1, n, x, y));
        }
    }

    return 0;
}