#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int M=1e2+10;
int t, n, m, k;
int dp[M][N];
vector<int> q[N];
void init(){
    for (int i=1; i<=n; i++){
        q[i].clear();
    }
    for (int l=0; l<=100; l++){
        for (int i=1; i<N; i++){
            dp[l][i]=-1;
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--){
        cin >> n >> m >> k;
        init();
        for (int i=1; i<=n; i++){
            int len;
            cin >> len;
            for (int j=1; j<=len; j++){
                int a;
                cin >> a;
                q[i].push_back(a);
            }
        }
        dp[0][1]=0;
        // printf("Debug1:\n");
        for (int l=1; l<=100; l++){
            for (int i=1; i<=n; i++){
                int len=0;
                for (int j=0; j<q[i].size(); j++){
                    int tmp=q[i][j];
                    len=max(len-1, 0LL);
                    if (len){
                        if (dp[l][tmp]==-1){
                            dp[l][tmp]=i;
                        }else if (dp[l][tmp]&&dp[l][tmp]!=i){
                            dp[l][tmp]=0;
                        }
                    }
                    if (dp[l-1][tmp]!=-1&&dp[l-1][tmp]!=i){
                        len=m;
                    }
                }
            }
        }
        for (int i=1; i<=k; i++){
            int r, c;
            cin >> r >> c;
            // printf("Debug: %d %d\n", r, c);
            if (dp[r][c]==-1){
                printf("0\n");
            }else{
                printf("1\n");
            }
        }
    }

    return 0;
}