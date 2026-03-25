#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n, m;
int a[N];
struct Segment_Tree{
    struct Node{
        int sum;
        bool flag=0;
    }e[N<<2];
    bool Check(int x){
        if (x==0||x==1){
            return 1;
        }
        return 0;
    }
    void Build(int x, int l, int r){
        if (l==r){
            e[x].sum=a[l];
            if (Check(a[l])){
                e[x].flag=1;
            }
            return ;
        }
        int mid=(l+r)>>1;
        Build(x<<1, l, mid);
        Build(x<<1|1, mid+1, r);
        e[x].sum=e[x<<1].sum+e[x<<1|1].sum;
        if (e[x<<1].flag&&e[x<<1|1].flag){
            e[x].flag=1;
        }
    }
    void Change(int x, int l, int r, int L, int R){
        if (e[x].flag){
            return ;
        }
        if (L<=l&&r<=R&&l==r){
            e[x].sum=sqrt(e[x].sum);
            if (Check(e[x].sum)){
                e[x].flag=1;
            }
            return ;
        }
        int mid=(l+r)>>1;
        if (L<=mid){
            Change(x<<1, l, mid, L, R);
        }
        if (mid+1<=R){
            Change(x<<1|1, mid+1, r, L, R);
        }
        e[x].sum=e[x<<1].sum+e[x<<1|1].sum;
        if (e[x<<1].flag&&e[x<<1|1].flag){
            e[x].flag=1;
        }
    }
    int Query(int x, int l, int r, int L, int R){
        if (L<=l&&r<=R){
            return e[x].sum;
        }
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
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    tree.Build(1, 1, n);
    cin >> m;
    for (int i=1; i<=m; i++){
        int opt, x, y;
        cin >> opt >> x >> y;
        if (x>y){
            swap(x, y);
        }
        if (opt==1){
            printf("%lld\n", tree.Query(1, 1, n, x, y));
        }
        if (opt==2){
            tree.Change(1, 1, n, x, y);
        }
    }

    return 0;
}