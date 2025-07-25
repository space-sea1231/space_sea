#include <bits/stdc++.h>
using namespace std;
int n;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    int max_1=0, max_2=0;
    for (int i=1; i<=n; i++){
        int a;
        cin >> a;
        if (a>max_1){
            max_2=max_1;
            max_1=a;
        }else if (a>max_2){
            max_2=a;
        }
        if (i>=2){
            printf("%d ", max_2);
        }
    }
    return 0;
}