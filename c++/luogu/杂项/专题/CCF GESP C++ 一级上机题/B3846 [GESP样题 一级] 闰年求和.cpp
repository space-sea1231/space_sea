#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y;
    cin >> x >> y;
    int sum=0;
    for (int i=x+1; i<y; i++){
        if ((i%4==0&&i%100!=0)||i%400==0){
            sum+=i;
        }
    }
    printf("%d\n", sum);

    return 0;
}