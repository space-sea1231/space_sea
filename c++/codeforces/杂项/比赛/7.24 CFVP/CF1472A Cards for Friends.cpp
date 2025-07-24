#include <iostream>
#include <stdio.h>
#define __Debug
using namespace std;
typedef long long ll;
int t;
int n,w,h;
int Pow(ll a,int b){
  int sum=1;
  while(b>0){
    if(b&1==true){
      sum=sum*a;
    }
    a=a*a;
    b=b>>1;
  }
  return sum;
}
signed main(){
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  cin>>t;
  while(t--){
    cin>>w>>h>>n;
    int cnt=0;
    while(w%2==0){
      if(cnt>=30){
        break;
      }
      w=w>>1;
      cnt++;
    }
    while (h%2==0){
      if(cnt>=30){
        break;
      }
      h=h>>1;
      cnt++;
    }
    if(Pow(2,cnt)>=n){
      printf("YES\n");
    }
    else{
      printf("NO\n");
    }
  }
  return 0;
}