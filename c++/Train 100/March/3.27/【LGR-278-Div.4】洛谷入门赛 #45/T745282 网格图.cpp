#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e3 + 10;
int n, m;
char c[N][N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n * 2 + 1; i++) {
        for (int j = 1; j <= m * 2 + 1; j++) {
            if ((i & 1) && (j & 1)) printf("+");
            if ((i & 1) && !(j & 1)) printf("-");
            if (!(i & 1) && (j & 1)) printf("|");
            if (!(i & 1) && !(j & 1)) printf(" ");
        }
        printf("\n");
    } 
    return 0;
}