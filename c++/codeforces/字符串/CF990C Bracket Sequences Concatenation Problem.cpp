#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
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
        int len=s.size(), res=0;
        for (int j=0; j<len; j++){
            if (s[j]=='('){
                sum[i]++;
            }
            else{
                if (sum[i]>0){
                    sum[i]--;
                }else{
                    res--;
                }
            }
        }
        if (res<0&&sum[i]!=0){
            sum[i]=INF;
        }
        else if (sum[i]==0){
            sum[i]=res;
        }
        if (sum[i]==0){
            ans++;
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