#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
const int Z=2;
int n, m;
struct Trie_Tree{
    int num=1;
    int ch[N][Z], sum[N];
    int ed[N], tmp[N];
    void add(int len){
        int u=1;
        for (int i=1; i<=len; i++){
            int c=tmp[i];
            if (!ch[u][c]){
                ch[u][c]=++num;
            }
            u=ch[u][c];
            sum[u]++;
        }
        ed[u]++;
    }
    int find(int len){
        int u=1, ans=0;
        for (int i=1; i<=len; i++){
            int c=tmp[i];
            if (!ch[u][c]){
                return ans;
            }
            u=ch[u][c];
            ans+=ed[u];
        }
        return ans-ed[u]+sum[u];
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        int len;
        cin >> len;
        for (int j=1; j<=len; j++){
            cin >> tree.tmp[j];
        }
        tree.add(len);
    }
    for (int i=1; i<=m; i++){
        int len;
        cin >> len;
        for (int j=1; j<=len; j++){
            cin >> tree.tmp[j];
        }
        printf("%d\n", tree.find(len));
    }
    
    return 0;
}