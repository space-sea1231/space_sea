#include <bits/stdc++.h>
using namespace std;
int n;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++){
        int a, b;
        cin >> a >> b;
        printf("%d\n", a+b);
    }

    return 0;
}