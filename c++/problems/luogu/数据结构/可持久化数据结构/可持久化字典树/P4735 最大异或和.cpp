#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=6e5+10;

int n, m;
int sum[N];

namespace Trie{
    int num;
    int root[N];
    int last[N<<5];

    struct Node{
        int son[2];
    };
    Node node[N<<5];

    void Insert(int now, int k, int p, int q){
        if (k<0){
            last[q]=now;
            return;
        }
        int c=sum[now]>>k&1;
        if (p>0){
            node[q].son[c^1]=node[p].son[c^1];
        }
        node[q].son[c]=++num;
        Insert(now, k-1, node[p].son[c], node[q].son[c]);
        last[q]=max(last[node[q].son[0]], last[node[q].son[1]]);
    }
    int Query(int now, int val, int k, int limit){
        if (k<0){
            return sum[last[now]]^val;
        }
        int c=val>>k&1;
        if (last[node[now].son[c^1]]>=limit){
            return Query(node[now].son[c^1], val, k-1, limit);
        }
        else{
            return Query(node[now].son[c], val, k-1, limit);
        }
    }
    void Init(){
        last[0]=-1;
        root[0]=++num;
        Insert(0, 23, 0, root[0]);
    }
}
using namespace Trie;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m; Init();
    for (int i=1; i<=n; i++){
        int x;
        cin >> x;
        sum[i]=sum[i-1]^x;
        root[i]=++num;
        Insert(i, 23, root[i-1], root[i]);
    }
    for (int i=1; i<=m; i++){
        char opt;
        cin >> opt;
        if (opt=='A'){
            int x;
            cin >> x;
            root[++n]=++num;
            sum[n]=sum[n-1]^x;
            Insert(n, 23, root[n-1], root[n]);
        }
        if (opt=='Q'){
            int l, r, x;
            cin >> l >> r >> x;
            printf("%d\n", Query(root[r-1], sum[n]^x, 23, l-1));
        }
    }
    return 0;
}