#include <bits/stdc++.h>
using namespace std;
const int N=5e2+10;
int n, m, cnt;
int a[N][N], b[N][N];
void swing(int x, int y, int r, int z){
    for (int i=x-r; i<=x+r; i++){
        for (int j=y-r; j<=y+r; j++){
            if (z==0){
                b[x-y+j][x+y-i]=a[i][j];
            }else{
                b[x+y-j][y-x+i]=a[i][j];
            }
        }
    }
    for (int i=x-r; i<=x+r; i++){
        for (int j=y-r; j<=y+r; j++){
            a[i][j]=b[i][j];
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            a[i][j]=++cnt;
        }
    }
    for (int i=1; i<=m; i++){
        int x, y, r, z;
        cin >> x >> y >> r >> z;
        swing(x, y, r, z);
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}