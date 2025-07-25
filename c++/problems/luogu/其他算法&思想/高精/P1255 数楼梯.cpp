#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=5e3+10;

int n;
int ans1[N], ans2[N], ans3[N], tmp[N];
int len1, len2, len3;

void Add(){
    for (int i=0; i<len2; i++){
        ans1[i]=ans2[i]+ans3[i];
    }
    int x=0;
    for (int i=0; i<len1; i++){
        ans1[i]=ans1[i]+x;
        x=ans1[i]/10;
        ans1[i]=ans1[i]%10;
    }
    while (x>0){
        ans1[len1++]=x%10;
        x=x/10;
    }
    len3=len2;
    for (int i=0; i<len2; i++){
        ans3[i]=ans2[i];
    }
    len2=len1;
    for (int i=0; i<len1; i++){
        ans2[i]=ans1[i];
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    ans1[0]=ans2[0]=ans3[0]=1;
    len1=len2=len3=1;
    for (int i=2; i<=n; i++){
        Add();
    }
    for (int i=len1-1; i>=0; i--){
        printf("%d", ans1[i]);
    }
    return 0;
}
/*
0 1 2
      --
    --
  --
--
*/