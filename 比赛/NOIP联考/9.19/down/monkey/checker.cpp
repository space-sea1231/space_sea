# include <bits/stdc++.h>
# include "testlib.h"
using namespace std;
const int M = 3005;
int Aex, Oex, n, m, U[M], V[M], x, y;
vector<array<int, 2> > E[M];
bool vis[M];
int main(int argc, char **argv) {
    	registerTestlibCmd(argc,argv);

    // registerLemonChecker(argc, argv);

    Aex = ans.readInt(), Oex = ouf.readInt();
    if (Oex != 1 && Oex != 0)
        quitf(_wa, "Invalid output.");
    if (Aex != Oex)
        quitf(_wa, "The existence of the answer is not right.");
    if (Aex == 0)
        quitf(_ok, "Accepted. No Answer.");
    n = inf.readInt();  // c
    n = inf.readInt(), m = inf.readInt();
    for (int i = 1; i <= m; i++) {
        x = inf.readInt(), y = inf.readInt();
        U[i] = x, V[i] = y;
        E[x].push_back({ y, i }), E[y].push_back({ x, i });
    }
    //	quitf(_ok,"Test.\n");
    int op, id, k = ouf.readInt(0, 2 * m + 2), now = ouf.readInt(1, n);
    bool mod = 0;
    int ST = 0;
    int SCORE = 100;
    for (int i = 1; i <= k; i++) {
        op = ouf.readInt();
        if (op != 1 && op != -1)
            quitf(_wa, "Integer \"op\" is neither 1 nor -1.");
        if (op == -1 && mod == 1)
            SCORE = min(SCORE, 25);
        if (op == -1)
            mod = 1, ST = i;
        else {
            id = ouf.readInt(1, m);
            if (SCORE != 100)
                continue;
            if (U[id] != now && V[id] != now)
                SCORE = min(SCORE, 25);
            if (U[id] != now)
                swap(U[id], V[id]);
            if (vis[id])
                SCORE = min(SCORE, 25);
            if (mod) {
                if ((ST - i) % 2 == 0)
                    vis[id] = 1;
                now = V[id];
            } else
                now = V[id], vis[id] = 1;
        }
    }
    ouf.readEoln();
    if (SCORE != 100)
        quitp(_pc(25 - 16), "You made an illegal operation!");
    for (int i = 1; i <= m; i++)
        if (!vis[i])
            quitp(_pc(25 - 16), "Some edges aren't destroyed!");
    quitf(_ok, "Accepted. Valid Constuction.");
    return 0;
}

