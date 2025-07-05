#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

const int N=1e5+10;

int n;
int valx[N<<1];

struct ScanLine{
    int l, r, h;
    int val;

    bool operator<(const ScanLine &ref)const{
        return h<ref.h;
    }
}line[N<<1];
struct SegmentTree{
    
}
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
    seg.Init(1, 1, tot-1);
    for (int i=1; i<n; i++){
        seg.Add(1, line[i].l, line[i].r, line[i].val);
    }
    return 0;
}