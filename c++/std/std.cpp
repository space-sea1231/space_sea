#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int Maxn=1e6+5;
char s[Maxn];
int n,m,x[Maxn],y[Maxn],c[Maxn],sa[Maxn];//c->原字符串出现次数的前缀和
int height[Maxn],rk[Maxn];
void SA()
{	
    for(int i=1;i<=n;i++){x[i]=s[i];++c[x[i]];}
    for(int i=2;i<=m;i++)c[i]+=c[i-1];
    for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
    for(int i=1;i<=n;i++) printf("%d ", sa[i]);//sa->排名第i的字符的位置
    printf("\n");
    for(int k=1;k<=n;k=k<<1)
    {	
        int num=0;
        for (int i=n-k+1;i<=n;++i) y[++num]=i;
        for(int i=1;i<=n;i++)
            if(sa[i]>k)y[++num]=sa[i]-k;
        for(int i=1;i<=m;i++)c[i]=0;
        for(int i=1;i<=n;i++)c[x[i]]++;
        for(int i=2;i<=m;i++)c[i]+=c[i-1];
        for(int i=n;i>=1;i--){sa[c[x[y[i]]]--]=y[i];y[i]=0;}
        swap(x,y);
        num=1;x[sa[1]]=1;
        for(int i=2;i<=n;i++)
        {	
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])x[sa[i]]=num;
            else x[sa[i]]=++num;
        }
        if(num==n)break;
        m=num;
    }
    for(int i=1;i<=n;i++)
        printf("%d ",sa[i]);
    printf("\n");
}
int main()
{	
    scanf("%s",s+1);
    n=strlen(s+1);
    m=122;
    SA();
    //LCP(); 
    return 0;
}
