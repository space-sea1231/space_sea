#include<bits/stdc++.h>
using namespace std;
int T,n,tz[2000005],cnt,x,las,qwq[2000005];
#define ll long long
const ll mod=998244353;
ll ans,su,jc1,ans2,jc2;
int main(){
   freopen("wo.in","r",stdin);
   freopen("wo.out","w",stdout);
   ios::sync_with_stdio(false);
   cin.tie(0),cout.tie(0);
   cin>>T;
   while(T--){
   ans=cnt=0;cin>>n;n*=2;jc1=jc2=ans=ans2=su=0;jc1=jc2=su=1;
   for(int i=1;i<=n;i++)tz[i]=qwq[i]=0;
   for(int i=1;i<=n;i++){
   cin>>x;
   if((i&1)==0)
   if(x==0||las==0){cnt++;if(x==0&&las==0)su=(su*2)%mod;}
   else tz[x]=tz[las]=1;
   if(x!=0)qwq[x]=1;
   las=x;
   }
   //cout<<cnt<<endl;
   for(int i=n;i>=1;i--)
   if(tz[i]==0)
   if(cnt>0){if(qwq[i]==0){ans++,jc1=(jc1*ans)%mod;}cnt--;}
   else {if(qwq[i]==0){ans2++;jc2=(jc2*ans2)%mod;}}
  // cout<<"lsm"<<ans2<<endl;
   cout<<(((jc1*jc2)%mod)*su)%mod<<"\n";
   }
}
