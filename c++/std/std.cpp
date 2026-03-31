#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 5e4 + 10;
int n, L;
int top = 1, back = 1;
int a[N], sum[N];
int que[N];
ll f[N];

ll X(int src) {
    return sum[src];
}
ll Y(int src) {
    return f[src] + (sum[src] + L) * (sum[src] + L);
}
double Cal(int a, int b) {
    return (double)(Y(b) - Y(a)) / (X(b) - X(a));
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> L;
    que[top++] = 0, L++;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i] + 1;
    }
    for (int i = 1; i <= n; i++) {
        while (back + 1 < top && Cal(que[top - 2], que[top - 1]) >= Cal(que[top - 2], i)) top--;
        que[top++] = i;
        while (back + 1 < top && Cal(que[back], que[back + 1]) <= (sum[i] << 1)) back++;
        f[i] = f[que[back]] + (sum[i] - sum[que[back]] - L) * (sum[i] - sum[que[back]] - L);
    }
    printf("%lld\n", f[n]);
    return 0;
}
/*

*/