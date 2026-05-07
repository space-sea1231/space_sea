#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

int a, b;

void Exgcd(int a, int b, int &x, int &y){
    if (b==0) {
        x=1, y=0;
        return ;
    }
    Exgcd(b, a%b, x, y);
    int z=x; x=y; y=z-y*(a/b);
}

signed main(){
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    cin >> a >> b;
    int x, y;
    Exgcd(a, b, x, y);
    printf("%d\n", (x%b+b)%b);
    return 0;
}