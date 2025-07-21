#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e3+10;
const int K=26;

int n, m, k, s;
int a[N][N];
int suma[K][N][N];
int sumb[K][N][N];
int dis[N][N];
int sx[N], sy[N], fx[N], fy[N];
char c[N];

inline int Touch(int i, int j){
    int sx1, sy1, fx1, fy1;
    sx1=sx[j], sy1=sy[j];
    if (sx1>sx[i]&&sx1<fx[i]&&sy1>sy[i]&&sy1<fy[i]){
        return 1;
    }
    sx1=sx[j], sy1=fy[j];
    if (sx1>sx[i]&&sx1<fx[i]&&sy1>sy[i]&&sy1<fy[i]){
        return 2;
    }
    sx1=fx[j], sy1=sy[j];
    if (sx1>sx[i]&&sx1<fx[i]&&sy1>sy[i]&&sy1<fy[i]){
        return 3;
    }
    sx1=fx[j], sy1=fy[j];
    if (sx1>sx[i]&&sx1<fx[i]&&sy1>sy[i]&&sy1<fy[i]){
        return 4;
    }
    return 0;
}
inline int Sum(int sx, int sy, int fx, int fy, int c){
    return suma[c][fx][fy]-suma[c][fx][sy-1]-suma[c][sx-1][fy]+suma[c][sx-1][sy-1];
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /*Input*/
    cin >> n >> m >> k >> s;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            char c;
            cin >> c;
            a[i][j]=c-'a';
        }
    }
    /*Init*/
    for (int c=0; c<26; c++){
        for (int i=1; i<=n; i++){
            for (int j=1; j<=m; j++){
                suma[c][i][j]=suma[c][i-1][j]+suma[c][i][j-1]-suma[c][i-1][j-1]+abs(c-a[i][j]);
                sumb[c][i][j]=sumb[c][i-1][j]+sumb[c][i][j-1]-sumb[c][i-1][j-1]+abs(c-a[i][j]);
            }
        }
    }
    for (int i=1; i<=k; i++){
        cin >> sx[i] >> sy[i] >> fx[i] >> fy[i] >> c[i];
        for (int j=1; j<i; j++){
            int opt=Touch(i, j);
            if (opt>0){
                int tmp=0;
                tmp=tmp+Sum(sx[i], sy[i], fx[i], fy[i], c[i]-'a');
                tmp=tmp+Sum(sx[j], sy[j], fx[j], fy[j], c[j]-'a');
                int sx1, fx1, sy1, fy1;
                if (opt==1){
                    sx1=sx[j];
                    sy1=sy[j];
                    fx1=fx[i];
                    fy1=fy[i];
                }
                if (opt==2){
                    sx1=sx[j];
                    sy1=sy[i];
                    fx1=fx[i];
                    fy1=fy[j];
                }
                if (opt==3){
                    sx1=sx[j];
                    sy1=sy[i];
                    fx1=fx[j];
                    fy1=fy[i];
                }
                if (opt==4){
                    sx1=sx[i];
                    sy1=sy[i];
                    fx1=fx[j];
                    fy1=fy[j];
                }
            }
            else{
                int tmp=0;
                tmp=tmp+Sum(sx[i], sy[i], fx[i], fy[i], c[i]-'a');
                tmp=tmp+Sum(sx[j], sy[j], fx[j], fy[j], c[j]-'a');
                dis[i][j]=dis[j][i]=tmp;
            }
        }
    }
    return 0;
}