#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=2e6+10;

int n;
int ans;

namespace Trie{
    int root=1, tot=1;

    struct Node{
        int son[2];
    }node[N];

    int Search(int x){
        int now=root, sum=0;
        for (int i=30; i>=0; i--){
            bool flag=(x>=(1<<i));
            x=(x<(1<<i)?x:x-(1<<i));
            if (node[now].son[flag^1]){
                now=node[now].son[flag^1];
                sum=sum+(1<<i);
            }
            else if (node[now].son[flag]){
                now=node[now].son[flag];
            }
            else{
                return sum;
            }
        }
        return sum;
    }
    void Add(int x){
        int now=root;
        for (int i=30; i>=0; i--){
            bool flag=(x>=(1<<i));
            x=(x<(1<<i)?x:x-(1<<i));
            if (node[now].son[flag]){
                now=node[now].son[flag];
            }
            else{
                node[now].son[flag]=++tot;
                now=tot;
            }
        }
        return;
    }
}
using namespace Trie;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=1; i<=n; i++){
        int a;
        cin >> a;
        ans=max(ans, Search(a));
        Add(a);
    }
    printf("%d\n", ans);

    return 0;
}