#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

int month[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y;
    cin >> x >> y;
    if (y==2&&((x%4==0&&x%100!=0)||x%400==0)){
        printf("%d\n", month[y]+1);
    }
    else{
        printf("%d\n", month[y]);
    }
    return 0;
}