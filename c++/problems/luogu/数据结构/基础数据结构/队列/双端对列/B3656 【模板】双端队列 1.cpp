#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
list<int> q[N];
int n;
string c;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int x,y;
    for (int i=1; i<=n; i++){
        cin >> c;
        // printf("Debug: %s\n", c);
        if (c=="push_front"){
            cin >> x >> y;
            q[x].push_front(y);
        }
        if (c=="push_back"){
            cin >> x >> y;
            q[x].push_back(y);
        }
        if (c=="pop_front"){
            cin >> x;
            if (q[x].empty()){
                continue;
            }
            q[x].pop_front();
        }
        if (c=="pop_back"){
            cin >> x;
            if (q[x].empty()){
                continue;
            }
            q[x].pop_back();
        }
        if (c=="size"){
            cin >> x;
            printf("%ld\n",q[x].size());
        }
        if (c=="front"){
            cin >> x;
            if (q[x].empty()){
                continue;
            }
            printf("%d\n",q[x].front());
        }
        if (c=="back"){
            cin >> x;
            if (q[x].empty()){
                continue;
            }
            printf("%d\n",q[x].back());
        }
    }
    return 0;
}