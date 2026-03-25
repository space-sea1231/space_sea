#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n, m, k, last;
struct Segment_Tree{
    struct Node{
        int maxn;
    }e[N<<2];
    void Add(int x, int l, int r, int X, int w){
        if (l==r){
            e[x].maxn=w;
            return ;
        }
        int mid=(l+r)>>1;
        if (X<=mid){
            Add(x<<1, l, mid, X, w);
        }else{
            Add(x<<1|1, mid+1, r, X, w);
        }
        e[x].maxn=max(e[x<<1].maxn, e[x<<1|1].maxn);
    }
    int Query(int x, int l, int r, int L, int R){
        if (L<=l&&r<=R){
            return e[x].maxn;
        }
        int mid=(l+r)>>1, maxn=0;
        if (L<=mid){
            maxn=max(maxn, Query(x<<1, l, mid, L, R));
        }
        if (mid+1<=R){
            maxn=max(maxn, Query(x<<1|1, mid+1, r, L, R));
        }
        return maxn;
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> m >> k;
    for (int i=1; i<=m; i++){
        char opt;
        cin >> opt;
        if (opt=='A'){
            int x;
            cin >> x;
            tree.Add(1, 1, N, ++n, (last+x)%k);
        }
        if (opt=='Q'){
            int x;
            cin >> x;
            last=tree.Query(1, 1, N, n-x+1, n);
            printf("%d\n", last);

        }
    }
    return 0;
}