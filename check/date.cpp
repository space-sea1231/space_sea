#include <bits/stdc++.h>
using namespace std;
int random_date(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
int main(){
    freopen("date.in", "w", stdout);
    srand(time(NULL));//随机种子
    int n=random_date(1, 10);
    printf("%d\n", n);
    for (int i=2; i<=n; i++){
        int k=random_date(1, i-1);
        int p=random_date(0, 1);
        printf("%d %d\n", k, p);
    }
    int m=random_date(1, n);
    for (int i=1; i<=m; i++){
        int x=random_date(1, n);
        printf("%d\n", x);
    }

    return 0;
}