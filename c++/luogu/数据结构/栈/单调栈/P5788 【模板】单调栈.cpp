#include <bits/stdc++.h>
using namespace std;
const int N=3e6+10;
int n;
int pos[N];
struct Node{
    int val, id;
};
stack <Node> s;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        int x;
        cin >> x;
        while (!s.empty()&&x>s.top().val){
            pos[s.top().id]=i;
            s.pop();
        }
        s.push({x, i});
    }
    for (int i=1; i<=n; i++){
        printf("%d ", pos[i]);
    }

    return 0;
}