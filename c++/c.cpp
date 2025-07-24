#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=2e5+10;

int t;
int n;
int a[N];
int f[N];

signed main(){
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  cin >> t;
  while (t--){
    cin >> n;
    /*Input*/
    for (int i=1; i<=n; i++){
      cin >> a[i];
    } 
    /*Init*/
    for (int i=1; i<=n; i++){
      f[i]=0;
    }
    /*Solve*/
    int ans=0;
    for (int i=1; i<=n; i++){
      if (a[i]+i<=n){
        f[i+a[i]]=max(f[i+a[i]], f[i]+a[i]);
      }
      f[i]=f[i]+a[i];
      ans=max(ans, f[i]);
    }
    printf("%d\n", ans);
  }
  return 0;
}