#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int Z=32;
int n, m;
struct Sparse_Table{
    int dp[N][Z], lg[N];
    Sparse_Table(){
        lg[0]=-1;
        for (int i=1; i<N; i++){
            lg[i]=lg[i>>1]+1;
        }
    }
    void init(){
        for (int j=1; j<=lg[n]; j++){
            for (int i=1; i+(1<<j)-1<=n; i++){
                dp[i][j]=max(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int query(int l, int r){
        int len=lg[r-l+1];
        return max(dp[l][len], dp[r-(1<<len)+1][len]);
    }
}st;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> st.dp[i][0];
    }
    st.init();
    cin >> m;
    for (int i=1; i<=m; i++){
        int l, r;
        cin >> l >> r;
        printf("%d\n", st.query(l, r));
    }

    return 0;
}