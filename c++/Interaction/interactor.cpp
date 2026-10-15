#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerInteraction(argc, argv);
    int n    = inf.readInt();
    int maxk = inf.readInt();
    int x    = inf.readInt();   // 毒水
    int y    = inf.readInt();   // 变异鼠选择参数

    cout << n << " " << maxk << endl;   // endl 会刷新

    vector<vector<int>> mice;
    while (true) {
        int op = ouf.readInt(1, 2, "op");
        if (op == 2) break;
        if ((int)mice.size() >= maxk)
            quitf(_wa, "too many mice, maxk = %d", maxk);
        int m = ouf.readInt(0, n, "m");
        vector<int> b(m);
        for (int &v : b) v = ouf.readInt(1, n, "B");
        mice.push_back(b);
    }

    int k = mice.size();
    int mut = k ? (y - 1) % k : -1;
    for (int i = 0; i < k; i++) {
        bool has = find(mice[i].begin(), mice[i].end(), x) != mice[i].end();
        bool dead = (i == mut) ? !has : has;   // 变异鼠相反
        cout << (dead ? 0 : 1) << (i + 1 < k ? ' ' : '\n');
    }
    if (k == 0) cout << "\n";
    cout.flush();

    int ans = ouf.readInt(1, n, "answer");
    if (ans != x) quitf(_wa, "wrong answer: expected %d, found %d", x, ans);
    quitf(_ok, "n=%d, used %d mice", n, k);
}