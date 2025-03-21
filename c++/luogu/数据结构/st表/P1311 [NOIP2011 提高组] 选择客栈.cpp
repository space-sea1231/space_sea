#include <bits/stdc++.h>
using namespace std;
const int N=2e6+10;
const int M=1e4+10;
const int Z=32;
int n, m, k, ans;
int color[N], last[M];
int sum[M], cnt[M];
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
                dp[i][j]=min(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int query(int l, int r){
        int len=lg[r-l+1];
        return min(dp[l][len], dp[r-(1<<len)+1][len]);
    }
}st;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m >> k;
    for (int i=1; i<=n; i++){
        cin >> color[i] >> st.dp[i][0];
    }
    st.init();
    for (int i=1; i<=n; i++){
        if (sum[color[i]]){
            int tmp=st.query(last[color[i]], i);
            if (tmp<=k){
                ans+=sum[color[i]];
                cnt[color[i]]=sum[color[i]];
            }else{
                ans+=cnt[color[i]];
            }
        }
        last[color[i]]=i;
        sum[color[i]]++;
    }
    printf("%d\n", ans);

    return 0;
}