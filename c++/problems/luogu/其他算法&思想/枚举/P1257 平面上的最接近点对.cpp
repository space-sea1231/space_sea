#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
const int INF=(1<<30);
int n;
double x[N], y[N];
double ans=INF;
double dis(int a, int b){
    return sqrt(abs(x[a]-x[b])*abs(x[a]-x[b])+abs(y[a]-y[b])*abs(y[a]-y[b]));
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> x[i] >> y[i];
        for (int j=1; j<i; j++){
            ans=min(ans, dis(i, j));
        }
    }
    printf("%.4lf", ans);
    
    return 0;
}