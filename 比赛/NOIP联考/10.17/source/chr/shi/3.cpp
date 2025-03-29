#include<bits/stdc++.h>
#include<sys/time.h>
#define int long long
using namespace std;
const int N=2e6+10;
int a[N];
signed main()
{
    freopen("1.in","w",stdout);
	timeval tm;
    gettimeofday(&tm,NULL);
    mt19937 rd(tm.tv_sec*1000000+tm.tv_usec);
    int t=1000;
    cout<<t<<'\n';
    while(t--)
    {
        int n=rd()%1000+5;
        for(int i=1;i<=n;i++) cout<<(char)('0'+rd()%2);
        cout<<'\n';
    }
    return 0;
}
