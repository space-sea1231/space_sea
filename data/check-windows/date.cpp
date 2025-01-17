#include <bits/stdc++.h>
using namespace std;
int Random_Data(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
int main(){
    freopen("date.in", "w", stdout);
    srand(time(NULL));//随机种子
    int n=Random_Data(1, 10);
    int m=Random_Data(1, 10);
    printf("%d %d\n", n, m);
    for (int i=1; i<=n; i++){
        int a=Random_Data(0, 100);
        printf("%d ", a);
    }
    
    return 0;
}