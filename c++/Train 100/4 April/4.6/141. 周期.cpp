#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n;
char c[N];
int nxt[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    int T = 0;
    while (cin >> n, n) {
        printf("Test case #%d\n", ++T);
        cin >> c + 1;
        int len = strlen(c + 1);
        for (int i = 2, j = 0; i <= len; i++) {
            while (j && c[i] != c[j + 1]) j = nxt[j];
            if (c[i] == c[j + 1]) j++;
            nxt[i] = j;
        }
        for (int i = 1; i <= len; i++) {
            if (i % (i - nxt[i]) == 0 && i / (i - nxt[i]) > 1) printf("%d %d\n", i, i / (i - nxt[i]));
        }
        printf("\n");
    }
    return 0;
}