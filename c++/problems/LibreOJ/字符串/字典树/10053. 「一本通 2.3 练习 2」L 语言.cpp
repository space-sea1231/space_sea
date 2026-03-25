#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int Z=30;
int n, m;
bool flag[N<<4];
char s[N<<4];
struct Trie_Tree{
    int num=1;
    int ch[N<<4][Z];
    bool ed[N<<4];
    void add(char *s){
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
    void find(int start, char *s){
        int u=1, len=strlen(s);
        for (int i=start; i<len; i++){
            int c=s[i]-'a';
            if (!ch[u][c]){
                return ;
            }
            u=ch[u][c];
            if (ed[u]){
                flag[i+1]=1;
            }
        }
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> s;
        tree.add(s);
    }
    for (int i=1; i<=m; i++){
        cin >> s;
        memset(flag, 0, sizeof(flag));
        flag[0]=1;
        int len=strlen(s);
        for (int j=0; j<len; j++){
            if (flag[j]){
                tree.find(j, s);
            }
        }
        for (int j=len; j>=0; j--){
            if (flag[j]){
                printf("%d\n", j);
                break;
            }
        }
    }

    return 0;
}