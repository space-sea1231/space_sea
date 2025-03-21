#include <bits/stdc++.h>
using namespace std;
int Random(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
int main(){
    freopen("data.in", "w", stdout);
    srand(time(NULL));//随机种子
    int n=Random(1, 5);
    int m=Random(1, 10);
    printf("%d %d\n", n, m);
    for (int i=1; i<=m; i++){
        int u=Random(1, n);
        int v=Random(1, n);
        while (u==v){
            v=Random(1, n);
        }
        int w=Random(1, 10);
        printf("%d %d %d\n", u, v, w);
    }
    int q=Random(1, 10);
    printf("%d\n", q);
    for (int i=1; i<=q; i++){
        int u=Random(1, n);
        int v=Random(1, n);
        while (u==v){
            v=Random(1, n);
        }
        printf("%d %d\n", u, v);
    }

    return 0;
}