#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e7 + 10;

int n;
char c[N << 1];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> (c + 1);
    for (int i = 1; i <= n; i++) c[i + n] = c[i];
    int i = 1, j = 2, k;
    while (i <= n && j <= n) {
        for (k = 0; k < n && c[i + k] == c[j + k]; k++);
        if (k == n) break;
        if (c[i + k] > c[j + k]) {
            i += k + 1;
            if (i == j) i++;
        }
        else if (c[i + k] < c[j + k]) {
            j += k + 1;
            if (i == j) j++;
        }
    }
    int start = min(i, j);
    for (int k = start; k < start + n; k++) printf("%c", c[k]);
    return 0;
}