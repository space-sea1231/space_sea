#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e6+10;

int n;
// vector<int> a(1), ans;

// vector<int> Mul(vector<int> &a, vector<int> &b){
//     vector<int> c(a.size()+b.size()+1);
//     int lena=a.size();
//     int lenb=b.size();
//     for (int i=0; i<lena; i++){
//         for (int j=0; j<lenb; j++){
//             c[i+j]=c[i+j]+a[i]*b[j];
//         }
//     }
//     int lenc=c.size(), x=0;
//     for (int i=0; i<lenc; i++){
//         c[i]=c[i]+x;
//         x=c[i]/10;
//         c[i]=c[i]%10;
//     }
//     while (x){
//         c.push_back(x%10);
//         x=x/10;
//     }
//     return c;
// }
// vector<int> Pow(vector<int> a, int b){
//     vector<int> sum(a.size());
//     sum[0]=1;
//     while (b>0){
//         if (b&1==true){
//             sum=Mul(sum, a);
//         }
//         a=Mul(a, a);
//         b=b>>1;
//     }
//     return sum;
// }
int a[N], ans[N], tmp[N];
int lena, lenb;
void Mul(int a[], int b[], int &lena, int &lenb){
    memset(tmp, 0, sizeof(tmp));
    for (int i=1; i<=min(501, lena); i++){
        for (int j=1; j<=min(501, lenb); j++){
            tmp[i+j-1]=tmp[i+j-1]+a[i]*b[j];
        }
    }
    lena=min(501, lena+lenb-1);
    int x=0;
    for (int i=1; i<=lena; i++){
        tmp[i]=tmp[i]+x;
        x=tmp[i]/10;
        a[i]=tmp[i]%10;
    }
    while (x>0){
        if (lena>501){
            break;
        }
        a[++lena]=x%10;
        x=x/10;
    }
    return;
}
void Pow(int a[], int b){
    ans[1]=1, lenb=1;
    while (b>0){
        if (b&1==true){
            Mul(ans, a, lenb, lena);
        }
        Mul(a, a, lena, lena);
        b=b>>1;
    }
    return;
}
void Sub(int a[], int b){
    for (int i=1; i<=lenb; i++){
        a[i]=a[i]-b;
        if (a[i]>=0){
            return;
        }
        a[i]=a[i]+10;
    }
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a[1]=2, lena=1;
    Pow(a, n);
    Sub(ans, 1);
    printf("%d", (int)ceil(n*log10(2)));
    for (int i=500; i>=1; i--){
        if (i%50==0){
            printf("\n");
        }
        printf("%d", ans[i]);
    }
    // a[0]=2; ans=Pow(a, n);
    // int len=ans.s();
    // printf("%d\n", len);
    // for (int i=499; i>=0; i--){
    //     if (i>=len){
    //         printf("0");
    //     }
    //     else{
    //         printf("%d", ans[i]);
    //     }
    // }
    return 0;
}