#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

string s;
vector<int> a, b;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> s;
    int siz = s.size();
    bool flag = true;
    for (int i = siz - 1; ~i; i--) {
        if (s[i] == 'Z') {
            if (!flag) {
                printf("-1\n");
                return 0;
            }
        } else flag = false;
    }
    for (int i = 0; i < siz; i++) {
        if (s[i] == 'Z') {
            a.emplace_back(0);
            b.emplace_back(0);
        }
        if (s[i] == 'X') {
            a.emplace_back(1);
            b.emplace_back(0);
        }
        if (s[i] == 'Y') {
            a.emplace_back(0);
            b.emplace_back(1);
        }
    }
    for (int x:a) printf("%d", x);
    printf("\n");
    for (int x:b) printf("%d", x);
    printf("\n");
    return 0;
}