#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 4e4 + 10;

int n;
int phi[N], prm[N];
bool vis[N];

void Phi() {
    phi[1] = 1;
    int top = 0;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            prm[++top] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= top && prm[j] * i <= n; j++) {
            vis[prm[j] * i] = true;
            if (i % prm[j]) phi[prm[j] * i] = phi[i] * (prm[j] - 1);
            else {
                phi[prm[j] * i] = phi[i] * prm[j];
                break;
            }
        }
    }
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    if (n-- == 1) {
        printf("0\n");
        return 0;
    }
    Phi();
    int ans = 0;
    // for (int i = 1; i <= n; i++) printf("%d\n", phi[i]);
    for (int i = 2; i <= n; i++) ans += (phi[i] << 1);
    printf("%d\n", ans + 3);
    return 0;
}