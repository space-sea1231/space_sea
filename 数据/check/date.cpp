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
    for (int i=1; i<=n; i++){
        int opt=random_date(1, 3);
        if
        printf("%d ", opt);
        if (opt==1){
            int x=random_date(1, 100);
            printf("%d", x);
        }
        printf("\n");
    }

    return 0;
}