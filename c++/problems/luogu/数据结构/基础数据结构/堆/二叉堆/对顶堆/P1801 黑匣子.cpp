#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n, m;
int a[N];
priority_queue<int> q, p;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    int last=0;
    for (int i=1; i<=m; i++){
        int x;
        cin >> x;
        for (int j=last+1; j<=x; j++){
            q.push(a[j]);
            if (q.size()==i){
                p.push(-q.top());
                q.pop();
            }
        }
        printf("%d\n", -p.top());
        q.push(-p.top());
        p.pop();
        last=x;
    }

    return 0;
}