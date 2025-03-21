#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
void dfs1(int len,int off,vector<int> &v){
    if(len<3) return ;
    if(len%2){
        for(int i=1;i<len;i+=2){
            v.push_back(off+i);
        }
        dfs1(len-2,off+1,v);
    }
    else{
        dfs1(len-1,off,v);
        int mid=len/2;
        v.push_back(off+mid);
        for(int i=mid+1;i<len-2;i+=2){
            v.push_back(i+off);
            if(i+1<len-2)
            v.push_back(i+off+1);
        }
        dfs1(len-3,off+mid-1,v);
    }
}
void work(){
    string s;
    cin>>s;
    int n=s.length();
    s=' '+s;
    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=s[i]-'0';                                                                        
    }
    if(sum==0){
        vector<int> v;
        printf("%d 0\n\n",n>=3?n==4?2:n-1:0);
    }
    else if(sum==1){
        int pos=0;                         
        for(int i=1;i<=n;i++){
            if(s[i]=='1'){
                pos=i;
            }
        }
        if((pos-1)%2==0||(n-pos)%2==0){
            printf("%d 0\n\n",n>3?n-1:1);
        }
        else{
            printf("%d 0\n\n",n-2);
        }
    }
}
int main(){
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--){
        work();
    }
    return 0;
}
/*

*/