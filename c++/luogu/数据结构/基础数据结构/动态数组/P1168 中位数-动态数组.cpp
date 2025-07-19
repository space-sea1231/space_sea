#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n;
vector<int> q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        int a;
        cin >> a;
        q.insert(lower_bound(q.begin(), q.end(), a), a);
        if (i%2){
            printf("%d\n", q[i/2]);
        }
    }
    return 0;
}