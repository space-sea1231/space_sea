#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;

const int N=1e5+10;

int n;
ll ans;
int valx[N<<1];

struct ScanLine{
    int l, r, h;
    int val;

    bool operator<(const ScanLine &ref)const{
        return h<ref.h;
    }
}line[N<<1];
struct SegmentTree{
    struct Node{
        int l, r;
        int val, len;
    }node[N<<5];
    void Build(int x, int l, int r){
        node[x].l=l;
        node[x].r=r;
        if (l==r){
            return ;
        }
        int mid=(l+r)>>1;
        Build(x<<1, l, mid);
        Build(x<<1|1, mid+1, r);
    }
    void PushUp(int x){
        int l=node[x].l;
        int r=node[x].r;
        if (node[x].val){
            node[x].len=valx[r+1]-valx[l];
        }else{
            node[x].len=node[x<<1].len+node[x<<1|1].len;
        }
    }
    void Add(int x, int L, int R, int val){
        int l=node[x].l;
        int r=node[x].r;
        if (valx[r+1]<=L||R<=valx[l]){
            return ;
        }
        if (L<=valx[l]&&valx[r+1]<=R){
            node[x].val+=val;
            PushUp(x);
            return ;
        }
        int mid=(l+r)>>1;
        Add(x<<1, L, R, val);
        Add(x<<1|1, L, R, val);
        PushUp(x);
    }
}seg;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=1; i<=n; i++){
        int sx, sy, fx, fy;
        cin >> sx >> sy >> fx >> fy;
        line[(i<<1)-1]=(ScanLine){sx, fx, sy, 1};
        line[i<<1]=(ScanLine){sx, fx, fy, -1};
        valx[(i<<1)-1]=sx;
        valx[i<<1]=fx;
    }
    n<<=1;
    sort(line+1, line+n+1);
    sort(valx+1, valx+n+1);
    int tot=unique(valx+1, valx+n+1)-valx-1;
    seg.Build(1, 1, tot-1);
    for (int i=1; i<n; i++){
        seg.Add(1, line[i].l, line[i].r, line[i].val);
        ans+=seg.node[1].len*(line[i+1].h-line[i].h);
    }
    printf("%lld\n", ans);

    return 0;
}