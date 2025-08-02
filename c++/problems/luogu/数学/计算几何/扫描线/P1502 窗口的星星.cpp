#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
// #define __Debug
#define int long long

using namespace std;
typedef long long ll;

const int N=1e6+10;

int t;
int n, w, h;
ll ans;
int valx[N<<1];
// ll sum[N<<1];

struct ScanLine{
    int l, r, h;
    int val;

    bool operator<(const ScanLine &ref)const{
        if (h == ref.h) return val > ref.val;
        return h<ref.h;
    }
}line[N<<1];

struct SegmentTree{
    struct Node{
        int l, r;
        ll val, maxn;
    }node[N<<2];
    void Build(int x, int l, int r){
        node[x].l=l;
        node[x].r=r;
        node[x].val=node[x].maxn=0;
        if (l==r){
            return ;
        }
        int mid=(l+r)>>1;
        Build(x<<1, l, mid);
        Build(x<<1|1, mid+1, r);
    }
    void PushUp(int x){
        node[x].maxn=max(node[x<<1].maxn, node[x<<1|1].maxn);
    }
    void PushDown(int x){
        node[x<<1].val+=node[x].val;
        node[x<<1].maxn+=node[x].val;
        node[x<<1|1].val+=node[x].val;
        node[x<<1|1].maxn+=node[x].val;
        // sum[node[x<<1].l]+=node[x].val;
        // sum[node[x<<1].r]+=node[x].val;
        // sum[node[x<<1|1].l]+=node[x].val;
        // sum[node[x<<1|1].r]+=node[x].val;
        // ans=max(ans, sum[node[x<<1].l]);
        // ans=max(ans, sum[node[x<<1].r]);
        // ans=max(ans, sum[node[x<<1|1].l]);
        // ans=max(ans, sum[node[x<<1|1].r]);
        node[x].val=0;
    }
    void Add(int x, int L, int R, int val){
        int l=node[x].l;
        int r=node[x].r;
        // if (valx[r]<L||R<valx[l]){
        //     return ;
        // }
        if (L<=valx[l]&&valx[r]<=R){
            node[x].val+=val;
            node[x].maxn+=val;
            // sum[l]+=val;
            // sum[r]+=val;
            // ans=max(ans, sum[l]);
            // ans=max(ans, sum[r]);
            return ;
        }
        PushDown(x);
        int mid=(l+r)>>1;
        if(L<=valx[mid])Add(x<<1,L,R,val);
	    if(R>valx[mid])Add(x<<1|1,L,R,val);
        PushUp(x);
    }
}seg;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--){
        // memset(line, 0, sizeof(line));
        // memset(valx, 0, sizeof(valx));
        // memset(seg.node, 0, sizeof(seg.node));
        cin >> n >> w >> h;
        for (int i=1; i<=n; i++){
            int sx, sy, fx, fy, val;
            cin >> sx >> sy >> val;
            fx=sx+w-1, fy=sy+h-1;
            line[(i<<1)-1]=(ScanLine){sx, fx, sy, val};
            line[i<<1]=(ScanLine){sx, fx, fy, -val};
            valx[(i<<1)-1]=sx;
            valx[i<<1]=fx;
        }
        n<<=1;
        sort(line+1, line+n+1);
        sort(valx+1, valx+n+1);
        int tot=unique(valx+1, valx+n+1)-valx-1;
        seg.Build(1, 1, tot);
        ll ans=0;
        for (int i=1; i<n; i++){
            seg.Add(1, line[i].l, line[i].r, line[i].val);
            #ifdef __Debug
                printf("i=%d l=%d r=%d val=%d\n", i, line[i].l, line[i].r, line[i].val);
            #endif
            // sum[line[i].l]+=line[i].val;
            // sum[line[i].r]+=line[i].val;
            // ans=max(ans, sum[line[i].l]);
            // ans=max(ans, sum[line[i].r]);
            ans=max(ans, seg.node[1].maxn);
        }
        printf("%lld\n", ans);
    }

    return 0;
}