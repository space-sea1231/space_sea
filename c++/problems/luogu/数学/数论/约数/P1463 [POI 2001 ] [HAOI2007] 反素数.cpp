#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e6+10;

int n;
int maxn, ans;
int prime[11]={0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

ll Pow(ll a, ll b){
    if (b==0){
        return 1;
    }
    ll sum=1;
    while (b){
        if (b&1){
            sum*=a;
        }
        a*=a;
        b>>=1;
    }
    return sum;
}
void Dfs(int dep, int pre, int sum, int cnt){
    if (dep==11){
        if (cnt>maxn||(cnt==maxn&&sum<ans)){
            maxn=cnt;
            ans=sum;
        }
        return;
    }
    for (int i=0; i<=pre&&Pow(prime[dep], i)*sum<=n; i++){
        Dfs(dep+1, i, Pow(prime[dep], i)*sum, cnt*(i+1));
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    Dfs(1, 31, 1, 1);
    printf("%d\n", ans);

    return 0;
}