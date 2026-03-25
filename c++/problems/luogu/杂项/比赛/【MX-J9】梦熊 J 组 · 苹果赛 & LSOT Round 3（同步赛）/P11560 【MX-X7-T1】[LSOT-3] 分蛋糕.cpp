#include <bits/stdc++.h>
using namespace std;
int a, b, cnt;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> a >> b;
    while (abs(a-b)>abs((a<<1)-b)){
        a<<=1;
        cnt++;
    }
    cnt+=abs(a-b);
    printf("%d\n", cnt);
    
    return 0;
}