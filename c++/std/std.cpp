#include <iostream>
#include <stdio.h>
#include <cmath>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 5e4 + 10;
const int M = 3e2 + 10;

int n, m;
int tot;
int a[N];
int belong[N];
int L[M], R[M];
int bucket[M][N];
int ans[M][M];

int Gcd(int a, int b) {
    while (b ^= a ^= b ^= a %= b);
    return a;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    int size = sqrt(n);
    for (int i = 1; i <= n / size; i++) {
        for (int j = (i - 1) * size + 1; j <= i * size; j++) {
            belong[j] = i;
        }
        tot++;
        L[tot] = (tot - 1) * size + 1;
        R[tot] = tot * size;
    }
    if (R[tot] != n) {
        tot++;
        L[tot] = R[tot - 1] + 1;
        R[tot] = n;
    }
    for (int i = 1; i <= tot; i++) {
        for (int j = 1; j <= n; j++) bucket[i][j] = bucket[i - 1][j];
        for (int j = L[i]; j <= R[i]; j++) bucket[i][a[j]]++;
    }
    for (int i = 1; i <= tot; i++) {
        for (int j = i; j <= tot; j++) {
            ans[i][j] = ;
        }
    }
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;

        int d = Gcd(ans[])
        printf("%d\n", )
    }
    return 0;
}
