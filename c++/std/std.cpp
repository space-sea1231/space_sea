#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e2 + 10;
const int M = 11;

int n, m;
int a[N];
int num;
int sit[1 << M], sta[1 << M];

void Dfs(int x, int cnt, int cur) {
    if (cur >= n) {
        sit[++num] = x;
        sta[num] = cnt;
        return;
    }
    Dfs(x, cnt, cur + 1);
    Dfs(x + (1 << cur), cnt + 1, cur + 3);
    return;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            a[i] += c == 'H' ? (1 << (j - 1)) : 0;
        }
    }
    Dfs(0, 0, 0);
    
    return 0;
}