#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+10;
int n, t;
int a[N];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> t;
    for (int i=1; i<=n; i++){
        char c;
        cin >> c;
        a[i]=c-'0';
    }
    int x=1;
    while (x<n){
        x<<=1;
    }
    t=t%x;
    for (int i=1; i<=t; i++){
        for (int j=n; j>=2; j--){
            a[j]=a[j]^a[j-1];
        }
    }
    for (int i=1; i<=n; i++){
        printf("%d", a[i]);
    }

    return 0;
}