#include<bits/stdc++.h>
using namespace std;
const int N=4e5+10;
int t,n,p[N],cnt,id[N],tot;
unsigned int ans,res;
void calc(){
	res=1;
	cnt=1;
	tot=0;
	id[1]=++tot;
	for(int i=2;i<=n;i++){
		if(p[i]>p[i-1])cnt++;
		else{
			cnt=1;
			tot++;
		}
		id[i]=tot;
		res+=cnt;
	}
}
int main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>p[i];
		}
		calc();
		ans=res;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				swap(p[i],p[j]);
				calc();
				ans=max(ans,res);
				swap(p[i],p[j]);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
