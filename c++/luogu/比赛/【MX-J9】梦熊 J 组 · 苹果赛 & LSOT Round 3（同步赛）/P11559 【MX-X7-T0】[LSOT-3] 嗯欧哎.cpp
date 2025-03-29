#include <bits/stdc++.h>
using namespace std;
int a[3];
bool A(int a){
    return a>=85&&a<=100;
}
bool B(int a){
    return a>=45&&a<=84;
}
bool C(int a){
    return a>=25&&a<=44;
}
bool D(int a){
    return a>=1&&a<=24;
}
bool check(){
    if (B(a[1])&&C(a[2])&&D(a[3])){
        return 1;
    }
    if (A(a[1])&&B(a[2])&&C(a[3])){
        return 1;
    }
    if (A(a[1])&&A(a[2])&&(B(a[3])||C(a[3]))){
        return 1;
    }
    if (A(a[1])&&A(a[2])&&A(a[3])){
        return 1;
    }
    return 0;
}
bool cmp(int a, int b){
    return a>b;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    for (int i=1; i<=3; i++){
        cin >> a[i];
    }
    sort(a+1, a+3+1, cmp);
    if (check()){
        printf("Yes\n");
    }else{
        printf("No\n");
    }
    return 0;
}