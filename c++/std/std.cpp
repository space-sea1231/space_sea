#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;
typedef unsigned int uint;

const int N = 2e7 + 10;

int n;
uint seed;
uint a[N];
bool vis[N];

uint getnext(){
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> seed;
    for (int i = 1; i <= n; i++) a[i] = getnext();
    vis[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            for (int j = i, k = 1; j <= n; j += i, k++) {
                a[j] += a[k];
                vis[j] = 1;
            }
        }
    }
    uint ans = 0;
    for (int i = 1; i <= n; i++) ans ^= a[i];
    printf("%u\n", ans); 
    return 0;
}