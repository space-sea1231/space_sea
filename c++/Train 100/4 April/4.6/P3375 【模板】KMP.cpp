#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

string s1, s2;
int nxt[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> s1 >> s2;
    int len1 = s1.size(), len2 = s2.size();
    s1 = " " + s1, s2 = " " + s2;
    for (int i = 2, j = 0; i <= len2; i++) {
        while (j && s2[i] != s2[j + 1]) j = nxt[j];
        if (s2[i] == s2[j + 1]) j++;
        nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= len1; i++) {
        while (j && (j == len2 || s1[i] != s2[j + 1])) j = nxt[j];
        if (s1[i] == s2[j + 1]) j++;
        if (j == len2) printf("%d\n", i - len2 + 1);
    }
    for (int i = 1; i <= len2; i++) printf("%d ", nxt[i]);
    printf("\n");
    return 0;
}