#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int M=5e5+10;
int n, k, c, ans;
struct node{
    int l, r, sum, vis;
}tree[N<<1];
struct cow{
    int l, r, m;
    bool operator < (const cow &a){
        return r<a.r;
    }
}e[M];
void build(int x, int l, int r){
    tree[x].l=l, tree[x].r=r;
    if (l==r){
        return ;
    }
    int mid=(l+r)>>1;
    build(x<<1, l, mid);
    build(x<<1|1, mid+1, r);
}
void down(int x){
    tree[x<<1].vis+=tree[x].vis;
    tree[x<<1|1].vis+=tree[x].vis;
    tree[x<<1].sum+=tree[x].vis;
    tree[x<<1|1].sum+=tree[x].vis;
    tree[x].vis=0;
}
int check(int x, int l, int r){
    if (l<=tree[x].l&&tree[x].r<=r){
        return tree[x].sum;
    }
    if (tree[x].vis){
        down(x);
    }
    int mid=(tree[x].l+tree[x].r)>>1;
    int maxn=0;
    if (l<=mid){
        maxn=max(maxn, check(x<<1, l, r));
    }
    if (mid<r){
        maxn=max(maxn, check(x<<1|1, l, r));
    }
    tree[x].sum=max(tree[x<<1].sum, tree[x<<1|1].sum);
    
    return maxn;
}
void update(int x, int l, int r, int w){
    if (l<=tree[x].l&&tree[x].r<=r){
        tree[x].sum+=w;
        tree[x].vis+=w;
        return ;
    }
    if (tree[x].vis){
        down(x);
    }
    int mid=(tree[x].l+tree[x].r)>>1;
    int maxn=0;
    if (l<=mid){
        update(x<<1, l, r, w);
    }
    if (mid<r){
        update(x<<1|1, l, r, w);
    }
    tree[x].sum=max(tree[x<<1].sum, tree[x<<1|1].sum);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> k >> n >> c;
    build(1, 1, n);
    for (int i=1; i<=n*2; i++){
        // printf("Debug: %d %d %d\n", i, tree[i].l, tree[i].r);
    }
    for (int i=1; i<=k; i++){
        cin >> e[i].l >> e[i].r >> e[i].m;
    }
    sort(e+1, e+k+1);
    for (int i=1; i<=k; i++){
        // printf("Debug2: %d %d %d\n", e[i].l, e[i].r, e[i].m);
    }
    // return 0;
    for (int i=1; i<=k; i++){
        int sum=check(1, e[i].l, e[i].r-1);
        sum=min(c-sum, e[i].m);
        ans+=sum;
        update(1, e[i].l, e[i].r-1, sum);
    }
    printf("%d", ans);

    return 0;
}