#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

ll a[33]={0, 3, 2, 1,  3, 1, 2,  3, 2, 1,  2, 3, 1,  3, 2, 1,       3, 2, 1,  3, 1, 2,  3, 2, 1,  2, 3, 1,  3, 2, 1, 3};
ll b[33]={0, 1, 2, 3,  1, 3, 2,  1, 2, 3,  2, 1, 3,  1, 2, 3,       1, 2, 3,  1, 3, 2,  1, 2, 3,  2, 1, 3,  1, 2, 3, 1};
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    printf("5\n");
    printf("32 ");
    int sum=1;
    for (int i=0; i<32; i++){
        sum+=a[i];
        printf("%d ", sum);
    }
    sum=2;
    printf("\n");
    printf("32 ");
    for (int i=0; i<32; i++){
        sum+=b[i];
        printf("%d ", sum);
    }
    printf("\n");

    return 0;
}