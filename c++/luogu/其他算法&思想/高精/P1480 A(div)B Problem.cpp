#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e3+10;
struct Div{
    int len, b, start=1;
    int a[N], sum[N];
    void in(){
        string s;
        cin >> s >> b;
        len=s.size();
        for (int i=1; i<=len; i++){
            a[i]=s[i-1]-'0';
        }
    }
    void div(){
        int tmp=0;
        for (int i=1; i<=len; i++){
            sum[i]=(tmp*10+a[i])/b;
            tmp=(tmp*10+a[i])%b;
        }
        while (!sum[start]&&start<len){
            start++;
        }
    }
    void out(){
        for (int i=start; i<=len; i++){
            printf("%lld", sum[i]);
        }
    }
}calc;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    calc.in();
    calc.div();
    calc.out();

    return 0;
}