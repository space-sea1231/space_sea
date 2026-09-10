#include <bits/stdc++.h>

using namespace std;

void solveTestcase();

typedef int i32;
typedef long long i64;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    i32 T; cin >> T;while (T -- ) {
        solveTestcase();
    }
    return 0;
}

void solveTestcase() {
    i32 n;
    i64 m;
    cin >> n >> m;

    string s;
    cin >> s;

    i32 st = -1, la = -1;

    for (i32 i = 0; i < (i32)s.size(); i++) {
        if (s[i] == '?') {
            if (!~st) {
                st = i;
            }
            la = i;
        }
    }

    if (st == -1) {
        cout << s << "\n";
        return;
    }

    i32 half = n / 2;
    i32 v = 0;

    for (char c : s) {
        if (c == '(') {
            v++;
        }
    }

    i32 len = la - st + 1;
    i32 lft = half - v;
    i32 rgt = len - lft;

    i64 nv = 0, re = 0;

    for (i32 i = 0; i < st; i++) {
        if (s[i] == '(') {
            nv++;
        } else {
            re += nv;
            nv--;
        }
    }

    i32 H = nv;
    i32 env = H + lft - rgt;

    nv = env;

    for (i32 i = la + 1; i < n; i++) {
        if (s[i] == '(') {
            nv++;
        } else {
            re += nv;
            nv--;
        }
    }

    i64 blockValue = m - re;

	assert(blockValue >= 0);

    i64 target =
        blockValue
        - 1LL * rgt * H
        + 1LL * rgt * (rgt - 1) / 2;

    vector<i32> a(rgt + 1);

    i64 minimum = 0;

    for (i32 i = 1; i <= rgt; i++) {
        a[i] = max(0, i - H);
        minimum += a[i];
    }

    i64 remain = target - minimum;

    for (i32 i = rgt; i >= 1; i--) {
        i32 upper;

        if (i == rgt) {
            upper = lft;
        } else {
            upper = a[i + 1];
        }

        i64 add = min<i64>(remain, upper - a[i]);

        a[i] += add;
        remain -= add;
    }

    string mid;
    mid.reserve(len);

    i32 usedLeft = 0;

    for (i32 i = 1; i <= rgt; i++) {
        while (usedLeft < a[i]) {
            mid.push_back('(');
            usedLeft++;
        }

        mid.push_back(')');
    }

    while (usedLeft < lft) {
        mid.push_back('(');
        usedLeft++;
    }

    for (i32 i = 0; i < len; i++) {
        s[st + i] = mid[i];
    }

    cout << s << "\n";
}