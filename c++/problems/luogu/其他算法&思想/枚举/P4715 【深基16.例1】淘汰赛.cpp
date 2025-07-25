#include <bits/stdc++.h>
using namespace std;
const int N=10;
const int INF=1<<30;
int n;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    int max_1=-INF, max_2=-INF;
    int id_1, id_2;
    for (int i=1; i*2<=(1<<n); i++){
        int a;
        cin >> a;
        if (max_1<a){
            max_1=a;
            id_1=i;
        }
    }
    for (int i=(1<<n)/2+1; i<=(1<<n); i++){
        int a;
        cin >> a;
        if (max_2<a){
            max_2=a;
            id_2=i;
        }
    }
    if (max_1<max_2){
        printf("%d", id_1);
    }else{
        printf("%d", id_2);
    }

    return 0;
}