#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
// #define __Debug

using namespace std;
typedef long long ll;

const int N=3e5+10;
const int INF=0x3f3f3f3f;

int n, k;
ll ans;
int sum[N];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    string s;
    for (int i=1; i<=n; i++){
        cin >> s;
        int len=s.size();
        bool flag=false;
        if (s[0]==')'&&s[len-1]=='('){
            sum[i]=INF;
            continue;
        }
        for (int j=0; j<len; j++){
            if (s[j]=='('){
                sum[i]++;
            }
            else{
                sum[i]--;
            }
            if (sum[i]<0){
                flag=true;
            }
        }
        if ((sum[i]<0&&s[len-1]=='(')||(sum[i]>0&&s[0]==')')){
            sum[i]=INF;
        }
        if (sum[i]==0){
            if (flag==false){
                ans++;
            }
            sum[i]=INF;
        }
    }
    sort(sum+1, sum+n+1);
    ans=ans*ans;
    #ifdef __Debug
        for (int i=1; i<=n; i++){
            printf("%d ", sum[i]);
        }
        printf("\n");
    #endif
    for (int i=1; i<=n; i++){
        if (sum[i]>=0) break;
        int l=lower_bound(sum+1+i, sum+n+1, -sum[i])-sum;
        int r=upper_bound(sum+1+i, sum+n+1, -sum[i])-sum;
        ans=ans+r-l;
    }
    printf("%lld\n", ans);

    return 0;
}
//)()(
//()))(