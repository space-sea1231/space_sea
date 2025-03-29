#include <bits/stdc++.h>
using namespace std;
int t, n, m;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        bool flag=1;
        cin >> n >> m;
        for (int i=2; i*i<=n; i++){
            if (n%i==0){
                if (i<=m){
                    flag=0;
                    break;
                }
                if (i*i!=n){
                    if (n/i<=m){
                        flag=0;
                        break;
                    }
                }
            }
        }
        if (flag&&(m<n||n==1)){
            printf("YES\n");
        }else{
            printf("NO\n");
        }
    }

    return 0;
}