#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 20;

string s;
int cnt[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> s;
    int len = s.size();
    for (int i = 0; i < len; i++) if (isdigit(s[i])) cnt[s[i] - '0']++;
    bool flag = false;
    for (int i = 9; i >= 1; i--) {
        for (int j = 1; j <= cnt[i]; j++) {
            printf("%d", i);
            flag = true;
        }
    }
    if (flag) for (int i = 1; i <= cnt[0]; i++) printf("0");
    else printf("0");
    return 0;
}