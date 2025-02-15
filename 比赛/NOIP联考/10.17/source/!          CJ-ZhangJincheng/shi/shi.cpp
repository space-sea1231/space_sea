#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 1000010
int t,n,a[N];
string s;
signed main(){
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>t;
    while(t--){
        cin>>s;
        n=s.size();
        s=" "+s;
        int sum=0,pos=0;
        for(int i=1;i<=n;i++){
            a[i]=s[i]-'0';
            if(a[i]){
                sum++;
                pos=i;
            }
        }
        if(sum>1){
            cout<<"Manba out!\n";
            continue;
        }
        if(sum==0){
            int tmp=n/3;
            cout<<tmp*2<<' '<<tmp<<endl;
            for(int i=1;i<=tmp;i++){
                cout<<tmp*3-1<<' ';
            }
            cout<<endl;
        }
        else{
            if(sum==1){
                if((pos%2)==1){
                    int nn=n-1,sum=0,pp=pos,tmp=nn/3;
                    while(pp!=1){
                        pp-=2;
                        sum++;
                    }
                    sum+=tmp;
                    cout<<tmp*2+1<<' '<<sum<<endl;
                    while(pos!=1){
                        cout<<pos-1<<' ';
                        pos-=2;
                    }
                    for(int i=1;i<=tmp;i++){
                        cout<<tmp*3<<" ";
                    }
                    cout<<endl;
                }
                else{
                    if((pos%2)==(n%2)){
                        int nn=n-1,sum=0,pp=pos,tmp=nn/3;
                        while(pp!=n){
                            sum++;
                            pp+=2;
                        }
                        sum+=tmp;
                        cout<<tmp*2+1<<' '<<sum<<endl;
                        while(pos!=n){
                            cout<<pos+1<<' ';
                            pos+=2;
                        }
                        for(int i=1;i<=tmp;i++){
                            cout<<tmp*3-1<<' ';
                        }
                        cout<<endl;
                    }
                    else{
                        int nn=n-2,sum=0,pp=pos,tmp=nn/3;
                        while(pp!=2){
                            sum++;
                            pp-=2;
                        }
                        sum+=tmp;
                        cout<<tmp*2+1<<' '<<sum<<endl;
                        while(pos!=2){
                            cout<<pos-1<<' ';
                            pos-=2;
                        }
                        for(int i=1;i<=tmp;i++){
                            cout<<tmp*3+1<<' ';
                        }
                        cout<<endl;
                    }
                }
            }
        }
    }
    return 0;
}