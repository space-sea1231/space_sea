#include <bits/stdc++.h>
using namespace std;
int Random(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
int main(){
    freopen("data.in", "w", stdout);
    srand(time(NULL));//随机种子
    int n=Random(1, 10);
    int m=Random(1, 10);
    printf("%d %d\n", n, m);
    for (int i=1; i<=n; i++){
        int a=Random(1, 10);
        printf("%d ", a);
    }
    printf("\n");
    for (int i=1; i<=m; i++){
        int l=Random(1, n);
        int r=Random(l, n);
        printf("%d %d\n", l, r);
    }

    return 0;
}