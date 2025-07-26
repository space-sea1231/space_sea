#include<bits/stdc++.h>
using namespace std;
const int N=4e5+5;
int T,n;
int p[N];
int dp[N];
int ans;
void check(){
    for(int i=1;i<=n;i++)dp[i]=1;
    int sum=0;
    for(int i=1;i<=n;i++){
        if(p[i]>p[i-1]){
            dp[i]+=dp[i-1];
        }
        sum+=dp[i];
    }
    ans=max(ans,sum);
    return ;
}
int main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    cin >> T;
    while(T--){
        ans=0;
        cin >> n;
        for(int i=1;i<=n;i++){
            cin >> p[i];
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                swap(p[i],p[j]);
                check();
                swap(p[i],p[j]);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}