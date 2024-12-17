#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int INF=1LL<<60;
int n, m, ans, a[N];
struct node{
    int sum, vis, l, r;
}tree[N<<1];
struct cow{
    int l, r;
    bool operator < (const cow &a){
        return r<a.r;
    }
}e[N];
void build (int x, int l, int r){
    int mid=(l+r)>>1;
    tree[x].l=l;
    tree[x].r=r;
    if (l==r){
        tree[x].sum=a[l];
        return ;
    }
    build(x<<1, l, mid);
    build(x<<1|1, mid+1, r);
    tree[x].sum=min(tree[x<<1].sum, tree[x<<1|1].sum);
}
void down(int x){
    tree[x<<1].vis+=tree[x].vis;
    tree[x<<1|1].vis+=tree[x].vis;
    tree[x<<1].sum-=tree[x].vis;
    tree[x<<1|1].sum-=tree[x].vis;
    tree[x].vis=0;
}
int check(int x, int l, int r){
    int mid=(tree[x].l+tree[x].r)>>1;
    if (tree[x].l>=l&&tree[x].r<=r){
        return tree[x].sum;
    }
    if (tree[x].vis){
        down(x);
    }
    int minn=INF;
    if (l<=mid){
        minn=min(minn, check(x<<1, l, r));
    }
    if (mid<r){
        minn=min(minn, check(x<<1|1, l, r));
    }
    return minn;
}
void update(int x, int l, int r){
    int mid=(tree[x].l+tree[x].r)>>1;
    if (tree[x].l>=l&&tree[x].r<=r){
        tree[x].sum--;
        tree[x].vis++;
        return ;
    }
    if (tree[x].vis){
        down(x);
    }
    if (l<=mid){
        update(x<<1, l, r);
    }
    if (mid<r){
        update(x<<1|1, l, r);
    }
    tree[x].sum=min(tree[x<<1].sum, tree[x<<1|1].sum);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    build(1, 1, n);
    for (int i=1; i<=m; i++){
        cin >> e[i].l >> e[i].r;
    }
    sort(e+1, e+m+1);
    for (int i=1; i<=m; i++){
        if (check(1, e[i].l, e[i].r)>0){
            update(1, e[i].l, e[i].r);
            ans++;
        }
    }
    printf("%lld", ans);
    
    return 0;
}