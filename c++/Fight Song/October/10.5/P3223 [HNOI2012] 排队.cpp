#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int n, m;
int lena, lenb;
vector<int> a(N), b(N);

void Mula(int x) {
    int tmp = 0;
    for (int i = 1; i <= lena; i++) {
        a[i] = a[i] * x + tmp;
        tmp = a[i] / 10;
        a[i] %= 10;
    }
    while (tmp) {
        a[++lena] = tmp % 10;
        tmp /= 10;
    }
}
void Mulb(int x) {
    int tmp = 0;
    for (int i = 1; i <= lenb; i++) {
        b[i] = b[i] * x + tmp;
        tmp = b[i] / 10;
        b[i] %= 10;
    }
    while (tmp) {
        b[++lenb] = tmp % 10;
        tmp /= 10;
    }
}
void Sub() {
    for (int i = 1; i <= lena; i++) {
        a[i] -= b[i];
        if (a[i] < 0) {
            a[i] += 10;
            a[i + 1]--;
        }
    }
    while (lena > 1 && !a[lena]) lena--;
}
void Out() {
    for (int i = lena; i; i--) printf("%d", a[i]);
    printf("\n");
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m; n += 2;
    a[1] = 1, lena = 1;
    b[1] = 1, lenb = 1;
    if (m > n + 1) {printf("0\n"); return 0;}

    for (int i = n - m + 2; i <= n + 1; i++) Mula(i);
    for (int i = 1; i <= n; i++) Mula(i);

    for (int i = 1; i <= 2; i++) Mulb(i);
    for (int i = 1; i <= n - 1; i++) Mulb(i);
    for (int i = n - m + 1; i <= n; i++) Mulb(i);

    Sub(); Out();
    return 0;
}