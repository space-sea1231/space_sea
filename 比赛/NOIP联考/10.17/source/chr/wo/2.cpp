#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=20;
int a[N],b[N];
void run()
{
    int n;
    cin>>n;
    for(int i=1;i<=2*n;i++) cin>>a[i],b[i]=i;
    int ans=0;
    do
    {
        bool flag=1;
        for(int i=1;i<=2*n;i++) if(a[i]&&a[i]!=b[i]) flag=0;
        if(!flag) continue;
        int now=0;
        for(int i=1;i<=2*n;i+=2) now+=abs(b[i]-b[i+1]);
        ans=max(ans,now);
    } while (next_permutation(b+1,b+1+2*n));
    int cnt=0;
    do
    {
        bool flag=1;
        for(int i=1;i<=2*n;i++) if(a[i]&&a[i]!=b[i]) flag=0;
        if(!flag) continue;
        int now=0;
        for(int i=1;i<=2*n;i+=2) now+=abs(b[i]-b[i+1]);
        cnt+=now==ans;
    } while (next_permutation(b+1,b+1+2*n));
    cout<<cnt<<'\n';
}
signed main()
{
    freopen("1.in","r",stdin);
    freopen("2.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) run();
	return 0;
}
