#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 110;

int n;
string s;
int m[N], f[N][N];

bool Check(int l, int r, int len) {
    for (int i = l; i <= r; i++) {
        if (s[i] != s[(i - l) % len + l]) return false;
    }
    return true;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> s;
    n = s.size();
    s = ' ' + s; // 变为 1-indexed
    
    // 预处理数字的位数
    for (int i = 1; i <= 9; i++) m[i] = 1;
    for (int i = 10; i <= 99; i++) m[i] = 2;
    m[100] = 3;
    
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++) f[i][i] = 1;
    
    // 区间 DP
    for (int l = 2; l <= n; l++) {
        for (int i = 1, j = i + l - 1; j <= n; i++, j++) {
            // 1. 枚举断点合并
            for (int k = i; k < j; k++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
            }
            
            // 2. 枚举折叠长度
            for (int k = i; k < j; k++) {
                int len = k - i + 1;
                if (l % len != 0) continue;
                if (Check(i, j, len)) {
                    // 折叠后的代价 = 循环节内部代价 + 括号代价(2) + 数字代价
                    f[i][j] = min(f[i][j], f[i][k] + 2 + m[l / len]);
                }
            }
        }
    }
    
    printf("%d\n", f[1][n]);
    return 0;
}