#include <bits/stdc++.h>
using namespace std;
const int N=4e6+10;
const int Z=2;
int n, ans;
struct Trie_Tree{
    int num=1;
    int ch[N][Z];
    void add(int x){
        int u=1;
        for (int i=30; i>=0; i--){
            int c=(x>>i)&1;
            if (!ch[u][c]){
                ch[u][c]=++num;
            }
            u=ch[u][c];
        }
    }
    int find(int x){
        int u=1, sum=0;
        for (int i=30; i>=0; i--){
            int c=(x>>i)&1;
            if (ch[u][c^1]){
                sum+=(1<<i);
                c^=1;
            }
            u=ch[u][c];
        }
        return sum;
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        int x;
        cin >> x;
        ans=max(ans, tree.find(x));
        tree.add(x);
    }
    printf("%d\n", ans);
    
    return 0;
}