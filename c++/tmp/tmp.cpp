#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    int tmp[99]={11, 1, 2, 3, 4, 5, 6, 11, 11, 11, 11, 23};
    int a=22, n=7;
    // int l=1, r=n, pos=n;
    // while (l<=r){
    //     int mid=(l+r)>>1;
    //     if (tmp[0]+tmp[mid]>=a){
    //         pos=mid;
    //         r=mid-1;
    //     }else{
    //         l=mid+1;
    //     }
    // }
    int pos=lower_bound(tmp+1, tmp+n+1, a-tmp[0])-tmp;
    printf("%d\n", pos);
    return 0;
}