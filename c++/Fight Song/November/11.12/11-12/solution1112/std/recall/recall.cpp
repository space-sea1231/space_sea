#include<bits/stdc++.h>
using namespace std;
int n,e;
vector<int> ans;
void MoLing_qwq(){
    scanf("%d",&n);
    if(n==1){puts("1");return;}
    e=0;
    while((1<<e)<=n)++e;
    if((1<<e)-1==n){puts("-1");return;}
    ans.clear();
    if(n%2==0){
        for(int i=2;i<=n;i+=2)ans.push_back(i),ans.push_back(i-1);
    }
    else if(n%4==1){
        ans.push_back(n);
        for(int i=2;i<n;i+=2)ans.push_back(i),ans.push_back(i-1);
    }
    else if(n%4==3){
        int p=-1;
        for(int i=2;i<n;i+=2)if((i&n)!=i){p=i;break;}
        ans.push_back(n);
        for(int i=p;i<n;i+=2)ans.push_back(i),ans.push_back(i-1);
        for(int i=2;i<p;i+=2)ans.push_back(i),ans.push_back(i-1);
    }
    for(int i=0;i<n;++i)printf("%d%c",ans[i],i==n-1?'\n':' ');
}
int main(){
    freopen("recall.in","r",stdin);
    freopen("recall.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)MoLing_qwq();
    return 0;
}
