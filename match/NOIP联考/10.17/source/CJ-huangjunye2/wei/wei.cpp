#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int a[10005];
int n;
long long check(){
    long long sum=0;
    for(int i=1;i<=n;i++){
        int mx=a[i];
        sum++;
        for(int j=i+1;j<=n;j++){
            if(a[j]<mx){
                break;
            }
            mx=a[j];
            sum++;
        }
    }
    return sum;
}
void work(){
    
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    long long ans=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            swap(a[i],a[j]);
            ans=max(check(),ans);
            swap(a[i],a[j]);
        }
    }
    printf("%lld\n",ans);
}
int main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--){
        work();
    }
    return 0;
}
/*

*/