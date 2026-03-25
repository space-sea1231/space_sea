#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

int a, b, x, y;

void Exgcd(int a, int b, int &x, int &y){
    if (b==0) {x=1, y=0; return;}
    Exgcd(b, a%b, x, y);
    int z=x; x=y; y=z-y*(a/b);
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;
    Exgcd(a, b, x, y);
    printf("%d\n", (x%b+b)%b);
    
    return 0;
}