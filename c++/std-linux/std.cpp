#include <bits/stdc++.h>
using namespace std;
const int N=5e2+10;
struct Add{
    int len_a, len_b, len;
    int a[N], b[N], sum[N];
    void in(){
        string s;
        cin >> s;
        len_a=s.size();
        for (int i=1; i<=len_a; i++){
            a[i]=s[len_a-i]-'0';
        }
        cin >> s;
        len_b=s.size();
        for (int i=1; i<=len_b; i++){
            b[i]=s[len_b-i]-'0';
        }
    }
    void add(){
        int tmp=0;
        len=max(len_a, len_b);
        for (int i=1; i<=len; i++){
            sum[i]=a[i]+b[i]+tmp;
            tmp=sum[i]/10;
            sum[i]%=10;
        }
        if (tmp){
            sum[++len]=tmp;
        }
    }
    void out(){
        for (int i=len; i>=1; i--){
            printf("%d", sum[i]);
        }
    }
}calc;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    calc.in();
    calc.add();
    calc.out();

    return 0;
}