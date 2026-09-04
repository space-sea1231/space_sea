#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
const int maxn=50000;
int f[21],ans[21],a[10000];
int ansd[1000000];
int len,n,k;
bool vis[maxn];
double ansx=1000000000,lg[1000];  //g为第g个质因数。
void dfs(int tol,double d,int g){ //d为当前的答案（用log缩小）
    if(ansx<d||g==16) return; //剪枝1
    if(tol==1){
        if(ansx>d){
            memcpy(ans,f,sizeof(f));
            ansx=d;
        }
        return;
    }
    for(int i=0;(i+1)*(i+1)<=tol;i++)
    if(tol%(i+1)==0){  //剪枝2
        f[g]=i;
        dfs(tol/(i+1),d+f[g]*lg[a[g]],g+1);
        f[g]=tol/(i+1)-1;
        dfs(i+1,d+f[g]*lg[a[g]],g+1);
        f[g]=0;
    }
}

void mem(){  //线性筛求素数，没有必要。
    vis[1]=1;
    int m=sqrt(maxn+0.05);
    for(int i=2;i<=m;i++)
    if(!vis[i]){
        for(int j=i*i;j<maxn;j+=i)
        vis[j]=1;
    }
    for(int i=2;i<=maxn;i++)
    if(!vis[i]){
        a[k]=i;
        if(k<=20) lg[a[k]]=log(a[k]);
        k++;
    }
}

int main(){
    mem();
    scanf("%d",&n);
    dfs(n,0,0);
    int top=0,x=0;
    ansd[0]=1;
    for(int i=0;i<=20;i++)
    while(ans[i]){  //高精乘低精
        ans[i]--;
        x=0;
        for(int j=0;j<=top;j++){
            ansd[j]=a[i]*ansd[j]+x;
            if(ansd[j]>=10){
                x=ansd[j]/10;
                ansd[j]=ansd[j]%10;
                if(j==top) top++;
            }else x=0;
        }
    }
    for(int i=top;i>=0;i--)
    printf("%d",ansd[i]);
    printf("\n");
    return 0;
}
