#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
int n, m;
int sum;
int a[N];
char c[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> c >> m;
    int len=strlen(c);
    for(int i=0;i<len;i++){
        if(c[i]>='A') c[i]=c[i]-'A'+10;
        if(c[i]>='0'&&c[i]<='9') c[i]-='0'; 
    }
    for (int i=0; i<len; i++){
        sum=sum*n+c[i];
    }
    vector<char> q;
    while(sum){
        char tmp;
        if (sum%m>=10){
            tmp='A'+sum%m-10;
        }else{
            tmp=sum%m+'0';
        }
        q.push_back(tmp);
        sum/=m;
    }
    reverse(q.begin(),q.end());
    for(char i:q){
        printf("%c",i);
    }

    return 0;
}