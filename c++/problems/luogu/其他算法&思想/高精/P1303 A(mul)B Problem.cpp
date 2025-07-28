#include <bits/stdc++.h>
using namespace std;
const int N=2e3+10;
struct Mul{
    int len_a, len_b, len;
    int a[N], b[N], sum[N<<1];
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
    }
    void mul(){
        int tmp=0;
        len=len_a+len_b;
        for (int i=1; i<=len_a; i++){
    		for (int j=1; j<=len_b; j++){
    			tmp=(a[i]*b[j]+sum[i+j-1])/10;
    			sum[i+j-1]=(a[i]*b[j]+sum[i+j-1])%10;
    			sum[i+j]+=tmp;
    		}
    	}
        while (!sum[len]&&len>1){
            len--;
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
    calc.mul();
    calc.out();

    return 0;
}