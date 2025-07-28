#include <bits/stdc++.h>
#define int long long
using namespace std;
int a, b, x, y;
void exgcd(int a, int b){
    if (b==0){
        x=1, y=0;
        return ;
    }
    exgcd(b, a%b);
    int z=x;
    x=y;
    y=z-a/b*y;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> a >> b;
    exgcd(a, b);
    x=(x%b+b)%b;
    printf("%lld", x);
    
    return 0;
}