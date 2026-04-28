#include <iostream>
#include <stdio.h>
#include <cmath>
#define __Debug
#define int long long

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
int n, m;
int top, back;
int sum[N];
int stk[N];
double ans;

double Cal(int x, int y) {
    return ((double)sum[y] - sum[x]) / (y - x);
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        sum[i] = sum[i - 1] + a;
    }
    for (int i = m; i <= n; i++) {
        while (top - back >= 2 && Cal(i - m, stk[top - 1]) < Cal(i - m, stk[top - 2])) top--;
        stk[top++] = i - m;
        while (top - back >= 2 && Cal(i, stk[back]) < Cal(i, stk[back + 1])) back++;
        ans = max(ans, Cal(i, stk[back]));
    }
    printf("%lld\n", (ll)floor(ans * 1000));

    return 0;
}