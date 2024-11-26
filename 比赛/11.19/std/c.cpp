#include <bits/stdc++.h>
#define N 504
#define mod 998244353
using namespace std;
typedef long long ll;

int n, m, aa[N], a[N], pos0, tot;
bool vst[N];
int pre[N], suf[N];
ll f[N][N], sump[N][N], sums[N][N];

struct Pnt { int fi, se; } rec[N];

void cal ()
{
    for (int l=1; l<=tot+1; l++) {
        for (int r=l; r<=tot+1; r++) {
            sump[l][r]=(sump[l][r-1]+f[l][r]) %mod;
        }
    }
    for (int r=1; r<=tot+1; r++) {
        for (int l=r; l>=1; l--) {
            sums[l][r]=(sums[l+1][r]+f[l][r]) %mod;
        }
    }
}

int main ()
{
  std::freopen("c.in", "r", stdin);
  std::freopen("c.out", "w", stdout);
    scanf("%d %d", &n, &m);
    for (int i=1; i<=m; i++) { scanf("%d", &aa[i]); vst[aa[i]]=1; if (!aa[i]) { pos0=i; } }

    int mn=-1;
    for (int i=0; i<n; i++) if (!vst[i]) { mn=i; break; }
    if (mn==-1) { printf("1\n"); return 0; }

    for (int i=1; i<=m; i++) if (aa[i]) { a[++tot]=aa[i]; }
    pre[0]=n; for (int i=1; i<=tot; i++) { pre[i]=min(pre[i-1], a[i]); }
    suf[tot+1]=n; for (int i=tot; i>=1; i--) { suf[i]=min(suf[i+1], a[i]); }

    for (int i=1; i<=tot+1; i++) { rec[i]=(Pnt){ pre[i-1], suf[i] }; }

    if (vst[0]) { f[pos0][pos0]=1; }
    else {
        for (int i=1; i<=tot+1; i++) { f[i][i]=1; }
    }
    cal();

    for (int i=1; i<n; i++) {
        if (!vst[i]) {
            for (int l=1; l<=tot+1; l++) {
                for (int r=l; r<=tot+1; r++) {
                    f[l][r]=0;
                    if (rec[r].se>i) { f[l][r]+=sump[l][r]; }
                    if (rec[l].fi>i) { f[l][r]+=sums[l][r]; }
                    f[l][r]%=mod;
                }
            }
        }
        cal();
    }

    ll ans=0;
    for (int l=1; l<=tot+1; l++) {
        for (int r=l; r<=tot+1; r++) { ans+=f[l][r]; ans%=mod; }
    }
    printf("%lld\n", ans);

    return 0;
}