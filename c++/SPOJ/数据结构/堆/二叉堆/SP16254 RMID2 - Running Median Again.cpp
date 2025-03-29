#include <bits/stdc++.h>
using namespace std;
int t, n;
priority_queue<int> q;
priority_queue<int, vector<int>, greater<int> > p;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        int cnt=0;
        while (cin >> n){
            if (n==-1){
                printf("%d\n", q.top());
                q.pop();
                cnt--;
                if (q.size()<(cnt+1)/2){
                    int tmp=p.top();
                    p.pop();
                    q.push(tmp);
                }
            }else{
                q.push(n);
                cnt++;
                if (q.size()>(cnt+1)/2){
                    int tmp=q.top();
                    q.pop();
                    p.push(tmp);
                }
            }
        }
    }
    return 0;
}