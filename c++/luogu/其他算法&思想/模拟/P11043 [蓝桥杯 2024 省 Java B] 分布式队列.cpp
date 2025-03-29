#include <bits/stdc++.h>
using namespace std;
const int N=20;
const int INF=(1<<30);
int n;
int cnt[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    string s;
    while (cin >> s){
        if (s=="add"){
            cnt[1]++;
        }
        if (s=="sync"){
            int x;
            cin >> x;
            cnt[x+1]++;
        }
        if (s=="query"){
            int minn=INF;
            for (int i=1; i<=n; i++){
                minn=min(minn, cnt[i]);
            }
            printf("%d\n", minn);
        }
    }
    
    return 0;
}