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
    int t=3;
    cout<<t<<'\n';
    while(t--)
    {
        int n=1e6;
        for(int i=1;i<=2*n;i++) a[i]=i;
        shuffle(a+1,a+1+2*n,rd);
        for(int i=1;i<=n;i++) a[rd()%(2*n)+1]=0;
        cout<<n<<'\n';
        for(int i=1;i<=2*n;i++) cout<<a[i]<<' ';
        cout<<'\n';
    }
    return 0;
}
