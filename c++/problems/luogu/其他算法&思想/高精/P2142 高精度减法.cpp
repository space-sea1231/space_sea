#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct Sub{
    int len_a, len_b, len;
    int a[N], b[N], sum[N];
    bool flag=0;
    bool check(){
        if (len_a==len_b){
            for (int i=1; i<=len_a; i++){
                if (a[i]<b[i]){
                    return 1;
                }
            }
            return 0;
        }
        if (len_a<len_b){
            return 1;
        }else{
            return 0;
        }
    }
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
        if (check()){
            for (int i=1; i<=len_a; i++){
                sum[i]=a[i];
            }
            memset(a, 0, sizeof(a));
            for (int i=1; i<=len_b; i++){
                a[i]=b[i];
            }
            memset(b, 0, sizeof(b));
            for (int i=1; i<=len_a; i++){
                b[i]=sum[i];
            }
            swap(len_a, len_b);
            flag=1;
        }
    }
    void sub(){
        int tmp=0;
        len=max(len_a, len_b);
        for (int i=1; i<=len; i++){
            if (a[i]<b[i]){
                a[i+1]--;
                a[i]+=10;
            }
            sum[i]=a[i]-b[i];
        }
        while (!sum[len]&&len>1){
            len--;
        }
    }
    void out(){
        if (flag){
            printf("-");
        }
        for (int i=len; i>=1; i--){
            printf("%d", sum[i]);
        }
    }
}calc;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    calc.in();
    calc.sub();
    calc.out();

    return 0;
}