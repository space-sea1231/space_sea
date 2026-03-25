#include <bits/stdc++.h>
using namespace std;
int n, ans;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        int a;
        cin >> a;
        ans^=a;
    }
    printf("%d\n", ans);

    return 0;
}