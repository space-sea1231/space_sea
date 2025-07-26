#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e6+5;
int T,n,a[N],ans=0;
string as;vector<int> v,ansv;
int nand(int x,int y){
	return (x==0&&y==0);
} 
void dfs(int x,int ii){
	int sum=0;
	for (int i=1;i<=n;i++){
//		cout<<a[i]<<' ';
		 sum+=a[i];
	}
//	cout<<endl;
	if (ans<sum){
		ans=sum;
		ansv=v;
	}
	if (x>n)	return;
	if (ii>=n)	return;
	for (int i=1;i<n;i++){
		int yb=a[i-1],ya=a[i+1];
		a[i-1]=nand(a[i-1],a[i]);
		a[i+1]=nand(a[i+1],a[i]);
		v.push_back(i); 
		dfs(x+1,ii+1);
		v.pop_back();
		a[i-1]=yb;a[i+1]=ya;
	}
}
signed main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		cin>>as;n=as.size();ans=0;
		v.clear();ansv.clear();
		int flag=0;
		for (int i=1;i<=as.size();i++){
			a[i]=a[i+1]=a[i+2]=0;;
			a[i]=as[i-1]-'0';
			flag+=a[i];
		}
		if (!flag){
			if (n<=2){
				printf("0 0\n");
				continue;
			}
			printf("%lld %lld\n",(n+1)/2,n/2);
			for (int i=2;i<=n;i+=2){
				printf("%lld ",i);
			}
			puts("");
			continue;
		}
		if (flag==1){
			if (n<=2){
				printf("1 0\n");
				continue;
			}int cnt=0; 
			for (int i=2;i<n;i++){
				if (a[i]==1){
					continue;
				}
				a[i-1]=nand(a[i],a[i-1]);a[i+1]=nand(a[i],a[i+1]);ansv.push_back(i);
			}
			for (int i=1;i<=n;i++){
				if (a[i])	cnt++;
			}
			printf("%lld %lld\n",cnt,ansv.size());
			for (int i=0;i<ansv.size();i++)	printf("%lld ",ansv[i]);
			puts("");
			continue;
		}
		dfs(1,2);
		printf("%lld %lld\n",ans,ansv.size());
		for (int i=0;i<ansv.size();i++){
			printf("%lld ",ansv[i]);
		}
		printf("\n");
	}
	return 0;
}

