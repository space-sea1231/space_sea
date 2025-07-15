#include <bits/stdc++.h>
using namespace std;
int n;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        int x, y;
        cin >> x >> y;
        if (x==y&&x==1){
            printf("1\n");
            continue;
        }
        printf("%d\n", y-x);
    }

    return 0;
}