#include <bits/stdc++.h>
#define N 150005
using namespace std;
typedef long long ll;

int n, num[N*3], tot;
struct Pnt { int x, y, z; } p[N];
vector <int> vecx[N*3], vecy[N*3], vecz[N*3];
int mxx, mxy, mxz, curx[N*3], cury[N*3], curz[N*3];
int cnt[N];
bool vst[N];

queue <int> q;

inline void ins (int i)
{
    cnt[i]++;
    if (cnt[i]>=2 && !vst[i]) { q.push(i); vst[i]=1; }
}

int main ()
{
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);

    scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        scanf("%d %d %d", &p[i].x, &p[i].y, &p[i].z);
        num[++tot]=p[i].x;
        num[++tot]=p[i].y;
        num[++tot]=p[i].z;
    }

    sort(num+1, num+tot+1);
    tot=unique(num+1, num+tot+1)-(num+1);
    for (int i=1; i<=n; i++) {
        p[i].x=lower_bound(num+1, num+tot+1, p[i].x)-num;
        p[i].y=lower_bound(num+1, num+tot+1, p[i].y)-num;
        p[i].z=lower_bound(num+1, num+tot+1, p[i].z)-num;
        vecx[p[i].x].push_back(i); mxx=max(mxx, p[i].x);
        vecy[p[i].y].push_back(i); mxy=max(mxy, p[i].y);
        vecz[p[i].z].push_back(i); mxz=max(mxz, p[i].z);
    }

    for (int i=1; i<=n; i++) {
        if (p[i].x==mxx) { ins(i); }
        if (p[i].y==mxy) { ins(i); }
        if (p[i].z==mxz) { ins(i); }
    }
    for (int i=1; i<=tot; i++) {
        curx[i]=vecx[i].size();
        cury[i]=vecy[i].size();
        curz[i]=vecz[i].size();
    }

    while (!q.empty()) {
        int id=q.front(); q.pop();
        curx[p[id].x]--; cury[p[id].y]--; curz[p[id].z]--;

        bool ok=0;
        while (mxx && !curx[mxx]) { mxx--; ok=1; }
        if (ok) {
            for (int i=0; i<(int)vecx[mxx].size(); i++) {
                int j=vecx[mxx][i]; ins(j);
            }
        }
        ok=0;
        while (mxy && !cury[mxy]) { mxy--; ok=1; }
        if (ok) {
            for (int i=0; i<(int)vecy[mxy].size(); i++) {
                int j=vecy[mxy][i]; ins(j);
            }
        }
        ok=0;
        while (mxz && !curz[mxz]) { mxz--; ok=1; }
        if (ok) {
            for (int i=0; i<(int)vecz[mxz].size(); i++) {
                int j=vecz[mxz][i]; ins(j);
            }
        }
    }

    if (!mxx && !mxy && !mxz) { printf("-1\n"); }
    else { printf("%d\n", num[mxx]+num[mxy]+num[mxz]); }

    return 0;
}