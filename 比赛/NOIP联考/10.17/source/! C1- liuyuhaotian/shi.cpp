#include <bits/stdc++.h>
using namespace std;

int t;
string s;

int main() {
    freopen("shi.in", "r", stdin);
    freopen("shi.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--) {
        cin >> s;
        if (s == "001" || s == "100" || s == "010") cout << "1 0\n";
        else {
            int flg = 1;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '0') flg = 0;
            }
            cout << s.size() - 1 + flg << " 0" << '\n';
        }
    }
	return 0;
}
/*
000 101
001 100
100 001
101 000

010 010
011 010
110 010
111 010
*/