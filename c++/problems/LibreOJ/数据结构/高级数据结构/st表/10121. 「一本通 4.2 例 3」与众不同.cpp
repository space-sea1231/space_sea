#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int M=1e6+10;
const int Z=32;
int n, m;
int last[M<<1], pre[N];
struct Sparse_Table{
    int dp[N][Z], lg[N];
    Sparse_Table(){
        lg[0]=-1;
        for (int i=1; i<N; i++){
            lg[i]=lg[i>>1]+1;
        }
    }
    void Init(){
        for (int j=1; j<=lg[n]; j++){
            for (int i=1; i+(1<<j)-1<=n; i++){
                dp[i][j]=max(dp[i][j-1], dp[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int Query(int l, int r){
        if (l>r){
            return 0;
        }
        int len=lg[r-l+1];
        return max(dp[l][len], dp[r-(1<<len)+1][len]);
    }
}st;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        int x;
        cin >> x;
        pre[i]=max(pre[i-1], last[x+M]+1);
        st.dp[i][0]=i-pre[i]+1;
        last[x+M]=i;
    }
    st.Init();
    for (int i=1; i<=m; i++){
        int l, r;
        cin >> l >> r;
        l++, r++;
        int mid=lower_bound(pre+l+1, pre+r+1, l)-pre-1;
        printf("%d\n", max(mid-l+1, st.Query(mid+1, r)));
    }

    return 0;
}