#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
const int M=60;
const int Z=30;
int n, m;
struct Trie_Tree{
    int num=1;
    int ch[N*M][Z];
    char s[M];
    bool ed[N*M], vis[N*M];
    void add(){
        int u=1, len=strlen(s);
        for (int i=0; i<len; i++){
            int c=s[i]-'a';
            if (!ch[u][c]){
                ch[u][c]=++num;
            }
            u=ch[u][c];
        }
        ed[u]=1;
    }
    void find(){
        int u=1, len=strlen(s);
        for (int i=0; i<len; i++){
            int c=s[i]-'a';
            if (!ch[u][c]){
                printf("WRONG\n");
                return ;
            }
            u=ch[u][c];
        }
        if (!ed[u]){
            printf("WRONG\n");
        }else if (vis[u]){
            printf("REPEAT\n");
        }else{
            vis[u]=1;
            printf("OK\n");
        }
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> tree.s;
        tree.add();
    }
    cin >> m;
    for (int i=1; i<=m; i++){
        cin >> tree.s;
        tree.find();
    }
    
    return 0;
}