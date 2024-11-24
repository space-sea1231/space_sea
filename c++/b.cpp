#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int n,pl;
double a[1001][1001];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
       for(int j=1;j<=n+1;j++)
       cin>>a[i][j];
    for(int i=1;i<=n;i++)
    {
        pl=i;
        for(int j=i;j<=n;j++) {
        	if(a[j][i]>a[pl][i]) pl=i;
		}                                     
        if(a[pl][i]==0) {cout<<"No Solution";return 0;} //无解或有自由元   
        for(int j=1;j<=n+1;j++)
        swap(a[i][j],a[pl][j]);
        double k=a[i][i];
        for(int j=1;j<=n+1;j++)
        a[i][j]=a[i][j]/k; 
        for(int j=1;j<=n;j++)
        {
            if(i!=j)
            { 
                double ki=a[j][i];
                for(int m=1;m<=n+1;m++)
                a[j][m]=a[j][m]-ki*a[i][m];
            }
        }
    }
    for(int i=1;i<=n;i++)
    printf("%.2lf\n",a[i][n+1]);
    return 0;
}