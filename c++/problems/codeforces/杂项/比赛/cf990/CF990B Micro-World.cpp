#include <iostream>
#include <stdio.h>
#include <algorithm>
// #define __Debug

using namespace std;
typedef long long ll;

const int N=2e5+10;

int n, k;
int ans;
int a[N];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    // a[1]=1, a[2]=2, a[3]=3;
    // int idx=upper_bound(a+1, a+3+1, 2)-a;
    // printf("%d\n", idx);
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    sort(a+1, a+n+1);
    for (int i=1; i<=n; i++){
        int idx=lower_bound(a+i+1, a+n+1, a[i]+k)-a;
        if ((a[idx]>a[i]&&a[idx]==a[i]+k)||(a[idx-1]>a[i]&&a[idx-1]<=a[i]+k)){
            ans++;
        }
    }
    printf("%d\n", n-ans);

    return 0;
}