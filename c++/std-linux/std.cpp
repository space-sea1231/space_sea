#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n;
int ans;
int a[N];
priority_queue<int, vector<int> greter<int> > q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    for (int i=1; i<=n; i++){
        q.push(a[i]);
        if (q.top()<a[i]){
            ans+=a[i]-q.top();
            q.pop();
            q.push(a[i]);
        }
    }
    printf("%d\n", ans);

    return 0;
}