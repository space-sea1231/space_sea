#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;

int n;
int a[N];
int ans[N];
string s;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> s; s = " " + s;
    sort(a + 1, a + n + 1);
    int l = 1, r = n;
    for (int i = n; i; i--) {
        if (s[i] == s[i - 1]) ans[i] = l++;
        else ans[i] = r--;
                 
    }
    bool flag;
    if (s[n] == 'L') flag = (n % 2 == 1);
    else flag = (n % 2 == 0);

    for (int i = 1; i <= n; i++) {
        printf("%d ", a[ans[i]]);
        if (flag) printf("%c\n", ans[i] % 2 == 1 ? 'L' : 'R');
        else printf("%c\n", ans[i] % 2 == 0 ? 'L' : 'R');
    }
    return 0;
}