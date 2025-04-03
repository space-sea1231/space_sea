#include <bits/stdc++.h>
using namespace std;
signed main(){
    freopen("change.in", "r", stdin);
    freopen("change.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    while (getline(cin, s)){
        if (*s.end()=='\n'){
            s.erase(s.end()-1);
        }
        s='"'+s+'"'+',';
        cout << s << endl;
    }

    return 0;
}