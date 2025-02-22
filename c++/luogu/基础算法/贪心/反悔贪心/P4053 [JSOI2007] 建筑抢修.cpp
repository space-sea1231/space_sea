#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int n;
int sum;
struct Node{
    int v, w;
    bool operator<(const Node &x)const{
        return w<x.w;
    }
}e[N];
priority_queue<int> q;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> e[i].v >> e[i].w;
    }
    sort(e+1, e+n+1);
    for (int i=1; i<=n; i++){
        q.push(e[i].v);
        sum+=e[i].v;
        if (e[i].w<=sum){
            sum-=q.top();
            q.pop();
        }
    }
    int ans=q.size();
    printf("%lld\n", ans);

    return 0;
}