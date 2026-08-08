#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int t;

bool Dfs(int a, int b) {
    if (b == 0) return false;
    int x = b, y = a - a / b * b;
    if (!Dfs(x, y)) return true; 
    else if (2 * b < a) return true;
    else return false;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        if (a < b) swap(a, b);
        if (Dfs(a, b)) printf("Stan wins\n");
        else printf("Ollie wins\n");
    }
    return 0;
}