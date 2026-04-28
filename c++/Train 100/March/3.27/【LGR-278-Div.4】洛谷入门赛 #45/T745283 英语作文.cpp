#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

string c;

bool Check(char c) {
    if ('A' <= c && c <= 'Z') return true;
    return false;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> c;
    if (!Check(c[0])) c[0] = c[0] - 32;
    int siz = c.size();
    for (int i = 1; i < siz; i++) {
        if (Check(c[i]) && c[i - 1] != '.') c.insert(i, "."), i++, siz++;
        if (c[i] == '.' && 'a' <= c[i + 1] && c[i + 1] <= 'z' && i != siz - 1) c[i + 1] = c[i + 1] - 32;
    }
    if (c[siz - 1] != '.') c = c + ".";
    cout << c;
    return 0;
}