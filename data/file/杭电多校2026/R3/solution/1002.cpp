#include <bits/stdc++.h>
using namespace std;
typedef long double db;

inline int read(){
    char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    int ans = 0;
    while (isdigit(ch)) ans = ans * 10 + ch - '0', ch = getchar();
    return ans;
}
int n, w;
db solve(vector<int> &p){
    db s = 0;
    for(int i: p) s += 1.00 / i;
    if(s <= 1) {
        return (db)w / s;
    } else {
        vector<db> v;
        for(int i: p) v.push_back(1.00 * i / (i-1));
        sort(v.begin(), v.end(), greater<>());
        db ans = 0;
        db c = 0, k = 0;
        for(db i: v){
            c++;
            k += 1.00 / i;
            ans = max(ans, (db)w / k * (c-1));
        }
        return ans;
    }
}
int main(){
    int _ = read();
    while(_--){
        n = read(), w = read();
        vector<int> v(n);
        for(int &i: v) i = read();
        cout << fixed << setprecision(10) << solve(v) << '\n';
    }
    return 0;
}