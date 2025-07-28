#include <iostream>
#include <stdio.h>
#include <cstring>
#define Change(c) c-'a'
// #define __Debug

using namespace std;
typedef long long ll;

const int N=1e6+10;

int n, m;
char c[N];

namespace Trie{
    int root=1, num=1;

    struct Node{
        int son[26];
        int cnt;
    }node[N];

    void Add(char c[]){
        int len=strlen(c), now=root;
        for (int i=0; i<len; i++){
            if (node[now].son[Change(c[i])]==0){
                node[now].son[Change(c[i])]=++num;
                now=num;
            }
            else{
                now=node[now].son[Change(c[i])];
            }
        }
        node[now].cnt++;
        return;
    }
    int Find(char c[]){
        int len=strlen(c), now=root, sum=0;
        for (int i=0; i<len; i++){
            if (node[now].son[Change(c[i])]==0){
                return sum;
            }
            else{
                now=node[now].son[Change(c[i])];
                sum=sum+node[now].cnt;
            }
        }
        return sum;
    }
}
using namespace Trie;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    #ifdef __Debug
        printf("%d\n", strlen(c));
    #endif
    for(int i=1; i<=n; i++){
        cin >> c;
        Add(c);
    }
    for (int i=1; i<=m; i++){
        cin >> c;
        printf("%d\n", Find(c));
    }
    return 0;
}