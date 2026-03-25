#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int a[N], ans[N];
int n, num;
void build(int root){
    if(root>n){
        return;
    }
    build(root<<1);
    ans[root]=a[++num];
    build(root<<1|1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    sort(a+1, a+n+1);
    build(1);
    for(int i=1; i<=n; i++){
        printf("%d ", ans[i]);
    }

    return 0;
}