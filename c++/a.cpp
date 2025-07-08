#include <algorithm>
#include <cstdio>
using std::min;
long long n,k,ans;
int main(int argc,char *argv[])
{
	scanf("%lld %lld",&n,&k);
	for(long long l=1,r,t;l<=n;l=r+1)
		r=(t=k/l) ? min(k/t,n) : n;
        ans-=t*(r-l+1)*(l+r)>>1;
	printf("%lld\n",ans+n*k);
	return 0;
}