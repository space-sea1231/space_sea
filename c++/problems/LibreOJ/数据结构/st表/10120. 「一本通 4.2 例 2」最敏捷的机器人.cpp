#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int Z=32;
int n, m;
struct Sparse_Table{
    int lg[N], a[N];
    int dp[N][Z], pd[N][Z];
    Sparse_Table(){
        lg[0]=-1;
        for (int i=1; i<N; i++){
            lg[i]=lg[i>>1]+1;
        }
    }
    void init(){
        for (int i=1; i<=n; i++){
            dp[i][0]=a[i];
            pd[i][0]=a[i];
        }
        for (int j=1; j<=lg[n]; j++){
            for (int i=1; i+(1<<j)-1<=n; i++){
                dp[i][j]=max(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
                pd[i][j]=min(pd[i][j-1], pd[i+(1<<(j-1))][j-1]);
            }
        }
    }
    void query(int l, int r){
        int len=lg[r-l+1];
        int maxn=max(dp[l][len], dp[r-(1<<len)+1][len]);
        int minn=min(pd[l][len], pd[r-(1<<len)+1][len]);
        printf("%d %d\n", maxn, minn);
    }
}st;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> st.a[i];
    }
    st.init();
    for (int i=1; i+m-1<=n; i++){
        st.query(i, i+m-1);
    }

    return 0;
}