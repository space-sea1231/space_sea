#include <bits/stdc++.h>
using namespace std;
int random_date(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
int main(){
    freopen("date.in", "w", stdout);
    srand(time(NULL));//随机种子
    int x=random_date(1, 5000);
    int y=random_date(1, 5000);
    printf("%d %d", x, y);

    return 0;
}