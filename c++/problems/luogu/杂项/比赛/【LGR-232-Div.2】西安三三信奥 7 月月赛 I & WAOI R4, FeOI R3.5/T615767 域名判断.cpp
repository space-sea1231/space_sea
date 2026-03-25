#include <iostream>
#include <stdio.h>
#include <string>
// #define __Debug

using namespace std;
typedef long long ll;

string s;

signed main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    cin >> s;
    int len=s.size();
    for (int i=0; i<len; i++){
        s[i]=tolower(s[i]);
    }
    bool last=false, flag=false;
    for (int i=0; i<len; i++){
        if (s[i]=='.'){
            if (s.substr(i+1, 3)=="edu"){
                last=true, flag=true;
            }
            if (s.substr(i+1, 2)=="cn"&&last==true){
                printf("%d ", i+3);
            }
            if (flag==false){
                last=false;
            }
            flag=false;
        }
    }
    return 0;
}