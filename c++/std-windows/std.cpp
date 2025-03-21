#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
const int Z=2;
struct Trie_Tree{
    int num=1;
    bool flag=0;
    bool ch[N][Z];
    void add(string s){
        int u=1, len=s.size();
        for (int i=0; i<len; i++){
            int c=s[i]-'0';
            if (!ch[u][c]){
                ch[u][c]=++num;
            }
            u=ch[u][c];
        }
    }
    void find(string s){
        int u=1, len=s.size();
        for (int i=0; i<len; i++){
            int c=s[i]-'0';
            if (!ch[u][c]){
                return ;
            }
            u=ch[u][c];
        }
        flag=1;
    }
    void init(){
        memset(ch, 0, sizeof(ch));
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
                printf("Set %d is immediately decodable\n", ++cnt);
            }else{
                printf("Set %d is not immediately decodable\n", ++cnt);
            }
            tree.init();
        }else{
            tree.add(s);
        }
    }

    return 0;
}
/*
我只会写矩阵面积并
不会写矩阵周长
我都不会扫描线

废了
192行
我都只写了120行
封装了亿下
我先继续颓loj去了，你等会搜一下linux能不能发弹窗，有事的话发弹窗告诉我


*/