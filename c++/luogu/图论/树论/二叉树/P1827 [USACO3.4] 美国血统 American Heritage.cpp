#include <bits/stdc++.h>
using namespace std;
string a, b;
void go(string x, string y){
    if (x.empty()){
        return ;
    }
    char root=x[0];
    int cut=y.find(root);
    x.erase(x.begin());
    string x_l=x.substr(0, cut);
    string x_r=x.substr(cut);
    string y_l=y.substr(0, cut);
    string y_r=y.substr(cut+1);
    go(x_l, y_l);
    go(x_r, y_r);
    printf("%c", root);
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> a >> b;
    go(b, a);

    return 0;
}