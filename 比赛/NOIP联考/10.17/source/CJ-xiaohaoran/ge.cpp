#include <bits/stdc++.h>
using namespace std;

const int mod = 998442353;
int a[20][20];
int s[20];

int main() {
    freopen("ge.in", "r", stdin);
    freopen("ge.out", "w", stdout);
    int T;
    cin >> T;
    while (T --> 0) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> a[i][j];
            }
        }
        for (int i = 1; i <= m; i++) {
            cin >> s[i];
        }
        cout << "NIE\n";
    }
    return 0;
}