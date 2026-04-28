#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

int n;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    string s;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        if ('a' <= s[0] && s[0] <= 'z') s[0] -= 32;
        int siz = s.size();
        for (int j = 1; j < siz; j++) {
            if ('A' <= s[j] && s[j] <= 'Z') s[j] += 32;
        }
        printf("%s\n", s.c_str());
    }

    return 0;
}