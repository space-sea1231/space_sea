#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;

int t, s;
int nxt[N];

bool KMP(string a, string b) {
    int lena = a.size(), lenb = b.size();
    if (lena < lenb) return false;
    for (int i = 1, j = 0; i < lenb; i++) {
        while (j && b[i] != b[j]) j = nxt[j - 1];
        if (b[i] == b[j]) j++;
        nxt[i] = j;
    }
    for (int i = 0, j = 0; i < lena; i++) {
        while (j && (j == lenb && a[i] != b[j])) j = nxt[j - 1];
        if (a[i] == b[j]) j++;
        if (j == lenb) return true;
    }
    return false;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t >> s;
    string c;
    int sum = s;
    for (int i = 1; i <= t; i++) {
        cin >> c;
        if (KMP(c, "kirai")) sum = min(sum, 0);
        else if (KMP(c, "daishuki")) sum += 2;
        else if (KMP(c, "shuki")) sum++;
        else sum--;
    }
    if (sum > 0) printf("%d\n", sum - s);
    else printf("shuki\n");
    return 0;
}