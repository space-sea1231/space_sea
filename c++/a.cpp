#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;

int n;
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
struct Node {
    int x, y;
    int pos;
}; 

Node node[N];

int Change(char c) {
    if (c == 'N') return 0;
    if (c == 'W') return 1;
    if (c == 'E') return 2;
    if (c == 'S') return 3;
    return -1;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> node[i].x >> node[i].y >> c;
        node[i].pos = Change(c);

    }
    return 0;
}