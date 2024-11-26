#include<bits/stdc++.h>
using namespace std;
int T,n,sum,op1,op2,cnt,ans[10000005];
string s;
void inline del_to_only_one(){
   for(int i=1;i<n;i++)
   if(s[i]=='1'&&s[i-1]=='1'){cnt++;ans[cnt]=i;s[i-1]='0';s[i+1]='0';}
   else if(s[i]=='0'&&s[i-1]=='1'){cnt++;ans[cnt]=i;s[i-1]='0',s[i]='0',s[i+1]=((s[i+1]=='0')^48);}
   if(s[n-1]=='1'&&s[n]=='1'){cnt++;ans[cnt]=n-1;s[n]='0';}
}
void inline handsome(){
   int x=n-(s[n]=='0');
   cnt++;ans[cnt]=x-2;
   cnt++;ans[cnt]=x-1;
   cnt++;ans[cnt]=x-2;
   s[n]=s[n-1]='0';
   return ;
}
void inline beautiful(){
  cnt++;ans[cnt]=n-4;
  cnt++;ans[cnt]=n-1;
  cnt++;ans[cnt]=n-2;
  cnt++;ans[cnt]=n-1;
  s[n-5]='1';
}
void inline wonderful(int x){
  if(x%2==0)
  {for(int i=x+1;i<=n;i+=2){cnt++;ans[cnt]=i;}s[x]='0',s[n]='1';}
  if(x%2==1)
  {for(int i=x-1;i>=1;i-=2){cnt++;ans[cnt]=i;}s[x]='0',s[1]='1';}
}
void inline QAQ(int l,int r){
//cout<<"?"<<l<<" "<<r<<" "<<cnt<<endl;
   while(1){
   if(r<=l+1)return ;
   if(r==l+2){cnt++;ans[cnt]=l+1;return ;}
   if(r==l+4){cnt++;ans[cnt]=l+1;cnt++;ans[cnt]=l+3;cnt++;ans[cnt]=l+2;return ;}
   cnt++;ans[cnt]=l+1;
   cnt++;ans[cnt]=l+3;
   cnt++;ans[cnt]=l+2;
   cnt++;ans[cnt]=l+3;
   cnt++;ans[cnt]=l+2;
   l++;
   }
}
int main(){
freopen("shi.in","r",stdin);
freopen("shi.out","w",stdout);
ios::sync_with_stdio(false);
cin.tie(0),cout.tie(0);
   cin>>T;
   while(T--){
   cin>>s;
   n=s.size();cnt=0;sum=0;op1=0;op2=0;
   s=" "+s;
   for(int i=1;i<=n;i++)if(s[i]=='1'){sum++;if(i%2==1)op1++;else op2++;}
   if(n==1||n==2){cout<<sum<<" "<<0<<"\n";continue;}
   if(n==3){if(sum==0)cout<<2<<" "<<1<<"\n"<<2<<"\n";else cout<<sum<<" "<<0<<"\n";continue;}
   if(n==4&&sum!=1&&(sum!=2||op1!=op2)){
   if(sum==0)cout<<2<<" "<<1<<"\n"<<2<<"\n";
   else cout<<sum<<" "<<0<<"\n";
   continue;
   }
   if(sum==n){cout<<n<<" "<<0<<"\n";continue;}
   cout<<n-1<<" ";
   del_to_only_one();sum=0;
   for(int i=1;i<=n;i++){sum+=(s[i]=='1');}
   if(n%2==1&&sum==1)handsome();
   if(n%2==0&&sum==0)beautiful();
   if(n%2==0)for(int i=1;i<=n;i++)if(s[i]=='1'){wonderful(i);break;}
   QAQ(1+(s[1]=='1'),n-(s[n]=='1'));
   cout<<min(13*n,cnt)<<"\n";
   for(int i=1;i<=min(13*n,cnt);i++)cout<<ans[i]<<" ";
   cout<<"\n";
   }
}
