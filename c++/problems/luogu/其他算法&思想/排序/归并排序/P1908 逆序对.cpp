#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int n, ans;
int a[N], tmp[N];
void Merge(int l, int r){
    if (l==r){
        return ;
    }
    int mid=(l+r)>>1LL;
    Merge(l, mid);
    Merge(mid+1, r);
    int ptr_l=l, ptr_r=mid+1, ptr_tmp=l;
    while (ptr_l<=mid&&ptr_r<=r){
        if (a[ptr_l]<=a[ptr_r]){
            tmp[ptr_tmp++]=a[ptr_l++];
        }else{
            tmp[ptr_tmp++]=a[ptr_r++];
            ans+=mid-ptr_l+1;
        }
    }
    while (ptr_l<=mid){
        tmp[ptr_tmp++]=a[ptr_l++];
    }
    while (ptr_r<=r){
        tmp[ptr_tmp++]=a[ptr_r++];
    }
    for (int i=l; i<=r; i++){
        a[i]=tmp[i];
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    Merge(1, n);
    printf("%lld\n", ans);

    return 0;
}