#include <bits/stdc++.h>
using namespace std;
#define p push_back

bool a[3000010];
vector<int> ans;
int n;
int xx, yy;

bool nand(bool x, bool y) {return (!x) & (!y);}

void work(int l, int r) {
    if (r - l < 2) return ;
    if (r - l == 2) {
        ans.p(l + 1);
        return ;
    }
    int x = l, y = l + 1;
    while (y < r) {
        ans.p(y);
        y += 2;
    }
    work(l + 1, y - 2);
}

void move(int id) {
    if (n & 1) {
        if (id & 1) {
            if (id > n / 2) {
                while (id != n) {
                    ans.p(id + 1);
                    id += 2;
                }
                yy = n - 1;
            }
            else {
                while (id != 1) {
                    ans.p(id - 1);
                    id -= 2;
                }
                xx = 2;
            }
        }
        else {
            if (id > n / 2) {
                while (id != n - 1) {
                    ans.p(id + 1);
                    id += 2;
                }
                yy = n - 2;
            }
            else {
                while (id != 2) {
                    ans.p(id - 1);
                    id -= 2;
                }
                xx = 3;
            }
        }
    }
    else {
        if (id & 1) {
            while (id != 1) {
                ans.p(id - 1);
                id -= 2;
            }
            xx = 2;
        }
        else {
            while (id != n) {
                ans.p(id + 1);
                id += 2;
            }
            yy = n - 1;
        }
    }
}

int main() {
    freopen("shi.in", "r", stdin);
    freopen("shi.out", "w", stdout);
    int T;
    cin >> T;
    while (T --> 0) {
        ans.clear();
        string s;
        cin >> s;
        n = s.size();
        s = " " + s;
        int flag = 0;
        for (int i = 1; i <= n; i++) {
            a[i] = s[i] - '0';
            if (a[i] != 0) flag++;
        }
        if (!flag) {
            work(1, n);
            int t = ans.size();
            cout << 0 << " " << t << "\n";
            for (int i = 0; i < t; i++) {
                cout << ans[i] << " ";
            }
            cout << "\n";
        }
        else if (flag == 1) {
            int id = 0;
            xx = 1, yy = n;
            for (int i = 1; i <= n; i++) {
                if (a[i]) {
                    id = i;
                    break;
                }
            }
            move(id);
            work(xx, yy);
            int t = ans.size();
            cout << 0 << " " << t << "\n";
            for (int i = 0; i < t; i++) {
                cout << ans[i] << " ";
            }
            cout << "\n";
        }
        else {
            cout << n << " " << 0 << "\n";
        }
    }
    return 0;
}
//100010110011