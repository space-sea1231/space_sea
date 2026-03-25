#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
const int Z=2;
struct Trie_Tree{
    int num=1;
    int ch[N][Z];
    bool flag=0;
    bool ed[N];
    void add(string s){
        int u=1, len=s.size();
        for (int i=0; i<len; i++){
            int c=s[i]-'0';
            if (!ch[u][c]){
                ch[u][c]=++num;
            }
            u=ch[u][c];
            if (ed[u]){
                flag=1;
            }
        }
        ed[u]=1;
    }
    void init(){
        memset(ch, 0, sizeof(ch));
        memset(ed, 0, sizeof(ed));
        num=1, flag=0;
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    string s;
    int cnt=0;
    while (cin >> s){
        if (s=="9"){
            if (tree.flag){
                printf("Set %d is not immediately decodable\n", ++cnt);
            }else{
                printf("Set %d is immediately decodable\n", ++cnt);
            }
            tree.init();
        }else{
            tree.add(s);
        }
    }

    return 0;
}