#include<bits/stdc++.h>
using namespace std;
const int N=5e4+5;
int n,m;
int len;
int L[N],R[N];
int pos[N],a[N];
int lh[N],rh[N];
stack<int> q;
void update0(int x){
    int y=pos[x];
    a[x]=1;
    lh[y]=min(lh[y],x-1);
    rh[y]=max(rh[y],x+1);
    return ;
}
void update1(int x){
    int y=pos[x];
    a[x]=0;
    int i;
    for(i=L[y];i<=R[y];i++){
        if(a[i]==1)break;
    }
    lh[y]=i-1;
    for(i=R[y];i>=L[y];i--){
        if(a[i]==1)break;
    }
    rh[y]=i+1;
    return ;
}
int query(int x){
    int y=pos[x];
    int lt=x,rt=x;
    int i;
    if(a[x]==1)return 0;
    for(i=x;i>=L[y];i--){
        if(a[i]==1)break;
    }
    lt=min(x,i+1);
    int res=lt;
    if(lt==L[y]&&a[L[y]]!=1){
        int cnt=y-1;
        while(cnt>0&&rh[cnt]==L[cnt]&&a[L[cnt]]!=1){
            cnt--;
        }
        lt=rh[cnt];
        if(cnt<=0)lt=1;;
    }
    for(i=x;i<=R[y];i++){
        if(a[i]==1)break;
    }
    rt=max(x,i-1);
    int cnt=y;
    if(rt==R[y]&&a[R[y]]!=1){
        int cnt=y+1;
        while(cnt<=len&&lh[cnt]==R[cnt]&&a[R[cnt]]!=1){
            cnt++;
        }
        rt=lh[cnt];
        if(cnt>len)rt=n;
    }
    if(rt-lt+1<0)exit(res);
    return rt-lt+1;
}
int main(){
    cin >> n >> m;
    len=sqrt(n);
    for(int i=1;i<=len;i++){
        L[i]=R[i-1]+1;
        R[i]=len*i;
        lh[i]=R[i];
        rh[i]=L[i];
    }
    if(R[len]!=n){
        len++;
        R[len]=n;
        L[len]=R[len-1]+1;
        lh[len]=R[len];
        rh[len]=L[len];
    }
    for(int i=1;i<=len;i++){
        for(int j=L[i];j<=R[i];j++){
            pos[j]=i;
        }
    }
    while(m--){
        char opt;
        int x;
        cin >> opt;
        if(opt=='D'){
            cin >> x;
            q.push(x);
            update0(x);
        }else if(opt=='R'){
            x=q.top();
            q.pop();
            update1(x);
        }else{
            cin >> x;
            cout << query(x) << "\n";
        }
    }
    return 0;
}