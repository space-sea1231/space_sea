#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
int t, n;
int a[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        bool flag=1;
        cin >> n;
        for (int i=1; i<=n; i++){
            cin >> a[i];
        }
        for (int i=0; i<=n; i++){
            int cnt=i;
            for (int j=1; j<=n; j++){
                if (a[j]>i){
                    cnt--;
                }
            }
            if (cnt==0){
                printf("%d\n", i);
                flag=0;
                break;
            }
        }
        if (flag){
            printf("-1\n");
        }
    }

    return 0;
}