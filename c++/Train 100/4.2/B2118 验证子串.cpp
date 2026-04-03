#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

string s1, s2;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> s1 >> s2;
    if (s1.size() <= s2.size()) swap(s1, s2);
    int len1 = s1.size();
    int len2 = s2.size();
    for (int i = 0; i < len1 - len2 + 1; i++) {
        bool flag = true;
        for (int j = 0; j < len2; j++) {
            if (s1[j + i] != s2[j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            printf("%s is substring of %s\n", s2.c_str(), s1.c_str());
            return 0;
        }
    }
    printf("No substring\n");
    return 0;
}