#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n;
long long ans;
struct Node{
    int v, w;
    bool operator<(const Node &x)const{
        return v<x.v;
    }
}e[N];
priority_queue<int, vector<int>, greater<int> > q;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> e[i].v >> e[i].w;
    }
    sort(e+1, e+n+1);
    for (int i=1; i<=n; i++){
        if (e[i].v<=q.size()){
            if (e[i].w>q.top()){
                ans-=q.top();
                q.pop();
                q.push(e[i].w);
                ans+=e[i].w;
            }
        }else{
            q.push(e[i].w);
            ans+=e[i].w;
        }
    }
    printf("%lld\n", ans);

    return 0;
}