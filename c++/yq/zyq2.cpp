#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
struct cxt{
    int x,y1,y2,flag;
}s[800001],t[800001];
int comp(cxt a,cxt b){ return a.x==b.x?a.flag>b.flag:a.x<b.x;}
int n,m,x,y,x1,y1,z,tot,a[800001],b[800001],xb=400001,ans;
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
    {
        scanf("%d%d%d%d",&x,&y,&x1,&y1);           
        s[++tot].x=x;s[tot].y1=y;s[tot].y2=y1;s[tot].flag=1;
        t[tot].x=y;t[tot].y1=x;t[tot].y2=x1;t[tot].flag=1;
        s[++tot].x=x1;s[tot].y1=y;s[tot].y2=y1;
        t[tot].x=y1;t[tot].y1=x;t[tot].y2=x1;
    }
    sort(s+1,s+tot+1,comp);
    sort(t+1,t+tot+1,comp);
    for (int i=1;i<=tot;++i)
    {
        if (s[i].flag) for (int j=s[i].y1;j<s[i].y2;++j) {if (!a[j+xb]) ++ans;++a[j+xb];}
          else for (int j=s[i].y1;j<s[i].y2;++j) {--a[j+xb];if (!a[j+xb]) ++ans;}
        if (t[i].flag) for (int j=t[i].y1;j<t[i].y2;++j) {if (!b[j+xb]) ++ans;++b[j+xb];}
          else for (int j=t[i].y1;j<t[i].y2;++j) {--b[j+xb];if (!b[j+xb]) ++ans;}
    }
    printf("%d",ans);
}