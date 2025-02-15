#include<bits/stdc++.h>
using namespace std;
const int N=20;
const int mod=998442353;
int a[N];
int n,m;
int s[N];
int T;
void slove1(){
    for(int i=1;i<=m;i++)cin >> a[i];
    int mini=1e9,maxi=-1e9,minid,maxid;
    for(int i=1;i<=m;i++){
        if(mini>a[i]){
            mini=a[i];
            minid=i;
        }
        if(maxi<a[i]){
            maxi=a[i];
            maxid=i;
        }
    }
    int minans=2e9,cnt=0;
    for(int i=1;i<=m;i++){
        int x;
        cin >> x;
        if(x==0)continue;
        int cntans=min(abs(a[i]-maxi),abs(a[i]-mini));
        if(cntans<minans){
            minans=cntans;
            cnt=1;
        }else if(minans==cntans){
            cnt++;
        }
    }
    cout << (minans+abs(mini-maxi))%mod << " " << cnt << "\n";
}
void slove(){
    cin >> n >> m;
    if(n==1)slove1();   
    else{
        int x;
        for(int j=1;j<=n;j++)for(int i=1;i<=m;i++)cin >> a[i];
        for(int i=1;i<=m;i++)cin >> x;
    }
    return ;
}
int main(){
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
    cin >> T;
    while(T--){
        slove();
    }
}