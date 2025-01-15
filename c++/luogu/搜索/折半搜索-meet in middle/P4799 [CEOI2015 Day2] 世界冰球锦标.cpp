#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=50;
int n, m, ans;
int money[N];
vector<int> a, b;
void serch(int l, int r, int sum, vector<int> &q){
    if (sum>m){
        return ;
    }
    if (l>r){
        q.push_back(sum);
        return ;
    }
    serch(l+1, r, sum, q);
    serch(l+1, r, sum+money[l], q);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> money[i];
    }
    serch(1, (n>>1), 0, a);
    serch((n>>1)+1, n, 0, b);
    sort(a.begin(), a.end());
    for (int i=0; i<b.size(); i++){
        ans+=upper_bound(a.begin(), a.end(), m-b[i])-a.begin();
    }
    printf("%lld", ans);

    return 0;
}