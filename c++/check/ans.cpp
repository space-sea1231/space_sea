#include<bits/stdc++.h>
using namespace std;
int a[110],qian[110],hou[110];

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int minn=1e9;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            minn=min(minn,a[i]);
        }
        bool fl=1;
        for(int i=1;i<=n;i++){
            if(a[i]%minn){
                fl=0;break;
            }
        }
        if(fl){
            cout<<n-1<<"\n";
            continue;
        }
        hou[n+1]=0;
        for(int i=1;i<=n;i++)qian[i]=__gcd(qian[i-1],a[i]);
        for(int i=n;i>=1;i--)hou[i]=__gcd(hou[i+1],a[i]);
        fl=0;
        for(int i=1;i<=n;i++){
            int G=0;
            for(int j=1;j<=n;j++){
                if(j==i)continue;
                if(a[j]%a[i]==0)continue;
                G=__gcd(G,a[j]);
            }
            if(G>a[i]){
                fl=1;break;
            }
        }
        if(fl){
            cout<<n<<"\n";
            continue;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i]%a[j]==1){
                    fl=1;break;
                }
            }
        }
        if(fl){
            cout<<n<<"\n";
            continue;
        }
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                int A=min(a[i],a[j]),B=max(a[i],a[j]);
                int yu=B%A;
                if(yu==0)continue;
                if(a[i]==B){
                    if(__gcd(qian[i-1],hou[i+1])%yu==0){
                        fl=1;
                        break;
                    }
                }
                else{
                    if(__gcd(qian[j-1],hou[j+1])%yu==0){
                        fl=1;
                        break;
                    }
                }
            }
        }
        if(fl){
            cout<<n<<"\n";
            continue;
        }
        cout<<n+1<<"\n";
    }
    return 0;
}
/*
3 3 3
4 3 4
5 3 5
6 3 3
7 3 3
8 3 4

*/