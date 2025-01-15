#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int n, m, Mod, a[N];
struct node{
    int l, r, sum, vis_a, vis_m;
}e[N*2];
void build(int x, int l, int r){
    int mid=(l+r)>>1;
    e[x].l=l;
    e[x].r=r;
    e[x].vis_m=1;
    if (l==r){
        e[x].sum=a[l]%Mod;
        return;
    }
    build(x*2, l, mid);
    build(x*2+1, mid+1, r);
    e[x].sum=(e[x*2].sum+e[x*2+1].sum)%Mod;
}
void down(int x){
    e[x*2].sum=(e[x*2].sum*e[x].vis_m+(e[x*2].r-e[x*2].l+1)*e[x].vis_a)%Mod;
    e[x*2+1].sum=(e[x*2+1].sum*e[x].vis_m+(e[x*2+1].r-e[x*2+1].l+1)*e[x].vis_a)%Mod;
    e[x*2].vis_a=(e[x*2].vis_a*e[x].vis_m+e[x].vis_a)%Mod;
    e[x*2+1].vis_a=(e[x*2+1].vis_a*e[x].vis_m+e[x].vis_a)%Mod;
    e[x*2].vis_m=(e[x*2].vis_m*e[x].vis_m)%Mod;
    e[x*2+1].vis_m=(e[x*2+1].vis_m*e[x].vis_m)%Mod;
    e[x].vis_a=0;
    e[x].vis_m=1;
}
void mul(int x, int l, int r, int w){
    int mid=(e[x].l+e[x].r)>>1;
    if (e[x].l>=l&&e[x].r<=r){
        e[x].vis_a=e[x].vis_a*w%Mod;
        e[x].vis_m=e[x].vis_m*w%Mod;
        e[x].sum=e[x].sum*w%Mod;
        return;
    }
    down(x);
    if (l<=mid){
        mul(x*2, l, r, w);
    }
    if (mid<r){
        mul(x*2+1, l, r, w);
    }
    e[x].sum=(e[x*2].sum+e[x*2+1].sum)%Mod;
}
void add(int x, int l, int r, int w){
    int mid=(e[x].l+e[x].r)>>1;
    if (e[x].l>=l&&e[x].r<=r){
        e[x].vis_a=(e[x].vis_a+w)%Mod;
        e[x].sum=(e[x].sum+(e[x].r-e[x].l+1)*w)%Mod;
        return;
    }
    down(x);
    if (l<=mid){
        add(x*2, l, r, w);
    }
    if (mid<r){
        add(x*2+1, l, r, w);
    }
    e[x].sum=(e[x*2].sum+e[x*2+1].sum)%Mod;
}
int sum(int x, int l, int r){
    int mid=(e[x].l+e[x].r)>>1;
    if (e[x].l>=l&&e[x].r<=r){
        return e[x].sum;
    }
    down(x);
    int ans=0;
    if (l<=mid){
        ans=(ans+sum(x*2, l, r))%Mod;
    }
    if (mid<r){
        ans=(ans+sum(x*2+1, l, r))%Mod;
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> Mod;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    build(1, 1, n);
    int opt, x, y, z;
    for (int i=1; i<=m; i++){
        cin >> opt;
        if (opt==1){
            cin >> x >> y >> z;
            mul(1, x, y, z);
        }
        if (opt==2){
            cin >> x >> y >> z;
            add(1, x, y, z);
        }
        if (opt==3){
            cin >> x >> y;
            printf("%lld\n", sum(1, x, y));
        }
    }
    return 0;
}
//