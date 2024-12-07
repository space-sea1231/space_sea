#include <bits/stdc++.h>
using namespace std;
int random_date(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
int main(){
    freopen("date.in", "w", stdout);
    srand(time(NULL));//随机种子
    int k=random_date(1, 10);
    int n=10;
    int m=random_date(1, 10);
    printf("%d %d %d\n", k, n, m);
    for (int i=1; i<=k; i++){
        int a=random_date(1, 10);
        printf("%d\n", a);
    }
    for (int i=1; i<=m; i++){
        int u=random_date(1, 10);
        int v=random_date(1, 10);
        while (u==v){
            u=random_date(1, 10);
            v=random_date(1, 10);
        }
        printf("%d %d\n", u, v);
    }

    return 0;
}