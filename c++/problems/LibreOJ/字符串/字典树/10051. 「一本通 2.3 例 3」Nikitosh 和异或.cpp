#include <bits/stdc++.h>
using namespace std;
const int N=4e5+10;
const int Z=2;
int n;
int a[N], l[N], r[N];
struct Trie_Tree{
    int num=1;
    int ch[N<<5][Z];
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
    void init(){
        memset(ch, 0, sizeof(ch));
        num=1, add(0);
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    tree.init();
    int sum=0;
    for (int i=1; i<=n; i++){
        sum^=a[i];
        tree.add(sum);
        l[i]=max(l[i-1], tree.find(sum));
    }
    tree.init();
    for (int i=n; i>=1; i--){
        sum^=a[i];
        tree.add(sum);
        r[i]=max(r[i+1], tree.find(sum));
    }
    int ans=0;
    for (int i=1; i<=n; i++){
        ans=max(ans, l[i]+r[i+1]);
    }
    printf("%d\n", ans);

    return 0;
}