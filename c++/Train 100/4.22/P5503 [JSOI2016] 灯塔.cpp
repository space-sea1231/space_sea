#include <iostream>
#include <stdio.h>
#include <cmath>
#define __Debug
using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n;
int a[N];
double ans[N];

double Calc(int x, int y) {
    return a[x] - a[y] + sqrt(y - x);
}
void Solve(int l, int r, int L, int R) {
    if (l > r) return;
    int mid = (l + r) >> 1, p = L;
    for (int i = L + 1; i <= min(mid, R); i++) if (Calc(p, mid) < Calc(i, mid)) p = i;
    ans[mid] = max(ans[mid], Calc(p, mid));
    Solve(l, mid - 1, L, p);
    Solve(mid + 1, r, p, R);
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    Solve(1, n, 1, n);
    for (int i = 1; i * 2 <= n; i++) swap(a[i], a[n - i + 1]), swap(ans[i], ans[n - i + 1]);
    Solve(1, n, 1, n);
    for (int i = 1; i * 2 <= n; i++) swap(a[i], a[n - i + 1]), swap(ans[i], ans[n - i + 1]);
    for (int i = 1; i <= n; i++) printf("%.0lf\n", ceil(ans[i]));
    return 0;
}