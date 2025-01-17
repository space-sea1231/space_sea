#include <bits/stdc++.h>
using namespace std;
int Random_Data(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
int main(){
    freopen("date.in", "w", stdout);
    srand(time(NULL));//随机种子
    int n=Random_Data(1, 10);
    printf("%d\n", n);
    for (int i=1; i<=n; i++){
        int opt=Random_Data(1, 3);
        if
        printf("%d ", opt);
        if (opt==1){
            int x=Random_Data(1, 100);
            printf("%d", x);
        }
        printf("\n");
    }

    return 0;
}