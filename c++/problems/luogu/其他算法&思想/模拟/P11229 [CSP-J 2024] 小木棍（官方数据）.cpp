#include <bits/stdc++.h>
using namespace std;
const int N=15;
int a[N]={0, -1, 1, 7, 4, 2, 6, 8, 10, 18, 22, 20, 28, 68, 88};
int b[N]={88, 108, 188, 200, 208, 288, 688};
int t, n;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        cin >> n;
        if (n<=14){
            printf("%d\n", a[n]);
        }else{
            int cnt=n/7-2;
            printf("%d", b[n%7]);
            for (int i=1; i<=cnt; i++){
                printf("8");
            }
            printf("\n");
        }
    }
    return 0;
}