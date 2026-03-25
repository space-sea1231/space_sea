#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
int n, m;
deque<int> q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        q.push_back(i);
    }
    int cnt=0;
    while (!q.empty()){
        int x=q.front();
        q.pop_front();
        if (++cnt==m){
            printf("%d ", x);
            cnt=0;
        }else{
            q.push_back(x);
        }
    }

    return 0;
}