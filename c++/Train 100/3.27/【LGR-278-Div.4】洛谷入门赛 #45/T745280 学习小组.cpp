#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
int n;
int a[N << 1];
int ans[N << 1];
int vis[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= (n << 1); i++) {
        cin >> a[i];
        if (!vis[a[i]]) vis[a[i]] = i;
        else ans[i] = vis[a[i]], ans[vis[a[i]]] = i;
    }
    for (int i = 1; i <= (n << 1); i++) printf("%d ", ans[i]);
    return 0;
}