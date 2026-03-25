#include <bits/stdc++.h>
using namespace std;
const int N=3e6+10;
const int Z=70;
int t, n, m;
struct Trie_Tree{
    int num=1;
    int ch[N][Z], sum[N];
    bool ed[N];
    int change(char c){
        if ('A'<=c&&c<='Z'){
            return c-'A';
        }
        if ('a'<=c&&c<='z'){
            return c-'a'+26;
        }
        return c-'0'+52;
    }
    void add(string s){
        int u=1, len=s.size();
        for (int i=0; i<len; i++){
            int c=change(s[i]);
            if (!ch[u][c]){
                ch[u][c]=++num;
            }
            u=ch[u][c];
            sum[u]++;
        }
        ed[u]=1;
    }
    int find(string s){
        int u=1, len=s.size();
        for (int i=0; i<len; i++){
            int c=change(s[i]);
            if (!ch[u][c]){
                return 0;
            }
            u=ch[u][c];
        }
        return sum[u];
    }
    void init(){
        for (int i=1; i<=num; i++){
            for (int j=0; j<70; j++){
                ch[i][j]=0;
            }
            ed[i]=0;
            sum[i]=0;
        }
        num=1;
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        tree.init();
        cin >> n >> m;
        string s;
        for (int i=1; i<=n; i++){
            cin >> s;
            tree.add(s);
        }
        for (int i=1; i<=m; i++){
            cin >> s;
            printf("%d\n", tree.find(s));
        }
    }
    return 0;
}