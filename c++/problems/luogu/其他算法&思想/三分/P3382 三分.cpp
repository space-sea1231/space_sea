#include <bits/stdc++.h>
using namespace std;
const int N=20;
const double eps=1e-7;
int n;
double l, r;
double a[N];
double check(double mid){
    double sum=0;
    for (int i=n; i>=0; i--){
        sum=sum*mid+a[i];
    }
    return sum;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> l >> r;
    for (int i=n; i>=0; i--){
        cin >> a[i];
    }
    double ans=0;
    while (fabs(l-r)>=eps){
        double mid=(l+r)/2;
        if (check(mid+eps)>check(mid-eps)){
            l=mid;
        }else{
            r=mid;
            ans=mid;
        }
    }
    printf("%.5lf", ans);

    return 0;
}