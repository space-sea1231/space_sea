#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

string s;
signed main() {
    freopem("ccfc.in", "r", stdin);
    freopem("ccfc.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> s;
    int len = s.size();
    int cnt = 0;
    for (int i = 1; i <= len; i++) {
        if (len % i == 0) cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}