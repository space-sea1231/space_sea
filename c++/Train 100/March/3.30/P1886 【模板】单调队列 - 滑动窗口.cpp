#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e6 + 10;
int n, m;
int a[N];
int top, back;
int stk[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        while (top > back && stk[back] <= i - m) back++;
        while (top > back && a[stk[top - 1]] > a[i]) top--;
        stk[top++] = i;
        if (i >= m) printf("%d ", a[stk[back]]);
    }
    printf("\n");
    top = back = 0;
    for (int i = 1; i <= n; i++) {
        while (top > back && stk[back] <= i - m) back++;
        while (top > back && a[stk[top - 1]] < a[i]) top--;
        stk[top++] = i;
        if (i >= m) printf("%d ", a[stk[back]]);
    }
    return 0;
}