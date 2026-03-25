#include <bits/stdc++.h>
using namespace std;
const int N=2e3+10;
int n, m, t, k;
int C[N][N], ans[N][N];
void Build(){
    C[0][0]=1;
    C[1][0]=C[1][1]=1;
    for (int i=2; i<=N-10; i++){
        C[i][0]=1;
        for (int j=1; j<=i; j++){
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%k;
            ans[i][j]=ans[i-1][j]+ans[i][j-1]-ans[i-1][j-1];
            if (!C[i][j]){
                ans[i][j]++;
            }
        }
        ans[i][i+1]=ans[i][i];
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t >> k;
    Build();
    while (t--){
        cin >> n >> m;
        printf("%d\n", ans[n][min(n, m)]);
    }

    return 0;
}