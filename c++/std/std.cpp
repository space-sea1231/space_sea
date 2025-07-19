#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e6+10;

int n, m;
int a[N];

namespace SegmentTree{
    int num;
    int root[N<<1];
    
    struct Node{
        int lson, rson;
        int dat;
    };
    Node node[N<<8];

    int Build(int l, int r){
        int p=++num;
        if (l==r){
            node[p].dat=a[l];
            return p;
        }
        int mid=(l+r)>>1;
        node[p].lson=Build(l, mid);
        node[p].rson=Build(mid+1, r);
        return p;
    }
    int Insert(int now, int l, int r, int cur, int val){
        int p=++num;
        node[p]=node[now];
        if (l==r){
            node[p].dat=val;
            return p;
        }
        int mid=(l+r)>>1;
        if (cur<=mid){
            node[p].lson=Insert(node[now].lson, l, mid, cur, val);
        }
        else{
            node[p].rson=Insert(node[now].rson, mid+1, r, cur, val);
        }
        return p;
    }
    int Query(int now, int l, int r, int cur){
        if (l==r){
            return node[now].dat;
        }
        int mid=(l+r)>>1;
        if (cur<=mid){
            return Query(node[now].lson, l, mid, cur);
        }
        else{
            return Query(node[now].rson, mid+1, r, cur);
        }
        return 0;
    }
}
using namespace SegmentTree;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    root[0]=Build(1, n);
    for (int i=1; i<=m; i++){
        int ver, opt;
        cin >> ver >> opt;
        if (opt==1){
            int cur, val;
            cin >> cur >> val;
            root[i]=Insert(root[ver], 1, n, cur, val);
        }
        if (opt==2){
            int cur;
            cin >> cur;
            printf("%d\n", Query(root[ver], 1, n, cur));
            root[i]=root[ver];
        }
    }

    return 0;
}