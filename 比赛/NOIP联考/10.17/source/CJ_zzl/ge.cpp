#include<bits/stdc++.h>
using namespace std;
int n,m,T,x[20],mi,mi1,ma,ma1,op[20];
int main(){
freopen("ge.in","r",stdin);
freopen("ge.out","w",stdout);
   cin>>T;
   while(T--){
   cin>>n>>m;mi1=ma1=1;mi=1e9,ma=0;ma1=0;
   for(int i=1;i<=m;i++){cin>>x[i];if(x[i]<mi){mi=x[i],mi1=1;}if(x[i]>ma){ma=x[i],ma1=1;}}mi1=1000000000;
   for(int i=1;i<=m;i++){cin>>op[i];if(op[i]==1){if((ma-x[i])+ma-mi<mi1)mi1=(ma-x[i])+ma-mi,ma1=0;if((x[i]-mi)+ma-mi<mi1)mi1=(x[i]-mi)+ma-mi,ma1=0;if((x[i]-mi)+ma-mi==mi1)ma1++;if((ma-x[i])+ma-mi==mi1)ma1++;}}
   if(mi1==1000000000){cout<<"NIE\n";continue;}
   cout<<mi1<<" "<<ma1<<"\n";
   }
}
