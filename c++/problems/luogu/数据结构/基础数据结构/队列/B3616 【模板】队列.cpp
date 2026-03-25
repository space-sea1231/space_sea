#include <bits/stdc++.h>
using namespace std;
int n;
queue<int> q;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        int opt;
        cin >> opt;
        if (opt==1){
            int x;
            cin >> x;
            q.push(x);
        }
        if (opt==2){
            if (!q.empty()){
                q.pop();
            }else{
                printf("ERR_CANNOT_POP\n");
            }
        }
        if (opt==3){
            if (!q.empty()){
                printf("%d\n", q.front());
            }else{
                printf("ERR_CANNOT_QUERY\n");
            }
        }
        if (opt==4){
            int siz=q.size();
            printf("%d\n", siz);
        }
    }

    return 0;
}