#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n, m, Mod;
struct Segment_Tree{
    int a[N];
    struct node{
        int sum, vis_add, vis_mul;
    }e[N*2];
    void build(int x, int l, int r){
        int mid=(l+r)>>1;
        e[x].vis_mul=1;
        if (l==r){
            e[x].sum=a[l]%Mod;
            return;
        }
        build(x<<1, l, mid);
        build(x<<1|1, mid+1, r);
        e[x].sum=(e[x<<1].sum+e[x<<1|1].sum)%Mod;
    }
    void down(int x, int l, int r){
        int mid=(l+r)>>1;
        e[x<<1].sum=(e[x<<1].sum*e[x].vis_mul+(mid-l+1)*e[x].vis_add)%Mod;
        e[x<<1|1].sum=(e[x<<1|1].sum*e[x].vis_mul+(r-mid)*e[x].vis_add)%Mod;
        e[x<<1].vis_add=(e[x<<1].vis_add*e[x].vis_mul+e[x].vis_add)%Mod;
        e[x<<1|1].vis_add=(e[x<<1|1].vis_add*e[x].vis_mul+e[x].vis_add)%Mod;
        e[x<<1].vis_mul=(e[x<<1].vis_mul*e[x].vis_mul)%Mod;
        e[x<<1|1].vis_mul=(e[x<<1|1].vis_mul*e[x].vis_mul)%Mod;
        e[x].vis_add=0, e[x].vis_mul=1;
    }
    void mul(int x, int l, int r, int L, int R, int w){
        if (L<=l&&r<=R){
            e[x].vis_add=e[x].vis_add*w%Mod;
            e[x].vis_mul=e[x].vis_mul*w%Mod;
            e[x].sum=e[x].sum*w%Mod;
            return;
        }
        down(x, l, r);
        int mid=(l+r)>>1;
        if (L<=mid){
            mul(x<<1, l, mid, L, R, w);
        }
        if (mid+1<=R){
            mul(x<<1|1, mid+1, r, L, R, w);
        }
        e[x].sum=(e[x<<1].sum+e[x<<1|1].sum)%Mod;
    }
    void add(int x, int l, int r, int L, int R, int w){
        if (L<=l&&r<=R){
            e[x].vis_add=(e[x].vis_add+w)%Mod;
            e[x].sum=(e[x].sum+(r-l+1)*w)%Mod;
            return;
        }
        down(x, l, r);
        int mid=(l+r)>>1;
        if (L<=mid){
            add(x<<1, l, mid, L, R, w);
        }
        if (mid+1<=R){
            add(x<<1|1, mid+1, r, L, R, w);
        }
        e[x].sum=(e[x<<1].sum+e[x<<1|1].sum)%Mod;
    }
    int sum(int x, int l, int r, int L, int R){
        if (L<=l&&r<=R){
            return e[x].sum;
        }
        down(x, l, r);
        int mid=(l+r)>>1, ans=0;
        if (L<=mid){
            ans=(ans+sum(x<<1, l, mid, L, R))%Mod;
        }
        if (mid+1<=R){
            ans=(ans+sum(x<<1|1, mid+1, r, L, R))%Mod;
        }
        return ans;
    }
}tree;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> Mod;
    for (int i=1; i<=n; i++){
        cin >> tree.a[i];
    }
    tree.build(1, 1, n);
    int opt, x, y, z;
    for (int i=1; i<=m; i++){
        cin >> opt;
        if (opt==1){
            cin >> x >> y >> z;
            tree.mul(1, 1, n, x, y, z);
        }
        if (opt==2){
            cin >> x >> y >> z;
            tree.add(1, 1, n, x, y, z);
        }
        if (opt==3){
            cin >> x >> y;
            printf("%lld\n", tree.sum(1, 1, n, x, y));
        }
    }
    return 0;
}
//