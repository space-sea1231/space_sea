#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("mex.in", "r", stdin);
    freopen("mex.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string a;
    cin >> n >> a;

    if (a.find('0') == string::npos) {
        cout << "0\n";
        return 0;
    }

    vector<int> f(n + 1);

    string choose(n + 1, '0');

    int first[10];
    fill(first, first + 10, -1);

    for (int i = n; i >= 0; --i) {
        if (i < n) {
            first[a[i] - '0'] = i;
        }

        f[i] = n + 2;

        for (int d = 0; d <= 9; ++d) {
            int p = first[d];
            int len = (p == -1 ? 1 : 1 + f[p + 1]);

            if (len < f[i]) {
                f[i] = len;
                choose[i] = char('0' + d);
            }
        }
    }

    int bestLen = n + 2;
    char digit = '1';

    for (int d = 1; d <= 9; ++d) {
        int p = first[d];
        int len = (p == -1 ? 1 : 1 + f[p + 1]);

        if (len < bestLen) {
            bestLen = len;
            digit = char('0' + d);
        }
    }

    string answer;
    int pos = 0;

    while (true) {
        answer.push_back(digit);
        while (pos < n && a[pos] != digit) {
            ++pos;
        }
        if (pos == n) {
            break;
        }
        ++pos;
        digit = choose[pos];
    }

    cout << answer << '\n';
    return 0;
}