#include <bits/stdc++.h>
using namespace std;
const int N=4e4+10;
const int M=2e2+10;
int n, m;
int a[N], idx[N];
int L[N], R[N], Z[N];
int cnt[M][N], sum[M][N];
int pos[N], tot[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
        idx[i]=a[i];
    }
    sort(idx+1, idx+n+1);
    int len=unique(idx+1, idx+n+1)-idx-1;
    for (int i=1; i<=n; i++){
        a[i]=lower_bound(idx+1, idx+len+1, a[i])-idx-1;
    }
    int siz=sqrt(n);
    for (int i=1; i<=siz; i++){
        L[i]=(i-1)*siz+1;
        R[i]=i*siz;
    }
    if (R[siz]<n){
        siz++;
        L[siz]=R[siz-1]+1;
        R[siz]=n;
    }
    for (int i=1; i<=siz; i++){
        for (int j=L[i]; j<=R[i]; j++){
            sum[i][a[j]]++;
            pos[j]=i;
        }
        for (int j=1; j<=len; j++){
            sum[i][j]+=sum[i-1][j];
        }
    }
    for (int i=1; i<=siz; i++){
        for (int j=i; j<=siz; j++){
            int maxn=cnt[i][j-1];
            for (int k=L[i]; k<=R[j]; k++){
                if (sum[j][a[k]]-sum[i-1][a[k]]>sum[j][maxn]-sum[i-1][maxn]||(sum[j][a[k]]-sum[i-1][a[k]]==sum[j][maxn]-sum[i-1][maxn]&&a[j]<maxn)){
                    maxn=a[k];
                }
            }
            cnt[i][j]=maxn;
        }
    }
    int z=0;
    for (int i=1; i<=m; i++){
        int x, y;
        cin >> x >> y;
        x=(x+z-1)%n+1, y=(y+z-1)%n+1;
        if (x>y){
            swap(x, y);
        }
        int l=pos[x], r=pos[y];
        int maxn=0;
        if (r-l>1){
            maxn=cnt[l+1][r-1];
            for (int j=x; j<=R[l]; j++){
                tot[a[j]]++;
            }
            for (int j=L[r]; j<=y; j++){
                tot[a[j]]++;
            }
            for (int j=x; j<=R[l]; j++){
                int tmp=sum[r-1][a[j]]-sum[l][a[j]]+tot[a[j]];
                int pre=sum[r-1][maxn]-sum[l][maxn]+tot[maxn];
                if (tmp>pre||(tmp==pre&&a[j]<maxn)){
                    maxn=a[j];
                }
            }
            for (int j=L[r]; j<=y; j++){
                int tmp=sum[r-1][a[j]]-sum[l][a[j]]+tot[a[j]];
                int pre=sum[r-1][maxn]-sum[l][maxn]+tot[maxn];
                if (tmp>pre||(tmp==pre&&a[j]<maxn)){
                    maxn=a[j];
                }
            }
            for (int j=x; j<=R[l]; j++){
                tot[a[j]]=0;
            }
            for (int j=L[r]; j<=y; j++){
                tot[a[j]]=0;
            }
        }else{
            for (int j=x; j<=y; j++){
                tot[a[j]]++;
            }
            for (int j=x; j<=y; j++){
                if (tot[a[j]]>tot[maxn]||(tot[a[j]]==tot[maxn]&&a[j]<maxn)){
                    maxn=a[j];
                }
            }
            for (int j=x; j<=y; j++){
                tot[a[j]]=0;
            }
        }
        z=idx[maxn];
        printf("%d\n", z);
    }

    return 0;
}