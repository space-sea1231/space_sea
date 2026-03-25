#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int Z=20;
int t, n;
string s[N];
struct Trie_Tree{
    int num=1;
    int ch[N][Z];
    bool ed[N];
    int change(char c){
        return c-'0';
    }
    void add(string s){
        int u=1, len=s.size();
        for (int i=0; i<len; i++){
            int c=change(s[i]);
            if (!ch[u][c]){
                ch[u][c]=++num;
            }
            u=ch[u][c];
        }
        ed[u]=1;
    }
    bool find(string s){
        int u=1, len=s.size();
        for (int i=0; i<len; i++){
            int c=change(s[i]);
            if (!ch[u][c]){
                return 0;
            }
            u=ch[u][c];
        }
        return 1; 
    }
    void init(){
        memset(ch, 0, sizeof(ch));
        memset(ed, 0, sizeof(ed));
        num=1;
    }
}tree;
bool cmp(string a, string b){
    return a.size()>b.size();
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        tree.init();
        cin >> n;
        for (int i=1; i<=n; i++){
            cin >> s[i];
        }
        sort(s+1, s+n+1, cmp);
        bool flag=0;
        for (int i=1; i<=n; i++){
            if (tree.find(s[i])){
                flag=1;
                break;
            }
            tree.add(s[i]);
        }
        if (flag){
            printf("NO\n");
        }else{
            printf("YES\n");
        }
    }

    return 0;
}